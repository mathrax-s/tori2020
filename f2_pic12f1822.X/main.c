#include	<pic.h>														//	�v���W�F�N�g�ݒ�őI�����ꂽ�f�o�C�X�������I�Ɉ��p����܂�
#include	<stdlib.h>

#include "pitches.h"


__CONFIG(
        FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF
        & CPD_OFF & BOREN_OFF & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF
        );

__CONFIG(
        WRT_OFF & PLLEN_ON & STVREN_OFF & LVP_OFF
        );


#define	_XTAL_FREQ				32000000



extern const unsigned char sinwave[];
extern const unsigned char envelopeTable[];
extern const unsigned char onkai_d[];
extern const unsigned char onkai_f[];
extern unsigned char waveTable[];
extern unsigned int ENV_DELAY;
extern unsigned int dpos;


//���K�����邽�߂̃f�[�^�i����؂�镔���j
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


//���K�����邽�߂̃f�[�^�i����؂�Ȃ����܂�̕����j
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

//�����ɂ����ϐ�
unsigned int waveData; //�g�`��ǂݍ��ޕϐ�
unsigned char voice_on; //�������Ă��邩�ǂ����t���O
unsigned char synth_waveData; //�g�`���ꎞ�i�[����ϐ�
unsigned char env; //�G���x���[�v�e�[�u���̈ʒu
unsigned int envelopeCount; //�G���x���[�v���Ԃ��J�E���g����
unsigned char envelopeValue; //�G���x���[�v���ꎞ�i�[����ϐ�

unsigned char dat_d; //���K�̌v�Z�ɂ����ϐ�
unsigned char dat_f; //���K�̌v�Z�ɂ����ϐ�
unsigned int pos_d; //���K�̌v�Z�ɂ����ϐ�
unsigned int pos_f; //���K�̌v�Z�ɂ����ϐ�
unsigned char pos; //���K�̌v�Z�ɂ����ϐ�

//���̒����ɂ����ϐ�
unsigned int pitch;
unsigned int count;
unsigned int ENV_DELAY; //�G���x���[�v�̎���


char scale[] = {
    //re  mi   so  la  ti
    //NOTE_D5, NOTE_E5, NOTE_G5, NOTE_A5,
    //  NOTE_B5,
    //  NOTE_D6, NOTE_E6, NOTE_G6, NOTE_A6, NOTE_B6,
    //  NOTE_D7, NOTE_E7, NOTE_G7, NOTE_A7//, NOTE_B7,

    NOTE_F6, NOTE_G6, NOTE_A6, NOTE_AS6, NOTE_C7, NOTE_D7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_A7

    //NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_GS5, NOTE_B5,
    //NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_GS6, NOTE_B6,

    // NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_GS5, NOTE_AS5,
    // NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_GS6,
    // NOTE_C7, NOTE_D7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_GS7,

    //  NOTE_C5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,
    //  NOTE_C6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6,
    //  NOTE_C7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_A7

};

//�����ЂƂI�ԂƂ���
//���ۂɖ炷�̂͂����ł͂Ȃ��ł�

void soundPlay(char onkai) {
    //��������
    dat_d = onkai_d[onkai];
    //��������
    dat_f = onkai_f[onkai];
    //�G���x���[�v���ŏ��ɂ��ǂ�
    env = 0;
    envelopeCount = 0;
    //�����Ȃ��Ă�t���O���P�ɂ���
    voice_on = 1;
}

#define UART_BUFFER_SIZE   4     // �t�r�`�q�s�̎�M�o�b�t�@�T�C�Y
char UART_Buffer[UART_BUFFER_SIZE]; // ��M�����f�[�^���i�[����o�b�t�@
int UART_Buffer_inptr; // ��M�o�b�t�@�̓ǂݍ��݃|�C���^�[
int UART_Buffer_outptr; // ��M�o�b�t�@�̏������݃|�C���^�[

unsigned int UART_Read() {
    unsigned int ans;

    // �o�b�t�@�͋�ł���
    if (UART_Buffer_inptr == UART_Buffer_outptr) return 0xffff;
    // �o�b�t�@����ǂݏo��
    ans = UART_Buffer[UART_Buffer_inptr];
    // �o�b�t�@�ǂݍ��݃|�C���^�[�����ɐi�߂�
    UART_Buffer_inptr = (UART_Buffer_inptr + 1) % UART_BUFFER_SIZE;

    return ans;
}

int UART_Available() {
    return (UART_Buffer_outptr + UART_BUFFER_SIZE - UART_Buffer_inptr) % UART_BUFFER_SIZE;
}

void InitUART(int rx, int tx, char brg) {
    RXDTSEL = 0; // 6�ԃs��(RA1)��RX��M�s���Ƃ���
    TXCKSEL = 0; // 7�ԃs��(RA0)��TX���M�s���Ƃ���
    if (rx == 2) RXDTSEL = 1; // 2�ԃs��(RA5)��RX��M�s���Ƃ���
    if (tx == 3) TXCKSEL = 1; // 3�ԃs��(RA4)��TX��M�s���Ƃ���


    TXSTA = 0b00100100; // ���M���ݒ�F�񓯊����[�h�@�W�r�b�g�E�m���p���e�B
    RCSTA = 0b10010000; // ��M���ݒ�
    SPBRG = brg; // �{�[���[�g�̐ݒ�
    RCIF = 0; // USART�����ݎ�M�t���O�̏�����
    RCIE = 1; // USART�����ݎ�M��L���ɂ���
    PEIE = 1; // ���ӑ��u�����݂�L���ɂ���
    //GIE    = 1 ;                  // �S�����ݏ�����������
    UART_Buffer_inptr = 0; // ��M�o�b�t�@�̓ǂݍ��݃|�C���^�[�̏�����
    UART_Buffer_outptr = 0; // ��M�o�b�t�@�̏������݃|�C���^�[�̏�����
}

