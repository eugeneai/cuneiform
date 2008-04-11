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
/*  �����      : ���� ���������					                                          */
/*  �����������                                                               */
/*  � ���������                                                               */
/*  ������     :							                                  */
/*  ��������   :  16.10.2000                                                  */
/*  ����       :  'RMARKER.H'                                                 */
/*  ���������� :  ��������� ����������                                        */
/*  ���������� :                                                              */
/*----------------------------------------------------------------------------*/
//Almi 16.06.00 //Last edit ........
#ifndef __RMARKER_H
#define __RMARKER_H

#ifndef __GLOBUS_H
 #include "globus.h"
#endif

#ifdef __RMARKER__
  #define RMARKER_FUNC  FUN_EXPO
#else
  #define RMARKER_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
        extern "C" {
#endif

#ifdef PPS_MAC
   #pragma export on
#endif

#pragma pack (push,8)

#ifndef Handle
        #define Handle void *
#endif
		
			
///////////////////////////////////////////////////////////////////////////////////////////
RMARKER_FUNC(Bool32) RMARKER_Init(Word16 wHeightCode,Handle hStorage);
RMARKER_FUNC(Bool32) RMARKER_Done();
RMARKER_FUNC(Word32) RMARKER_GetReturnCode();
RMARKER_FUNC(Int8 *) RMARKER_GetReturnString(Word32 dwError);
RMARKER_FUNC(Bool32) RMARKER_GetExportData(Word32 dwType, void * pData);
RMARKER_FUNC(Bool32) RMARKER_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tagRMPreProcessImage
{
	PWord8	*pgpRecogDIB;
	Bool32	gbAutoRotate;
	Bool32  gbDotMatrix;
	Bool32  gbFax100;
	Bool32  gbOneColumn;
	Bool32  gKillVSLComponents;
	Word32  gnLanguage;
	Word32  gnTables;
	Handle	hCPAGE;
	Handle  hCCOM;
	Word32  hCLINE;
	Handle  hDebugCancelSearchPictures;
	Handle  hDebugCancelComponent;
	Handle  hDebugCancelTurn;
	Handle  hDebugCancelSearchLines;
	Handle  hDebugCancelVerifyLines;
	Handle  hDebugCancelSearchDotLines;
	Handle  hDebugCancelRemoveLines;
	Handle  hDebugCancelSearchTables;
	Handle  hDebugLayoutFromFile;
	Handle  hDebugCancelExtractBlocks;
	Handle  hDebugHandLayout;
	Handle  hDebugPrintBlocksCPAGE;
	Handle  hDebugSVLines;
	Handle  hDebugSVLinesStep;
	Handle  hDebugSVLinesData;
	Handle  hDebugEnableSearchSegment;
	char *szLayoutFileName;
	char ** pglpRecogName;
	void *  pinfo;
	Handle* phLinesCCOM;
	PBool32 pgneed_clean_line;
	PInt32  pgnNumberTables;
	Word32  gnPictures; 
	Bool32* pgrc_line;
} RMPreProcessImage, *PRMPreProcessImage;

typedef struct tagRMCBProgressPoints
{
	void *	pProgressStart;
	void *	pProgressStepSearchTables;
	void *	pProgressStepAutoLayout;
	void *	pProgressFinish;
	void *  pInitPRGTIME;
	void *  pStorePRGTIME;
	void *  pRestorePRGTIME;
	void *  pDonePRGTIME;
	void *  prexcProgressStep;
	void *  pDPumaSkipComponent;
	void *  pDPumaSkipTurn;
	void *  pSetReturnCode;
	void *  pGetModulePath;
	void *  pSetUpdate;
} RMCBProgressPoints, *PRMCBProgressPoints;
////////////////////////////////////////////////////////////////////////////////////////////////

#define PUMA_SVL_FIRST_STEP                         0x1
#define PUMA_SVL_SECOND_STEP                        0x2
#define PUMA_SVL_THRID_STEP                         0x3
#define PUMAMaxNumLines                             2000

////////////////////////////////////////////////////////////////////////////////////////////////
#define DEC_FUN(a,b,c) typedef a (*FNRMARKER##b)c; RMARKER_FUNC(a) RMARKER_##b c
DEC_FUN(Bool32, PageMarkup,          (PRMPreProcessImage,void*,int,void*,int)); 
DEC_FUN(Bool32, SearchTableInZone,    (Handle hPage,Handle hCCOM,Word32 perc,Rect32 rect));
#undef DEC_FUN

///////////////
#ifdef PPS_MAC
   #pragma export off
#endif

#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif //
