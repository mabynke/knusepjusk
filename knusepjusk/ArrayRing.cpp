#include "ArrayRing.h"

double abs(int n) {
  if (n >= 0) {
    return n;
  } else {
    return -n;
  }
}

ArrayRing::ArrayRing(int length, int initValue) : length(length) {
  position = 0;
  array = new double[length];
  for (int i = 0; i < length; ++i) {
    array[i] = initValue;
  }
};

double ArrayRing::getAverage() {
  double sum = 0;
  for (int i = 0; i < length; ++i) {
    sum += array[i];
  }
  return sum / length;
}


void ArrayRing::add(double digit) {
  position = (position + 1) % length;
  array[position] = digit;
}

bool ArrayRing::isLastNDigit(int n, double digit, double error) {
  int posCopy = this->position;
  for (int i = 0; i < n; ++i) {
    const double tall = array[(posCopy - i) % length];
    if (abs(tall - digit) > error) {
      return false;
    }
  }
  return true;
}

