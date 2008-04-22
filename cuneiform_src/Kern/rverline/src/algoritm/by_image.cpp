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
/*  Author     :  Alexander Mikhailov                                        */
/*  Last Edit  :  22.06.99                                                   */
/*  Source     :  'By_Image.CPP'                                             */
/*  ���������� :  ������� ��������� ����������� �����.                       */
/*  ���������� :  ��������� ����������� ����� �� �����������.                */
/*---------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
/*#include <windows.h>*/
#include <stdlib.h>
#include <string.h>
/*  interface our-other  */
#include "lnsdefs.h"
#define _Not_Cpagetyps
#include "cpage.h"
#undef _Not_Cpagetyps
/*  interface my        */
#include "am_err.h"
#include "am_comm.h"
#include "vl_rule.h"
#include "myraster.h"
/*---------------------------------------------------------------------------*/
#define       MaxRastrHeight         33
#define       MaxRastrSize         1000
/*------------extern functions-----------------------------------------------*/
Bool MyGetRaster (Handle hCPage, VL_I_TASK *pTask, Word8 **ppData);
/*------------own functions--------------------------------------------------*/
Bool NoInvest (LineInfo *pLns, VL_I_TASK *pTask);
void BlackAddFromOneToOth (VL_I_TASK *pTask, Word8 *pData, Bool NormPhoto, int One, int Oth);
void MakeLightProfil (VL_I_TASK *pTask, int *Profil, Word8 *pData
					  , Bool NormPhoto, int *Beg, int *End, Bool UseSpusk);
Bool DecisionByImage (int *Profil, int Beg, int End, int Wid, int MaxLight
					  , int MinDark);
