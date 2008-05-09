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

/**********  ���������  *******************************************************/
/*  �����,                                                                    */
/*  �����������                                                               */
/*  � ���������                                                               */
/*  ������     :  ������� ��������                                            */
/*  ��������   :  08.06.00                                                    */
/*  ����       :  'dll.cpp'                                                   */
/*  ���������� :  ��������� ����������                                        */
/*  ���������� :                                                              */
/*----------------------------------------------------------------------------*/
#define __RSTUFF__

/*#include <windows.h>*/
#include "resource.h"
#include "rstuff.h"
#include "rsfunc.h"
#include "rsmemory.h"
#include "dpuma.h"
#include "pumadef.h"
#include "smetric.h"

#include "rline.h"

#define __RSTUFF_CPP__
#include "rsglobaldata.h"
#undef __RSTUFF_CPP__

#include "compat_defs.h"
//////////////////////////////////////////////////////////////////GLOBAL VARIABLES
struct tagRC16
{
	Word16        gwLowRC;
	Word16        gwHeightRC;
};
union  RCode
{
	tagRC16           RC16;
	Word32            gwRC;
};

static RCode  RC = {0};
static Word16 wHighErrCode=0;

#define RESULT 2

Bool32 gbRSLT = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////
static Handle            ghStorage = NULL;
static Handle            ghInst =  NULL;
Int32             InitCount =  0;
Handle ObvKillLines;
Handle OKL;
Handle Zone;
Handle OrtMove;
Handle hNewLine;
Handle hDotLine;
//Handle hUseCLine;
Handle hAngles;
Handle hCalcMuchSkew;
Handle hTalkMuchSkew;
Handle MainDebug;
Handle InsideKill;
Handle hNotTestAlik;
Handle NotKillPointed;

Handle hMainTime;
Handle hPrep;
Handle hContBigComp;
Handle hSearchLine;
Handle hCalcIncline;
Handle hOrto;
Handle hVerOrNewLine;
Handle hKillLine;
Handle hPrep2;
Handle hKillLineAfter;
Handle hEnd;
Handle hDebugAutoTemplate;
Handle hAutoTemplate1;
Handle hAutoTemplateBC;
Handle hAutoTemplateBCShow;
Handle hAutoTemplateMar;
Handle hAutoTemplateWrite;
Handle hWndTurn=NULL;
Handle hDebugPreprocess;
Handle hDebugPrintResolution;

int KVO=1;
int move;

#undef APIENRTY
#define APIENTRY

