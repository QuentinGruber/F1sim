//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Race.h"
#include "Cars.h"
#include "Circuit.h"
#include <chrono>
#include <thread>

Circuit Circuitos;
Cars Car1, Car2;


void Race::start_race() {
    // Init some stuff
    Car1.name = "Tutur";
    Car2.name = "Nulardos";
    /*
     * Disable this for easier testing
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

        // User choose to adjust some stuff on car 1
        Car1.Display_info();
        Display_choices();
        Car1.manual_adjustment();


        // User choose to adjust some stuff on car 2
        Car2.Display_info();
        Display_choices();
        Car2.manual_adjustment();


        // The car make the loop and some of his components are used
        Car1.Generate_speed();
        Car2.Generate_speed();
        Turn_anim();
        Display_Times();
        Car1.Wear(Circuitos.distance,(Circuitos.virage_droit + Circuitos.virage_gauche));
        Car2.Wear(Circuitos.distance,(Circuitos.virage_droit + Circuitos.virage_gauche));
        if(Car1.HasCrashed || Car2.HasCrashed) break;  // If one of the component get at a critical state the simulation end.
    }

}

void Race::Display_choices() {
    std::cout<< "Press 1 pour regonfler pneu ou 2 pour changer pneu" <<std::endl;
}

float Race::Loop_time(float Circuit_length, float Car_speed) {
    // speed in mps
    float Car_speed_mps = (Car_speed / 3600) * 1000;
    return (Circuit_length / Car_speed_mps);
}

void Race::Display_Times() {
    std::cout << Car1.name << " finish this turn in " << Loop_time(Circuitos.distance, Car1.speed) << "Seconds\n"
              << std::endl;
    std::cout << Car2.name << " finish this turn in " << Loop_time(Circuitos.distance, Car2.speed) << "Seconds\n"
              << std::endl;
}

void Race::Turn_anim() {
    int anim_speed = 20;
    float Temp_max;
    if (Loop_time(Circuitos.distance, Car1.speed) >= Loop_time(Circuitos.distance, Car2.speed))
        Temp_max = Loop_time(Circuitos.distance, Car1.speed);
    else
        Temp_max = Loop_time(Circuitos.distance, Car2.speed);

    for (int sec_g = 0; sec_g < Temp_max; sec_g++) {
        std::cout << Car1.name << ":";
        if(Car1.penality != 0 )
            std::cout << Car_progress(sec_g - Car1.penality, Loop_time(Circuitos.distance, Car1.speed));
        else
            std::cout << Car_progress(sec_g, Loop_time(Circuitos.distance, Car1.speed));
        std::cout << Car2.name << ":";
        if(Car2.penality != 0 )
            std::cout << Car_progress(sec_g - Car2.penality, Loop_time(Circuitos.distance, Car2.speed));
        else
            std::cout << Car_progress(sec_g, Loop_time(Circuitos.distance, Car2.speed));
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
