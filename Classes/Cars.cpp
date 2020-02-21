//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Cars.h"
#include "utils.h"

void Cars::Display_info() {
    std::cout << "\n[" << name << "'s info] " << std::endl;
    std::cout << "\nVitesse lors du dernier tour : " << speed << "km/h" << std::endl;
    std::cout << "pression_pneu : " << pression_pneu << "%" << " {Fix this with 1}" << std::endl;
    std::cout << "usure des pneu : " << usure_pneu << "%" << " {Fix this with 2}" << std::endl;
    std::cout << "Reservoir d'essence : " << fuel << "L" << " {Fix this with 3}" << std::endl;
    std::cout << "Taux d'huile : " << oil << "%" << " {Fix this with 4}" << std::endl;
    std::cout << "Temperature du moteur : " << temperature_moteur << " degres" << std::endl;
    std::cout << "Usure du DRS : " << usure_DRS << "%" << " {Fix this with 5}" << std::endl;
    std::cout << "Usure du systeme d'antiblocage : " << usure_antiblocage << "%" << " {Fix this with 6}" << std::endl;
    std::cout << "Usure du systeme de freinage : " << usure_systeme_freinage << "%" << " {Fix this with 7}"
              << std::endl;
    std::cout << "Usure de la colonne de direction : " << usure_colonne_direction << "%" << std::endl;
    std::cout << "Usure de la carroserie : " << usure_carroserie << "%" << std::endl;
    std::cout << "\nChoose if you want to fix something or not ( press 0 ): ";
}

void Cars::Wear(float Distance_Tour,float nb_virages) {
    // TODO: add some crash option ? with randomness
    int Crash_log = 0;
    // 0.00003% pressure loss per meter at more than 100km/h and 0.0003% during turns
    pression_pneu -= (0.00003f * Distance_Tour + 0.0003f * nb_virages) * (speed /
                                                                          10);
    usure_pneu -= (0.00001f * Distance_Tour + 0.00001f * nb_virages) * (speed / 10);
    fuel -= (75 * (Distance_Tour / 1000)) / 100; // 75 litres of oil per 100 km(on average)

    if (pression_pneu <= 0.0) Crash_log = 1;
    if (usure_pneu <= 0.0) Crash_log = 2;
    if (fuel <= 0.0) Crash_log = 3;

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
            std::cout << "[CRASH " << name << "] ran out of gas to finish the lap !" << std::endl;
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

void Cars::Generate_speed() {
    // Minimum average speed = 200 Maximum average speed = 323
    int Speed = 200 + (utils::rnd_number(1.0, 100.0) * 123) / 100;
    speed = Speed;
    temperature_moteur += (Speed / temperature_moteur);
}


void Cars::adjustment(int Choice) {
    // adjust the car in function of the user's choice
    switch (Choice) {
        case 1 :
            Regonfler_pneu();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 2:
            Changer_pneu();
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
            fix_antiblocage();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 7 :
            fix_sysfreinage();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        default:
            break;
    }
}


void Cars::auto_adjustment() {
    // auto-adjust the car to avoid it to crash
    penality = 0;
    int User_choice;
    if (fuel < 20) {
        User_choice = 3;
    } else if (usure_pneu < 20) {
        User_choice = 2;
    } else if (pression_pneu < 40) {
        User_choice = 1;
    } else {
        User_choice = 0;
    }

    adjustment(User_choice);
    refroidir_moteur();
}

void Cars::manual_adjustment() {
    // Ask user to choose an adjustment
    penality = 0;
    int User_choice;
    std::cin >> User_choice;
    adjustment(User_choice);
    refroidir_moteur();
}


void Cars::Regonfler_pneu() {
    pression_pneu += 30; // add +30% of pressure
    // tire pressure can't be at 100% if the wear of the tire isn't
    if (pression_pneu > (100.0 - (100 - usure_pneu) / 2)) {
        pression_pneu = 100.0 - (100 - usure_pneu) / 2;
    }
    std::cout << "Tire pressure : " << pression_pneu << "%";
}

void Cars::Changer_pneu() {
    // set tire wear to 100% like new one
    pression_pneu = 100;
    usure_pneu = 100;
    std::cout << "New tires installed ! ";
}

void Cars::refill_fuel() {
    // set fuel to max capacity
    fuel = 95;
    std::cout << "Full fuel tank ! ";
}

void Cars::change_oil() {
    oil = 100;
    std::cout << "Taux d'huile moteur retablit ! " << std::endl;
}

void Cars::fix_DRS() {
    // can't be fix to 100%
    if (usure_DRS < 80) {
        usure_DRS = 80;
        std::cout << "DRS fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on DRS ! " << std::endl;
    }
}

void Cars::fix_sysfreinage() {
    // can't be fix to 100%
    if (usure_systeme_freinage < 80) {
        usure_systeme_freinage = 80;
        std::cout << "sysfreinage fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on sysfreinage ! " << std::endl;
    }
}

void Cars::fix_antiblocage() {
    // can't be fix to 100%
    if (usure_antiblocage < 80) {
        usure_antiblocage = 80;
        std::cout << "antiblocage fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on antiblocage ! " << std::endl;
    }
}

void Cars::refroidir_moteur() {
    // cooled the engine by 4 degrees per second at standstill.
    temperature_moteur -= 4 * penality;
    // can't be inferior to 80 degres
    if (temperature_moteur < 80) {
        temperature_moteur = 80;
    }

}

