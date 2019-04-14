// CC-by-www.Electrosmash.com open-source project
// clean.c effect pedal, the signal is read by the ADC and wAAritten again using 2 PWM sigmals. 

#include <bcm2835.h>
#include <stdio.h>

// Define Input Pins

uint32_t read_timer=0;
uint32_t input_signal=0;
uint32_t output_signal=0;

#define DELAY_MAX 800000 	//800000 is 4 seconds approx.
#define DELAY_MIN 0

//variables for echo effect
short delay_st = 1;//控制延时（delay）功能开关，0开1关
uint32_t Delay_Depth = 50000; //default starting delay is 100000 is 0.5 sec approx.
uint32_t Delay_Buffer[DELAY_MAX];
uint32_t DelayCounter = 0;
uint32_t del = 0;//旋钮控制延时时间
uint32_t del_lev = 0;//旋钮控制延时大小
short distortion_st = 0;//控制失真（distortion）功能的开关
uint32_t dis = 0;//控制失真程度（旋钮）
uint32_t distortion_gain = 100;
short reverb_st = 0;//控制混响（reverb）开关
uint32_t Reverb_Depth1 = 10000;
uint32_t Reverb_Buffer1[DELAY_MAX];
uint32_t ReverbCounter1 = 0;
uint32_t Reverb_Depth2 = 50000;
uint32_t Reverb_Buffer2[DELAY_MAX];
uint32_t ReverbCounter2 = 0;
uint32_t Reverb_Depth3 = 50000;
uint32_t Reverb_Buffer3[DELAY_MAX];
uint32_t ReverbCounter3 = 0;
uint32_t Reverb_Depth4 = 50000;
uint32_t Reverb_Buffer4[DELAY_MAX];
uint32_t ReverbCounter4 = 0;
uint32_t rev = 0;//旋钮控制混响时间
short eq_st = 0;//控制均衡（eq）功能开关
#define NZEROS 2
#define NPOLES 2
long eq_gain = 0.0;
short bass = 0;//档位控制低通滤波器（但请做成旋钮。。。假装是个旋钮，类似于0-2 -->1档，2-4 -->2档之类的）
//short mid = 0;
short high = 0;//同上。。。控制高通滤波器
long coe_bass1 = 0.0;
long coe_bass2 = 0.0;
//long coe_mid1 = 0.0;
//long coe_mid2 = 0.0;
//long coe_mid3 = 0.0;
//long coe_mid4 = 0.0;
long coe_high1 = 0.0;
long coe_high2 = 0.0;

static float lowbufferx[NZEROS+1];
static float lowbuffery[NPOLES+1];
static float highbufferx[NZEROS+1];
static float highbuffery[NPOLES+1];

