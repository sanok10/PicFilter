#include "filters.h"
#include <QImage>
#include <QString>
#include <cstdio>
#include <math.h>

float calculate(QImage, int, int, int, bool);
float* calcSum(float *sumArr, int startPosI,int startPosJ, int start, QImage input, bool filterType);
QImage usefilters (QImage, bool, int);
int widh, high;
int start; //размер сетки

QImage usefilters (QImage input, bool filterType, int filterSize)
{
    long R, G, B, RpGpB;
    float bright;
    QImage result;
    for (int i = 0; i < input.width(); i++)
    {
        for (int ii = 0; ii < input.height(); ii++)
        {
            bright = calculate(input, filterSize, i, ii, filterType);
            //приводим яркость пикселя к яркости области
            QColor RGB(input.pixelColor(i,ii)); //перепутаны i и j
            R = RGB.red();
            G = RGB.green();
            B = RGB.blue();

           //bright / ((R+G+B)/3)
            RpGpB = (R+G+B)/3; //текущая яркость пикселя
            if (RpGpB == 0)
            {
                RpGpB = 1;// защита от деления на 0
            }
            if (bright == 0)
            {
                bright = 1;// защита от 0 значения яркости
            }
            if (R == 0 || G == 0 || B == 0)
            {
                if (R == 0)
                {
                    R += 1;
                }
                if (G == 0)
                {
                    G += 1;
                }
                if (B == 0)
                {
                    B +=1;
                }
            }
               R = R * bright / RpGpB; //получаем соотношение нужной яркости к текущей и приводим цвет к нужному
               G = G * bright / RpGpB;
               B = B * bright / RpGpB;
               if (R > 255 || G > 255 || B >255)
               {
                   if (R > 255)
                   {
                       R = 255;
                   }
                   if (G > 255)
                   {
                       G = 255;
                   }
                   if (B > 255)
                   {
                       B = 255;
                   }
               }
               input.setPixel(i, ii, qRgb(R, G, B)); //устанавливаем цвет пикселя перепутаны i и j

            //result = calculate(input, filterSize, i, ii, filterType);
        }
    }
    result = input;
    return result;
}

float calculate(QImage input, int start, int i, int j, bool filterType) // функция, вычисляющая среднее значение яркости
{
    float sum[2];//0 - яркость, 1 размер области
    sum [0] = 1;
    sum [1] = 1;
    long int R, G, B;
    float bright;
    if (i - start < 0) //обработка краев изображения
    {
        if (j - start >= 0)
        {
            calcSum(sum, 0, j - start, start, input, filterType);
        }
        else if (j - start < 0)
        {
             calcSum(sum, 0, 0, start, input, filterType);
        }
    }
    else if (i - start >= 0)
    {
        if (j - start >= 0 )
        {
            calcSum(sum, i - start, j - start, start, input, filterType);
        }
        else if (j - start < 0)
        {
            calcSum(sum, i - start, 0, start, input, filterType);
        }
    }
    if (sum[1] == 0)
    {
        sum[1]=1;
    }
    if (filterType == false) // если фильтр среднеарифметический
    {
        bright = sum[0] / (sum[1]*3); //вычисляем среднюю яркость области
    }
    else //если фильр среднеквадратичный
    {
        bright = pow(sum[0], (sum[1]/3));//вычисляем среднюю яркость области
      if (bright > 255) //на всякий случай
      {
        bright = 255;
      }

    }

    return bright;
}

//защити среднеквадратичный фильтр от нулей!
float* calcSum(float *sumArr, int startPosI,int startPosJ, int start, QImage input, bool filterType) //калькулятор суммы цветов области
{
    //вернем массив из средней яркости области и ее размера
        int high, widh;
    if (startPosI + start < input.width() && startPosJ + start < input.height() ) // обработка краев изображения
       {
            high = startPosI + start;
            widh = startPosJ + start;
       }
    if (startPosI + start > input.width())
    {
        high = input.height(); // если выходим за границы по высоте - считаем только до высоты
    }

    if (startPosJ + start > input.height())
    {
        widh = input.width(); // если выходим за границы по ширине - считаем только до ширины
    }
    for (int i2 = startPosI; i2 < high; i2++) // в зависимости от типа фильтра считаем по разному
        {
            for (int j2 = startPosI; j2 <= widh; j2++)
                {
                  QColor RGB(input.pixelColor(i2,j2));
                  float r = RGB.red();
                  float g = RGB.green();
                  float b = RGB.blue();
                if (filterType == false)
                {
                    sumArr[0] += (r + g + b)/3; // считаем яркость пикселя и прибавляем ее к сумме яркостей
                }
                   else if (filterType == true)
                  {
                       //защита от нулевых значений
                    //float r=1,g=1,b=1;
                    if (RGB.red() == 0 || RGB.green() == 0 ||RGB.blue() == 0)
                    {
                        if (RGB.green() == 0)
                        {
                          g = RGB.green() + 1 ;
                        }
                        if (RGB.red() == 0)
                        {
                           r = RGB.red()+1;
                        }

                        if (RGB.blue() == 0)
                        {
                           b = RGB.blue() + 1;
                        }
                         sumArr[0] *= (g+r+b)/3;
                    }
                    else
                    {
                       sumArr[0] *= (r+g+b)/3;
                    }
                  }
                }
        }
sumArr[1] = high*widh; // размер области
//sumArr[0] = sumArr[0]/sumArr[1]; //получаем среднюю яркость области
return sumArr;

}

float calkbright(int r, int g, int b) //функция считает яркость исходя из цвета в RGB
{
    float bright = (r+g+b)/3 ;
    return bright;
}
