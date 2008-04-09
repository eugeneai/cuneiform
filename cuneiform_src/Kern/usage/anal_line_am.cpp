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
    \file   Anal_Line_AM.CPP
    \brief  ���������� ������� ������������ ������� �����
    \author ��������� ��������
    \date   25.04.2005
*/
/*------------------------------------------------------------------------------------------------*/
/*  N-� �������� 25.04.2005:
    - ���������� � ��������� ����������, ������������� � ������ "Anal_Line_AM.CPP" � 16.04.2001  */
/*------------------------------------------------------------------------------------------------*/
/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  06.03.01                                                    */
/*  ����       :  'Anal_Line_AM.CPP'                                          */
/*  ���������� :  ���� ������ � ������� ������ �������.                       */
/*  ���������� :  ��������� ��������� ����� ��� �������� ������������.        */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <windows.h>
/*  ������������ ���  */
#include "LineDesc.H"
/*  ������������ �����  */
#include "skew1024.h"
/*  ������������ ���  */
#include "MarkDataDefs.H"
#include "UN_Buff.H"
#include "UN_Err.H"
/*----------    ���������� ���������    ----------------------------------------------------------*/
/*+ (MarkLineCrimSkew) +*/
/** ����������� ����������� ������� ���� */
static const int MIN_DELTA_SKEW_NORM = 31;// 05.04.01 � ���� 27;//23;
/** ������������ ����������� ������� ���� */
static const int MAX_DELTA_SKEW_NORM = 50;
/** ����������� ����� ������� ����� */
static const int MIN_LEN_LONG_LINE = 350;
//SkewWidForAnal = 9; ��� ���������, ����� �� ������������
/*----------    ��������� �������    -------------------------------------------------------------*/
/**
    \brief ������� ��������� �����, ������������ �� ����
    \param pL [in/out] - ������ �����
    \param nLine [in]  - ���������� ����� � �������
    \param pP [in]     - ������ �� ���������� ���������� � ���� �����
*/
static void MarkLineCrimSkew (RLT_LINE *pL, const int nLine, const RLT_LINEATDIR *pP)
{
    for (int i = 0;  i < nLine;  i++)//���������� �����
    {
        int Sect = ::LineSect (pL[i].Type);
//        DeltaNorm = (pL[i].Skew2Delta + 4)/2;
//        DeltaNorm = ((pL[i].Skew2Delta + 4)*3)/4;//04.04.01
        int DeltaNorm = pL[i].Skew2Delta;//16.04.01
        if (DeltaNorm < MIN_DELTA_SKEW_NORM)
            DeltaNorm = MIN_DELTA_SKEW_NORM;
        if ((DeltaNorm > MAX_DELTA_SKEW_NORM) || (pL[i].Len >= MIN_LEN_LONG_LINE))
            DeltaNorm = MAX_DELTA_SKEW_NORM;
        if (abs(pL[i].Skew - pP[Sect].SkewPool) > DeltaNorm)
            pL[i].Type |= RLT_LT_SkewConflict;
    }
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ���������� �� ���������� ���������� � ���� �����
    \param pL [in]    - ������ �����
    \param nLine [in] - ���������� ����� � �������
    \param pP [out]   - ������ �� ���������� ���������� � ���� �����
*/
static void MarkPoolLineInfo (const RLT_LINE *pL, int nLine, RLT_LINEATDIR *pP)
{
    for (int j = 0; j < 4; j++)//�� ������ ����������
    {
        pP[j].nLine = 0;
        pP[j].nLongLine = 0;
        pP[j].nLongNoAtPool = 0;
        pP[j].nShortContrPool = 0;
    }
    for (int i = 0;  i < nLine;  i++)//���������� �����
    {
        int Sect = ::LineSect (pL[i].Type);
        (pP[Sect].nLine)++;
        if ((pL[i].Type & RLT_LT_Long) == RLT_LT_Long)
            (pP[Sect].nLongLine)++;
        if ((pL[i].Type & RLT_LT_SkewConflict) == RLT_LT_SkewConflict)//������������� �� ����
        {
            if ((pL[i].Type & RLT_LT_Long) == RLT_LT_Long)
                (pP[Sect].nLongNoAtPool)++;
            else
                (pP[Sect].nShortContrPool)++;
        }
    }
}
/*----------    ���������� �������    ------------------------------------------------------------*/
/**
    \brief ������� ������� ����� � �� ����� �� ���������
    \param pLinePool [in/out] - ��������� �� ��������� ����� � ��������� ���������� � ���
    \param Skew [in]          - ���� ������� ��������� ��������
    \note  ������������ � SMetric � USAGE
*/
void AnalOfMyLines (RLT_LINEPOOL *pLinePool, const Int32 Skew)
{
    for (int j = 0;  j < 4;  j++)//�� ������ ���������� ���������� �������������
    {
        pLinePool->Pool[j].SkewPool = Skew;
        pLinePool->Pool[j].WeightSkew = 1; //��� ��������
    }
    MarkLineCrimSkew (pLinePool->pLine, pLinePool->nLine, pLinePool->Pool);
    MarkPoolLineInfo (pLinePool->pLine, pLinePool->nLine, pLinePool->Pool);
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ����������, � ������ ��������� ��������� ����� ��� �����
    \param Type [in]          - ��� �����
    \retval RLT_LINEDIR_TYPE  - ��������, � ������� ����� �����
*/
RLT_LINEDIR_TYPE LineSect (const char Type)
{
    if ((Type & RLT_LT_Kosaya) == RLT_LT_Kosaya)//"������������" �� ���������� �����
    {
        if ((Type & RLT_LT_Vertic) == RLT_LT_Vertic)
            return RLT_LDIR_Kosa1;
        else
            return RLT_LDIR_Kosa2;
    }
    else
    {
        if ((Type & RLT_LT_Vertic) == RLT_LT_Vertic)
            return RLT_LDIR_Verti;
        else
            return RLT_LDIR_Horiz;
    }
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ��������� ������������ ������������� ����� �� ������
    \param p_vB [in/out] - ��������� �� ����� ���������� � ��������� ������
    \param pRcLin [out]  - ��������� �� ������������ �������������
    \param SkewReg[in]   - ���� ������� ��������� ���������
*/
bool FindLinesReg (const void *p_vB, Rect16 *pRcLin,  const Int32 SkewReg)
{
    Point16 A = {0}, B = {0};
    const UN_BUFF *pB = static_cast<const UN_BUFF *>(p_vB);
    /*  ��������� ������  */
    int Ind = ::FindSuchAimedData (p_vB, UN_DT_RltLinePool, UN_DA_Linii);
    if (Ind < 0)
        return false;
    int nLine = (static_cast<RLT_LINEPOOL *>(pB->vPart[Ind]))->nLine;
    if (nLine <= 0)
        return false;
    Ind = ::FindSuchAimedData (p_vB, UN_DT_RltLine, UN_DA_Linii);
    if (Ind < 0)
        return false;
    RLT_LINE *pLine = reinterpret_cast<RLT_LINE *>(pB->vPart[Ind]);
    /*  �������������� ������� �������������  */
    A.x = pLine[0].Beg.x;
    A.y = pLine[0].Beg.y;
    B.x = pLine[0].End.x;
    B.y = pLine[0].End.y;
    ::Deskew (A, -SkewReg);
    ::Deskew (B, -SkewReg);
    pRcLin->left   = A.x;
    pRcLin->right  = A.x;
    pRcLin->top    = A.y;
    pRcLin->bottom = A.y;
    /*  ���� ���������� ������� ������� ��������� �����  */
    for (int i = 0;  i < nLine;  i++)
    {
        A.x = pLine[i].Beg.x;
        A.y = pLine[i].Beg.y;
        B.x = pLine[i].End.x;
        B.y = pLine[i].End.y;
        ::Deskew (A, -SkewReg);
        ::Deskew (B, -SkewReg);
        if (pRcLin->left   > A.x)
            pRcLin->left   = A.x;
        if (pRcLin->right  < A.x)
            pRcLin->right  = A.x;
        if (pRcLin->top    > A.y)
            pRcLin->top    = A.y;
        if (pRcLin->bottom < A.y)
            pRcLin->bottom = A.y;
        if (pRcLin->left   > B.x)
            pRcLin->left   = B.x;
        if (pRcLin->right  < B.x)
            pRcLin->right  = B.x;
        if (pRcLin->top    > B.y)
            pRcLin->top    = B.y;
        if (pRcLin->bottom < B.y)
            pRcLin->bottom = B.y;
    }
    return true;
}
/*------------------------------------------------------------------------------------------------*/
/*----------    ��������� �������    -------------------------------------------------------------*/
static void MarkLineCrimSkew (RLT_LINE *pL, const int nLine, const RLT_LINEATDIR *pP);
static void MarkPoolLineInfo (const RLT_LINE *pL, int nLine, RLT_LINEATDIR *pP);
/*------------------------------------------------------------------------------------------------*/
