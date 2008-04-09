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

/**********  ���������  ****************************************************************************/
/*  �����,                                                                                         */
/*  �����������                                                                                    */
/*  ������     :                                                                                   */
/*  ��������   :  30.08.00                                                                         */
/*  ����       :  'ShortVerticalLinesFilter.cpp'                                                   */
/*  ���������� :                                                                                   */
/*  ���������� :                                                                                   */
/*-------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <stdio.h>
#include <string.h>

#include "markpage.h"
#include "LineDefs.h"
#include "cline.h"

static Bool32 bShowDebug     = FALSE;
static Bool32 bShowStepDebug = FALSE;
static Bool32 bShowDebugData = FALSE;
//extern Handle hUseCLine;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
Bool32 ShortVerticalLinesProcess ( Word32 Step, PRMPreProcessImage Image )
{
	Bool32 bRet = FALSE;
	Bool32 bClear = FALSE;

	if ( Step == PUMA_SVL_FIRST_STEP && gSVLBuffer.LineInfoA)
	{

		gSVLBuffer.HLinesBufferA = gSVLBuffer.LineInfoA->Hor.Lns = NULL/*(LineInfo *)myAlloc(sizeof(LineInfo) * PUMAMaxNumLines)*/;
		//gSVLBuffer.VLinefBufferA = gSVLBuffer.LineInfoA->Ver.Lns = (LineInfo *)myAlloc(sizeof(LineInfo) * PUMAMaxNumLines);
		
		if ( gSVLBuffer.VLinefBufferA == NULL )
			gSVLBuffer.VLinefBufferA = gSVLBuffer.LineInfoA->Ver.Lns = (LineInfo *)CFIO_DAllocMemory((sizeof(LineInfo) * PUMAMaxNumLines), MAF_GALL_GPTR, (PInt8)"puma", (PInt8)"SVL step I lines pool");

		bRet = ReadSVLFromPageContainer( gSVLBuffer.LineInfoA, Image );
		bClear = bRet == FALSE;
	}

	if ( Step == PUMA_SVL_SECOND_STEP && gSVLBuffer.LineInfoB)
	{

		gSVLBuffer.HLinesBufferB = gSVLBuffer.LineInfoB->Hor.Lns = NULL/*(LineInfo *)myAlloc(sizeof(LineInfo) * PUMAMaxNumLines)*/;
		//gSVLBuffer.VLinefBufferB = gSVLBuffer.LineInfoB->Ver.Lns = (LineInfo *)myAlloc(sizeof(LineInfo) * PUMAMaxNumLines);
		
		if ( gSVLBuffer.VLinefBufferB == NULL )
			gSVLBuffer.VLinefBufferB = gSVLBuffer.LineInfoB->Ver.Lns = (LineInfo *)CFIO_DAllocMemory((sizeof(LineInfo) * PUMAMaxNumLines), MAF_GALL_GPTR, (PInt8)"puma", (PInt8)"SVL step II lines pool");

		bRet = ReadSVLFromPageContainer( gSVLBuffer.LineInfoB, Image );
		////////////////
		// ��������� � �������� ���
		if ( bRet )
		{
			bRet = SVLFilter(gSVLBuffer.LineInfoA, gSVLBuffer.LineInfoB, Image);
		}

		bClear = TRUE;
	}
	
	if ( Step == PUMA_SVL_THRID_STEP )
	{
		//myFree ( gSVLBuffer.HLinesBufferA );
		//myFree ( gSVLBuffer.HLinesBufferB );
		//myFree ( gSVLBuffer.VLinefBufferA );
		//myFree ( gSVLBuffer.VLinefBufferB );
		if ( gSVLBuffer.VLinefBufferA != NULL )
		{
			CFIO_FreeMemory(gSVLBuffer.VLinefBufferA);
		}

		if ( gSVLBuffer.VLinefBufferB != NULL )
		{
			CFIO_FreeMemory(gSVLBuffer.VLinefBufferB);
		}
		
		gSVLBuffer.VLinefBufferA = NULL;
		gSVLBuffer.VLinefBufferB = NULL;

		bRet = TRUE;
	}

	if ( bRet == FALSE )
	{
		SetReturnCode(IDS_ERR_INITIATED_BY_ALLEX);
	}

	return bRet;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 ReadSVLFromPageContainer ( LinesTotalInfo *LTInfo, PRMPreProcessImage Image )
{
 Bool32         bRet = TRUE;
		
// Handle         hBlockLine;
// Handle         hBlockLineHor;
// Handle         hBlockLineVer;
// Handle         hBlockLinePrev;
 Word32         nTagSize;
// Word32         nReal;
// Word32         wErr32;

 nTagSize = sizeof (LinesTotalInfo);
 Word32 size_line_com=sizeof(LINE_COM);
 Bool32 fl_break;
 int num=0;
 int count=0;
 Handle hPage=Image->hCPAGE;
 CLINE_handle hCLINE=Image->hCLINE;
 

//   if(!LDPUMA_Skip(hUseCLine))
//   {
	 CLINE_handle hline;
	 CPDLine cpdata; 
	 hline=CLINE_GetFirstLine(hCLINE);
     LTInfo->Hor.Cnt=0;
	 LTInfo->Ver.Cnt=0;
     while(hline)
	 {
	  fl_break=FALSE;
	  cpdata=CLINE_GetLineData(hline);
      if(!cpdata)
         hline=CLINE_GetNextLine(hline);
      else
	  {
		 if(count>=PUMAMaxNumLines)
			 fl_break=TRUE;
		 else
		 {
		   count++;
		  if(cpdata->Dir==LD_Horiz)
		  {
		   if(LTInfo->Hor.Lns)
		   {
		    num=LTInfo->Hor.Cnt;
		    LTInfo->Hor.Lns[num].A.x=(Int16)(cpdata->Line.Beg_X);
            LTInfo->Hor.Lns[num].A.y=(Int16)(cpdata->Line.Beg_Y);
		    LTInfo->Hor.Lns[num].B.x=(Int16)(cpdata->Line.End_X);
		    LTInfo->Hor.Lns[num].B.y=(Int16)(cpdata->Line.End_Y);
		    LTInfo->Hor.Lns[num].Thickness=cpdata->Line.Wid10/10;
            LTInfo->Hor.Lns[num].Flags=cpdata->Flags;
		    (LTInfo->Hor.Cnt)++;
		   }
		  }
		  else
		  {
		   if(LTInfo->Ver.Lns)
		   {
		    num=LTInfo->Ver.Cnt;
		    LTInfo->Ver.Lns[num].A.x=(Int16)(cpdata->Line.Beg_X);
            LTInfo->Ver.Lns[num].A.y=(Int16)(cpdata->Line.Beg_Y);
		    LTInfo->Ver.Lns[num].B.x=(Int16)(cpdata->Line.End_X);
		    LTInfo->Ver.Lns[num].B.y=(Int16)(cpdata->Line.End_Y);
		    LTInfo->Ver.Lns[num].Thickness=cpdata->Line.Wid10/10;
            LTInfo->Ver.Lns[num].Flags=cpdata->Flags;
		    (LTInfo->Ver.Cnt)++;
		   }
		  }
		 }
         hline=CLINE_GetNextLine(hline);
	  }
	  if(fl_break)
		  break;
	 }
		 return TRUE;
/*   }
   else
   {
	LineInfo       *pLHor, *pLVer;
	pLHor = LTInfo->Hor.Lns;
    pLVer = LTInfo->Ver.Lns;

	hBlockLine = CPAGE_GetBlockFirst (Image->hCPAGE, RLINE_BLOCK_TYPE);
	if (!hBlockLine)
	{
		//sprintf (pStr, "����� �� ����������.");
		//return RV_EMPTY;
		bRet =  FALSE;
	}

	wErr32 = CPAGE_GetReturnCode ();

	if (wErr32!=0)
	{
		//Error_CPage ("[GetBlockFirst]");
		bRet =  FALSE;
	}
	//�����.... ��� �����?
	if ( bRet )
	{
		nReal = CPAGE_GetBlockData (Image->hCPAGE, hBlockLine, RLINE_BLOCK_TYPE, (void *)LTInfo, nTagSize);
		
		wErr32 = CPAGE_GetReturnCode ();
	}
	
	if ((nReal!=nTagSize)||(wErr32!=0))
	{
		//Error_CPage ("[GetBlockData]");
		bRet = FALSE;
	}
	if (LTInfo->Hor.Cnt + LTInfo->Ver.Cnt >= PUMAMaxNumLines)
	{
		//sprintf (pStr, "�� ������� ������ ��� %d �����!", LTInfo.Hor.Cnt + LTInfo.Ver.Cnt);
		//return RV_DOUBT;
		bRet = FALSE;
	}
	//  �������������� �����  
	if ( bRet && pLHor != NULL )
	{
		for (Int32 i=0; i<LTInfo->Hor.Cnt; i++)
		{ 
			if (i==0)
				hBlockLineHor = CPAGE_GetBlockFirst (Image->hCPAGE, (Word32)(LTInfo->Hor.Lns));
			else
				hBlockLineHor = CPAGE_GetBlockNext (Image->hCPAGE, hBlockLinePrev, (Word32)(LTInfo->Hor.Lns));
			wErr32 = CPAGE_GetReturnCode ();
			if (wErr32!=0)
			{
				//if (i==0)
					//Error_CPage ("[GetBlockFirst]");
				//else
					//Error_CPage ("[GetBlockNext]");
				bRet = FALSE;
				break;
			}
			nTagSize = sizeof (LineInfo);
			nReal = CPAGE_GetBlockData (Image->hCPAGE, hBlockLineHor, (Word32)(LTInfo->Hor.Lns), (void *)&(pLHor[i]), nTagSize);
			wErr32 = CPAGE_GetReturnCode ();
			if ((nReal!=nTagSize)||(wErr32!=0))
			{
				//Error_CPage ("[GetBlockData]");
				bRet = FALSE;
				break;
			}
			hBlockLinePrev = hBlockLineHor;
		}
	}
	// ������������ �����  
	if ( bRet && pLVer != NULL )
	{
		for (Int32 i=0; i<LTInfo->Ver.Cnt; i++)
		{ 
			if (i==0)
				hBlockLineVer = CPAGE_GetBlockFirst (Image->hCPAGE, (Word32)(LTInfo->Ver.Lns));
			else
				hBlockLineVer = CPAGE_GetBlockNext (Image->hCPAGE, hBlockLinePrev, (Word32)(LTInfo->Ver.Lns));
			wErr32 = CPAGE_GetReturnCode ();
			if (wErr32!=0)
			{
				//if (i==0)
					//Error_CPage ("[GetBlockFirst]");
				//else
					//Error_CPage ("[GetBlockNext]");
				bRet = FALSE;
				break;
			}
			nTagSize = sizeof (LineInfo);
			nReal = CPAGE_GetBlockData (Image->hCPAGE, hBlockLineVer, (Word32)(LTInfo->Ver.Lns), (void *)&(pLVer[i]), nTagSize);
			wErr32 = CPAGE_GetReturnCode ();
			if ((nReal!=nTagSize)||(wErr32!=0))
			{
				//Error_CPage ("[GetBlockData]");
				bRet = FALSE;
				break;
			}
			hBlockLinePrev = hBlockLineVer;
		}
	}
	LTInfo->Hor.Lns = pLHor;
	LTInfo->Ver.Lns = pLVer;

   }
*/
	return bRet;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
Bool32 SVLFilter(LinesTotalInfo *LtiA, LinesTotalInfo *LtiB, PRMPreProcessImage Image)
{
	Bool32 rc = TRUE;
	Word32 LinesTotalA;
	Word32 LinesTotalB;
	char str[255];
	Int32 j = 0;
	Word32 SVLCount = 0;
	Rect16 ZoomRect;
	
	bShowDebug     = !LDPUMA_Skip(Image->hDebugSVLines);
	bShowStepDebug = !LDPUMA_Skip(Image->hDebugSVLinesStep);
	bShowDebugData = !LDPUMA_Skip(Image->hDebugSVLinesData);

	if ( LtiA == NULL || LtiB == NULL )
	{
		rc = FALSE;
		return rc;
	}

	LinesTotalA = LtiA->Ver.Cnt;
	LinesTotalB = LtiB->Ver.Cnt;
	
	if ( ( bShowDebug || bShowStepDebug )&& bShowDebugData ) 
	{
		sprintf( str, "VSL: �� ������ ������ - %i, ����� - %i\n", LinesTotalA, LinesTotalB);
		LDPUMA_Console(str);
	}

	for (Word32 i=0; i<LinesTotalB; i++)
	{
		if ( LtiB->Ver.Lns[i].Flags != LtiA->Ver.Lns[i].Flags )
		{
			if ( !(LtiA->Ver.Lns[i].Flags & LI_IsTrue) && (LtiB->Ver.Lns[i].Flags & LI_IsTrue) )
			{
				
				if ( SVLCount != 0 && bShowStepDebug )
					LDPUMA_WaitUserInput( Image->hDebugSVLinesStep, NULL );
				
				if ( bShowDebug || bShowStepDebug)
				{
					j = sprintf( str, "VSL: < %4.4i, %4.4i > < %4.4i, %4.4i > x %3.3i flag: from %#8.8x to %#8.8x", 
								 LtiB->Ver.Lns[i].A.x, 
								 LtiA->Ver.Lns[i].A.y, 
								 LtiB->Ver.Lns[i].B.x, 
								 LtiB->Ver.Lns[i].B.y, 
								 LtiB->Ver.Lns[i].Thickness, 
								 LtiA->Ver.Lns[i].Flags, 
								 LtiB->Ver.Lns[i].Flags);

					j += sprintf( str + j, " - �������");
				
					j += sprintf ( str + j, "\n");		
					
					if ( bShowDebugData )
						LDPUMA_Console(str);

					LDPUMA_DrawLine(NULL, &LtiB->Ver.Lns[i].A, &LtiB->Ver.Lns[i].B, 0/*LtiB->Skew1024*/, 0x00ff00, LtiB->Ver.Lns[i].Thickness, 315 );

					ZoomRect.top    = LtiB->Ver.Lns[i].A.y <= LtiB->Ver.Lns[i].B.y ? LtiB->Ver.Lns[i].A.y : LtiB->Ver.Lns[i].B.y;
					ZoomRect.bottom = LtiB->Ver.Lns[i].A.y >  LtiB->Ver.Lns[i].B.y ? LtiB->Ver.Lns[i].A.y : LtiB->Ver.Lns[i].B.y;
					ZoomRect.left   = LtiB->Ver.Lns[i].A.x <= LtiB->Ver.Lns[i].B.x ? LtiB->Ver.Lns[i].A.x : LtiB->Ver.Lns[i].B.x;
					ZoomRect.right  = LtiB->Ver.Lns[i].A.x >  LtiB->Ver.Lns[i].B.x ? LtiB->Ver.Lns[i].A.x : LtiB->Ver.Lns[i].B.x;
					ZoomRect.bottom -= ((ZoomRect.top - ZoomRect.bottom) / 3) >= ZoomRect.bottom ? ZoomRect.bottom : ((ZoomRect.top - ZoomRect.bottom) / 3);
					ZoomRect.top    += ((ZoomRect.top - ZoomRect.bottom) / 3);
					ZoomRect.left   -= ((ZoomRect.right - ZoomRect.left) / 3) >= ZoomRect.left ? ZoomRect.left : ((ZoomRect.right - ZoomRect.left) / 3);
					ZoomRect.right  += ((ZoomRect.right - ZoomRect.left) / 3);
					
					if ( bShowStepDebug )
						LDPUMA_ZoomToRect(NULL, &ZoomRect);

				}
				
				if ( !SVLComponentFilter(&LtiB->Ver.Lns[i], Image) )
				{
					rc = FALSE;
					break;
				}
				SVLCount++;
			}
		}
	}

	if ( bShowDebug || bShowStepDebug )
	{
		if ( j == 0 && bShowDebugData )
		{
			LDPUMA_Console("VSL: ������ ��������� �� �������\n");
		}
		else
		{
			LDPUMA_Console("VSL: ������� %i �����. ����� �� ��� ������ � ������ ������...\n", SVLCount);
			LDPUMA_WaitUserInput( Image->hDebugSVLines, NULL );
			LDPUMA_DeleteLines(NULL, 315);
			LDPUMA_DeleteRects(NULL, 316);
			ZoomRect.top    = 0;
			ZoomRect.bottom = 0;
			
			if ( bShowStepDebug ) 
				LDPUMA_ZoomToRect(NULL, &ZoomRect);
		}
	}
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
Bool32 SVLComponentFilter(LineInfo *Line, PRMPreProcessImage Image)
{
	CCOM_comp * pcomp;
	CCOM_comp * pdeadcom;
	Bool32 GoodComp;
	Rect16 Rc;
	Rect16 Rl;
	Int32 nRc = 0;
	Int32 Filter = 0;
	Int32 j = 0;
	char str[255];
	Int16 Thick = Line->Thickness / 2;
	Bool32 bDieComponent = FALSE;


	Rl.left   = Line->A.x;
	Rl.top    = Line->A.y;
	Rl.right  = Line->B.x;
	Rl.bottom = Line->B.y;

	if ( Rl.left <= Rl.right )
	{
		Rl.left  -= Thick;
		Rl.right += Thick;
	}
	else
	{
		Rl.left  += Thick;
		Rl.right -= Thick;
	}
	
	pcomp = CCOM_GetFirst ((Int32)(Image->hCCOM), NULL);
	
	do
	{
		GoodComp = CompIsGood (pcomp, Filter);
		
		if (GoodComp)
		{
			Rc.left   = pcomp->left;
			Rc.right  = pcomp->left + pcomp->w - 1;
			Rc.top    = pcomp->upper;
			Rc.bottom = pcomp->upper + pcomp->h - 1;
			nRc++;

			if ( IsRectIntersect(&Rl, &Rc) )
			{
				if ( Image->gKillVSLComponents )
				{
					pdeadcom = pcomp;
					pcomp = CCOM_GetNext (pcomp, NULL);
					bDieComponent = CCOM_Delete((Int32)(Image->hCCOM), pdeadcom);
				}

				if ( bShowDebug || bShowStepDebug )
				{
					j = sprintf( str, "VSL: intersect component < %4.4i, %4.4i > < %4.4i, %4.4i >", Rc.left, Rc.top, Rc.right, Rc.bottom ); 

					if ( bDieComponent )
						j += sprintf( str + j, " +dead+" );

					j += sprintf( str + j, "\n" );
					
					if ( bShowDebugData ) 
						LDPUMA_Console(str);

					LDPUMA_DrawRect(NULL, &Rc, 0, 0xff0000, 1, 316);
					bDieComponent = FALSE;
				}
			}
		}
		
		if ( !bDieComponent )
			pcomp = CCOM_GetNext (pcomp, NULL);
		else // Almi 18.09.00
			bDieComponent = FALSE;
		
		
	} while( pcomp != NULL );
	
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
Bool32 IsRectIntersect(Rect16 *A, Rect16 *B)
{
	Bool32 rc = FALSE;

	Int32 M1 = A->bottom >= A->top  ? A->bottom : A->top;
	Int32 M2 = A->right  >= A->left ? A->right  : A->left;
	Int32 m1 = A->bottom >= A->top  ? A->top    : A->bottom;
	Int32 m2 = A->right  >= A->left ? A->left   : A->right;
	Int32 M3 = B->bottom >= B->top  ? B->bottom : B->top;
	Int32 M4 = B->right  >= B->left ? B->right  : B->left;
	Int32 m3 = B->bottom >= B->top  ? B->top    : B->bottom;
	Int32 m4 = B->right  >= B->left ? B->left   : B->right;

	if ( ( ( ( B->top >= m1 ) && ( B->top <= M1 ) ) || ( ( B->bottom >= m1 ) && ( B->bottom <= M1 ) ) ) &&
		 ( ( ( B->left >= m2 ) && ( B->left <= M2 ) ) || ( ( B->right >= m2 ) && ( B->right <= M2 ) ) ) )
	{
		rc = TRUE;
	}

	if ( ( ( ( A->top >= m3 ) && ( A->top <= M3 ) ) || ( ( A->bottom >= m3 ) && ( A->bottom <= M3 ) ) ) &&
		 ( ( ( A->left >= m4 ) && ( A->left <= M4 ) ) || ( ( A->right >= m4 ) && ( A->right <= M4 ) ) ) )
	{
		rc = TRUE;
	}
	
	return rc;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� � ���������. ������ ��������, ��������� ��������
Bool32 CompIsGood (CCOM_comp * pcomp, Int32 Filter)
{
	switch (Filter)
	{
		case 0 :
			return TRUE;
		default :
			return FALSE;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file