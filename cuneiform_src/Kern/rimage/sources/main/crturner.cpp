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

// �RTurner.cpp: implementation of the CRTurner class.
//
//////////////////////////////////////////////////////////////////////
//#define RIMAGE_DUMP_TO_FILE
//////////////////////////////////////////////////////////////////////
#include "globus.h"
#include "crturner.h"
//#include "turn.h"
#include "criimage.h"
#include "crimemory.h"
#include "resource.h"
#include "memory.h"
//#include "dpuma.h"
#ifdef RIMAGE_DUMP_TO_FILE
#include "PumaMemoryToFileDumper.h"
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRTurner::CRTurner()
{
	Word32 i,j;
	Word8 mask, mask2;

	hLineBuffer = 0x00000000;   //NULL;

	wRightMask[0] = 0xfe;
	wLeftMask[0] = 0x7f;
	wRightShift[0] = 7;
	wBitMask[7] = 0x01;

	for ( i = 1; i < 8; i++ )
	{
		wRightMask[i] =  wRightMask[i - 1] << 1;

		wLeftMask[i] = wLeftMask[i - 1] >> 1;

		wRightShift[i] = wRightShift[i-1] - 1;

		wBitMask[7 - i] = wBitMask[8 - i] << 1;
	}

    for(i = 0; i < 256; i++)
    {
		Turn1at180[i] = 0;

		mask = 0x80;
		mask2 = 0x1;

		for(j = 0; j < 8; mask >>= 1, mask2 <<= 1, j++)
		{
			if((i & mask) != 0)
				Turn1at180[i] += mask2;

		}
	}

	for( i = 0; i < 132; i++)
	{
		memset(Turn1at90[i], 0x0, 8);
	}

	for( i = 0; i < 8; i++ )
		for (j = 0; j < 8; j++ )
		{
			Turn1at90[wBitMask[i]][j] = wBitMask[j];
		}
}

CRTurner::~CRTurner()
{

}

void * CRTurner::TurnDIB(void *pDIB, Word32 wAngle)
{
    return NULL;
}

Bool32 CRTurner::FreeDIB(void *pDIB)
{
	return TRUE;
}

Bool32 CRTurner::TurnDIB(PCTDIB pInDIB, PCTDIB pOutDIB, Word32 wAngle)
{
	Bool32 bRet;

	if ( !pInDIB || !pOutDIB )
		return FALSE;

	WriteDIBtoBMP("BeforeTurn.bmp",pInDIB);

	switch(wAngle)
	{
	case RIMAGE_TURN_90:
		bRet = Turn90(pInDIB, pOutDIB);
		break;
	case RIMAGE_TURN_270:
		bRet = Turn270(pInDIB, pOutDIB);
		break;
	case RIMAGE_TURN_180:
		bRet = Turn180(pInDIB, pOutDIB);
		break;

	default:
		bRet = FALSE;

	}

	WriteDIBtoBMP("AfterTurn.bmp", pInDIB);
	if ( bRet )
		WriteDIBtoBMP("DestinationTurn.bmp", pOutDIB);

	return bRet;
}

Bool32 CRTurner::Turn90(PCTDIB pInDIB, PCTDIB pOutDIB)
{
	Bool32 bRet = FALSE;

	if ( CheckInAndOut90(pInDIB, pOutDIB) )
	{
		switch (pInDIB->GetPixelSize())
		{
		case 1 :
			bRet = Turn90LA(pInDIB, pOutDIB);
			break;
		case 8:
		case 16:
		case 24:
		case 32:
			bRet = Turn90GC(pInDIB, pOutDIB);
			break;

		default:
			bRet = FALSE;
		}
	}

	return bRet;
}

Bool32 CRTurner::Turn180(PCTDIB pInDIB, PCTDIB pOutDIB)
{
	Bool32 bRet = FALSE;

	if ( CheckInAndOut180(pInDIB, pOutDIB) )
	{
		switch (pInDIB->GetPixelSize())
		{
		case 1 :
			bRet = Turn180LA(pInDIB, pOutDIB);
			break;
		case 8:
		case 16:
		case 24:
		case 32:
			bRet = Turn180GC(pInDIB, pOutDIB);
			break;

		default:
			bRet = FALSE;
		}
	}

	return bRet;
}

