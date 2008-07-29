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
/*  ��������   :  17.12.99                                                    */
/*  ����       :  'AM_RULE.CPP'                                              */
/*  ���������� :  ������� ������������ ���������� ������� ����������.         */
/*  ���������� :  ������ �� ���������� �����������.                           */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
/*  interface my        */
#include "am_comm.h"
#include "vl_rule.h"
/*------------own objects-----------------------------------------------------*/
/*  ����������� �����  */
static Handle VL_Into;
static Handle VL_I_PrimLines; //+
static Handle VL_I_PrimBoxes; //+
static Handle VL_Out;
static Handle VL_O_VerifLines;//+
static Handle VL_O_CorrLines; //+
static Handle VL_O_ModelLines;
static Handle VL_O_SaveComps; //+
static Handle VL_Control;
static Handle VL_C_ContErr;
static Handle VL_C_ContWarn;
static Handle VL_C_ContRare;
static Handle VL_Upravlenie;
static Handle VL_U_NoPointedLines;
static Handle VL_U_AbleKillShortVert;
static Handle VL_U_NewFormalVerify;
static Handle VL_U_NoInvestLongLines;
static Handle VL_U_NoInvestImage;
static Handle VL_U_AbleHoriZher;
static Handle VL_Debug;
static Handle VL_D_Info;
static Handle VL_D_InvestImage;
static Handle VL_D_WrResLine;
//Handle hUseCLine;
/*----------------------------------------------------------------------------*/
void AM_MakeTreeRules_VerifLines (Handle parent)
{
	char *pText;
/*  �������� �������  */
pText = " \
\n �������� ������� ������ �������� [����������� �����] ���������� 'RLTABLE'. \
\n ��� ����� ��������� ��� �������������� ������� : \
\n   (I) ����������� ���������� ����������� 'RLINE' ����� \
\n  (II) ������������� '���� ������������ �����' ��� ������� ������, ����� \
\n       ����� ���� �������� � ���������� �������� \
\n ��� ������� ��������� �����. \
\n �������� ������� ������� ����� ���� �����: \
\n a) '������� ������' \
\n �) '���������� ������' \
\n �) '�������� ������' \
\n �) '����������' \
\n �) '�������' \
\n ���� �) �) � �) ������������� ��� ������ ������������. ��� ������������ \
������������ � ������� ���� ������ ���������� � ������� � �������� ������ \
����������, � ����� ������ �� ������� ��������� ����������� ������, \
����������� � ������ �������� ��� ���������� ���������. \
\n ���� �) ������������ ��� ���������� ����������� ����������. \
\n ���� �) ������������ ��� ������������ ����������. \
\n Almi 26.05.99";
AM_RegiHelp (parent, pText, TRUE);
	/*  ������ ����  */
	AM_RegiVert (&VL_Into, "������� ������ /��/", parent);
	pText = " \
\n �������� ������� ��� ���� ����� ���������� 'RLTABLE' �������� : \
\n - ����� \
\n - ������� ��������� \
\n Almi 26.05.99";
	AM_RegiHelp (VL_Into, pText, FALSE);
		AM_RegiVert (&VL_I_PrimLines, "����� /��/", VL_Into);
		AM_RegiHelp (VL_I_PrimLines, "�����", FALSE);
		AM_RegiVert (&VL_I_PrimBoxes, "������� ��������� /��/", VL_Into);
		AM_RegiHelp (VL_I_PrimBoxes, "������� ���������", FALSE);
	/*  ������ ����  */
	AM_RegiVert (&VL_Out, "���������� ������ /��/", parent);
	pText = " \
\n ������������ ������ ���� ����� ���������� 'RLTABLE' �������� : \
\n - ������������ ����� ����������� ����� \
\n - ����������������� ����� \
\n - ������ ��������������� ����� \
\n - ��������� ���������� \
\n Almi 29.05.99";
	AM_RegiHelp (VL_Out, pText, FALSE);
		AM_RegiVert (&VL_O_VerifLines, "����������� �����", VL_Out);
		pText = "����������� ����� : \
\n ����� - ��������, ������� - ������, ������ - ������������ ��� ���������������, \
\n ���������� - ������� ������� ���������, ���������� - ���������";
		AM_RegiHelp (VL_O_VerifLines, pText, FALSE);
		AM_RegiVert (&VL_O_CorrLines, "����������������� �����", VL_Out);
		pText = "����������������� ����� : \
\n ��� - ��������� � ��� ����� ������ ����������� �������� � �������� \
\n ������������ �����, ���������� � �������� ��������� ���������.";
		AM_RegiHelp (VL_O_CorrLines, pText, FALSE);
		AM_RegiVert (&VL_O_ModelLines, "(�/�)��������������� �����", VL_Out);
		pText = "��������������� ����� : \
\n ��� - ��� �������������� ������, ���������������  ������ ��������� ����� \
\n ��� ������� ��������.";
		AM_RegiHelp (VL_O_ModelLines, pText, FALSE);
		AM_RegiVert (&VL_O_SaveComps, "������ ����� (��������� ����������)", VL_Out);
		pText = "������ ����� (��������� ����������) : \
\n ��� - ��� ��������� ���������, ������� ��������� ���������� �� ������ \
\n ����������� ���������� �����. �� ������������ ��� ������������� � \
\n ������������ � ������������� �����.";
		AM_RegiHelp (VL_O_SaveComps, pText, FALSE);
	/*  ������ ����  */
	AM_RegiVert (&VL_Control, "�������� ������ /��/", parent);
	AM_RegiHelp (VL_Control, "�������� ������", FALSE);
		AM_RegiVert (&VL_C_ContErr , "�������� ������ /��/", VL_Control);
		AM_RegiHelp (VL_C_ContErr  , "�������� ������", FALSE);
		AM_RegiVert (&VL_C_ContWarn, "�������� ����������� /��/", VL_Control);
		AM_RegiHelp (VL_C_ContWarn , "�������� �����������", FALSE);
		AM_RegiVert (&VL_C_ContRare, "�������� ������ �������� /��/", VL_Control);
		AM_RegiHelp (VL_C_ContRare , "�������� ������ ��������", FALSE);
	/*  ��������� ����  */
	AM_RegiVert (&VL_Upravlenie, "���������� ����������� /��/", parent);
	AM_RegiHelp (VL_Upravlenie, "���������� �����������", FALSE);
		AM_RegiVert (&VL_U_NoPointedLines , "�� ������ �������", VL_Upravlenie);
		AM_RegiHelp (VL_U_NoPointedLines  , "�� ������ �������", FALSE);
		AM_RegiVert (&VL_U_AbleKillShortVert , "����� ����������� �������� ������������", VL_Upravlenie);
		AM_RegiHelp (VL_U_AbleKillShortVert  , "����� ����������� �������� ������������", FALSE);
		AM_RegiVert (&VL_U_NewFormalVerify , "����� ���������� �����������", VL_Upravlenie);
		AM_RegiHelp (VL_U_NewFormalVerify  , "����� ���������� �����������", FALSE);
		AM_RegiVert (&VL_U_NoInvestLongLines, "�������� ����� ����� � ���������", VL_Upravlenie);
		AM_RegiHelp (VL_U_NoInvestLongLines , "�������� ����� ����� � ���������", FALSE);
		AM_RegiVert (&VL_U_NoInvestImage, "�������� �������� ����� � �������� ������", VL_Upravlenie);
		AM_RegiHelp (VL_U_NoInvestImage , "�������� �������� ����� � �������� ������", FALSE);
		AM_RegiVert (&VL_U_AbleHoriZher, "������ ������ �������������� �����", VL_Upravlenie);
		AM_RegiHelp (VL_U_AbleHoriZher , "������ ������ �������������� �����", FALSE);
	/*  ����� ����  */
	AM_RegiVert (&VL_Debug, "������� /��/", parent);
	AM_RegiHelp (VL_Debug, "���� ������������", FALSE);
		AM_RegiVert (&VL_D_Info , "����� ����������", VL_Debug);
		AM_RegiHelp (VL_D_Info  , "����� ����������", FALSE);
		AM_RegiVert (&VL_D_InvestImage , "�������� �� ����", VL_Debug);
		AM_RegiHelp (VL_D_InvestImage  , "�������� �� ����", FALSE);
		AM_RegiVert (&VL_D_WrResLine , "����������� ����������� ������ �����", VL_Debug);
		AM_RegiHelp (VL_D_WrResLine  , "����������� ����������� ������ �����", FALSE);
//	    AM_RegiVert(&hUseCLine,"������ � ����������� �����",NULL);
}
/*----------------------------------------------------------------------------*/
Handle AM_GetKeyOfRule (VL_RULES Code)
{
	switch (Code)
	{
		/*  ����������� �����  */
		case RU_VL_Into :
			return VL_Into;
		case RU_VL_I_PrimLines :
			return VL_I_PrimLines;
		case RU_VL_I_PrimBoxes :
			return VL_I_PrimBoxes;
		case RU_VL_Out :
			return VL_Out;
		case RU_VL_O_VerifLines :
			return VL_O_VerifLines;
		case RU_VL_O_CorrLines :
			return VL_O_CorrLines;
		case RU_VL_O_ModelLines :
			return VL_O_ModelLines;
		case RU_VL_O_SaveComps :
			return VL_O_SaveComps;
		case RU_VL_Control :
			return VL_Control;
		case RU_VL_C_ContErr :
			return VL_C_ContErr;
		case RU_VL_C_ContWarn :
			return VL_C_ContWarn;
		case RU_VL_C_ContRare :
			return VL_C_ContRare;
		case RU_VL_Upravlenie :
			return VL_Upravlenie;
		case RU_VL_U_NoPointedLines :
			return VL_U_NoPointedLines;
		case RU_VL_U_AbleKillShortVert :
			return VL_U_AbleKillShortVert;
		case RU_VL_U_NewFormalVerify :
			return VL_U_NewFormalVerify;
		case RU_VL_U_NoInvestLongLines :
			return VL_U_NoInvestLongLines;
		case RU_VL_U_AbleHoriZher :
			return VL_U_AbleHoriZher;
		case RU_VL_Debug :
			return VL_Debug;
		case RU_VL_D_Info :
			return VL_D_Info;
		case RU_VL_D_InvestImage :
			return VL_D_InvestImage;
		case RU_VL_D_WrResLine :
			return VL_D_WrResLine;
		/*******************/
		case RU_Unknown :
		default :
			return NULL;
	}
}
/*----------------------------------------------------------------------------*/
