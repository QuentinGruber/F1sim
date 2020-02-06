//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Course.h"
#include "Cars.h"
#include "Circuit.h"

void Course::start_course() {
    Circuit Circuitos;
    Cars tutur;
    for (int i = 0 ;i<=Circuitos.nb_tours;i++){ // every loop
        std::cout<<"TOUR "<<i<<std::endl; // display loop number
        tutur.Display_info();
        tutur.Usure();
    }

}
