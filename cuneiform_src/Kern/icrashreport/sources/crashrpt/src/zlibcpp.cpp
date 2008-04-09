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

///////////////////////////////////////////////////////////////////////////////
//
//  Module: zlibcpp.cpp
//
//    Desc: See zlibcpp.h
//
// Copyright (c) 2003 Michael Carruth
//
// Modified 27.12.2007 by Redart, Cognitive Tech
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "zlibcpp.h"
#include "utility.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------
// CZLib::CZLib
//
// 
//
CZLib::CZLib()
{
   m_zf = 0;
}


//-----------------------------------------------------------------------------
// CZLib::~CZLib
//
// Close open zip file
//
CZLib::~CZLib()
{
   if (m_zf)
      Close();
}


//-----------------------------------------------------------------------------
// CZLib::Open
//
// Create or open zip file
//
BOOL CZLib::Open(CString f_file, int f_nAppend)
{
   m_zf = zipOpen(f_file, f_nAppend);
   return (m_zf != NULL);
}


//-----------------------------------------------------------------------------
// CZLib::Close
//
// Close open zip file
//
void CZLib::Close()
{
   if (m_zf)
      zipClose(m_zf, NULL);

   m_zf = 0;
}


//-----------------------------------------------------------------------------
// CZLib::AddFile
//
// Adds a file to the zip archive
//
BOOL CZLib::AddFile(CString f_file)
{
   BOOL bReturn = FALSE;

   // Open file being added
   HANDLE hFile = NULL;
   hFile = CreateFile(f_file, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   if (hFile)
   {
      // Get file creation date
      FILETIME       ft = CUtility::getLastWriteFileTime(f_file);
      zip_fileinfo   zi = {0};

      FileTimeToDosDateTime(
         &ft,                       // last write FILETIME
         ((LPWORD)&zi.dosDate)+1,   // dos date
         ((LPWORD)&zi.dosDate)+0);  // dos time

      // Trim path off file name
      CString sFileName = f_file.Mid(f_file.ReverseFind(_T('\\')) + 1);

      // Start a new file in Zip
      if (ZIP_OK == zipOpenNewFileInZip(m_zf, 
                                        sFileName, 
                                        &zi, 
                                        NULL, 
                                        0, 
                                        NULL, 
                                        0, 
                                        NULL, 
                                        Z_DEFLATED, 
                                        Z_BEST_COMPRESSION))
      {
         // Write file to Zip in 4 KB chunks 
         const DWORD BUFFSIZE    = 4096;
         TCHAR buffer[BUFFSIZE]  = _T("");
         DWORD dwBytesRead       = 0;

         while (ReadFile(hFile, &buffer, BUFFSIZE, &dwBytesRead, NULL)
                && dwBytesRead)
         {
            if (ZIP_OK == zipWriteInFileInZip(m_zf, buffer, dwBytesRead)
               && dwBytesRead < BUFFSIZE)
            {
               // Success
               bReturn = TRUE;
            }
         }

         bReturn &= (ZIP_OK == zipCloseFileInZip(m_zf));
      }
      
      bReturn &= CloseHandle(hFile);
   }

   return bReturn;
}