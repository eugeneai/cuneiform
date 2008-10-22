/*
Copyright (c) 2008, Jussi Pakkanen

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the Cognitive Technologies nor the names of its
      contributors may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/** \file
 * Tables to convert characters in Windows code page
 * formats to UTF-8.
 */

#ifndef UTF8_TABLES_H_
#define UTF8_TABLES_H_


const char win1250_to_utf8[][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {2, 0, 0, 0},
  {3, 0, 0, 0},
  {4, 0, 0, 0},
  {5, 0, 0, 0},
  {6, 0, 0, 0},
  {7, 0, 0, 0},
  {8, 0, 0, 0},
  {9, 0, 0, 0},
  {10, 0, 0, 0},
  {11, 0, 0, 0},
  {12, 0, 0, 0},
  {13, 0, 0, 0},
  {14, 0, 0, 0},
  {15, 0, 0, 0},
  {16, 0, 0, 0},
  {17, 0, 0, 0},
  {18, 0, 0, 0},
  {19, 0, 0, 0},
  {20, 0, 0, 0},
  {21, 0, 0, 0},
  {22, 0, 0, 0},
  {23, 0, 0, 0},
  {24, 0, 0, 0},
  {25, 0, 0, 0},
  {26, 0, 0, 0},
  {27, 0, 0, 0},
  {28, 0, 0, 0},
  {29, 0, 0, 0},
  {30, 0, 0, 0},
  {31, 0, 0, 0},
  {32, 0, 0, 0},
  {33, 0, 0, 0},
  {34, 0, 0, 0},
  {35, 0, 0, 0},
  {36, 0, 0, 0},
  {37, 0, 0, 0},
  {38, 0, 0, 0},
  {39, 0, 0, 0},
  {40, 0, 0, 0},
  {41, 0, 0, 0},
  {42, 0, 0, 0},
  {43, 0, 0, 0},
  {44, 0, 0, 0},
  {45, 0, 0, 0},
  {46, 0, 0, 0},
  {47, 0, 0, 0},
  {48, 0, 0, 0},
  {49, 0, 0, 0},
  {50, 0, 0, 0},
  {51, 0, 0, 0},
  {52, 0, 0, 0},
  {53, 0, 0, 0},
  {54, 0, 0, 0},
  {55, 0, 0, 0},
  {56, 0, 0, 0},
  {57, 0, 0, 0},
  {58, 0, 0, 0},
  {59, 0, 0, 0},
  {60, 0, 0, 0},
  {61, 0, 0, 0},
  {62, 0, 0, 0},
  {63, 0, 0, 0},
  {64, 0, 0, 0},
  {65, 0, 0, 0},
  {66, 0, 0, 0},
  {67, 0, 0, 0},
  {68, 0, 0, 0},
  {69, 0, 0, 0},
  {70, 0, 0, 0},
  {71, 0, 0, 0},
  {72, 0, 0, 0},
  {73, 0, 0, 0},
  {74, 0, 0, 0},
  {75, 0, 0, 0},
  {76, 0, 0, 0},
  {77, 0, 0, 0},
  {78, 0, 0, 0},
  {79, 0, 0, 0},
  {80, 0, 0, 0},
  {81, 0, 0, 0},
  {82, 0, 0, 0},
  {83, 0, 0, 0},
  {84, 0, 0, 0},
  {85, 0, 0, 0},
  {86, 0, 0, 0},
  {87, 0, 0, 0},
  {88, 0, 0, 0},
  {89, 0, 0, 0},
  {90, 0, 0, 0},
  {91, 0, 0, 0},
  {92, 0, 0, 0},
  {93, 0, 0, 0},
  {94, 0, 0, 0},
  {95, 0, 0, 0},
  {96, 0, 0, 0},
  {97, 0, 0, 0},
  {98, 0, 0, 0},
  {99, 0, 0, 0},
  {100, 0, 0, 0},
  {101, 0, 0, 0},
  {102, 0, 0, 0},
  {103, 0, 0, 0},
  {104, 0, 0, 0},
  {105, 0, 0, 0},
  {106, 0, 0, 0},
  {107, 0, 0, 0},
  {108, 0, 0, 0},
  {109, 0, 0, 0},
  {110, 0, 0, 0},
  {111, 0, 0, 0},
  {112, 0, 0, 0},
  {113, 0, 0, 0},
  {114, 0, 0, 0},
  {115, 0, 0, 0},
  {116, 0, 0, 0},
  {117, 0, 0, 0},
  {118, 0, 0, 0},
  {119, 0, 0, 0},
  {120, 0, 0, 0},
  {121, 0, 0, 0},
  {122, 0, 0, 0},
  {123, 0, 0, 0},
  {124, 0, 0, 0},
  {125, 0, 0, 0},
  {126, 0, 0, 0},
  {127, 0, 0, 0},
  {226, 130, 172, 0},
  {239, 191, 189, 0},
  {226, 128, 154, 0},
  {239, 191, 189, 0},
  {226, 128, 158, 0},
  {226, 128, 166, 0},
  {226, 128, 160, 0},
  {226, 128, 161, 0},
  {239, 191, 189, 0},
  {226, 128, 176, 0},
  {197, 160, 0, 0},
  {226, 128, 185, 0},
  {197, 154, 0, 0},
  {197, 164, 0, 0},
  {197, 189, 0, 0},
  {197, 185, 0, 0},
  {239, 191, 189, 0},
  {226, 128, 152, 0},
  {226, 128, 153, 0},
  {226, 128, 156, 0},
  {226, 128, 157, 0},
  {226, 128, 162, 0},
  {226, 128, 147, 0},
  {226, 128, 148, 0},
  {239, 191, 189, 0},
  {226, 132, 162, 0},
  {197, 161, 0, 0},
  {226, 128, 186, 0},
  {197, 155, 0, 0},
  {197, 165, 0, 0},
  {197, 190, 0, 0},
  {197, 186, 0, 0},
  {194, 160, 0, 0},
  {203, 135, 0, 0},
  {203, 152, 0, 0},
  {197, 129, 0, 0},
  {194, 164, 0, 0},
  {196, 132, 0, 0},
  {194, 166, 0, 0},
  {194, 167, 0, 0},
  {194, 168, 0, 0},
  {194, 169, 0, 0},
  {197, 158, 0, 0},
  {194, 171, 0, 0},
  {194, 172, 0, 0},
  {194, 173, 0, 0},
  {194, 174, 0, 0},
  {197, 187, 0, 0},
  {194, 176, 0, 0},
  {194, 177, 0, 0},
  {203, 155, 0, 0},
  {197, 130, 0, 0},
  {194, 180, 0, 0},
  {194, 181, 0, 0},
  {194, 182, 0, 0},
  {194, 183, 0, 0},
  {194, 184, 0, 0},
  {196, 133, 0, 0},
  {197, 159, 0, 0},
  {194, 187, 0, 0},
  {196, 189, 0, 0},
  {203, 157, 0, 0},
  {196, 190, 0, 0},
  {197, 188, 0, 0},
  {197, 148, 0, 0},
  {195, 129, 0, 0},
  {195, 130, 0, 0},
  {196, 130, 0, 0},
  {195, 132, 0, 0},
  {196, 185, 0, 0},
  {196, 134, 0, 0},
  {195, 135, 0, 0},
  {196, 140, 0, 0},
  {195, 137, 0, 0},
  {196, 152, 0, 0},
  {195, 139, 0, 0},
  {196, 154, 0, 0},
  {195, 141, 0, 0},
  {195, 142, 0, 0},
  {196, 142, 0, 0},
  {196, 144, 0, 0},
  {197, 131, 0, 0},
  {197, 135, 0, 0},
  {195, 147, 0, 0},
  {195, 148, 0, 0},
  {197, 144, 0, 0},
  {195, 150, 0, 0},
  {195, 151, 0, 0},
  {197, 152, 0, 0},
  {197, 174, 0, 0},
  {195, 154, 0, 0},
  {197, 176, 0, 0},
  {195, 156, 0, 0},
  {195, 157, 0, 0},
  {197, 162, 0, 0},
  {195, 159, 0, 0},
  {197, 149, 0, 0},
  {195, 161, 0, 0},
  {195, 162, 0, 0},
  {196, 131, 0, 0},
  {195, 164, 0, 0},
  {196, 186, 0, 0},
  {196, 135, 0, 0},
  {195, 167, 0, 0},
  {196, 141, 0, 0},
  {195, 169, 0, 0},
  {196, 153, 0, 0},
  {195, 171, 0, 0},
  {196, 155, 0, 0},
  {195, 173, 0, 0},
  {195, 174, 0, 0},
  {196, 143, 0, 0},
  {196, 145, 0, 0},
  {197, 132, 0, 0},
  {197, 136, 0, 0},
  {195, 179, 0, 0},
  {195, 180, 0, 0},
  {197, 145, 0, 0},
  {195, 182, 0, 0},
  {195, 183, 0, 0},
  {197, 153, 0, 0},
  {197, 175, 0, 0},
  {195, 186, 0, 0},
  {197, 177, 0, 0},
  {195, 188, 0, 0},
  {195, 189, 0, 0},
  {197, 163, 0, 0},
  {203, 153, 0, 0},
};


