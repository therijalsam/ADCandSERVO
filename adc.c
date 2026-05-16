#include <stdint.h>
#include "sleep.h"
#include <stdio.h>

// 7-Segment
#define SEG_CTL      *((uint32_t *)0x43C10000)
#define SEG_DATA     *((uint32_t *)0x43C10004)

// XADC
#define XADC_DATA    *((uint32_t *)0x43C5020C)
#define XADC_CFG     *((uint32_t *)0x43C50300)

// SERVO (TTC0)
#define TTC0_ClkCntl_0   *((uint32_t *)0xF8001000)
#define TTC0_OpMode_0    *((uint32_t *)0xF800100C)
#define TTC0_Interval_0  *((uint32_t *)0xF8001024)
#define TTC0_Match_0     *((uint32_t *)0xF8001030)
#define TTC0_InterruptEn_0 *((uint32_t *)0xF8001060)
#define TTC0_EvntCntl_0  *((uint32_t *)0xF800106C)


void Disp_BCD(uint16_t value)
{
    uint32_t temp = 0;
    SEG_CTL = 1;

    for (int i = 0; i < 4; i++) {
        temp |= (value % 10) << (i * 8);
        value /= 10;
    }

    temp |= 0x80808080;
    SEG_DATA = temp;
}

int main(void)
{
    uint16_t adc_val = 0;
    uint32_t servo_val = 162;  

 
    TTC0_OpMode_0 = 0x11;
    usleep(2000);

    TTC0_ClkCntl_0 = 0x13;
    usleep(2000);

    TTC0_Interval_0 = 2160;  
    usleep(2000);

    TTC0_Match_0 = 162;
    TTC0_InterruptEn_0 = 0;
    TTC0_EvntCntl_0 = 0;
    usleep(2000);

    TTC0_OpMode_0 = 0x4A;

    while (1)
    {
        XADC_CFG = 0x3803;

        adc_val = (XADC_DATA >> 4) & 0xFF80;

        Disp_BCD(adc_val);

        servo_val = 50 + ((adc_val * (275 - 50)) / 4095);

        TTC0_Match_0 = servo_val;

        usleep(10000);
    }
}