Bool32 CRTurner::Turn270(PCTDIB pInDIB, PCTDIB pOutDIB)
{
	Bool32 bRet = FALSE;

	if ( CheckInAndOut90(pInDIB, pOutDIB) )
	{
		switch (pInDIB->GetPixelSize())
		{
		case 1 :
			bRet = Turn270LA(pInDIB, pOutDIB);
			break;
		case 8:
		case 16:
		case 24:
		case 32:
			bRet = Turn270GC(pInDIB, pOutDIB);
			break;

		default:
			bRet = FALSE;
		}
	}

	return bRet;
}

Bool32 CRTurner::Turn180LA(PCTDIB pInDIB, PCTDIB pOutDIB)
{
	Bool32 bRet = FALSE;
	Word32 nLine;
	Word32 sLine;
	Word32 sLineSize;
	Word32 sShift;
	Word32 rShift;
	PWord8 sPix;
	PWord8 nPix;
	Word32 wLines = pInDIB->GetLinesNumber();
	Word32 sLineWidth = pInDIB->GetLineWidth();
	Word32 sBytesPerLine = pOutDIB->GetUsedLineWidthInBytes();
	Word32 cByte;

	FreeBuffers();

	hLineBuffer = RIMAGEDAlloc((sLineSize = pInDIB->GetLineWidthInBytes()),"CRTurner::Turn180LA - line buffer" );
	LineBuffer  = (PWord8)RIMAGELock(hLineBuffer);

	// ������� ���������� �������
	sShift = pOutDIB->GetPixelShiftInByte(pOutDIB->GetLineWidth() - 1);
	rShift = 7 - sShift;

	for( nLine = 0, sLine = wLines - 1; nLine < wLines; nLine++, sLine--)
	{
		// �������� � ����� ��� ������ � ��� ���� �������� �
		sPix = (PWord8)pInDIB->GetPtrToLine(sLine);

		if ( sShift == 7 )
		{
			nPix = (PWord8)pOutDIB->GetPtrToLine(nLine) + sBytesPerLine - 1;
		}
		else
		{
			nPix = LineBuffer + sBytesPerLine - 1;
		}

		for (  cByte = 0; cByte < sBytesPerLine; cByte++ )
		{
			// ������ �������� �������������
			*nPix = Turn1at180[*sPix];
			nPix--;
			sPix++;
		}

		if ( sShift != 7 )
		{
			nPix = LineBuffer;

			for (  cByte = 0; cByte < sBytesPerLine; cByte++ )
			{
				// ��������
				*nPix = (*nPix) << rShift;
				*nPix |= (*(nPix + 1) >> (sShift + 1) ) & (wLeftMask[sShift]);
				nPix++;
			}
			// ������ �������� � ��������
			sPix = LineBuffer;
			nPix = (PWord8)pOutDIB->GetPtrToLine(nLine);
			memcpy(nPix, sPix, sBytesPerLine);
		}
		bRet = TRUE;
	}

	FreeBuffers();

	return bRet;
}

void CRTurner::FreeBuffers()
{
	if ( hLineBuffer )
	{
		RIMAGEFree(hLineBuffer);
		hLineBuffer = 0x00000000;//NULL;
	}
}

Bool32 CRTurner::CheckInAndOut180(PCTDIB pIn, PCTDIB pOut)
{
	if ( pIn->GetImageHeight() != pOut->GetImageHeight() ||
		 pIn->GetImageWidth()  != pOut->GetImageWidth()  ||
		 pIn->GetPixelSize()   != pOut->GetPixelSize()      )
	{
		SetReturnCode_rimage(IDS_RIMAGE_OUTCOME_DIB_NOT_LINK_TO_INCOME);
		 return FALSE;
	}

	return TRUE;
}

Bool32 CRTurner::CheckInAndOut90(PCTDIB pIn, PCTDIB pOut)
{
	if ( pIn->GetImageHeight() != pOut->GetImageWidth() ||
		 pIn->GetImageWidth()  != pOut->GetImageHeight()  ||
		 pIn->GetPixelSize()   != pOut->GetPixelSize()      )
	{
		SetReturnCode_rimage(IDS_RIMAGE_OUTCOME_DIB_NOT_LINK_TO_INCOME);
		return FALSE;
	}

	return TRUE;
}

