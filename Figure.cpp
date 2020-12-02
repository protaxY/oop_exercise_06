//Федоров Антон Сергеевич М8О-207Б-19
//вариант 30: фигура - 5-ти угольник, контейнер - динамический массив, аллокатор - список

#include "Figure.h"

Figure::Figure(Cord center, double radius){
    Center = center;
    Radius = radius;
}

Cord Figure::GetCenter(){
    return Center;
}