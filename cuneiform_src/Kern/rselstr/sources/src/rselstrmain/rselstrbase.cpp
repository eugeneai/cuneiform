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

#define __RSELSTR__
/*#include <windows.h>*/
#include <setjmp.h>

# include "dpuma.h"
# include "rselstr.h"
# include "resource.h"
# include "newfunc.h"
# include "kernel.h"
# include "pumadef.h"
# include "lhstr.h"

#include "compat_defs.h"

//////////////////////////////////////////////////////////////////GLOBAL VARIABLES
static Word16 gwHeightRC = 0;
static Word32 gwRC = 0;
static HANDLE ghStorage = NULL;
static HINSTANCE ghInst =  NULL;
Handle Root;
Handle VertCells=NULL;
Handle NegaCells=NULL;
Handle hShowCells=NULL;
Handle ShowNegaCells=NULL;
Handle ShowVertCells=NULL;
Handle hShowString;
Handle hDebugCancelPicturesAndTables = NULL;
Handle CutStrPrintFILE=NULL;
Handle hCutStr=NULL;
Handle hDebugCutStr=NULL;
Handle CutStrD=NULL;
Handle DifferenCutToHistory=NULL;
Handle hCutComp=NULL;
Handle CutCompPrintFILE=NULL;
Handle CutCompD=NULL;
Handle DifferenCutCompToHistory=NULL;
Handle MainDebug=NULL;
//Handle hVertCellsWork=NULL;
//Handle hNegaCellsWork=NULL;
Handle hTime=NULL;
//Handle hUseCLine=NULL;
Handle hStrPointedD;
//Handle hStrPointed;
Handle RselstrTime=NULL;
Handle hExit=NULL;
Handle MainTime=NULL;
Handle hDrawComp;


CLhstr* list=NULL;
CLPrepHstr* prelist=NULL;
Handle Root_CHSTR=NULL;
Handle PutToCHSTR;
Handle PutToCSTR;
Handle StrD;
Handle MainWindowD;
Handle CutStrV;
Handle StrPix;
Handle CutStrDel;
Handle SkewFromRLTABLE;
double cut_white=.90;
double cut_str=.85;
double inf_let_black=.2;
int inf_str_h=15;
int inf_str_w=8;

/////////////////////////////////////////