Bool32 CRTurner::Turn90LA(PCTDIB pInDIB, PCTDIB pOutDIB)
{
	Word32 dLines = pOutDIB->GetLinesNumber();
	Word32 sLines = pInDIB->GetLinesNumber();  //
	Int32  sX;
	Int32  dX;
	Int32  dLine;
	Int32  sLine;
	PWord8 sPix;
	PWord8 dPix;
	Word32 sBytesPerLine = pOutDIB->GetLineWidth()/8;
	Word32 cByte;
	Word32 sShift;

	for ( dLine = 0, sX = 0; dLine < (Int32)dLines; dLine++, sX++ )
	{
		// ������ �����
		dPix = (PWord8)pOutDIB->GetPtrToLine(dLine);
		// �����
		sShift = pInDIB->GetPixelShiftInByte(sX);
		// �� 8 ��������
		for ( cByte = 0, sLine = sLines - 1, dX = 0; cByte < sBytesPerLine; cByte++, dX += 8 )
		{
			*dPix = 0x0;

			//x.......
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][0];

			//.x......
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][1];

			//..x.....
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][2];

			//...x....
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][3];

			//....x...
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][4];

			//.....x..
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][5];

			//......x.
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][6];

			//.......x
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine--);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][7];

			dPix++;
		}

		// ��������� �������� ������
		if ( sLine >= 0 )
		{
			*dPix = 0x0;

			for ( ; sLine >= 0; sLine--, dX++ )
			{
				sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine);
				*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][(pOutDIB->GetPixelShiftInByte(dX))];
			}
		}
	}
	return TRUE;
}

Bool32 CRTurner::Turn270LA(PCTDIB pInDIB, PCTDIB pOutDIB)
{
	Word32 dLines = pOutDIB->GetLinesNumber();
	Word32 sLines = pInDIB->GetLinesNumber();  //
	Int32  sX;
	Int32  dX;
	Int32  dLine;
	Int32  sLine;
	PWord8 sPix;
	PWord8 dPix;
	Word32 sBytesPerLine = pOutDIB->GetLineWidth()/8;
	Word32 cByte;
	Word32 sShift;

	for ( dLine = 0, sX = dLines - 1; dLine < (Int32)dLines; dLine++, sX-- )
	{
		// ������ �����
		dPix = (PWord8)pOutDIB->GetPtrToLine(dLine);
		// �����
		sShift = pInDIB->GetPixelShiftInByte(sX);
		// �� 8 ��������
		for ( cByte = 0, sLine = 0, dX = 0; cByte < sBytesPerLine; cByte++, dX += 8 )
		{
			*dPix = 0x0;

			//x.......
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][0];

			//.x......
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][1];

			//..x.....
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][2];

			//...x....
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][3];

			//....x...
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][4];

			//.....x..
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][5];

			//......x.
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][6];

			//.......x
			sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine++);
			*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][7];

			dPix++;
		}

		// ��������� �������� ������
		// ���� ����
		if ( sLine < (Int32)sLines )
		{
			*dPix = 0x0;

			for ( ; sLine < (Int32)sLines; sLine++, dX++ )
			{
				sPix = (PWord8)pInDIB->GetPtrToPixel(sX, sLine);

				*dPix |= Turn1at90[((*sPix)&wBitMask[sShift])][(pOutDIB->GetPixelShiftInByte(dX))];
			}
		}
	}
	return TRUE;
}

