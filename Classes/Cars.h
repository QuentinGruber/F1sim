//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_CARS_H
#define PROJ_C_CARS_H
class Cars {
public:
    char* name;
    float pression_pneu = 100.0;
    float usure_pneu = 100.0;
    float temperature_moteur = 10.0;
    void Display_info();
    void Usure(float Distance_Tour,int nb_virages);
    void Regonfler_pneu();
    void Changer_pneu();
    void manual_adjustment();
    bool HasCrashed;
};
#endif //PROJ_C_CARS_H