/////////////////////////////////////////
BOOL APIENTRY DllMain( HINSTANCE  hModule, 
                        DWORD ul_reason_for_call, 
                        LPVOID lpReserved )
{
    switch( ul_reason_for_call ) 
	{
    case DLL_PROCESS_ATTACH:
		ghInst = hModule;
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
//////////////////////////////////////////////////////////////////////////////////
//
RSELSTR_FUNC(Bool32) RSELSTR_Init(Word16 wHeightCode,HANDLE hStorage)
{
	gwHeightRC = wHeightCode;
	LDPUMA_Init(0,NULL);
/*------------------------------------------------------------------------------------------*/

//	CHSTR_Init(wHeightCode,NULL);

/*------------------------------------------------------------------------------------------*/

    LDPUMA_Registry(&MainDebug,SNAP_ROOT_MAIN_DEBUG,NULL);
    LDPUMA_Registry(&MainTime,SNAP_ROOT_MAIN_TIME_CONTROL,NULL);

    LDPUMA_Registry(&RselstrTime,"��������� �����..",MainTime);
	LDPUMA_Registry(&hExit,"�� RSELSTR �� �������������",MainTime);
	

//	LDPUMA_Registry(&hVertCellsWork,"��������� ������������ ����� ������",MainDebug);
//    LDPUMA_RegistryHelp(hVertCellsWork,"����������� ������� �������� ��������� ������������ ����� ������.",FALSE);

//	LDPUMA_Registry(&hNegaCellsWork,"��������� ���������� ����� ������",MainDebug);
//    LDPUMA_RegistryHelp(hNegaCellsWork,"����������� ������� �������� ��������� ���������� ����� ������.",FALSE);

	LDPUMA_Registry(&hDebugCutStr,"����� ��������� ��������� �����������",MainDebug);
	LDPUMA_RegistryHelp(hDebugCutStr,"��������� ����� ��������� ��������� �����������",FALSE);

//	LDPUMA_Registry(&hStrPointed,"��������� ������ �������� ����� �� ������",MainDebug);
//    LDPUMA_RegistryHelp(hStrPointed,"����������� ������� �������� ��������� ������ �������� ����� �� ������.",FALSE);


	LDPUMA_Registry(&Root,SNAP_ROOT_STRINGS,NULL);
    LDPUMA_RegVariable(Root,"���������� ������� �������.",&layout,"unsigned char");
	LDPUMA_RegistryHelp(Root,"� ���������� ����� ���������� �������� ������ \
������� �� 5 �� 8. ��� ����������� ������� ������ ����� ���������� ������� RBLOCK.",TRUE);

    
	LDPUMA_Registry(&hShowString,"�������� ���������� ������",Root);
	LDPUMA_RegistryHelp(hShowString,"����� �������� ���������� ������ � ���������� ����������� � ���� ���������������.",FALSE);

	LDPUMA_Registry(&hStrPointedD,"�������� ������ � ������ ������������",Root);
	LDPUMA_RegistryHelp(hStrPointedD,"����� �������� ������ � ������ ������������.",FALSE);

	LDPUMA_Registry(&hShowCells,"�������� ���������� ������ � ������������!",Root);
	LDPUMA_RegistryHelp(hShowCells,"����� �������������� ������ � �������� \
� ��� ����������.",FALSE);


	LDPUMA_Registry(&VertCells,"������ � ������������� �������� ������",NULL);
	LDPUMA_RegistryHelp(VertCells,"������ � ������������� �������� ������",FALSE);

	LDPUMA_Registry(&NegaCells,"������ � ����������� �������� ������",NULL);
	LDPUMA_RegistryHelp(NegaCells,"������ � ����������� �������� ������",FALSE);

	LDPUMA_Registry(&ShowVertCells,"�������� ������������ ������ ������",VertCells);
	LDPUMA_RegistryHelp(ShowVertCells,"����� �������� ������ ������ � ������������ ������������� �����.",FALSE);

	LDPUMA_Registry(&ShowNegaCells,"�������� ���������� ������ ������",NegaCells);
	LDPUMA_RegistryHelp(ShowNegaCells,"����� �������� ���������� ������ ������.",FALSE);

    LDPUMA_Registry(&hCutStr,"����� ��������� ��������� �����������!",Root);
	LDPUMA_RegistryHelp(hCutStr,"������� ����� ��������� ��������� �����������",FALSE);

    LDPUMA_Registry(&CutStrPrintFILE,"������ � ���� ����������� ��������� �����������",hCutStr);
	LDPUMA_RegistryHelp(CutStrPrintFILE,"��������� ������ � ���� cutstr.res ����������� ��������� �����������",FALSE);

    LDPUMA_Registry(&CutStrD,"���������� �������� ����������� �����",hCutStr);
	LDPUMA_RegistryHelp(CutStrD,"��������� ���������� �������� ����������� ����� ��������� ������������",FALSE);

    LDPUMA_Registry(&DifferenCutToHistory,"���������� �������� �������",hCutStr);
	LDPUMA_RegistryHelp(DifferenCutToHistory,"��������� ���������� �������� ������� �� ����������� ��������",FALSE);

    LDPUMA_Registry(&hCutComp,"����� ��������� ���������",Root);
	LDPUMA_RegistryHelp(hCutComp,"��������� ����� ��������� ��������� �� ����������� ����� �������",FALSE);


    LDPUMA_Registry(&CutCompPrintFILE,"������ � ���� ����������� ���������",hCutComp);
	LDPUMA_RegistryHelp(CutCompPrintFILE,"��������� ������ � ���� cutcomp.res ����������� ���������",FALSE);

    LDPUMA_Registry(&CutCompD,"���������� �������� ����������� �����!!",hCutComp);
	LDPUMA_RegistryHelp(CutCompD,"��������� ���������� �������� ����������� ����� ���������",FALSE);

    LDPUMA_Registry(&DifferenCutCompToHistory,"���������� �������� �������!",hCutComp);
	LDPUMA_RegistryHelp(DifferenCutCompToHistory,"��������� ���������� �������� ������� �� ����������� ��������",FALSE);

    LDPUMA_Registry(&hTime,"�������� �������!!!",Root);
	LDPUMA_RegistryHelp(hTime,"��������� �������� �������",FALSE);

    LDPUMA_Registry(&hDrawComp,"���������� ��������� !!!",Root);
	LDPUMA_RegistryHelp(hDrawComp,"���������� ���������.",FALSE);


//	LDPUMA_Registry (&hUseCLine,"������ � ����������� �����",NULL);

 list=NULL;
 prelist=NULL;

// list=new CLhstr;
// prelist=new CLPrepHstr;
 
 LDPUMA_Registry (&Root_CHSTR,"���������� ����� � ������������� ��������", Root);
 char *pText;

 /*  �������� �������  */
 pText = "<������������� ���. �����������> \
 \n �������� ������� ���������� ����� � ������������� ��������.";
 LDPUMA_RegistryHelp (Root_CHSTR, pText, FALSE);

 /*  �������� � ���������*/
 LDPUMA_Registry (&PutToCHSTR,"�������� � ���������", Root_CHSTR);
 pText = "�������� ������ � ��������� ������� �����";
 LDPUMA_RegistryHelp (PutToCHSTR, pText, FALSE);

 /*  ������� ����� �� ������*/
 LDPUMA_Registry (&CutStrV,"����� �� ������",PutToCHSTR);
 pText = "�������������� ����� �������� �� ������";
 LDPUMA_RegistryHelp (CutStrV, pText, FALSE);
 LDPUMA_RegVariable (CutStrV,"cut_white",&cut_white,"double");
 LDPUMA_RegVariable (CutStrV,"cut_str",&cut_str,"double");
 LDPUMA_RegVariable (CutStrV,"inf_let_black",&inf_let_black,"double");
 LDPUMA_RegVariable (CutStrV,"inf_str_h",&inf_str_h,"int");
 LDPUMA_RegVariable (CutStrV,"inf_str_w",&inf_str_w,"int");
 
 /*  �������� � ��������� CSTR*/
 LDPUMA_Registry (&PutToCSTR,"�������� � ��������� CSTR", Root_CHSTR);
 pText = "��������� ������ �� CHSTR � CSTR";
 LDPUMA_RegistryHelp (PutToCSTR, pText, FALSE);

 /*������� ���������� ���������� ������ ��� �����*/
 LDPUMA_Registry (&StrD,"����������� ������", CutStrV);
 pText = "����������� ������, ������� �������� � ������ ������";
 LDPUMA_RegistryHelp (StrD, pText, FALSE);

 /*������� ���������� ������ �������� ��� �����*/
 LDPUMA_Registry (&StrPix,"����������� ������ �������� ��� �����", CutStrV);
 pText = "����������� ������ �������� ��� �����";
 LDPUMA_RegistryHelp (StrPix, pText, FALSE);

 /*������� ������ ��� �����*/
 LDPUMA_Registry (&CutStrDel,"������ ��� �����", CutStrV);
 pText = "������� �� ����������� ����� ��� �����";
 LDPUMA_RegistryHelp (CutStrDel, pText, FALSE);
 

 return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSELSTR_FUNC(Bool32) RSELSTR_Done()
{

/*------------------------------------------------------------------------------------------*/

//	CHSTR_Done();

/*------------------------------------------------------------------------------------------*/
	delete list;
	delete prelist;

	LDPUMA_Done();
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSELSTR_FUNC(Word32) RSELSTR_GetReturnCode()
{
	return gwRC;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSELSTR_FUNC(Int8 *) RSELSTR_GetReturnString(Word32 dwError)
{
return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSELSTR_FUNC(Bool32) RSELSTR_GetExportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;

#define CASE_FUNCTION(a)	case RSELSTR_FN##a:	*(FN##a *)pData = a; break

	switch(dwType)
	{
	CASE_FUNCTION(RSELSTR_ExtractTextStrings);
	CASE_FUNCTION(RSELSTR_PutObjects);
	CASE_FUNCTION(RSELSTR_CutStr);
	CASE_FUNCTION(RSELSTR_RotateRaster);
	CASE_FUNCTION(RSELSTR_UnRotateRect);
	CASE_FUNCTION(RSELSTR_CleanStr);
	CASE_FUNCTION(RSELSTR_TestForVertical);
	CASE_FUNCTION(RSELSTR_CutCompInTableZones);

	default:
		*(Handle *)pData = NULL;
		rc = FALSE;
	}
return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSELSTR_FUNC(Bool32) RSELSTR_SetImportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;

	gwRC = 0;

#define CASE_DATA(a,b,c)	case a: c = *(b *)pData; break
#define CASE_PDATA(a,b,c)	case a: c = (b)pData; break

	switch(dwType)
	{
	 CASE_PDATA(RSELSTR_FNRSELSTR_ProgressStart,	FNRSELSTR_ProgressStart ,fnProgressStart_rsel);
	 CASE_PDATA(RSELSTR_FNRSELSTR_ProgressStep,	FNRSELSTR_ProgressStep,	fnProgressStep_rsel);
	 CASE_PDATA(RSELSTR_FNRSELSTR_ProgressFinish,	FNRSELSTR_ProgressFinish,fnProgressFinish_rsel);	
	 default:
		SetReturnCode_rselstr(IDS_ERR_NOTIMPLEMENT);
		rc = FALSE;
	}

#undef CASE_DATA
#undef CASE_PDATA

return rc;

}

RSELSTR_FUNC(Word32) RSELSTR_SetReturnCode(Word32 rc)
{
return (Word32)(0);
}

void SetReturnCode_rselstr(Word32 rc)
{
Word16 low = (Word16)(rc &  0xFFFF);
Word16 hei = (Word16)(rc >> 16);

	if(hei)
		gwRC = rc;
	else
	{
		if(low - IDS_ERR_NO)
			gwRC = (Word32)(gwHeightRC<<16)|(low - IDS_ERR_NO);
		else
			gwRC = 0;
	}
}

Word32 GetReturnCode_rselstr()
{
Word32 rc = gwRC;
Word16 low = (Word16)(gwRC &  0xFFFF);
Word16 hei = (Word16)(gwRC >> 16);

	if(hei == gwHeightRC || hei == 0)
		rc = low + IDS_ERR_NO;
	
return rc;
}

void EnableDebug()
{
	
# ifdef LT_DEBUG
    switch (layout)
    {
        case 0:  LT_DebugGraphicsLevel = 0;  break;
        case 1:  LT_DebugGraphicsLevel = 1;  break;
        case 2:  LT_DebugGraphicsLevel = 2;  break;
        case 3:  LT_DebugGraphicsLevel = 3;  break;
        case 4:  LT_DebugGraphicsLevel = 4;  break;
        case 5:  LT_DebugGraphicsLevel = 1;  break;
        case 6:  LT_DebugGraphicsLevel = 1;  break;
        case 7:  LT_DebugGraphicsLevel = 1;  break;
        case 8:  LT_DebugGraphicsLevel = 1;  break;
        case 9:  LT_DebugGraphicsLevel = 0;  break;
        case 10: LT_DebugGraphicsLevel = 0;  break;
    }
# endif
# ifdef SE_DEBUG
    switch (layout)
    {
        case 0:  SE_DebugGraphicsLevel = 0;  break;
        case 1:  SE_DebugGraphicsLevel = 0;  break;
        case 2:  SE_DebugGraphicsLevel = 0;  break;
        case 3:  SE_DebugGraphicsLevel = 0;  break;
        case 4:  SE_DebugGraphicsLevel = 0;  break;
        case 5:  SE_DebugGraphicsLevel = 1;  break;
        case 6:  SE_DebugGraphicsLevel = 2;  break;
        case 7:  SE_DebugGraphicsLevel = 3;  break;
        case 8:  SE_DebugGraphicsLevel = 4;  break;
        case 9:  SE_DebugGraphicsLevel = 0;  break;
        case 10: SE_DebugGraphicsLevel = 0;  break;
    }
# endif
# ifdef MA_DEBUG
    switch (layout)
    {
        case 0:  MA_DebugLevel = 0;  break;
        case 1:  MA_DebugLevel = 0;  break;
        case 2:  MA_DebugLevel = 0;  break;
        case 3:  MA_DebugLevel = 0;  break;
        case 4:  MA_DebugLevel = 0;  break;
        case 5:  MA_DebugLevel = 0;  break;
        case 6:  MA_DebugLevel = 0;  break;
        case 7:  MA_DebugLevel = 0;  break;
        case 8:  MA_DebugLevel = 0;  break;
        case 9:  MA_DebugLevel = 1;  break;
        case 10: MA_DebugLevel = 2;  break;
    }
#endif
}

//end of file
