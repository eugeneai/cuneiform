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

#include "lnslang.h"

#ifndef PPS_MAC
#pragma hdrstop
#endif
#include "lns.h"

#include <string.h>

#include "sbambuk.h"
#include "sweeper.h"

#include "memops.h"


static  TImageOpen  __f_op = NULL;
static  TImageRead  __f_rd = NULL;
static  TImageClose __f_cl = NULL;

//*******************Rom********************
   RomBubble* Romptr;// = new RomBubble ;
   //Romptr->next = NULL;
   RomBubble* Romptr2 = NULL;
   RomBubble* Romptr3 = Romptr;
   Word8	  tmp_w8;
   //div_t div_result;
//******************************************

#define Tiger_Callback_ImageOpen       (*__f_op)
#define Tiger_Callback_ImageRead       (*__f_rd)
#define Tiger_Callback_ImageClose      (*__f_cl)

#define BUF_LEN   ((Int32)0x7FFF)

//***********Rom**************
void SetRomptr ( RomBubble* rptr)
{
	Romptr = rptr;
}
//****************************

void  InitSweeperCallbacks(
	TImageOpen  f_op,
	TImageRead  f_rd,
	TImageClose f_cl
								  )
	{
      __f_op = f_op;
		__f_rd = f_rd;
		__f_cl = f_cl;
	};

static THVSegBambuk* hvSB = NULL;
void InitSweeperData( THVSegBambuk* sb )
   {
      hvSB=sb;
   };

static Bool MustCloseImage = FALSE;
static Tiger_ImageInfo ImageInfo;

//static BYTE* ImageBuf = NULL;
static Word8* LinesBuf = NULL;
//static BYTE* ResultBuf = NULL;
static Int32  CurLine = 0;
static Bool  Ready = FALSE;

Bool Sweeper_ImageOpen (Tiger_ImageInfo* lpImageInfo)
	{

		if (hvSB == NULL)
			return WRONG();
		if ((__f_op == NULL) || (__f_rd == NULL) || (__f_cl == NULL))
			return WRONG();

		assert(LinesBuf == NULL);
		assert(CurLine == 0);
		assert(!Ready);
		if (	(LinesBuf != NULL)  ||
				(CurLine != 0)      ||
				(Ready)
			)
			return WRONG();


      LinesBuf  = (Word8*)malloc( BUF_LEN );
		if (LinesBuf == NULL) return WRONG();

		MustCloseImage = TRUE;
		if (!Tiger_Callback_ImageOpen(lpImageInfo))
			return WRONG();
		ImageInfo = *lpImageInfo;
		if (ImageInfo.wImageByteWidth * 4 >= BUF_LEN )
			return WRONG();
		memset( LinesBuf, 0 , BUF_LEN );
		Ready =  TRUE;
		return TRUE;
	}

static void unpack_segments( Word8* dstprev, Word8* dst, Word8* dstnext, Int32 line )
{
		// after unpack segments black pixels are 1, white 0
		// initially all filled by 0
	TSegBambuk& sb = hvSB->hBambuk;
	if (line > sb.lastEntry() )
		return;

	BHandle sh = sb.firstEntryMember( line );

	while ( sh != NULLBHandle )
	{
		TBlackSeg& bs = sb[sh];
		if (bs.right < bs.left)
		{
			int right = bs.left+1;
			int left  = bs.right;
			int leftoff = left >> 3;
         Word8* pb    = dst      + leftoff;
         Word8* prev  = dstprev  + leftoff;
         Word8* next  = dstnext  + leftoff;

			Word8  left_byte = ( 0xFF >> ( left -  (leftoff<<3) ) );
			*pb++   |= left_byte;
			*prev++ |= left_byte;
			*next++ |= left_byte;

			int rightoff = right >> 3;
			for ( int i = rightoff - leftoff -1; i > 0; i-- )
			{
				*pb  ++    |= 0xFF;
				*prev++    |= 0xFF;
				*next++    |= 0xFF;
			}
			assert( (pb - dst) == rightoff );
			Word8 right_byte = ~( 0xFF >> ( right - (rightoff<<3) ) );
			*pb   |= right_byte;
			*prev |= right_byte;
			*next |= right_byte;;
		}
		sh = sb.nextMember( sh );
	}
}

