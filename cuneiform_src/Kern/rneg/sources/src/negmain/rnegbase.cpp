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

#define __RNEG__

#include "rneg.h"
#include "rnegbase.h"
#include "compat_defs.h"

double inf_neg_black=.65;
double sup_neg_black_del=.7;
double weak_neg_black_del=.1;

Handle NegRoot;
Handle NegSearch;
Handle NegRec;
Handle NegSearchSize;
Handle NegSize;
Handle NegNorm;
Handle NegCut;
Handle NegCutStr;
Handle NegColor;
Handle NegSearchSizeD;
Handle NegSizeD;
Handle NegNormD;
Handle NegCutD;
Handle NegCutStrD;
Handle NegColorD;
Handle NegRecD;
Handle NegResD;
Handle NegSearchSizeDC;
Handle NegSizeDC;
Handle NegNormDC;
Handle NegCutDC;
Handle NegCutStrDC;
Handle NegColorDC;
Handle NegRecDC;
Handle MainWindowD;
Handle RecOneLetter;
Handle NegPrintFILE;
Handle TestCHSTR;
Handle PutToCHSTR;
Handle PrintResConsole;
Handle SetSkew;
Handle PutToCPage;
Handle hTime;
Handle hShowNegComps;
int TOP;
int BOTTOM;
int LEFT;
int RIGHT;
int VERTICALE;
int NEGATIVE;
int Skew=0;
double inf_prob=.6;
int NegRecTYPEE=0;


BOOL APIENTRY DllMain( HANDLE hModule,
                        DWORD ul_reason_for_call,
                        LPVOID lpReserved )
{
    switch( ul_reason_for_call )
	{
    case DLL_PROCESS_ATTACH:
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		break;
    }
    return TRUE;
}

/*----------------------------------------------------------------------------*/