Bool32 CRTurner::Turn90GC(PCTDIB pIn, PCTDIB pOut)
{
	Bool32  bRet = FALSE;
	Int32   sX;
	Int32   dX;
	Int32   dLine;
	Int32   sLine;
	PWord8  sPix8;
	PWord8  dPix8;
	PWord16 sPix16;
	PWord16 dPix16;
	PWord32 sPix32;
	PWord32 dPix32;
	Word32  dLines = pOut->GetLinesNumber();
	Word32  sLines = pIn->GetLinesNumber();  //
	Word32  wPixSize = pIn->GetPixelSize() / 8;

	switch (wPixSize)
	{
	case 1:
		for( dLine = 0, sX = 0;  dLine < (Int32)dLines; dLine++, sX++ )
		{
		CONTINUEPIXEL(dPix8 = (PWord8)pOut->GetPtrToLine( dLine ));

			for ( sLine = sLines - 1, dX = 0; dX < (Int32)sLines; sLine--, dX++, dPix8++ )
			{
				CONTINUEPIXEL(sPix8 = (PWord8)pIn->GetPtrToPixel( sX, sLine));
				*dPix8 = *sPix8;
			}
		}
		bRet = TRUE;
		break;

	case 2:
		for( dLine = 0, sX = 0;  dLine < (Int32)dLines; dLine++, sX++ )
		{
			CONTINUEPIXEL(dPix16 = (PWord16)pOut->GetPtrToLine( dLine ));

			for ( sLine = sLines - 1, dX = 0; dX < (Int32)sLines; sLine--, dX++, dPix16++ )
			{
				CONTINUEPIXEL(sPix16 = (PWord16)pIn->GetPtrToPixel( sX, sLine));
				*dPix16 = *sPix16;
			}
		}
		bRet = TRUE;
		break;

	case 3:
		for( dLine = 0, sX = 0;  dLine < (Int32)dLines; dLine++, sX++ )
		{
			CONTINUEPIXEL(dPix8 = (PWord8)pOut->GetPtrToLine( dLine )) ;

			for ( sLine = sLines - 1, dX = 0; dX < (Int32)sLines; sLine--, dX++ )
			{
				CONTINUEPIXEL(sPix8 = (PWord8)pIn->GetPtrToPixel( sX, sLine));
				*dPix8++ = *sPix8++;
				*dPix8++ = *sPix8++;
				*dPix8++ = *sPix8++;
			}
		}
		bRet = TRUE;
		break;

	case 4:
		for( dLine = 0, sX = 0;  dLine < (Int32)dLines; dLine++, sX++ )
		{
			CONTINUEPIXEL(dPix32 = (PWord32)pOut->GetPtrToLine( dLine ));

			for ( sLine = sLines - 1, dX = 0; dX < (Int32)sLines; sLine--, dX++, dPix32++ )
			{
				CONTINUEPIXEL(sPix32 = (PWord32)pIn->GetPtrToPixel( sX, sLine));
				*dPix32 = *sPix32;
			}
		}
		bRet = TRUE;
		break;

	default:
		bRet = FALSE;
	}

	return bRet;
}

Bool32 CRTurner::Turn180GC(PCTDIB pIn, PCTDIB pOut)
{
	Bool32  bRet = FALSE;
	Word32  dLine;
	Word32  sLine;
	Word32  wPix;
	PWord8  sPix8;
	PWord8  dPix8;
	PWord16 sPix16;
	PWord16 dPix16;
	PWord32 sPix32;
	PWord32 dPix32;
	Word32  wPixSize = pIn->GetPixelSize() / 8;
	Word32  wLines = pIn->GetLinesNumber();
	Word32  sLineWidth = pIn->GetLineWidth();

	switch (wPixSize)
	{
	case 1:
		for( dLine = 0, sLine = wLines - 1; dLine < wLines; dLine++, sLine--)
		{
			sPix8 = (PWord8)pIn->GetPtrToPixel( sLineWidth - 1, sLine);
			dPix8 = (PWord8)pOut->GetPtrToLine( dLine );

			for ( wPix = 0; wPix < sLineWidth; wPix++, sPix8 --, dPix8 ++ )
			{
				*dPix8 = *sPix8;
			}
		}
		bRet = TRUE;
		break;

	case 2:
		for( dLine = 0, sLine = wLines - 1; dLine < wLines; dLine++, sLine--)
		{
			sPix16 = (PWord16)pIn->GetPtrToPixel( sLineWidth - 1, sLine);
			dPix16 = (PWord16)pOut->GetPtrToLine( dLine );

			for ( wPix = 0; wPix < sLineWidth; wPix++, sPix16 --, dPix16 ++ )
			{
				*dPix16 = *sPix16;
			}
		}
		bRet = TRUE;
		break;

	case 3:
		for( dLine = 0, sLine = wLines - 1; dLine < wLines; dLine++, sLine--)
		{
			sPix8 = (PWord8)pIn->GetPtrToPixel( sLineWidth - 1, sLine);
			dPix8 = (PWord8)pOut->GetPtrToLine( dLine );

			for ( wPix = 0; wPix < sLineWidth; wPix++, sPix8 -= 6)
			{
				*dPix8++ = *sPix8++;
				*dPix8++ = *sPix8++;
				*dPix8++ = *sPix8++;
			}
		}
		bRet = TRUE;
		break;

	case 4:
		for( dLine = 0, sLine = wLines - 1; dLine < wLines; dLine++, sLine--)
		{
			sPix32 = (PWord32)pIn->GetPtrToPixel( sLineWidth - 1, sLine);
			dPix32 = (PWord32)pOut->GetPtrToLine( dLine );

			for ( wPix = 0; wPix < sLineWidth; wPix++, sPix32--, dPix32++ )
			{
				*dPix32 = *sPix32;
			}
		}
		bRet = TRUE;
		break;

	default:
		bRet = FALSE;
	}

	return bRet;
}

