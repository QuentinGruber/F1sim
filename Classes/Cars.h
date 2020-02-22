//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_CARS_H
#define PROJ_C_CARS_H
class Cars {
public:
    bool automated = false;
    int penality = 0;
    char *name = "Noname";
    int speed = 0;
    int position = 0;
    float last_loop_time = 0;
    float global_time = 0;
    float chance_crash = 0.1;
    bool HasCrashed = false;
    // télémétrie
    float tyre_pressure = 100.0;
    float tyre_wear = 100.0;
    float motor_temperature = 60.0; // min 60 max 120
    float oil = 100.0;
    float fuel = 95.0; // ferrari f1 stat
    float wear_braking_system = 100.0;
    float wear_column_direction = 100.0;
    float wear_DRS = 100.0;
    float wear_anti_locking = 100.0;
    float wear_carriage = 100.0;

    // Function

    void auto_adjustment();

    void manual_adjustment();

    void adjustment(int choice);

    void Generate_speed();

    void Display_info();

    void Wear(float Distance_lap, float turns);

    void Tyre_inflation();

    void Change_tyre();

    void lower_engine_temperature();

    void refill_fuel();
    void change_oil();
    void fix_DRS();
    void fix_sysfreinage();
    void fix_antiblocage();

};
#endif //PROJ_C_CARS_H