const char win1251_to_utf8[][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {2, 0, 0, 0},
  {3, 0, 0, 0},
  {4, 0, 0, 0},
  {5, 0, 0, 0},
  {6, 0, 0, 0},
  {7, 0, 0, 0},
  {8, 0, 0, 0},
  {9, 0, 0, 0},
  {10, 0, 0, 0},
  {11, 0, 0, 0},
  {12, 0, 0, 0},
  {13, 0, 0, 0},
  {14, 0, 0, 0},
  {15, 0, 0, 0},
  {16, 0, 0, 0},
  {17, 0, 0, 0},
  {18, 0, 0, 0},
  {19, 0, 0, 0},
  {20, 0, 0, 0},
  {21, 0, 0, 0},
  {22, 0, 0, 0},
  {23, 0, 0, 0},
  {24, 0, 0, 0},
  {25, 0, 0, 0},
  {26, 0, 0, 0},
  {27, 0, 0, 0},
  {28, 0, 0, 0},
  {29, 0, 0, 0},
  {30, 0, 0, 0},
  {31, 0, 0, 0},
  {32, 0, 0, 0},
  {33, 0, 0, 0},
  {34, 0, 0, 0},
  {35, 0, 0, 0},
  {36, 0, 0, 0},
  {37, 0, 0, 0},
  {38, 0, 0, 0},
  {39, 0, 0, 0},
  {40, 0, 0, 0},
  {41, 0, 0, 0},
  {42, 0, 0, 0},
  {43, 0, 0, 0},
  {44, 0, 0, 0},
  {45, 0, 0, 0},
  {46, 0, 0, 0},
  {47, 0, 0, 0},
  {48, 0, 0, 0},
  {49, 0, 0, 0},
  {50, 0, 0, 0},
  {51, 0, 0, 0},
  {52, 0, 0, 0},
  {53, 0, 0, 0},
  {54, 0, 0, 0},
  {55, 0, 0, 0},
  {56, 0, 0, 0},
  {57, 0, 0, 0},
  {58, 0, 0, 0},
  {59, 0, 0, 0},
  {60, 0, 0, 0},
  {61, 0, 0, 0},
  {62, 0, 0, 0},
  {63, 0, 0, 0},
  {64, 0, 0, 0},
  {65, 0, 0, 0},
  {66, 0, 0, 0},
  {67, 0, 0, 0},
  {68, 0, 0, 0},
  {69, 0, 0, 0},
  {70, 0, 0, 0},
  {71, 0, 0, 0},
  {72, 0, 0, 0},
  {73, 0, 0, 0},
  {74, 0, 0, 0},
  {75, 0, 0, 0},
  {76, 0, 0, 0},
  {77, 0, 0, 0},
  {78, 0, 0, 0},
  {79, 0, 0, 0},
  {80, 0, 0, 0},
  {81, 0, 0, 0},
  {82, 0, 0, 0},
  {83, 0, 0, 0},
  {84, 0, 0, 0},
  {85, 0, 0, 0},
  {86, 0, 0, 0},
  {87, 0, 0, 0},
  {88, 0, 0, 0},
  {89, 0, 0, 0},
  {90, 0, 0, 0},
  {91, 0, 0, 0},
  {92, 0, 0, 0},
  {93, 0, 0, 0},
  {94, 0, 0, 0},
  {95, 0, 0, 0},
  {96, 0, 0, 0},
  {97, 0, 0, 0},
  {98, 0, 0, 0},
  {99, 0, 0, 0},
  {100, 0, 0, 0},
  {101, 0, 0, 0},
  {102, 0, 0, 0},
  {103, 0, 0, 0},
  {104, 0, 0, 0},
  {105, 0, 0, 0},
  {106, 0, 0, 0},
  {107, 0, 0, 0},
  {108, 0, 0, 0},
  {109, 0, 0, 0},
  {110, 0, 0, 0},
  {111, 0, 0, 0},
  {112, 0, 0, 0},
  {113, 0, 0, 0},
  {114, 0, 0, 0},
  {115, 0, 0, 0},
  {116, 0, 0, 0},
  {117, 0, 0, 0},
  {118, 0, 0, 0},
  {119, 0, 0, 0},
  {120, 0, 0, 0},
  {121, 0, 0, 0},
  {122, 0, 0, 0},
  {123, 0, 0, 0},
  {124, 0, 0, 0},
  {125, 0, 0, 0},
  {126, 0, 0, 0},
  {127, 0, 0, 0},
  {208, 130, 0, 0},
  {208, 131, 0, 0},
  {226, 128, 154, 0},
  {209, 147, 0, 0},
  {226, 128, 158, 0},
  {226, 128, 166, 0},
  {226, 128, 160, 0},
  {226, 128, 161, 0},
  {226, 130, 172, 0},
  {226, 128, 176, 0},
  {208, 137, 0, 0},
  {226, 128, 185, 0},
  {208, 138, 0, 0},
  {208, 140, 0, 0},
  {208, 139, 0, 0},
  {208, 143, 0, 0},
  {209, 146, 0, 0},
  {226, 128, 152, 0},
  {226, 128, 153, 0},
  {226, 128, 156, 0},
  {226, 128, 157, 0},
  {226, 128, 162, 0},
  {226, 128, 147, 0},
  {226, 128, 148, 0},
  {239, 191, 189, 0},
  {226, 132, 162, 0},
  {209, 153, 0, 0},
  {226, 128, 186, 0},
  {209, 154, 0, 0},
  {209, 156, 0, 0},
  {209, 155, 0, 0},
  {209, 159, 0, 0},
  {194, 160, 0, 0},
  {208, 142, 0, 0},
  {209, 158, 0, 0},
  {208, 136, 0, 0},
  {194, 164, 0, 0},
  {210, 144, 0, 0},
  {194, 166, 0, 0},
  {194, 167, 0, 0},
  {208, 129, 0, 0},
  {194, 169, 0, 0},
  {208, 132, 0, 0},
  {194, 171, 0, 0},
  {194, 172, 0, 0},
  {194, 173, 0, 0},
  {194, 174, 0, 0},
  {208, 135, 0, 0},
  {194, 176, 0, 0},
  {194, 177, 0, 0},
  {208, 134, 0, 0},
  {209, 150, 0, 0},
  {210, 145, 0, 0},
  {194, 181, 0, 0},
  {194, 182, 0, 0},
  {194, 183, 0, 0},
  {209, 145, 0, 0},
  {226, 132, 150, 0},
  {209, 148, 0, 0},
  {194, 187, 0, 0},
  {209, 152, 0, 0},
  {208, 133, 0, 0},
  {209, 149, 0, 0},
  {209, 151, 0, 0},
  {208, 144, 0, 0},
  {208, 145, 0, 0},
  {208, 146, 0, 0},
  {208, 147, 0, 0},
  {208, 148, 0, 0},
  {208, 149, 0, 0},
  {208, 150, 0, 0},
  {208, 151, 0, 0},
  {208, 152, 0, 0},
  {208, 153, 0, 0},
  {208, 154, 0, 0},
  {208, 155, 0, 0},
  {208, 156, 0, 0},
  {208, 157, 0, 0},
  {208, 158, 0, 0},
  {208, 159, 0, 0},
  {208, 160, 0, 0},
  {208, 161, 0, 0},
  {208, 162, 0, 0},
  {208, 163, 0, 0},
  {208, 164, 0, 0},
  {208, 165, 0, 0},
  {208, 166, 0, 0},
  {208, 167, 0, 0},
  {208, 168, 0, 0},
  {208, 169, 0, 0},
  {208, 170, 0, 0},
  {208, 171, 0, 0},
  {208, 172, 0, 0},
  {208, 173, 0, 0},
  {208, 174, 0, 0},
  {208, 175, 0, 0},
  {208, 176, 0, 0},
  {208, 177, 0, 0},
  {208, 178, 0, 0},
  {208, 179, 0, 0},
  {208, 180, 0, 0},
  {208, 181, 0, 0},
  {208, 182, 0, 0},
  {208, 183, 0, 0},
  {208, 184, 0, 0},
  {208, 185, 0, 0},
  {208, 186, 0, 0},
  {208, 187, 0, 0},
  {208, 188, 0, 0},
  {208, 189, 0, 0},
  {208, 190, 0, 0},
  {208, 191, 0, 0},
  {209, 128, 0, 0},
  {209, 129, 0, 0},
  {209, 130, 0, 0},
  {209, 131, 0, 0},
  {209, 132, 0, 0},
  {209, 133, 0, 0},
  {209, 134, 0, 0},
  {209, 135, 0, 0},
  {209, 136, 0, 0},
  {209, 137, 0, 0},
  {209, 138, 0, 0},
  {209, 139, 0, 0},
  {209, 140, 0, 0},
  {209, 141, 0, 0},
  {209, 142, 0, 0},
  {209, 143, 0, 0},
};

