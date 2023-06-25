//
// Created by Quentin on 13/02/2020.
//

#include "utils.h"
#include <random>

std::random_device rd;
std::mt19937 mt(rd()); /// use Mersenne Twister 19937 generator
int utils::rnd_number(float min, float max) {
  /// Generate a random floating number between min and max
  /// A Mersenne Twister pseudo-random generator of 32-bit numbers with a state
  /// size of 19937 bits.
  std::uniform_real_distribution<double> dist(min, max);
  int rnd_number = dist(mt);
  return rnd_number;
}
