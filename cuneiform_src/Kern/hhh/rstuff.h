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
/*  �����      :  ��������� ��������                                          */
/*  �����������                                                               */
/*  � ���������                                                               */
/*  ������     :  ������� ��������                                            */
/*  ��������   :  08.06.00                                                    */
/*  ����       :  'RSTUFF.H'                                                */
/*  ���������� :  ��������� ����������                                        */
/*  ���������� :                                                              */
/*----------------------------------------------------------------------------*/
//Almi 16.06.00 //Last edit ........
#ifndef __RSTUFF_H
#define __RSTUFF_H

#ifndef __GLOBUS_H
 #include "globus.h"
#endif

#ifndef __PUMA_H
 #include "puma.h"
#endif

#ifdef __RSTUFF__
  #define RSTUFF_FUNC  FUN_EXPO
#else
  #define RSTUFF_FUNC  FUN_IMPO
#endif

#ifdef __cplusplus
        extern "C" {
#endif

#pragma pack (push,8)
/*
#ifndef Handle
        #define Handle void *
#endif
*/
///////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct tagRSPreProcessImage
{
	PWord8	*pgpRecogDIB;
	Bool32	gbAutoRotate;
	Bool32  gbDotMatrix;
	Bool32  gbFax100;
	Word32  gnLanguage;
	Word32  gnTables;
	Handle	hCPAGE;
	Handle  hDebugCancelSearchPictures;
	Handle  hDebugCancelComponent;
	Handle  hDebugCancelTurn;
	Handle  hDebugCancelSearchLines;
	Handle  hDebugCancelVerifyLines;
	Handle  hDebugCancelSearchDotLines;
	Handle  hDebugCancelRemoveLines;
	Handle  hDebugCancelSearchTables;
	Handle  hDebugCancelAutoTemplate;
	Handle  hDebugEnableSearchSegment;
	const char ** pglpRecogName;
	Handle* phCCOM;
	void *  pinfo;
	Handle* phLinesCCOM;
	void *  phCLINE;
	PBool32 pgneed_clean_line;
	PInt32  pgnNumberTables;
	Word32  gnPictures;
	Bool32* pgrc_line;
	Rect32  gRectTemplate;
	FNPUMA_XSetTemplate fnXSetTemplate;
	FNPUMA_XGetTemplate fnXGetTemplate;
	char *szLayoutFileName;
} RSPreProcessImage, *PRSPreProcessImage;
///////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct tagRSCBProgressPoints
{
	void *	pProgressStart;
	void *	pProgressStep;
	void *	pProgressStepLines;
	void *	pProgressStepTables;
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
} RSCBProgressPoints, *PRSCBProgressPoints;
///////////////////////////////////////////////////////////////////////////////////////////
RSTUFF_FUNC(Bool32) RSTUFF_Init(Word16 wHeightCode,Handle hStorage);
RSTUFF_FUNC(Bool32) RSTUFF_Done();
RSTUFF_FUNC(Word32) RSTUFF_GetReturnCode();
RSTUFF_FUNC(Int8 *) RSTUFF_GetReturnString(Word32 dwError);
RSTUFF_FUNC(Bool32) RSTUFF_GetExportData(Word32 dwType, void * pData);
RSTUFF_FUNC(Bool32) RSTUFF_SetImportData(Word32 dwType, void * pData);
/////////////////////////////////////////////////////////////

typedef enum
{
                RSTUFF_FN_RSBinarise = 1,
                RSTUFF_FN_RSNormalise,
                RSTUFF_FN_RSLayout,
				RSTUFF_FN_RSSetSpecPrj
} RSTUFF_EXPORT_ENTRIES;
//////////////////////////////////////////////////////////////////////////////////////////////
//typedef void   (*PRSTUFFCBPRogressStart)(void);
//typedef Bool32 (*PRSTUFFCBPRogressStep)(Word32);
//typedef void   (*PRSTUFFCBPRogressFinish)(void);
//////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
		RSTUFF_FN_SetProgresspoints = 128,
		RSTUFF_FN_SetProgressStart,
		RSTUFF_FN_SetProgressStep,
		RSTUFF_FN_SetProgressFinish,
		RSTUFF_FN_SetInitPRGTIME,
		RSTUFF_FN_SetDPumaSkipComponent
} RSTUFF_IMPORT_ENTRIES;
////////////////////////////////////////////////////////////////////////////////////////////////
/*  �������� �������  */
#define DEC_FUN(a,b,c) typedef a (*FNRSTUFF##b)c; RSTUFF_FUNC(a) RSTUFF_##b c
DEC_FUN(Bool32, RSBinarise,          (void));
DEC_FUN(Bool32, RSNormalise,         (PRSPreProcessImage,void* vBuff,int Size,void* vWork,int SizeWork));
DEC_FUN(Bool32, RSNormVerify,        (PRSPreProcessImage));
DEC_FUN(Bool32, RSNormRemoveLines,   (PRSPreProcessImage));
DEC_FUN(Bool32, RSLayout,            (PRSPreProcessImage));
DEC_FUN(Bool32, RSSetSpecPrj,          (Word8 NoSpecPrj));
#undef DEC_FUN


#pragma pack (pop)

#ifdef __cplusplus
            }
#endif

#endif //
