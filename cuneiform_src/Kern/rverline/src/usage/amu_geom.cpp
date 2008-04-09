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

#include <stdio.h>
/*  interface our util  */
#include "skew1024.h"
/*  interface my-my      */
#include "AMT_Geom.H"
/*----------------------------------------------------------------------------*/
void RotateRect (Rect16 *pRcRe, Rect16 *pRcId, Int32 Skew)
{
	Point32 DirIdeal;
	DirIdeal.x = (int)(.5 * (pRcRe->left + pRcRe->right + 1));
	DirIdeal.y = pRcRe->top;
	Deskew (DirIdeal, -Skew);
	pRcId->top = (Int16)DirIdeal.y;
	DirIdeal.x = (int)(.5 * (pRcRe->left + pRcRe->right + 1));
	DirIdeal.y = pRcRe->bottom;
	Deskew (DirIdeal, -Skew);
	pRcId->bottom = (Int16)DirIdeal.y;
	DirIdeal.x = pRcRe->left;
	DirIdeal.y = (int)(.5 * (pRcRe->top + pRcRe->bottom + 1));
	Deskew (DirIdeal, -Skew);
	pRcId->left = (Int16)DirIdeal.x;
	DirIdeal.x = pRcRe->right;
	DirIdeal.y = (int)(.5 * (pRcRe->top + pRcRe->bottom + 1));
	Deskew (DirIdeal, -Skew);
	pRcId->right = (Int16)DirIdeal.x;
}
/*----------------------------------------------------------------------------*/
void FindMinimIdealRegion (int nRc, int *pDo, Rect16 *pRcIdeal, Rect16 *pMIR)
{
	int MinTop, MaxBot, MinLef, MaxRig, CurTop, CurBot, CurLef, CurRig, i, iFirst;
	/*  ������� ������ ������� ����������  */
	iFirst = -1;
	for (i=0; i<nRc; i++)
	{
		if (pDo[i]!=1)
			continue;
		iFirst = i;
		break;
	}
	if (iFirst==-1)
	{/*  �� ����� ���������� ��� � ������ ��� �������  */
		pMIR->left   = 0;
		pMIR->right  = 0;
		pMIR->top    = 0;
		pMIR->bottom = 0;
		return;
	}
	/*  ������� �� ������ ����������  */
	MinTop = pRcIdeal[iFirst].top;
	MaxBot = pRcIdeal[iFirst].bottom;
	MinLef = pRcIdeal[iFirst].left;
	MaxRig = pRcIdeal[iFirst].right;
	/*  ������� �� ���� �����������  */
	for (i=iFirst; i<nRc; i++)
	{
		if (pDo[i]!=1)
			continue;
		CurTop = pRcIdeal[i].top;
		CurBot = pRcIdeal[i].bottom;
		CurLef = pRcIdeal[i].left;
		CurRig = pRcIdeal[i].right;
		if (MinTop > CurTop) MinTop = CurTop;
		if (MaxBot < CurBot) MaxBot = CurBot;
		if (MinLef > CurLef) MinLef = CurLef;
		if (MaxRig < CurRig) MaxRig = CurRig;
	}
	pMIR->left   = MinLef;
	pMIR->right  = MaxRig;
	pMIR->top    = MinTop;
	pMIR->bottom = MaxBot;
}
/*----------------------------------------------------------------------------*/
Bool CanUse (Point16 *pA, Point16 *pB, int Lev, int Lev_A, int Lev_B, int LimIsMax, int Near)
{
	Point16 C;
	if (LimIsMax)
	{
		if ((Lev_A<=Lev + Near)&&(Lev_B<=Lev + Near))
			return TRUE;
		if ((Lev_A>=Lev + Near)&&(Lev_B>=Lev + Near))
			return FALSE;
		C.x = ((Lev-Lev_B)*pA->x+(Lev_A-Lev)*pB->x)/(Lev_A-Lev_B);
		C.y = ((Lev-Lev_B)*pA->y+(Lev_A-Lev)*pB->y)/(Lev_A-Lev_B);
		if (Lev_A > Lev)
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
	else
	{
		if ((Lev_A>=Lev - Near)&&(Lev_B>=Lev - Near))
			return TRUE;
		if ((Lev_A<=Lev - Near)&&(Lev_B<=Lev - Near))
			return FALSE;
		C.x = ((Lev-Lev_B)*pA->x+(Lev_A-Lev)*pB->x)/(Lev_A-Lev_B);
		C.y = ((Lev-Lev_B)*pA->y+(Lev_A-Lev)*pB->y)/(Lev_A-Lev_B);
		if (Lev_A < Lev)
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
	return TRUE;
}
/*----------------------------------------------------------------------------*/
Bool HaveLinePartAtReg (Point16 *pA, Point16 *pB, Rect16 *pRc, Int32 Skew
						, int NearHor, int NearVer)
{
	int Lev, Lev_A, Lev_B;
	Point16 Cur_A, Cur_B;
	Bool ret;
	Cur_A.x =pA->x;
	Cur_A.y =pA->y;
	Deskew (Cur_A, -Skew);
	Cur_B.x =pB->x;
	Cur_B.y =pB->y;
	Deskew (Cur_B, -Skew);
	/*---------------------------------*/
	Lev_A = Cur_A.y;
	Lev_B = Cur_B.y;
	Lev = pRc->top;
	ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, FALSE, NearHor);
	if (!ret)
		return ret;
	Cur_A.x =pA->x;
	Cur_A.y =pA->y;
	Deskew (Cur_A, -Skew);
	Lev_A = Cur_A.y;
	Lev = pRc->bottom;
	ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, TRUE, NearHor);
	if (!ret)
		return ret;
	Cur_B.x =pB->x;
	Cur_B.y =pB->y;
	Deskew (Cur_B, -Skew);
	/*---------------------------------*/
	Lev_A = Cur_A.x;
	Lev_B = Cur_B.x;
	Lev = pRc->left;
	ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, FALSE, NearVer);
	if (!ret)
		return ret;
	Cur_A.x =pA->x;
	Cur_A.y =pA->y;
	Deskew (Cur_A, -Skew);
	Lev_A = Cur_A.x;
	Lev = pRc->right;
	ret = CanUse (pA, pB, Lev, Lev_A, Lev_B, TRUE, NearVer);
	if (!ret)
		return ret;
	/*---------------------------------*/
	return TRUE;
}
/*----------------------------------------------------------------------------*/
Bool IsRectsCross (Rect16 *pRc1, Rect16 *pRc2)
{
	if (pRc1->left > pRc2->right)
		return FALSE;
	if (pRc2->left > pRc1->right)
		return FALSE;
	if (pRc1->top  > pRc2->bottom)
		return FALSE;
	if (pRc2->top  > pRc1->bottom)
		return FALSE;
	return TRUE;
}
/*----------------------------------------------------------------------------*/
Bool MakeInternalRectId (Rect16 *pRcRe, Rect16 *pRcId, Int32 Skew)
{
	Point32 LefTop, RigTop, LefBot, RigBot;
	if ((Skew>512)||(Skew<-512))
		return FALSE;
	if (pRcRe->right - pRcRe->left < pRcRe->bottom - pRcRe->top)
		return FALSE;
	LefTop.x = pRcRe->left;
	LefTop.y = pRcRe->top;
	RigTop.x = pRcRe->right;
	RigTop.y = pRcRe->top;
	LefBot.x = pRcRe->left;
	LefBot.y = pRcRe->bottom;
	RigBot.x = pRcRe->right;
	RigBot.y = pRcRe->bottom;
	Deskew (LefTop, -Skew);
	Deskew (RigTop, -Skew);
	Deskew (LefBot, -Skew);
	Deskew (RigBot, -Skew);
	if (Skew>=0)
	{
		pRcId->top    = (Int16)LefTop.y;
		pRcId->bottom = (Int16)RigBot.y;
		pRcId->left   = (Int16)LefBot.x;
		pRcId->right  = (Int16)RigTop.x;
	}
	else
	{
		pRcId->top    = (Int16)RigTop.y;
		pRcId->bottom = (Int16)LefBot.y;
		pRcId->left   = (Int16)LefTop.x;
		pRcId->right  = (Int16)RigBot.x;
	}
	if (pRcId->top > pRcId->bottom)
		return FALSE;
	if (pRcId->left > pRcId->right)
		return FALSE;
	return TRUE;
}
/*----------------------------------------------------------------------------*/
