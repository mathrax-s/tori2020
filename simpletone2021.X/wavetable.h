/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef WAVETABLE_H
#define	WAVETABLE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
    volatile const unsigned char waveTable[] = {
        //サイン波
        // 
        127, 130, 133, 136, 139, 142, 145, 148, 152, 155, 158, 161, 164, 167, 170, 173,
        176, 179, 181, 184, 187, 190, 193, 195, 198, 200, 203, 206, 208, 210, 213, 215,
        217, 219, 222, 224, 226, 228, 230, 231, 233, 235, 237, 238, 240, 241, 242, 244,
        245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 253, 254, 254, 254, 254, 254,
        254, 254, 254, 254, 254, 253, 253, 252, 252, 251, 250, 250, 249, 248, 247, 246,
        244, 243, 242, 240, 239, 237, 236, 234, 232, 231, 229, 227, 225, 223, 221, 218,
        216, 214, 212, 209, 207, 204, 202, 199, 197, 194, 191, 188, 186, 183, 180, 177,
        174, 171, 168, 165, 162, 159, 156, 153, 150, 147, 144, 141, 138, 134, 131, 128,
        125, 122, 119, 115, 112, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79,
        76, 73, 70, 67, 65, 62, 59, 56, 54, 51, 49, 46, 44, 41, 39, 37,
        35, 32, 30, 28, 26, 24, 22, 21, 19, 17, 16, 14, 13, 11, 10, 9,
        7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 7, 8,
        9, 11, 12, 13, 15, 16, 18, 20, 22, 23, 25, 27, 29, 31, 34, 36,
        38, 40, 43, 45, 47, 50, 53, 55, 58, 60, 63, 66, 69, 72, 74, 77,
        80, 83, 86, 89, 92, 95, 98, 101, 105, 108, 111, 114, 117, 120, 123, 126,

    };



    //エンベロープ
    //データの数は必ず256個にしてください
    volatile const unsigned char envelopeTable[] = {
        ////減衰するカーブ
        127, 124, 121, 119, 116, 113, 111, 109, 106, 104, 102, 100, 97, 95, 93, 91,
        89, 87, 85, 84, 82, 80, 78, 77, 75, 73, 72, 70, 69, 67, 66, 64,
        63, 62, 60, 59, 58, 56, 55, 54, 53, 52, 51, 50, 48, 47, 46, 45,
        44, 43, 42, 42, 41, 40, 39, 38, 37, 36, 36, 35, 34, 33, 33, 32,
        31, 31, 30, 29, 29, 28, 27, 27, 26, 26, 25, 25, 24, 23, 23, 22,
        22, 21, 21, 21, 20, 20, 19, 19, 18, 18, 18, 17, 17, 16, 16, 16,
        15, 15, 15, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 11, 11, 11,
        11, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8,
        7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

        //  127,  121,  116,  111,  106,  102,  121,  97,  93,  89,  85,  82,  78,  75,  72,  69,
        //  66,  63,  60,  58,  55,  53,  51,  48,  46,  44,  42,  41,   39,   37,   36,   34,
        //   33,   31,   30,   29,   27,   26,   25,   24,   23,   22,   21,   20,   19,   18,   18,   17,
        //   16,   15,   15,   14,   13,   13,   12,   11,   11,   10,   10,   9,   9,   9,   8,   8,
        //   7,   7,   7,   6,   6,   6,   6,   5,   5,   5,   5,   4,   4,   4,   4,   4,
        //   3,   3,   3,   3,   3,   3,   3,   2,   2,   2,   2,   2,   2,   2,   2,   2,
        //   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
        //   0,   0,   0,   0,   0,   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0

    };
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* WAVETABLE_H */

