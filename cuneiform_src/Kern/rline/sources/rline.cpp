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

// ============================================================================
//
// ============================================================================

#define __RLINE__

#include <stdlib.h>
/*#include <windows.h>*/
#include <memory.h>
/*#include <crtdbg.h>*/
#include <fstream>
#include <stdio.h>
#include <assert.h>

#include "resource.h"
#include "rline.h"
#include "cline.h"
#include "ctiimage.h"
#include "c_types.h"
#include "cpage.h"
#include "lns.h"
#include "dpuma.h"
#include "pumadef.h"
#include "rshelllinescom.h"

#include "compat_defs.h"

Handle    hMainWindow;

Handle    RLINE_Root;

Handle	  hRLINE_Pass1;
Handle	  hRLINE_Pass2;
Handle	  hRLINE_Pass3;

Handle    hMainDebug;

Handle    RLINE_Search;
Handle	  hRLINE_Correct;

Handle	  hRLINE_Search_Debug;
Handle	  hRLINE_Search_Output;
Handle    hRLINE_Search_Output_ShowFrags;
Handle    hRLINE_CorrectOutput;
Handle    hRLINE_CorrectDebug;
Handle    hRLINE_CorrectDebugFrag;
Handle    hRLINE_CorrectControl;
Handle	  hRLINE_CorrectDrawLines;
Handle	  hRLINE_CorrectDrawFrags;
Handle    hRLINE_Pass3_Control;
Handle    hRLINE_Pass3Input;
Handle    hRLINE_Pass3Output;
Handle	  hRLINE_Pass3DrawLines;
Handle	  hRLINE_Pass3DrawFrags;
Handle    RLINE_NoFillgap;
Handle    RLINE_NoHorBorder;
Handle    RLINE_NoVerBorder;
Handle    RLINE_ShowLines;
Handle    RLINE_DeleteAll;
Handle    RLINE_ShowWithoutLines;
Handle    hDotKilledD;
Handle    hWriteLineInFile;
Handle    hWriteLineInFile3;
Handle	  hSkipDelSmallLines;
Handle	  hLinesPass2;
Handle    hPrint1Cr;
Handle    hPrint2Cr;
Handle    hPrint3Cr;
Handle    hPrint4Cr;
Handle    hDrawCrRast;
Handle    hRLINE_Pass2Output;
Handle	  hRLINE_Pass2DrawLines;
Handle	  hRLINE_Pass2DrawFrags;
Handle	  hLinesPass2Debug;
Handle	  hLinesPass2DebugSkipDouble;
Handle    hLinesPass2DebugSkipGlue;
Handle	  hLinesPass2DebugSkipFindLost;
Handle	  hDebugPrintCrossCheck;

Handle	  hDebugDrowTableZone;
Handle	  hDebugDrowFriendLines;
Handle	  hDebugDrowGroupOfExtensibleLines;
Handle	  hDebugDrawLosedVerticalLines;
Handle    hWriteLineInFile2;

Handle    hDebugShortLinesPrint;
Handle    hDebugShortLinesDrawRect;
Handle	  hShowCP;
Handle	  hShowCheckedRects;
Handle	  hPrintCheckedRects;
Handle    hShowCPLines;

Int32 hMinInterval = 10;
Int32 h1Interval = 25;
Int32 h2Interval = 63;
Int32 hMaxInterval = 150;
Int32 hSmallLineLen = 20;
Int32 hLongLineLen = 50;
Int32 hMaxDegreeDiff = 5;
Int32 hMaxShift = 36;
Int32 hRastDelta = 1;
Int32 hRLINE_Pass2Lost1 = 75;
Int32 hRLINE_Pass2Lost2 = 95;
//Handle    hUseCLine;
void *    hTmpDIB;
Word32    HorType;
Word32    VerType;

Handle Parts;
Handle Part2;
Handle Part3;
Handle Exit2;
Handle Exit3;
Handle MainWork2;
Handle MainWork3;
Handle Prep2;
Handle GetContainer3;
Handle PutContainer2;
Handle PutContainer3;
Handle Epilog2;

Bool32 gbNOFILLGAP3 = FALSE;
Bool32 gbNOHBORDER = FALSE;
Bool32 gbNOVBORDER = FALSE;

CIMAGEIMAGECALLBACK         cbk;

Imxs* swp_imxs;
Imxs imxs;


Word16    min_h_len = 40,
	      min_v_len = 40;
Word16	  rc16;
Word32	  rc32;

	//Almi 16.05.01
    int MinHorLenForTrue = 129;//113;//���� 100
	int MinVerLenForTrue = 94;//58; //����  50
//////////////////////////////////////////////////////////////////////////////////////////////

void SetReturnCode_rline( Word32 );
void SetReturnCode_rline( Word16 );
void CleanLineData( void* pdata,int size);


Bool16 SampleImageOpen (CIMAGE_ImageInfo* lpImageInfo)
{ return swp_imxs->f_op( (Imxs_ImageInfo*)lpImageInfo ); };
Word16 SampleImageRead ( PInt8 lpImage, Word16 wMaxSize)
{ return swp_imxs->f_re( (Word8*)lpImage, wMaxSize ); };
Bool16 SampleImageClose ( void )
{ return swp_imxs->f_cl( ); };


Bool16 DibOpen (Imxs_ImageInfo* lpImageInfo)
{ return cbk.CIMAGE_ImageOpen( (CIMAGE_ImageInfo*)lpImageInfo ); };
Int16  DibRead ( Word8* lpImage, Word16 wMaxSize)
{ return cbk.CIMAGE_ImageRead( (PInt8)lpImage, wMaxSize ); };
Bool16 DibClose ( void )
{ return cbk.CIMAGE_ImageClose( ); };



