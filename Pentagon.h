//Федоров Антон Сергеевич М8О-207Б-19
//вариант 30: фигура - 5-ти угольник, контейнер - динамический массив, аллокатор - список

#ifndef OOP_EXERCISE_03_PENTAGON_H
#define OOP_EXERCISE_03_PENTAGON_H

#include "Figure.h"

class Pentagon: public Figure{
public:
    Pentagon() = default;
    Pentagon(Cord center, double radius);
    double Area() override;
    void print() override;
};
#endif
