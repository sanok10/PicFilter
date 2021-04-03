#pragma once
#ifndef FILTERS_H
#define FILTERS_H
#include <QImage>
#include "mainwindow.h"


QImage calculate(QImage, int, int, int, bool);
int* calcSum(int, int,int, int, QImage, bool);
QImage usefilters (QImage, bool, int);
#endif // FILTERS_H
