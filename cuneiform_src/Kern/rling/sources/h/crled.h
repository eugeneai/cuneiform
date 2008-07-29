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

// CRLEd.h: interface for the CRLEd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRLED_H__994890B3_651D_11D3_A5C0_00C0F6A06129__INCLUDED_)
#define AFX_CRLED_H__994890B3_651D_11D3_A5C0_00C0F6A06129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "globus.h"
#include "cstr.h"
#include "recdefs.h"
////////////////////////////////////////////////////////////

#pragma pack( push, 1 )

//////////////////////////////////////////////////////////////
// ���������� ����� ���� �� ������ rpstr ���� cor_spel.h 7.09.99
// � ���� ������������� �� ������ ������ ������� ������, ����� ������
// ����������� �������� � �������� ������ ���
// ���� ����� �� ����� ������������ �� �����, �������� � ������ ������
//#include "cor_spell.h"

struct VersRef
{
    Word8   code;
    Word8   prob;
};

struct BitMapRef
{
    Word8 code;
    Word8 pos;
    Word16 row;
    Word16 col;
    Word16 width;
    Word16 height;
};

struct SheetDiskDescr
{
    Word8 code;
    Int8 quant_fragm;
    Word16 sheet_numb;
    Word16 descr_lth;
    Word8 byte_flag;
    Word16 resolution;
    Word16  incline;
    Int8 tabl[13];
};

struct FragmDisk
{
    Word8 code;
    Word8 fragm_numb;
    Word16 depth;
};

struct FragmDiskDescr
{
    Word8 code;
    Word16 row;
    Word16 col;
    Word16 height;
    Word16 w_width;
    Int8   type;
    Word8  kegl;
    Word8  font;
    Word8  language;
    Word8  type_underl;
};

#pragma pack ( pop )

///////////////////////////////////////////////////////////////////
#define CRL_ED_BUFFER_SIZE                     32000
#define CRL_ED_RECT_ARRAY_SIZE                 100
#define CRL_ED_VERS_ARRAY_SIZE                 100

class CRLEd
{


public:
	RecVersions GetVersElement(Word32 i, PWord32 pNVers);
	Rect16 GetRectElement(Word32 i);
	void * GetEdPool(void) { return (void *) mpEdBuffer; };
	void * GetEdOutPool(void) { return (void *) mpEdOutBuffer; };
	Word32 GetEdPoolSize(void) { return mpEdFileEnd - mpEdBuffer; };
	Bool32 ExcludeToVers(Int32 size, PChar8 pStr);
	Bool32 AddWord(CSTR_rast b, CSTR_rast e, PWord8 pLanguage);
	Bool32 MakeWord(CSTR_rast b, CSTR_rast e,PWord8 Language);
	void   Init();
	CRLEd();
	virtual ~CRLEd();

protected:
	Bool32 mbReadyToAdd;
	Rect16 mEdRect[CRL_ED_RECT_ARRAY_SIZE];
	RecVersions mEdVers[CRL_ED_VERS_ARRAY_SIZE];
	Int32 miEdNVers;
	Handle mhEdOutBuffer;
	Handle mhEdBuffer;
	PWord8 mpEdFileBound;
	PWord8 mpEdFileEnd;
	PWord8 mpEdOutBuffer;
	PWord8 mpEdBuffer;
	Word8  mHalfSpaces[3];
	struct SheetDiskDescr    mSdd;
	struct FragmDiskDescr    mFdd;
	struct FragmDisk         mFd;
	struct VersRef           mVr;
	struct BitMapRef         mBmr;
	//struct sheet_disk_descr    mSdd;
	//struct fragm_disk_descr    mFdd;
	//struct fragm_disk          mFd;
	//struct vers_ref            mVr;
	//struct bit_map_ref         mBmr;

private:
	void   Write(PWord8 pP, Word16 wSize);

};


#endif // !defined(AFX_CRLED_H__994890B3_651D_11D3_A5C0_00C0F6A06129__INCLUDED_)