int main(int argc, char **argv)
{
    // Start the BCM2835 Library to access GPIO.
    if(!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
        // Start the SPI BUS.
    bcm2835_spi_begin();
//    if(!bcm2835_spi_begin())
//    {
//      printf("bcm2835_spi_begin failed. Are you running as root??\n");
//      return 1;
//    }
	
	//define PWM	
    printf(" bbb ");
    bcm2835_gpio_fsel(18,BCM2835_GPIO_FSEL_ALT5 ); //PWM0 signal on GPIO18    
    bcm2835_gpio_fsel(13,BCM2835_GPIO_FSEL_ALT0 ); //PWM1 signal on GPIO13    
	bcm2835_pwm_set_clock(2); // Max clk frequency (19.2MHz/2 = 9.6MHz)
    bcm2835_pwm_set_mode(0,1 , 1); //channel 0, markspace mode, PWM enabled. 
	bcm2835_pwm_set_range(0,64);   //channel 0, 64 is max range (6bits): 9.6MHz/64=150KHz switching PWM freq.
    bcm2835_pwm_set_mode(1, 1, 1); //channel 1, markspace mode, PWM enabled.
	bcm2835_pwm_set_range(1,64);   //channel 0, 64 is max range (6bits): 9.6MHz/64=150KHz switching PWM freq.
	
	//define SPI bus configuration
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64); 	  // 4MHz clock with _64 
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
;
   	uint8_t mosi[10] = { 0x01, 0x00, 0x00 }; //12 bit ADC read 0x08 ch0, - 0c for ch1 
	uint8_t miso[10] = { 0 };
	

	
	while(1) //Main Loop
	{
	//read 10 bits ADC
    bcm2835_spi_transfernb(mosi, miso, 3);
    input_signal = miso[2] + ((miso[1] & 0x0F) << 8); 


    read_timer++;
    
//每0.25秒从GUI读取一次数据
    if (read_timer==50000)
    {


        read_timer=0;
        printf("in %d\n",input_signal);
        distortion_st = distortion_st;
        delay_st = delay_st;
        eq_st = eq_st;
        reverb_st = reverb_st;
        bass = bass;
        high = high;  
        Delay_Depth = Delay_Depth + del * 5000;
        distortion_gain = distortion_gain - dis * 50;
        del_lev = del_lev;
        Reverb_Depth1 = Reverb_Depth1 + rev * 5000;
        Reverb_Depth2 = Reverb_Depth2 + rev * 5000;
        Reverb_Depth3 = Reverb_Depth3 + rev * 5000;    
        //printf(" ddd ");

    }
	
	//**** CLEAN EFFECT ***///
	//Nothing to do, the input_signal goes directly to the PWM output.
	
	//generate output PWM signal 6 bits


    if(distortion_st==1)
    {
            if (input_signal > 1023 + distortion_gain)
                input_signal= 1023 + distortion_gain;
            if (input_signal < 1023 - distortion_gain)
                input_signal= 1023 - distortion_gain;
            //input_signal = input_signal;
    }

    if(eq_st==1)
    {
        switch(bass)
        {
        case 1://100Hz
            coe_bass1 = -0.9780305085;
            coe_bass2 =  1.9777864838;
            eq_gain = 6.847831502e+02;
            break;
        case 2://500Hz
            coe_bass1 = -0.8948743446;
            coe_bass2 =  1.8890330794;
            eq_gain = 6.847831502e+02;
            break;
        case 3://1500Hz
            coe_bass1 = -0.7166338735;
            coe_bass2 =  1.6692031429;
            eq_gain = 8.433351019e+01;
            break;
        case 4://5000Hz
            coe_bass1 = -0.3333333333;
            coe_bass2 =  0.9428090416;
            eq_gain = 1.024264069e+01;
            break;
        case 5://10000Hz
            coe_bass1 = -0.7166338735;
            coe_bass2 =  1.6692031429;
            eq_gain = 3.414213562e+00;
            break;
        }

     lowbufferx[0] = lowbufferx[1];
     lowbufferx[1] = lowbufferx[2];
     lowbufferx[2] = input_signal/eq_gain;
     lowbuffery[0] = lowbuffery[1];
     lowbuffery[1] = lowbuffery[2];
     lowbuffery[2] = (lowbufferx[0] + lowbufferx[2]) + 2 * lowbufferx[1]
             + (coe_bass1 * lowbuffery[0]) + (coe_bass2 * lowbuffery[1]);
     input_signal = (int)lowbuffery[2];
     switch(high)
     {
     case 1://100Hz
         coe_high1 = -0.9780305085;
         coe_high2 =  1.9777864838;
         eq_gain = 1.011169123e+00;
         break;
     case 2://500Hz
         coe_high1 = -0.8948743446;
         coe_high2 =  1.8890330794;
         eq_gain = 1.057108315e+00;
         break;
     case 3://1500Hz
         coe_high1 = -0.7166338735;
         coe_high2 =  1.6692031429;
         eq_gain = 1.181391774e+00;
         break;
     case 4://5000Hz
         coe_high1 = -0.3333333333;
         coe_high2 =  0.9428090416;
         eq_gain = 1.757359313e+00;
         break;
     case 5://10000Hz
         coe_high1 = -0.1715728753;
         coe_high2 =  0.0000000000;
         eq_gain = 3.414213562e+00;
         break;
     }
     highbufferx[0] = highbufferx[1];
     highbufferx[1] = highbufferx[2];
     highbufferx[2] = input_signal/eq_gain;
     highbuffery[0] = highbuffery[1];
     highbuffery[1] = highbuffery[2];
     highbuffery[2] = (highbufferx[0] + highbufferx[2]) - 2 * highbufferx[1]
             + (coe_bass1 * highbuffery[0]) + (coe_bass2 * highbuffery[1]);
     input_signal = (int)highbuffery[2];
    }


    if(delay_st==1)
    {
            Delay_Buffer[DelayCounter] = (input_signal + Delay_Buffer[DelayCounter])>>1;
    //        Delay_Buffer[DelayCounter] = input_signal;
            DelayCounter++;
            if(DelayCounter >= Delay_Depth)
                DelayCounter = 0;
            input_signal = (Delay_Buffer[DelayCounter]+input_signal)>>1;
            //input_signal = (int)(input_signal/2);
            //printf("%d\n",output_signal);
            //output_signal=input_signal;
     }

    if(reverb_st==1)
    {
            Reverb_Buffer1[ReverbCounter1]  = ((int)(input_signal * 0.5) + Reverb_Buffer1[ReverbCounter1])>>1;
            Reverb_Buffer2[ReverbCounter2]  = ((int)(input_signal * 0.5) + Reverb_Buffer2[ReverbCounter2])>>1;
            Reverb_Buffer3[ReverbCounter3]  = ((int)(input_signal * 0.5) + Reverb_Buffer3[ReverbCounter3])>>1;
            Reverb_Buffer4[ReverbCounter4]  = ((int)(input_signal * 0.5) + Reverb_Buffer4[ReverbCounter4])>>1;

            ReverbCounter1++;
            if(ReverbCounter1 >= Reverb_Depth1)
                ReverbCounter1 = 0;

            ReverbCounter2++;
            if(ReverbCounter2 >= Reverb_Depth2)
                ReverbCounter2 = 0;

            ReverbCounter3++;
            if(ReverbCounter3 >= Reverb_Depth3)
                ReverbCounter3 = 0;
            ReverbCounter4++;
            if(ReverbCounter4 >= Reverb_Depth4)
                ReverbCounter4 = 0;

            input_signal=(input_signal + (Reverb_Buffer1[ReverbCounter1])+(Reverb_Buffer2[ReverbCounter2])
                          +(Reverb_Buffer3[ReverbCounter3])+ +(Reverb_Buffer4[ReverbCounter4]))>>2;
            //input_signal = (int)(input_signal/2);
    }
    if(distortion_st==1)
    {
        input_signal = input_signal * 2;
    }


    if (read_timer==0)
    {
        printf("out %d\n",input_signal);
    }
    

    
    
    output_signal = input_signal;
    bcm2835_pwm_set_data(1,output_signal & 0x3F);
    bcm2835_pwm_set_data(0,output_signal >> 6);

    }
	
	//close all and exit
	bcm2835_spi_end();
    bcm2835_close();
    return 0;
}


