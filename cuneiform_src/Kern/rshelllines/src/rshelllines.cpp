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

// RShellLines.cpp: implementation of the ShellLine's functions.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//
//	Description: ShellLine's functions implementation
//
//	Implemented: by B.M. Shahverdiev
//
//

#include "stdafx.h"
#include "resource.h"
#define __RSL__
#define __RSL_EXTERN__
#include "cttypes.h"
#include "linedefs.h"
#include "pumadef.h"
#include "cpage.h"  
#include "ctiimage.h"
#include "dpuma.h"
#include "rshelllinescom.h"
#include "rshelllines.h"  
#include "rsl.h"
#include "rverline.h"
#include "un_buff.h"
#include "cfio.h"

#define CRIME_CUT   50
#define RESULT      2
#define RSL_HANDLE 1
#define RSL_VERLINE CPAGE_GetInternalType("RVL_VERIFY")

#define     RSL_AboutLines_SizeMyBuff    492000
#define     RSL_AboutLines_SizeWorkMem   180000

//#define     RSL_ERR_NO_MEMORY "������ ��������� ������ ��������"
#define RSL_ERR_NO_MEMORY 1
#define     MAF_GALL_GPTR              0x0010
Char8       cCommentBuffer[CFIO_MAX_COMMENT];

static char *Buffer = NULL;
static char *WorkMem = NULL;

static Word16            gwHeightRC = 0;
static Word16            gwLowRC = 0;
static HANDLE            ghStorage = NULL;
static HINSTANCE         ghInst =  NULL;
//DVP DLine*             tempLine;
HANDLE			  hSkipDeleteNoiseEvents = NULL;
HANDLE			  hPrintUnderlineTest = NULL;
HANDLE			  hSkipCheckUnderlining = NULL;
HANDLE			  hPrintUnderlines = NULL;
HANDLE			  hSkipCheckRaster = NULL;
HANDLE			  hPrintRasterCheck = NULL;
HANDLE			  hSkipCorrectPolynomia = NULL;
HANDLE			  hPrintCorrectPolynomia = NULL;
HANDLE			  hSkipDelFragLines = NULL;
HANDLE			  hPrintFragLines = NULL;
HANDLE			  hPreRSL_Root = NULL;
HANDLE			  hPreRSL_Control = NULL;
HANDLE			  hPreRSL_Debug = NULL;
HANDLE			  hDebugFragOwnerControl = NULL;


typedef Bool32 (*FNPUMA_XSetTemplate)(Rect32 rect);
typedef Bool32 (*FNPUMA_XGetTemplate)(Rect32 *pRect);
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
    char ** pglpRecogName;
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

Bool32 AboutLines (PRSPreProcessImage Image, Bool32 *BadScan, Int32 *ScanQual);