const char win1252_to_utf8[][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {2, 0, 0, 0},
  {3, 0, 0, 0},
  {4, 0, 0, 0},
  {5, 0, 0, 0},
  {6, 0, 0, 0},
  {7, 0, 0, 0},
  {8, 0, 0, 0},
  {9, 0, 0, 0},
  {10, 0, 0, 0},
  {11, 0, 0, 0},
  {12, 0, 0, 0},
  {13, 0, 0, 0},
  {14, 0, 0, 0},
  {15, 0, 0, 0},
  {16, 0, 0, 0},
  {17, 0, 0, 0},
  {18, 0, 0, 0},
  {19, 0, 0, 0},
  {20, 0, 0, 0},
  {21, 0, 0, 0},
  {22, 0, 0, 0},
  {23, 0, 0, 0},
  {24, 0, 0, 0},
  {25, 0, 0, 0},
  {26, 0, 0, 0},
  {27, 0, 0, 0},
  {28, 0, 0, 0},
  {29, 0, 0, 0},
  {30, 0, 0, 0},
  {31, 0, 0, 0},
  {32, 0, 0, 0},
  {33, 0, 0, 0},
  {34, 0, 0, 0},
  {35, 0, 0, 0},
  {36, 0, 0, 0},
  {37, 0, 0, 0},
  {38, 0, 0, 0},
  {39, 0, 0, 0},
  {40, 0, 0, 0},
  {41, 0, 0, 0},
  {42, 0, 0, 0},
  {43, 0, 0, 0},
  {44, 0, 0, 0},
  {45, 0, 0, 0},
  {46, 0, 0, 0},
  {47, 0, 0, 0},
  {48, 0, 0, 0},
  {49, 0, 0, 0},
  {50, 0, 0, 0},
  {51, 0, 0, 0},
  {52, 0, 0, 0},
  {53, 0, 0, 0},
  {54, 0, 0, 0},
  {55, 0, 0, 0},
  {56, 0, 0, 0},
  {57, 0, 0, 0},
  {58, 0, 0, 0},
  {59, 0, 0, 0},
  {60, 0, 0, 0},
  {61, 0, 0, 0},
  {62, 0, 0, 0},
  {63, 0, 0, 0},
  {64, 0, 0, 0},
  {65, 0, 0, 0},
  {66, 0, 0, 0},
  {67, 0, 0, 0},
  {68, 0, 0, 0},
  {69, 0, 0, 0},
  {70, 0, 0, 0},
  {71, 0, 0, 0},
  {72, 0, 0, 0},
  {73, 0, 0, 0},
  {74, 0, 0, 0},
  {75, 0, 0, 0},
  {76, 0, 0, 0},
  {77, 0, 0, 0},
  {78, 0, 0, 0},
  {79, 0, 0, 0},
  {80, 0, 0, 0},
  {81, 0, 0, 0},
  {82, 0, 0, 0},
  {83, 0, 0, 0},
  {84, 0, 0, 0},
  {85, 0, 0, 0},
  {86, 0, 0, 0},
  {87, 0, 0, 0},
  {88, 0, 0, 0},
  {89, 0, 0, 0},
  {90, 0, 0, 0},
  {91, 0, 0, 0},
  {92, 0, 0, 0},
  {93, 0, 0, 0},
  {94, 0, 0, 0},
  {95, 0, 0, 0},
  {96, 0, 0, 0},
  {97, 0, 0, 0},
  {98, 0, 0, 0},
  {99, 0, 0, 0},
  {100, 0, 0, 0},
  {101, 0, 0, 0},
  {102, 0, 0, 0},
  {103, 0, 0, 0},
  {104, 0, 0, 0},
  {105, 0, 0, 0},
  {106, 0, 0, 0},
  {107, 0, 0, 0},
  {108, 0, 0, 0},
  {109, 0, 0, 0},
  {110, 0, 0, 0},
  {111, 0, 0, 0},
  {112, 0, 0, 0},
  {113, 0, 0, 0},
  {114, 0, 0, 0},
  {115, 0, 0, 0},
  {116, 0, 0, 0},
  {117, 0, 0, 0},
  {118, 0, 0, 0},
  {119, 0, 0, 0},
  {120, 0, 0, 0},
  {121, 0, 0, 0},
  {122, 0, 0, 0},
  {123, 0, 0, 0},
  {124, 0, 0, 0},
  {125, 0, 0, 0},
  {126, 0, 0, 0},
  {127, 0, 0, 0},
  {226, 130, 172, 0},
  {239, 191, 189, 0},
  {226, 128, 154, 0},
  {198, 146, 0, 0},
  {226, 128, 158, 0},
  {226, 128, 166, 0},
  {226, 128, 160, 0},
  {226, 128, 161, 0},
  {203, 134, 0, 0},
  {226, 128, 176, 0},
  {197, 160, 0, 0},
  {226, 128, 185, 0},
  {197, 146, 0, 0},
  {239, 191, 189, 0},
  {197, 189, 0, 0},
  {239, 191, 189, 0},
  {239, 191, 189, 0},
  {226, 128, 152, 0},
  {226, 128, 153, 0},
  {226, 128, 156, 0},
  {226, 128, 157, 0},
  {226, 128, 162, 0},
  {226, 128, 147, 0},
  {226, 128, 148, 0},
  {203, 156, 0, 0},
  {226, 132, 162, 0},
  {197, 161, 0, 0},
  {226, 128, 186, 0},
  {197, 147, 0, 0},
  {239, 191, 189, 0},
  {197, 190, 0, 0},
  {197, 184, 0, 0},
  {194, 160, 0, 0},
  {194, 161, 0, 0},
  {194, 162, 0, 0},
  {194, 163, 0, 0},
  {194, 164, 0, 0},
  {194, 165, 0, 0},
  {194, 166, 0, 0},
  {194, 167, 0, 0},
  {194, 168, 0, 0},
  {194, 169, 0, 0},
  {194, 170, 0, 0},
  {194, 171, 0, 0},
  {194, 172, 0, 0},
  {194, 173, 0, 0},
  {194, 174, 0, 0},
  {194, 175, 0, 0},
  {194, 176, 0, 0},
  {194, 177, 0, 0},
  {194, 178, 0, 0},
  {194, 179, 0, 0},
  {194, 180, 0, 0},
  {194, 181, 0, 0},
  {194, 182, 0, 0},
  {194, 183, 0, 0},
  {194, 184, 0, 0},
  {194, 185, 0, 0},
  {194, 186, 0, 0},
  {194, 187, 0, 0},
  {194, 188, 0, 0},
  {194, 189, 0, 0},
  {194, 190, 0, 0},
  {194, 191, 0, 0},
  {195, 128, 0, 0},
  {195, 129, 0, 0},
  {195, 130, 0, 0},
  {195, 131, 0, 0},
  {195, 132, 0, 0},
  {195, 133, 0, 0},
  {195, 134, 0, 0},
  {195, 135, 0, 0},
  {195, 136, 0, 0},
  {195, 137, 0, 0},
  {195, 138, 0, 0},
  {195, 139, 0, 0},
  {195, 140, 0, 0},
  {195, 141, 0, 0},
  {195, 142, 0, 0},
  {195, 143, 0, 0},
  {195, 144, 0, 0},
  {195, 145, 0, 0},
  {195, 146, 0, 0},
  {195, 147, 0, 0},
  {195, 148, 0, 0},
  {195, 149, 0, 0},
  {195, 150, 0, 0},
  {195, 151, 0, 0},
  {195, 152, 0, 0},
  {195, 153, 0, 0},
  {195, 154, 0, 0},
  {195, 155, 0, 0},
  {195, 156, 0, 0},
  {195, 157, 0, 0},
  {195, 158, 0, 0},
  {195, 159, 0, 0},
  {195, 160, 0, 0},
  {195, 161, 0, 0},
  {195, 162, 0, 0},
  {195, 163, 0, 0},
  {195, 164, 0, 0},
  {195, 165, 0, 0},
  {195, 166, 0, 0},
  {195, 167, 0, 0},
  {195, 168, 0, 0},
  {195, 169, 0, 0},
  {195, 170, 0, 0},
  {195, 171, 0, 0},
  {195, 172, 0, 0},
  {195, 173, 0, 0},
  {195, 174, 0, 0},
  {195, 175, 0, 0},
  {195, 176, 0, 0},
  {195, 177, 0, 0},
  {195, 178, 0, 0},
  {195, 179, 0, 0},
  {195, 180, 0, 0},
  {195, 181, 0, 0},
  {195, 182, 0, 0},
  {195, 183, 0, 0},
  {195, 184, 0, 0},
  {195, 185, 0, 0},
  {195, 186, 0, 0},
  {195, 187, 0, 0},
  {195, 188, 0, 0},
  {195, 189, 0, 0},
  {195, 190, 0, 0},
  {195, 191, 0, 0},
};


