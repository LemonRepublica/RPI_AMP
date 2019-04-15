#ifndef ST_H
#define ST_H
#include <QObject>


class St
{
public:
    St();
    void distortion_st(uint32_t read_timer,
                       uint32_t distortion_gain,
                       uint32_t& input_signal);


    void eq_st(uint32_t read_timer,
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
               float buffery[]);

    void delay_st(uint32_t read_timer,
                  uint32_t Delay_Buffer[],
                  uint32_t& DelayCounter,
                  uint32_t& input_signal,
                  uint32_t Delay_Depth,
                  uint32_t del_lev);

    void reverb_st(uint32_t read_timer,
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
                   uint32_t Reverb_Depth5);

};

#endif // ST_H
