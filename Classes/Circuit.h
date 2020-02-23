//
// Created by Quentin on 06/02/2020.
//

#ifndef PROJ_C_CIRCUIT_H
#define PROJ_C_CIRCUIT_H


class Circuit {
public:
    /// Number of laps in the race
    int lap = 50;
    /// Circuit length in meter
    float Circuit_length = 5371.0;
    /// Number of right bends in the circuit
    float right_bends = 4.0;
    /// Number of left bends in the circuit
    float left_bends = 5.0;

};


#endif //PROJ_C_CIRCUIT_H
