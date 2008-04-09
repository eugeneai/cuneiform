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

/*------------------------------------------------------------------------------------------------*/
/**
    \file   UN_Buff.CPP
    \brief  ���������� ������� ������ �� ������� ����������
    \author ��������� ��������
    \date   22.04.2005
*/
/*------------------------------------------------------------------------------------------------*/
/*  N-� �������� 22.04.2005:
    - ���������� � ��������� ����������, ������������� � ������ "UN_Buff.CPP" � 02.03.2001  */
/*------------------------------------------------------------------------------------------------*/
/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  03.02.01                                                    */
/*  ����       :  'UN_Buff.CPP'                                               */
/*  ���������� :  ������� ������ � �������.                                   */
/*  ���������� :  ����������� ������ � �������.                               */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
/*  ������������ ���  */
#include "UN_Buff.H"
/*----------    ���������� �������    ------------------------------------------------------------*/
void CleanLastDataPart (void *p_vB)
{
    UN_BUFF *pB = static_cast<UN_BUFF *>(p_vB);
    pB->SizeCurr += pB->SizePartTotal[pB->nPart - 1];
    pB->vCurr = pB->vPart[pB->nPart - 1];
    pB->vPart[pB->nPart - 1] = NULL;
    pB->TypePart[pB->nPart - 1] = 0;//==UN_DT_Unknown;
    pB->AimPart[pB->nPart] = 0;//==UN_DA_Unknown;
    pB->SizePartUnits[pB->nPart - 1] = 0;
    pB->nPartUnits[pB->nPart-1] = 0;
    pB->SizePartTotal[pB->nPart - 1] = 0;
    (pB->nPart)--;
}
/*------------------------------------------------------------------------------------------------*/
void EndLastDataPart (void *p_vB, const char Aim, const char Type, const int SizeU, const int nU)
{
    UN_BUFF *pB = static_cast<UN_BUFF *>(p_vB);
    pB->vPart[pB->nPart] = pB->vCurr;
    pB->TypePart[pB->nPart] = Type;
    pB->AimPart[pB->nPart] = Aim;
    pB->SizePartUnits[pB->nPart] = SizeU;
    pB->nPartUnits[pB->nPart] = nU;
    pB->SizePartTotal[pB->nPart] = SizeU * nU;
    (pB->nPart)++;
    pB->SizeCurr -= (SizeU * nU);
    char *p_cCurr = (static_cast<char *>(pB->vCurr)) + SizeU * nU;
    pB->vCurr = static_cast<void *>(p_cCurr);
}
/*------------------------------------------------------------------------------------------------*/
int FindSuchData (const void *p_vB, const int WhatData)
{
    const UN_BUFF *pB = static_cast<const UN_BUFF *>(p_vB);
    int Ind = -1;
    /*  ���������� ��� ������  */
    for (int i = 0;  i < pB->nPart;  i++)
    {
        if (pB->TypePart[i] != WhatData)
            continue;
        Ind = i;
        break;
    }
    return Ind;
}
/*------------------------------------------------------------------------------------------------*/
int FindSuchAimedData (const void *p_vB, const int WhatData, const int WhatAim)
{
    const UN_BUFF *pB = static_cast<const UN_BUFF *>(p_vB);
    int Ind = -1;
    /*  ���������� ��� ������  */
    for (int i = 0;  i < pB->nPart;  i++)
    {
        if (pB->TypePart[i] != WhatData)
            continue;
        if (pB->AimPart[i] != WhatAim)
            continue;
        Ind = i;
        break;
    }
    return Ind;
}
/*------------------------------------------------------------------------------------------------*/
int FindNextSuchData (const void *p_vB, const int WhatData, const int IndPrev)
{
    const UN_BUFF *pB = static_cast<const UN_BUFF *>(p_vB);
    int Ind = IndPrev;
    /*  ���������� ��� ������ ����� ��������  */
    for (int i = IndPrev + 1;  i < pB->nPart;  i++)
    {
        if (pB->TypePart[i] != WhatData)
            continue;
        Ind = i;
        break;
    }
    return Ind;
}
/*------------------------------------------------------------------------------------------------*/
