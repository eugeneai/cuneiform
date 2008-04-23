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

/*#include<windows.h>*/
#include "rmarker.h"
#include "rmarkermem.h"
#include "rmfunc.h"
#include "rneg.h"
#include "pumadef.h"
#include "dpuma.h"

Handle hLayout;
Handle MainDebug;
Handle DebugFill;
//Handle hUseCLine;
Handle hVertCells;
Handle hNegaCells;
Handle hDebugUpDown;
Handle hDebugSpell;
Handle hDebugPictures;
Handle hPrintFileVertCells;
Handle hVertCellsAuto;
Handle hNegaCellsAuto;
Handle hDebugNeg;
Handle hDebugLinePass3;
Handle hDebugLinePass2;
Handle hDebugVerifLine;
Handle hZone;
Handle hNoRazrTabl;
Handle hNoGiveNeg;
Handle hNoSeePict;

Handle hMainTime;
Handle hPrep;
Handle hPicture;
Handle hNegative;
Handle hTableZones;
Handle hPrintCrossedPics;
Handle hVCutInZones;
Handle hSearchTables;
Handle hAnalTables;
Handle hSVLP;
Handle hBlocks;
Handle hLines3;
Handle hNegaTestCells;
Handle hVertTestCells;
Handle hFon;
Handle hEnd;
Handle hSegment;
//extern Word8* Buffer;
//extern Word8* WorkMem;


RMARKER_FUNC(Bool32) RMARKER_PageMarkup(PRMPreProcessImage Image,void* vBuff,int Size,void* vWork,int SizeWork)
{
	SetMainBuff(vBuff,Size);
	SetWorkBuff(vWork,SizeWork);
	Bool32 rc=PageMarkup(Image);
	ReSetMem();
	return rc;
}

RMARKER_FUNC(Bool32) RMARKER_SearchTableInZone(Handle hPage,Handle hCCOM,Word32 perc,Rect32 rect)
{
	return TRUE;
}

RMARKER_FUNC(Bool32) RMARKER_SetImportData(Word32 dwType, void * pData)
{
	BOOL rc = FALSE;

	rc = SetCBProgressPoints( pData );
	return rc;
}

