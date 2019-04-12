#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <stdint.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_dial_valueChanged(int value);
    void on_dial_2_valueChanged(int value);
    void UserMainLoop(void);
    void UserDistorLoop(void);
    void UserDelayLoop(void);
private:
    Ui::MainWindow *ui;
    QTimer *SystemTimer;
    QTimer *DistorTimer;
    QTimer *DelayTimer;

    uint8_t  *mosi; //12 bit ADC read 0x08 ch0, - 0c for ch1
    uint8_t  *miso;

    uint8_t UserInit(void);

    void UserOver(void);
};

#endif // MAINWINDOW_H
