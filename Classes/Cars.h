//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_CARS_H
#define PROJ_C_CARS_H
class Cars {
public:
    int penality = 0;
    char* name = "Noname";
    int speed = 0;
    float pression_pneu = 100.0;
    float usure_pneu = 100.0;
    float temperature_moteur = 10.0;
    void Generate_speed();
    void Display_info();
    void Wear(float Distance_Tour,float nb_virages);
    void Regonfler_pneu();
    void Changer_pneu();
    void manual_adjustment();
    bool HasCrashed = false;
};
#endif //PROJ_C_CARS_H