int InvestShortLineWithRastr_rv_pne (Handle hCPage, LineInfo *pLns);
/*---------------------------------------------------------------------------*/
Bool NoInvest (LineInfo *pLns, VL_I_TASK *pTask)
{
	if ((pLns->Thickness<0)||(pLns->Thickness>20))
		return TRUE;
	pTask->LineWid = pLns->Thickness;
	pTask->MySpusk = pLns->B.y - pLns->A.y;
	pTask->MyHeight = pTask->FreeHeight + abs(pTask->MySpusk) + pLns->Thickness;
	if (pTask->MyHeight > pTask->MaxHeight)
		return TRUE;
	pTask->MyNormWidth = pLns->B.x - pLns->A.x + 1;
	if (pTask->MyNormWidth <= 0)
		return TRUE;
	pTask->MyExtrWidth = 8*((pTask->MyNormWidth+7)/8);
	if ((pTask->MyExtrWidth/8) * pTask->MyHeight > pTask->MaxSize)
		return TRUE;
	pTask->MyLeft = pLns->A.x;
	pTask->MyTop  = (pLns->A.y + pLns->B.y + 1 - pTask->MyHeight)/2;
	return FALSE;
}
/*---------------------------------------------------------------------------*/
void BlackAddFromOneToOth (VL_I_TASK *pTask, Word8 *pData, Bool NormPhoto, int One, int Oth)
{
	Word8 *b;
	Word8 *c;
	int j;
	for (j=0; j<(pTask->MyExtrWidth/8); j++)
	{
		b = &(pData[One*(pTask->MyExtrWidth/8) + j]);
		c = &(pData[Oth*(pTask->MyExtrWidth/8) + j]);
		if (!NormPhoto)
		{
			if (!((*b)&0x01))
				(*c)&=(0xFF^0x01);
			if (!((*b)&0x02))
				(*c)&=(0xFF^0x02);
			if (!((*b)&0x04))
				(*c)&=(0xFF^0x04);
			if (!((*b)&0x08))
				(*c)&=(0xFF^0x08);
			if (!((*b)&0x10))
				(*c)&=(0xFF^0x10);
			if (!((*b)&0x20))
				(*c)&=(0xFF^0x20);
			if (!((*b)&0x40))
				(*c)&=(0xFF^0x40);
			if (!((*b)&0x80))
				(*c)&=(0xFF^0x80);
		}
		else
		{
			if (((*b)&0x01))
				(*c)|=0x01;
			if (((*b)&0x02))
				(*c)|=0x02;
			if (((*b)&0x04))
				(*c)|=0x04;
			if (((*b)&0x08))
				(*c)|=0x08;
			if (((*b)&0x10))
				(*c)|=0x10;
			if (((*b)&0x20))
				(*c)|=0x20;
			if (((*b)&0x40))
				(*c)|=0x40;
			if (((*b)&0x80))
				(*c)|=0x80;
		}
	}
}
/*---------------------------------------------------------------------------*/
void MakeLightProfil (VL_I_TASK *pTask, int *Profil, Word8 *pData
					  , Bool NormPhoto, int *Beg, int *End, Bool UseSpusk)
{
	Word8 a;
	Word8 *b;
	int i, j, k, Okrug;
	/*  1. ���������� ������� ����������� "�����������" �����������.  */
	if (UseSpusk)
	{
		if (pTask->MySpusk>=0)
		{
			*Beg = 0;
			*End = pTask->MyHeight - 1 - pTask->MySpusk;
		}
		else
		{
			*Beg = 0 - pTask->MySpusk;
			*End = pTask->MyHeight - 1;
		}
	}
	else
	{
		*Beg = 0;
		*End = pTask->MyHeight - 1;
	}
	/*  2. �������� "������ ���������" ���������� ������ �� ������������.  */
	if (pTask->MyExtrWidth > pTask->MyNormWidth)
	{
		for (i=0; i<=pTask->MyHeight - 1; i++)
		{
			b = &(pData[i*(pTask->MyExtrWidth/8) + pTask->MyExtrWidth/8 - 1]);
			if (NormPhoto)
			{
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 1)
					(*b)&=(0xFF^0x01);
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 2)
					(*b)&=(0xFF^0x02);
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 3)
					(*b)&=(0xFF^0x04);
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 4)
					(*b)&=(0xFF^0x08);
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 5)
					(*b)&=(0xFF^0x10);
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 6)
					(*b)&=(0xFF^0x20);
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 7)
					(*b)&=(0xFF^0x40);
			}
			else
			{
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 1)
					(*b)|=0x01;
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 2)
					(*b)|=0x02;
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 3)
					(*b)|=0x04;
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 4)
					(*b)|=0x08;
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 5)
					(*b)|=0x10;
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 6)
					(*b)|=0x20;
				if (pTask->MyExtrWidth - pTask->MyNormWidth >= 7)
					(*b)|=0x40;
			}
		}
	}
	/*  3. ��� ����� ����� ����������� "������ �������" �� 1 ����� � ����.  */
	if (pTask->LineWid <= 2)
	{
		for (i=1; i<=pTask->MyHeight - 1; i++)
			BlackAddFromOneToOth (pTask, pData, NormPhoto, i, i-1);
		for (i=pTask->MyHeight - 2; i>=0; i--)
			BlackAddFromOneToOth (pTask, pData, NormPhoto, i, i+1);
	}
	/*  4. ������� ���������� �����������.  */
	Okrug = (pTask->MyExtrWidth/8 - 1 + 1)/2;
	for (i=*Beg; i<=*End; i++)
	{
		Profil[i] = 0;
		for (j=0; j<(pTask->MyExtrWidth/8); j++)
		{
			if (UseSpusk)
				k = i + pTask->MySpusk
				*((j + Okrug)/(pTask->MyExtrWidth/8 - 1));
			else
				k = i;
			a = pData[k*(pTask->MyExtrWidth/8) + j];
			if (a&0x01)
				Profil[i]++;
			if (a&0x02)
				Profil[i]++;
			if (a&0x04)
				Profil[i]++;
			if (a&0x08)
				Profil[i]++;
			if (a&0x10)
				Profil[i]++;
			if (a&0x20)
				Profil[i]++;
			if (a&0x40)
				Profil[i]++;
			if (a&0x80)
				Profil[i]++;
		}
	}
	/*  5. ���� �����������.  */
	if (!NormPhoto)
	{
		for (i=*Beg; i<=*End; i++)
			Profil[i] = pTask->MyExtrWidth - Profil[i];
	}
}
/*---------------------------------------------------------------------------*/
Bool DecisionByImage (int *Profil, int Beg, int End, int Wid, int MaxLight, int MinDark)
{
	Bool IsSuchLevel;
	int i, iPos;
	IsSuchLevel = FALSE;
	for (i=Beg; i<=End; i++)
	{
		if (100*Profil[i]>MaxLight*Wid)
			continue;
		IsSuchLevel = TRUE;
		break;
	}
	if (!IsSuchLevel)
		return FALSE;
	iPos=i;
	IsSuchLevel = FALSE;
	for (i=iPos; i<=End; i++)
	{
		if (100*Profil[i]<MinDark*Wid)
			continue;
		IsSuchLevel = TRUE;
		break;
	}
	if (!IsSuchLevel)
		return FALSE;
	iPos=i;
	IsSuchLevel = FALSE;
	for (i=iPos; i<=End; i++)
	{
		if (100*Profil[i]>MaxLight*Wid)
			continue;
		IsSuchLevel = TRUE;
		break;
	}
	if (!IsSuchLevel)
		return FALSE;
	return TRUE;
}
/*---------------------------------------------------------------------------*/
int InvestShortLineWithRastr_rv_pne (Handle hCPage, LineInfo *pLns)
{
	VL_I_TASK Task = {0};
	Word8 Data[MaxRastrSize];
	Word8 *Buffer;
	Bool ret;
	int i, Beg, End, Okrug;
	int Profil[MaxRastrHeight];
	/*  1. ���������.  */
	Task.MaxHeight  = MaxRastrHeight;
	Task.MaxSize    = MaxRastrSize;
	Task.FreeHeight = 13;
	/*  2. ���������� ������ �� �������� �� ����.  */
	if (pLns->Flags & LI_NOTWHOLE)
		return RV_EMPTY;
	if (pLns->Flags & LI_COMPLEX)
		return RV_EMPTY;
	/*  3. ������ ������ �� �������� �� ����. ���������� ������.  */
	ret = NoInvest (pLns, &Task);
	if (ret)
	{
		if (!AM_Skip (AM_GetKeyOfRule (RU_VL_C_ContWarn)))
			AM_Console ("����� �� �������� �� ���� ����� (%d %d) (%d %d)\n"
			,pLns->A.x ,pLns->A.y, pLns->B.x, pLns->B.y);
		return RV_EMPTY;
	}
	/*  4. ������ ����� �����������.  */
	memset (Data, 0, sizeof (Data));
	Buffer = Data;
	ret = MyGetRaster (hCPage, &Task, &Buffer);
	if (!ret)
	{
		if (!AM_Skip (AM_GetKeyOfRule (RU_VL_C_ContWarn)))
			AM_Console ("�� ���� ������ �� ���� ��� ����� (%d %d) (%d %d)\n"
			,pLns->A.x ,pLns->A.y, pLns->B.x, pLns->B.y);
		return RV_EMPTY;
	}
	/*  5. �����������.  */
	MakeLightProfil (&Task, Profil, Buffer, FALSE, &Beg, &End, TRUE);
	if (!AM_Skip (AM_GetKeyOfRule (RU_VL_D_InvestImage)))
	{
		Okrug = (Task.MyNormWidth + 1)/2;
		AM_Console ("��������� ��� ������� (%d %d) (%d %d)\n"
		, Task.MyLeft, Task.MyTop, Task.MyLeft + Task.MyNormWidth - 1, Task.MyTop + Task.MyHeight - 1);
		for (i=Beg; i<=End; i++)
		{
			AM_Console ("Level = %d Dark = %4d   [%3d]\n"
				, Task.MyTop + i, Profil[i]
				, (100*Profil[i] + Okrug)/(Task.MyNormWidth));
		}
	}
	/*  5-1. ����������� ���� ���������, ������� ������ ���� �� ����.  
	memset (Data, 0, sizeof (Data));
	Buffer = Data;
	ret = MyGetRaster (hCPage, &Task, &Buffer);
	if (!ret)
	{
		if (!AM_Skip (AM_GetKeyOfRule (RU_VL_C_ContWarn)))
			AM_Console ("�� � ����! �� ���� ������ ��� (%d %d) (%d %d)\n"
			,pLns->A.x ,pLns->A.y, pLns->B.x, pLns->B.y);
	}*/
	/*  6. ������� �� �����.  */
//	if ((Task.LineWid <= 2)&&((Task.MyNormWidth >= 300)))
	if ((Task.LineWid <= 3)&&((Task.MyNormWidth >= 200))) //28.09.00
		ret = DecisionByImage (Profil, Beg, End, Task.MyNormWidth, 10, 69);//70);
	else
		ret = DecisionByImage (Profil, Beg, End, Task.MyNormWidth, 10, 90);
	if (!AM_Skip (AM_GetKeyOfRule (RU_VL_D_InvestImage)))
	{
		if (ret)
			AM_Console ("��������� ����� (%d %d)-(%d %d) ������ %d\n"
			, pLns->A.x ,pLns->A.y, pLns->B.x, pLns->B.y, pLns->Thickness);
		else
			AM_Console ("����� ����� (%d %d)-(%d %d) ������ %d\n"
			, pLns->A.x ,pLns->A.y, pLns->B.x, pLns->B.y, pLns->Thickness);
	}
	if (ret)
		return RV_POSITIVE;
	else
		return RV_NEGATIVE;
}
/*---------------------------------------------------------------------------*/
