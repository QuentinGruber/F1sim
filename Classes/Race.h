//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_RACE_H
#define PROJ_C_RACE_H
using namespace std;

class Race {
public:
    static void start_race();

    static void Calculate_cars_loop_position();

    static void Display_learderboard();

private:

    static void random_collid();

    static float Loop_time(float Circuit_length, float Car_speed, float penality);

    static void Display_Times();

    static void Lap_anim();

    static char *Car_progress(float elapsed_time, float Total_time);
};

#endif //PROJ_C_RACE_H