const char win1254_to_utf8[][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {2, 0, 0, 0},
  {3, 0, 0, 0},
  {4, 0, 0, 0},
  {5, 0, 0, 0},
  {6, 0, 0, 0},
  {7, 0, 0, 0},
  {8, 0, 0, 0},
  {9, 0, 0, 0},
  {10, 0, 0, 0},
  {11, 0, 0, 0},
  {12, 0, 0, 0},
  {13, 0, 0, 0},
  {14, 0, 0, 0},
  {15, 0, 0, 0},
  {16, 0, 0, 0},
  {17, 0, 0, 0},
  {18, 0, 0, 0},
  {19, 0, 0, 0},
  {20, 0, 0, 0},
  {21, 0, 0, 0},
  {22, 0, 0, 0},
  {23, 0, 0, 0},
  {24, 0, 0, 0},
  {25, 0, 0, 0},
  {26, 0, 0, 0},
  {27, 0, 0, 0},
  {28, 0, 0, 0},
  {29, 0, 0, 0},
  {30, 0, 0, 0},
  {31, 0, 0, 0},
  {32, 0, 0, 0},
  {33, 0, 0, 0},
  {34, 0, 0, 0},
  {35, 0, 0, 0},
  {36, 0, 0, 0},
  {37, 0, 0, 0},
  {38, 0, 0, 0},
  {39, 0, 0, 0},
  {40, 0, 0, 0},
  {41, 0, 0, 0},
  {42, 0, 0, 0},
  {43, 0, 0, 0},
  {44, 0, 0, 0},
  {45, 0, 0, 0},
  {46, 0, 0, 0},
  {47, 0, 0, 0},
  {48, 0, 0, 0},
  {49, 0, 0, 0},
  {50, 0, 0, 0},
  {51, 0, 0, 0},
  {52, 0, 0, 0},
  {53, 0, 0, 0},
  {54, 0, 0, 0},
  {55, 0, 0, 0},
  {56, 0, 0, 0},
  {57, 0, 0, 0},
  {58, 0, 0, 0},
  {59, 0, 0, 0},
  {60, 0, 0, 0},
  {61, 0, 0, 0},
  {62, 0, 0, 0},
  {63, 0, 0, 0},
  {64, 0, 0, 0},
  {65, 0, 0, 0},
  {66, 0, 0, 0},
  {67, 0, 0, 0},
  {68, 0, 0, 0},
  {69, 0, 0, 0},
  {70, 0, 0, 0},
  {71, 0, 0, 0},
  {72, 0, 0, 0},
  {73, 0, 0, 0},
  {74, 0, 0, 0},
  {75, 0, 0, 0},
  {76, 0, 0, 0},
  {77, 0, 0, 0},
  {78, 0, 0, 0},
  {79, 0, 0, 0},
  {80, 0, 0, 0},
  {81, 0, 0, 0},
  {82, 0, 0, 0},
  {83, 0, 0, 0},
  {84, 0, 0, 0},
  {85, 0, 0, 0},
  {86, 0, 0, 0},
  {87, 0, 0, 0},
  {88, 0, 0, 0},
  {89, 0, 0, 0},
  {90, 0, 0, 0},
  {91, 0, 0, 0},
  {92, 0, 0, 0},
  {93, 0, 0, 0},
  {94, 0, 0, 0},
  {95, 0, 0, 0},
  {96, 0, 0, 0},
  {97, 0, 0, 0},
  {98, 0, 0, 0},
  {99, 0, 0, 0},
  {100, 0, 0, 0},
  {101, 0, 0, 0},
  {102, 0, 0, 0},
  {103, 0, 0, 0},
  {104, 0, 0, 0},
  {105, 0, 0, 0},
  {106, 0, 0, 0},
  {107, 0, 0, 0},
  {108, 0, 0, 0},
  {109, 0, 0, 0},
  {110, 0, 0, 0},
  {111, 0, 0, 0},
  {112, 0, 0, 0},
  {113, 0, 0, 0},
  {114, 0, 0, 0},
  {115, 0, 0, 0},
  {116, 0, 0, 0},
  {117, 0, 0, 0},
  {118, 0, 0, 0},
  {119, 0, 0, 0},
  {120, 0, 0, 0},
  {121, 0, 0, 0},
  {122, 0, 0, 0},
  {123, 0, 0, 0},
  {124, 0, 0, 0},
  {125, 0, 0, 0},
  {126, 0, 0, 0},
  {127, 0, 0, 0},
  {226, 130, 172, 0},
  {239, 191, 189, 0},
  {226, 128, 154, 0},
  {198, 146, 0, 0},
  {226, 128, 158, 0},
  {226, 128, 166, 0},
  {226, 128, 160, 0},
  {226, 128, 161, 0},
  {203, 134, 0, 0},
  {226, 128, 176, 0},
  {197, 160, 0, 0},
  {226, 128, 185, 0},
  {197, 146, 0, 0},
  {239, 191, 189, 0},
  {239, 191, 189, 0},
  {239, 191, 189, 0},
  {239, 191, 189, 0},
  {226, 128, 152, 0},
  {226, 128, 153, 0},
  {226, 128, 156, 0},
  {226, 128, 157, 0},
  {226, 128, 162, 0},
  {226, 128, 147, 0},
  {226, 128, 148, 0},
  {203, 156, 0, 0},
  {226, 132, 162, 0},
  {197, 161, 0, 0},
  {226, 128, 186, 0},
  {197, 147, 0, 0},
  {239, 191, 189, 0},
  {239, 191, 189, 0},
  {197, 184, 0, 0},
  {194, 160, 0, 0},
  {194, 161, 0, 0},
  {194, 162, 0, 0},
  {194, 163, 0, 0},
  {194, 164, 0, 0},
  {194, 165, 0, 0},
  {194, 166, 0, 0},
  {194, 167, 0, 0},
  {194, 168, 0, 0},
  {194, 169, 0, 0},
  {194, 170, 0, 0},
  {194, 171, 0, 0},
  {194, 172, 0, 0},
  {194, 173, 0, 0},
  {194, 174, 0, 0},
  {194, 175, 0, 0},
  {194, 176, 0, 0},
  {194, 177, 0, 0},
  {194, 178, 0, 0},
  {194, 179, 0, 0},
  {194, 180, 0, 0},
  {194, 181, 0, 0},
  {194, 182, 0, 0},
  {194, 183, 0, 0},
  {194, 184, 0, 0},
  {194, 185, 0, 0},
  {194, 186, 0, 0},
  {194, 187, 0, 0},
  {194, 188, 0, 0},
  {194, 189, 0, 0},
  {194, 190, 0, 0},
  {194, 191, 0, 0},
  {195, 128, 0, 0},
  {195, 129, 0, 0},
  {195, 130, 0, 0},
  {195, 131, 0, 0},
  {195, 132, 0, 0},
  {195, 133, 0, 0},
  {195, 134, 0, 0},
  {195, 135, 0, 0},
  {195, 136, 0, 0},
  {195, 137, 0, 0},
  {195, 138, 0, 0},
  {195, 139, 0, 0},
  {195, 140, 0, 0},
  {195, 141, 0, 0},
  {195, 142, 0, 0},
  {195, 143, 0, 0},
  {196, 158, 0, 0},
  {195, 145, 0, 0},
  {195, 146, 0, 0},
  {195, 147, 0, 0},
  {195, 148, 0, 0},
  {195, 149, 0, 0},
  {195, 150, 0, 0},
  {195, 151, 0, 0},
  {195, 152, 0, 0},
  {195, 153, 0, 0},
  {195, 154, 0, 0},
  {195, 155, 0, 0},
  {195, 156, 0, 0},
  {196, 176, 0, 0},
  {197, 158, 0, 0},
  {195, 159, 0, 0},
  {195, 160, 0, 0},
  {195, 161, 0, 0},
  {195, 162, 0, 0},
  {195, 163, 0, 0},
  {195, 164, 0, 0},
  {195, 165, 0, 0},
  {195, 166, 0, 0},
  {195, 167, 0, 0},
  {195, 168, 0, 0},
  {195, 169, 0, 0},
  {195, 170, 0, 0},
  {195, 171, 0, 0},
  {195, 172, 0, 0},
  {195, 173, 0, 0},
  {195, 174, 0, 0},
  {195, 175, 0, 0},
  {196, 159, 0, 0},
  {195, 177, 0, 0},
  {195, 178, 0, 0},
  {195, 179, 0, 0},
  {195, 180, 0, 0},
  {195, 181, 0, 0},
  {195, 182, 0, 0},
  {195, 183, 0, 0},
  {195, 184, 0, 0},
  {195, 185, 0, 0},
  {195, 186, 0, 0},
  {195, 187, 0, 0},
  {195, 188, 0, 0},
  {196, 177, 0, 0},
  {197, 159, 0, 0},
  {195, 191, 0, 0},
};


