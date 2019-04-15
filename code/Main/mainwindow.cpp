//Overall view:
//This is a 4-effect guitar signal processer: Distortion, Delay, Reverb, EQ
//a GUI is applied to control all the effects

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "bcm2835.h"
#include <stdio.h>


//variable define

uint32_t read_timer=0;
uint32_t input_signal=0;
uint32_t output_signal=0;

#define DELAY_MAX 800000
#define DELAY_MIN 0

//variables for echo effect
short delay_st = 0;//delay on/off
uint32_t Delay_Depth = 50000; //50000means about 4 seconds
uint32_t Delay_Buffer[DELAY_MAX];//set a delay buffer to store former data
uint32_t DelayCounter = 0;
uint32_t del = 0;//control the delay time
uint32_t del_lev = 0;//control the delay level
short distortion_st = 0;//distortion on/off
float dis = 0.0;//control the level of distortion(also the level of the sound)
uint32_t distortion_gain = 100;
short reverb_st = 0;//reverb on/off
uint32_t Reverb_Depth1 = 10000;//reverb is like the delay effect,so their variable define is alike
uint32_t Reverb_Buffer1[DELAY_MAX];
uint32_t ReverbCounter1 = 0;
uint32_t Reverb_Depth2 = 15000;
uint32_t Reverb_Buffer2[DELAY_MAX];
uint32_t ReverbCounter2 = 0;
uint32_t Reverb_Depth3 = 15000;
uint32_t Reverb_Buffer3[DELAY_MAX];
uint32_t ReverbCounter3 = 0;
uint32_t Reverb_Depth4 = 30000;
uint32_t Reverb_Buffer4[DELAY_MAX];
uint32_t ReverbCounter4 = 0;
uint32_t Reverb_Depth5 = 25000;
uint32_t Reverb_Buffer5[DELAY_MAX];
uint32_t ReverbCounter5 = 0;//5 reverb buffers are set to simulate the reverb by apply multi echoes
float rev = 0;//reverb time control
short eq_st = 0;//EQ on/off
#define NZEROS 4//Zeros for 2nd order Butterworth filter
#define NPOLES 4//Poles
float eq_gain = 0.0;//gain for the IIR filter
float bass = 0;//select tone
float high = 0;//eq level control
double coe1 = 0.0;//Butterworth Bandstop filter need 6 coefficients
double coe2 = 0.0;
double coe3 = 0.0;
double coe4 = 0.0;
double coe5 = 0.0;
double coe6 = 0.0;
int countt = 0;//just a counter ,meaningless

