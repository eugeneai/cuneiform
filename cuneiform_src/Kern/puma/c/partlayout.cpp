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

#ifdef _DEBUG
	#include <windows.h>
#endif

#define __PUMA__

#include <stdio.h>
#include <string.h>

#include "mpuma.h"
#include "cfio.h"

static Bool32 rblockProgressStep(Word32 perc)
{
	return ProgressStep(2,NULL,perc);
}
static void   rblockProgressFinish( void )
{
	ProgressStep(2,NULL,100);
}
/////////////////////////////////////////////////////////////////////////
// Allex
// ��������� ��� �������� ����� �� RStuff
Bool32 DPumaSkipComponent( void )
{
	return LDPUMA_Skip(hDebugCancelComponent);
}
Bool32 DPumaSkipTurn( void )
{
	return LDPUMA_Skip(hDebugCancelTurn);
}
/////////////////////////////////////////////////////////////////////////
//end Allex
/////////////////////////////////////////////////
Bool32 Layout(PWord8 lpdata)
{
	Bool32 rc = TRUE;
	int nBlock = 0;
	Int32  Nominator = 0;   // ���������
	Int32  Denominator = 0;	// ����������� ������������� ���� ��������

	RSCBProgressPoints CBforRS;
	RSPreProcessImage  DataforRS;

	RMCBProgressPoints CBforRM;
	RMPreProcessImage  DataforRM;

	PAGEINFO           PInfo = {0};
	//Bool32 rc_line = TRUE;
	//Bool32 need_clean_line = FALSE;
	PRGTIME	prev;

	ClearAll();

	void* MemBuf=NULL;
	int    size_buf=0;
	void* MemWork=NULL;
	int    size_work=0;
	GiveMainBuff(&MemBuf,&size_buf);
	GiveWorkBuff(&MemWork,&size_work);

	///////////////////////////////////////////////////////////Allex
	// ���������� ����������� ���
	prev = StorePRGTIME(0, 6);
	rc = BinariseImage();
	RestorePRGTIME(prev);
	///////////////////////////////////////////////////////////Allex
	prev = StorePRGTIME(6, 10);

	if ( rc )
	{

#define SET_CB(a,b)   a.p##b = (void*)b
		SET_CB(CBforRS, ProgressStart);
		CBforRS.pProgressStep       = (void*)ProgressStepLayout;
		CBforRS.pProgressStepLines  = (void*)ProgressStepLines;
		CBforRS.pProgressStepTables = (void*)ProgressStepTables;
		SET_CB(CBforRS, ProgressFinish);
		SET_CB(CBforRS, InitPRGTIME);
		SET_CB(CBforRS, StorePRGTIME);
		SET_CB(CBforRS, RestorePRGTIME);
		SET_CB(CBforRS, DonePRGTIME);
		SET_CB(CBforRS, rexcProgressStep);
		SET_CB(CBforRS, DPumaSkipComponent);
		SET_CB(CBforRS, DPumaSkipTurn);
		SET_CB(CBforRS, SetReturnCode);
		SET_CB(CBforRS, GetModulePath);
		SET_CB(CBforRS, SetUpdate);

///////////////////////////////////////////////////////////////////////////////////

		SET_CB(CBforRM, ProgressStart);
		CBforRM.pProgressStepAutoLayout   = (void*)ProgressStepAutoLayout;
		CBforRM.pProgressStepSearchTables = (void*)ProgressStepSearchTables;
		SET_CB(CBforRM, ProgressFinish);
		SET_CB(CBforRM, InitPRGTIME);
		SET_CB(CBforRM, StorePRGTIME);
		SET_CB(CBforRM, RestorePRGTIME);
		SET_CB(CBforRM, DonePRGTIME);
		SET_CB(CBforRM, rexcProgressStep);
		SET_CB(CBforRM, DPumaSkipComponent);
		SET_CB(CBforRM, DPumaSkipTurn);
		SET_CB(CBforRM, SetReturnCode);
		SET_CB(CBforRM, GetModulePath);
		SET_CB(CBforRM, SetUpdate);

///////////////////////////////////////////////////////////////////////////////////
#undef SET_CB
///////////////////////////////////////////////////////////////////////////////////

		DataforRS.gbAutoRotate               = gbAutoRotate;
		DataforRS.pgpRecogDIB                = &gpRecogDIB;
		DataforRS.pinfo                      = &info;
		DataforRS.hCPAGE                     = hCPAGE;
		DataforRS.phCCOM                     = &hCCOM;
		DataforRS.phCLINE                    = &hCLINE;
		DataforRS.phLinesCCOM                = &hLinesCCOM;
		DataforRS.gnPictures                 = gnPictures;
		DataforRS.gnLanguage                 = gnLanguage;
		DataforRS.gbDotMatrix                = gbDotMatrix;
		DataforRS.gbFax100                   = gbFax100;
		DataforRS.pglpRecogName              = &glpRecogName;
		DataforRS.pgrc_line                  = &grc_line;
		DataforRS.gnTables                   = gnTables;
		DataforRS.pgnNumberTables            = &gnNumberTables;
		DataforRS.pgneed_clean_line          = &gneed_clean_line;
		DataforRS.gRectTemplate              = gRectTemplate;
		DataforRS.fnXSetTemplate             = PUMA_XSetTemplate;
		DataforRS.fnXGetTemplate             = PUMA_XGetTemplate;
		DataforRS.hDebugCancelSearchPictures = hDebugCancelSearchPictures;
		DataforRS.hDebugCancelComponent      = hDebugCancelComponent;
		DataforRS.hDebugCancelTurn           = hDebugCancelTurn;
		DataforRS.hDebugCancelAutoTemplate   = hDebugCancelAutoTemplate;
		DataforRS.hDebugCancelSearchLines    = hDebugCancelSearchLines;
		DataforRS.hDebugCancelVerifyLines    = hDebugCancelVerifyLines;
		DataforRS.hDebugCancelSearchDotLines   = hDebugCancelSearchDotLines;
		DataforRS.hDebugCancelRemoveLines    = hDebugCancelRemoveLines;
		DataforRS.hDebugCancelSearchTables   = hDebugCancelSearchTables;
		DataforRS.szLayoutFileName			 = szLayoutFileName;
		DataforRS.hDebugEnableSearchSegment  = hDebugEnableSearchSegment;

		// �������
		if ( RSTUFF_SetImportData(RSTUFF_FN_SetProgresspoints,  &CBforRS) )
		{
			///����������� - ���������, ����� ��������, ����� �����
			rc = RSTUFF_RSNormalise(&DataforRS,MemBuf,size_buf,MemWork,size_work);

			if( !rc )
			{
				SetReturnCode(RSTUFF_GetReturnCode());
				rc = FALSE;
			}

//	Rect32 rect={50,100,3300,2449};
//			PUMA_XSetTemplate(rect);	//Paul 26-02-2002

//			PUMA_XSetTemplate(DataforRS.gRectTemplate);	//Paul 26-02-2002
		}
	}

//    RestorePRGTIME(prev);

	// Gleb 02.11.2000
	// ����� - ��������. �������� � RMARKER.DLL
	if( rc )
	{
		DataforRM.gbAutoRotate               = gbAutoRotate;
		DataforRM.pgpRecogDIB                = &gpRecogDIB;
		DataforRM.gbOneColumn				 = gbOneColumn;
		DataforRM.gKillVSLComponents		 = gKillVSLComponents;
		DataforRM.pinfo                      = &info;
		DataforRM.hCPAGE                     = hCPAGE;
		DataforRM.hCCOM                      = hCCOM;
		DataforRM.hCLINE                     = hCLINE;
		DataforRM.phLinesCCOM                = &hLinesCCOM;
		DataforRM.gnPictures                 = gnPictures;
		DataforRM.gnLanguage                 = gnLanguage;
		DataforRM.gbDotMatrix                = gbDotMatrix;
		DataforRM.gbFax100                   = gbFax100;
		DataforRM.pglpRecogName              = &glpRecogName;
		DataforRM.pgrc_line                  = &grc_line;
		DataforRM.gnTables                   = gnTables;
		DataforRM.pgnNumberTables            = &gnNumberTables;
		DataforRM.pgneed_clean_line          = &gneed_clean_line;
		DataforRM.hDebugCancelSearchPictures = hDebugCancelSearchPictures;
		DataforRM.hDebugCancelComponent      = hDebugCancelComponent;
		DataforRM.hDebugCancelTurn           = hDebugCancelTurn;
		DataforRM.hDebugCancelSearchLines    = hDebugCancelSearchLines;
		DataforRM.hDebugCancelVerifyLines    = hDebugCancelVerifyLines;
		DataforRM.hDebugCancelSearchDotLines    = hDebugCancelSearchDotLines;
		DataforRM.hDebugCancelRemoveLines    = hDebugCancelRemoveLines;
		DataforRM.hDebugCancelSearchTables   = hDebugCancelSearchTables;
		DataforRM.hDebugLayoutFromFile		 = hDebugLayoutFromFile;
		DataforRM.hDebugCancelExtractBlocks  = hDebugCancelExtractBlocks;
		DataforRM.hDebugHandLayout			 = hDebugHandLayout;
		DataforRM.hDebugPrintBlocksCPAGE	 = hDebugPrintBlocksCPAGE;
		DataforRM.hDebugSVLines				 = hDebugSVLines;
		DataforRM.hDebugSVLinesStep			 = hDebugSVLinesStep;
		DataforRM.hDebugSVLinesData			 = hDebugSVLinesData;
		DataforRM.szLayoutFileName			 = szLayoutFileName;
		DataforRM.hDebugEnableSearchSegment  = hDebugEnableSearchSegment;

		if ( RMARKER_SetImportData(0,  &CBforRM) )
		{
			rc = RMARKER_PageMarkup(&DataforRM,MemBuf,size_buf,MemWork,size_work);

			if( !rc )
			{
				SetReturnCode(RMARKER_GetReturnCode());
			}
			else
				hCPAGE = DataforRM.hCPAGE;	  //Paul 25-01-2001

		}
	}

	//
	// �������� �������� ��� �������������� Layout
	//

	if(rc && !LDPUMA_Skip(hDebugHandLayout))
	{
				// ������� ���������� �����������
		Handle hRotateDIB = NULL;
		Point32 p  = {0};

		if(PUMA_XGetRotateDIB(&hRotateDIB,&p)==FALSE)
		{
			LDPUMA_Console("��������������: <%s>.\
��� ������ � Layout ����� ������������ �� ���������� �����������.\n",PUMA_GetReturnString(PUMA_GetReturnCode()));
			PAGEINFO           PInfo = {0};
			GetPageInfo(hCPAGE,&PInfo);
			CIMAGE_ReadDIB((PWord8 )PInfo.szImageName,(Handle*)&hRotateDIB,TRUE);
		}
		//LDPUMA_CreateWindow("���������� �����������",hRotateDIB);
		LDPUMA_HandLayout(hRotateDIB, 0 ,&p);
		CIMAGE_DeleteImage((PWord8)PUMA_IMAGE_ROTATE);
	}
	//
	if(!LDPUMA_Skip(hDebugPrintBlocksCPAGE))
	{
		LDPUMA_Console("��������� CPAGE ��������: \n ��� : ������\n");
		Handle block = CPAGE_GetBlockFirst(hCPAGE,0);
		while(block)
		{
			LDPUMA_Console("%s : %i\n",
				CPAGE_GetNameInternalType(CPAGE_GetBlockType(hCPAGE,block)),
				CPAGE_GetBlockData(hCPAGE,block,CPAGE_GetBlockType(hCPAGE,block),NULL,0)
				);
			block = CPAGE_GetBlockNext(hCPAGE,block,0);
		}
	}

	if(rc)
		SetUpdate(FLG_UPDATE_NO,FLG_UPDATE_CPAGE);

    return rc;
}