const char win1257_to_utf8[][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {2, 0, 0, 0},
  {3, 0, 0, 0},
  {4, 0, 0, 0},
  {5, 0, 0, 0},
  {6, 0, 0, 0},
  {7, 0, 0, 0},
  {8, 0, 0, 0},
  {9, 0, 0, 0},
  {10, 0, 0, 0},
  {11, 0, 0, 0},
  {12, 0, 0, 0},
  {13, 0, 0, 0},
  {14, 0, 0, 0},
  {15, 0, 0, 0},
  {16, 0, 0, 0},
  {17, 0, 0, 0},
  {18, 0, 0, 0},
  {19, 0, 0, 0},
  {20, 0, 0, 0},
  {21, 0, 0, 0},
  {22, 0, 0, 0},
  {23, 0, 0, 0},
  {24, 0, 0, 0},
  {25, 0, 0, 0},
  {26, 0, 0, 0},
  {27, 0, 0, 0},
  {28, 0, 0, 0},
  {29, 0, 0, 0},
  {30, 0, 0, 0},
  {31, 0, 0, 0},
  {32, 0, 0, 0},
  {33, 0, 0, 0},
  {34, 0, 0, 0},
  {35, 0, 0, 0},
  {36, 0, 0, 0},
  {37, 0, 0, 0},
  {38, 0, 0, 0},
  {39, 0, 0, 0},
  {40, 0, 0, 0},
  {41, 0, 0, 0},
  {42, 0, 0, 0},
  {43, 0, 0, 0},
  {44, 0, 0, 0},
  {45, 0, 0, 0},
  {46, 0, 0, 0},
  {47, 0, 0, 0},
  {48, 0, 0, 0},
  {49, 0, 0, 0},
  {50, 0, 0, 0},
  {51, 0, 0, 0},
  {52, 0, 0, 0},
  {53, 0, 0, 0},
  {54, 0, 0, 0},
  {55, 0, 0, 0},
  {56, 0, 0, 0},
  {57, 0, 0, 0},
  {58, 0, 0, 0},
  {59, 0, 0, 0},
  {60, 0, 0, 0},
  {61, 0, 0, 0},
  {62, 0, 0, 0},
  {63, 0, 0, 0},
  {64, 0, 0, 0},
  {65, 0, 0, 0},
  {66, 0, 0, 0},
  {67, 0, 0, 0},
  {68, 0, 0, 0},
  {69, 0, 0, 0},
  {70, 0, 0, 0},
  {71, 0, 0, 0},
  {72, 0, 0, 0},
  {73, 0, 0, 0},
  {74, 0, 0, 0},
  {75, 0, 0, 0},
  {76, 0, 0, 0},
  {77, 0, 0, 0},
  {78, 0, 0, 0},
  {79, 0, 0, 0},
  {80, 0, 0, 0},
  {81, 0, 0, 0},
  {82, 0, 0, 0},
  {83, 0, 0, 0},
  {84, 0, 0, 0},
  {85, 0, 0, 0},
  {86, 0, 0, 0},
  {87, 0, 0, 0},
  {88, 0, 0, 0},
  {89, 0, 0, 0},
  {90, 0, 0, 0},
  {91, 0, 0, 0},
  {92, 0, 0, 0},
  {93, 0, 0, 0},
  {94, 0, 0, 0},
  {95, 0, 0, 0},
  {96, 0, 0, 0},
  {97, 0, 0, 0},
  {98, 0, 0, 0},
  {99, 0, 0, 0},
  {100, 0, 0, 0},
  {101, 0, 0, 0},
  {102, 0, 0, 0},
  {103, 0, 0, 0},
  {104, 0, 0, 0},
  {105, 0, 0, 0},
  {106, 0, 0, 0},
  {107, 0, 0, 0},
  {108, 0, 0, 0},
  {109, 0, 0, 0},
  {110, 0, 0, 0},
  {111, 0, 0, 0},
  {112, 0, 0, 0},
  {113, 0, 0, 0},
  {114, 0, 0, 0},
  {115, 0, 0, 0},
  {116, 0, 0, 0},
  {117, 0, 0, 0},
  {118, 0, 0, 0},
  {119, 0, 0, 0},
  {120, 0, 0, 0},
  {121, 0, 0, 0},
  {122, 0, 0, 0},
  {123, 0, 0, 0},
  {124, 0, 0, 0},
  {125, 0, 0, 0},
  {126, 0, 0, 0},
  {127, 0, 0, 0},
  {226, 130, 172, 0},
  {239, 191, 189, 0},
  {226, 128, 154, 0},
  {239, 191, 189, 0},
  {226, 128, 158, 0},
  {226, 128, 166, 0},
  {226, 128, 160, 0},
  {226, 128, 161, 0},
  {239, 191, 189, 0},
  {226, 128, 176, 0},
  {239, 191, 189, 0},
  {226, 128, 185, 0},
  {239, 191, 189, 0},
  {194, 168, 0, 0},
  {203, 135, 0, 0},
  {194, 184, 0, 0},
  {239, 191, 189, 0},
  {226, 128, 152, 0},
  {226, 128, 153, 0},
  {226, 128, 156, 0},
  {226, 128, 157, 0},
  {226, 128, 162, 0},
  {226, 128, 147, 0},
  {226, 128, 148, 0},
  {239, 191, 189, 0},
  {226, 132, 162, 0},
  {239, 191, 189, 0},
  {226, 128, 186, 0},
  {239, 191, 189, 0},
  {194, 175, 0, 0},
  {203, 155, 0, 0},
  {239, 191, 189, 0},
  {194, 160, 0, 0},
  {239, 191, 189, 0},
  {194, 162, 0, 0},
  {194, 163, 0, 0},
  {194, 164, 0, 0},
  {239, 191, 189, 0},
  {194, 166, 0, 0},
  {194, 167, 0, 0},
  {195, 152, 0, 0},
  {194, 169, 0, 0},
  {197, 150, 0, 0},
  {194, 171, 0, 0},
  {194, 172, 0, 0},
  {194, 173, 0, 0},
  {194, 174, 0, 0},
  {195, 134, 0, 0},
  {194, 176, 0, 0},
  {194, 177, 0, 0},
  {194, 178, 0, 0},
  {194, 179, 0, 0},
  {194, 180, 0, 0},
  {194, 181, 0, 0},
  {194, 182, 0, 0},
  {194, 183, 0, 0},
  {195, 184, 0, 0},
  {194, 185, 0, 0},
  {197, 151, 0, 0},
  {194, 187, 0, 0},
  {194, 188, 0, 0},
  {194, 189, 0, 0},
  {194, 190, 0, 0},
  {195, 166, 0, 0},
  {196, 132, 0, 0},
  {196, 174, 0, 0},
  {196, 128, 0, 0},
  {196, 134, 0, 0},
  {195, 132, 0, 0},
  {195, 133, 0, 0},
  {196, 152, 0, 0},
  {196, 146, 0, 0},
  {196, 140, 0, 0},
  {195, 137, 0, 0},
  {197, 185, 0, 0},
  {196, 150, 0, 0},
  {196, 162, 0, 0},
  {196, 182, 0, 0},
  {196, 170, 0, 0},
  {196, 187, 0, 0},
  {197, 160, 0, 0},
  {197, 131, 0, 0},
  {197, 133, 0, 0},
  {195, 147, 0, 0},
  {197, 140, 0, 0},
  {195, 149, 0, 0},
  {195, 150, 0, 0},
  {195, 151, 0, 0},
  {197, 178, 0, 0},
  {197, 129, 0, 0},
  {197, 154, 0, 0},
  {197, 170, 0, 0},
  {195, 156, 0, 0},
  {197, 187, 0, 0},
  {197, 189, 0, 0},
  {195, 159, 0, 0},
  {196, 133, 0, 0},
  {196, 175, 0, 0},
  {196, 129, 0, 0},
  {196, 135, 0, 0},
  {195, 164, 0, 0},
  {195, 165, 0, 0},
  {196, 153, 0, 0},
  {196, 147, 0, 0},
  {196, 141, 0, 0},
  {195, 169, 0, 0},
  {197, 186, 0, 0},
  {196, 151, 0, 0},
  {196, 163, 0, 0},
  {196, 183, 0, 0},
  {196, 171, 0, 0},
  {196, 188, 0, 0},
  {197, 161, 0, 0},
  {197, 132, 0, 0},
  {197, 134, 0, 0},
  {195, 179, 0, 0},
  {197, 141, 0, 0},
  {195, 181, 0, 0},
  {195, 182, 0, 0},
  {195, 183, 0, 0},
  {197, 179, 0, 0},
  {197, 130, 0, 0},
  {197, 155, 0, 0},
  {197, 171, 0, 0},
  {195, 188, 0, 0},
  {197, 188, 0, 0},
  {197, 190, 0, 0},
  {203, 153, 0, 0},
};


#endif