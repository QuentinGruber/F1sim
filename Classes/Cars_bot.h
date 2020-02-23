//
// Created by Quentin on 10/02/2020.
//

#ifndef PROJ_C_CARS_BOT_H
#define PROJ_C_CARS_BOT_H


class Cars_bot {
public:
    /// Average speed last lap
    int speed = 0;
    /// Damage due to collision
    float damage = 0.0;
    /// Time penality is the time the car is at pit stop
    float penality = 0;
    /// Global race time of the car \n Can be set at 40404 aka "Crash time" to identify that a car has crash in the leaderboard
    float global_time = 0;
    /// Car's name
    char *name = "undefined";
    /// If has crashed (Due to collid or not)
    bool HasCrashed = false;

    void Generate_speed();
    void Random_pit_stop();
    void Random_crash();

};


#endif //PROJ_C_CARS_BOT_H
