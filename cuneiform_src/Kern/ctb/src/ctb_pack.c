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

//************************************************************************//
//* CTB_pack : PCX pack-unpack functions *********************************//
//************************************************************************//
#include "ctb.h"
Int16 encput( Word8 byt, Word8 cnt,Word8 *save)
{
if( cnt )
	{
	if( cnt==1 && (0xC0!=(0xC0&byt)) )
		{
		*save++ = byt;
		return(1);
		}
	else
		{
		*save++ = (0xC0|cnt);
		*save++ = byt;
		return(2);
		}
	}

return(0);
}


// PACKING //
Int16 encLine(Word8 *inBuff, Int16 inLen,Word8 *buf, Int16 outLen)
{
Word8 curr,last;
Word16 scrIndex;
Word16 total;
Word8 runCount;

total    = 0;
runCount = 1;
last     = *inBuff;

for( scrIndex=1;scrIndex<inLen&&total<outLen;scrIndex++)
	{
	curr = *(++inBuff);
	if( curr==last )	// There is a "run" in the data, encode it //
		{
		runCount++;
		if( runCount==63 )
			{
			total += encput(last,runCount,&buf[total]);
			runCount = 0;
			}
		}
	else			// No "run" - curr!=last	//
		{
		if( runCount )
			total += encput(last,runCount,&buf[total]);
		last = curr;
		runCount = 1;
		}
	}	// endloop 	//

if( runCount )	// finish up 	//
	return total+encput(last,runCount,&buf[total]) ;

return total;
}

#ifndef ASM_USED
// UNPACKING //
// exist analog asm_delLine in assembler LINE.ASM //

Int16 decLine(Word8 *inBuffer, Int16 inLen, Word8 *outBuffer)
{
Word8 cnt, *inB, *inE;

for( inB=inBuffer, inE=inBuffer+inLen ; inB<inE ; inB++)
	{	// increment by cnt bellow	//

	if( *inB>=0xC0 )
		{
		cnt = 0x3F & *inB++;
		memset(outBuffer,*inB,cnt);
		outBuffer += cnt;
		}
	else
      *outBuffer++ = *inB;
  } // end loop //

return (0);
}
#endif