RMARKER_FUNC(Bool32) RMARKER_Init(Word16 wHeightCode,Handle hStorage)
{

 LDPUMA_Init  (0,NULL);

// Buffer=NULL;
// Buffer=(Word8*)RMARKERAlloc(BufferSize*sizeof(Word8));
// if(!Buffer)
//	return FALSE;
// WorkMem=(Word8*)RMARKERAlloc(WorkMemSize*sizeof(Word8));
// if(!WorkMem)
//	return FALSE;

/*------------------------------------------------------------------------------------------*/

	RNEG_Init(wHeightCode,NULL);


/*------------------------------------------------------------------------------------------*/
#ifdef _USE_RFILL_   
	if (!RFILL_Init())
	{
		Word32  retCode = RFILL_GetReturnCode   ();
		char   *pszMsg  = RFILL_GetReturnString (retCode);
		return  FALSE;
	}
#endif //_USE_RFILL_
/*------------------------------------------------------------------------------------------*/

	
 LDPUMA_Registry(&hMainTime,SNAP_ROOT_MAIN_TIME_CONTROL,NULL);
	LDPUMA_Registry(&hPrep,"����������.����. ���. ����.",hMainTime);
	LDPUMA_Registry(&hPicture,"��������� ����. ��������.",hMainTime);
	LDPUMA_Registry(&hNegative,"��������� ���������..",hMainTime);
	LDPUMA_Registry(&hTableZones,"��������� ��� ������..",hMainTime);
	LDPUMA_Registry(&hLines3,"�����.������ ������..",hMainTime);
	LDPUMA_Registry(&hVCutInZones,"����. ����� � ��.",hMainTime);
	LDPUMA_Registry(&hSearchTables,"����� ������..",hMainTime);
	LDPUMA_Registry(&hAnalTables,"������ ��������� ������..",hMainTime);
	LDPUMA_Registry(&hSVLP,"����. ���. ����.",hMainTime);
	LDPUMA_Registry(&hBlocks,"��������� ����������..",hMainTime);
	LDPUMA_Registry(&hNegaTestCells,"���. ����. ����� ������..",hMainTime);
	LDPUMA_Registry(&hVertTestCells,"����. ����. ����� ������..",hMainTime);
	LDPUMA_Registry(&hFon,"���� ����..",hMainTime);
	LDPUMA_Registry(&hEnd,"�� RMARKER �� ��������� �����..",hMainTime);
	LDPUMA_Registry(&hSegment,"������ ��������� ����������...",hMainTime);

 LDPUMA_Registry(&MainDebug,SNAP_ROOT_MAIN_DEBUG, NULL );


// LDPUMA_Registry (&hUseCLine,"������ � ����������� �����",NULL);

 LDPUMA_Registry(&DebugFill,"����� ���� � ��������",MainDebug);
 LDPUMA_RegistryHelp(DebugFill,"����������� ������� �������� ����� ���� � ��������.",FALSE);

 LDPUMA_Registry(&hDebugNeg,"���� ������ ���������.",NULL);

 LDPUMA_Registry(&hDebugLinePass3,"���� ������ �����.",NULL);
 LDPUMA_Registry(&hDebugLinePass2,"���� �������� ������� �� ������.",NULL);
 LDPUMA_Registry(&hDebugVerifLine,"����������� �����.",NULL);

 LDPUMA_Registry(&hNegaCellsAuto,"����������� ���������� ����� ������",MainDebug);
 LDPUMA_RegistryHelp(hNegaCellsAuto,"����������� ������� �������� ����������� ���������� ����� ������.",FALSE);

 LDPUMA_Registry(&hVertCellsAuto,"���� �������������� ������������ ����������� ����� ������.",NULL);

 LDPUMA_Registry(&hVertCells,"������ � ������������� �������� ������",NULL);

 LDPUMA_Registry(&hPrintFileVertCells,"������ � ���� ������������ �����",hVertCells);
 LDPUMA_RegistryHelp(hPrintFileVertCells,"��������� ������ � ���� vertcell.res ������������ ����� ������.",FALSE);

 LDPUMA_Registry(&hNegaCells,"������ � ����������� �������� ������",NULL);

 LDPUMA_Registry(&hDebugUpDown,"������ ����",hVertCells);
 LDPUMA_RegistryHelp(hDebugUpDown,"��� ����������� ������� ������������ ������ ����� ��������� ���� ������-����.",FALSE);
 
 LDPUMA_Registry(&hDebugPictures,SNAP_LAYOUT_PICTURES,NULL);

 LDPUMA_Registry(&hLayout,SNAP_ROOT_LAYOUT,NULL);

 LDPUMA_RegistryHelp(hZone,"������� ������ ��� ������.",FALSE);

 LDPUMA_Registry(&hPrintCrossedPics, "������ ������������ ��������� ��������", hLayout);
 LDPUMA_RegistryHelp(hPrintCrossedPics, "������ � ���� crossed.txt ��������� ��������, ������������ ���� ������", FALSE);

 LDPUMA_Registry(&hNoRazrTabl, "�������� ���������� ��������� ������.",hZone);
 LDPUMA_RegistryHelp(hNoRazrTabl, "�������� ���������� ��������� ������.", FALSE);

 LDPUMA_Registry(&hNoGiveNeg, "�� ������� ��������.",hZone);
 LDPUMA_RegistryHelp(hNoGiveNeg, "�� ������� ��������.", FALSE);

 LDPUMA_Registry(&hNoSeePict,"�� ��������� ��������.",hZone);
 LDPUMA_RegistryHelp(hNoSeePict,"�� ��������� ��������.",FALSE);


 remove("crossed.txt");

	return TRUE;
}

RMARKER_FUNC(Bool32) RMARKER_Done()
{
//	if ( Buffer )
//		RMARKERFree(Buffer);
//	if ( WorkMem )
//		RMARKERFree(WorkMem);

/*------------------------------------------------------------------------------------------*/

	RNEG_Done();

/*------------------------------------------------------------------------------------------*/
#ifdef _USE_RFILL_
    if (!RFILL_Done())
	{
		Word32  retCode = RFILL_GetReturnCode   ();
		char   *pszMsg  = RFILL_GetReturnString (retCode);
		return  FALSE;
	}
#endif //_USE_RFILL_
/*------------------------------------------------------------------------------------------*/

	LDPUMA_Done();
	return TRUE;
}

RMARKER_FUNC(Int8 *) RMARKER_GetReturnString(Word32 dwError)
{return NULL;
}

RMARKER_FUNC(Bool32) RMARKER_GetExportData(Word32 dwType, void * pData)
{return FALSE;
}

Word32 RMARKER_GetReturnCode(void)
{
	return GetReturnCode();
}
