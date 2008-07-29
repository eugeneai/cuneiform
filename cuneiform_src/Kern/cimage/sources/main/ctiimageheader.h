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

# ifndef __CTI_HEADER_H_
# define __CTI_HEADER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

# if defined (_DEBUG)
# pragma message( __FILE__" : Image header")
# endif // (_DEBUG)

#include "resource.h"
#include "ctidefines.h"
#include "ctiimage.h"
#include "ctimemory.h"
#include "ctimask.h"

class CTIImageHeader
{
private:
	CTIImageHeader *          pNext;
	Int8                      ImageName[CIMAGE_MAX_IMAGE_NAME];
	PCIMAGEBITMAPINFOHEADER   ImageInfo;
	void *                    Image;
	PCTIMask                  WriteMask;
	PCTIMask                  ReadMask;
	Bool32                    ImageExternal;
	Bool32                    mbEnableReadMask;
	Bool32                    mbEnableWriteMask;
	Handle                    hImage;

public:
	CTIImageHeader();
	CTIImageHeader(PChar8  lpName, Handle hImagehandle, Word32 Flag);
	CTIImageHeader(PChar8  lpName, PCIMAGEBITMAPINFOHEADER lpInfo, void * lpImage, Word32 wFlag);
	~CTIImageHeader();

private:

public:
	Bool32                    IsMaskEnabled(PChar8 MaskType);
	Bool32                    EnableMask(PChar8 cMaskType, Bool32 mEnabled);
	Bool32                    CheckName(PChar8  Name);
	CTIImageHeader *          GetNext(void) { return pNext; };
	CTIImageHeader *          SetNext(CTIImageHeader * pSet ) { return (pNext = pSet); };
	void *                    GetImage(void) { return Image; };
	PCIMAGEBITMAPINFOHEADER   GetImageInfo(void) { return ImageInfo; };
	Bool32                    IsExtImage(void) { return !IsIntImage(); };
	Bool32                    IsIntImage(void) { return (ImageExternal == 0); };
	Handle                    GetImageHandle(void) { return hImage; };
	Handle                    SetImageHandle(Handle NewHandle) { return (hImage = NewHandle); };
	Bool32                    SetWriteMask(PCTIMask WMask){return ((WriteMask = WMask) != NULL); };
	PCTIMask                  GetWriteMask(void){return WriteMask; };
	Bool32                    SetReadMask(PCTIMask RMask) {return ((ReadMask = RMask) != NULL); };
	PCTIMask                  GetReadMask(void) {return ReadMask; };
};
# endif    //__CTI_HEADER_H_
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
