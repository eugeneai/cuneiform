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

#ifndef RLING_SECONDARY
  #define __RLING__
#else
  #define __RLINGS__
#endif

#include "resource.h"
#include "rlcontrol.h"
#include "crling.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// exteren globals
extern CRLControl * Control;
// extern functions
void SetReturnCode(Word16 rc);
Word16 GetReturnCode();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Int32) RLING_IsDictonaryAvailable(Word32 wLang, PInt8 pPath)
#else
RLINGS_FUNC(Int32) RLINGS_IsDictonaryAvailable(Word32 wLang, PInt8 pPath)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->IsDictonaryAvailable( wLang, (PChar8) pPath);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_LoadDictonary(Word32 wLang, PInt8 pPath)
#else
RLINGS_FUNC(Bool32) RLINGS_LoadDictonary(Word32 wLang, PInt8 pPath)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->LoadDictonary( wLang, (PChar8) pPath);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_LoadUserDictonary(PInt8 pUserDictList, PInt8 pPath)
#else
RLINGS_FUNC(Bool32) RLINGS_LoadUserDictonary(PInt8 pUserDictList, PInt8 pPath)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->LoadUserDictonary( (PChar8)pUserDictList, (PChar8)pPath);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_LoadSecDictonary(Word32 wLang, PInt8 pPath)
#else
RLINGS_FUNC(Bool32) RLINGS_LoadSecDictonary(Word32 wLang, PInt8 pPath)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->LoadSecDictonary( wLang, (PChar8) pPath);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_LoadSecUserDictonary(PInt8 pUserDictList, PInt8 pPath)
#else
RLINGS_FUNC(Bool32) RLINGS_LoadSecUserDictonary(PInt8 pUserDictList, PInt8 pPath)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->LoadSecUserDictonary( (PChar8)pUserDictList, (PChar8)pPath);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_UnloadDictonary(void)
#else
RLINGS_FUNC(Bool32) RLINGS_UnloadDictonary(void)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->UnLoadDictonary();

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_UnloadUserDictonary(void)
#else
RLINGS_FUNC(Bool32) RLINGS_UnloadUserDictonary(void)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->UnLoadUserDictonary();

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_UnloadSecDictonary(void)
#else
RLINGS_FUNC(Bool32) RLINGS_UnloadSecDictonary(void)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->UnLoadSecDictonary();

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_UnloadSecUserDictonary(void)
#else
RLINGS_FUNC(Bool32) RLINGS_UnloadSecUserDictonary(void)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->UnLoadSecUserDictonary();

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CheckWord(PInt8 pWord, PInt32 pOutCheck)
#else
RLINGS_FUNC(Bool32) RLINGS_CheckWord(PInt8 pWord, PInt32 pOutCheck)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CheckWord( (PChar8)pWord, pOutCheck);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CheckSecWord(PInt8 pWord, PInt32 pOutCheck)
#else
RLINGS_FUNC(Bool32) RLINGS_CheckSecWord(PInt8 pWord, PInt32 pOutCheck)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CheckSecWord( (PChar8)pWord, pOutCheck);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/*
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CheckFile(PInt8 pFile, PInt32 pOutCheck)
#else
RLINGS_FUNC(Bool32) RLINGS_CheckFile(PInt8 pFile, PInt32 pOutCheck)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CheckFile( (PChar8)pFile, pOutCheck);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CheckED(void * pEDPool, void * pEDOutPool, Word32 wEDPoolSize, PWord32 pwEDOutPoolSize, PInt32 pOutCheck)
#else
RLINGS_FUNC(Bool32) RLINGS_CheckED(void * pEDPool, void * pEDOutPool, Word32 wEDPoolSize, PWord32 pwEDOutPoolSize, PInt32 pOutCheck)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CheckED( pEDPool, pEDOutPool, wEDPoolSize, pwEDOutPoolSize, pOutCheck);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CheckSecED(void * pEDPool, void * pEDOutPool, Word32 wEDPoolSize, PWord32 pwEDOutPoolSize, PInt32 pOutCheck)
#else
RLINGS_FUNC(Bool32) RLINGS_CheckSecED(void * pEDPool, void * pEDOutPool, Word32 wEDPoolSize, PWord32 pwEDOutPoolSize, PInt32 pOutCheck)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CheckSecED( pEDPool, pEDOutPool, wEDPoolSize, pwEDOutPoolSize, pOutCheck);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CorrectWord(void * Begin, void * End, PWord32 pLanguage, PInt8 pCorrWord)
#else
RLINGS_FUNC(Bool32) RLINGS_CorrectWord(void * Begin, void * End, PWord32 pLanguage, PInt8 pCorrWord)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CorrectWord( (CSTR_rast)Begin, (CSTR_rast)End, pLanguage, (PChar8)pCorrWord);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CorrectSecWord(void * Begin, void * End, PWord32 pLanguage, PInt8 pCorrWord)
#else
RLINGS_FUNC(Bool32) RLINGS_CorrectSecWord(void * Begin, void * End, PWord32 pLanguage, PInt8 pCorrWord)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CorrectSecWord( (CSTR_rast)Begin, (CSTR_rast)End, pLanguage, (PChar8)pCorrWord);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CorrectHypWord(void * BeginF, void * EndF, PWord32 pLanguageF, void * BeginS, void * EndS, PWord32 pLanguageS, PInt8 pCorrWord)
#else
RLINGS_FUNC(Bool32) RLINGS_CorrectHypWord(void * BeginF, void * EndF, PWord32 pLanguageF, void * BeginS, void * EndS, PWord32 pLanguageS, PInt8 pCorrWord)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CorrectHypWord( (CSTR_rast)BeginF, (CSTR_rast)EndF, pLanguageF, (CSTR_rast)BeginS, (CSTR_rast)EndS, pLanguageS, (PChar8)pCorrWord);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Bool32) RLING_CorrectSecHypWord(void * BeginF, void * EndF, PWord32 pLanguageF, void * BeginS, void * EndS, PWord32 pLanguageS, PInt8 pCorrWord)
#else
RLINGS_FUNC(Bool32) RLINGS_CorrectSecHypWord(void * BeginF, void * EndF, PWord32 pLanguageF, void * BeginS, void * EndS, PWord32 pLanguageS, PInt8 pCorrWord)
#endif
{
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->CorrectSecHypWord( (CSTR_rast)BeginF, (CSTR_rast)EndF, pLanguageF, (CSTR_rast)BeginS, (CSTR_rast)EndS, pLanguageS, (PChar8)pCorrWord);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Rect16) RLING_GetCorrectedRectElement(Word32 i)
#else
RLINGS_FUNC(Rect16) RLINGS_GetCorrectedRectElement(Word32 i)
#endif
{
	Rect16 Empt = {0,0,0,0};
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->GetCorrectedRectElement(i);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return Empt;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(Rect16) RLING_GetSecCorrectedRectElement(Word32 i)
#else
RLINGS_FUNC(Rect16) RLINGS_GetSecCorrectedRectElement(Word32 i)
#endif
{
	Rect16 Empt = {0,0,0,0};
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->GetSecCorrectedRectElement(i);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return Empt;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(RecVersions) RLING_GetCorrectedVersElement(Word32 i, PWord32 pNVers)
#else
RLINGS_FUNC(RecVersions) RLINGS_GetCorrectedVersElement(Word32 i, PWord32 pNVers)
#endif
{
	RecVersions Empt = {0,0,0};
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->GetCorrectedVersElemet(i, pNVers);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return Empt;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#if defined( __RLING__ )
RLING_FUNC(RecVersions) RLING_GetSecCorrectedVersElement(Word32 i, PWord32 pNVers)
#else
RLINGS_FUNC(RecVersions) RLINGS_GetSecCorrectedVersElement(Word32 i, PWord32 pNVers)
#endif
{
	RecVersions Empt = {0,0,0};
	SetReturnCode(IDS_RLING_ERR_NO);

	if ( Control )
		return Control->GetSecCorrectedVersElement(i, pNVers);

	SetReturnCode(IDS_RLING_DLL_NOT_INITIALISING);
	return Empt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