Bool32 RLINE_SubInit ( void )
{
	hMainWindow = LDPUMA_CreateWindow( NULL, NULL );

	LDPUMA_Registry(&hMainDebug,SNAP_ROOT_MAIN_DEBUG,NULL);

	LDPUMA_Registry(&RLINE_Root,SNAP_ROOT_LINES, NULL); // ����������� ������� �������

	LDPUMA_Registry(&hRLINE_Pass1, SNAP_PASS1_LINES, RLINE_Root);
	LDPUMA_Registry(&hRLINE_Pass2, SNAP_PASS2_LINES, RLINE_Root);
	LDPUMA_RegistryHelp(hRLINE_Pass2, "��� ��������� - ���������� II ������", FALSE);
		LDPUMA_RegVariable(hRLINE_Pass2, "���������� (%) ��� �����. �����", &hRLINE_Pass2Lost1, "long");
		LDPUMA_RegVariable(hRLINE_Pass2, "���������� (%) ��� �����. �����", &hRLINE_Pass2Lost2, "long");
	LDPUMA_Registry(&hRLINE_Pass3, SNAP_PASS3_LINES, RLINE_Root);

	LDPUMA_Registry(&RLINE_Search,"����� LNS", hRLINE_Pass1); // ����������� ������� �������
	LDPUMA_RegistryHelp(RLINE_Search,
		"��������� ����� ����� ��������� LNS32.DLL.", FALSE);
	LDPUMA_Registry(&hRLINE_Correct, "��������� ����� LNS", hRLINE_Pass1);
	LDPUMA_RegistryHelp(hRLINE_Correct,
		"��������� �����, ��������� LNS.", FALSE);

	LDPUMA_Registry(&hRLINE_CorrectOutput,"��������� ��������� �����", hRLINE_Correct);
		LDPUMA_Registry(&hRLINE_CorrectDrawLines,"�������� ����������������� ����� (I)", hRLINE_CorrectOutput);
		LDPUMA_Registry(&hRLINE_CorrectDrawFrags,"�������� ��������� ����� (I)", hRLINE_CorrectOutput);
	LDPUMA_Registry(&hRLINE_CorrectDebug,"������� ��������� �����", hRLINE_Correct);
		LDPUMA_Registry(&hRLINE_CorrectDebugFrag, "������������ ������������ �� LNS", hRLINE_CorrectDebug);
		LDPUMA_RegistryHelp(hRLINE_CorrectDebugFrag, "�.�. �� ��������������������� ����� ��� ���������", FALSE);
	LDPUMA_Registry(&hRLINE_CorrectControl,"�������� ��������� �����", hRLINE_Correct);
	LDPUMA_Registry(&Part2,"������������ ��������� �����", hRLINE_Correct);

	LDPUMA_Registry(&hRLINE_Pass3Input,"������� ������ III �������", hRLINE_Pass3);
	LDPUMA_Registry(&hRLINE_Pass3Output,"��������� III �������", hRLINE_Pass3);
		LDPUMA_Registry(&hRLINE_Pass3DrawLines,"�������� ����� (III)", hRLINE_Pass3Output);
		LDPUMA_Registry(&hRLINE_Pass3DrawFrags,"�������� ��������� ����� (III)", hRLINE_Pass3Output);
	LDPUMA_Registry(&hRLINE_Pass3_Control,"�������� �������� �������",hRLINE_Pass3);
	LDPUMA_Registry(&Part3,"������������ �������� �������",hRLINE_Pass3);

	LDPUMA_Registry(&hRLINE_Search_Output, "��������� LNS", RLINE_Search);
	LDPUMA_Registry(&hRLINE_Search_Debug, "������� LNS", RLINE_Search);

	//LDPUMA_Registry(&RLINE_NoFillgap,"�� ��������� '������������' �����", RLINE_Root); // ����������� ������� �������
	LDPUMA_Registry(&RLINE_NoFillgap,"��������� '������������' �����", hRLINE_Search_Debug); // ����������� ������� �������
	LDPUMA_RegistryHelp(RLINE_NoFillgap,
		"��� '�������������' ���������� ��������� ������� ����� �� 3 �������. ���� ����� ������������ \
��� ������ � ������������ �� ���������� ��������.", FALSE);
	//LDPUMA_Registry(&RLINE_NoHorBorder,"�� �������� �������������� ����", RLINE_Root); // ����������� ������� �������
	LDPUMA_Registry(&RLINE_NoHorBorder,"�������� �������������� ����", hRLINE_Search_Debug); // ����������� ������� �������
	LDPUMA_RegistryHelp(RLINE_NoHorBorder,
		"����������� ������ ��������� ��������� �������� �����������", FALSE); // ����������� ������� �������
	//LDPUMA_Registry(&RLINE_NoVerBorder,"�� �������� ������������ ����", RLINE_Root); // ����������� ������� �������
	LDPUMA_Registry(&RLINE_NoVerBorder,"�������� ������������ ����", hRLINE_Search_Debug); // ����������� ������� �������
	LDPUMA_RegistryHelp(RLINE_NoVerBorder,
		"����������� ������ ��������� ��������� �������� �����������", FALSE); // ����������� ������� �������

	LDPUMA_Registry(&RLINE_ShowLines,"���������� ����� ����� ���������", hRLINE_Search_Output); // ����������� ������� �������
	LDPUMA_RegistryHelp(RLINE_ShowLines,
		"���������� ����� ����� ���������", FALSE); // ����������� ������� �������
	LDPUMA_Registry(&hRLINE_Search_Output_ShowFrags,"���������� ��������� ����� LNS", hRLINE_Search_Output); // ����������� ������� �������
	LDPUMA_RegistryHelp(hRLINE_Search_Output_ShowFrags,
		"���������� ��������� ����� ����� ��������� (��������, ���� ��� ��������� ����� �� ������ ������� ������������ ������������ LNS)", FALSE); // ����������� ������� �������

	LDPUMA_Registry(&hWriteLineInFile, "������ ����� ����� ���������", hRLINE_CorrectControl);
    LDPUMA_RegistryHelp(hWriteLineInFile, "�������� ���������� ������� ������� � ���� lines.res", FALSE);

    LDPUMA_Registry(&hWriteLineInFile3, "������ ����������� ������ �������� ������� �� ������", hRLINE_Pass3_Control);
    LDPUMA_RegistryHelp(hWriteLineInFile3, "�������� ���������� �������� ������� � ���� lines3.res", FALSE);

	/*	//������� ���������� � RStuff
	LDPUMA_Registry(&RLINE_ShowWithoutLines,"�������� ����������� ����� ������ �����", RLINE_Root); // ����������� ������� �������
	LDPUMA_RegistryHelp(RLINE_ShowWithoutLines,
		"�������� ����������� ����� ������ �����", FALSE); // ����������� ������� �������
*/
//    LDPUMA_Registry (&hUseCLine,"������ � ����������� �����",NULL);
/*
	LDPUMA_Registry(&Parts,"������������ ������� � �������� �������",RLINE_Root);
	LDPUMA_RegistryHelp(Parts,"������������ ������� � �������� ������� �� ������",FALSE);
*/
//	LDPUMA_Registry(&Part2,"������ ������",Parts);
	LDPUMA_Registry(&Prep2,"���������������� ����� (2)",Part2);
	LDPUMA_Registry(&MainWork2,"�������������� ����� (2)",Part2);
	LDPUMA_Registry(&PutContainer2,"������� � ��������� (2)",Part2);
    LDPUMA_Registry(&Epilog2,"������ (2)",Part2);
	LDPUMA_Registry(&Exit2,"����� �� ������� (2)",Part2);

//	LDPUMA_Registry(&Part3,"������ ������",Parts);
	LDPUMA_Registry(&GetContainer3,"������ �� ���������� (3)",Part3);
	LDPUMA_Registry(&MainWork3,"�������������� ����� (3)",Part3);
	LDPUMA_Registry(&PutContainer3,"������� � ��������� (3)",Part3);
	LDPUMA_Registry(&Exit3,"����� �� ������� (3)",Part3);

	//Almi 16.05.01
    LDPUMA_RegVariable(hRLINE_Correct,"������������ ������ ��������",&MinHorLenForTrue,"unsigned");
    LDPUMA_RegVariable(hRLINE_Correct,"������������ ������ ��������",&MinVerLenForTrue,"unsigned");

	LDPUMA_Registry(&hDotKilledD,"���������� �������� �������� �����", hRLINE_CorrectControl);
	LDPUMA_RegistryHelp(hDotKilledD,"���������� �������� �������� �����", FALSE);

	LDPUMA_Registry(&hSkipDelSmallLines, "�� ������� ��������� ������� �����", hRLINE_CorrectDebug);
	LDPUMA_RegistryHelp(hSkipDelSmallLines, "��������� � ���������� �������� (������ ������ 30) ���������� �� ����� �������", FALSE);

	LDPUMA_Registry(&hRLINE_Pass2Output,"��������� II �������", hRLINE_Pass2);
		LDPUMA_Registry(&hRLINE_Pass2DrawLines,"�������� ����� (II)", hRLINE_Pass2Output);
		LDPUMA_Registry(&hRLINE_Pass2DrawFrags,"�������� ��������� ����� (II)", hRLINE_Pass2Output);
	LDPUMA_Registry(&hLinesPass2, "�������� II ������� �� ������", hRLINE_Pass2);
	LDPUMA_RegistryHelp(hLinesPass2, "��� ��������� - ���������� II ������", FALSE);
	LDPUMA_Registry(&hLinesPass2Debug, "������� II ������� �� ������", hRLINE_Pass2);
		LDPUMA_Registry(&hLinesPass2DebugSkipDouble, "���������� ��������� �������", hLinesPass2Debug);
		LDPUMA_Registry(&hLinesPass2DebugSkipGlue, "���������� ������� �����", hLinesPass2Debug);
		LDPUMA_Registry(&hLinesPass2DebugSkipFindLost, "���������� �������������� ����������", hLinesPass2Debug);

	    LDPUMA_Registry(&hWriteLineInFile2, "������ ����������� ������ ������� ������� �� ������", hLinesPass2);
		LDPUMA_RegistryHelp(hWriteLineInFile2, "�������� ���������� ������� ������� � ���� lines2.res", FALSE);

	LDPUMA_RegVariable(hRLINE_Pass2, "����������� �������� ����� �������", &hMinInterval, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "������ �������� ����� �������", &h1Interval, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "������ �������� ����� �������", &h2Interval, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "������������ �������� ����� �������", &hMaxInterval, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "����� ��������� �����", &hSmallLineLen, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "����� ������� �����", &hLongLineLen, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "������������ �������� ���� ������� (� ����� ����� �������)", &hMaxDegreeDiff, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "������������ ������� ����� (� ��������)", &hMaxShift, "unsigned");
	LDPUMA_RegVariable(hRLINE_Pass2, "���������� ������", &hRastDelta, "unsigned");

	LDPUMA_Registry(&hPrint1Cr, "������ �������� 1 ��������", hLinesPass2);
	LDPUMA_RegistryHelp(hPrint1Cr, "������ � ������� ����������� �������� 1 �������� (� ������ ������)", FALSE);
	LDPUMA_Registry(&hPrint2Cr, "������ �������� 2 ��������", hLinesPass2);
	LDPUMA_RegistryHelp(hPrint2Cr, "������ � ������� ����������� �������� 2 �������� (� ������ ������)", FALSE);
	LDPUMA_Registry(&hPrint3Cr, "������ �������� 3 ��������", hLinesPass2);
	LDPUMA_RegistryHelp(hPrint3Cr, "������ � ������� ����������� �������� 3 �������� (� ������ ������)", FALSE);
	LDPUMA_Registry(&hPrint4Cr, "������ �������� 4 ��������", hLinesPass2);
	LDPUMA_RegistryHelp(hPrint4Cr, "������ � ������� ����������� �������� 4 �������� (� ������ ������)", FALSE);
	LDPUMA_Registry(&hDrawCrRast, "�������� ����� ����� �������", hLinesPass2);
	LDPUMA_RegistryHelp(hDrawCrRast, "�������� ����� ����� ������� ��� �������� ����������", FALSE);
	LDPUMA_Registry(&hShowCPLines, "�������� ����� ����� ���������������", hLinesPass2);
	LDPUMA_RegistryHelp(hShowCPLines, "�������� ����� ����� ��������������� �� ������ � �������� ����", FALSE);
	LDPUMA_Registry(&hShowCP, "�������� ����� �����������", hLinesPass2);
	LDPUMA_RegistryHelp(hShowCP, "�������� ����� ����������� ����� � �������� ����", FALSE);
	LDPUMA_Registry(&hShowCheckedRects, "�������� ����������� ���������", hLinesPass2);
	LDPUMA_RegistryHelp(hShowCheckedRects, "�������� ����������� �������������� ����������-���������� �� �������������� � �������� ����", FALSE);
	LDPUMA_Registry(&hPrintCheckedRects, "������ �������� ����������", hLinesPass2);
	LDPUMA_RegistryHelp(hPrintCheckedRects, "�������� � ������� ���������� �������� ���������� ��������������� ����������-���������� �� ��������������", FALSE);

  	LDPUMA_Registry(&hDebugDrowTableZone,"�������� ���� ������ ����� II �������",hRLINE_Pass3Input);
	LDPUMA_Registry(&hDebugDrowFriendLines,"�������� �����, �������� � ���� ������",hRLINE_Pass3_Control);
	LDPUMA_Registry(&hDebugDrowGroupOfExtensibleLines,"�������� ������ �����(������� ����� ������� ����� �����) � �������� ����",hRLINE_Pass3_Control);
	LDPUMA_Registry(&hDebugDrawLosedVerticalLines,"�������� ������ ������������ �����(������� � ������ ������ LNS-�� ����� ���������������) � �������� ����",hRLINE_Pass3_Control);
	LDPUMA_Registry(&hDebugPrintCrossCheck,"������ �������� ����� ����������� ���. �����", hRLINE_Pass3_Control);

	LDPUMA_Registry(&hDebugShortLinesPrint, "����� ����������� �������� �������� ����� �� �������", hRLINE_CorrectControl);
//	LDPUMA_Registry(&hDebugShortLinesDrawRect, "�������� �������������� �������� �����", hRLINE_CorrectControl);
//  LDPUMA_RegistryHelp(hDebugShortLinesDrawRect, "�������� �������������� ������� ����� ��� ���������� �� ���������", FALSE);

#ifdef _DEBUG
/*    ofstream outfile("lines.res", ios::out|ios::binary);
    if (outfile) outfile.close();
*/
	int err_no;
	if (remove("lines.res") == -1) err_no = errno;
	if (remove("lines.txt") == -1) err_no = errno;
	remove("lines2.res");
	remove("lines3.res");
#endif

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////

Bool32 RLINE_SearchLines( void* lpInPage,void* phCLINE)
{

	CLINE_handle* PHCLINE=(CLINE_handle*)phCLINE;
    CLINE_DeleteContainer(*PHCLINE);
	LinesTotalInfo          lti;		 // ��������� �������� �����
	PAGEINFO                PInfo;  	 // �������� ��������
	char*		            pImage;	     // ��������� �� �����������
//	Handle				    pBlock;		 // ��������� �� ����
	LnsSetupStr				ls;

//	Word32 tmpw32;
	Int32  result_h_count,
		   result_v_count;

	// �������� PAGEINFO ������� ��������
	if (!CPAGE_GetPageData( lpInPage,PT_PAGEINFO,(void*)&PInfo,sizeof(PInfo)))
	{
		LDPUMA_Console( " Error in GetPageData " );
		rc32 = CPAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	// �������� � pImage �� PInfo ��������� �� �����������, ��������� �� ���������
	pImage = (char*)&PInfo.szImageName;

	min_h_len = (Word16)(PInfo.DPIX*40/300);
	min_v_len = (Word16)(PInfo.DPIY*40/300);

///////////////////////////////////////////////////////////////////////////////////////////////
    /*
	LDPUMA_MessageBoxOk (" Please load DIB in MAIN window \n and set all settings");
	if (!(hTmpDIB = LDPUMA_GetDIBptr( NULL )))
	{
		LDPUMA_Console( " Can't get ptr from MAIN window (error) " );
		//rc32 = DPUMA_GetErrorCode();
		SetReturnCode( rc32 );
		return FALSE;
	}

	if (!CIMAGE_WriteDIB( pImage, hTmpDIB, 0 ))
	{
		LDPUMA_Console( " Error in WriteDIB " );
		rc32 = CIMAGE_GetReturnCode();
		SetReturnCode( rc32 );
		return FALSE;
	}*/
///////////////////////////////////////////////////////////////////////////////////////////////

	if (!CIMAGE_GetCallbackImage( (PWord8)pImage, &cbk))
	{
		LDPUMA_Console( " Error in GetCallbackImage " );
		rc32 = CIMAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	imxs.f_op = DibOpen;								// �� �� ����� �� �� ������ �������� ������
	imxs.f_re = DibRead;								// � ���� �� ���� � CIMAGE � LNS32 ���������
	imxs.f_cl = DibClose;								// imxs->... cbk->... ����� �������������� �����.


	// �������������� ��������
	LnsPageStart(&imxs);

	// ��������� ���������� ������ LNS32.dll
	ls.nOptions = 0;
	LnsSetup ( &ls );

	if ( !LDPUMA_Skip(RLINE_NoFillgap) )
	{
		gbNOFILLGAP3 = TRUE;
	}
	else
	{
		gbNOFILLGAP3 = FALSE;
	}
	ls.nOptions |= gbNOFILLGAP3 ? 0 : LSS_NOFILLGAP3_FILTER;

	if ( !LDPUMA_Skip(RLINE_NoHorBorder) )
	{
		gbNOHBORDER = TRUE;
	}
	else
	{
		gbNOHBORDER = FALSE;
	}
	ls.nOptions |= gbNOHBORDER ? 0 : LSS_NOHBORDER_FILTER;

	if ( !LDPUMA_Skip(RLINE_NoVerBorder) )
	{
		gbNOVBORDER = TRUE;
	}
	else
	{
		gbNOVBORDER = FALSE;
	}
	ls.nOptions |= gbNOVBORDER ? 0 : LSS_NOVBORDER_FILTER;

	LnsSetup ( &ls );


	// ��������...
	if (!LnsExtractLines( min_h_len, min_v_len, &result_h_count, &result_v_count ))
	{
		//rc16 = LnsGetError ();
		SetReturnCode_rline( rc16 );
        CLINE_DeleteContainer(*PHCLINE);
        *PHCLINE = CLINE_CreateContainer(TRUE);
		return FALSE;
	}

	if (result_h_count)
    {
      lti.Hor.Lns = (LineInfo*)malloc(result_h_count * sizeof(LineInfo));
      if (lti.Hor.Lns == NULL)
	  {
		  SetReturnCode_rline( rc16 );
		  return FALSE;
	  }
	}
	else lti.Hor.Lns = NULL;
    lti.Hor.Cnt = result_h_count;

	if (result_v_count)
	{
      lti.Ver.Lns = (LineInfo*)malloc(result_v_count * sizeof(LineInfo));
      if (lti.Ver.Lns == NULL)
	  {
		  SetReturnCode_rline( rc16 );
		  return FALSE;
	  }
	}
	else lti.Ver.Lns = NULL;
    lti.Ver.Cnt = result_v_count;

	if (!LnsUpload( &lti, min_h_len, min_v_len ))
	{
		SetReturnCode_rline( rc16 );
		return FALSE;
	}

	if(!LDPUMA_Skip(RLINE_ShowLines))
	{
        Handle draw_window = LDPUMA_GetWindowHandle (NAME_IMAGE_ORTOMOVE);
		if (!draw_window) draw_window = LDPUMA_GetWindowHandle (PUMA_IMAGE_TURN);
        if (!draw_window) draw_window = LDPUMA_CreateWindow(NULL, NULL);

        Word32 x = 255<<8;
		Int32 temp;
		int i;
		for(i=0;i<lti.Hor.Cnt;i++)
		{
			temp = (-100)*lti.Hor.Lns[i].Thickness;
			_ASSERT(lti.Hor.Lns[i].Thickness>0);
			LDPUMA_DrawLine(draw_window, &lti.Hor.Lns[i].A, &lti.Hor.Lns[i].B, 0, x, (WORD)temp, 512);
		}
		for(i=0;i<lti.Ver.Cnt;i++)
		{
			temp = (-100)*lti.Ver.Lns[i].Thickness;
			_ASSERT(lti.Ver.Lns[i].Thickness>0);
			LDPUMA_DrawLine(draw_window, &lti.Ver.Lns[i].A, &lti.Ver.Lns[i].B, 0, x, (WORD)temp, 512);
		}
		if (lti.Hor.Cnt || lti.Ver.Cnt)
        {
            LDPUMA_Console("������� ����� �������...\n");
		    LDPUMA_WaitUserInput(RLINE_ShowLines, draw_window );
            LDPUMA_DeleteLines(draw_window, 512);
        }
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
   int i;

//   if(!LDPUMA_Skip(hUseCLine))
//   {
	CLINE_handle hCLINE=CLINE_CreateContainer(TRUE);
	if(!hCLINE)
		return FALSE;
	CLINE_handle hline;
	DLine data;
	int size_line=sizeof(DLine);
	LineInfo* linfo;
    for(i=0;i<lti.Hor.Cnt;i++)
	{
	 hline=CLINE_AddNewLine(hCLINE);
	 if(!hline)
	 {
		 CLINE_DeleteContainer(hCLINE);
		 return FALSE;
	 }
	 linfo=&(lti.Hor.Lns[i]);
	 CleanLineData(&data,size_line);
	 data.ProcessingType=HorizantalLine;
	 data.Line.Beg_X=linfo->A.x;
     data.Line.Beg_Y=linfo->A.y;
	 data.Line.End_X=linfo->B.x;
	 data.Line.End_Y=linfo->B.y;
	 data.Line.Wid10=linfo->Thickness*10;
	 data.Dens=(linfo->Quality*100)/255;
	 data.Flags=linfo->Flags;
	 data.n_event=linfo->SegCnt;
	 data.Dir=LD_Horiz;

	 if(!CLINE_SetLineData(hline,(CPDLine)(&data)))
	 {
		 CLINE_DeleteContainer(hCLINE);
		 return FALSE;
	 }

	}
    for(i=0;i<lti.Ver.Cnt;i++)
	{
	 hline=CLINE_AddNewLine(hCLINE);
	 if(!hline)
	 {
		 CLINE_DeleteContainer(hCLINE);
		 return FALSE;
	 }
	 linfo=&(lti.Ver.Lns[i]);
	 CleanLineData(&data,size_line);

	 data.Line.Beg_X=linfo->A.x;
     data.Line.Beg_Y=linfo->A.y;
	 data.Line.End_X=linfo->B.x;
	 data.Line.End_Y=linfo->B.y;
	 data.Line.Wid10=linfo->Thickness*10;
	 data.Dens=(linfo->Quality*100)/255;
	 data.n_event=linfo->SegCnt;
	 data.Flags=linfo->Flags;
	 data.Dir=LD_Verti;
	 data.ProcessingType=VerticalLine;

	 if(!CLINE_SetLineData(hline,(CPDLine)(&data)))
	 {
		 CLINE_DeleteContainer(hCLINE);
		 return FALSE;
	 }
	}
    *PHCLINE=hCLINE;

	if (!LDPUMA_Skip(hRLINE_CorrectDebugFrag))
	{
		ExtractAllEvents(hCLINE, &lti);

 		if (!LDPUMA_Skip(hRLINE_Search_Output_ShowFrags))
			DrawFragsForAllLines(hCLINE, hRLINE_Search_Output_ShowFrags);
	}

	if(lti.Hor.Lns) free(lti.Hor.Lns);
	if(lti.Ver.Lns) free(lti.Ver.Lns);

/*   }
   else
   {
	// ������� �����
	HorType = CPAGE_GetUserBlockType();
	VerType = CPAGE_GetUserBlockType();

	tmpw32 = sizeof(LineInfo);
	for(i=0;i<lti.Hor.Cnt;i++)
	{
		pBlock = CPAGE_CreateBlock( lpInPage, HorType, 0, 0, (void**)&lti.Hor.Lns[i] , tmpw32);
		if (!pBlock)
		{
			LDPUMA_Console( " Error in CreateBlock " );
			rc32 = CPAGE_GetReturnCode();
			SetReturnCode( rc32 );
			return FALSE;
		}
	}

	for(i=0;i<lti.Ver.Cnt;i++)
	{
		pBlock = CPAGE_CreateBlock( lpInPage, VerType, 0, 0, (void**)&lti.Ver.Lns[i] , tmpw32);
		if (!pBlock)
		{
			LDPUMA_Console( " Error in CreateBlock " );
			rc32 = CPAGE_GetReturnCode();
			SetReturnCode_rline( rc32 );
			return FALSE;
		}
	}

	if(lti.Hor.Lns) free(lti.Hor.Lns);
	if(lti.Ver.Lns) free(lti.Ver.Lns);


	lti.Hor.Lns = (LineInfo*)HorType;
	lti.Ver.Lns = (LineInfo*)VerType;
//////////////////////////////////////////////////////////////////////////////////////////////////

	tmpw32 = sizeof(LinesTotalInfo);
	pBlock = CPAGE_CreateBlock( lpInPage, RLINE_BLOCK_TYPE, 0, 0, (void**)&lti , tmpw32);
	if (!pBlock)
	{
		LDPUMA_Console( " Error in CreateBlock " );
		rc32 = CPAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}
   }
*/
	// ��������� ������ �� ���������
	LnsPageFinish();


	if ( !LDPUMA_Skip(RLINE_Search) )
	{
		LDPUMA_Console("��������� ����� ����������� SerachLines");
		LDPUMA_WaitUserInput(RLINE_Search,NULL);
	}


	return TRUE;
}



Bool32 RLINE_DeleteLines(void* lpInPage , char* lpOutDIB)
{

//	LinesTotalInfo        lti;		 // ��������� �������� �����
	LinesTotalInfo		  lti2;
	PAGEINFO              PInfo;	 // �������� ��������
	char*		          pImage;	 // ��������� �� �����������
	LnsSetupStr			  ls;
//	Handle                pBlock;
//	Word32				  size32;
	int					  i;


	Int32  result_h_count,
		   result_v_count;
	Bool DelAllLines;
	DelAllLines = FALSE;
	CLINE_handle hCLINE=CLINE_GetMainContainer();
	//DelAllLines = !LDPUMA_Skip(RLINE_DeleteAll);



	// �������� PAGEINFO ������� ��������
	if (!CPAGE_GetPageData( lpInPage,PT_PAGEINFO,(void*)&PInfo,sizeof(PInfo)))
	{
		LDPUMA_Console( " Error in GetPageData " );
		rc32 = CPAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	// �������� � pImage �� PInfo ��������� �� �����������,
	// ��������� �� ���������
	pImage = (char*)&PInfo.szImageName;

	min_h_len = (Word16)(PInfo.DPIX*40/300);
	min_v_len = (Word16)(PInfo.DPIY*40/300);

/*   if(LDPUMA_Skip(hUseCLine))
   {
	pBlock = CPAGE_GetBlockFirst ( lpInPage, RLINE_BLOCK_TYPE );
	if ( pBlock == NULL)
	{
		LDPUMA_Console( " Error in GetBlockFirst " );
		rc32 = CPAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	size32 = CPAGE_GetBlockData( lpInPage, pBlock, RLINE_BLOCK_TYPE, &lti, sizeof(LinesTotalInfo));
	if (size32 != sizeof(LinesTotalInfo) )
	{
		rc32 = CPAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	HorType = (Word32)lti.Hor.Lns;
	VerType = (Word32)lti.Ver.Lns;
   }
*/
	if (!CIMAGE_GetCallbackImage((PWord8) pImage, &cbk))
	{
		LDPUMA_Console( " Error in GetCallbackImage " );
		rc32 = CIMAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	imxs.f_op = DibOpen;								// �� �� ����� �� �� ������ �������� ������
	imxs.f_re = DibRead;								// � ���� �� ���� � CIMAGE � LNS32 ���������
	imxs.f_cl = DibClose;								// imxs->... cbk->... ����� �������������� �����.

	// �������������� ��������
	LnsPageStart(&imxs);

	// ��������� ���������� ������ LNS32.dll
	ls.nOptions = 0;
	LnsSetup ( &ls );

	if ( !LDPUMA_Skip(RLINE_NoFillgap) )
	{
		gbNOFILLGAP3 = TRUE;
	}
	else
	{
		gbNOFILLGAP3 = FALSE;
	}
	ls.nOptions |= gbNOFILLGAP3 ? 0 : LSS_NOFILLGAP3_FILTER;

	if ( !LDPUMA_Skip(RLINE_NoHorBorder) )
	{
		gbNOHBORDER = TRUE;
	}
	else
	{
		gbNOHBORDER = FALSE;
	}
	ls.nOptions |= gbNOHBORDER ? 0 : LSS_NOHBORDER_FILTER;

	if ( !LDPUMA_Skip(RLINE_NoVerBorder) )
	{
		gbNOVBORDER = TRUE;
	}
	else
	{
		gbNOVBORDER = FALSE;
	}
	ls.nOptions |= gbNOVBORDER ? 0 : LSS_NOVBORDER_FILTER;

	LnsSetup ( &ls );

	//��������...
	if (!LnsExtractLines( min_h_len, min_v_len, &result_h_count, &result_v_count ))
	{
		SetReturnCode_rline( rc16 );
		return FALSE;
	}

	if (result_h_count)
    {
      lti2.Hor.Lns = (LineInfo*)malloc(result_h_count * sizeof(LineInfo));
      if (lti2.Hor.Lns == NULL)
      {
		  SetReturnCode_rline( rc16 );
		  return FALSE;
	  }
	}
	else lti2.Hor.Lns = NULL;
    lti2.Hor.Cnt = result_h_count;

	if (result_v_count)
	{
      lti2.Ver.Lns = (LineInfo*)malloc(result_v_count * sizeof(LineInfo));
      if (lti2.Ver.Lns == NULL)
      {
		  SetReturnCode_rline( rc16 );
		  return FALSE;
	  }
	}
	else lti2.Ver.Lns = NULL;
    lti2.Ver.Cnt = result_v_count;

	if (!LnsUpload( &lti2, min_h_len, min_v_len ))
	{
		SetReturnCode_rline( rc16 );
		return FALSE;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
//   if(!LDPUMA_Skip(hUseCLine))
//   {
	CLINE_handle hline;
	if(DelAllLines)
	{
		for(i=lti2.Hor.Cnt-1;i>=0;i--)
			lti2.Hor.Lns[i].Flags=LI_SWEEP;
		for(i=lti2.Ver.Cnt-1;i>=0;i--)
			lti2.Ver.Lns[i].Flags=LI_SWEEP;
	}
	else
	{
	 for(hline=CLINE_GetFirstLine(hCLINE);hline;hline=CLINE_GetNextLine(hline))
	 {
      CPDLine cpdata=CLINE_GetLineData(hline);
	  if (!cpdata)
	  {
			rc32 = CLINE_GetReturnCode();
			SetReturnCode_rline( rc32 );
			return FALSE;
	  }
      if(cpdata->Dir==LD_Horiz)
	  {
		for (i=0; i<lti2.Hor.Cnt; i++)
		{
			if( (lti2.Hor.Lns[i].A.x == cpdata->Line.Beg_X) && (lti2.Hor.Lns[i].B.x == cpdata->Line.End_X) &&
					(lti2.Hor.Lns[i].A.y == cpdata->Line.Beg_Y) && (lti2.Hor.Lns[i].B.y == cpdata->Line.End_Y) )
			{
					if (cpdata->Flags & LI_NOTWHOLE)
					{
					 lti2.Hor.Lns[i].Anew = cpdata->lns_data.Anew;
					 lti2.Hor.Lns[i].Bnew = cpdata->lns_data.Bnew;
					}
					lti2.Hor.Lns[i].Flags = cpdata->Flags;
					if (cpdata->Flags &  LI_IsTrue)
						lti2.Hor.Lns[i].Flags |= LI_SWEEP;
					i=lti2.Hor.Cnt;
			}
		}
	  }
	  else
	  {
		for (i=0; i<lti2.Ver.Cnt; i++)
		{
			if( (lti2.Ver.Lns[i].A.x == cpdata->Line.Beg_X) && (lti2.Ver.Lns[i].B.x == cpdata->Line.End_X) &&
					(lti2.Ver.Lns[i].A.y == cpdata->Line.Beg_Y) && (lti2.Ver.Lns[i].B.y == cpdata->Line.End_Y) )
			{
					if (cpdata->Flags & LI_NOTWHOLE)
					{
					 lti2.Ver.Lns[i].Anew = cpdata->lns_data.Anew;
					 lti2.Ver.Lns[i].Bnew = cpdata->lns_data.Bnew;
					}
					lti2.Ver.Lns[i].Flags = cpdata->Flags;
					if (cpdata->Flags &  LI_IsTrue)
						lti2.Ver.Lns[i].Flags |= LI_SWEEP;
					i=lti2.Ver.Cnt;
			}
		}
	  }
	 }
	}
/*   }
   else
   {
	LineInfo			  lInfo;
	pBlock = CPAGE_GetBlockFirst ( lpInPage, HorType );

	while ( pBlock )
	{
		size32 = CPAGE_GetBlockData( lpInPage, pBlock, HorType, &lInfo, sizeof(LineInfo));
		if (size32 != sizeof(LineInfo) )
		{
			rc32 = CPAGE_GetReturnCode();
			SetReturnCode_rline( rc32 );
			return FALSE;
		}

		for (i=0; i<lti2.Hor.Cnt; i++)
		{
			if (DelAllLines)
			{
				lti2.Hor.Lns[i].Flags = LI_SWEEP;
			}
			else
			{
				if( (lti2.Hor.Lns[i].A.x == lInfo.A.x) && (lti2.Hor.Lns[i].B.x == lInfo.B.x) &&
					(lti2.Hor.Lns[i].A.y == lInfo.A.y) && (lti2.Hor.Lns[i].B.y == lInfo.B.y) )
				{
					if (lInfo.Flags &  LI_IsTrue)
						lInfo.Flags |= LI_SWEEP;
					//************
					if (lInfo.Flags & LI_NOTWHOLE)
					{
					lti2.Hor.Lns[i].Anew = lInfo.Anew;
					lti2.Hor.Lns[i].Bnew = lInfo.Bnew;
					}
					//************
					lti2.Hor.Lns[i].Flags = lInfo.Flags;

				}
			}
		}

		pBlock = CPAGE_GetBlockNext( lpInPage, pBlock, HorType );

	}

/////////////////////////////////////////////////////////////////////////////////////////////

	pBlock = CPAGE_GetBlockFirst ( lpInPage, VerType );

	while ( pBlock )
	{
		size32 = CPAGE_GetBlockData( lpInPage, pBlock, VerType, &lInfo, sizeof(LineInfo));
		if (size32 != sizeof(LineInfo) )
		{
			rc32 = CPAGE_GetReturnCode();
			SetReturnCode_rline( rc32 );
			return FALSE;
		}

		for (i=0; i<lti2.Ver.Cnt; i++)
		{
			if (DelAllLines)
			{
				lti2.Ver.Lns[i].Flags = LI_SWEEP;
			}
			else
			{
				if( (lti2.Ver.Lns[i].A.x == lInfo.A.x) && (lti2.Ver.Lns[i].B.x == lInfo.B.x) &&
					(lti2.Ver.Lns[i].A.y == lInfo.A.y) && (lti2.Ver.Lns[i].B.y == lInfo.B.y) )
				{
					if (lInfo.Flags &  LI_IsTrue)
						lInfo.Flags |= LI_SWEEP;
					//************
					if (lInfo.Flags & LI_NOTWHOLE)
					{
					lti2.Ver.Lns[i].Anew = lInfo.Anew;
					lti2.Ver.Lns[i].Bnew = lInfo.Bnew;
					}
					//************
					lti2.Ver.Lns[i].Flags = lInfo.Flags;

				}
			}
		}

		pBlock = CPAGE_GetBlockNext( lpInPage, pBlock, VerType );

	}
   }
*/
/////////////////////////////////////////////////////////////////////////////////////////////
	swp_imxs = LnsGetSweepedImage( &lti2 );


	CIMAGEIMAGECALLBACK cbk1;
	cbk1.CIMAGE_ImageOpen  = SampleImageOpen;
	cbk1.CIMAGE_ImageRead  = SampleImageRead;
	cbk1.CIMAGE_ImageClose = SampleImageClose;


	if (!CIMAGE_GetCallbackImage( (PWord8)pImage, &cbk))
	{
		rc32 = CIMAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}

	if (!CIMAGE_WriteCallbackImage( (PWord8)lpOutDIB, cbk1 ))
	{
		rc32 = CIMAGE_GetReturnCode();
		SetReturnCode_rline( rc32 );
		return FALSE;
	}


	LnsPageFinish();

	if(!LDPUMA_Skip(RLINE_ShowWithoutLines))
	{
		BITMAPINFOHEADER * lp = NULL ;
		CIMAGE_ReadDIB((PWord8)PUMA_IMAGE_DELLINE,(Handle*)&lp,TRUE);
		Handle hwnd = LDPUMA_CreateWindow("����� ������ �����",lp);
		LDPUMA_Console("������� ����� �������...");
		LDPUMA_WaitUserInput(RLINE_ShowWithoutLines, hwnd );
	}

	if(lti2.Hor.Lns) free(lti2.Hor.Lns);
	if(lti2.Ver.Lns) free(lti2.Ver.Lns);

	return TRUE;
}

void CleanLineData(void* pdata,int size)
{
	Word8* mas=(Word8*)pdata;
	for(int i=size-1;i>=0;i--)
	{
		mas[i]=0;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
//end of file
