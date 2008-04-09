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
    \brief  �������� ������� �������������� �������
    \author ��������� ��������
    \date   19.04.2005
*/
/*------------------------------------------------------------------------------------------------*/
/*  N-� �������� 19.04.2005:
    - ���������� � ��������� ����������, ������������� � ������ "AMU_Geom.CPP" � 02.03.2001  */
/*------------------------------------------------------------------------------------------------*/
/*  ������������ �����  */
#include "cttypes.h"
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� �������� ��������������
    \param pRcRe [in]  - ��������� �� ������������� � �������� �����������
    \param pRcId [out] - ��������� �� ������������� � ��������� �����������
    \param Skew[in]    - ���� ������� ��������� ���������
    \note  ������������ � RLTable � USAGE
*/
void RotateRect (const Rect16 *pRcRe, Rect16 *pRcId, Int32 Skew);
/**
    \brief ������� ���������� ������������ ��������������, ������������� ��������
    \param nRc [in]      - ���������� ������������ ���������������
    \param pDo [in]      - ������ ������� �� ������������ ���������������
    \param pRcIdeal [in] - ������ ������������ ���������������
    \param pMIR [out]    - ��������� �� ������������ �������������
    \note  ������������ ������ � SStreak
*/
void FindMinimIdealRegion (const int nRc, const int *pDo, const Rect16 *pRcIdeal, Rect16 *pMIR);
/**
    \brief ������� ���������, ���������� �� ����� �������������
    \param pA [in/out]  - ��������� �� ����� - ������ ����� � �������� �����������
    \param pB [in/out]  - ��������� �� ����� - ����� ����� � �������� �����������
    \param pRc [in]     - ��������� �� ����������� ������������� � ��������� �����������
    \param Skew [in]    - ���� ������� ��������� ���������
    \param NearHor [in] - �������� ��������, ����������� ���������� � �����
    \param NearVer [in] - �������� ��������, ����������� ���������� � �����
    \retval bool        - ��� ���������� ��� ���
    \note  ������������ � RVerLine � USAGE
*/
bool HaveLinePartAtReg (Point16 *pA, Point16 *pB, const Rect16 *pRc, const Int32 Skew
    , const int NearHor, const int NearVer);
/**
    \brief ������� ���������, ������������ �� ��� ��������������
    \param pRc1 [in] - ��������� �� ������ �������������
    \param pRc2 [in] - ��������� �� ������ �������������
    \retval bool     - ��� ������������ ��� ���
    \note  ������������ ������ � MZoning
*/
bool IsRectsCross (const Rect16 *pRc1, const Rect16 *pRc2);
/**
    \brief ������� �������� �������������� - �������� ������ ������� RotateRect
    \param pRcRe [in]  - ��������� �� ������������� � �������� �����������
    \param pRcId [out] - ��������� �� ������������� � ��������� �����������
    \param Skew[in]    - ���� ������� ��������� ���������
    \note  ������������ ������ � MZoning
*/
bool MakeInternalRectId (const Rect16 *pRcRe, Rect16 *pRcId, Int32 Skew);
/*------------------------------------------------------------------------------------------------*/
