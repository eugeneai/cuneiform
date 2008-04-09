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

#define __RIMAGE__

#include "resource.h"
#include "CRIImage.h"
#include "CRIMemory.h"
#include "CRIDefines.h"

#include "CRIControl.h"

// exteren globals
extern CRIControl * Control;
// extern functions
void SetReturnCode(Word16 rc);
Word16 GetReturnCode();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_SetMargins(PRIMAGEMARGINS pMargins)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->SetMargins( pMargins );

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_SetProgressCB(PRIMAGECBPRogressStart pStart, PRIMAGECBPRogressStep pStep, PRIMAGECBPRogressFinish pFinish)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->SetProgressCallBacks( pStart, pStep, pFinish );

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_Binarise(PWord8 cDIBIn, PWord8 cDIBOut, Word32 wFlag, Word32 UseMargins)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->Binarise( (PChar8)cDIBIn, (PChar8)cDIBOut, wFlag, UseMargins);

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_Rotate(PWord8 cDIBIn, PWord8 cDIBOut, Int32 High, Int32 Low, Word32 UseMargins)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->Rotate( (PChar8)cDIBIn, (PChar8)cDIBOut, High, Low, UseMargins);

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_RotatePoint( PWord8 cDIBIn, Int32 wX, Int32 wY, PInt32 prX, PInt32 prY)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->RotatePoint( (PChar8)cDIBIn, wX, wY, prX, prY );

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_Roll(PWord8 cDIBIn, PWord8 cDIBOut, Int32 High, Int32 Low, Word32 UseMargins)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->Roll( (PChar8)cDIBIn, (PChar8)cDIBOut, High, Low, UseMargins);

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_Turn(PWord8 cDIBIn, PWord8 cDIBOut, Word32 wFlag, Word32 UseMargins)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->Turn( (PChar8)cDIBIn, (PChar8)cDIBOut, wFlag, UseMargins);

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
RIMAGE_FUNC(Bool32) RIMAGE_Inverse(PWord8 cDIBIn, PWord8 cDIBOut, Word32 UseMargins)
{
	SetReturnCode(IDS_RIMAGE_ERR_NO);

	if ( Control )
		return Control->Inverse( (PChar8)cDIBIn, (PChar8)cDIBOut, UseMargins);

	SetReturnCode(IDS_RIMAGE_DLL_NOT_INITIALISING);
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file