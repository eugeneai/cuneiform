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

// �RTurner.h: interface for the CRTurner class.
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#if !defined(CRTURNER_H__)
#define CRTURNER_H__
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
///////////////////////////////////////////////////////////////////////////////////////////////////
//
# if defined (_DEBUG)
# pragma message( __FILE__" : Turner for x90 angles")
# endif // (_DEBUG)
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "globus.h"
#include "ctdib.h"

#define CONTINUEPIXEL(a)         if ( !(a) ) continue;
///////////////////////////////////////////////////////////////////////////////////////////////////
//
class CRTurner
{
public:
	Bool32    TurnDIB(PCTDIB pInDIB, PCTDIB pOutDIB, Word32 wAngle);
	Bool32    FreeDIB(void * pDIB);
	void *    TurnDIB( void * pDIB, Word32 wAngle);
	CRTurner();
	virtual   ~CRTurner();

private:
	Bool32    WriteDIBtoBMP(const char *cName, PCTDIB pDIB);
	Bool32    Turn270GC(PCTDIB pIn, PCTDIB pOut);
	Bool32    Turn180GC(PCTDIB pIn, PCTDIB pOut);
	Bool32    Turn90GC(PCTDIB pIn, PCTDIB pOut);
	Bool32    Turn270LA(PCTDIB pInDIB, PCTDIB pOutDIB);
	Bool32    Turn90LA(PCTDIB pInDIB, PCTDIB pOutDIB);
	Bool32    CheckInAndOut180(PCTDIB pIn, PCTDIB pOut);
	Bool32    CheckInAndOut90(PCTDIB pIn, PCTDIB pOut);
	void      FreeBuffers(void);
	Bool32    Turn270(PCTDIB pInDIB, PCTDIB pOutDIB);
	Bool32    Turn180(PCTDIB pInDIB, PCTDIB pOutDIB);
	Bool32    Turn90(PCTDIB pInDIB, PCTDIB pOutDIB);
	Bool32    Turn180LA(PCTDIB pInDIB, PCTDIB pOutDIB);

protected:
	Word32    wRightShift[8];// { 7, 6, 5, 4, 3, 2, 1, 0};
	Word8     wRightMask[8]; // { 11111110b, 11111100b, 11111000b, 11110000b, 11100000b, 11000000b, 10000000b, 00000000b };
	Word8     wLeftMask[8];  // { 11111110b, 11111100b, 11111000b, 11110000b, 11100000b, 11000000b, 10000000b, 00000000b };
	Word8     wBitMask[8];  //  { 10000000b, 01000000b, 00100000b, 00010000b, 00001000b, 00000100b, 00000010b, 00000001b };
	Handle    hLineBuffer;
	PWord8    LineBuffer;
	Word8     Turn1at180[256];
	Word8     Turn1at90[132][8];
};

typedef  CRTurner   *PCRTurner,  **PPCRTurner;
#endif // !defined(CRTURNER_H__)
