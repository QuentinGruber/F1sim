//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_CARS_H
#define PROJ_C_CARS_H
class Cars {
public:
    /// If the car adjustment are automated
    bool automated = false;
    /// Time penality is the time the car is at pit stop
    float penality = 0.0;
    /// Car's name
    char *name = "Noname";
    /// Average speed last lap
    int speed = 0;
    /// Current position in the race
    int position = 0;
    /// Last loop time
    float last_loop_time = 0;
    /// Global race time of the car \n Can be set at 40404 aka "Crash time" to identify that a car has crash in the leaderboard
    float global_time = 0;
    /// If has crashed (Due to collid or not)
    bool HasCrashed = false;
    // télémétrie
    /// In %, critical state = 0.0
    /// \n Tyre pressure can't be at 100% if the wear of the tire isn't
    float tyre_pressure = 100.0;
    /// In %, critical state = 0.0
    float tyre_wear = 100.0;
    /// min 60 degres critical state = 130 degres
    float motor_temperature = 60.0;
    /// In %, has no critical state.
    /// Degrades faster if the engine is hot.
    float oil = 100.0;
    /// In liter, critical state = 0.0
    /// \n Ferrari f1 stat : 75 litres of oil per 100 km(on average)
    float fuel = 95.0;
    /// In % critical state = 0.0
    /// \n Can't be fix to 100%
    float wear_braking_system = 100.0;
    /// In % critical state = 0.0
    /// \n Can't be fix
    float wear_column_direction = 100.0;
    /// In % critical state = 0.0
    /// \n Can't be fix to 100%
    float wear_DRS = 100.0;
    /// In % critical state = 0.0
    /// \n Can't be fix to 100%
    float wear_anti_locking = 100.0;
    /// In % critical state = 0.0
    /// \n Can't be fix
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
