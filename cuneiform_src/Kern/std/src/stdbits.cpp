/*
 Copyright (c) 1993-2008, Cognitive Technologies
 All rights reserved.

 ����������� ��������� ��������������� � ������������� ��� � ���� ��������� ����,
 ��� � � �������� �����, � ����������� ��� ���, ��� ���������� ��������� �������:

 * ��� ��������� ��������������� ��������� ���� ������ ���������� ���������
 ���� ����������� �� ��������� �����, ���� ������ ������� � �����������
 ����� �� ��������.
 * ��� ��������� ��������������� ��������� ���� � ������������ �/��� �
 ������ ����������, ������������ ��� ���������������, ������ �����������
 ��������� ���� ���������� �� ��������� �����, ���� ������ ������� �
 ����������� ����� �� ��������.
 * �� �������� Cognitive Technologies, �� ����� �� ����������� �� �����
 ���� ������������ � �������� �������� ��������� �/��� �����������
 ���������, ���������� �� ���� ��, ��� ���������������� �����������
 ����������.

 ��� ��������� ������������� ����������� ��������� ���� �/��� ������� ������ "���
 ��� ����" ��� ������-���� ���� ��������, ���������� ���� ��� ���������������,
 ������� �������� ������������ �������� � ����������� ��� ���������� ����, �� ��
 ������������� ���. �� �������� ��������� ���� � �� ���� ������ ����, �������
 ����� �������� �/��� �������� �������������� ���������, �� � ���� ������ ��
 ��Ѩ� ���������������, ������� ����� �����, ���������, ����������� ���
 ������������� ������, ��������� � �������������� ��� ���������� ����������
 ������������� ������������� ��������� (������� ������ ������, ��� ������,
 ������� ���������, ��� ������ �/��� ������ �������, ���������� ��-�� ��������
 ������� ��� �/��� ������ ��������� �������� ��������� � ������� �����������,
 �� �� ������������� ����� ��������), �� �� ������������� ���, ���� ���� �����
 �������� ��� ������ ���� ���� �������� � ����������� ����� ������� � ������.

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

#include "internal.h"
#pragma hdrstop
#include "std.h"

/* This function transforms the black-white image into a sequence of intervals.
 Example: 0000000100000001 is transformed into 00000007 00010007 00010000. So, we have 0 blacks, 7 whites, 1 black, 7 whites and 1 black.

 Clearly, this function will not work properly if there is 64K (or more) of consecutive whites (or blacks).
 */

STD_FUNC(int) stdBits2Ints(Word8* pBits, int nByteWidth, Int32* pIntervals) {

    /* Here, pIntervals is a pointer to the interval buffer. It should have length (in bytes) == (nByteWidth*4)*4 */

    Int32* p = pIntervals;
    Word8 b = 0;

    *p = 0;

    bool c, current_color = 0;
    int length;

    while (nByteWidth) {
        nByteWidth--;

        length = 8;
        b = *pBits++;

        while (length > 0) {
            if (b > 127)
                c = 1;
            if (b < 128)
                c = 0;
            if (c == 0)
                *p += 0x1;
            if (c == 1 && current_color == 1)
                *p += 0x10000;
            if (c == 1 && current_color == 0)
                *++p = 0x10000;
            current_color = c;
            b = (b - 128 * c) * 2;
            length = length - 1;
        }

    };

    if (*p & 0xffff0000)
        p++;
    return p - pIntervals;
}
