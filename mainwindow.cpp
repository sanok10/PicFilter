#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QString>
#include "filters.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool filterType; //тип фильтра false - среднеарифметический, true - медианный
QImage picture;
/*
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //Функция отображения координат пикселя и RGB значений
    int x=ui->label->x;
    int y=ui->label->y;

    QImage temp;
     temp = ui->label->pixmap()->toImage();
     QColor u= temp.pixel(x,y);

     ui->label_10->setText(QString::number(x)+','+QString::number(y));
     ui->label_11->setText(QString::number(u.red())+','+QString::number(u.green())+','+QString::number(u.blue()));
}
*/
void MainWindow::on_openFileBttn_clicked() //открыть файл
{

    ::picture.load(ui->lineEdit->text());//загружаем путь из текстового окна
    QPixmap pixmap(ui->lineEdit->text()); //создаем пиксмап
    ui->label->setPixmap(pixmap);      //натягиваем сову на глобус
    ui->label->show();
}

void MainWindow::on_saveBttn_clicked()
{
    ::picture.save(ui->lineEdit_2->text()); // сохраняем картинку по пути из 2 окна
    //сохранить результат
}

void MainWindow::on_goBttn_clicked()
{
    ui->label_5->setText("Выполняется");
    if (ui->SRfilterBttn->isChecked() != false || ui->radioButton->isChecked() != false)
    {
        ::picture = usefilters(::picture, ::filterType, ui->fildSizeSlider->value()); //применяем фильтр
        ::picture.save(ui->lineEdit_2->text()); // сохраняем картинку по пути из 2 окна
        QPixmap pixmap2(ui->lineEdit_2->text()); //создаем 2 пиксмап
        ui->label->setPixmap(pixmap2);      //натягиваем сову на глобус
        ui->label->show();                 //
        ui->label_5->setText("Готово!");
    }
    else
    {
        ui->label_5->setText("Ошибка!");
    }
}


void MainWindow::on_adFilterBttn_clicked()
{
    ::filterType = false;
    //выбран адаптивный фильтр
}

void MainWindow::on_fildSizeSlider_rangeChanged(int min, int max)
{

    ui->label_4->setText(QString(ui->fildSizeSlider->value()));
}

void MainWindow::on_radioButton_clicked()
{
    ::filterType = true;
    //выбран адаптивный усредняющий фильтр
}

/*void MainWindow::on_radioButton_pressed()
{
    ::filterType = true;
    //выбран адаптивный усредняющий фильтр
}*/

void MainWindow::on_SRfilterBttn_clicked()
{
    ::filterType = false; //выбран среднеарифметический
}


