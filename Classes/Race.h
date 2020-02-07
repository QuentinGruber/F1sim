//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_RACE_H
#define PROJ_C_RACE_H

class Race {
public:static void start_race();

private:
    static void Display_choices();
    static float Loop_time(float Circuit_length,float Car_speed);
    static void Display_Times();
};

#endif //PROJ_C_RACE_H
