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
        Car1.Wear(Circuitos.distance,(Circuitos.virage_droit + Circuitos.virage_gauche));
        Car2.Wear(Circuitos.distance,(Circuitos.virage_droit + Circuitos.virage_gauche));
        if(Car1.HasCrashed || Car2.HasCrashed) break;  // If one of the component get at a critical state the simulation end.
    }

}

void Race::Display_choices() {
    std::cout<< "Press 1 pour regonfler pneu ou 2 pour changer pneu" <<std::endl;
}
