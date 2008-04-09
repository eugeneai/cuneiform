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

/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  06.03.01                                                    */
/*  ����       :  'Util_Line_AM.CPP'                                          */
/*  ���������� :  ����� ������ � ������� ����� �������.                       */
/*  ���������� :  ������������ ��� ������ � ��������������� �������.          */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <windows.h>
/*  interface my        */
#include "LineDesc.H"
#include "MarkDataDefs.H"
/*  interface our  */
#include "skew1024.h"
/*  interface my-my      */
#include "AM_COMM.H"
#include "UN_Buff.H"
#include "UN_Err.H"
#include "Line_AM_Util.H" //own functions
/*----------------------------------------------------------------------------*/
void LastForLinesAM (void *vB)
{
	UN_BUFF *pB;
	RLT_LINEPOOL *pLinePool;
	pB = (UN_BUFF *)vB;
	pLinePool = (RLT_LINEPOOL *)pB->vPart[pB->nPart-2];
	pLinePool->nLine = pB->nPartUnits[pB->nPart-1];
}
/*----------------------------------------------------------------------------*/
Bool ReferForLinesAM (void *vLinePool, void *vB, int Aim)
{
	int Ind;
	UN_BUFF *pB;
	RLT_LINEPOOL *pLinePool;
	pLinePool = (RLT_LINEPOOL *)vLinePool;
	pB = (UN_BUFF *)vB;
	Ind = FindSuchAimedData (vB, UN_DT_RltLine, Aim);
	if (Ind < 0)
		return FALSE;
	pLinePool->pLine = (RLT_LINE *)pB->vPart[Ind];
	return TRUE;
}
/*---------------------------------------------------------------------------*/
Bool TakeFixedPlace_rv (void *vB, int Type, int Aim, char *pStr)
{
	UN_BUFF *pB;
	int nTeor;
	pB = (UN_BUFF *)vB;
	switch ((UN_DATATYPES)Type)
	{
		case UN_DT_RltLinePool :
			nTeor = sizeof (RLT_LINEPOOL);
			if (nTeor > pB->SizeCurr)
			{
				sprintf (pStr, "�� ������� ������ ��� %s!", "1 ��������� RLT_LINEPOOL");
				return RV_DOUBT;
			}
			memset (pB->vCurr, 0, nTeor);
			EndLastDataPart (vB, Aim, Type, nTeor, 1);
			return RV_TRUE;
		default :
			return RV_FALSE;
	}
}
/*----------------------------------------------------------------------------*/
Bool PrepareLinesAM_rv (int Aim, void *vB, void **vvData)
{
	int Ind;
	Bool ret;
	UN_BUFF *pB;
	pB = (UN_BUFF *)vB;
	*vvData = NULL;
	Ind = FindSuchAimedData (vB, UN_DT_RltLinePool, Aim);
	if (Ind < 0)
		return RV_EMPTY;
	*vvData = pB->vPart[Ind];
	ret = ReferForLinesAM (*vvData, vB, Aim);
	return ret;
}
/*----------------------------------------------------------------------------*/
void MarkLineType (void *vLine, Bool Hori, Bool ContWarn)
{
	RLT_LINE *pLine = (RLT_LINE *)vLine;
	pLine->Type = RLT_LT_Line;
	if (abs(pLine->Skew)>256)
	{
		pLine->Type |= RLT_LT_Kosaya;
		if (ContWarn)
		{
          #ifdef Almi 
			if (Hori)
				AM_Console ("Rlt-Warning-Continue : ���������� ����� �������������� �����!");
			else
				AM_Console ("Rlt-Warning-Continue : ���������� ����� ������������ �����!");
          #endif
			if (Hori)
			{
				if (pLine->Skew < 0)
				{
					pLine->Type |= RLT_LT_Vertic;
                #ifdef Almi
					if (ContWarn)
						AM_Console ("Rlt-Warning-Continue : ����� �������������� ����� ����� ������� ��� ����� ������������!");
                #endif
				}
			}
			else
			{
				if (pLine->Skew > 0)
				{
					pLine->Type |= RLT_LT_Vertic;
				}
				else
				{
                 #ifdef Almi
					if (ContWarn)
						AM_Console ("Rlt-Warning-Continue : ����� ������������ ����� ����� ������� ��� ����� ��������������!");
                 #endif				
				}
			}
		}
	}
	else
		if (!Hori)
			pLine->Type |= RLT_LT_Vertic;
	if (pLine->Len>=128)
		pLine->Type |= RLT_LT_Long;
}
/*----------------------------------------------------------------------------*/
