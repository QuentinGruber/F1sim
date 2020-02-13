//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Race.h"
#include "Cars.h"
#include "Circuit.h"
#include "Cars_bot.h"
#include <chrono>
#include <thread>
#include <algorithm>

char *bot_namelist[21] = {"Bertand", "Bernie", "Olive", "Paul", "Jacob", "Maxon", "Laurent",
                          "Aurelie", "Quentin", "Alban", "Judiael", "Alick", "Alcapone",
                          "Anne marie", "Cyril", "Emma", "Mohamed", "Louise", "Clara", "Lancelot",
                          "Pierre"};
Circuit Circuitos;
Cars Car1, Car2;
const int NB_BOT = 20;
Cars_bot *bot = new Cars_bot[NB_BOT];

void Race::start_race() {
    // Init some stuff
    Car1.name = "Tutur";
    Car2.name = "Nulardos";

    for(int i = 0;i < NB_BOT;i++){ // give to all bot a name
        if (i < size(bot_namelist)){
            bot[i].name = bot_namelist[i];
        }
        else{
            bot[i].name = "NoName";
        }
    }

    // debug

    for(int i = 0;i<NB_BOT;i++){
        std::cout<<"Bot name :"<<bot[i].name<<std::endl;
    }

    /*
     * Disable this for easier testing TODO: make the user choose some parameters or use default one
    // Wait for User response to start simulation
    char User_response;
    do {
        std::cout << "Start simulation? [y]" << std::endl;
        std::cin >> User_response;
        if (User_response == 'y' || User_response == 'Y' )
            break;
    }while (true);
    */

    // Start the race
    for (int i = 1; i <= Circuitos.nb_tours; i++) { // every loop
        std::cout << "<--- TOUR " << i << " --->" << std::endl; // display loop number

        if (i != 1) { // si le premier tour est passé
            for (int j = 0; j < NB_BOT; j++) {
                bot[j].Random_pit_stop();
            }
        }
        // User choose to adjust some stuff on car 1
        Car1.Display_info();
        if (Car1.automated)
            Car1.auto_adjustment();
        else
            Car1.manual_adjustment();

        // User choose to adjust some stuff on car 2
        Car2.Display_info();
        if (Car2.automated)
            Car2.auto_adjustment();
        else
            Car2.manual_adjustment();


        // The car make the loop and some of his components are used
        Car1.Generate_speed();
        Car2.Generate_speed();
        for (int j = 0; j < NB_BOT; j++) {
            bot[j].Generate_speed();
            bot[j].global_time += Loop_time(Circuitos.distance, bot[j].speed,bot[j].penality);
        }
        Car1.last_loop_time = Loop_time(Circuitos.distance, Car1.speed, Car1.penality);
        Car2.last_loop_time = Loop_time(Circuitos.distance, Car2.speed , Car2.penality);
        Car1.global_time += Car1.last_loop_time;
        Car2.global_time += Car2.last_loop_time;
        Make_leaderboard();
        Turn_anim();
        Display_Times();
        Car1.Wear(Circuitos.distance, (Circuitos.virage_droit + Circuitos.virage_gauche));
        Car2.Wear(Circuitos.distance, (Circuitos.virage_droit + Circuitos.virage_gauche));
        if (Car1.HasCrashed || Car2.HasCrashed)
            break;  // If one of the component get at a critical state the simulation end.
    }
    Display_learderboard();
    system("pause");
}

float Race::Loop_time(float Circuit_length, float Car_speed, float penality) {
    // speed in mps
    float Car_speed_mps = (Car_speed / 3600) * 1000;
    return (Circuit_length / Car_speed_mps) + penality;
}

void Race::Display_Times() {
    std::cout << Car1.name << " finish this turn in " << Car1.last_loop_time << "Seconds"
              << " and his current position in the race is " << Car1.position << std::endl;
    std::cout << Car2.name << " finish this turn in " << Car2.last_loop_time << "Seconds"
              << " and his current position in the race is " << Car2.position << std::endl;
}

void Race::Turn_anim() { // TODO: fix anim not smooth anymore
    int anim_speed = 20;
    float Temp_max;
    if (Car1.last_loop_time >= Car2.last_loop_time)
        Temp_max = Car1.last_loop_time;
    else
        Temp_max = Car2.last_loop_time;

    for (int sec_g = 0; sec_g < Temp_max; sec_g++) {
        std::cout << Car1.name << ":";
        if(Car1.penality != 0 )
            std::cout << Car_progress(sec_g - Car1.penality, Car1.last_loop_time);
        else
            std::cout << Car_progress(sec_g, Car1.last_loop_time);
        std::cout << Car2.name << ":";
        if(Car2.penality != 0 )
            std::cout << Car_progress(sec_g - Car2.penality, Car2.last_loop_time);
        else
            std::cout << Car_progress(sec_g, Car2.last_loop_time);
        if (sec_g == int(Temp_max)) {
            // Clean screen // TODO: retirer le vomit
            std::cout << "\r";
            std::cout << "                                                                                         "
                      << std::endl;
            // std::cout <<"Temps depuis le debut du tour : "<<sec_g<<std::endl; // Active le fait de garder l'anim à l'écran quand terminé
        } else std::cout << "Temps depuis le debut du tour : " << sec_g << " Speed :X" << anim_speed << '\r';

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / anim_speed));
    }

}

char *Race::Car_progress(float elapsed_time, float Total_time) {

    std::string Animtoshow;
    Animtoshow.append("[");
    for (int p = 1; p <= 10; p++) {
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
    strcpy(Animtoshow_Converted, Animtoshow.c_str());
    char *Animtoshow_Render = Animtoshow_Converted;
    return Animtoshow_Render;
}

void Race::Make_leaderboard() {
    float Leaderboard[NB_BOT + 2]; // init leaderboard tab
    Leaderboard[0] = Car1.global_time;
    Leaderboard[1] = Car2.global_time;
    for (int t = 0; t < NB_BOT; t++) {
        Leaderboard[2 + t] = bot[t].global_time;
    }
    std::sort(&Leaderboard[0], &Leaderboard[0] + (NB_BOT + 2)); // trie par ordre croissant
    for (int i = 0; i < NB_BOT + 2; i++) { // find player position
        if (Leaderboard[i] == Car1.global_time) {
            Car1.position = i;
        }
        if (Leaderboard[i] == Car2.global_time) {
            Car2.position = i;
        }
    }
}

void Race::Display_learderboard() {
    // init stuff
    float Leaderboard[NB_BOT + 2]; // init leaderboard tab
    Leaderboard[0] = Car1.global_time; // TODO: better Leaderboard systeme
    Leaderboard[1] = Car2.global_time;
    for (int t = 0; t < NB_BOT; t++) {
        Leaderboard[2 + t] = bot[t].global_time;
    }
    std::string Current_position_name;
    std::sort(&Leaderboard[0], &Leaderboard[0] + (NB_BOT + 2)); // trie par ordre croissant
    for (int i = 0; i < NB_BOT + 2; i++) { // find player position
        if (Leaderboard[i] == Car1.global_time) {
            Current_position_name = Car1.name;
        }
        if (Leaderboard[i] == Car2.global_time) {
            Current_position_name = Car2.name;
        }
        for (int j = 0; j < NB_BOT; j++) {
            if (Leaderboard[i] == bot[j].global_time) {
                Current_position_name += "(Bot) ";
                Current_position_name += bot[j].name;
            }
        }
        std::cout << "Position " << i << " : " << Current_position_name << std::endl;
        Current_position_name = ""; // reset string
    }
}
