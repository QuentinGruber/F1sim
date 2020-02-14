//
// Created by Quentin on 10/02/2020.
//

#include "Cars_bot.h"
#include "utils.h"


void Cars_bot::Generate_speed() {
    int Speed = 200 + (utils::rnd_number(0.0, 100.0) * 123) / 100; // Vitesse minimum de 200 max de 323
    speed = Speed;

}

void Cars_bot::Random_pit_stop() {
    penality = 0; // reset it at the beginning
    if (utils::rnd_number(0.0, 100.0) < 10) { // 10 % chance que le bot s'arrête
        penality = utils::rnd_number(0.0, 100.0); // add a random penality between 0 and 20
    }
}

void Cars_bot::Random_crash() {
    if(utils::rnd_number(0.0,1000.0) < 1){
        HasCrashed = true;
        global_time = 40404;
    }
}
