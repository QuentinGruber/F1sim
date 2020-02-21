//
// Created by Quentin on 10/02/2020.
//

#ifndef PROJ_C_CARS_BOT_H
#define PROJ_C_CARS_BOT_H


class Cars_bot {
public:
    int speed = 0;
    float damage = 0.0;
    float penality = 0;
    float global_time = 0;
    char *name = "undefined";
    bool HasCrashed = false;

    void Generate_speed();
    void Random_pit_stop();
    void Random_crash();

};


#endif //PROJ_C_CARS_BOT_H
