#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <bcm2835.h>
#include <stdio.h>

// Define Input Pins
uint32_t read_timer=0;
uint32_t input_signal=0;
uint32_t output_signal;

//variables for booster effect
short distortion = 1;
//short delay = 1;
uint32_t distortion_gain=2047;
//variables for delay effect
#define DELAY_MAX 800000 	//800000 is 4 seconds approx.
#define DELAY_MIN 0
uint32_t Delay_Buffer[DELAY_MAX];
uint32_t DelayCounter = 0;
uint32_t delay;

uint8_t dis = 0;
//uint8_t delay = 0;

//variables for echo effect
uint32_t Echo_Buffer[DELAY_MAX];
uint32_t Delay_Depth = 50000; //default starting delay is 100000 is 0.5 sec approx.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dial->setNotchesVisible(1);
    ui->dial_2->setNotchesVisible(1);
    ui->dial->setRange(0,100);
    ui->dial_2->setRange(0,100);
    SystemTimer=new QTimer(this);
    connect(SystemTimer,SIGNAL(timeout()),this,SLOT(UserMainLoop()));
    DistorTimer=new QTimer(this);
    connect(DistorTimer,SIGNAL(timeout()),this,SLOT(UserDistorLoop()));
    DelayTimer=new QTimer(this);
    connect(DelayTimer,SIGNAL(timeout()),this,SLOT(UserDelayLoop()));

    UserInit();

    mosi=new uint8_t[10]{ 0x01, 0x00, 0x00 }; //12 bit ADC read 0x08 ch0, - 0c for ch1
    miso=new uint8_t[10]{ 0 };
}
//---------------------------------------------------------------
uint8_t MainWindow::UserInit(void)
{
    qDebug()<<"UserInit";
//    if (!bcm2835_init())
//    {
//      printf("bcm2835_init failed. Are you running as root??\n");
//      qDebug()<<"bcm2835_init failed. Are you running as root??\n";
//      return 1;
//    }
//    // Start the SPI BUS.
//    if (!bcm2835_spi_begin())
//    {
//      printf("bcm2835_spi_begin failed. Are you running as root??\n");
//      qDebug()<<"bcm2835_spi_begin failed. Are you running as root??\n";
//      return 1;
//    }

//    //define PWM
//    bcm2835_gpio_fsel(18,BCM2835_GPIO_FSEL_ALT5 ); //PWM0 signal on GPIO18
//    bcm2835_gpio_fsel(13,BCM2835_GPIO_FSEL_ALT0 ); //PWM1 signal on GPIO13
//    bcm2835_pwm_set_clock(2); // Max clk frequency (19.2MHz/2 = 9.6MHz)
//    bcm2835_pwm_set_mode(0,1 , 1); //channel 0, markspace mode, PWM enabled.
//    bcm2835_pwm_set_range(0,64);   //channel 0, 64 is max range (6bits): 9.6MHz/64=150KHz switching PWM freq.
//    bcm2835_pwm_set_mode(1, 1, 1); //channel 1, markspace mode, PWM enabled.
//    bcm2835_pwm_set_range(1,64);   //channel 0, 64 is max range (6bits): 9.6MHz/64=150KHz switching PWM freq.

//    //define SPI bus configuration
//    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
//    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
//    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);       // 4MHz clock with _64
//    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
//    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
}
void MainWindow::UserMainLoop(void)
{
      qDebug()<<"MainLoop";
    //read 12 bits ADC
//    bcm2835_spi_transfernb(mosi, miso, 3);
//    input_signal = miso[2] + ((miso[1] & 0x0F) << 8);
//    read_timer++;
//    //Read the GUI every 50000 times (0.25s) to save resources.
//    if (read_timer==50000)
//    {
//        distortion_gain = distortion_gain + dis * 50;
//        Delay_Depth = Delay_Depth + delay * 5000;
//    }

}
void MainWindow::UserDistorLoop(void)
{
//    if(distortion)
//    {
//        if (input_signal > 2047 + distortion_gain)
//            input_signal= 2047 + distortion_gain;
//        if (input_signal < 2047 - distortion_gain)
//            input_signal= 2047 - distortion_gain;
//    }
        qDebug()<<"DistoryLoop";
}
void MainWindow::UserDelayLoop(void)
{
//    if(delay)
//    {
//        Delay_Buffer[DelayCounter] = input_signal;
//        DelayCounter++;
//        if(DelayCounter >= Delay_Depth)
//            DelayCounter = 0;
//        output_signal = (Delay_Buffer[DelayCounter]+input_signal)>>1;
//    }
        qDebug()<<"DelayLoop";
}
void MainWindow::UserOver(void)
{
//    bcm2835_pwm_set_data(1,output_signal & 0x3F);
//    bcm2835_pwm_set_data(0,output_signal >> 6);
//    //close all and exit
//    bcm2835_spi_end();
//    delete mosi;
//    delete miso;
      qDebug()<<"UserOver";
}

//----------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    SystemTimer->start(50);
    ui->pushButton->setDisabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    DistorTimer->start(50);
    ui->pushButton_2->setDisabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    DelayTimer->start(50);
    ui->pushButton_3->setDisabled(true);
}

void MainWindow::on_dial_valueChanged(int value)
{
    float v=0;
    v=value/10.0;
    //dis=v;
    qDebug()<<"value 1:"<<v;
}
void MainWindow::on_dial_2_valueChanged(int value)
{
    float v=0;
    v=value/10.0;
   // delay=v;
    qDebug()<<"value 2:"<<v;
}
MainWindow::~MainWindow()
{
    delete ui;
    SystemTimer->stop();
    DistorTimer->stop();
    DelayTimer->stop();
    delete SystemTimer;
    delete DistorTimer;
    delete DelayTimer;
    UserOver();
}