Int16 Sweeper_ImageRead (Word8* lpImage, Word16 wMaxSize)
{
	if (!Ready)
      return 0;

   Int32 max_read_rqst = BUF_LEN - 4*ImageInfo.wImageByteWidth;
   Int32 size_read = (Int32)Tiger_Callback_ImageRead( (Word8*)lpImage, (Word16) MIN( wMaxSize, max_read_rqst ) );
	if (size_read ==0)
		return 0;
	assert( size_read <= max_read_rqst );
	assert( (size_read % ImageInfo.wImageByteWidth) == 0 );

   Int32 dw_size = ( size_read + 3 ) >> 2;
	int lines_read = size_read / ImageInfo.wImageByteWidth;
	assert( (ImageInfo.wAddX % 8) == 0 );
	Romptr2 = Romptr->next; //********Rom
	Romptr3 = Romptr;		//********Rom
   Word8* scn = LinesBuf + (ImageInfo.wAddX >> 3);
   /*
	if (CurLine == 0)  // first call
	{	unpack_segments( scn, scn, scn + ImageInfo.wImageByteWidth, CurLine );
		CurLine++;
	}
   */

	memset( LinesBuf, 0 , (lines_read+2) * ImageInfo.wImageByteWidth );

   if (CurLine > 0) // unpack upper line to suppress dusts under it
      unpack_segments(  scn, scn, scn + ImageInfo.wImageByteWidth, CurLine-1 );

	scn += ImageInfo.wImageByteWidth; // now scn shifted 1 line down;

	for ( int i=0; i<lines_read; i++, CurLine++, scn += ImageInfo.wImageByteWidth )
	{
		unpack_segments( 	scn-ImageInfo.wImageByteWidth,   // prev line
								scn,                             // cur line
								scn+ImageInfo.wImageByteWidth,   // next line
								CurLine
							);
		// after unpack segments black pixels are 1, white 0
	}

   ////// VP, 17 jun 99
   if (CurLine < ImageInfo.wImageHeight-1)
      unpack_segments( scn-ImageInfo.wImageByteWidth, scn, scn, CurLine+1 );
   //////////////////

	if (ImageInfo.bFotoMetrics)
	{  // white pixel is 1

		__CopyOR( lpImage, LinesBuf + ImageInfo.wImageByteWidth, size_read );

		//*******************Rom***************
		for (int j=0; j<lines_read; j++)
		{
			while (( Romptr2 != NULL )&&(Romptr2->Begin <= CurLine-lines_read+1+j))
			{
				if(Romptr2->Begin <= CurLine-lines_read+1+j)
				{
					if (Romptr2->End < CurLine-lines_read+1+j)
					{
						Romptr3->next = Romptr2->next;
						//delete Romptr2;
						Romptr2 = Romptr3;
					}
					else
					{
//						div_result = div ( Romptr2->Column, 8);
//						tmp_w8 = lbit_byte[div_result.rem];
//						lpImage[j*ImageInfo.wImageByteWidth+div_result.quot] |= tmp_w8;
                  int off = j*ImageInfo.wImageByteWidth + (Romptr2->Column >> 3);
                  int pix = Romptr2->Column & 7;
                  lpImage[off] |= ( 1 << (7-pix) );
                  int off1 = j*ImageInfo.wImageByteWidth + ((Romptr2->Column+1) >> 3);
                  int pix1 = (Romptr2->Column+1) & 7;
                  lpImage[off1] |= ( 1 << (7-pix1) );
                  int off2 = j*ImageInfo.wImageByteWidth + ((Romptr2->Column-1) >> 3);
                  int pix2 = (Romptr2->Column-1) & 7;
                  lpImage[off2] |= ( 1 << (7-pix2) );
					}
				}
				Romptr3 = Romptr2;
				if (Romptr3!=NULL) Romptr2 = Romptr3->next;
			}
         Romptr2 = Romptr->next; //********Rom
	      Romptr3 = Romptr;		//********Rom
		}
		//**************************************
	}
	else
	{  // white pixel is 0
		__InvertSelf( LinesBuf + ImageInfo.wImageByteWidth, size_read );
		__CopyAND( lpImage, LinesBuf + ImageInfo.wImageByteWidth, size_read );
	  	//*******************Rom***************
		for (int j=0; j<lines_read; j++)
		{
			while (( Romptr2 != NULL )&&(Romptr2->Begin <= CurLine-lines_read+1+j))
			{
				if(Romptr2->Begin <= CurLine-lines_read+1+j)
				{
					if (Romptr2->End < CurLine-lines_read+1+j)
					{
						Romptr3->next = Romptr2->next;
						//delete Romptr2;
						Romptr2 = Romptr3;
					}
					else
					{
//						div_result = div ( Romptr2->Column, 8);
//						tmp_w8 = ~lbit_byte[div_result.rem];
//						lpImage[j*ImageInfo.wImageByteWidth+div_result.quot] &= tmp_w8;
                  int off = j*ImageInfo.wImageByteWidth + (Romptr2->Column >> 3);
                  int pix = Romptr2->Column & 7;
                  lpImage[off] &= ~( 1 << (7-pix) );
                  int off1 = j*ImageInfo.wImageByteWidth + ((Romptr2->Column+1) >> 3);
                  int pix1 = (Romptr2->Column+1) & 7;
                  lpImage[off1] &= ~( 1 << (7-pix1) );
                  int off2 = j*ImageInfo.wImageByteWidth + ((Romptr2->Column-1) >> 3);
                  int pix2 = (Romptr2->Column-1) & 7;
                  lpImage[off2] &= ~( 1 << (7-pix2) );
					}
				}
				Romptr3 = Romptr2;
				if (Romptr3!=NULL) Romptr2 = Romptr3->next;
			}
         Romptr2 = Romptr->next; //********Rom
	      Romptr3 = Romptr;		//********Rom
		}
		//**************************************

	}
	// pop up two last lines in lines buf
/*
	memcpy( LinesBuf, scn-(ImageInfo.wAddX % 8), ImageInfo.wImageByteWidth*2);
	memset( LinesBuf+ImageInfo.wImageByteWidth*2, 0 , size_read + ImageInfo.wImageByteWidth );
*/

	return (Int16)size_read;
};

Bool  Sweeper_ImageClose (void)
{  //...
	if (LinesBuf)
      free(LinesBuf  );
   LinesBuf   = NULL;
	CurLine = 0;
	Ready = FALSE;
	//...
   Bool ret = TRUE;
	if (MustCloseImage)
	{  ret = Tiger_Callback_ImageClose();
		MustCloseImage = FALSE;
	}
	return ret;
};