void main(void) {

    int i;
    int j;

    int data;

    OSCCON = 0b01110000;
    LATA = 0;
    TRISA = 0b00100000; //RA5 RX
    LATA = 0b00000000;

    //SWITCH
    //WPUA0 = 0;
    //InitUART(2, 3, 16); //115200
    InitUART(2, 3, 34); //57600

    //ALL Digital
    ANSELA = 0;

    CCP1SEL = 0; // 5�ԃs��(RA2)��CCP1�s���Ƃ��ďo��
    CCP1CON = 0b00001100; // PWM�@�\(�V���O��)���g�p����
    T2CON = 0b00000000; // TMR2�v���X�P�[���l���P�U�{�ɐݒ�
    CCPR1L = 0; // �f���[�e�B�l�͂O�ŏ�����
    CCPR1H = 0;
    TMR2 = 0; // �^�C�}�[�Q�J�E���^�[��������
    PR2 = 255; // PWM�̎�����ݒ�i1000Hz�Őݒ�j
    TMR2ON = 1; // TMR2(PWM)�X�^�[�g


    //	***** �^�C�}�O�̃��[�h�ݒ� *****
    OPTION_REG = 0;
    TMR0 = 0;
    T0IE = 0;
    T0IF = 0;

    // Timer0 interrupt
    T0IE = 1;
    GIE = 1;

    //�s�b�`�Ɖ��̒����𐔂���J�E���^��0�ɂ���
    pitch = 0;
    count = 0;

    //�ϐ���0�ɏ���������
    voice_on = 0;
    env = 0;
    envelopeCount = 0;
    pos_d = 0;
    pos_f = 0;

    ENV_DELAY = 300; //*40;
    while (1) {


        if (UART_Available() != 0) {
            // ��M�����f�[�^�ɉ��s�R�[�h��t���Ă��̂܂ܕԂ�
            data = UART_Read(); // �P�o�C�g�f�[�^����M����

            if (data >= 'a' && data < ('a' + (int) sizeof (scale))) {
                soundPlay(scale[data - 'a']);
            }

        }
    }

}

/******************************
GlobalInt
 *******************************/
void interrupt GlobalInt(void) {
    int i;
    int x;
    char dt;

    if (RCIF == 1) { // �����݂͂t�r�`�q�s�ʐM�̎�M���H
        // ���W�X�^����f�[�^����M
        dt = RCREG;
        x = (UART_Buffer_outptr + 1) % UART_BUFFER_SIZE;
        if (x != UART_Buffer_inptr) {
            // �o�b�t�@�����t�łȂ��Ȃ�f�[�^��ۑ�����
            UART_Buffer[UART_Buffer_outptr] = dt;
            // �o�b�t�@�������݃|�C���^�[�����ɐi�߂�
            UART_Buffer_outptr = x;
        }

        // �I�[�o�����G���[����(RCREG�o�b�t�@���R�ڂ̃f�[�^����M������I�[�o�t���[)
        if (OERR == 1) {
            CREN = 0;
            while (OERR);
            CREN = 1;
        }

        // �����ݎ�M�t���O�����Z�b�g
        RCIF = 0;
    }


    if (T0IF) {
        //�X�s�[�J�[�ɏo���g�`���O�ɂ��āA
        waveData = 0;

        //�����A�����Ȃ��Ă�t���O���P��������A
        if (voice_on) {

            //�����̔g�f�[�^�ɁA�T�C���g�e�[�u����pos�̈ʒu�̒l��ݒ�
            synth_waveData = waveTable[pos];

            //�G���x���[�v����
            //�G���x���[�v���ԃJ�E���g���O��������A
            if (envelopeCount == 0) {
                //�G���x���[�v�̒l���A�G���x���[�v�e�[�u����env�̈ʒu�̒l��ݒ�
                //������env�͎��փJ�E���g
                envelopeValue = envelopeTable[env++];

                //�G���x���[�v���Ԃ��AENV_DELAY�ɂ���
                envelopeCount = ENV_DELAY;

                //�����G���x���[�v�e�[�u���ʒu���Ō�ɂȂ�����A
                if (env == 255) {
                    //�����Ȃ��Ă�t���O���O�ɂ���
                    voice_on = 0;
                }

            }                //�G���x���[�v���Ԃ��Â��Ă���Ƃ��A
            else {
                //�G���x���[�v���Ԃ��J�E���g�_�E��
                envelopeCount--;
            }


            //�T�C���g���������ɓǂݏo�������v�Z����Ƃ���
            //���������́A���̂܂ܑ����Ă���
            pos_d += dat_d;
            //�����������A���̂܂ܑ����Ă���
            pos_f += dat_f;

            //�ŏI�I�ɂ́A
            //�����ꂽ���������ƁA�����ꂽ������256�Ŋ������l���A�T�C���g�e�[�u���̈ʒu�ɂȂ�
            pos = (pos_d + (pos_f >> 8)) & 0xFF;

        }

        //�a���̌v�Z
        //���ꂼ��̉��̔g�`�ɁA�G���x���[�v���������̂��A�����B
        waveData = synth_waveData * envelopeValue >> 7;


        CCPR1L = waveData; ///NUM_VOICE;
        T0IF = 0;
    }


}
