//
// Created by Quentin on 06/02/2020.
//
#include <iostream>
#include "Cars.h"
#include <random>

void Cars::Display_info() {
    std::cout << "\n[" << name << "'s info] " << std::endl;
    std::cout << "\nVitesse lors du dernier tour : " << speed << "km/h" << std::endl;
    std::cout << "pression_pneu : " << pression_pneu << "%" << " {Fix this with 1}" << std::endl;
    std::cout << "usure des pneu : " << usure_pneu << "%" << " {Fix this with 2}" << std::endl;
    std::cout << "Reservoir d'essence : " << essence << "L" << " {Fix this with 3}" << std::endl;
    std::cout << "Taux d'huile : " << taux_huile << "%" << " {Fix this with 4}" << std::endl;
    std::cout << "Temperature du moteur : " << temperature_moteur << " degres" " {Fix this with 5}" << std::endl;
    std::cout << "Usure du DRS : " << usure_DRS << "%" << " {Fix this with 6}" << std::endl;
    std::cout << "Usure du systeme d'antiblocage : " << usure_antiblocage << "%" << " {Fix this with 7}" << std::endl;
    std::cout << "Usure du systeme de freinage : " << usure_systeme_freinage << "%" << " {Fix this with 8}"
              << std::endl;
    std::cout << "Usure de la colonne de direction : " << usure_colonne_direction << "%" << std::endl;
    std::cout << "Usure de la carroserie : " << usure_carroserie << "%" << std::endl;
    std::cout << "\nChoose if you want to fix something or not ( press 0 ): ";
}

void Cars::Wear(float Distance_Tour,float nb_virages) {
    int Crash_log = 0;
    pression_pneu -= (0.00003f * Distance_Tour + 0.0003f * nb_virages) * (speed /
                                                                          10); // 0.01% de perte de pression par mètre à + de 100km/h et le double pendant les virages
    usure_pneu -= (0.00001f * Distance_Tour + 0.00001f * nb_virages) * (speed / 10);
    essence -= (75 * (Distance_Tour / 1000)) / 100; // 75 litre au 100 pour l'essences (en moyenne)

    if (pression_pneu <= 0.0) Crash_log = 1;
    if (usure_pneu <= 0.0) Crash_log = 2;

    switch (Crash_log) {
        case 1 :
            std::cout << "[CRASH " << name << "] Un pneu etait en depression ;)" << std::endl;
            HasCrashed = true;
            break;
        case 2 :
            std::cout << "[CRASH " << name << "] Un pneu a eclate" << std::endl;
            HasCrashed = true;
            break;
        default:
            break;
    }

}

void Cars::Generate_speed() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    int rnd_number = dist(mt);
    int Speed = 200 + (rnd_number * 123) / 100; // Vitesse minimum de 200 max de 323
    speed = Speed;

}

void Cars::manual_adjustment() {
    penality = 0;
    int User_choice;
    std::cin >> User_choice;
    switch (User_choice) {
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
            // les pompes à essence ne peuvent pas dépasser 12,1 litres par secondes
            penality = ((95 - essence) / 12.1) + 5.0; // minimum 5 secondes de penalité
            std::cout << " Penality : " << penality << "sec" << std::endl;
            refill_fuel();
            break;
        case 4 :
            change_oil();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 5 :
            // temperature moteur
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 6 :
            fix_DRS();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 7 :
            fix_antiblocage();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        case 8 :
            fix_sysfreinage();
            penality = 10;
            std::cout << " Penality : " << penality << "sec" << std::endl;
            break;
        default:
            break;
    }

}

void Cars::Regonfler_pneu() {
    pression_pneu += 30;
    if (pression_pneu>(100.0 - (100 -usure_pneu)/2)){
        pression_pneu = 100.0 - (100 -usure_pneu)/2;
    }
    std::cout << "Pression_pneu : " << pression_pneu << "%";
}

void Cars::Changer_pneu() {
    pression_pneu = 100;
    usure_pneu = 100;
    std::cout << "Pneu neuf installé ! ";
}

void Cars::refill_fuel() {
    essence = 95;
    std::cout << "Reservoir d'essence plein ! ";
}

void Cars::change_oil() {
    taux_huile = 100;
    std::cout << "Taux d'huile moteur retablit ! " << std::endl;
}

void Cars::fix_DRS() {
    if (usure_DRS < 80) {
        usure_DRS = 80;
        std::cout << "DRS fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on DRS ! " << std::endl;
    }
}

void Cars::fix_sysfreinage() {
    if (usure_systeme_freinage < 80) {
        usure_systeme_freinage = 80;
        std::cout << "sysfreinage fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on sysfreinage ! " << std::endl;
    }
}

void Cars::fix_antiblocage() {
    if (usure_antiblocage < 80) {
        usure_antiblocage = 80;
        std::cout << "antiblocage fixed at the best we can ! " << std::endl;
    } else {
        std::cout << "Nothing to fix on antiblocage ! " << std::endl;
    }
}

