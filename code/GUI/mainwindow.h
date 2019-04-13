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
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_dial_3_valueChanged(int value);

    void on_dial_4_valueChanged(int value);

    void on_dial_5_valueChanged(int value);

    void on_dial_6_valueChanged(int value);

    void on_dial_7_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QTimer *SystemTimer;

    uint8_t  *mosi; //12 bit ADC read 0x08 ch0, - 0c for ch1
    uint8_t  *miso;
    bool UserMainFlag;
    bool UserDistorFlag;
    bool UserDelayFlag;
    bool UserReverbFlag;
    bool UserEQFlag;

    float DelayTimeValue;
    float DelayLeverValue;
    float ReverbLevelValue;
    float BasValue;
    float MidValue;
    float HighValue;

    float Get_DelayTimeValue(void);
    float Get_DelayLeverValue(void);
    float Get_ReverbLevelValue(void);
    float Get_BasValue(void);
    float Get_MidValue(void);
    float Get_HighValue(void);

    uint8_t UserInit(void);

    void UserOver(void);
};

#endif // MAINWINDOW_H
