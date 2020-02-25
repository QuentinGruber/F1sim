//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Cars.h"
#include "utils.h"

void Cars::Display_info() { /// Display car's info and if not automated ask user to choose an adjustment
    std::cout << "\n[" << name << "'s info] " << std::endl;
    std::cout << "\nSpeed on the last lap : " << speed << "km/h" << std::endl;
    std::cout << "tyre pressure : " << tyre_pressure << "%" << " {Fix this with 1}" << std::endl;
    std::cout << "tyre wear : " << tyre_wear << "%" << " {Fix this with 2}" << std::endl;
    std::cout << "Fuel tank : " << fuel << "L" << " {Fix this with 3}" << std::endl;
    std::cout << "Motor's oil wear : " << oil << "%" << " {Fix this with 4}" << std::endl;
    std::cout << "Engine temperature : " << motor_temperature << " degres" << std::endl;
    std::cout << "DRS wear : " << wear_DRS << "%" << " {Fix this with 5}" << std::endl;
    std::cout << "anti-lock braking system wear : " << wear_anti_locking << "%" << " {Fix this with 6}" << std::endl;
    std::cout << "brake system wear : " << wear_braking_system << "%" << " {Fix this with 7}"
              << std::endl;
    std::cout << "Wear of the steering column : " << wear_column_direction << "%" << std::endl;
    std::cout << "Wear of the car's bodywork : " << wear_carriage << "%" << std::endl;
    if (!automated) // useless to display if automated
        std::cout << "\nChoose if you want to fix something or not ( press 0 ): ";
}

void Cars::Wear(float Distance_lap, float bends) {
    /// Applies a degradation to the different elements of the car according to the properties of the car,
    /// the length of the lap and the number of bends.

    int Crash_log = 0;
    // 0.00003% pressure loss per meter at more than 100km/h and 0.0003% during bends
    tyre_pressure -= (0.00003f * Distance_lap + 0.0003f * bends) * (speed /
                                                                    10);
    tyre_wear -= (0.00001f * Distance_lap + 0.00001f * bends) * (speed / 10);
    fuel -= (75 * (Distance_lap / 1000)) / 100; // 75 litres of oil per 100 km(on average)
    oil -= (0.00001f * Distance_lap) * (motor_temperature / 10);


    if (tyre_pressure <= 0.0) Crash_log = 1;
    if (tyre_wear <= 0.0) Crash_log = 2;
    if (fuel <= 0.0) Crash_log = 3;
    if (motor_temperature >= 130.0) Crash_log = 4;
    if (wear_DRS <= 25.0) Crash_log = 5;
    if (wear_anti_locking <= 25.0) Crash_log = 6;
    if (wear_braking_system <= 25.0) Crash_log = 7;
    if (wear_column_direction <= 25.0) Crash_log = 8;
    if (wear_carriage <= 30.0) Crash_log = 9;
    if(Random_crash()) Crash_log = 10;
    /// If a telemetry element has reached a critical state:
    /// \n -Send a crash log.
    /// \n -Set HasCrashed to true.
    switch (Crash_log) {
        case 1 :
            std::cout << "[CRASH " << name << "] His tires reached a critical pressure level !" << std::endl;
            HasCrashed = true;
            break;
        case 2 :
            std::cout << "[CRASH " << name << "] One of his tires blew out !" << std::endl;
            HasCrashed = true;
            break;
        case 3:
            std::cout << "[CRASH " << name << "] Ran out of gas to finish the lap !" << std::endl;
            HasCrashed = true;
            break;
        case 4:
            std::cout << "[CRASH " << name << "] Engine damaged due to its temperature !" << std::endl;
            HasCrashed = true;
            break;
        case 5:
            std::cout << "[CRASH " << name << "] DRS excessively damaged !" << std::endl;
            HasCrashed = true;
            break;
        case 6:
            std::cout << "[CRASH " << name << "] Anti-locking excessively damaged !" << std::endl;
            HasCrashed = true;
            break;
        case 7:
            std::cout << "[CRASH " << name << "] Braking system excessively damaged !" << std::endl;
            HasCrashed = true;
            break;
        case 8:
            std::cout << "[CRASH " << name << "] Column direction excessively damaged !" << std::endl;
            HasCrashed = true;
            break;
        case 9:
            std::cout << "[CRASH " << name << "] Carriage excessively damaged !" << std::endl;
            HasCrashed = true;
            break;
        case 10:
            std::cout << "[CRASH " << name << "] Crashed due to a technical problem !" << std::endl;
            HasCrashed = true;
            break;
        default:
            break;
    }
    if(HasCrashed)
        // set global time to "Crash time"
        global_time = 40404; // 40404 to be sure that we can't get this time without crashing
    // "Crash time" is a time that we use to identify that a car has crash
}

