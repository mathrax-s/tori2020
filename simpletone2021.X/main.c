/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC12F1840
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"



//‰¹ŠK‚ğ‚Â‚­‚é‚½‚ß‚Ìƒf[ƒ^iŠ„‚èØ‚ê‚é•”•ªj
const unsigned char onkai_d[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    5,
    5,
    5,
    5,
    6,
    6,
    7,
    7,
    7,
    8,
    8,
    9,
    10,
    10,
    11,
    11,
    12,
    13,
    14,
    14,
    15,
    16,
    17,
    18,
    20,
    21,
    22,
    23,
    25,
    26,
    28,
    29,
    31,
    33,
    35,
    37,
    40,
    42,
    44,
    47,
    50,
    53,
    56,
    59,
    63,
    67,
    71
};


//‰¹ŠK‚ğ‚Â‚­‚é‚½‚ß‚Ìƒf[ƒ^iŠ„‚èØ‚ê‚È‚¢‚ ‚Ü‚è‚Ì•”•ªj
const unsigned char onkai_f[] = {
    143,
    151,
    160,
    169,
    180,
    190,
    201,
    213,
    226,
    239,
    254,
    14,
    30,
    47,
    64,
    83,
    104,
    125,
    147,
    171,
    197,
    223,
    252,
    27,
    59,
    93,
    128,
    166,
    207,
    249,
    39,
    87,
    138,
    191,
    248,
    53,
    117,
    185,
    1,
    77,
    158,
    243,
    78,
    174,
    20,
    127,
    241,
    106,
    234,
    114,
    2,
    154,
    60,
    230,
    156,
    92,
    40,
    254,
    226,
    212,
    213,
    228,
    4,
    53,
    119,
    205,
    56,
    183,
    79,
    253,
    134,
    104,
    170,
    127,
    8,
    105,
    238,
    155,
    112,
    111,
    157,
    250,
    139,
    83,
    84
};

//‰¹ì‚è‚É‚Â‚©‚¤•Ï”
unsigned int waveData; //”gŒ`‚ğ“Ç‚İ‚Ş•Ï”
unsigned char voice_on; //‰¹‚ª–Â‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©ƒtƒ‰ƒO
unsigned char synth_waveData; //”gŒ`‚ğˆêŠi”[‚·‚é•Ï”
unsigned char env; //ƒGƒ“ƒxƒ[ƒvƒe[ƒuƒ‹‚ÌˆÊ’u
unsigned int envelopeCount; //ƒGƒ“ƒxƒ[ƒvŠÔ‚ğƒJƒEƒ“ƒg‚·‚é
unsigned char envelopeValue; //ƒGƒ“ƒxƒ[ƒv‚ğˆêŠi”[‚·‚é•Ï”

unsigned char dat_d; //‰¹ŠK‚ÌŒvZ‚É‚Â‚©‚¤•Ï”
unsigned char dat_f; //‰¹ŠK‚ÌŒvZ‚É‚Â‚©‚¤•Ï”
unsigned char pos_d; //‰¹ŠK‚ÌŒvZ‚É‚Â‚©‚¤•Ï”
unsigned int pos_f; //‰¹ŠK‚ÌŒvZ‚É‚Â‚©‚¤•Ï”
unsigned char pos; //‰¹ŠK‚ÌŒvZ‚É‚Â‚©‚¤•Ï”

//‰¹‚Ì’·‚³‚É‚Â‚©‚¤•Ï”
unsigned int pitch;
unsigned int count;
unsigned int ENV_DELAY; //ƒGƒ“ƒxƒ[ƒv‚ÌŠÔ


char scale[] = {

    NOTE_F6, NOTE_G6, NOTE_A6, NOTE_AS6, NOTE_C7, NOTE_D7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_A7

    

};

//‰¹‚ğ‚Ğ‚Æ‚Â‘I‚Ô‚Æ‚±‚ë
//ÀÛ‚É–Â‚ç‚·‚Ì‚Í‚±‚±‚Å‚Í‚È‚¢‚Å‚·

void soundPlay(char onkai) {
    //®”•”•ª
    dat_d = onkai_d[onkai];
    //¬”•”•ª
    dat_f = onkai_f[onkai];
    //ƒGƒ“ƒxƒ[ƒv‚ğÅ‰‚É‚à‚Ç‚·
    env = 0;
    envelopeCount = 0;
    //‰¹‚ª‚È‚Á‚Ä‚éƒtƒ‰ƒO‚ğ‚P‚É‚·‚é
    voice_on = 1;
}

/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    //ƒsƒbƒ`‚Æ‰¹‚Ì’·‚³‚ğ”‚¦‚éƒJƒEƒ“ƒ^‚ğ0‚É‚·‚é
    pitch = 0;
    count = 0;

    //•Ï”‚ğ0‚É‰Šú‰»‚·‚é
    voice_on = 0;
    env = 0;
    envelopeCount = 0;
    pos_d = 0;
    pos_f = 0;

    ENV_DELAY = 300; //*40;
    
    while (1) {
        // Add your application code
        if (EUSART_is_rx_ready()) {
            uint8_t data = EUSART_Read();

            if (data >= 'a' && data < ('a' + (int) sizeof (scale))) {
                soundPlay(scale[data - 'a']);
            }
        }

    }
}
/**
 End of File
 */