Bool32 CRTurner::Turn270GC(PCTDIB pIn, PCTDIB pOut)
{
	Bool32  bRet = FALSE;
	Int32   sX;
	Int32   dX;
	Int32   dLine;
	Int32   sLine;
	PWord8  sPix8;
	PWord8  dPix8;
	PWord16 sPix16;
	PWord16 dPix16;
	PWord32 sPix32;
	PWord32 dPix32;
	Word32  dLines = pOut->GetLinesNumber();
	Word32  sLines = pIn->GetLinesNumber();  //
	Word32  wPixSize = pIn->GetPixelSize() / 8;

	switch (wPixSize)
	{
	case 1:
		for( dLine = 0, sX = dLines - 1;  dLine < (Int32)dLines; dLine++, sX-- )
		{
			CONTINUEPIXEL(dPix8 = (PWord8)pOut->GetPtrToLine( dLine ));

			for ( sLine = 0, dX = 0; sLine < (Int32)sLines; sLine++, dX++, dPix8++ )
			{
				CONTINUEPIXEL(sPix8 = (PWord8)pIn->GetPtrToPixel( sX, sLine));
				*dPix8 = *sPix8;
			}
		}
		bRet = TRUE;
		break;

	case 2:
		for( dLine = 0, sX = dLines - 1;  dLine < (Int32)dLines; dLine++, sX-- )
		{
			CONTINUEPIXEL(dPix16 = (PWord16)pOut->GetPtrToLine( dLine ));

			for ( sLine = 0, dX = 0; sLine < (Int32)sLines; sLine++, dX++, dPix16++ )
			{
				CONTINUEPIXEL(sPix16 = (PWord16)pIn->GetPtrToPixel( sX, sLine));
				*dPix16 = *sPix16;
			}
		}
		bRet = TRUE;
		break;

	case 3:
		for( dLine = 0, sX = dLines - 1;  dLine < (Int32)dLines; dLine++, sX-- )
		{
			CONTINUEPIXEL(dPix8 = (PWord8)pOut->GetPtrToLine( dLine ));

			for ( sLine = 0, dX = 0; sLine < (Int32)sLines; sLine++, dX++  )
			{
				CONTINUEPIXEL(sPix8 = (PWord8)pIn->GetPtrToPixel( sX, sLine));
				*dPix8++ = *sPix8++;
				*dPix8++ = *sPix8++;
				*dPix8++ = *sPix8++;
			}
		}
		bRet = TRUE;
		break;

	case 4:
		for( dLine = 0, sX = dLines - 1;  dLine < (Int32)dLines; dLine++, sX-- )
		{
			CONTINUEPIXEL(dPix32 = (PWord32)pOut->GetPtrToLine( dLine ));

			for ( sLine = 0, dX = 0; sLine < (Int32)sLines; sLine++, dX++, dPix32++ )
			{
				CONTINUEPIXEL(sPix32 = (PWord32)pIn->GetPtrToPixel( sX, sLine));
				*dPix32 = *sPix32;
			}
		}
		bRet = TRUE;
		break;

	default:
		bRet = FALSE;
	}

	return bRet;
}

Bool32 CRTurner::WriteDIBtoBMP(PChar8 cName, PCTDIB pDIB)
{
#ifdef RIMAGE_DUMP_TO_FILE
	Word32  wBMPSize = pDIB->GetDIBSize() + 14;
	PumaMemoryToFileDumper BMPDump(cName);

	BMPDump.AddDump("BM",2);
	BMPDump.AddDump((char *)&wBMPSize,4);
	wBMPSize = 0;
	BMPDump.AddDump((char *)&wBMPSize,4);
	wBMPSize = 14 + pDIB->GetHeaderSize() + pDIB->GetRGBPalleteSize();
	BMPDump.AddDump((char *)&wBMPSize,4);
	BMPDump.AddDump(pDIB->GetPtrToHeader(), pDIB->GetDIBSize());
	BMPDump.EndDump();
#endif
	return TRUE;
}
