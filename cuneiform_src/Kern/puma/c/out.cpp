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

#include "mpuma.h"
#include <string.h>


Bool32 ConverROUT(char * lpOutFileName, Int32 lnFormat, Int32 lnCode,Bool32 bAppend)
{
	char szName[260];
	strcpy(szName,lpOutFileName);
	char * str = strrchr(szName,'.');
	if(str)
		*(str)='\0';

	if (/*
		!ROUT_SetImportData(ROUT_PCHAR_TableTextSeparators,
						TableTextSeparators) ||
		!ROUT_SetImportData(ROUT_ULONG_TableTextIntervalBetweenCellsYY,
						(void*)TableTextIntervalBetweenCellsYY)||
		!ROUT_SetImportData(ROUT_ULONG_TableTextIntervalBetweenCellsXX,
						(void*)TableTextIntervalBetweenCellsXX)||
		!ROUT_SetImportData(ROUT_ULONG_TableTextLeftIndent,
						(void*)TableTextLeftIndent)||
		!ROUT_SetImportData(ROUT_LONG_TableTextOptions,
						(void*)TableTextOptions)*/
		!ROUT_SetImportData(ROUT_BOOL_PreserveLineBreaks,
					  (void*)gnPreserveLineBreaks)||
		!ROUT_SetImportData(ROUT_PCHAR_PageName,szName) ||
		!ROUT_SetImportData(ROUT_HANDLE_PageHandle,ghEdPage)||
		!ROUT_SetImportData(ROUT_LONG_Format,(void*)lnFormat)||
		!ROUT_SetImportData(ROUT_LONG_Code,(void*)lnCode)||
		!ROUT_SetImportData(ROUT_PCHAR_BAD_CHAR,&gnUnrecogChar))
	{
		SetReturnCode_puma(ROUT_GetReturnCode());
		return FALSE;
	}

	/*
	if (!LoadAlphabet(Rec6DatFilename))
		{
		SetReturnCode_puma(ROUT_GetReturnCode());
		return FALSE;
		}

	if (!ROUT_SetAlphabet(sizeAlphabet,upper,lower,vowels))
		{
		SetReturnCode_puma(ROUT_GetReturnCode());
		return FALSE;
		}
	*/
		// ���������� ��������
		long countObjects = ROUT_CountObjects();
		if ( countObjects == -1 )
			{
				SetReturnCode_puma(ROUT_GetReturnCode());
				return FALSE;
			}

		for (long objIndex = 1;
			objIndex <= countObjects;
			objIndex++)
			{
			char path[260] = "";

			char *p = lpOutFileName;
			if ( countObjects!=1)
			{
                p = (char*)ROUT_GetDefaultObjectName(objIndex);
                if(!p)
                {
				    SetReturnCode_puma(ROUT_GetReturnCode());
				    return FALSE;
                }
			}

			strcpy(path,p);

			if (!ROUT_SaveObject(objIndex,path,bAppend))
				{
					SetReturnCode_puma(ROUT_GetReturnCode());
					return FALSE;
				}
			} // ���� �� �������� �� ��������

	return TRUE;
}

Word32 ConverROUTtoMemory(Handle hEd, Int32 lnFormat, Int32 lnCode, Byte * lpMem, Word32 size)
{
Word32 rc = 0;
	if (
		!ROUT_SetImportData(ROUT_BOOL_PreserveLineBreaks,
					  (void*)gnPreserveLineBreaks)||
		!ROUT_SetImportData(ROUT_HANDLE_PageHandle,hEd)||
		!ROUT_SetImportData(ROUT_LONG_Format,(void*)lnFormat)||
		!ROUT_SetImportData(ROUT_LONG_Code,(void*)lnCode)||
		!ROUT_SetImportData(ROUT_PCHAR_BAD_CHAR,&gnUnrecogChar))
	{
		SetReturnCode_puma(ROUT_GetReturnCode());
		return rc;
	}

		// ���������� ��������
		long countObjects = ROUT_CountObjects();
		if ( countObjects == -1 )
			{
				SetReturnCode_puma(ROUT_GetReturnCode());
				return rc;
			}
// ���������� ������ ������
		long nSize = 0;
		for (long objIndex = 1;
			objIndex <= countObjects;
			objIndex++)
			{
				long nCurSize = ROUT_GetObjectSize(objIndex);
				nSize += nCurSize;
				if(nSize <= (long)size)
				{
					if (!ROUT_GetObject(objIndex,lpMem + (nSize - nCurSize),&nCurSize))
						{
							SetReturnCode_puma(ROUT_GetReturnCode());
							return rc;
						}
				}
			} // ���� �� �������� �� ��������
	rc = nSize;
	return rc;
}