RNEG_FUNC(Bool32) RNEG_Init(Word16 wHeightCode,Handle parent)
{
 LDPUMA_Init(0,NULL);


 LDPUMA_Registry (&NegRoot,"����� � ������������� ���������", parent);
 const char *pText;
 /*  �������� �������  */
 pText = "<������������� ���. �����������> \
 \n �������� ������� ������� ������ � ������������� ���������.";
 LDPUMA_RegistryHelp (NegRoot, pText, FALSE);
 LDPUMA_RegVariable (NegRoot,"inf_neg_black",&inf_neg_black,"double");
 LDPUMA_RegVariable (NegRoot,"sup_neg_black_del",&sup_neg_black_del,"double");
 LDPUMA_RegVariable (NegRoot,"weak_neg_black_del",&weak_neg_black_del,"double");

 /*������� ������� ���� �������*/
 LDPUMA_Registry (&SetSkew,"������ ���� �������", NegRoot);
 pText = "������ ���� ������� ��������";
 LDPUMA_RegistryHelp (SetSkew, pText, FALSE);
 LDPUMA_RegVariable (SetSkew,"Skew",&Skew,"int");

 /*������� ������*/
 LDPUMA_Registry (&NegSearch,"����� ���������� � ��������", NegRoot);
 pText = "����� ���������� � ��������";
 LDPUMA_RegistryHelp (NegSearch, pText, FALSE);

 /*������� pac����������*/
 LDPUMA_Registry (&NegRec,"������������� ����������� ���������", NegRoot);
 pText = "������������� ����������� ���������";
 LDPUMA_RegistryHelp (NegRec, pText, FALSE);
 LDPUMA_RegVariable (NegRec,"NegRecTYPEE",&NegRecTYPEE,"int");


 /*������� ������ �� ��������*/
 LDPUMA_Registry (&NegSearchSize,"����� �� ��������", NegSearch);
 pText = "����� ���������� � �������� �� ��������";
 LDPUMA_RegistryHelp (NegSearchSize, pText, FALSE);

 /*������� ������ �� ��������*/
 LDPUMA_Registry (&NegSize,"����� �� ��������", NegSearch);
 pText = "����� ���������� � �������� �� ��������";
 LDPUMA_RegistryHelp (NegSize, pText, FALSE);

 /*������� ������������ ��������� ����������*/
 LDPUMA_Registry (&NegNorm,"������������", NegSearch);
 pText = "������������ ��������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegNorm, pText, FALSE);

 /*������� ����� ��������� ����������*/
 LDPUMA_Registry (&NegCut,"�����", NegSearch);
 pText = "����� ��������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegCut, pText, FALSE);

 /*������� ����� �������������*/
 LDPUMA_Registry (&NegCutStr,"����� �������������", NegSearch);
 pText = "����� ��������� ������������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegCutStr, pText, FALSE);

 /*������� ������ �� �������� �����*/
 LDPUMA_Registry (&NegColor,"����� �� �������� �����", NegSearch);
 pText = "����� �� �������� ����� ��������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegColor, pText, FALSE);

 /*������� ���������� ��������� ���������� � �������� �� ��������*/
 LDPUMA_Registry (&NegSearchSizeD,"���������� �� ��������", NegSearchSize);
 pText = "���������� ��������� ���������� � �������� �� ��������";
 LDPUMA_RegistryHelp (NegSearchSizeD, pText, FALSE);

 /*���� �� ��������� ?*/
 LDPUMA_Registry (&NegSearchSizeDC,"�� �������!!!", NegSearchSizeD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegSearchSizeDC, pText, FALSE);

 /*������� ���������� ��������� ���������� � �������� �� ��������*/
 LDPUMA_Registry (&NegSizeD,"������������� ���������� �� ��������", NegSize);
 pText = "���������� ��������� ���������� � �������� �� ��������";
 LDPUMA_RegistryHelp (NegSizeD, pText, FALSE);

/*���� �� ��������� ?*/
 LDPUMA_Registry (&NegSizeDC,"�� �������!!!!", NegSizeD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegSizeDC, pText, FALSE);

 /*������� ���������� ��������������� ���������� � ��������*/
 LDPUMA_Registry (&NegNormD,"���������� ���������������", NegNorm);
 pText = "���������� ��������������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegNormD, pText, FALSE);

 /*���� �� ��������� ?*/
 LDPUMA_Registry (&NegNormDC,"�� ���������!!!", NegNormD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegNormDC, pText, FALSE);

 /*������� ���������� ����������� ���������� � ��������*/
 LDPUMA_Registry (&NegCutD,"���������� �����������", NegCut);
 pText = "���������� ����������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegCutD, pText, FALSE);

 /*���� �� ��������� ?*/
 LDPUMA_Registry (&NegCutDC,"�� ���������!!!!", NegCutD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegCutDC, pText, FALSE);

 /*������� ���������� ����������� ������������� ���������� � ��������*/
 LDPUMA_Registry (&NegCutStrD,"���������� ����������� �������������", NegCutStr);
 pText = "���������� ����������� ������������� ���������� � ��������";
 LDPUMA_RegistryHelp (NegCutStrD, pText, FALSE);

 /*���� �� ��������� ?*/
 LDPUMA_Registry (&NegCutStrDC,"�� ���������!!!!!", NegCutStrD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegCutStrDC, pText, FALSE);

 /*������� ���������� ����� ������ �� �������� �����*/
 LDPUMA_Registry (&NegColorD,"���������� �� �������� �����", NegColor);
 pText = "���������� ���������� � �������� ����� ������ �� �������� �����";
 LDPUMA_RegistryHelp (NegColorD, pText, FALSE);

 /*���� �� ��������� ?*/
 LDPUMA_Registry (&NegColorDC,"�� ���������!!!", NegColorD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegColorDC, pText, FALSE);

 /*������� ���������� ��������� � ��������*/
 LDPUMA_Registry (&NegRecD,"���������� ���������", NegRec);
 pText = "���������� ��������� � ��������";
 LDPUMA_RegistryHelp (NegRecD, pText, FALSE);

 /*���� �� ��������� ?*/
 LDPUMA_Registry (&NegRecDC,"�� �������!!!", NegRecD);
 pText = "���������� ��� ��������";
 LDPUMA_RegistryHelp (NegRecDC, pText, FALSE);

 /*������� ���������� ����������*/
 LDPUMA_Registry (&NegResD,"���������� �������� ����������", NegRoot);
 pText = "���������� �������� ����������";
 LDPUMA_RegistryHelp (NegResD, pText, FALSE);
 PrintResConsole=NegResD;

 /*����� ��������� � ����������� �������� � ��������� ������������*/
 LDPUMA_Registry (&hShowNegComps, "�������� ��������� � ��������� ����", NegResD);
 LDPUMA_RegistryHelp (hShowNegComps, "������ ���������� � ������������ �������� ������������ ��� ���� ����������: �����-����� � ������-����", FALSE);

 /*������� ������ � ���� ����������*/
 LDPUMA_Registry (&NegPrintFILE,"������ � ���� �����������", NegRoot);
 pText = "������ � ���� recneg.res �����������";
 LDPUMA_RegistryHelp (NegPrintFILE, pText, FALSE);

/*������� ������ � ������� ����������*/
/*
 LDPUMA_Registry (&PrintResConsole,"������ � ������� �����������", NegRoot);
 pText = "������ � ������� ����������� ������������� � ������������� ������";
 LDPUMA_RegistryHelp (PrintResConsole, pText, FALSE);
*/
 /*������������ ������� RecogOneLetter*/
 LDPUMA_Registry (&RecOneLetter,"������������ ������� RecogOneLetter", NegRec);
 pText = "������������ ������� RecogOneLetter";
 LDPUMA_RegistryHelp (RecOneLetter, pText, FALSE);

 /*���� ���������� CHSTR*/
 LDPUMA_Registry (&TestCHSTR,"���� ���������� CHSTR", NegRoot);
 pText = "�������� � CHSTR ������ � �����������, ��������� � ������ �������";
 LDPUMA_RegistryHelp (TestCHSTR, pText, FALSE);
 LDPUMA_RegVariable (TestCHSTR,"TOP",&TOP,"int");
 LDPUMA_RegVariable (TestCHSTR,"BOTTOM",&BOTTOM,"int");
 LDPUMA_RegVariable (TestCHSTR,"LEFT",&LEFT,"int");
 LDPUMA_RegVariable (TestCHSTR,"RIGHT",&RIGHT,"int");
 LDPUMA_RegVariable (TestCHSTR,"VERTICALE",&VERTICALE,"int");
 LDPUMA_RegVariable (TestCHSTR,"NEGATIVE",&NEGATIVE,"int");

 /*���� ���������� CHSTR*/
 LDPUMA_Registry (&PutToCHSTR,"���������� ���������� � CHSTR", NegRoot);
 pText = "���������� ���������� ���������� � CHSTR";
 LDPUMA_RegistryHelp (PutToCHSTR, pText, FALSE);

 /*���������� ���������� � CPage*/
 LDPUMA_Registry (&PutToCPage,"���������� ���������� � CPage", NegRoot);
 pText = "���������� ���������� ���������� � CPage";
 LDPUMA_RegistryHelp (PutToCPage, pText, FALSE);
 LDPUMA_RegVariable (PutToCPage,"inf_prob",&inf_prob,"double");

 LDPUMA_Registry (&hTime,"�������� �������!!!!!!", NegRoot);
 pText = "�������� �������!";
 LDPUMA_RegistryHelp (hTime, pText, FALSE);


 return TRUE;
}

/*---------------------------------------------------------------------------*/
RNEG_FUNC(Bool32) RNEG_Done()
{
	LDPUMA_Done();
	return TRUE;
}
/*---------------------------------------------------------------------------*/
RNEG_FUNC(Word32) RNEG_GetReturnCode()
{
	return (Word32)(0);
}
/*---------------------------------------------------------------------------*/
RNEG_FUNC(Int8 *) RNEG_GetReturnString(Word32 dwError)
{
	return NULL;
}
/*---------------------------------------------------------------------------*/
RNEG_FUNC(Bool32) RNEG_GetExportData(Word32 dwType, void * pData)
{


#define CASE_FUNCTION(a)	case RNEG_FN##a:	*(FN##a *)pData = a; break

	switch(dwType)
	{
		CASE_FUNCTION(RNEG_RecogNeg);
		CASE_FUNCTION(RNEG_TestForNegative);

		default:
			*(Handle *)pData = NULL;
			return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*/
RNEG_FUNC(Bool32) RNEG_SetImportData(Word32 dwType, void *pData)
{

	return FALSE;
}
/*----------------------------------------------------------------------------*/
