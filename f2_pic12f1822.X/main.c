#include	<pic.h>														//	プロジェクト設定で選択されたデバイスが自動的に引用されます
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


//音階をつくるためのデータ（割り切れる部分）
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


//音階をつくるためのデータ（割り切れないあまりの部分）
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

//音作りにつかう変数
unsigned int waveData; //波形を読み込む変数
unsigned char voice_on; //音が鳴っているかどうかフラグ
unsigned char synth_waveData; //波形を一時格納する変数
unsigned char env; //エンベロープテーブルの位置
unsigned int envelopeCount; //エンベロープ時間をカウントする
unsigned char envelopeValue; //エンベロープを一時格納する変数

unsigned char dat_d; //音階の計算につかう変数
unsigned char dat_f; //音階の計算につかう変数
unsigned int pos_d; //音階の計算につかう変数
unsigned int pos_f; //音階の計算につかう変数
unsigned char pos; //音階の計算につかう変数

//音の長さにつかう変数
unsigned int pitch;
unsigned int count;
unsigned int ENV_DELAY; //エンベロープの時間


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

//音をひとつ選ぶところ
//実際に鳴らすのはここではないです

void soundPlay(char onkai) {
    //整数部分
    dat_d = onkai_d[onkai];
    //小数部分
    dat_f = onkai_f[onkai];
    //エンベロープを最初にもどす
    env = 0;
    envelopeCount = 0;
    //音がなってるフラグを１にする
    voice_on = 1;
}

#define UART_BUFFER_SIZE   4     // ＵＳＡＲＴの受信バッファサイズ
char UART_Buffer[UART_BUFFER_SIZE]; // 受信したデータを格納するバッファ
int UART_Buffer_inptr; // 受信バッファの読み込みポインター
int UART_Buffer_outptr; // 受信バッファの書き込みポインター

unsigned int UART_Read() {
    unsigned int ans;

    // バッファは空である
    if (UART_Buffer_inptr == UART_Buffer_outptr) return 0xffff;
    // バッファから読み出す
    ans = UART_Buffer[UART_Buffer_inptr];
    // バッファ読み込みポインターを次に進める
    UART_Buffer_inptr = (UART_Buffer_inptr + 1) % UART_BUFFER_SIZE;

    return ans;
}

int UART_Available() {
    return (UART_Buffer_outptr + UART_BUFFER_SIZE - UART_Buffer_inptr) % UART_BUFFER_SIZE;
}

void InitUART(int rx, int tx, char brg) {
    RXDTSEL = 0; // 6番ピン(RA1)をRX受信ピンとする
    TXCKSEL = 0; // 7番ピン(RA0)をTX送信ピンとする
    if (rx == 2) RXDTSEL = 1; // 2番ピン(RA5)をRX受信ピンとする
    if (tx == 3) TXCKSEL = 1; // 3番ピン(RA4)をTX受信ピンとする


    TXSTA = 0b00100100; // 送信情報設定：非同期モード　８ビット・ノンパリティ
    RCSTA = 0b10010000; // 受信情報設定
    SPBRG = brg; // ボーレートの設定
    RCIF = 0; // USART割込み受信フラグの初期化
    RCIE = 1; // USART割込み受信を有効にする
    PEIE = 1; // 周辺装置割込みを有効にする
    //GIE    = 1 ;                  // 全割込み処理を許可する
    UART_Buffer_inptr = 0; // 受信バッファの読み込みポインターの初期化
    UART_Buffer_outptr = 0; // 受信バッファの書き込みポインターの初期化
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

    CCP1SEL = 0; // 5番ピン(RA2)をCCP1ピンとして出力
    CCP1CON = 0b00001100; // PWM機能(シングル)を使用する
    T2CON = 0b00000000; // TMR2プリスケーラ値を１６倍に設定
    CCPR1L = 0; // デューティ値は０で初期化
    CCPR1H = 0;
    TMR2 = 0; // タイマー２カウンターを初期化
    PR2 = 255; // PWMの周期を設定（1000Hzで設定）
    TMR2ON = 1; // TMR2(PWM)スタート


    //	***** タイマ０のモード設定 *****
    OPTION_REG = 0;
    TMR0 = 0;
    T0IE = 0;
    T0IF = 0;

    // Timer0 interrupt
    T0IE = 1;
    GIE = 1;

    //ピッチと音の長さを数えるカウンタを0にする
    pitch = 0;
    count = 0;

    //変数を0に初期化する
    voice_on = 0;
    env = 0;
    envelopeCount = 0;
    pos_d = 0;
    pos_f = 0;

    ENV_DELAY = 300; //*40;
    while (1) {


        if (UART_Available() != 0) {
            // 受信したデータに改行コードを付けてそのまま返す
            data = UART_Read(); // １バイトデータを受信する

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

    if (RCIF == 1) { // 割込みはＵＳＡＲＴ通信の受信か？
        // レジスタからデータを受信
        dt = RCREG;
        x = (UART_Buffer_outptr + 1) % UART_BUFFER_SIZE;
        if (x != UART_Buffer_inptr) {
            // バッファが満杯でないならデータを保存する
            UART_Buffer[UART_Buffer_outptr] = dt;
            // バッファ書き込みポインターを次に進める
            UART_Buffer_outptr = x;
        }

        // オーバランエラー処理(RCREGバッファが３個目のデータを受信したらオーバフロー)
        if (OERR == 1) {
            CREN = 0;
            while (OERR);
            CREN = 1;
        }

        // 割込み受信フラグをリセット
        RCIF = 0;
    }


    if (T0IF) {
        //スピーカーに出す波形を０にして、
        waveData = 0;

        //もし、音がなってるフラグが１だったら、
        if (voice_on) {

            //自分の波データに、サイン波テーブルのposの位置の値を設定
            synth_waveData = waveTable[pos];

            //エンベロープ処理
            //エンベロープ時間カウントが０だったら、
            if (envelopeCount == 0) {
                //エンベロープの値を、エンベロープテーブルのenvの位置の値を設定
                //同時にenvは次へカウント
                envelopeValue = envelopeTable[env++];

                //エンベロープ時間を、ENV_DELAYにする
                envelopeCount = ENV_DELAY;

                //もしエンベロープテーブル位置が最後になったら、
                if (env == 255) {
                    //音がなってるフラグを０にする
                    voice_on = 0;
                }

            }                //エンベロープ時間がつづいているとき、
            else {
                //エンベロープ時間をカウントダウン
                envelopeCount--;
            }


            //サイン波を何個おきに読み出すかを計算するところ
            //整数部分は、そのまま足していく
            pos_d += dat_d;
            //小数部分も、そのまま足していく
            pos_f += dat_f;

            //最終的には、
            //足された整数部分と、足された小数を256で割った値が、サイン波テーブルの位置になる
            pos = (pos_d + (pos_f >> 8)) & 0xFF;

        }

        //和音の計算
        //それぞれの音の波形に、エンベロープをつけたものを、足す。
        waveData = synth_waveData * envelopeValue >> 7;


        CCPR1L = waveData; ///NUM_VOICE;
        T0IF = 0;
    }


}
