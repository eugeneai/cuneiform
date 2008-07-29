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

#include "stdafx.h"

# include <fcntl.h>
# include <io.h>
# include <string.h>

//# include "tgcall.h"
# include "tgcallbk.h"
# include "tigerdef.h"
# include "dpuma.h"

HANDLE ToMono(HANDLE hDIB);

typedef struct
	{
	Word32 dwBeg;   // ������ �������� ���������
	Word32 dwEnd;	// �����

	Word32 dwStep;  // ������� ����� ����
	char * name;	// ������� �������� ����
	} PRGTIME;


PRGTIME g_PrgTime;

static HANDLE s_hTempDIB = NULL;
static char * s_pData = NULL;
static char * s_pDIB = NULL;
static TIGER_IMAGEINFO s_ImageInfo;
static int s_line = 0;
static int s_WidthBytesInDIB = 0;
////////////////////////////////////
extern FNPROGRESS_START fnProgressStart;
extern FNPROGRESS_STOP  fnProgressStop;
extern FNPROGRESS_STEP  fnProgressStep;

//////////////////////////////////////////////////////
static Word32 bInitPrgTime = 0;
Bool32  DonePRGTIME()
{
	Bool32 rc = FALSE;
	if(	bInitPrgTime )
		bInitPrgTime--;

	if(!bInitPrgTime)
	{
		fnProgressStop();
		g_pRecognition->Fire_ProgressFinish();
		rc = TRUE;
	}

return rc;
}

Bool32  InitPRGTIME()
{
	Bool32 rc = FALSE;
	if(!bInitPrgTime)
	{
		g_PrgTime.dwBeg  = 0;
		g_PrgTime.dwEnd  = 100;
		g_PrgTime.dwStep = 0;
		g_PrgTime.name   = "";
		rc = TRUE;

		fnProgressStart();
		g_pRecognition->Fire_ProgressStart();
	}
	bInitPrgTime++;
	return rc;
}
PRGTIME	 StorePRGTIME(Word32 beg, Word32 end)
{
	PRGTIME rc = g_PrgTime;

	Word32 newBeg = g_PrgTime.dwBeg + (g_PrgTime.dwEnd - g_PrgTime.dwBeg)*beg/100;
	Word32 newEnd = g_PrgTime.dwBeg + (g_PrgTime.dwEnd - g_PrgTime.dwBeg)*end/100;

	g_PrgTime.dwBeg = newBeg;
	g_PrgTime.dwEnd = newEnd;

return rc;
}

void RestorePRGTIME(PRGTIME	prev)
{
	g_PrgTime  = prev;
}
////////////////////////////////////////////
FNBOOL16 Tiger_Callback_ImageOpen (LPTIGER_IMAGEINFO lpImageInfo)
{

 s_pDIB = NULL;

 LPBITMAPINFOHEADER pDIB = (LPBITMAPINFOHEADER)g_pDIB;

 if(!pDIB)
	 return FALSE;


 if(pDIB->biBitCount==1)
	s_pDIB = g_pDIB;

 if(s_pDIB==NULL)
 {
	s_hTempDIB = ToMono(g_pDIB);
	if(s_hTempDIB)
		s_pDIB = (char *)GlobalLock(s_hTempDIB);
	LDPUMA_CreateWindow(NULL,s_pDIB);
 }

 if(s_pDIB == NULL)
	return FALSE;


 pDIB = (LPBITMAPINFOHEADER)s_pDIB;



lpImageInfo->wImageWidth = (WORD)pDIB->biWidth;           // Height of the image in lines
lpImageInfo->wImageHeight = (WORD)pDIB->biHeight;            // Width of the image in pixels
s_WidthBytesInDIB = ((((lpImageInfo->wImageWidth+7)/8 + 3)/4) * 4);
lpImageInfo->wImageByteWidth = (lpImageInfo->wImageWidth+7)/8;        // Size of the image line in bytes
lpImageInfo->wImageDisplacement = 0;     // Displacement of the first pixel of
							  //   image line in pixels, usually 0
lpImageInfo->wResolutionX = ((WORD)((double)pDIB->biXPelsPerMeter/100.0*25.4)+5)/10;           // Resolution by X-axe

if(lpImageInfo->wResolutionX<200)
	lpImageInfo->wResolutionX = 200;

if(lpImageInfo->wResolutionX>400)
	lpImageInfo->wResolutionX = 400;

lpImageInfo->wResolutionY = lpImageInfo->wResolutionX;           // Resolution by Y-axe
lpImageInfo->bFotoMetrics = 1;           // White pixel
lpImageInfo->bUnused = 0;                // not used; for alignment purpose only

lpImageInfo->wAddX = 0;
lpImageInfo->wAddY = 0;

s_ImageInfo = *lpImageInfo;
s_line = 0;
s_pData = (char *)pDIB +
	 sizeof(BITMAPINFOHEADER) + 2*sizeof(RGBQUAD) +
	 s_WidthBytesInDIB*s_ImageInfo.wImageHeight;

return TRUE;
}
////////////////////////////////////////////

