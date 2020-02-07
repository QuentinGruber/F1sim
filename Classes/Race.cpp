//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Race.h"
#include "Cars.h"
#include "Circuit.h"

Circuit Circuitos;
Cars Car1,Car2;


void Race::start_race() {
    // Init some stuff
    Car1.name ="Tutur";
    Car2.name ="Nulardos";
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
    for (int i = 1 ;i<=Circuitos.nb_tours;i++){ // every loop
        std::cout<<"TOUR "<<i<<std::endl; // display loop number

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
    float Car_speed_mps = (Car_speed/3600)*1000;
    return Car_speed_mps;
}

void Race::Display_Times() {
    std::cout<<Car1.name<<" finish this turn in "<<Loop_time(Circuitos.distance,Car1.speed)<<"Seconds"<<std::endl;
    std::cout<<Car2.name<<" finish this turn in "<<Loop_time(Circuitos.distance,Car2.speed)<<"Seconds"<<std::endl;
}

