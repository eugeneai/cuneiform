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
    \file   AMU_Geom.CPP
    \brief  ���������� ������� �������������� �������
    \author ��������� ��������
    \date   21.04.2005
*/
/*------------------------------------------------------------------------------------------------*/
/*  N-� �������� 21.04.2005:
    - ���������� � ��������� ����������, ������������� � ������ "AMU_Geom.CPP" � 02.03.2001  */
/*------------------------------------------------------------------------------------------------*/
#include <stdio.h>
/*  ������������ �����  */
#include "skew1024.h"
/*  ������������ ��� (����������)  */
#include "AMT_Geom.H"
/*----------    ���������� ���������    ----------------------------------------------------------*/
/*+ (AverageRoundToBig) +*/
static const double HALF = .5; ///< �������� :-)
/*+ (MakeInternalRectId) +*/
static const int SIZE_SKEW_SCALE = 1024; ///< ������� ����� �����
/** ������������ �� ������ ���� ��� ����������� ������������� */
static const int MAX_ABS_SKEW = SIZE_SKEW_SCALE / 2;
/*----------    ��������� �������    -------------------------------------------------------------*/
/**
    \brief ������� ��������� ����� �� ������
    \param pA [in/out]   - ��������� �� ����� - ������ ����� � �������� �����������
    \param pB [in/out]   - ��������� �� ����� - ����� ����� � �������� �����������
    \param Lev [in]      - ������� ��������� � ��������� �����������
    \param Lev_A [in]    - ������� ������ ����� � ��������� �����������
    \param Lev_B [in]    - ������� ����� ����� � ��������� �����������
    \param LimIsMax [in] - ������� �� ����� ������� ���������
    \param Near [in]     - ���������� ������ (?)
    \retval bool         - ��� �������� ��� ���
*/
static bool CanUse (Point16 *pA, Point16 *pB, const int Lev, const int Lev_A, const int Lev_B
    , const bool LimIsMax, const int Near)
{
    Point16 C = {0};
    if (LimIsMax)//������� ������������ ������
    {
        if ((Lev_A <= Lev + Near) && (Lev_B <= Lev + Near))
            return true;
        if ((Lev_A >= Lev + Near) && (Lev_B >= Lev + Near))
            return false;
        /*  ������� ����� �������  */
        C.x = ((Lev - Lev_B) * pA->x + (Lev_A - Lev) * pB->x) / (Lev_A - Lev_B);
        C.y = ((Lev - Lev_B) * pA->y + (Lev_A - Lev) * pB->y) / (Lev_A - Lev_B);
        if (Lev_A > Lev)//�������� ��������
        {
            pA->x = C.x;
            pA->y = C.y;
        }
        else
        {
            pB->x = C.x;
            pB->y = C.y;
        }
    }
    else//������� ������������ �����
    {
        if ((Lev_A >= Lev - Near) && (Lev_B >= Lev - Near))
            return true;
        if ((Lev_A <= Lev - Near) && (Lev_B <= Lev - Near))
            return false;
        /*  ������� ����� �������  */
        C.x = ((Lev - Lev_B) * pA->x + (Lev_A - Lev) * pB->x) / (Lev_A - Lev_B);
        C.y = ((Lev - Lev_B) * pA->y + (Lev_A - Lev) * pB->y) / (Lev_A - Lev_B);
        if (Lev_A < Lev)//�������� �������
        {
            pA->x = C.x;
            pA->y = C.y;
        }
        else
        {
            pB->x = C.x;
            pB->y = C.y;
        }
    }
    return true;
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ���������� � ����������� � ������� �������
    \param a [in] - ������ �����������
    \param a [in] - ������ �����������
    \retval int   - ���������
*/
inline static int AverageRoundToBig (Int16 a, Int16 b)
{
    return static_cast<int>(HALF * (a + b + 1));
}
/*----------    ���������� �������    ------------------------------------------------------------*/
void RotateRect (const Rect16 *pRcRe, Rect16 *pRcId, Int32 Skew)
{
    Point32 DirIdeal = {0};
    /*  ���������� ������ �������� ����  */
    DirIdeal.x = AverageRoundToBig (pRcRe->left, pRcRe->right);
    DirIdeal.y = pRcRe->top;
    ::Deskew (DirIdeal, -Skew);
    pRcId->top = static_cast<Int16>(DirIdeal.y);
    /*  ���������� ������� �������� ����  */
    DirIdeal.x = AverageRoundToBig (pRcRe->left, pRcRe->right);
    DirIdeal.y = pRcRe->bottom;
    ::Deskew (DirIdeal, -Skew);
    pRcId->bottom = static_cast<Int16>(DirIdeal.y);
    /*  ���������� ������ ������� ����  */
    DirIdeal.x = pRcRe->left;
    DirIdeal.y = AverageRoundToBig (pRcRe->top, pRcRe->bottom);
    ::Deskew (DirIdeal, -Skew);
    pRcId->left = static_cast<Int16>(DirIdeal.x);
    /*  ���������� ������� ������� ����  */
    DirIdeal.x = pRcRe->right;
    DirIdeal.y = AverageRoundToBig (pRcRe->top, pRcRe->bottom);
    ::Deskew (DirIdeal, -Skew);
    pRcId->right = static_cast<Int16>(DirIdeal.x);
}
/*------------------------------------------------------------------------------------------------*/
void FindMinimIdealRegion (const int nRc, const int *pDo, const Rect16 *pRcIdeal, Rect16 *pMIR)
{
    /*  ������� ������ ������� ����������  */
    int iFirst = -1;
    for (int i = 0; i < nRc; i++)
    {
        if (pDo[i] != 1)
            continue;
        iFirst = i;
        break;
    }
    if (iFirst == -1)
    {/*  �� ����� ���������� ��� � ������ ��� �������  */
        pMIR->left   = 0;
        pMIR->right  = 0;
        pMIR->top    = 0;
        pMIR->bottom = 0;
        return;
    }
    /*  ������� �� ������ ����������  */
    int MinTop = pRcIdeal[iFirst].top;
    int MaxBot = pRcIdeal[iFirst].bottom;
    int MinLef = pRcIdeal[iFirst].left;
    int MaxRig = pRcIdeal[iFirst].right;
    /*  ������� �� ���� �����������  */
    for (i = iFirst; i < nRc; i++)
    {
        if (pDo[i] != 1)
            continue;
        int CurTop = pRcIdeal[i].top;
        int CurBot = pRcIdeal[i].bottom;
        int CurLef = pRcIdeal[i].left;
        int CurRig = pRcIdeal[i].right;
        if (MinTop > CurTop)
            MinTop = CurTop;
        if (MaxBot < CurBot)
            MaxBot = CurBot;
        if (MinLef > CurLef)
            MinLef = CurLef;
        if (MaxRig < CurRig)
            MaxRig = CurRig;
    }
    pMIR->left   = MinLef;
    pMIR->right  = MaxRig;
    pMIR->top    = MinTop;
    pMIR->bottom = MaxBot;
}
/*------------------------------------------------------------------------------------------------*/
bool HaveLinePartAtReg (Point16 *pA, Point16 *pB, const Rect16 *pRc, const Int32 Skew
    , const int NearHor, const int NearVer)
{
    Point16 Cur_A = {0}, Cur_B = {0};
    /*  �������� ���  */
    Cur_A.x = pA->x;
    Cur_A.y = pA->y;
    ::Deskew (Cur_A, -Skew);
    Cur_B.x = pB->x;
    Cur_B.y = pB->y;
    ::Deskew (Cur_B, -Skew);
    int Lev_A = Cur_A.y;
    int Lev_B = Cur_B.y;
    int Lev = pRc->top;
    bool ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, false, NearHor);
    if (!ret)
        return ret;
    /*  �������� ����  */
    Cur_A.x = pA->x;
    Cur_A.y = pA->y;
    ::Deskew (Cur_A, -Skew);
    Lev_A = Cur_A.y;
    Lev = pRc->bottom;
    ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, true, NearHor);
    if (!ret)
        return ret;
    /*  �������� �����  */
    Cur_B.x = pB->x;
    Cur_B.y = pB->y;
    ::Deskew (Cur_B, -Skew);
    Lev_A = Cur_A.x;
    Lev_B = Cur_B.x;
    Lev = pRc->left;
    ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, false, NearVer);
    if (!ret)
        return ret;
    /*  �������� ������  */
    Cur_A.x = pA->x;
    Cur_A.y = pA->y;
    ::Deskew (Cur_A, -Skew);
    Lev_A = Cur_A.x;
    Lev = pRc->right;
    ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, true, NearVer);
    if (!ret)
        return ret;
    return true;
}
/*------------------------------------------------------------------------------------------------*/
bool IsRectsCross (const Rect16 *pRc1, const Rect16 *pRc2)
{
    if (pRc1->left > pRc2->right)
        return false;
    if (pRc2->left > pRc1->right)
        return false;
    if (pRc1->top  > pRc2->bottom)
        return false;
    if (pRc2->top  > pRc1->bottom)
        return false;
    return true;
}
/*------------------------------------------------------------------------------------------------*/
bool MakeInternalRectId (const Rect16 *pRcRe, Rect16 *pRcId, Int32 Skew)
{
    Point32 LefTop = {0}, RigTop = {0}, LefBot = {0}, RigBot = {0};
    if ((Skew > MAX_ABS_SKEW) || (Skew < -MAX_ABS_SKEW))
        return false;
    if (pRcRe->right - pRcRe->left < pRcRe->bottom - pRcRe->top)
        return false;
    LefTop.x = pRcRe->left;
    LefTop.y = pRcRe->top;
    RigTop.x = pRcRe->right;
    RigTop.y = pRcRe->top;
    LefBot.x = pRcRe->left;
    LefBot.y = pRcRe->bottom;
    RigBot.x = pRcRe->right;
    RigBot.y = pRcRe->bottom;
    ::Deskew (LefTop, -Skew);
    ::Deskew (RigTop, -Skew);
    ::Deskew (LefBot, -Skew);
    ::Deskew (RigBot, -Skew);
    if (Skew >= 0)//�� ������� ������� �� ������ �������� ����
    {
        pRcId->top    = static_cast<Int16>(LefTop.y);
        pRcId->bottom = static_cast<Int16>(RigBot.y);
        pRcId->left   = static_cast<Int16>(LefBot.x);
        pRcId->right  = static_cast<Int16>(RigTop.x);
    }
    else
    {
        pRcId->top    = static_cast<Int16>(RigTop.y);
        pRcId->bottom = static_cast<Int16>(LefBot.y);
        pRcId->left   = static_cast<Int16>(LefTop.x);
        pRcId->right  = static_cast<Int16>(RigBot.x);
    }
    if (pRcId->top > pRcId->bottom)
        return false;
    if (pRcId->left > pRcId->right)
        return false;
    return true;
}
/*------------------------------------------------------------------------------------------------*/
/*----------    ��������� �������    -------------------------------------------------------------*/
static bool CanUse (Point16 *pA, Point16 *pB, const int Lev, const int Lev_A, const int Lev_B
    , const bool LimIsMax, int Near);
inline static int AverageRoundToBig (Int16 a, Int16 b);
/*------------------------------------------------------------------------------------------------*/
