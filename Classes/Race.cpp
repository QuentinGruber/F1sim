//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include <cstring>
#include "utils.h"
#include "Race.h"
#include "Cars.h"
#include "Circuit.h"
#include "Cars_bot.h"
#include <chrono>
#include <thread>
#include <algorithm>

// Name list for bots
char *bot_namelist[21] = {"Bertand", "Bernie", "Olive", "Paul", "Jacob", "Maxon", "Laurent",
                          "Aurelie", "Quentin", "Alban", "Judicael", "Alick", "Alcapone",
                          "Anne marie", "Cyril", "Emma", "Mohamed", "Louise", "Clara", "Lancelot",
                          "Pierre"};
/// location "Le Castellet",France
Circuit Paul_Ricard; 
Cars Car1, Car2; // init our 2 cars
/// define the number of bots during the race
const int NB_BOT = 20;
Cars_bot *bot = new Cars_bot[NB_BOT]; // init the bots

void Race::start_race() {
    // Give cars a name
    Car1.name = "Schumacher";
    Car2.name = "Hamilton";

    for (int i = 0; i < NB_BOT; i++) { // give to all bot a name
        if (i < size(bot_namelist)) {
            bot[i].name = bot_namelist[i];
        } else { // if we doesn't have enough name in our namelist , the remaining bots were be called "NoName"
            bot[i].name = "NoName";
        }
    }

    // Wait for User response to start simulation
    char User_response;
    do {
        std::cout << "To start the simulation in 'Manual' press [m] \n"
                     "To start the simulation in 'Automated?' press [a] " << std::endl;
        std::cin >> User_response;
        if (User_response == 'm' || User_response == 'M')
            break;
        else if (User_response == 'a' || User_response == 'A') {
            Car1.automated = true;
            Car2.automated = true;
            break;
        }
    }while (true);

    /// Start the race
    for (int i = 1; i <= Paul_Ricard.lap; i++) { // every loop
        std::cout << "<--- TOUR " << i << " --->" << std::endl; // display loop number

        if (i != 1) {// if first loop is passed
            for (int j = 0; j < NB_BOT; j++) {
                bot[j].Random_pit_stop(); // bot may have a random pit stop
                bot[j].Random_crash(); // and may have a random crash
            }
        }
        // User choose to adjust some stuff on car 1 if it didn't crash
        if (!Car1.HasCrashed) {
            Car1.Display_info();
            if (Car1.automated)
                Car1.auto_adjustment();
            else
                Car1.manual_adjustment();
        }
        // User choose to adjust some stuff on car 2 if it didn't crash
        if (!Car2.HasCrashed) {
            Car2.Display_info();
            if (Car2.automated)
                Car2.auto_adjustment();
            else
                Car2.manual_adjustment();
        }

        // Generate cars's average speed during the race
        // If they didn't crash

        if (!Car1.HasCrashed) {
            Car1.Generate_speed();
        }
        if (!Car2.HasCrashed) {
            Car2.Generate_speed();
        }
        for (int j = 0; j < NB_BOT; j++) {
            if (!bot[j].HasCrashed) {
                bot[j].Generate_speed();
                bot[j].global_time += Loop_time(Paul_Ricard.Circuit_length, bot[j].speed, bot[j].penality);
            }
        }

        random_collid();

        // If they didn't crash it calculate the loop time of the cars
        // and add it to there global time
        if (!Car1.HasCrashed) {
            Car1.last_loop_time = Loop_time(Paul_Ricard.Circuit_length, Car1.speed, Car1.penality);
            Car1.global_time += Car1.last_loop_time;
        }
        if (!Car2.HasCrashed) {
            Car2.last_loop_time = Loop_time(Paul_Ricard.Circuit_length, Car2.speed, Car2.penality);
            Car2.global_time += Car2.last_loop_time;

        }
        // Display an animation of loop progression and when it finish display times
        Calculate_cars_loop_position();
        Lap_anim();
        Display_Times();

        // Apply degration to the player's cars
        if (!Car1.HasCrashed)
            Car1.Wear(Paul_Ricard.Circuit_length, (Paul_Ricard.right_bends + Paul_Ricard.left_bends));
        if (!Car2.HasCrashed)
            Car2.Wear(Paul_Ricard.Circuit_length, (Paul_Ricard.right_bends + Paul_Ricard.left_bends));
    }
    // the race end so we display an leaderboard
    Display_learderboard();
    system("pause"); // and hold the windows so we can see which position we get
}

float Race::Loop_time(float Circuit_length, float Car_speed, float penality) {
    /// calculates the time it took a car to complete the lap.
    // speed in mps
    float Car_speed_mps = (Car_speed / 3600) * 1000;
    return (Circuit_length / Car_speed_mps) + penality; /// loop time equal travel time + time penality
}

void Race::Display_Times() {
    /// Display the time of the player's cars and their position in the race
    if(!Car1.HasCrashed) {
        std::cout << Car1.name << " finish this lap in " << Car1.last_loop_time << "Seconds"
                  << " and his current position in the race is " << Car1.position + 1 << std::endl;
    }
    if(!Car2.HasCrashed) {
        std::cout << Car2.name << " finish this lap in " << Car2.last_loop_time << "Seconds"
                  << " and his current position in the race is " << Car2.position + 1 << std::endl;
    }
}

void Race::Lap_anim() {/// Display an animation of the progress of the player's cars in the lap
    int anim_speed = 20;
    float Temp_max;
    if (Car1.last_loop_time + Car1.penality >= Car2.last_loop_time + Car2.penality)
        Temp_max = Car1.last_loop_time + Car1.penality;
    else
        Temp_max = Car2.last_loop_time + Car2.penality;

    for (int sec_g = 0; sec_g < Temp_max; sec_g++) {
        std::cout << Car1.name << ":";
        if (!Car1.HasCrashed) {
            if (Car1.penality != 0)
                std::cout << Car_progress(sec_g - Car1.penality, Car1.last_loop_time);
            else
                std::cout << Car_progress(sec_g, Car1.last_loop_time);
        } else {
            std::cout << "[CRASHED...]";
        }
        std::cout << Car2.name << ":";
        if (!Car2.HasCrashed) {
            if (Car2.penality != 0)
                std::cout << Car_progress(sec_g - Car2.penality, Car2.last_loop_time);
            else
                std::cout << Car_progress(sec_g, Car2.last_loop_time);
        } else {
            std::cout << "[CRASHED...]";
        }
        if (sec_g == int(Temp_max)) {
            // Clean screen
            std::cout << "\r";
            std::cout << "                                                                                         "
                         "                                                                                         "
                      << std::endl;
        } else std::cout << "Time since the beginning of the lap  : " << sec_g << " Speed :X" << anim_speed << '\r';

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / anim_speed));
    }

}

char *Race::Car_progress(float elapsed_time, float Total_time) {
    /// Our anim is a progress bar that has 10 progress point
    std::string Animtoshow;
    Animtoshow.append("[");
    for (int p = 1; p <= 10; p++) {
        /// when a car has done 1/10 of the lap it add an "#"
        /// \n exemple : [##_______] when the car has done more than 2/10 of the lap ( "_" are space )
        if (p == 10 && (p * 0.99) < (elapsed_time / Total_time) * 10) {
            Animtoshow.append("#");
        } else if (p < (elapsed_time / Total_time) * 10) {
            Animtoshow.append("#");
        } else {
            Animtoshow.append(" ");
        }
    }
    Animtoshow.append("]");
    char *Animtoshow_Converted = new char[Animtoshow.length() + 1];
    std::strcpy(Animtoshow_Converted, Animtoshow.c_str());
    char *Animtoshow_Render = Animtoshow_Converted;
    return Animtoshow_Render;
}

void Race::Calculate_cars_loop_position() { /// Calculate the position of all the cars in the race
    float Leaderboard[NB_BOT + 2]; // init leaderboard tab
    // Get cars global time in the board
    Leaderboard[0] = Car1.global_time;
    Leaderboard[1] = Car2.global_time;
    for (int t = 0; t < NB_BOT; t++) {
        Leaderboard[2 + t] = bot[t].global_time;
    }
    // sort the board in ascending order
    std::sort(&Leaderboard[0], &Leaderboard[0] + (NB_BOT + 2));
    for (int i = 0; i < NB_BOT + 2; i++) { // find player position
        if (Leaderboard[i] == Car1.global_time) {
            Car1.position = i; // update player position
        }
        if (Leaderboard[i] == Car2.global_time) {
            Car2.position = i; // update player position
        }
    }
}

void Race::Display_learderboard() { /// Display a ranking of all the cars in the race
    std::cout<<"--[RACE LEADERBOARD]--"<<std::endl;
    float Leaderboard[NB_BOT + 2]; // init leaderboard tab
    // Get cars global time in the board
    Leaderboard[0] = Car1.global_time;
    Leaderboard[1] = Car2.global_time;
    for (int t = 0; t < NB_BOT; t++) {
        Leaderboard[2 + t] = bot[t].global_time;
    }
    std::string Current_position_name;
    // sort the board in ascending order
    std::sort(&Leaderboard[0], &Leaderboard[0] + (NB_BOT + 2));
    for (int i = 0; i < NB_BOT + 2; i++) { // find player position
        bool position_found = false;
        if (Leaderboard[i] == Car1.global_time) {
            Current_position_name += Car1.name;
            position_found = true;
        }
        if (Leaderboard[i] == Car2.global_time) {
            if (!position_found)
                Current_position_name += Car2.name;
            else {
                Current_position_name += ",";
                Current_position_name += Car2.name;
            }
            position_found = true;
        }
        for (int j = 0; j < NB_BOT; j++) { // find bots position
            if (Leaderboard[i] == bot[j].global_time) {
                if (position_found == 0) {
                    Current_position_name += "(Bot) ";
                    Current_position_name += bot[j].name;
                    position_found = true;
                } else {
                    Current_position_name += ",(Bot) ";
                    Current_position_name += bot[j].name;
                    position_found = true;
                }
            }
        }
        if (Leaderboard[i] != 40404) // if time is not equal to "crash time"
        {
            // Display cars position
            std::cout << "Position " << i + 1 << " : " << Current_position_name << " time : " << Leaderboard[i] / 60
                      << " minute" << std::endl;
        } else {
            // Display cars that crashed during the race
            std::cout << Current_position_name << " crashed during the race..." << std::endl;
            break;
        }
        Current_position_name = ""; // reset string
    }
}

void Race::random_collid() { /// Generate random collision between cars
    if (utils::rnd_number(0.0, 50) < 1) { /// 1 in 50 chance that there will be a collision this lap
        int which_player = utils::rnd_number(0.0, 2.0);
        int which_bot = utils::rnd_number(1.0, NB_BOT);
        for (int i = 0; i <= 4; i++) {
            /// If the impact is too violent, colliding vehicles may crash.
            float Collision_power_multiplicator = utils::rnd_number(1.0, 5.0);
            switch (i) {
                case 0:
                    if (which_player == 1)
                        Car1.wear_DRS -= 15 * Collision_power_multiplicator;
                    else
                        Car2.wear_DRS -= 15 * Collision_power_multiplicator;
                    bot[which_bot].damage += Collision_power_multiplicator;
                    break;
                case 1:
                    if (which_player == 1)
                        Car1.wear_anti_locking -= 15 * Collision_power_multiplicator;
                    else
                        Car2.wear_anti_locking -= 15 * Collision_power_multiplicator;
                    bot[which_bot].damage += Collision_power_multiplicator;
                    break;
                case 2:
                    if (which_player == 1)
                        Car1.wear_braking_system -= 15 * Collision_power_multiplicator;
                    else
                        Car2.wear_braking_system -= 15 * Collision_power_multiplicator;
                    bot[which_bot].damage += Collision_power_multiplicator;
                    break;
                case 3:
                    if (which_player == 1)
                        Car1.wear_column_direction -= 15 * Collision_power_multiplicator;
                    else
                        Car2.wear_column_direction -= 15 * Collision_power_multiplicator;
                    bot[which_bot].damage += Collision_power_multiplicator;
                    break;
                case 4:
                    if (which_player == 1)
                        Car1.wear_carriage -= 15 * Collision_power_multiplicator;
                    else
                        Car2.wear_carriage -= 15 * Collision_power_multiplicator;
                    bot[which_bot].damage += Collision_power_multiplicator;
                    break;
            }
        }
        if (bot[which_bot].damage > 15.0) {
            bot[which_bot].HasCrashed = true;
            bot[which_bot].global_time = 40404;

            if (which_player == 1)
                std::cout << "[Collision] " << bot[which_bot].name << " crashed during the lap by colliding " << Car1.name << std::endl;
            else
                std::cout << "[Collision] " << bot[which_bot].name << " crashed during the lap by colliding " << Car2.name << std::endl;
        }
        else{
            if (which_player == 1)
                std::cout << "[Collision] " << bot[which_bot].name << " collided with  " << Car1.name << std::endl;
            else
                std::cout << "[Collision] " << bot[which_bot].name << " collided with " << Car2.name << std::endl;
        }
        random_collid(); /// Can have multiple collision
    }

}
