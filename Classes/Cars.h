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
    float pression_pneu = 100.0;
    float usure_pneu = 100.0;
    float temperature_moteur = 100.0;
    float taux_huile = 100.0;
    float essence = 95.0; // ferrari f1 stat
    float usure_systeme_freinage = 100.0;
    float usure_colonne_direction = 100.0;
    float usure_DRS = 100.0;
    float usure_antiblocage = 100.0;
    float usure_carroserie = 100.0;

    // Function
    void auto_adjustment();

    void manual_adjustment();

    void adjustment(int choice);

    void crash_test();

    void Generate_speed();

    void Display_info();

    void Wear(float Distance_Tour, float nb_virages);

    void Regonfler_pneu();

    void Changer_pneu();

    void refill_fuel();
    void change_oil();
    void fix_DRS();
    void fix_sysfreinage();
    void fix_antiblocage();

};
#endif //PROJ_C_CARS_H
