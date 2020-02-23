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
    /// 5.371km converted in meter
    float distance = 5371.0;
    /// Number of right turn in the circuit
    float right_turn = 3.0;
    /// Number of left turn in the circuit
    float left_turn = 4.0;

};


#endif //PROJ_C_CIRCUIT_H