FNWORD Tiger_Callback_ImageRead (LPSTR lpImage, WORD wMaxSize)
{
	 if(wMaxSize<s_ImageInfo.wImageByteWidth)
		return 0;

	 if(s_line < s_ImageInfo.wImageHeight)
		memcpy(lpImage,s_pData - (s_line+1)*s_WidthBytesInDIB,s_ImageInfo.wImageByteWidth);
	 else
		 return 0;
	s_line++;
return s_ImageInfo.wImageByteWidth;
}
/////////////////////////////////////////
FNBOOL16 Tiger_Callback_ImageClose (void)
{
	if(s_hTempDIB)
	{
		GlobalFree(s_hTempDIB);
		s_hTempDIB = NULL;
	}
    return (TRUE);
}

FNVOID Tiger_Callback_ReportError (WORD wStatus, LPSTR lpMessage)
{
    wStatus = wStatus;
//	g_pRecognition->SetError(lpMessage);
}

static WORD swPercent = 0;
static WORD swStageNumber = 0;
static char StageName[256];

//static int  countProgressStart = 0;

FNBOOL16 Tiger_Callback_ProgressStart (void)
{
	BOOL16 rc = TRUE;
	swPercent = 0;
	swStageNumber = 0;
	StageName[0]='\0';
//	countProgressStart - ��������� ��������� ��������� ����� �������� ����������
//	if(!countProgressStart)
//		rc = fnProgressStart() & (BOOL16)g_pRecognition->Fire_ProgressStart();

//	countProgressStart++;

	return rc;
}

FNBOOL16 Tiger_Callback_ProgressFinish (void)
{
	BOOL16 rc = TRUE;
//	if(countProgressStart)
//		countProgressStart--;

//	if(!countProgressStart)
//		rc = fnProgressStop() & (BOOL16)g_pRecognition->Fire_ProgressFinish();
return rc;
}


FNBOOL16 Tiger_Callback_ProgressSetPerc (WORD wPercent)
{
	USES_CONVERSION;

	Word32 perc = g_PrgTime.dwBeg + wPercent*(g_PrgTime.dwEnd - g_PrgTime.dwBeg)/100;
	swPercent = (WORD)perc;

    return fnProgressStep(swStageNumber,StageName,perc) &
		(BOOL16)g_pRecognition->Fire_ProgressStep((long)swStageNumber,T2OLE(StageName),(long)perc);
}

FNBOOL16 Tiger_Callback_ProgressSetStage
(
    WORD wStageNumber,
    LPSTR lpStageName,
    WORD wVolume
)
{
	USES_CONVERSION;
	swStageNumber = wStageNumber;
	strcpy(StageName,lpStageName);

	g_PrgTime.dwStep = wStageNumber;
	g_PrgTime.name = lpStageName;


    return fnProgressStep(swStageNumber,StageName,swPercent) &
		(BOOL16)g_pRecognition->Fire_ProgressStep((long)swStageNumber,T2OLE(StageName),(long)swPercent);
}

FNBOOL16 Tiger_Callback_ImageOpen_xy (LPTIGER_IMAGEINFO lpImageInfo,WORD x,WORD y,WORD w,WORD h)
{
lpImageInfo=lpImageInfo;
x=x;
y=y;
w=w;
h=h;
return TRUE;
}

FNDWORD Tiger_Callback_ProcessPictures(LPSTR buf, DWORD lth)
{
buf=buf;
lth=lth;
return TRUE;
}

FNBOOL Tiger_Callback_Get_One_Word (LPSTR Buffer )
{
	return TRUE;
}