extern Word8* Buffer;
extern Word8* WorkMem;
/////////////////////////////////////////
BOOL APIENTRY DllMain( HINSTANCE hModule,
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
RSTUFF_FUNC(Bool32) RSTUFF_Init(Word16 wHeightCode,Handle hStorage)
{

    Bool32 rc = TRUE;

	wHighErrCode = wHeightCode;

	LDPUMA_Init(0, NULL);
//	Buffer=NULL;
//	Buffer=(Word8*)RSTUFFAlloc(BufferSize*sizeof(Word8));
//	if(!Buffer)
//		return FALSE;
//	WorkMem=(Word8*)RSTUFFAlloc(WorkMemSize*sizeof(Word8));
//	if(!WorkMem)
//		return FALSE;

	gLTInfo = (LinesTotalInfo*)RSTUFFAlloc(sizeof(LinesTotalInfo));

   	if(!SMetric_Init (wHeightCode, hStorage))
	{
		return FALSE;
	}

/*    if (!SLINEDOT_Init(PUMA_MODULE_SLINEDOT, hStorage))
    {
        //        SetReturnCode(SLINEDOT_GetReturnCode());
        return FALSE;
    }*/

    rc = RLINE_Init(PUMA_MODULE_RLINE, hStorage);

    if(!rc)
    {
//        SetReturnCode(RLINE_GetReturnCode());
        return FALSE;
	}

    if (rc == RESULT)
        gbRSLT = TRUE;

	DebugInit();

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32)RSTUFF_Done()
{
	if ( gLTInfo )
		RSTUFFFree(gLTInfo);
//	if ( Buffer )
//		RSTUFFFree(Buffer);
//	if ( WorkMem )
//		RSTUFFFree(WorkMem);

	if (!SMetric_Done())
	{
		return FALSE;
	}

/*    if (!SLINEDOT_Done())
    {
        return FALSE;
	}*/

    if (!RLINE_Done())
    {
        return FALSE;
    }

	LDPUMA_Done();

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32)RSTUFF_Reset()
{
	SetReturnCode((Word16)0);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Word32) RSTUFF_GetReturnCode()
{
	return RC.gwRC;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Int8 *) RSTUFF_GetReturnString(Word32 dwError)
{
	Word16 rc = (Word16)(dwError & 0xFFFF);
	static Int8 szBuffer[512];

	if( dwError >> 16 != RC.RC16.gwHeightRC)
		RC.RC16.gwLowRC = IDS_RSTUFF_ERR_NOTIMPLEMENT;

	if( rc >= IDS_RSTUFF_ERR_NO )
		LoadString((HINSTANCE)ghInst,rc,(char *)szBuffer,sizeof(szBuffer));
	else
		return NULL;

	return szBuffer;
}
//////////////////////////////////////////////////////////////////////////////////
//
#define CASE_FUNCTION(a)	case RSTUFF_FN_##a:	*(FNRSTUFF##a *)pData = RSTUFF_##a; break
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_GetExportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;

	RC.gwRC = 0;


	switch(dwType)
	{
	CASE_FUNCTION(RSBinarise);
	CASE_FUNCTION(RSNormalise);
	CASE_FUNCTION(RSLayout);

	default:
		*(Handle *)pData = NULL;
		SetReturnCode((Word16)IDS_RSTUFF_ERR_NOTIMPLEMENT);
		rc = FALSE;
	}

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_SetImportData(Word32 dwType, void * pData)
{
	BOOL rc = FALSE;
	RC.gwRC = 0;

	switch(dwType)
	{
	case RSTUFF_FN_SetProgresspoints:
		rc = SetCBProgressPoints( pData );
		break;
//	case RSTUFF_FN_SetProgressStart:
//		pProgressStart = pData;
//		rc = TRUE;
//		break;
//	case RSTUFF_FN_SetProgressStep:
//		pProgressStep = pData;
//		rc = TRUE;
//		break;
//	case RSTUFF_FN_SetProgressFinish:
//		pProgressFinish = pData;
//		rc = TRUE;
//		break;
//	case RSTUFF_FN_SetInitPRGTIME:
//		pInitPRGTIME = pData;
//		rc = TRUE;
//		break;
	default:
		SetReturnCode((Word16)IDS_RSTUFF_ERR_NOTIMPLEMENT);
		rc = FALSE;
	}

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_RSBinarise( void )
{
	SetReturnCode((Word16)0);

	return Binarise();
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_RSNormalise( PRSPreProcessImage Image,void* vBuff,int Size,void* vWork,int SizeWork )
{
	SetReturnCode((Word16)0);
	SetMainBuff(vBuff,Size);
	SetWorkBuff(vWork,SizeWork);
	Bool32 rc=Normalise( Image );
	ReSetMem();
	return rc;

}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_RSNormVerify( PRSPreProcessImage Image )
{
	SetReturnCode((Word16)0);

	return VerifyN( Image );
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_RSNormRemoveLines( PRSPreProcessImage Image )
{
	SetReturnCode((Word16)0);

	return KillLinesN( Image );
}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_RSLayout( PRSPreProcessImage Image )
{
	SetReturnCode((Word16)0);

	return Layout(Image);
}
//////////////////////////////////////////////////////////////////////////////////
//
void SetReturnCode(Word16 rc)
{
	if (rc==0)
		RC.gwRC=0;
	else
	{
		RC.RC16.gwLowRC = rc;
		RC.RC16.gwHeightRC = wHighErrCode;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
void SetReturnCode(Word32 rc)
{
	RC.gwRC=rc;
//	Word16 low = (Word16)(rc &  0xFFFF);
//	Word16 hei = (Word16)(rc >> 16);
//	if(low > 0 && low != IDS_RSTUFF_ERR_NO)
//		LDPUMA_Console("%s\n",GetModulesString(gwRC));
//
//	if(gwRC == nDebugReturnCode &&
//		nDebugReturnCode)
//			LDPUMA_Stop();
}

void DebugInit (void)
{
	hWndTurn=NULL;
	LDPUMA_Registry(&hMainTime,SNAP_ROOT_MAIN_TIME_CONTROL,NULL);

	LDPUMA_Registry(&hPrep,"����������.",hMainTime);
	LDPUMA_RegistryHelp(hPrep,"�����������.��������� ���������.������������ �����������.",FALSE);
	LDPUMA_Registry(&hSearchLine,"LNS.����� �����.",hMainTime);
	LDPUMA_Registry(&hCalcIncline,"���������� ����� �������..",hMainTime);
	LDPUMA_Registry(&hOrto,"��������� ��������.",hMainTime);
  LDPUMA_Registry(&hContBigComp,"���������� ���������� BigComp",hMainTime);
	LDPUMA_Registry(&hVerOrNewLine,"����������� ��� ������ ������.",hMainTime);
	LDPUMA_Registry(&hKillLine,"������ �����.",hMainTime);
	LDPUMA_Registry(&hPrep2,"����� ������.",hMainTime);
	LDPUMA_RegistryHelp(hPrep2,"��������� ���������.������������ �����������.",FALSE);
	LDPUMA_Registry(&hKillLineAfter,"�������� �����.",hMainTime);
	LDPUMA_Registry(&hEnd,"�� RSTUFF �� RMARKER",hMainTime);

	 LDPUMA_Registry(&MainDebug,SNAP_ROOT_MAIN_DEBUG, NULL );

	 LDPUMA_Registry(&hDebugRoot, SNAP_ROOT_STUFF, NULL);

	LDPUMA_Registry(&hDebugPreprocess, SNAP_STUFF_BINARIZE, hDebugRoot);
	LDPUMA_Registry(&hDebugPrintResolution, "������ ������ ����������", hDebugPreprocess);
	LDPUMA_RegistryHelp(hDebugPrintResolution, "������� �� ������� ����������, �������������� �� �����������, � ������ ��� ������� �� ���������", FALSE);

	LDPUMA_Registry(&hDebugKillLines, SNAP_STUFF_KILL_LINES, hDebugRoot);
    LDPUMA_RegistryHelp(hDebugKillLines,
            "<�������������: A.��������> ����� � �������� ����� � ���������� � ��� ���������."
            ,FALSE);
    LDPUMA_RegVariable(hDebugKillLines,"����� ����������",&gKillComponents,"unsigned");
    LDPUMA_RegVariable(hDebugKillLines,"���� ��������� (� ��������)",&gKillZone,"unsigned");
    LDPUMA_RegVariable(hDebugKillLines,"�������� (0 - 255)",&gKillRate,"unsigned");

    LDPUMA_Registry(&hDebugKillLinesStep,SNAP_KILL_LINES_STEP, hDebugKillLines);
    LDPUMA_RegistryHelp(hDebugKillLinesStep,
            "��������� ������."
            ,FALSE);

    LDPUMA_Registry(&hDebugKillLinesData,SNAP_KILL_LINES_DATA, hDebugKillLines);
    LDPUMA_RegistryHelp(hDebugKillLinesData,
            "���� �� ���� �� �������������"
            ,FALSE);

    LDPUMA_Registry(&hDebugKillLinesShowComponentsBefore,SNAP_KILL_LINES_SHOW_BEFORE, hDebugKillLines);
    LDPUMA_RegistryHelp(hDebugKillLinesData,
            "���������� ���������� �� �������� ���� �����"
            ,FALSE);
    LDPUMA_Registry(&hDebugKillLinesShowComponentsAfter,SNAP_KILL_LINES_SHOW_AFTER, hDebugKillLines);
    LDPUMA_RegistryHelp(hDebugKillLinesData,
            "���������� ���������� ����� �������� ���� �����"
            ,FALSE);

	LDPUMA_Registry(&OKL,"����������� �������� �����" ,hDebugRoot);
    LDPUMA_RegistryHelp(OKL,
            "<������������� ���. �����������> \
              \n �������� ������� ������� ������������ �������� �����\
			  ����������� ������� ������� ������ � ����� ������� �� ��������.",FALSE);

    LDPUMA_Registry(&Zone,"��������� ���",OKL);
    LDPUMA_RegistryHelp(Zone,"��������� ������ ����� �� 2*...",FALSE);
    LDPUMA_RegVariable(Zone,"Height+",&KVO,"int");
    LDPUMA_Registry(&hNotTestAlik,"�� ��������� �����",OKL);
    LDPUMA_RegistryHelp(hNotTestAlik,"�� ��������� �����",FALSE);

//	LDPUMA_Registry(&InsideKill,"�������� ����� �����" ,MainDebug);
//	LDPUMA_RegistryHelp(InsideKill,"��������� �������� ����� �����",FALSE);
	LDPUMA_Registry(&NotKillPointed,"�� ������� �������� �����" ,MainDebug);
	LDPUMA_RegistryHelp(NotKillPointed,"�� ������� �������� �����",FALSE);
	LDPUMA_Registry(&OrtMove,"���� ����������������� ������." ,NULL);
	LDPUMA_Registry(&ObvKillLines,"����������� �������� �����." ,MainDebug);
	LDPUMA_RegistryHelp(ObvKillLines,"��������� ����������� �������� �����.",FALSE);

    LDPUMA_Registry (&hDotLine,"����� �������� �����.", MainDebug);
    LDPUMA_RegistryHelp(hDotLine, "�������� ����� �������� ����� ����������� RShellLines", FALSE);

//    LDPUMA_RegVariable(OrtMove,"�����",&move,"int");

    LDPUMA_Registry (&hNewLine,"����������� �����.",MainDebug);
    LDPUMA_RegistryHelp (hNewLine,"����������� ����� ������ ������� ������� �����", FALSE);
//	LDPUMA_Registry (&hUseCLine,"������ � ����������� �����",NULL);

	LDPUMA_Registry(&hAngles, "���������� �����.",hDebugRoot);
	LDPUMA_RegistryHelp(hAngles, "���������� �����.",FALSE);
	LDPUMA_Registry(&hCalcMuchSkew, "��������� ������ ����.",hAngles);
	LDPUMA_RegistryHelp(hCalcMuchSkew, "��������� ������ ����.", FALSE);
	LDPUMA_Registry(&hTalkMuchSkew, "���������� � ������ �����.",hAngles);
	LDPUMA_RegistryHelp(hTalkMuchSkew, "���������� � ������ �����.", FALSE);
/*-Andrey: moved to RNORM
//-----------------------
	LDPUMA_Registry(&hDebugAutoTemplate,"�������������� ����������� ������� �������������.",hMainTime);
	LDPUMA_RegistryHelp(hDebugAutoTemplate,"�������������� ����������� ������� �������������.",FALSE);
	LDPUMA_Registry(&hAutoTemplate1,"���������.",hDebugAutoTemplate);
	LDPUMA_Registry(&hAutoTemplateWrite,"�������� � ����.",hDebugAutoTemplate);
	LDPUMA_RegistryHelp(hAutoTemplateWrite,"�������� � ����.",FALSE);
	LDPUMA_Registry(&hAutoTemplateBC,"������� ����������.",hDebugAutoTemplate);
	LDPUMA_RegistryHelp(hAutoTemplateBC,"������� ����������.",FALSE);
	LDPUMA_Registry(&hAutoTemplateBCShow,"���������� ������� ���������.",hDebugAutoTemplate);
	LDPUMA_RegistryHelp(hAutoTemplateBCShow,"���������� ������� ���������.",FALSE);
	LDPUMA_Registry(&hAutoTemplateMar,"����.",hDebugAutoTemplate);
	LDPUMA_RegistryHelp(hAutoTemplateMar,"����.",FALSE);
-*/

}
//////////////////////////////////////////////////////////////////////////////////
//
RSTUFF_FUNC(Bool32) RSTUFF_RSSetSpecPrj( Word8 NoSpecPrj)
{
	db_spec_prj = NoSpecPrj;

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////

//end of file