static float bufferx[NZEROS+1];//this kink of IIR filter have delay of 6
static float buffery[NPOLES+1];
//------------------------------------------GUI
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
    ui->dial_7->setNotchesVisible(1);

    ui->dial->setRange(0,100);
    ui->dial_2->setRange(0,100);
    ui->dial_3->setRange(0,100);
    ui->dial_4->setRange(0,100);
    ui->dial_5->setRange(0,100);
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

    SystemTimer->start(0.01);
}
//---------------------------------------------------------------
uint8_t MainWindow::UserInit(void)
{
    qDebug()<<"UserInit";

    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    // Start the SPI BUS.
    bcm2835_spi_begin();
//   if (!bcm2835_spi_begin())
//    {
//      printf("bcm2835_spi_begin failed. Are you running as root??\n");
//      return 1;
//    }

    //define PWM
    bcm2835_gpio_fsel(18,BCM2835_GPIO_FSEL_ALT5 ); //PWM0 signal on GPIO18
    bcm2835_gpio_fsel(12,BCM2835_GPIO_FSEL_ALT0 ); //PWM1 signal on GPIO12
    bcm2835_pwm_set_clock(2); // Max clk frequency as 19.2MHz/2 = 9.6MHz
    bcm2835_pwm_set_mode(0,1 , 1); //channel 0, markspace mode, PWM enabled.
    bcm2835_pwm_set_range(0,64);   //64 is for 6bits(maxim)
    bcm2835_pwm_set_mode(1, 1, 1); //channel 1, markspace mode, PWM enabled.
    bcm2835_pwm_set_range(1,64);   //as above

    //define SPI bus configuration
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     
    
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64); 	  // 4MHz clock with _64
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
}
void MainWindow::UserMainLoop(void)
{
//the main loop start from here
      if(UserMainFlag)
      {
//          qDebug()<<"MainLoop";
         bcm2835_spi_transfernb((char *)mosi, (char *)miso, 3);
         input_signal = miso[2] + ((miso[1] & 0x0F) << 8);//once input 8 bits from ADC, so 12 bits ADC need 2 sequences to read the data
         //so the second sequence is 4 bits, 0x0F is for 00001111.
         //then put the data of two sequences together to get the full signal
         read_timer++;
         //qDebug()<<read_timer;
        //Read from the GUI every 50000 sequences
         if (read_timer==50000)
         {
             read_timer=0;
              qDebug()<<"MainLoop11";
             qDebug()<<"in"<<input_signal;
             //these data are controled by the GUI
             distortion_st =UserDistorFlag;
             delay_st =UserDelayFlag;
             reverb_st = UserReverbFlag;
             eq_st = UserEQFlag;
             bass = Get_BasValue();
             high = Get_HighValue();
             //high1 = (int)(high/2)+1;
             //qDebug()<<"high"<<high1;
             del = Get_DelayTimeValue();
            // qDebug()<<"del"<<del;
             Delay_Depth = 10000 + (int)(del * 5000);
             //transform the del_time value to the Delay_Depth, the min is 10000 sequences, the max is 60000
             //qDebug()<<"Delay_Depth"<<Delay_Depth;
             //qDebug()<<"dis"<<dis;
             distortion_gain = 100 + (int)(dis * 50);
             //transform distortion level value to distortion_gain
             //qDebug()<<"distortion_gain"<<distortion_gain;
             del_lev = Get_DelayLeverValue();
             if (del_lev>11)
                 del_lev = 0;
             //qDebug()<<"del_lev"<<del_lev;
             rev = rev;
             //qDebug()<<"rev"<<rev;
             rev = Get_ReverbLevelValue();
             //qDebug()<<"rev"<<rev;
             //like the Dealy effect
             Reverb_Depth1 = 10000 + rev * 3000;
             Reverb_Depth2 = 30000 + rev * 6000;
             Reverb_Depth3 = 20000 + rev * 3000;
             Reverb_Depth4 = 15000 + rev * 2000;
             Reverb_Depth5 = 20000 + rev * 5000;
             //printf(" ddd ");
             countt++;
             qDebug()<<"Count"<<countt;
         }

         if(distortion_st){
             st.distortion_st(read_timer, distortion_gain, input_signal);
         }
         //qDebug()<<"in"<<input_signal;

         if(eq_st){
             st.eq_st(read_timer, bass, coe1, coe2, coe3, coe4, coe5, coe6,
                      eq_gain, input_signal, high, bufferx, buffery);
         //qDebug()<<"in"<<input_signal;
         }
         if (read_timer==0){
             qDebug()<<"eqLoop1"<<input_signal;
         }

         if(delay_st){
             st.delay_st(read_timer,    Delay_Buffer,   DelayCounter,
                         input_signal,  Delay_Depth,    del_lev);
         }

         if(reverb_st){
             st.reverb_st(read_timer,       Reverb_Buffer1, ReverbCounter1, Reverb_Buffer2,
                          ReverbCounter2,   Reverb_Buffer3, ReverbCounter3, Reverb_Buffer4,
                          ReverbCounter4,   Reverb_Buffer5, ReverbCounter5, input_signal,
                          Reverb_Depth1,    Reverb_Depth2,  Reverb_Depth3,  Reverb_Depth4,
                          Reverb_Depth5);

         }



         if(distortion_st||reverb_st==1)
         {
             input_signal = (int)(input_signal * 1.5);
         }

        //see the output signal
         if (read_timer==0)
         {
             qDebug()<<"out"<<input_signal;
         }

         output_signal = input_signal;
         bcm2835_pwm_set_data(1,output_signal & 0x3F);
         bcm2835_pwm_set_data(0,output_signal >> 6);
         //PWM is 6 bits
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
float MainWindow::Get_HighValue(void)
{
    return HighValue;
}

void MainWindow::UserOver(void)
{
    bcm2835_spi_end();
    bcm2835_close();
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

