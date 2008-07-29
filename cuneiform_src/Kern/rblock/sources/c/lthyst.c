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



/****************************************************************************
 *                                                                          *
 *                   P A G E   L A Y O U T                                  *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              LTHYST.C - Working with hystogram                           *
 *                                                                          *
 ***************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "c_memory.h"
# include "layout.h"
# include "my_mem.h"

int  *pHystogram           = NULL;
int  *pHystVertHeightesSum = NULL;
int  *pHystHorzHeightesSum = NULL;
int  *pHystInt1            = NULL;
int  *pHystInt2            = NULL;
int  *pHystTops            = NULL;
int  *pHystBottoms         = NULL;
int  nHystColumns          = 0;
int  nHystColumnWidth      = 0;

BOOL HystogramAllocateBody (void)
{
    BLOCK *p;
    int nBlockWidth;
    int nBlockHeight;
    int nMaxValue;

    HystogramFreeData ();
    nMaxValue = 0;

    for (p = pBlocksList; p != NULL; p = p -> pNext)
    {
        nBlockWidth  = p -> Rect.xRight  - p -> Rect.xLeft + 1;
        nBlockHeight = p -> Rect.yBottom - p -> Rect.yTop  + 1;

        if (nBlockWidth > nMaxValue)
            nMaxValue = nBlockWidth;

        if (nBlockHeight > nMaxValue)
            nMaxValue = nBlockHeight;
    }

    if (nMaxValue == 0)
        return (FALSE);

    nMaxValue++;
    pHystogram = malloc ((nMaxValue + 1) * sizeof (int));//Andrey 05.03.2003: +1 �.�. � ���������� ����� �������������� ������ �� ������ ��������

    if (pHystogram == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 1");

    if (bOptionPointSizeAnalysis)
    {
        pHystVertHeightesSum = malloc (nMaxValue * sizeof (int));

        if (pHystVertHeightesSum == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 2");

        pHystHorzHeightesSum = malloc (nMaxValue * sizeof (int));

        if (pHystHorzHeightesSum == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 3");

        pHystInt1 = malloc (nMaxValue * sizeof (int));

        if (pHystInt1 == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 4");

        pHystInt2 = malloc (nMaxValue * sizeof (int));

        if (pHystInt2 == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 5");
    }

    if (bOptionSpecialHorizontalCutting)
    {
        pHystTops = malloc (nMaxValue * sizeof (int));

        if (pHystTops == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 6");

        pHystBottoms = malloc (nMaxValue * sizeof (int));

        if (pHystBottoms == NULL)
        ErrorNoEnoughMemory ("in LTHYST.C,HystogramAllocateBody,part 7");
    }

    return (TRUE);
}

void HystogramMakeIntegral (int *pInt, int *p, int nWidth)
{
    int nSum = 0;
    int i;

    for (i = 0; i < nWidth; i++)
    {
        nSum += p [i];
        pInt [i] = nSum;
    }
}

void HystogramFreeData (void)
{
    if (pHystogram != NULL)
    {
        free (pHystogram);
        pHystogram = NULL;
    }

    if (bOptionPointSizeAnalysis)
    {
        if (pHystVertHeightesSum != NULL)
        {
            free (pHystVertHeightesSum);
            pHystVertHeightesSum = NULL;
        }

        if (pHystHorzHeightesSum != NULL)
        {
            free (pHystHorzHeightesSum);
            pHystHorzHeightesSum = NULL;
        }

        if (pHystInt1 != NULL)
        {
            free (pHystInt1);
            pHystInt1 = NULL;
        }

        if (pHystInt2 != NULL)
        {
            free (pHystInt2);
            pHystInt2 = NULL;
        }
    }

    if (bOptionSpecialHorizontalCutting)
    {
        if (pHystTops != NULL)
        {
            free (pHystTops);
            pHystTops = NULL;
        }

        if (pHystBottoms != NULL)
        {
            free (pHystBottoms);
            pHystBottoms = NULL;
        }
    }

    nHystColumns         = 0;
    nHystColumnWidth     = 0;
}