//  BOOL APIENTRY DllMain( HANDLE hModule, 
//                         DWORD  ul_reason_for_call, 
//                         LPVOID lpReserved
//  				  )
//  {
//      switch (ul_reason_for_call)
//      {
//  	  case DLL_PROCESS_ATTACH:
//   	  case DLL_THREAD_ATTACH:
//        case DLL_THREAD_DETACH:
//        case DLL_PROCESS_DETACH:
//  	  break;
//      }
//      return TRUE;
//  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                     FindLineFrag                                       
RSHELLLINES_API Bool32 FindLineFrag(CLINE_handle processedline, Bool32 OnlyPosyAndStat, 
									Bool32 Is2ndPath, CLINE_handle hContainer, 
									Bool32 IfNeedFragment, Bool32 IfStraightFrag)
{
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                     FindLineAttr                                       
RSHELLLINES_API Bool32 FindLineAttr(CLINE_handle line, DLine* pCLine, Bool32 AbleSeeOldAttr)
{
    //SetWidth(line, pCLine);
    return TRUE;
}

///////////////////////////////////////////////////////////////
RSL_FUNC(Bool32) RSL_Init(Word16 wHeightCode,HANDLE hStorage)
{
	LDPUMA_Init(0,NULL);
	LDPUMA_Registry(&hDebugRSL,SNAP_STUFF_RSL,NULL);
	LDPUMA_Registry(&hPreRSL_Root, "��������������� ��������� �����", hDebugRSL);
	LDPUMA_Registry(&hPreRSL_Debug, "������� ������ (pre)", hPreRSL_Root);
	LDPUMA_Registry(&hPreRSL_Control, "�������� ������ (pre)", hPreRSL_Root);

	LDPUMA_Registry(&hSkipCheckUnderlining, "��������� �������� ���������", hPreRSL_Debug);
	LDPUMA_Registry(&hPrintUnderlineTest, "����� ����������� �������� �������������", hPreRSL_Control);
	LDPUMA_RegistryHelp(hPrintUnderlineTest, "� Console ���������� ���������� ������ ����� (�� 1000) � ������� ����� ������ �����", FALSE);
	LDPUMA_Registry(&hPrintUnderlines, "����� ��������� ���������", hPreRSL_Control);
	LDPUMA_RegistryHelp(hPrintUnderlines, "� Console ���������� ���������� �����, ������������ ��� ��������", FALSE);

	LDPUMA_Registry(&hSkipCheckRaster, "�� ��������� ����� �� ������", hPreRSL_Debug);
	LDPUMA_RegistryHelp(hSkipCheckRaster, "���� ��������� �������� ����� �� ������, ����� ������������� �����, ���������� �� ������� ������", FALSE);
	LDPUMA_Registry(&hPrintRasterCheck, "����� ����������� �������� ������", hPreRSL_Control);
	LDPUMA_RegistryHelp(hPrintRasterCheck, "� Console ���������� ���������� ������ ����� (�� 1000) � ������ �����", FALSE);

	LDPUMA_Registry(&hDebugFrag,"����� ���������� �����",hDebugRSL);
    LDPUMA_Registry(&hDebugFragOwner,"������� ������ ���������� �����",hDebugFrag);
    LDPUMA_Registry(&hDebugFragOwnerControl,"�������� ������ ���������� �����",hDebugFrag);

	LDPUMA_Registry(&hDebugDrowRectForRaster,"�������� ������������� �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hSkipCorrectPolynomia,"�� �������������� 4-��������� �����",hDebugFragOwner);
	LDPUMA_Registry(&hPrintCorrectPolynomia,"��������� �������� 4-���������� �����",hDebugFragOwnerControl);
	LDPUMA_RegistryHelp(hPrintCorrectPolynomia,"����� �� ������� ����������� �������� 4-���������� �����",FALSE);
	LDPUMA_Registry(&hDebugDrowPolynomia,"�������� ������ �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugDrowCleanedRaster,"�������� ������������� ����� ����� ���������",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugDrowGetCorrectedLineStripesIntervals,"�������� ������������ ������������� �����",hDebugFragOwnerControl);

	LDPUMA_Registry(&hDebugDrowVerticalLineRaster,"�������� ����� ������������ �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugDrowVerticalLineStripesIntervals,"�������� ������������ ������������� ������������ �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugDrowVerticalLineCutPoints,"�������� ����� ����������� ������������ �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugTypeIntervals,"����� �� Consol ��������� ���������� �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugTypeStripe,"����� �� Consol ������������ ������������� �����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hSkipDeleteNoiseEvents, "�� ��������� �������� ������� ����������", hDebugFragOwner);
	LDPUMA_RegistryHelp(hSkipDeleteNoiseEvents, "�� ������� ������� ���������", FALSE);
	LDPUMA_Registry(&hSkipDelFragLines, "�� ������� ������ ����������������� �����", hDebugFragOwner);
	LDPUMA_RegistryHelp(hSkipDelFragLines, "�� ������� ����� � ������ ���������� ������ 5", FALSE);
	LDPUMA_Registry(&hPrintFragLines, "������ ����������� �������� ������������", hDebugFragOwnerControl);
	LDPUMA_RegistryHelp(hPrintFragLines, "����� �� Consol ����������� �������� ���������� �� ��������", FALSE);
	LDPUMA_Registry(&hDebugDrawLineFragmentsOwnWindow,"�������� ��������� ����� � ��������� ����",hDebugFragOwnerControl);
	LDPUMA_Registry(&hDebugDroweparationPoints,"�������� ����� ������� ����� � ��������� ����",hDebugFragOwnerControl);
    LDPUMA_Registry(&hDebugDrawLineFragments,"�������� ��������� ����� � �������� ����",hDebugFragOwnerControl);
    LDPUMA_RegistryHelp(hDebugDrawLineFragments, "��������� �������� ��� ������ ����� � �����������", FALSE);

	LDPUMA_Registry(&hDebugAttr,"����� ��������� �����",hDebugRSL);
    LDPUMA_Registry(&hDebugAttrOwner,"�������� ������ ��������� �����",hDebugAttr);
	LDPUMA_Registry(&hDebugTypeWidth,"����� �� Consol ������ �����",hDebugAttrOwner);
	LDPUMA_Registry(&hDebugTypeDegree,"����� �� Consol ���� ������� �����",hDebugAttrOwner);
    
    gwHeightRC = wHeightCode;
    
    return RESULT;
}

void SetReturnCode_rshelllines(Word16 rc)
{
    gwLowRC = rc;
}

//////////////////////////////////////////////////////////////////////////////////
//
RSL_FUNC(Bool32) RSL_Done()
{
 	LDPUMA_Done();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
//
RSL_FUNC(Word32) RSL_GetReturnCode()
{
    Word32 rc = 0;
    if((gwLowRC - IDS_ERR_NO)>0)
        rc = (Word32)(gwHeightRC<<16)|(gwLowRC - IDS_ERR_NO);

    return rc;
}

//////////////////////////////////////////////////////////////////////////////////
//
RSL_FUNC(Int8 *) RSL_GetReturnString(Word32 dwError)
{
	Word16 rc = (Word16)(dwError & 0xFFFF) + IDS_ERR_NO;
	static Int8 szBuffer[512];

	if( dwError >> 16 != gwHeightRC)
		gwLowRC = IDS_ERR_NOTIMPLEMENT;

	if( rc >= IDS_ERR_NO )
		LoadString(ghInst,rc,(char *)szBuffer,sizeof(szBuffer));
	else
		return NULL;

	return szBuffer;
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//
RSL_FUNC(Bool32) RSL_GetExportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;

return rc;
}

//////////////////////////////////////////////////////////////////////////////////
//
RSL_FUNC(Bool32) RSL_SetImportData(Word32 dwType, void * pData)
{
	Bool32 rc = RESULT;

    if (dwType != RSL_HANDLE)
        return FALSE;

    Handle* phCPage = (Handle*) pData;

    RSPreProcessImage IImage;
    PRSPreProcessImage Image = &IImage;

    Word32 nTeor = sizeof (RSPreProcessImage);
    Handle hPage = CPAGE_GetHandlePage(CPAGE_GetCurrentPage());
    Handle VerifyN = CPAGE_GetBlockFirst (*phCPage, RSL_VERLINE);//hPage, RSL_VERLINE);
    Word32 nReal = CPAGE_GetBlockData (*phCPage, VerifyN, RSL_VERLINE, Image, nTeor);
//     Word32 err32 = CPAGE_GetReturnCode ();
//     if (err32)
//         return FALSE;
    
    if( *Image->pgrc_line )
    {
        if(LDPUMA_Skip(Image->hDebugCancelVerifyLines))
        {
            Regime_VerifyLines val = Image->gnTables ? RVL_FutuTablCorr:RVL_Default;
            
            if( !RVERLINE_SetImportData(RVERLINE_DTRVERLINE_RegimeOfVerifyLines,&val)||
                !RVERLINE_MarkLines(*Image->phCCOM, Image->hCPAGE))
            {
                SetReturnCode_rshelllines((Word16)RVERLINE_GetReturnCode());
                rc = FALSE;
            }
            else
            {
                Bool32 BadScan = FALSE;
                Int32  ScanQual= 0;
                AboutLines(Image, &BadScan, &ScanQual);
            }
            
            if(!*Image->pgneed_clean_line)
                LDPUMA_Console("Warning: RSL said that the lines do not have to withdraw.\n");
        }
        else
            LDPUMA_Console("Missing stage of the evaluation lines.\n");
    }  
    
    //CPAGE_DeleteBlock(&phCPage, VerifyN);

    return rc;
}

//////////////////////////////////////////////////////////////////////////////////
//
void *	RSLAlloc(Word32 stAllocateBlock)
{
    char * mem = NULL;
    
#ifdef _NO_CFIO
    
#ifdef  RSL_USE_GLOBAL_MEM
    
    mem = (char *)GlobalAlloc(GPTR, stAllocateBlock);
    
#else
    
    mem = ::new char[stAllocateBlock];
    memset(mem, 0, stAllocateBlock );
    
#endif
    
    if(!mem)
        SetReturnCode_rshelllines((Word16)RSL_ERR_NO_MEMORY);
#else
    
    mem = (char *)CFIO_DAllocMemory(stAllocateBlock,MAF_GALL_GPTR,(Int8*)"RSL", (Int8*)cCommentBuffer);
    
    if(!mem)
        SetReturnCode_rshelllines((Word16)RSL_ERR_NO_MEMORY);
    
#endif
    
    return mem;
}

void	RSLFree(void * mem)
{
#ifdef _NO_CFIO
    
#ifdef  RSL_USE_GLOBAL_MEM
    
    GlobalFree(mem);
    
#else
    
    ::delete []	mem;
    
#endif
#else
    
    CFIO_FreeMemory(mem);
    
#endif
}
 
Bool32 AboutLines (PRSPreProcessImage Image, Bool32 *BadScan, Int32 *ScanQual)
{
	int SizeMain, SizeWork;

	UN_BUFF MainBuff = {0};

	void *vMain;
	char *cWork;
	Bool32 bRc = TRUE;
	
	//////////////////////////////////////////////////////////////////////////////////
	Buffer  = (char *)RSLAlloc(RSL_AboutLines_SizeMyBuff);
	WorkMem = (char *)RSLAlloc(RSL_AboutLines_SizeWorkMem);

	if (Buffer == NULL || WorkMem == NULL )
	{
		SetReturnCode_rshelllines((Word16)RSL_ERR_NO_MEMORY);
		bRc =  FALSE;
	}
	
	if ( bRc )
		do
		{
			//////////////////////////////////////////////////////////////////////////////////////
			/*  1. ��������.  */
			if ((Image->pgneed_clean_line==NULL)&&(BadScan!=NULL))
				break;
				//return TRUE;
			
			/*  2. �������������.  */
			vMain = Buffer;
			SizeMain = RSL_AboutLines_SizeMyBuff;
			MainBuff.vBuff    = vMain;
			MainBuff.SizeBuff = SizeMain;
			MainBuff.vCurr    = MainBuff.vBuff;
			MainBuff.SizeCurr = MainBuff.SizeBuff;
			cWork = WorkMem;
			SizeWork = RSL_AboutLines_SizeWorkMem;
			

			if (Image->pgneed_clean_line!=NULL)
			{
				*Image->pgneed_clean_line = FALSE;
				CLINE_handle hCLINE=*((CLINE_handle*)(Image->phCLINE));
				BOOL fl_break=FALSE;
				for(CLINE_handle hline=CLINE_GetFirstLine(hCLINE);hline;hline=CLINE_GetNextLine(hline))
				{
					CPDLine cpdata=CLINE_GetLineData(hline);
					if(!cpdata)
						continue;
					if(cpdata->Flags&LI_IsTrue)
					{
						*Image->pgneed_clean_line=TRUE;
						fl_break=TRUE;
					}
					if(fl_break)
						break;
				}
				if (1)
				{
					if (*Image->pgneed_clean_line)
						LDPUMA_ConsoleN ("RSource: ����� ����� �����.");
					else
						LDPUMA_ConsoleN ("RSource: �� ���� ������� �����!");
				}
			}
//		   }

			if (BadScan!=NULL)
			{
				if (1)
					LDPUMA_ConsoleN ("RSource: �������� ������������ : �� ���� ���� ����������.");
				*BadScan = TRUE;
				*ScanQual = 100;
			}
		} while ( false );

	RSLFree(Buffer);
	RSLFree(WorkMem);

	return bRc;
}

//////////////////////////////////////////////////////////////////////////////////
//
Word16 GetReturnCode_rshelllines()
{
	return gwLowRC;
}

#define two0         1
#define two1         2
#define two2         4
#define two3         8
#define two4         16
#define two5         32
#define two6         64
#define two7         128
#define two8         256
#define two9         512
#define two10        1024
#define two11        2048
#define two12        4096
#define two13        8192
#define two14        16384
#define two15        32768
#define two16        65536
#define two17        131072
#define two18        262144
#define two19        524288
#define two20        1048576
#define two21        2097152
#define two22        4194304
#define two23        8388608
#define two24        16777216
#define two25        33554432
#define two26        67108864
#define two27        134217728
#define two28        268435456
#define two29        536870912
#define two30        1073741824
#define two31        2147483648

struct FictInterval
{
	Int32 Level;
	Int32 Pos;
	Int32 End;
	Int32 RelIndex;
};

static int _cdecl mycompare( const void *elem1, const void *elem2 )
{
  
  FictInterval *a = (FictInterval*) elem1;
  FictInterval *b = (FictInterval*) elem2;

   if(a->Level == b->Level)
   {
	   return a->Pos - b->Pos;
   }
   return a->Level - b->Level;
};

// struct TieComp
// {
// 	Int32 LeftBorder;
// 	Int32 RightBorder;
// 	Int32 Weight;
// 	Bool32 IsNoiseComp;
// 	Int32 VoteResult;
// };

void   DeleteNoiseEvents(CLINE_handle hLine, DLine* pLine)
{
	return;
}

void CheckUnderlining(CLINE_handle hLine, DLine* pLine, LPSTR pSourceRaster)
{
	return;
}

Bool32 CompareRasterParts(CPDLine pLine, LPSTR pSourceRaster, Bool32 CheckSerif)
{
    return TRUE;
}

RSHELLLINES_API Bool32 RSL_CorrectDoubleLines(CLINE_handle hLine1, CLINE_handle hLine2)
{
	return TRUE;
}

RSHELLLINES_API Bool32     RSL_SplitLine(CLINE_handle hLine, CLINE_handle hContainer)
{
	return TRUE;
}

int SL_IsInPoly(Point32* a, CLINE_SL_POLY* p)
{
    return 0;
}

BOOL SL_IsPointInAB(Point32 *P,Point32 *A,Point32 *B)
{    
    return FALSE;
}

void CalculateRectForRaster(DLine* pCLine, PAGEINFO* page_info)
{
}

void CalculatePolynomia(DLine* pCLine, PAGEINFO* page_info)
{
}

void DrowRectForRaster(Rect32* rect)
{
}

void DrowPolynomia(DLine* pCLine)
{
}

void   DrowVerticalLineStripesIntervals(CLINE_handle line, Handle HndMyWindow)
{
}

void   CleaningRaster(DLine* pCLine, LPSTR Buffer)
{
}

void   DrowCleanedRaster(DLine* pCLine, LPSTR Buffer, CIMAGEBITMAPINFOHEADER* image_info, Handle* HndMyWindow)
{
}

void   DrowVerticalLineRaster(DLine* pCLine, LPSTR Buffer, CIMAGEBITMAPINFOHEADER* image_info, Handle* HndMyWindow)
{
}

void   Transpose_bit_matrixes(PCHAR buf_in,PCHAR buf_out, Rect32* rect)
{
}

BOOL GetLineStripesIntervals(CLINE_handle line, DLine* pCLine, PCHAR  pRaster, BOOL FlagVerticalLine)
{  
    return TRUE;
}

void   FillingStripes(CLINE_handle line, int y, INT Count, WORD* pIntervals, BOOL FlagVerticalLine, DLine* pCLine)
{
}

void   CheckDotLines(DLine* pCLine, BOOL FlagVerticalLine)
{
}

void   TypeIntervals(int y, INT Count, WORD* pIntervals)
{
}

void   TypeStripe(CLINE_handle hStripe, DEvent* pStripe)
{
}

BOOL   GetLineFragments(CLINE_handle line, DLine* pCLine)
{
    return TRUE;
}

Handle DrawLineFragments(CLINE_handle line, CPDLine pCLine, Handle HndMyWindow, int ColorIndex, Bool32 ForAllLines)// = FALSE)
{
    return NULL;
}

RSHELLLINES_API void DrawFriendLines(CLINE_handle hContainer, GLM* friendlinesmass)
{
}
                                      
void DrawGroupOfExtensibleLines(CLINE_handle hContainer, GLM* hGroup, int CountLines)
{
}
                                   
RSHELLLINES_API void DrawLosedVerticalLines(GLM* friendlinesmass, int CountLines)
{
}
                                     
RSHELLLINES_API void DrowAllLines(CLINE_handle hContainer, Handle hDrowAllLines)
{
}
                                     
RSHELLLINES_API void DrawBigComps(CLINE_handle hContainer)
{
} 

RSHELLLINES_API void DrawFragsForAllLines(CLINE_handle hContainer, Handle hDebugDrawAllLineFragments)
{
}

RSHELLLINES_API void InitLine(DLine* linedata)
{
}

RSHELLLINES_API void FindDotLines(Handle hCCOM,Handle hCPAGE, CLINE_handle hContainer)
{
}

RSHELLLINES_API Bool32 CheckSeparationPoints(CLINE_handle hLine, CLINE_handle hComp)
{
    return FALSE;
}

RSHELLLINES_API Bool SL_GetRaster(Rect32* rect, Word8** ppData, PAGEINFO* page_info)
{
    return TRUE;
}

RSHELLLINES_API void SetLinesAndCompsRelationship(CLINE_handle hContainer, CLINE_handle hFictContainer)
{
}

RSHELLLINES_API void FindFriendLines(CLINE_handle hContainer, GLM* friendlinesmass)
{
} 

RSHELLLINES_API void FindGroupOfExtensibleLines(CLINE_handle hContainer, GLM* friendlinesmass, Bool32 IfDrawResult)
{
} 

RSHELLLINES_API Int32 RSL_VerifyShortLine(CPDLine pLine, Handle hCCOM, PAGEINFO* page_info, Word8 lang, Word8 debug_flags, Int32 *cross_point)
{
    return 0;
}

RSHELLLINES_API Bool32 GetNextPartOfLine(CLINE_handle hContainer, CLINE_handle hLine)
{
    return FALSE;
}

Bool32 SetExtLines(CLINE_handle hExtContainer, CLINE_handle hContainer, CLINE_handle* hLinesMass, 
                   Int32 CountLines)
{
    return FALSE;
}

Int32 CountBlackRaster(CPDLine pLine, CPDLine pLineExt, Bool32 IsHor, Int32 delta, Handle hDrawRaster)
{
    return 0;
}

