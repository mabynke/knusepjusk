#ifndef ARRAY_RING_H
#define ARRAY_RING_H

class ArrayRing {
  private:
    double *array;
    int position;
    int length;
  public:
    ArrayRing(int length, int initValue);
    ArrayRing(int length) : ArrayRing(length, 0) {};
    double getAverage();
    void add(double);
    bool isLastNDigit(int n, double digit, double error);
};

#endif
