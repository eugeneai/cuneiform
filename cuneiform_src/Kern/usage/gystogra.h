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

#include "cttypes.h"
/*---------------------------------------------------------------------------*/
typedef struct tagUn_GYST
{
	int     Shift;
	int     nElem;
	int     End;
	int     *Signal;
} Un_GYST;
/*---------------------------------------------------------------------------*/
Bool MakeTopBotGysts (Rect16 *pRc, int nRc, Int32 Skew, int MaxSize,
				Un_GYST *pBegGt, Un_GYST *pEndGt);
Bool MakeLefRigGysts (Rect16 *pRc, int nRc, Int32 Skew, int MaxSize,
				Un_GYST *pBegGt, Un_GYST *pEndGt);
Bool MakeTopMidBotGysts (Rect16 *pRc, int nRc, Int32 Skew, int MaxSize,
				Un_GYST *pBegGt, Un_GYST *pMidGt, Un_GYST *pEndGt);
Bool MakeLefMidRigGysts (Rect16 *pRc, int nRc, Int32 Skew, int MaxSize,
				Un_GYST *pBegGt, Un_GYST *pMidGt, Un_GYST *pEndGt);
int ScoreComp (const Rect16 *pRcReg, const Int32 Skew, const Rect16 *pRc, const int nRc);
void MakeNormVertGyst (const Rect16 *pRcReg, const Int32 Skew, const Rect16 *pRc, const int nRc, int *Sig);
Bool MakeVertGysts (Rect16 *pRc, int nRc, Int32 Skew, int Amnist, int MaxSize, Un_GYST *pVerGt, int *pWhatDo);
void MakeNormHoriGyst (const Rect16 *pRcReg, const Int32 Skew, const Rect16 *pRc, const int nRc, int *Sig);
Bool MakeHoriGysts (Rect16 *pRc, int nRc, Int32 Skew, int MaxSize, Un_GYST *pHorGt, int *pWhatDo);
Bool MakeHoriSrez (Rect16 *pRcId, int nRc, int BegSrez, int EndSrez, int MaxSize, Un_GYST *pHorGt, int *pWhatDo);
Bool MakeVertSrez (Rect16 *pRcId, int nRc, int BegSrez, int EndSrez, int MaxSize, Un_GYST *pVerGt, int *pWhatDo);
Bool FindNextHole (Un_GYST *pDarkGt, int Beg, int End, int *NewBeg, int *NewEnd);
Bool FindNextHoleWithBound (int MaxSig, Un_GYST *pDarkGt, int Beg, int End, int *NewBeg, int *NewEnd, int MinLent);
Bool FindNormNextHoleWithBound (int *pSig, int LenSig, int Beg, int End
						, int *NewBeg, int *NewEnd, int MaxSig, int MinLent);
Bool FindMainHole (int Beg, int End, int MaxSig, Un_GYST *pOrtGt, int *NewBeg, int *NewEnd, int *NewMax);
/*---------------------------------------------------------------------------*/
