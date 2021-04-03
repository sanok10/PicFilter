#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFileBttn_clicked();

    void on_saveBttn_clicked();

    void on_goBttn_clicked();

    void on_radioButton_clicked();

    void on_SRfilterBttn_clicked();

    void on_adFilterBttn_clicked();

    void on_fildSizeSlider_rangeChanged(int min, int max);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
