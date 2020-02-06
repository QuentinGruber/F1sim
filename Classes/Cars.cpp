//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Cars.h"

void Cars::Display_info() {
    std::cout<<"[Car's info] "<<"pression_pneu : "<<pression_pneu<<" usure_pneu : "<<usure_pneu<<std::endl;
}

void Cars::Usure() {
    pression_pneu--;
    usure_pneu--;
}

void Cars::Regonfler_pneu() {
    pression_pneu += 30;
    if (pression_pneu>100.0){
        pression_pneu = 100;
    }
}

void Cars::Changer_pneu() {
    pression_pneu = 100;
    usure_pneu = 100;
}

