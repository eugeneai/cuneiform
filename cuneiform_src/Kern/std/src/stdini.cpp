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

#include "internal.h"
#pragma hdrstop
#include "std.h"
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////  ������� ������ � INI-�������

#ifdef WIN32
   #include "win_mini.h"
#endif

#include "XPath.h"

static Bool32 IsFullName(const char* szFileName)
{
    int len=strlen(szFileName);
    if(len<2)
        return FALSE;
    if(szFileName[1]==':')
        return TRUE;
    if(!strncmp(szFileName,"\\\\",2))
        return TRUE;
    return FALSE;
}

static void SetFullName(char* szFullFileName,const char* szIniFileName,Int32 nFlags)
{
    strcpy(szFullFileName,szIniFileName);
    if(!IsFullName(szIniFileName) && !(nFlags & STD_SETPROF_DIR_WINDOWS))
    {
       sprintf(szFullFileName,"%s\\%s",stdGetHomeDirectory(),szIniFileName);
       XPath xpini = szFullFileName; XPath xpfl = szFullFileName;
	   xpini.CutPath().CheckSlash(); 
	   if(!(nFlags & STD_SETPROF_DIR_VERSION))
		   xpini +="..\\CONFIG\\";
       xpini += xpfl.CutNameEx();
       strcpy(szFullFileName,(const char*)xpini);
    }
}


STD_FUNC( Bool32 ) stdGetProfileString(char* szString,Int32* nStrLen,const char* szIniFileName,const char* szSection,const char* szKey,Int32 nFlags, const char* pszStrDefault)
{
    char szFullFileName[_MAX_PATH]={0};
	SetFullName(szFullFileName,szIniFileName,nFlags);
    if(GetPrivateProfileString(szSection,szKey,pszStrDefault,szString,*nStrLen,szFullFileName)==(Word32)(*nStrLen-1))
       return FALSE;
    return TRUE;
}

STD_FUNC( Int32 ) stdGetProfileInt(const char* szIniFileName,const char* szSection,const char* szKey,Int32 nFlags,Int32 nValDefault)
{
    char szFullFileName[_MAX_PATH]={0};
	SetFullName(szFullFileName,szIniFileName,nFlags);
    return GetPrivateProfileInt(szSection,szKey,nValDefault,szFullFileName);
}

STD_FUNC( Bool32 ) stdSetProfileString(const char* szString,const char* szIniFileName,const char* szSection,const char* szKey,Int32 nFlags)
{
    char szFullFileName[_MAX_PATH]={0};
	SetFullName(szFullFileName,szIniFileName,nFlags);
    if(!WritePrivateProfileString(szSection,szKey,szString,szFullFileName))
        return FALSE;
    return TRUE;
}

STD_FUNC( Bool32 ) stdSetProfileInt(Int32 nValue,const char* szIniFileName,const char* szSection,const char* szKey,Int32 nFlags)
{
    char szStrNumber[256]={0};
    itoa(nValue,szStrNumber,10);
    char szFullFileName[_MAX_PATH]={0};
	SetFullName(szFullFileName,szIniFileName,nFlags);
    if(!WritePrivateProfileString(szSection,szKey,szStrNumber,szFullFileName))
        return FALSE;
    return TRUE;
}
