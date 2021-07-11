/**
  @Generated PIC10 / PIC12 / PIC16 / PIC18 MCUs Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.h

  @Summary:
    This is the mcc.h file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78.1
        Device            :  PIC12F1840
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above or later
        MPLAB             :  MPLAB X 5.30
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

#ifndef MCC_H
#define	MCC_H
#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include "interrupt_manager.h"
#include "epwm.h"
#include "tmr2.h"
#include "tmr0.h"
#include "eusart.h"
#include "../pitches.h"
#include "../wavetable.h"

extern const unsigned char sinwave[];
extern volatile const unsigned char envelopeTable[];
extern const unsigned char onkai_d[];
extern const unsigned char onkai_f[];
extern volatile const unsigned char waveTable[];
extern unsigned int ENV_DELAY;
extern unsigned int dpos;

//�����ɂ����ϐ�
extern unsigned int waveData; //�g�`��ǂݍ��ޕϐ�
extern unsigned char voice_on; //�������Ă��邩�ǂ����t���O
extern unsigned char synth_waveData; //�g�`���ꎞ�i�[����ϐ�
extern unsigned char env; //�G���x���[�v�e�[�u���̈ʒu
extern unsigned int envelopeCount; //�G���x���[�v���Ԃ��J�E���g����
extern unsigned char envelopeValue; //�G���x���[�v���ꎞ�i�[����ϐ�

extern unsigned char dat_d; //���K�̌v�Z�ɂ����ϐ�
extern unsigned char dat_f; //���K�̌v�Z�ɂ����ϐ�
extern unsigned char pos_d; //���K�̌v�Z�ɂ����ϐ�
extern unsigned int pos_f; //���K�̌v�Z�ɂ����ϐ�
extern unsigned char pos; //���K�̌v�Z�ɂ����ϐ�

//���̒����ɂ����ϐ�
extern unsigned int pitch;
extern unsigned int count;
extern unsigned int ENV_DELAY; //�G���x���[�v�̎���

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */
void SYSTEM_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 * @Example
    OSCILLATOR_Initialize(void);
 */
void OSCILLATOR_Initialize(void);
/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the WDT module to the default states configured in the
 *                  MCC GUI
 * @Example
    WDT_Initialize(void);
 */
void WDT_Initialize(void);

#endif	/* MCC_H */
/**
 End of File
*/