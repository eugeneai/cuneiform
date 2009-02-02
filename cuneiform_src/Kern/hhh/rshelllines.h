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

// RShellLines.h: interface for the ShellLine's functions.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//
//	Description: ShellLine's functions definition
//
//	Implemented: by B.M. Shahverdiev
//
//

#include "globus.h"

#ifdef __RSHELLLINES_EXPORTS__
  #define RSHELLLINES_FUNC  FUN_EXPO
  #define RSHELLLINES_CLASS CLASS_EXPO
#else
  #define RSHELLLINES_FUNC  FUN_IMPO
  #define RSHELLLINES_CLASS CLASS_IMPO
#endif

#define step             8
#define SizeWhitePicsels 1
#define SizeBlackPicsels 16
#define MAXRASTERSIZE    1000

int    SL_IsInPoly(Point32* a, CLINE_SL_POLY* p); //
BOOL   SL_IsPointInAB(Point32 *P,Point32 *A,Point32 *B); //
void   CalculateRectForRaster(DLine* pCLine, PAGEINFO* page_info); //
void   CalculatePolynomia(DLine* pCLine, PAGEINFO* page_info); //
void   DrowRectForRaster(Rect32* rect); //
void   DrowPolynomia(DLine* pCLine); //
//void   DrowGetCorrectedLineStripesIntervals(CLine* pCLine, Handle HndMyWindow);
void   DrowVerticalLineStripesIntervals(CLINE_handle line, Handle HndMyWindow);
void   CleaningRaster(DLine* pCLine, LPSTR Buffer); //
void   DrowCleanedRaster(DLine* pCLine, LPSTR Buffer, CIMAGEBITMAPINFOHEADER* image_info, Handle* HndMyWindow); //
void   DrowVerticalLineRaster(DLine* pCLine, LPSTR Buffer, CIMAGEBITMAPINFOHEADER* image_info, Handle* HndMyWindow); //
void   Transpose_bit_matrixes(PCHAR buf_in,PCHAR buf_out, Rect32* rect); //
BOOL   GetLineStripesIntervals(CLINE_handle line, DLine* pCLine, PCHAR  pRaster, BOOL FlagVerticalLine); //
//BOOL   GetCorrectedLineStripesIntervals(CLine* pCLine);
void   FillingStripes(CLINE_handle line, int y, INT Count, WORD* pIntervals, BOOL FlagVerticalLine, DLine* pCLine); //
void   CheckDotLines(DLine* pCLine, BOOL FlagVerticalLine); //
int    Bits2Ints(Word8* pBits, int nByteWidth, Int32* pIntervals); //
void   TypeIntervals(int y, INT Count, WORD* pIntervals); //
void   TypeStripe(CLINE_handle hStripe, DEvent* pStripe); //
BOOL   GetLineFragments(CLINE_handle line, DLine* pCLine); //
Handle DrawLineFragments(CLINE_handle line, CPDLine pCLine, Handle HndMyWindow, int ColorIndex, Bool32 ForAllLines = FALSE); //
//void DrawSeparationPoints(CLine* pCLine, Handle HndMyWindow);
BOOL   CorrectLineFragments(CLINE_handle line, DLine* pCLine); //
HANDLE GetTransposedRaster(DLine* pCLine, LPSTR Buffer, LPSTR* pRaster); //
void   FreeTransposedBuffer(HANDLE hbuf, LPSTR pRaster); //
void   DrowVerticalLineCutPoints(CLINE_handle line, Handle HndMyWindowVert); //
void   Drow2Rects(Rect32*  rect, Rect32*  rect1); //
void   DeleteNoiseEvents(CLINE_handle hLine, DLine* pLine);
void   CheckUnderlining(CLINE_handle hLine, DLine* pLine, LPSTR pSourceRaster);
Bool32 CompareRasterParts(CPDLine pLine, LPSTR pSourceRaster, Bool32 CheckSerif);
//////////////////////////////////////////////////////////////////////////////////
//
#ifdef __RSL_EXTERN__
	#define EXTERN
	#define VAL(a) = a
#else
	#define EXTERN extern
	#define VAL(a)
#endif


EXTERN Handle hDebugRSL					                   VAL( NULL );

EXTERN Handle hDebugFrag                                   VAL( NULL );
EXTERN Handle hDebugFragOwner                              VAL( NULL );
EXTERN Handle hDebugDrowPolynomia                          VAL( NULL );
EXTERN Handle hDebugDrowRectForRaster                      VAL( NULL );
EXTERN Handle hDebugDrowCleanedRaster                      VAL( NULL );
EXTERN Handle hDebugDrowGetCorrectedLineStripesIntervals   VAL( NULL );
//EXTERN Handle hDebugDrowFriendLines                        VAL( NULL );
//EXTERN Handle hDebugDrowGroupOfExtensibleLines             VAL( NULL );
EXTERN Handle hDebugDroweparationPoints                    VAL( NULL );
//EXTERN Handle hDebugDrawLosedVerticalLines                 VAL( NULL );


EXTERN Handle hDebugDrowVerticalLineRaster                 VAL( NULL );
EXTERN Handle hDebugDrowVerticalLineStripesIntervals       VAL( NULL );
EXTERN Handle hDebugDrowVerticalLineCutPoints              VAL( NULL );

EXTERN Handle hDebugTypeIntervals                          VAL( NULL );
EXTERN Handle hDebugTypeStripe                             VAL( NULL );
EXTERN Handle hDebugDrawLineFragments                      VAL( NULL );
//EXTERN Handle hDebugDrawAllLineFragments                   VAL( NULL );
EXTERN Handle hDebugDrawLineFragmentsOwnWindow             VAL( NULL );

EXTERN Handle hDebugAttr                                   VAL( NULL );
EXTERN Handle hDebugAttrOwner                              VAL( NULL );
EXTERN Handle hDebugTypeWidth                              VAL( NULL );
EXTERN Handle hDebugTypeDegree                             VAL( NULL );

//EXTERN Handle hDebugDrowPass3                              VAL( NULL );
//EXTERN Handle hDebugDrowTableZone                          VAL( NULL );


EXTERN Handle hDebugProfileRSL	      	        		   VAL( NULL );
//EXTERN Handle hDebugProfStart	      	        		   VAL( NULL );
EXTERN Handle hDebugProfFindLineFrag  	        		   VAL( NULL );
EXTERN Handle hDebugProfEndFindLineFrag                    VAL( NULL );
EXTERN Handle hDebugProfSL_GetRaster                       VAL( NULL );
