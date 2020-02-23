//
// Created by Quentin on 10/02/2020.
//

#include "Cars_bot.h"
#include "utils.h"


void Cars_bot::Generate_speed() { /// Randomly generate car average speed during a lap
    /// Minimum average speed = 200 km/h Maximum average speed = 323 km/h
    int Speed = 200 + (utils::rnd_number(0.0, 100.0) * 123) / 100;
    speed = Speed;

}

void Cars_bot::Random_pit_stop() { /// Randomly generate a pit stop
    /// Needed for balancing reasons
    penality = 0; // reset penality at the beginning
    if (utils::rnd_number(0.0, 100.0) < 10) { /// 10 % chance that the bot will stop
        penality = utils::rnd_number(0.0, 100.0); /// add a random penality between 0 and 20 sec
    }
}

void Cars_bot::Random_crash() { /// Randomly generate a car crash
    if (utils::rnd_number(0.0, 1000.0) < 1) { /// 1 in 1000 chance that the bot will crash
        HasCrashed = true;
        global_time = 40404; /// set global time to "Crash Time"
    }
}
