//
// Created by Quentin on 13/02/2020.
//

#include <random>
#include "utils.h"

int utils::rnd_number(float min, float max) {
    // Generate random number
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(min, max);
    int rnd_number = dist(mt);
    return rnd_number;
}