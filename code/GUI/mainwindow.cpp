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
    ui->dial_3->setNotchesVisible(1);
    ui->dial_4->setNotchesVisible(1);
    ui->dial_5->setNotchesVisible(1);
    ui->dial_6->setNotchesVisible(1);
    ui->dial_7->setNotchesVisible(1);

    ui->dial->setRange(0,100);
    ui->dial_2->setRange(0,100);
    ui->dial_3->setRange(0,100);
    ui->dial_4->setRange(0,100);
    ui->dial_5->setRange(0,100);
    ui->dial_6->setRange(0,100);
    ui->dial_7->setRange(0,100);

    SystemTimer=new QTimer(this);
    connect(SystemTimer,SIGNAL(timeout()),this,SLOT(UserMainLoop()));
    UserMainFlag=false;
    UserDistorFlag=false;
    UserDelayFlag=false;
    UserReverbFlag=false;
    UserEQFlag=false;

    UserInit();

    mosi=new uint8_t[10]{ 0x01, 0x00, 0x00 }; //12 bit ADC read 0x08 ch0, - 0c for ch1
    miso=new uint8_t[10]{ 0 };

    SystemTimer->start(50);
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
      if(UserMainFlag)
      {
         qDebug()<<"MainLoop";
         //Main Loop  is Here
         if(UserDistorFlag)
         {
           qDebug()<<"DistorLoop";
           //Distor Loop is Here
		   cout<<""<<get
         }
         if(UserDelayFlag)
         {
           qDebug()<<"DelayLoop";
           //Delay Loop is Here
         }
         if(UserReverbFlag)
         {
           qDebug()<<"ReverLoop";
         }
         if(UserEQFlag)
         {
           qDebug()<<"EQ Loop";
         }

      }

}
float MainWindow::Get_DelayTimeValue(void)
{
    return DelayTimeValue;
}
float MainWindow::Get_DelayLeverValue(void)
{
    return DelayLeverValue;
}
float MainWindow::Get_ReverbLevelValue(void)
{
    return ReverbLevelValue;
}
float MainWindow::Get_BasValue(void)
{
    return BasValue;
}
float MainWindow::Get_MidValue(void)
{
    return MidValue;
}
float MainWindow::Get_HighValue(void)
{
    return HighValue;
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
    UserMainFlag=UserMainFlag==true?false:true;
}

void MainWindow::on_pushButton_2_clicked()
{
    UserDistorFlag=UserDistorFlag==true?false:true;
}

void MainWindow::on_pushButton_3_clicked()
{
    UserDelayFlag=UserDelayFlag==true?false:true;
}
void MainWindow::on_pushButton_4_clicked()
{
    UserReverbFlag=UserReverbFlag==true?false:true;
}

void MainWindow::on_pushButton_5_clicked()
{
    UserEQFlag=UserEQFlag==true?false:true;
}

void MainWindow::on_dial_valueChanged(int value)
{
    float v=0;
    v=value/10.0;
    dis=v;
}
void MainWindow::on_dial_2_valueChanged(int value)
{
   DelayTimeValue=value/10.0;
}
void MainWindow::on_dial_3_valueChanged(int value)
{
   DelayLeverValue=value/10.0;
}

void MainWindow::on_dial_4_valueChanged(int value)
{
   ReverbLevelValue=value/10.0;
}

void MainWindow::on_dial_5_valueChanged(int value)
{
    BasValue=value/10.0;
}

void MainWindow::on_dial_6_valueChanged(int value)
{
    MidValue=value/10.0;
}

void MainWindow::on_dial_7_valueChanged(int value)
{
    HighValue=value/10.0;
}

MainWindow::~MainWindow()
{
    delete ui;
    SystemTimer->stop();
    delete SystemTimer;
    UserOver();
}

