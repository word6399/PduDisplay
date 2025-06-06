// Copyright 2018-2025 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License. 

#include "dsps_biquad_platform.h"
#if (dsps_biquad_f32_arp4_enabled == 1)

// This is bi quad filter form II for ESP32 processor.
    .text
    .align  4
    .global dsps_biquad_sf32_arp4
    .type   dsps_biquad_sf32_arp4,@function
// The function implements the following C code:
//esp_err_t dsps_biquad_f32_arp4(const float* input, float* output, int len, float* coef, float* w)
//  {
//    for (int i = 0 ; i < len ; i++) {
//        float d0 = input[i*2 + 0] - coef[3] * w[0] - coef[4] * w[1];
//        output[i*2 + 0] = coef[0] * d0 +  coef[1] * w[0] + coef[2] * w[1];
//        w[1] = w[0];
//        w[0] = d0;
//
//        d0 = input[i*2 + 1] - coef[3] * w[2] - coef[4] * w[3];
//        output[i*2 + 1] = coef[0] * d0 +  coef[1] * w[2] + coef[2] * w[3];
//        w[3] = w[2];
//        w[2] = d0;
//    }
//    return ESP_OK;
//  }

dsps_biquad_sf32_arp4: 
// input    - a0
// output   - a1
// len  - a2
// coeffs  - a3
// w- a4

// fa0 - b0
// fa1 - b1
// fa2 - b2
// fa3 - a1
// fa4 - a2

// fa5 - w0
// fa6 - w1

    add sp,sp,-16

    flw         fa0, 0(a3) // coeff[0] : b0
    flw         fa1, 4(a3) // coeff[1] : b1
    flw         fa2, 8(a3) // coeff[2] : b2
    flw         fa3, 12(a3) // coeff[3] : a1
    flw         fa4, 16(a3) // coeff[4] : a2

    fneg.S      fa5, fa3    // -a[1]
    fneg.S      fa6, fa4    // -a[2]

    flw         ft0, 0(a4)  // ft0 - f7 w0
    flw         ft1, 4(a4)  // ft1 - f8 w1
    flw         ft5, 8(a4)  // ft0 - f12 w2
    flw         ft6, 12(a4)  // ft1 - f13 w3

    flw         ft2, 0(a0)      // ft2 - f9 = x[i]
    esp.lp.setup    0, a2, .iir_loop_end // label to the last executed instruction
        fmadd.S     ft2, ft0, fa5, ft2  // ft2 = x[i] - a1*w0

        fmul.s      ft3, fa1, ft0    // ft3 = w0*b1
        fmadd.s     ft2, ft1, fa6, ft2   // ft2 += -a2*w1 = d0

        fmadd.s     ft3, ft2, fa0, ft3  // f10 += b0*d0
        addi        a0, a0, 4           // in++;
        fmadd.s     ft3, fa2, ft1, ft3  // f10+= b2*w1, f10 - result

        fmv.s       ft1, ft0            // w1 = w0
        fmv.s       ft0, ft2            // w0 = d0

        flw         ft2, 0(a0)
        fsw         ft3, 0(a1)
        addi        a1, a1, 4           // out++;

        fmadd.S     ft2, ft5, fa5, ft2  // ft2 = x[i] - a1*w0
        fmul.s      ft3, fa1, ft5    // ft3 = w0*b1
        fmadd.s     ft2, ft6, fa6, ft2   // ft2 += -a2*w1 = d0


        fmadd.s     ft3, ft2, fa0, ft3  // f10 += b0*d0
        addi        a0, a0, 4           // in++;
        fmadd.s     ft3, fa2, ft6, ft3  // f10+= b2*w1, f10 - result

        fmv.s       ft6, ft5            // w1 = w0
        fmv.s       ft5, ft2            // w0 = d0

        flw         ft2, 0(a0)
        fsw         ft3, 0(a1)
        addi        a1, a1, 4           // out++;

.iir_loop_end: nop
    fsw         ft0, 0(a4)  // ft0 - f7
    fsw         ft1, 4(a4)  // ft1 - f8
    fsw         ft5, 8(a4)  // ft5 - f12
    fsw         ft6, 12(a4)  // ft6 - f13

    mv  a0, a6
    add sp,sp,16
    ret

#endif // dsps_biquad_f32_aes3_enabled
