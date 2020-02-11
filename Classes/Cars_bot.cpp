//
// Created by Quentin on 10/02/2020.
//

#include "Cars_bot.h"
#include <iostream>
#include <random>


void Cars_bot::Generate_speed() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    int rnd_number = dist(mt);
    int Speed = 200 + (rnd_number * 123) / 100; // Vitesse minimum de 200 max de 323
    speed = Speed;

}

void Cars_bot::Random_pit_stop() {
    penality = 0; // reset it at the beginning
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    std::uniform_real_distribution<double> dist2(1.0, 20.0);
    int rnd_number = dist(mt);
    int rnd_number2 = dist2(mt);
    if (rnd_number < 10) { // 10 % chance que le bot s'arrête
        penality = rnd_number2; // add a random penality between 1 and 20
    }
}
