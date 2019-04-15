#include "st.h"
#include <QDebug>

St::St()
{

}

void St::distortion_st(uint32_t read_timer,
                       uint32_t distortion_gain,
                       uint32_t& input_signal)
{
    if (read_timer==0){
        qDebug()<<"DistorLoop";
    }
    if (input_signal > 2047 + distortion_gain)
      input_signal= 2047 + distortion_gain;
    if (input_signal < 2047 - distortion_gain)
      input_signal= 2047 - distortion_gain;
}

void St::eq_st(uint32_t read_timer,
               float bass,
               double& coe1,
               double& coe2,
               double& coe3,
               double& coe4,
               double& coe5,
               double& coe6,
               float& eq_gain,
               uint32_t& input_signal,
               float high,
               float bufferx[],
               float buffery[])
{
    if (read_timer==0)
    {
    qDebug()<<"EQ Loop";
    qDebug()<<"bass"<<bass;
    qDebug()<<"high"<<high;
    qDebug()<<"coe1"<<coe1;
    }
     if (bass<=2)
      {
         //1000-15000Hz
         coe1 = -0.1742373434;
         coe2 =  0.4242847127;
         coe3 = -1.1742373434;
         coe4 =  1.9113247840;
         coe5 =  -3.6016161772;
         coe6 =   5.2429097719;
         eq_gain = 3.084091054e+00;
       }
     else if (bass<=4)
      {
         //2500-12500Hz
         coe1 = -0.3981522939;
         coe2 =  1.8048015305;
         coe3 = -3.3585222750;
         coe4 =  2.9448662203;
         coe5 =  -3.7885487581;
         coe6 =   5.5882754232;
         eq_gain = 1.595290011e+00;
      }
      else if (bass<=6)
      {
          //2500-12500Hz
          coe1 = -0.3981522939;
          coe2 =  1.8048015305;
          coe3 = -3.3585222750;
          coe4 =  2.9448662203;
          coe5 =  -3.7885487581;
          coe6 =   5.5882754232;
          eq_gain = 1.595290011e+00;
     }
      else if (bass<=8)
          {
          //250-5000Hz
          coe1 = -0.4954364568;
          coe2 =  2.2889737155;
          coe3 = -4.0847207924;
          coe4 =  3.2910462235;
          coe5 =  -3.9720369081;
          coe6 =   5.9442692998;
          eq_gain = 1.423664055e+00;
         }
     else
      {
      //150-1500Hz
          coe1 = -0.9048692656;
          coe2 =  3.7087063213;
          coe3 = -5.7027465052;
          coe4 =  3.8989090873;
          coe5 =  -3.9987658490;
          coe6 =   5.9975320787;
          eq_gain = 1.051253417e+00;
        }
      //qDebug()<<"basssss";
      bufferx[0] = bufferx[1];
      bufferx[1] = bufferx[2];
      bufferx[2] = bufferx[3];
      bufferx[3] = bufferx[4];
      bufferx[4] = input_signal/eq_gain;
      buffery[0] = buffery[1];
      buffery[1] = buffery[2];
      buffery[2] = buffery[3];
      buffery[3] = buffery[4];
      buffery[4] = (bufferx[0] + bufferx[4])
              + coe5 * (bufferx[1] + bufferx[3]) + coe6 * bufferx[2]
              + (coe1 * buffery[0]) + (coe2 * buffery[1])
              + (coe3 * buffery[2]) + (coe4 * buffery[3]);
      input_signal = (int)(buffery[4]*((high * 0.05)+0.5));

      //qDebug()<<"eqLoop"<<input_signal;
      if (read_timer==0){
          qDebug()<<"eqLoop"<<input_signal;
      }



}

void St::delay_st(uint32_t read_timer,
                  uint32_t Delay_Buffer[],
                  uint32_t& DelayCounter,
                  uint32_t& input_signal,
                  uint32_t Delay_Depth,
                  uint32_t del_lev)
{
    if (read_timer==0)
    {
        qDebug()<<"DelayLoop";
    }
    //Delay Loop is Here
    Delay_Buffer[DelayCounter] = input_signal + Delay_Buffer[DelayCounter]>>1;
    //        Delay_Buffer[DelayCounter] = input_signal;
    DelayCounter++;
    if(DelayCounter >= Delay_Depth)
      DelayCounter = 0;
    input_signal = (int)(Delay_Buffer[DelayCounter]* ((del_lev * 0.05)+0.5))+input_signal>>1;
    //input_signal = (int)(input_signal/2);
    //printf("%d\n",output_signal);
    //output_signal=input_signal;
}

void St::reverb_st(uint32_t read_timer,
                   uint32_t Reverb_Buffer1[],
                   uint32_t& ReverbCounter1,
                   uint32_t Reverb_Buffer2[],
                   uint32_t& ReverbCounter2,
                   uint32_t Reverb_Buffer3[],
                   uint32_t& ReverbCounter3,
                   uint32_t Reverb_Buffer4[],
                   uint32_t& ReverbCounter4,
                   uint32_t Reverb_Buffer5[],
                   uint32_t& ReverbCounter5,
                   uint32_t& input_signal,
                   uint32_t Reverb_Depth1,
                   uint32_t Reverb_Depth2,
                   uint32_t Reverb_Depth3,
                   uint32_t Reverb_Depth4,
                   uint32_t Reverb_Depth5)
{
    if (read_timer==0)
    {
        qDebug()<<"ReverLoop";
    }
    Reverb_Buffer1[ReverbCounter1]  = (input_signal + Reverb_Buffer1[ReverbCounter1])>>1;
    Reverb_Buffer2[ReverbCounter2]  = (input_signal + Reverb_Buffer2[ReverbCounter2])>>1;
    Reverb_Buffer3[ReverbCounter3]  = (input_signal + Reverb_Buffer3[ReverbCounter3])>>1;
    Reverb_Buffer4[ReverbCounter4]  = (input_signal + Reverb_Buffer4[ReverbCounter4])>>1;
    Reverb_Buffer5[ReverbCounter5]  = (input_signal + Reverb_Buffer5[ReverbCounter5])>>1;


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
    ReverbCounter5++;
    if(ReverbCounter5 >= Reverb_Depth5)
        ReverbCounter5 = 0;

    input_signal=(int)(input_signal + ((Reverb_Buffer1[ReverbCounter1]) * 0.65)
                       +((Reverb_Buffer2[ReverbCounter2]) * 0.6)
                       +((Reverb_Buffer3[ReverbCounter3] * 0.55))
                       +((Reverb_Buffer4[ReverbCounter4] * 0.5))
                       +((Reverb_Buffer5[ReverbCounter5] * 0.45)))>>2;
    //input_signal = (int)(input_signal * 1.1);
}
