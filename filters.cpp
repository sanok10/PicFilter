#include "filters.h"
#include <QImage>
#include <QString>
#include <cstdio>
#include <math.h>

QImage calculate(QImage, int, int, int, bool);
int* calcSum(int *sumArr, int startPosI,int startPosJ, int start, QImage input, bool filterType);
QImage usefilters (QImage, bool, int);
int widh, high;
int start; //размер сетки

QImage usefilters (QImage input, bool filterType, int filterSize)
{
    QImage result;
    for (int i = 0; i <= input.height(); i++)
    {
        for (int ii = 0; ii <= input.width(); ii++)
        {
            result = calculate(input, filterSize, i, ii, filterType);
        }
    }
    result = input;
    return result;
}

QImage calculate(QImage input, int start, int i, int j, bool filterType) // функция, вычисляющая среднее значение яркости
{
    int sum[2];//0 - яркость, 1 размер области
    int R, G, B, bright;
    if (i - start <= 0) //обработка краев изображения
    {
        calcSum(sum, 0, j - start, start, input, filterType);
    }
    else if (j - start <= 0)
    {
        calcSum(sum, i - start, 0, start, input, filterType);
    }
    else if (i - start > 0 && j-start > 0)
    {
        calcSum(sum, i - start, j - start, start, input, filterType);
    }
    else if (i - start <= 0 && j-start <= 0)
    {
        calcSum(sum, 0, 0, start, input, filterType);
    }
    if (filterType == true) // если фильтр среднеарифметический
    {
        bright = sum[0] / sum[1]; //вычисляем среднюю яркость области
        /*sum[0] = sum[0] / (start + 2)*(start + 2);
        sum[1] = sum[1] / (start + 2)*(start + 2);
        sum[2] = sum[2] / (start + 2)*(start + 2);*/
    }
    if (filterType == false) //если фильр среднеквадратичный
    {
        bright = pow(sum[0], 1/sum[1]);//вычисляем среднюю яркость области
      if (bright > 255) //на всякий случай
      {
        bright = 255;

      }

        /*
        sum[0] = pow(sum[0], 1/(start+2)) ;
        sum[1] =pow(sum[1], 1/(start+2));
        sum[2] =pow(sum[2], 1/(start+2));*/
    }
    //приводим яркость пикселя к яркости области
    QColor RGB(input.pixelColor(i,j));
    R = RGB.red();
    G = RGB.green();
    B = RGB.blue();

   //bright / ((R+G+B)/3)

    R = R * (bright / ((R+G+B)/3)) ; //получаем соотношение нужной яркости к текущей и приводим цвет к нужному
    G = G * (bright / ((R+G+B)/3)) ;
    B = B * (bright / ((R+G+B)/3)) ;
    input.setPixel(i, j, qRgb(R, G, B)); //устанавливаем цвет пикселя

    return input;
}
// я придумал усреднение цвета, а не яркости, я умный, но идиот
//а может попробовать это не менять? выше чето сыпется
//защити среднеквадратичный фильтр от нулей!
int* calcSum(int *sumArr, int startPosI,int startPosJ, int start, QImage input, bool filterType) //калькулятор суммы цветов области
{
    //вернем массив из средней яркости области и ее размера
        int high, widh;
    if (startPosI + start < input.height() && startPosJ + start < input.width() ) // обработка краев изображения
       {
            high = startPosI + start;
            widh = startPosJ + start;
       }
    if (startPosI + start > input.height())
    {
        high = input.height(); // если выходим за границы по высоте - считаем только до высоты
    }

    if (startPosJ + start > input.width())
    {
        widh = input.width(); // если выходим за границы по ширине - считаем только до ширины
    }
    for (int i2 = startPosI; i2 < high; i2++) // в зависимости от типа фильтра считаем по разному
        {
            for (int j2 = startPosI; j2 < widh; j2++)
                {
                  QColor RGB(input.pixelColor(i2,j2));
                if (filterType == true)
                {
                    sumArr[0] += (RGB.red() + RGB.green() + RGB.blue())/3; // считаем яркость пикселя и прибавляем ее к сумме яркостей
                }
                   if (filterType == false)
                  {
                       //защита от нулевых значений
                    if (RGB.red() == 0)
                    {
                        sumArr[0] *= (RGB.red()+1 + RGB.green() + RGB.blue())/3;
                    }
                    else
                    {
                       sumArr[0] *= (RGB.red() + RGB.green() + RGB.blue())/3;
                    }
                    if (RGB.green() == 0)
                    {
                        sumArr[0] *= (RGB.green()+ 1 + RGB.red()  + RGB.blue())/3;
                    }
                    else
                    {
                       sumArr[0] *= (RGB.red() + RGB.green() + RGB.blue())/3;
                    }
                    if (RGB.blue() == 0)
                    {
                        sumArr[0] *= (RGB.blue() + 1 + RGB.red() + RGB.green())/3;
                    }
                    else
                    {
                        sumArr[0] *= (RGB.red() + RGB.green() + RGB.blue())/3;
                    }

                  }
                }
        }
sumArr[1] = high*widh; // размер области
//sumArr[0] = sumArr[0]/sumArr[1]; //получаем среднюю яркость области
return sumArr;

}

int calkbright(int r, int g, int b) //функция считает яркость исходя из цвета в RGB
{
    int bright = (r+g+b)/3 ;
    return bright;
}
