//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Cars.h"

void Cars::Display_info() {
    std::cout<<"["<<name<<"'s info] "<<"pression_pneu : "<<pression_pneu<<"%"<<" usure_pneu : "<<usure_pneu<<"%"<<std::endl;
}

void Cars::Wear(float Distance_Tour,float nb_virages) {
    int Crash_log = 0;
    pression_pneu -= (0.003f * Distance_Tour + 0.003f * nb_virages); // 0.03% de perte de pression par mètre et le double pendant les virages
    usure_pneu -= (0.001f * Distance_Tour + 0.003f * nb_virages);
    if(pression_pneu<=0.0) Crash_log = 1;
    if(usure_pneu<=0.0) Crash_log = 2;

    switch (Crash_log) {
        case 1 : std::cout<<"[CRASH "<<name<<"] Un pneu etait en depression ;)"<<std::endl;
            HasCrashed = true;
            break;
        case 2 : std::cout<<"[CRASH "<<name<<"] Un pneu a eclate"<<std::endl;
            HasCrashed = true;
            break;
        default:
            break;
    }

}

void Cars::manual_adjustment() {
    int User_choice;
    std::cin>> User_choice;
    switch (User_choice) {
        case 1 :
            Regonfler_pneu();
            break;
        case 2:
            Changer_pneu();
            break;
        default:
            break;
    }

}

void Cars::Regonfler_pneu() {
    pression_pneu += 30;
    if (pression_pneu>100.0){
        pression_pneu = 100;
    }
    std::cout<<"Pression_pneu : "<<pression_pneu<<"%"<<std::endl;
}

void Cars::Changer_pneu() {
    pression_pneu = 100;
    usure_pneu = 100;
    std::cout<<"Pneu neuf installé ! "<<std::endl;
}

