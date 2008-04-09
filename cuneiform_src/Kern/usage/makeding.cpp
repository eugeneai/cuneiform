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
    \file   MakeDing.CPP
    \brief  ���������� ������� ��������� � ������ ������������
    \author ��������� ��������
    \date   25.04.2005
*/
/*------------------------------------------------------------------------------------------------*/
/*  N-� �������� 25.04.2005:
    - ���������� � ��������� ����������, ������������� � ������ "MakeDing.CPP" � 15.04.2002  */
/*------------------------------------------------------------------------------------------------*/
/**********  ���������  **********/
/*  Author     :  Alexander Mikhailov                                        */
/*  Last Edit  :  12.10.99                                                   */
/*  Source     :  'MakeDing.CPP'                                             */
/*  ���������� :  ������� ��������� � ������ ������������.                   */
/*  ���������� :  II � III ����� ��������� ������ ������.                    */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <windows.h>
/*  interface my        */
#include "LineDesc.H"
#include "DingDesc.H"
#include "AlgParam.H"
#include "MakeDing.H"
/*  interface our  */
#include "skew1024.h"
/*----------    ���������� ���������    ----------------------------------------------------------*/
/*+ (MakeDingFromOneLine) +*/
static const int SIZE_REL_EXT_SCALE = 1024; ///< ������� ����� ������������� ����������
static const int MIN_LEN_STICK = (40 + 1); ///< ����������� ����� ������ ������������ ����� �� �����
static const int MAX_LEN_STICK = (60 - 1); ///< ������������ ����� ������ ������������ ����� �� ���.
static const int MIN_LEN_NORM_HORI = 100; ///< ����������� ����� ���������� �������������� �����
/*+ (IsNearestOldDing) +*/ /*+ (IsNearestDing) +*/
/** ������������ ���������� �� ������ �������� ������� ����������� �� ������ ������ */
static const int MAX_DIST_OLD_LEV_NEW_BORDER = 40;
/** ������������ ������� �������� ������� ����������� �� ����������� � ����� */
static const int MAX_HOLE_OLD_BORDER_NEW_LEV = 50;
/*+ (FindNextZveno) +*/
static const double HALF = .5; ///< �������� :-)
/** ������������ ���������� ����� �������� ������� ������������ */
static const int MAX_DIST_FRIEND_DING_BORDER = 14;
/*+ (MakeAbsendDing) +*/
static const int EXT_DING_BORDER = 40; ///< ���������� ����� �����������
/*+ (MakeAllAbsendDing) +*/
static const int MIN_LEN_BASIS_DING = 184; ///< ����������� ����� �������� �����������
/*+ (DelFreeDing) +*/
/** ������������ ������� ����������� �� ����������� � ��������� */
static const int MAX_HOLE_BORDER_NEAREST_LEV = 10;
/*+ (JoinDoubleDing) +*/
/** ������������ ���������� ����� �������������� ������������� */
static const int MAX_DIST_DOUBLE_DING = 10;
/*----------    ��������� �������    -------------------------------------------------------------*/
/**
    \brief ������� ������������ ����������� �� �����
    \param pDing [out] - ��������� �� �����������
    \param Skew[in]    - ���� ������� ��������� ���������
    \param pLine [in]  - ��������� �� �����
    \param Hori [in]   - �������������� �� ����� ��������������
    \param pParam [in] - ��������� �� ��������� ����������
*/
static void MakeDingFromOneLine (RLT_DING *pDing, const int Skew, const RLT_LINE *pLine
    , const bool Hori, const RLT_PARAM *pParam)
{
    Point16 A = {0}, B = {0};
    pDing->Width = pLine->Wid;
    if (pLine->Type & RLT_LT_Line)//����� - ����� ���������
    {
        pDing->Type  = RLT_DT_Line;
        if (pLine->Type & RLT_LT_Pointed)
            pDing->Type  |= RLT_DT_Pointed;
        if (pLine->Type & RLT_LT_Doubt)
            pDing->Type  |= RLT_DT_Doubt;//26.04.01
    }
    else//����� - ����������� ������
    {
        if (pLine->Type & RLT_LT_Ssel)
            pDing->Type  = RLT_DT_Ssel;
        else
            pDing->Type  = RLT_DT_Unknown;
    }
    /*  ������������� ����������  */
    int Udl = (pLine->Len * pParam->MaxRelUdlDng + SIZE_REL_EXT_SCALE / 2) / SIZE_REL_EXT_SCALE;
    if ((!Hori) && (pLine->Len >= MIN_LEN_STICK) && (pLine->Len <= MAX_LEN_STICK))
        Udl = pParam->MaxAbsUdlDng;
    if (Udl > pParam->MaxAbsUdlDng)
        Udl = pParam->MaxAbsUdlDng;
    if (Udl < pParam->MinAbsUdlDng)
        Udl = pParam->MinAbsUdlDng;
    if (Hori && (pLine->Len < MIN_LEN_NORM_HORI))
        Udl = 0;//16.04.01
    pDing->Width = pLine->Wid;
//    if (pDing->Width > 16)
//        Udl /= 2;
    A.x = pLine->Beg.x;
    A.y = pLine->Beg.y;
    B.x = pLine->End.x;
    B.y = pLine->End.y;
    ::Deskew (A, -Skew);
    ::Deskew (B, -Skew);
    if (Hori)//��������������
    {
        pDing->Beg = A.x;
        pDing->End = B.x;
        pDing->Beg_Big = A.x - Udl;
        pDing->End_Big = B.x + Udl;
        pDing->Level = A.y + B.y;
    }
    else//������������
    {
        pDing->Beg = A.y;
        pDing->End = B.y;
        pDing->Beg_Big = A.y - Udl;
        pDing->End_Big = B.y + Udl;
        pDing->Level = A.x + B.x;
    }
    if (pDing->Level >= 0)
        pDing->Level = (pDing->Level + 1) / 2;
    else
        pDing->Level = (pDing->Level - 1) / 2;
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ���������, ���������� �� ������ �����������, ������� � ����� ������������
    \param pD [out]    - ������ ������������
    \param nD [out]    - ���������� ������������
    \param Level [out] - ��������� ����� ������������ �����������
    \param Pos [out]   - ������� ������������ �����������
    \retval bool       - ���������� ��� ���
*/
static bool IsNearestOldDing (const RLT_DING *pD, const int nD, const int Level, const int Pos)
{
    for (int i = 0;  i < nD;  i++)
    {
        if (abs(pD[i].Level - Level) > MAX_DIST_OLD_LEV_NEW_BORDER)
            continue;
        if (pD[i].Beg > Pos + MAX_HOLE_OLD_BORDER_NEW_LEV)
            continue;
        if (pD[i].End < Pos - MAX_HOLE_OLD_BORDER_NEW_LEV)
            continue;
        return true;
    }
    return false;
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ���������, ���������� �� ������ �����������, ������� � ����� ������������
    \param pD [out]    - ������ ������������
    \param nD [out]    - ���������� ������������
    \param Level [out] - ������� ������������ �����������
    \param Beg [out]   - ��������� ������ ������������ �����������
    \param End [out]   - ��������� ����� ������������ �����������
    \retval bool       - ���������� ��� ���
*/
static bool IsNearestDing (const RLT_DING *pD, const int nD, const Int32 Level, const Int32 Beg
    , const Int32 End)
{
    for (int i = 0;  i < nD;  i++)
    {
        if (abs(pD[i].Level - Level) > MAX_DIST_OLD_LEV_NEW_BORDER)
            continue;
        if (pD[i].Beg > Beg + MAX_HOLE_OLD_BORDER_NEW_LEV)
            continue;
        if (pD[i].End < End - MAX_HOLE_OLD_BORDER_NEW_LEV)
            continue;
        return true;
    }
    return false;
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ���������� �� ����������� ����� � �������� (�� ����������� �������)
    \param p_Mas [in/out] - ����� �����
    \param p_Ind [in/out] - ����� ��������
    \param n [in]         - ����������� �������
*/
static void MyISort (int *p_Mas, int *p_Ind, const int n)
{
    for (int i = 0;  i < n - 1;  i++)//����������� �� ���������� �����
    {
        for (int j = i + 1;  j < n;  j++)//����� ����������� �������
        {
            if (p_Mas[i] <= p_Mas[j])
                continue;
            int k = p_Mas[i];
            p_Mas[i] = p_Mas[j];
            p_Mas[j] = k;
            int l = p_Ind[i];
            p_Ind[i] = p_Ind[j];
            p_Ind[j] = l;
        }
    }
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ��������� ������� ������� ������������
    \param p_Mas [in/out]    - ����� ������ ������� ������������
    \param p_Row [in/out]    - ����� ������� ������� ������������
    \param n [in]            - ����������� �������
    \param p_i0 [in/out]     - ��������� �� ������, �� ������� �������� ������� ����������� �� ����
    \param p_Level [out]     - ������� ���������� �������� �����������
    \param p_Beg [out]       - ������ ���������� �������� �����������
    \param p_End [out]       - ����� ���������� �������� �����������
    \param MinVoiForCre [in] - ����������� ����� ������� �� �������� ������ �����������
    \retval bool             - ������� ��� ���
*/
static bool FindNextZveno (int *p_Mas, int *p_Row, const int n, int *p_i0, int *p_Level, int *p_Beg
    , int *p_End, const int MinVoiForCre)
{
    /*  ����� ���������  */
    for (int i = *p_i0 + 1;  i < n - 1;  i++)//���� ������ ����������� � ���������� �������
    {
        int Wid = 1;
        int Sum = p_Mas[i];
        int iFin = 0; //�������� ������� (!)
        for (int j = i + 1;  j < n;  j++)//���� ���������� ���������
        {
            if (abs (p_Mas[i] - p_Mas[j]) > MAX_DIST_FRIEND_DING_BORDER)
                break;
            Wid++;
            Sum += p_Mas[j];
            iFin = j;
        }
        if (Wid < MinVoiForCre)//���������� ������
            continue;
        *p_i0 = iFin;
        *p_Beg = p_Row[i];
        *p_End = p_Row[i];
        for (j = i + 1;  j <= iFin;  j++)//���� ����� ������� ������ �� ������ (!) � ������
        {
            if (*p_Beg > p_Row[j])
                *p_Beg = p_Row[j];//������ ������� �� �����������
            if (*p_End < p_Row[j])
                *p_End = p_Row[j];
        }
        if (Sum >= 0)
            *p_Level = static_cast<int>(static_cast<double>(Sum) / static_cast<double>(Wid) + HALF);
        else
            *p_Level = static_cast<int>(static_cast<double>(Sum) / static_cast<double>(Wid) - HALF);
        return true;
    }
    return false;
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ������������ ���������� �����������
    \param pD [out]   - ��������� �� �����������
    \param Level [in] - ������� �����������
    \param Beg [in]   - ������ �����������
    \param End [in]   - ����� �����������
*/
static void MakeAbsendDing (RLT_DING *pD, const Int32 Level, const Int32 Beg, const Int32 End)
{
    pD->Beg = Beg;
    pD->End = End;
    pD->Beg_Big = Beg - EXT_DING_BORDER;
    pD->End_Big = End + EXT_DING_BORDER;
    pD->Level = Level;
    pD->Width = 1;
    pD->Type = RLT_DT_Unknown;
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ������������ ���� ������������� (?) ������� ������������
    \param pD1 [out]         - ����������� ������ ������������
    \param nD1 [in]          - ���������� ������������ � ����������� ������� �� ����������
    \param pD2 [out]         - ������������� ������ ������������
    \param nD2 [in]          - ���������� ������������ � ������������� �������
    \param p_Stat1 [out]     - ������ ������� � ����������� ������� ������������
    \param p_n1 [in/out]     - ������� ���������� ������������ � ����������� �������
    \param FromBeg [in]      - �� ������ �� ����������� �����
    \param MinVoiForCre [in] - ����������� ����� ������� �� �������� ������ �����������
    \param MinLenOpory [in]  - ����������� ����� �������� ����������� (�� ���������) (!)
*/
static void MakeAllAbsendDing (RLT_DING *pD1, const int nD1, const RLT_DING *pD2, const int nD2
    , char *p_Stat1, int *p_n1, bool const FromBeg, const int MinVoiForCre, const int MinLenOpory)
{
    int Mas[MaxMyDings], Row[MaxMyDings];
    int kD2 = 0;
    if (FromBeg)//����� �� ������ �� �����������
    {
        for (int i = 0;  i < nD2;  i++)//�������� ������� �����������
        {
            if (pD2[i].Type & RLT_DT_Refused)
                continue;
            if (pD2[i].End - pD2[i].Beg + 1 < MIN_LEN_BASIS_DING)
                continue;
            if (pD2[i].End - pD2[i].Beg + 1 < MinLenOpory)
                continue;
            if (IsNearestOldDing (pD1, nD1, pD2[i].Beg, pD2[i].Level))
                continue;
//            if (IsParallelDing (pD2, nD2, i, pD2[i].Level))
  //              continue;
            Mas[kD2] = pD2[i].Beg;
            Row[kD2] = pD2[i].Level;
            kD2++;
        }
    }
    else//����� �� ����� �����������
    {
        for (int i = 0;  i < nD2;  i++)//�������� ������� �����������
        {
            if (pD2[i].Type & RLT_DT_Refused)
                continue;
            if (pD2[i].End - pD2[i].Beg + 1 < MIN_LEN_BASIS_DING)
                continue;
            if (pD2[i].End - pD2[i].Beg + 1 < MinLenOpory)
                continue;
            if (IsNearestOldDing (pD1, nD1, pD2[i].End, pD2[i].Level))
                continue;
//            if (IsParallelDing (pD2, nD2, i, pD2[i].Level))
  //              continue;
            Mas[kD2] = pD2[i].End;
            Row[kD2] = pD2[i].Level;
            kD2++;
        }
    }
    MyISort (Row, Mas, kD2);//��������� �� ����������� ������
    int i = -1;
    int Beg = 0, End = 0, Level = 0;//������� ���������������� �����������
    while (1)//����������� �����, ���� ����������
    {
        bool ret = FindNextZveno (Mas, Row, kD2, &i, &Level, &Beg, &End, MinVoiForCre);
        if (!ret)
            break;
        ret = IsNearestDing (pD1, nD1, Level, Beg, End);
        if (ret)
            continue;
        if (*p_n1 >= MaxMyDings)//������������� ������ (!)
            continue;  // �����! �� ���� ������� ������
        MakeAbsendDing (&(pD1[*p_n1]), Level, Beg, End);
        p_Stat1[*p_n1] = RLT_DS_Created;
        (*p_n1)++;
    }
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ��������� � ��������� ������� ����������� ������������
    \param pD1 [in]      - ����������� ������ ������������
    \param nD1 [in]      - ���������� ������������ � ����������� �������
    \param pD2 [in]      - ������������� ������ ������������
    \param nD2 [in]      - ���������� ������������ � ������������� �������
    \param p_Stat1 [out] - ������ ������� � ����������� ������� ������������
*/
static void DelFreeDing (const RLT_DING *pD1, const int nD1, const RLT_DING *pD2, const int nD2
    , char *p_Stat1)
{
    for (int i = 0;  i < nD1; i++)//���������� ����������� �����������
    {
        bool NeedDel = true;
        for (int j = 0;  j < nD2;  j++)//���� ������������� �����������
        {
            if (pD1[i].Beg_Big > pD2[j].Level + MAX_HOLE_BORDER_NEAREST_LEV)
                continue;
            if (pD1[i].End_Big < pD2[j].Level - MAX_HOLE_BORDER_NEAREST_LEV)
                continue;
            if (pD2[j].Beg_Big > pD1[i].Level + MAX_HOLE_BORDER_NEAREST_LEV)
                continue;
            if (pD2[j].End_Big < pD1[i].Level - MAX_HOLE_BORDER_NEAREST_LEV)
                continue;
            NeedDel = false;
            break;
        }
        if (NeedDel)
            p_Stat1[i] = RLT_DS_Delete;
    }
}
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� ���������, �������� �� ���� ������������ ������, � ���� ��, �� ������ ������
    \param pD [out]      - ������ ������������
    \param p_nD [in/out] - ���������� ������������ � �������
    \param p_Stat [out]  - ������ ������� � ������� ������������
    \param pForw [out]   - ������ ������� �� �������� ������������
    \param MyMaxL [in]   - ������������ ���������� ������������ ��� ������������ �� ��������
    \param StepAlg [in]  - ����� ������������� ����
    \param Shft [in]     - ����� ������ ������������� ������� ��� ������ �������
    \param i [in]        - ����� ������� �����������
    \param j [in]        - ����� ������� �����������
    \retval bool         - ������������ ������ �������
*/
static bool JoinDoubleDing (RLT_DING *pD, int *p_nD, char *p_Stat, int *pForw, const int MyMaxL
    , const int StepAlg, const int Shft, const int i, const int j)
{
    if ((p_Stat[j] != RLT_DS_Normal) && (p_Stat[j] != RLT_DS_Created))
        return true;
    if (abs(pD[j].Level - pD[i].Level) > MAX_DIST_DOUBLE_DING + (pD[j].Width + pD[i].Width) / 2)
        return true;
    if ((pD[j].Beg_Big > pD[i].End) && (pD[j].Beg > pD[i].End_Big))
        return true;
    if ((pD[i].Beg_Big > pD[j].End) && (pD[i].Beg > pD[j].End_Big))
        return true;
    //09.11.01
    if ((pD[i].Type == RLT_DT_Line) && (pD[j].Type == RLT_DT_Line))//��������� ������� �����
    {
        if ((pD[j].Beg > pD[i].Beg) && (pD[j].Beg_Big < pD[i].Beg))
            return true;
        if ((pD[i].Beg > pD[j].Beg) && (pD[i].Beg_Big < pD[j].Beg))
            return true;
    }
    //////////
    if (*p_nD >= MaxMyDings)
        return false;
    /*  ������ ����������  */
    p_Stat[i] = RLT_DS_WasChanged;
    p_Stat[j] = RLT_DS_WasChanged;
    p_Stat[*p_nD] = RLT_DS_MadeOnBase;
    pForw[(2 * MyMaxL * StepAlg + Shft) + i] = Shft + *p_nD;
    pForw[(2 * MyMaxL * StepAlg + Shft) + j] = Shft + *p_nD;
    if (pD[i].Beg <= pD[j].Beg)
        pD[*p_nD].Beg = pD[i].Beg;
    else
        pD[*p_nD].Beg = pD[j].Beg;
    if (pD[i].End >= pD[j].End)
        pD[*p_nD].End = pD[i].End;
    else
        pD[*p_nD].End = pD[j].End;
    if (pD[i].Beg_Big <= pD[j].Beg_Big)
        pD[*p_nD].Beg_Big = pD[i].Beg_Big;
    else
        pD[*p_nD].Beg_Big = pD[j].Beg_Big;
    if (pD[i].End_Big >= pD[j].End_Big)
        pD[*p_nD].End_Big = pD[i].End_Big;
    else
        pD[*p_nD].End_Big = pD[j].End_Big;
/*        Level = pD[i].Level + pD[j].Level;
        if (Level>=0)
            pD[*nD].Level = (Level + 1)/2;
        else
            pD[*nD].Level = (Level - 1)/2;
        Width = (pD[i].Width + pD[j].Width + 1)/2;
        Width += abs(pD[i].Level - pD[j].Level);
        pD[*nD].Width = Width; */
    int Wei_i = (pD[i].End - pD[i].Beg) * pD[j].Width;
    int Wei_j = (pD[j].End - pD[j].Beg) * pD[i].Width;
    //15.04.02-Beg
    if (Wei_i < 0)
        Wei_i = 0;
    if (Wei_j < 0)
        Wei_j = 0;
    int Level = 0; //�������� ������� (!)
    if ((Wei_i == 0) && (Wei_j == 0))
        Level = (pD[i].Level + pD[j].Level) / 2;
    else//15.04.02-End
        Level = (Wei_i * pD[i].Level + Wei_j * pD[j].Level) / (Wei_i + Wei_j);
    pD[*p_nD].Level = Level;
    //15.04.02-Beg
    int Width = 0; //�������� ������� (!)
    if ((Wei_i == 0) && (Wei_j == 0))
        Width = (pD[i].Width + pD[j].Width) / 2;
    else//15.04.02-End
        Width = (Wei_i * pD[i].Width + Wei_j * pD[j].Width) / (Wei_i + Wei_j);
    pD[*p_nD].Width = Width;
    (*p_nD)++;
    return true;
}
/*----------    ���������� �������    ------------------------------------------------------------*/
void EvolFor_MakeDing (const RLT_LINEPOOL *pLinePool, int *pForw, int *pBack, const int MyMaxL
    , const int StepAlg)
{
    RLT_LINE *pL = pLinePool->pLine;
    int nHori = 0;
    int nVert = 0;
    for (int i = 0;  i < pLinePool->nLine;  i++)//���������� �����
    {
        if ((pL[i].Type & RLT_LT_SkewConflict) == RLT_LT_SkewConflict)
            continue;
        int Sect = ::LineSect (pL[i].Type);
        switch (Sect)//������ �������� ���� ����� �����
        {
            case RLT_LDIR_Horiz ://��������������
                pForw[(2 * MyMaxL * StepAlg) + i] = nHori;
                pBack[(2 * MyMaxL * StepAlg) + nHori] = i;
                nHori++;
                break;
            case RLT_LDIR_Verti ://������������
                pForw[(2 * MyMaxL * StepAlg) + MyMaxL + i] = MyMaxL + nVert;
                pBack[(2 * MyMaxL * StepAlg) + MyMaxL + nVert] = MyMaxL + i;
                nVert++;
                break;
            default :
                continue;
        }
    }
}
/*------------------------------------------------------------------------------------------------*/
bool MakeDingFromLine (RLT_DINGPOOL *pDingPool, const RLT_LINEPOOL *pLinePool
    , const RLT_PARAM *pParam, const Int32 SkewReg)
{
//    RLT_LINEATDIR *pP;
    RLT_LINE *pL = pLinePool->pLine;
//    pP = pLinePool->Pool;
    pDingPool->Skew = SkewReg;
    /*  ������� �����������  */
    pDingPool->nHori = 0;
    pDingPool->nVert = 0;
    for (int i = 0;  i < pLinePool->nLine; i++)//���������� �����
    {
        if ((pL[i].Type & RLT_LT_SkewConflict) == RLT_LT_SkewConflict)
            continue;
        int Sect = ::LineSect (pL[i].Type);
        switch (Sect)//������ ����������� ���� ����� �����
        {
            case RLT_LDIR_Horiz ://��������������
                if (pDingPool->nHori >= MaxMyDings)
                    return false;
                pDingPool->HoriStat[pDingPool->nHori] = RLT_DS_Normal;
                MakeDingFromOneLine (&(pDingPool->Hori[pDingPool->nHori]), pDingPool->Skew, &(pL[i])
                    , true, pParam);
                (pDingPool->nHori)++;
                break;
            case RLT_LDIR_Verti ://������������
                if (pDingPool->nVert >= MaxMyDings)
                    return false;
                pDingPool->VertStat[pDingPool->nVert] = RLT_DS_Normal;
                MakeDingFromOneLine (&(pDingPool->Vert[pDingPool->nVert]), pDingPool->Skew, &(pL[i])
                    , false, pParam);
                (pDingPool->nVert)++;
                break;
            default :
                continue;
        }
    }
    return true;
}
/*------------------------------------------------------------------------------------------------*/
bool DelAndAddDing (RLT_DINGPOOL *pDingPool, int *pForw, int *pBack, const int MyMaxL
    , const int StepAlg, const RLT_REVIDING *pReviDing)
{
//    Rect32 Bound, Found;
    /*  ������� ��������� ������� ������� ������������  */
//    FindBoundsOfDingRegion (pDingPool, &Bound, &Found);
//    if (!(Found.left&&Found.right&&Found.top&&Found.bottom))
//        return FALSE;
    /*  ��������� ����������� ����������� �� ����� �������  */
//    AddAbsendDingForBound (pDingPool, &Bound);
    int nHori = pDingPool->nHori;
    int nVert = pDingPool->nVert;
    /*  ����������� �������� ���������  */
    for (int i = 0;  i < 2 * MyMaxL;  i++)
    {
        pForw[(2*MyMaxL*StepAlg) + i] = i;
        pBack[(2*MyMaxL*StepAlg) + i] = i;
    }
    /*  ������� ����������� �������������� �� �������  */
    MakeAllAbsendDing (pDingPool->Hori, nHori, pDingPool->Vert, nVert
        , pDingPool->HoriStat, &(pDingPool->nHori), true, pReviDing->MinVoiForCre
        , pReviDing->VerMinLenOpory);
    /*  ������� ����������� �������������� �� ������  */
    MakeAllAbsendDing (pDingPool->Hori, nHori, pDingPool->Vert, nVert
        , pDingPool->HoriStat, &(pDingPool->nHori), false, pReviDing->MinVoiForCre
        , pReviDing->VerMinLenOpory);
    /*  ������� ����������� ������������ �� �������  */
    MakeAllAbsendDing (pDingPool->Vert, nVert, pDingPool->Hori, nHori
        , pDingPool->VertStat, &(pDingPool->nVert), true, pReviDing->MinVoiForCre
        , pReviDing->HorMinLenOpory);
    /*  ������� ����������� ������������ �� ������  */
    MakeAllAbsendDing (pDingPool->Vert, nVert, pDingPool->Hori, nHori
        , pDingPool->VertStat, &(pDingPool->nVert), false, pReviDing->MinVoiForCre
        , pReviDing->HorMinLenOpory);
    /*  ������� ��������� �������������� �����������  */
    DelFreeDing (pDingPool->Hori, pDingPool->nHori, pDingPool->Vert, pDingPool->nVert
        , pDingPool->HoriStat);
    /*  ������� ��������� ������������ �����������  */
    DelFreeDing (pDingPool->Vert, pDingPool->nVert, pDingPool->Hori, pDingPool->nHori
        , pDingPool->VertStat);
    /*  �������� ������������� �������������� �����������  */
    for (i = 0;  i < pDingPool->nHori;  i++)
    {
        if (pDingPool->HoriStat[i] != RLT_DS_Normal)
            continue;
        for (int j = i + 1;  j < pDingPool->nHori;  j++)//���������� ����������
        {
            bool ret = JoinDoubleDing (pDingPool->Hori, &pDingPool->nHori, pDingPool->HoriStat
                , pForw, MyMaxL, StepAlg, 0, i, j);
            if (!ret)
                return false;
        }
    }
    /*  �������� ������������� ������������ �����������  */
    for (i = 0;  i < pDingPool->nVert;  i++)
    {
        if (pDingPool->VertStat[i] != RLT_DS_Normal)
            continue;
        for (int j = i + 1;  j < pDingPool->nVert;  j++)//���������� ����������
        {
            bool ret = JoinDoubleDing (pDingPool->Vert, &pDingPool->nVert, pDingPool->VertStat
                , pForw, MyMaxL, StepAlg, MyMaxL, i, j);
            if (!ret)
                return false;
        }
    }
    return true;
}
/*------------------------------------------------------------------------------------------------*/
/*----------    ��������� �������    -------------------------------------------------------------*/
static void MakeDingFromOneLine (RLT_DING *pDing, const int Skew, const RLT_LINE *pLine
    , const bool Hori, const RLT_PARAM *pParam);
static bool IsNearestOldDing (const RLT_DING *pD, const int nD, const int Level, const int Pos);
static bool IsNearestDing (const RLT_DING *pD, const int nD, const Int32 Level, const Int32 Beg
    , const Int32 End);
static void MyISort (int *p_Mas, int *p_Ind, const int n);
static bool FindNextZveno (int *p_Mas, int *p_Row, const int n, int *p_i0, int *p_Level, int *p_Beg
    , int *p_End, const int MinVoiForCre);
static void MakeAbsendDing (RLT_DING *pD, const Int32 Level, const Int32 Beg, const Int32 End);
static void MakeAllAbsendDing (RLT_DING *pD1, const int nD1, const RLT_DING *pD2, const int nD2
    , char *p_Stat1, int *p_n1, bool const FromBeg, const int MinVoiForCre, const int MinLenOpory);
static void DelFreeDing (const RLT_DING *pD1, const int nD1, const RLT_DING *pD2, const int nD2
    , char *p_Stat1);
static bool JoinDoubleDing (RLT_DING *pD, int *p_nD, char *p_Stat, int *pForw, const int MyMaxL
    , const int StepAlg, const int Shft, const int i, const int j);
/*------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
static bool IsParallelDing (RLT_DING *pD, int nD, int iMy, int Level)
{
    int i;
    for (i = 0;  i < nD;  i++)
    {
        if (pD[i].End - pD[i].Beg + 1 <184)     //new
            continue;
        if (i == iMy)
            continue;
        if (abs(pD[i].Level - Level) > 40)
            continue;
//        return TRUE;
    }
    return FALSE;
}
static void AddAbsendDingForBound (RLT_DINGPOOL *pDingPool, Rect32 *pB)
{
    Bool NoCreate = IsNearestDing (pDingPool->Vert, pDingPool->nVert, pB->left, pB->top
        , pB->bottom);
    if ((!NoCreate) && (pDingPool->nVert < MaxMyDings))
    {
        MakeAbsendDing (&(pDingPool->Vert[pDingPool->nVert]), pB->left, pB->top, pB->bottom);
        pDingPool->VertStat[pDingPool->nVert] = RLT_DS_Created;
        (pDingPool->nVert)++;
    }
    NoCreate = IsNearestDing (pDingPool->Vert, pDingPool->nVert, pB->right, pB->top, pB->bottom);
    if ((!NoCreate) && (pDingPool->nVert < MaxMyDings))
    {
        MakeAbsendDing (&(pDingPool->Vert[pDingPool->nVert]), pB->right, pB->top, pB->bottom);
        pDingPool->VertStat[pDingPool->nVert] = RLT_DS_Created;
        (pDingPool->nVert)++;
    }
    NoCreate = IsNearestDing (pDingPool->Hori, pDingPool->nHori, pB->top, pB->left, pB->right);
    if ((!NoCreate) && (pDingPool->nHori < MaxMyDings))
    {
        MakeAbsendDing (&(pDingPool->Hori[pDingPool->nHori]), pB->top, pB->left, pB->right);
        pDingPool->HoriStat[pDingPool->nHori] = RLT_DS_Created;
        (pDingPool->nHori)++;
    }
    NoCreate = IsNearestDing (pDingPool->Hori, pDingPool->nHori, pB->bottom, pB->left, pB->right);
    if ((!NoCreate) && (pDingPool->nHori < MaxMyDings))
    {
        MakeAbsendDing (&(pDingPool->Hori[pDingPool->nHori]), pB->bottom, pB->left, pB->right);
        pDingPool->HoriStat[pDingPool->nHori] = RLT_DS_Created;
        (pDingPool->nHori)++;
    }
}
/*---------------------------------------------------------------------------*/