bool Cars::Random_crash() { /// Randomly generate a car crash influenced by car's element wear
    float Start_Crash_chance = 100000;  /// 1 in 100000 chance that the car will crash if his element are new one

    float crash_chance_increase = (300-(wear_braking_system + wear_DRS + wear_anti_locking));
    float Crash_chance = ((Start_Crash_chance / (crash_chance_increase + 1 )) * (wear_column_direction / 100));
    if (utils::rnd_number(0.0, Crash_chance) < 1) {
        HasCrashed = true;
        global_time = 40404; /// set global time to "Crash Time"
        return true;
    } else return false;

}


void Cars::Generate_speed() {/// Randomly generate car average speed during a lap
    /// Minimum average speed = 200 km/h Maximum average speed = 323 km/h
    int Speed = 200 + (utils::rnd_number(1.0, 100.0) * 123) / 100;
    speed = Speed;
    motor_temperature += (Speed / motor_temperature);
}


void Cars::adjustment(int Choice) {
    /// Adjust the car in function of the user's choice
    switch (Choice) {
        case 1 :
            Tyre_inflation();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 2:
            Change_tyre();
            penality = 20;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 3:
            // Fuel pumps may not exceed 12.1 litres per second.
            penality = ((95 - fuel) / 12.1) + 5.0; // minimum 5 second penalty
            std::cout << " Penality : " << penality << "sec" << std::endl;
            refill_fuel();
            break;
        case 4 :
            change_oil();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 5 :
            fix_DRS();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 6 :
            fix_anti_lock();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 7 :
            fix_braking_system();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 666: // CHEAT CODE / Easter egg
            std::cout << "[666] HAIL SATAN !!! [666]" << std::endl;
            std::cout << "[666] You sold your soul to the devil ! [666}" << std::endl;
            global_time = -666; // will win the race
            break;
        default:
            break;
    }
}


void Cars::auto_adjustment() { /// auto-adjust the car to avoid it to crash
    penality = 0;
    int User_choice;
    if (fuel < 10) {
        User_choice = 3;
    } else if (tyre_wear < 20) {
        User_choice = 2;
    } else if (oil < 85) {
        User_choice = 4;
    } else if (tyre_pressure < 40) {
        User_choice = 1;
    } else if (wear_DRS < 70) {
        User_choice = 5;
    } else if (wear_anti_locking < 70) {
        User_choice = 6;
    } else if (wear_braking_system < 70) {
        User_choice = 7;
    } else {
        User_choice = 0;
    }

    adjustment(User_choice);
    lower_engine_temperature();
}

void Cars::manual_adjustment() {
    /// Ask user to choose an adjustment
    penality = 0;
    int User_choice;
    std::cin >> User_choice;
    adjustment(User_choice);
    lower_engine_temperature();
}


void Cars::Tyre_inflation() {
    tyre_pressure += 30; /// add +30% of pressure to tyre
    /// tyre pressure can't be at 100% if the wear of the tire isn't
    if (tyre_pressure > (100.0 - (100 - tyre_wear) / 2)) {
        tyre_pressure = 100.0 - (100 - tyre_wear) / 2;
    }
    std::cout << "Tyre pressure : " << tyre_pressure << "%";
}

void Cars::Change_tyre() {
    /// Set tyre wear & tyre pressure to 100% like new one
    tyre_pressure = 100;
    tyre_wear = 100;
    std::cout << "New tyres installed ! ";
}

void Cars::refill_fuel() {
    /// Set fuel to max capacity
    fuel = 95;
    std::cout << "Full fuel tank ! ";
}

void Cars::change_oil() {
    /// Set oil to 100%
    oil = 100;
    std::cout << "Engine oil level restored ! " << std::endl;
}

void Cars::fix_DRS() {
    /// Repairs the DRS at 80%.
    if (wear_DRS < 80) {
        wear_DRS = 80;
        std::cout << "DRS fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on DRS ! " << std::endl;
    }
}

void Cars::fix_braking_system() {
    /// Repairs the braking system at 80%.
    if (wear_braking_system < 80) {
        wear_braking_system = 80;
        std::cout << "sysfreinage fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on sysfreinage ! " << std::endl;
    }
}

void Cars::fix_anti_lock() {
    /// Repairs the anti-lock at 80%.
    if (wear_anti_locking < 80) {
        wear_anti_locking = 80;
        std::cout << "antiblocage fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on antiblocage ! " << std::endl;
    }
}

void Cars::lower_engine_temperature() {
    /// Cooled the engine by 1 degrees per second at standstill if oil is at 100%
    motor_temperature -= (1 * (oil/100)) * penality;
    /// can't be inferior to 80 degres
    if (motor_temperature < 80) {
        motor_temperature = 80;
    }

}

