#pragma once
#ifndef FILTERS_H
#define FILTERS_H
#include <QImage>
#include "mainwindow.h"


QImage calculate(float, int, int, int, bool);
float* calcSum(float, int,int, int, QImage, bool);
QImage usefilters (QImage, bool, int);
#endif // FILTERS_H
