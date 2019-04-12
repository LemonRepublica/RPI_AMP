// CC-by-www.Electrosmash.com open-source project
// clean.c effect pedal, the signal is read by the ADC and written again using 2 PWM sigmals. 

#include <bcm2835.h>
#include <stdio.h>

// Define Input Pins

uint32_t read_timer=0;
uint32_t input_signal=0;
uint32_t output_signal=0;

#define DELAY_MAX 800000 	//800000 is 4 seconds approx.
#define DELAY_MIN 0

//variables for delay
short delay_st = 0;
uint32_t Delay_Depth = 50000; //about 0.25s
uint32_t Delay_Buffer[DELAY_MAX];//define a buffer to record former data
uint32_t DelayCounter = 0;//delay time
uint32_t del = 0;//delay time discount
uint32_t del_lev = 1;//delay level discount
//variables for distortion
short distortion_st = 0;
uint32_t dis = 0;//gain discount
uint32_t distortion_gain = 100;
//varibles for reverb
//reverb is like 3 times delay
short reverb_st = 1;
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
uint32_t rev = 0;


int main(int argc, char **argv)
{
    // Start the BCM2835 Library to access GPIO.
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
	// Start the SPI BUS.
	if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
	
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
	//read 12 bits ADC
    bcm2835_spi_transfernb(mosi, miso, 3);
    input_signal = miso[2] + ((miso[1] & 0x0F) << 8); //once input 8 bits,so need 4bits from last time

	//Read the PUSH buttons every 50000 times (0.25s) to save resources.
    read_timer++;
    if (read_timer==50000)//every 0.25s read data from GUI
    {
        read_timer=0;
        printf("%d\n",input_signal);
        Delay_Depth = Delay_Depth + del * 5000;
        distortion_gain = distortion_gain - dis * 50;
        del_lev = del_lev;
        Reverb_Depth1 = Reverb_Depth1 + rev * 5000;
        Reverb_Depth2 = Reverb_Depth2 + rev * 5000;
        Reverb_Depth3 = Reverb_Depth3 + rev * 5000;


        printf(" ddd ");

    }
	

//distortion is to set the data which above or below the setting values direct to the values itself
    if(distortion_st==1)
            {
            if (input_signal > 1023 + distortion_gain)//define of anlog distortion
                input_signal= 1023 + distortion_gain;
            if (input_signal < 1023 - distortion_gain)
                input_signal= 1023 - distortion_gain;
            input_signal = input_signal;
    }

//delay is put the former data into a buffer and then put them to the output
    if(delay_st==1)
            {
            Delay_Buffer[DelayCounter] = ((int)(input_signal * del_lev * 0.5) + Delay_Buffer[DelayCounter])>>1;
    //      Delay_Buffer[DelayCounter] = input_signal;
            DelayCounter++;
            if(DelayCounter >= Delay_Depth)
                DelayCounter = 0;
            input_signal = (Delay_Buffer[DelayCounter]+input_signal)>>1;
            //input_signal = (int)(input_signal/2);
            //printf("%d\n",output_signal);
            //output_signal=input_signal;
        }
//reverb is imitate the effect in a carve or hall
//there are a lot of echoes in those place
//so apply multi-echo and then add them together to get a simple reverb
    if(reverb_st==1)
            {
            Reverb_Buffer1[ReverbCounter1]  = ((int)(input_signal * 0.5) + Reverb_Buffer1[ReverbCounter1])>>1;//set a discount to the input or the output maybe distorted
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
    
//in the anlog distortion the sound may be louder than the original sound
//however according to the code above the data is set to two constants
//the output is quiter,so take a boost to the output
    if(distortion_st==1)
    {
    input_signal = input_signal * 3;
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


