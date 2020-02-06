//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_CARS_H
#define PROJ_C_CARS_H
class Cars {
public:
    float pression_pneu = 10.0;
    float usure_pneu = 10.0;
    float temperature_moteur = 10.0;
    void Display_info();
    void Usure();
    void Regonfler_pneu();
    void Changer_pneu();
};
#endif //PROJ_C_CARS_H
