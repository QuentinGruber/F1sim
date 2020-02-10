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
    bool HasCrashed = false;
    // télémétrie
    float pression_pneu = 100.0;
    float usure_pneu = 100.0;
    float temperature_moteur = 100.0;
    float taux_huile = 100.0;
    float taux_essence = 100.0;
    float usure_systeme_freinage = 100.0;
    float usure_colonne_direction = 100.0;
    float usure_DRS = 100.0;
    float usure_antiblocage = 100.0;
    float usure_carroserie = 100.0;
    // Function
    void Generate_speed();
    void Display_info();
    void Wear(float Distance_Tour,float nb_virages);
    void Regonfler_pneu();
    void Changer_pneu();
    void manual_adjustment();
    void refill_fuel();
    void change_oil();
    void fix_DRS();
    void fix_sysfreinage();
    void fix_antiblocage();

};
#endif //PROJ_C_CARS_H
