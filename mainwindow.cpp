#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QString>
#include "filters.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool filterType; //тип фильтра false - среднеарифметический, true - медианный
QImage picture;

void MainWindow::on_openFileBttn_clicked() //открыть файл
{

    ::picture.load(ui->lineEdit->text());//загружаем путь из текстового окна
    QPixmap pixmap(ui->lineEdit->text()); //создаем пиксмап
    ui->label->setPixmap(pixmap);      //натягиваем сову на глобус
    ui->label->show();                 //
}

void MainWindow::on_saveBttn_clicked()
{
    ::picture.save(ui->lineEdit_2->text()); // сохраняем картинку по пути из 2 окна
    //сохранить результат
}

void MainWindow::on_goBttn_clicked()
{
    if (ui->SRfilterBttn->isChecked() != false || ui->adFilterBttn->isChecked() != false)
    {
        ::picture = usefilters(picture, ::filterType);//применяем фильтр
        ui->label_5->setText("Готово!");
    }
    else
    {
        ui->label_5->setText("Ошибка!");
    }
}


void MainWindow::on_SRfilterBttn_clicked()
{
    filterType = false;
    //выбран среднеквадратический фильтр
}

void MainWindow::on_adFilterBttn_clicked()
{
    //выбран адаптивный фильтр
}
