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


// Rout.cpp

//********************************************************************
//
// Rout.cpp - �������������� ������� ������ ROUT
//
// This file creation date: 20.05.99
// By Eugene Pliskin pliskin@cs.isa.ac.ru
//********************************************************************

#include <fcntl.h>
#include <string.h>
#include "stdafx.h"
#include "rout_own.h"

static BOOL Static_GetTargetObject(Handle hObject, long reason);
static BOOL Static_GetFirstTable(Handle hObject,long reason);
static BOOL GetWorkMem();
static BOOL FreeWorkMem();
static BOOL LoadAlphabet(long language,char *rec6xxxFilename);
static BOOL UpdateActiveAlphabet();
static BOOL HaveTablesOnPage();

//********************************************************************
Bool32 ROUT_LoadEd
		(
		char *lpEdFile,		// ��� ����� ��� ����� � ������
		Bool32 readFromFile,	// TRUE, ���� ������ ��� �����
		Word32 bufLen		// ����� (������ ��� readFromFile=FALSE)
		)
{
// �������� ED-�����.
// ��������� ��� � CED_ReadFormattedEd.
	//DEBUG_PRINT("ROUT_LoadEd");
	ClearError();

	gPageHandle = CED_ReadFormattedEd(
						lpEdFile,
						readFromFile,
						bufLen);

	if ( !gPageHandle ||
		!CED_GetCountSection(gPageHandle)
		)
		{
		PAGE_NOT_LOADED;
		return FALSE;
		}

	// �������� ���� ��������� ����
	gPageLoadedByMe = TRUE;

	// ���������� ��� �������� ��� ����������
	if(readFromFile)
		{
		char drive[_MAX_DRIVE],dir[_MAX_PATH],
			 name[_MAX_PATH],ext[_MAX_EXT];
		_splitpath(lpEdFile,drive,dir,name,ext);

		strcpy(gPageName,drive);
		strcat(gPageName,dir);
		strcat(gPageName,name);
		}

	//DEBUG_PRINT("ROUT_LoadEd successful");
	return TRUE;
}
//********************************************************************
Bool32 ROUT_UnloadEd(void)
{
// �������� ED-�����
//	DEBUG_PRINT("ROUT_UnloadEd");
	ClearError();

	// �������� ���� ��������� ����?
	if(gPageLoadedByMe)
		{
		CED_DeletePage(gPageHandle);
		}

	gPageHandle = NULL;
	gPageLoadedByMe = FALSE;

	return TRUE;
}
//********************************************************************
// ��������������� � ���� ������ � ������ � ����
Bool32 ROUT_SaveObject(
		ULONG objIndex,	// ������ ������� ������� �� 1
		char *path,		// ���� �� ��������� �����
		Bool32 append		// ���������� � ����� �����
		)
{
// ��������������� � ���� ������ � ������ � ����
//	DEBUG_PRINT("ROUT_OneFile");
	ClearError();

	// ��������� �� ��������
	if ( !gPageHandle )
		{
		PAGE_NOT_LOADED;
		return FALSE;
		}

	// ����� �����
	gTargetObjectIndex = objIndex;
	gTargetObjectHandle = NULL;
	BrowsePage(Static_GetTargetObject,
				TRUE,	// wantSkipTableCells
				TRUE	// wantSkipParagraphs
				);

	if ( !gTargetObjectHandle )
		{
		OBJECT_NOT_FOUND;
		return FALSE;
		}

	// ��������� ������ ��� ������
	if ( !GetWorkMem() )
		return FALSE;

	// ��������� ��������������� �� ������
	long sizeMem = 0;
	if ( !ROUT_GetObject(
			objIndex,
			0,	// lpMem
			&sizeMem)	// sizeMem
		)
		{
		FreeWorkMem();
		return FALSE;
		}

	// ������� ����
	Handle f = NULL;
	ULONG pos = 0;

	f = MyOpen(path,OSF_CREATE | OSF_OPEN |
				     OSF_WRITE | OSF_BINARY );
	if (!f)
		{
		ERR_OPEN_FILE;
		FreeWorkMem();
		return FALSE;
		}

	// ���������� � ����� �����
	if (append && (gFormat == ROUT_FMT_Text ||
				   gFormat == ROUT_FMT_SmartText ||
				   gFormat == ROUT_FMT_TableText ||
				   0))
		{
		pos = MySeek(f,0,FS_END);
		if ( pos > 0 )
			{
			// �������� ������ ������
			if (MyWrite(f,gEOL,strlen(gEOL)) != strlen(gEOL))
				{
				MyClose(f,0);
				FreeWorkMem();
				return FALSE;
				}
			}
		}
	else
		pos = MySeek(f,0,FS_BEGIN);

	if ( pos == -1 )
		{
		MyClose(f,0);
		FreeWorkMem();
		return FALSE;
		}

	// �������� ������ �� ������
	ULONG lth = gMemCur - gMemStart;
	if (MyWrite(f, (char*)gMemStart, lth) != lth)
		{
		MyClose(f,0);
		FreeWorkMem();
		return FALSE;
		}

	// ������� ����
	if ( !MyClose(f,CSF_SAVEDISK))
		{
		ERR_CLOSE_FILE;
		FreeWorkMem();
		return FALSE;
		}

	FreeWorkMem();
	return TRUE;
}
//********************************************************************
// ��������������� � ���� ������ �� �������� ������
Bool32 ROUT_GetObject
		(
		ULONG objIndex,	// ������ ������� ������� �� 1
		Byte *lpMem,	// ����� ����� ������ ( 0 - ������ ������)
		long *sizeMem	// �� �����: ����� ����� ������
						// �� ������: ����� �������������� ������
		)
{
//	DEBUG_PRINT("ROUT_OneFormat");
	ClearError();

	// ��������� �� ��������
	if ( !gPageHandle )
		{
		PAGE_NOT_LOADED;
		return FALSE;
		}

	// ���������� ������� ������
	INIT_MEMORY(lpMem,*sizeMem);

	switch(gFormat)
		{
		case ROUT_FMT_Text:
		case ROUT_FMT_SmartText:
			MakeText();
			break;

		case ROUT_FMT_HTML:
			MakeHTML();
			break;

		case ROUT_FMT_TableText:
			MakeTableText();
			break;

		case ROUT_FMT_DBF:
			MakeTableDBF();
			break;

		case ROUT_FMT_CSV:
		case ROUT_FMT_WKS:

		default:
			NOT_IMPLEMENTED; break;
		}

	// ������� ������������ ������
	*sizeMem = gMemCur - gMemStart;

	return (gwLowRC_rout?FALSE:TRUE);
}
//********************************************************************
BOOL SetLanguage(long language)
{
// ��������� �� ���� �������������.

	// ����� �� ����
	if ( language < 0 || language >= LANG_TOTAL )
		{

		// ���� 255 ��������, ��� ���� �� �����,
		// ��� ������������, � ���������, ��� ��������
		if (language == 255)
			{
			return TRUE;
			}
		else
			{
			DEBUG_PRINT ("������������ ���� �������������: %d",language);
			return FALSE;
			}
		}

	ASSERT(LANG_UZBEK==16);

	gLanguage = language;

	langUzbek = ( gLanguage == LANG_UZBEK );
	langKaz = ( gLanguage == LANG_KAZ ||
				gLanguage == LANG_KAZ_ENG
			  );

	if ( !UpdateActiveAlphabet() )
		return FALSE;

	if ( !UpdateActiveCodeTable() )
		return FALSE;

	return TRUE;
}
//********************************************************************
BOOL SetFormat(long format)
{
// ��������� �� ������

	if ( format == ROUT_FMT_Text ||
		 format == ROUT_FMT_SmartText ||
		 format == ROUT_FMT_TableText ||
		 format == ROUT_FMT_CSV ||
		 format == ROUT_FMT_DBF ||
		 format == ROUT_FMT_WKS ||
		 format == ROUT_FMT_HTML ||
		 0)
		{
		gFormat = format;
		return TRUE;
		}

	WRONG_ARGUMENT;
	return FALSE;
}
//********************************************************************
BOOL SetActiveCode(long code)
{
// ��������� �� �������� ���������

	if ( code < 1 || code > ROUT_CODE_MAX )
		{
		WRONG_ARGUMENT;
		return FALSE;
		}

	gActiveCode = code;

	UpdateActiveCodeTable();
	return TRUE;
}
//********************************************************************
long ROUT_ListFormats(PWord8 buf, ULONG sizeBuf)
{
// ��������� ������ �������������� ��������
// ���������� ���������� �������� ��� -1 ��� ������
	long count = 0;
	ROUT_ITEM *p = (ROUT_ITEM*)buf;

	ClearError();

	memset(buf, 0, sizeBuf);
	if (sizeBuf < ROUT_FMT_COUNT * sizeof(ROUT_ITEM))
		{
		NO_MEMORY;
		return -1;
		}

#define ITEM(a) {\
	p->code = ROUT_FMT_##a;\
	LoadString((HINSTANCE)ghInst_rout, IDS_FMT_##a,\
		p->name,sizeof(p->name));\
	p++; count++;\
		}

	ITEM (Text);
	//ITEM (SmartText);
	ITEM (TableText);
	//ITEM (CSV);
	ITEM (DBF);
	//ITEM (WKS);
	ITEM (HTML);

#undef ITEM

	return count;
}
//********************************************************************
long ROUT_ListCodes(PWord8 buf, ULONG sizeBuf)
{
// ��������� ������ ��������� ��� ������� �������
// ���������� ���������� ��������� ��� -1 ��� ������
	long count = 0;
	ROUT_ITEM *p = (ROUT_ITEM*)buf;

	ClearError();

	memset(buf, 0, sizeBuf);
	if (sizeBuf < ROUT_CODE_COUNT * sizeof(ROUT_ITEM))
		{
		NO_MEMORY;
		return -1;
		}

#define ITEM(a) {\
	p->code = ROUT_CODE_##a;\
	LoadString((HINSTANCE)ghInst_rout, IDS_CODE_##a,\
		p->name,sizeof(p->name));\
	p++; count++;\
		}

	switch(gFormat)
		{
		case ROUT_FMT_Text:
		case ROUT_FMT_SmartText:
		case ROUT_FMT_TableText:
			ITEM(ASCII);
			ITEM(ANSI);
			ITEM(KOI8R);
			ITEM(ISO);
			break;

		case ROUT_FMT_CSV:
		case ROUT_FMT_WKS:
			ITEM(ANSI);
			break;

		case ROUT_FMT_DBF:
			ITEM(ASCII);
			ITEM(ANSI);
			break;

		case ROUT_FMT_HTML:
			ITEM(ANSI);
			ITEM(KOI8R);
			ITEM(ISO);
			break;

		default:
			return -1;
		}

#undef ITEM

	return count;
}
//********************************************************************
Byte ROUT_Byte(Byte c)
{
// �������������� ���� ���� �� ������� �������
	ClearError();

	if (!gActiveCodeTable)
		{
		NOT_IMPLEMENTED;
		return c;
		}

	return gActiveCodeTable[c];
}
//********************************************************************
Bool32 ROUT_Block(
		Byte *lpMem,	// ����� ����� ������
		long sizeMem	// ����� ����� ������
		)
{
// �������������� ���� ������ �� ������� �������
	ClearError();

	if (!gActiveCodeTable)
		{
		NOT_IMPLEMENTED;
		return FALSE;
		}

	while ( sizeMem-- > 0 )
		{
		*lpMem = gActiveCodeTable[*lpMem];
		lpMem++;
		}

	return TRUE;
}
//********************************************************************
long ROUT_CountObjects()
{
// ��������� ���������� �������� �� ��������.
// �������������� ������������� ��������� �������� (ROUT_LoadEd)
// � ���������� ������ ������ (ROUT_LONG_Format).
//
// ��� ��������� �������� ������ ���������� ������ �� ��������,
// � ��� ��������� �������� ������ ������ 1.
//
	long count = 0;
	ClearError();

	switch ( gFormat )
		{
		case ROUT_FMT_Text:
		case ROUT_FMT_SmartText:
		case ROUT_FMT_HTML:
			return 1;
			break;

		case ROUT_FMT_TableText:
		case ROUT_FMT_CSV:
		case ROUT_FMT_WKS:
		case ROUT_FMT_DBF:
			// ����������� �������� � �������
			// ���������� ������
			gTargetObjectIndex = LONG_MAX;
			gTargetObjectHandle = NULL;
			BrowsePage(NULL,
					TRUE,	// wantSkipTableCells
					TRUE	// wantSkipParagraphs
					);

			return gHitTables;

		default:
			{
			DEBUG_PRINT("Wrong gFormat");
			}
		}

	return 0;
}
//********************************************************************
BOOL Static_GetTargetObject(
			Handle hObject,
			long reason	// ��. enum BROWSE_REASON
			)
{
// ����� ������� �� ��������.
// gTargetObjectIndex - ������� ����� �������
// ���������� FALSE ��� ���� ����� ���������� �����.

	static long countObjectsFound; // Static �� �������...

	if(reason == BROWSE_PAGE_START)
		countObjectsFound = 0;

	switch ( gFormat )
		{
		case ROUT_FMT_Text:
		case ROUT_FMT_SmartText:
		case ROUT_FMT_HTML:
			gTargetObjectHandle = gPageHandle;
			return FALSE;	// ��������� �����
			break;

		case ROUT_FMT_TableText:
		case ROUT_FMT_CSV:
		case ROUT_FMT_WKS:
		case ROUT_FMT_DBF:
			if (reason == BROWSE_TABLE_START)
				{
				gTargetObjectHandle = hObject;

				// ��������� ��������� ������
				countObjectsFound++;
				if ( countObjectsFound >= gTargetObjectIndex )
					return FALSE;	// ��������� �����
				}
			break;

		default:
			{
			DEBUG_PRINT("Wrong gFormat");
			}
		}

	return TRUE;	// ���������� �����
}
//********************************************************************
Bool32 ROUT_SetAlphabet(
		Word32 sizeAlphabet,// ���������� ����
		char *upper,		// ��������� �����
		char *lower,		// �������� �����
		char *vowels		// ������� ����
		)
{
// ������ ��������, ������������ �� REC6.DAT � SPELABC.C.
	ClearError();

	gSizeAlphabet = 0;
	memset( &gUpper[0], 0, sizeof(gUpper));
	memset( &gLower[0], 0, sizeof(gLower));
	memset( &gVowels[0], 0, sizeof(gVowels));
	memset( &gAlphabetTable[0], 0, sizeof(gAlphabetTable));

	if (strlen(upper) != sizeAlphabet ||
		strlen(lower) != sizeAlphabet ||
		strlen(vowels) > sizeAlphabet ||
		sizeAlphabet > sizeof(gUpper) - 1
		)
		{
		WRONG_ARGUMENT;
		return FALSE;
		}

	gSizeAlphabet = sizeAlphabet;
	memcpy( &gUpper[0], upper, sizeAlphabet );
	memcpy( &gLower[0], lower, sizeAlphabet );
	memcpy( &gVowels[0], vowels, sizeAlphabet );

	// �������� ���������� � ������,
	// �� ���������� ���� �� ������
	ASSERT(sizeAlphabet + 26 < 256);
	strcat((char*)gUpper, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	strcat((char*)gLower, "abcdefghijklmnopqrstuvwxyz");
	strcat((char*)gVowels,"^bcd^fgh^^klmn^pqrst^v^x^z");

	// ��������� ����������� �������
	Byte *p = NULL;

	for ( p = gUpper; * p; p++)
		gAlphabetTable[*p] |= CASE_UPPER;

	for ( p = gLower; * p; p++)
		gAlphabetTable[*p] |= CASE_LOWER;

	for ( p = gVowels; * p; p++)
		gAlphabetTable[*p] |= CASE_VOWEL;

	for ( p = (Byte*)"0123456789"; * p; p++)
		gAlphabetTable[*p] |= CASE_DIGIT;

	return TRUE;
}
//********************************************************************
char *ROUT_GetDefaultObjectName(
		ULONG objIndex	// ������ ������� ������� �� 1
		)
{
/*
	������������ ��� ��������� ����� �� ����� ��������
	��� ������� ���������� ������-��������� � ���
	��������� ������� �������.
*/
	char suffix[40] = "", ext[5] = "";
	static char name[_MAX_PATH] = "";

	switch(gFormat)
		{
		case ROUT_FMT_Text:
			//strcpy(suffix,"");
			strcpy(ext,".txt");
			break;

		case ROUT_FMT_SmartText:
			strcpy(suffix,"_s");
			strcpy(ext,".txt");
			break;

		case ROUT_FMT_TableText:
			strcpy(suffix,"_b");
			strcpy(ext,".txt");
			break;

		case ROUT_FMT_CSV:
			//strcpy(suffix,"");
			strcpy(ext,".csv");
			break;

		case ROUT_FMT_DBF:
			//strcpy(suffix,"");
			strcpy(ext,".dbf");
			break;

		case ROUT_FMT_WKS:
			//strcpy(suffix,"");
			strcpy(ext,".wks");
			break;

		case ROUT_FMT_HTML:
			//strcpy(suffix,"");
			strcpy(ext,".htm");
			break;

		default:
			{
			NOT_IMPLEMENTED;
			return NULL;
			}
		}

	switch(gActiveCode)
		{
		case ROUT_CODE_ASCII:
			if ( gFormat != ROUT_FMT_Text &&
				 gFormat != ROUT_FMT_SmartText &&
				 gFormat != ROUT_FMT_TableText &&
				 gFormat != ROUT_FMT_DBF
				)
				{
				NOT_IMPLEMENTED;
				return NULL;
				}

			strcat(suffix,"_a");
			break;

		case ROUT_CODE_ANSI:
			strcat(suffix,"_w");	// All formats
			break;

		case ROUT_CODE_KOI8R:
			if ( gFormat != ROUT_FMT_Text &&
				 gFormat != ROUT_FMT_SmartText &&
				 gFormat != ROUT_FMT_TableText &&
				 gFormat != ROUT_FMT_DBF &&
				 gFormat != ROUT_FMT_HTML
				)
				{
				NOT_IMPLEMENTED;
				return NULL;
				}

			strcat(suffix,"_k");
			break;

		case ROUT_CODE_ISO:
			if ( gFormat != ROUT_FMT_Text &&
				 gFormat != ROUT_FMT_SmartText &&
				 gFormat != ROUT_FMT_TableText &&
				 gFormat != ROUT_FMT_DBF &&
				 gFormat != ROUT_FMT_HTML
				)
				{
				NOT_IMPLEMENTED;
				return NULL;
				}

			strcat(suffix,"_i");
			break;

		default:
			{
			NOT_IMPLEMENTED;
			return NULL;
			}
		}

	strcpy(name,gPageName);	// ��� �������� ��� ����������
	strcat(name,suffix);

	// �������� ������ ������� ������� �� 2
	if (objIndex > 1 )
		sprintf(name+strlen(name),"%d",objIndex);

	strcat(name,ext);

	return name;
}
//*****************************************************************
static BOOL GetWorkMem()
{
// ��������� ��������� ���� ����� ������
// � ���� �� �����, �� ������������
// ���� ����� ������, ����������
// �� ROUT_Init()
//
	Byte *p = NULL;
	long lth = 1024<<10;	// 1M

	p = (Byte*)MyAlloc(lth, 0);
	if (!p )
		{
		// ������������ ����������� ����� ������
		p = (Byte*)gOwnMemory;
		lth = gOwnMemorySize;

		DEBUG_PRINT("ROUT.CPP MyGetFreeMem: MyAlloc failed, using own memory");
		}

	// ���������� ������� ������
	INIT_MEMORY(p,lth);

	return TRUE;

}
//********************************************************************
static BOOL FreeWorkMem()
{
// ���������� ������� ������
	BOOL good = TRUE;

	// ����������� ������ �� �������
	if (gMemStart &&
		gMemStart != gOwnMemory
		)
		good =  MyFree(gMemStart);

	// ������ ����� ������
	gMemStart = NULL;
	gMemEnd = NULL;
	gMemCur = NULL;

	return good;

}
//********************************************************************
ULONG ROUT_GetObjectSize(
		ULONG objIndex	// ������ ������� ������� �� 1
		)
{
// ������ ������� ��� ����������� ����� �������
	Byte *p = NULL;
	long lth = 256<<10;		// 256K
	long sizeMem = 0;

	ClearError();

	for (long attempt = 1; attempt < 3; attempt++)
		{
		p = (Byte*)MyAlloc(lth,0);
		if (!p)
			{
			NO_MEMORY;
			return 0;
			}

		InitMemory(p,lth);

		// ��������� ��������������� �� ������
		sizeMem = lth;
		if ( ROUT_GetObject(
				objIndex,
				0,	// lpMem
				&sizeMem)	// sizeMem
			)
			{
			FreeWorkMem();
			return sizeMem + 2*gBumperSize;
			}

		// ��������� ������� � ������� �������
		FreeWorkMem();
		lth = lth <<1 ;
		}

	return 0;	// �������
}
//********************************************************************
Bool32 ROUT_LoadRec6List(
		char *rec6AllFilename
		)
{
/* �������� ����� rec6all.dat, � �������
	����������� ����� ������ rec6xxx.dat
	� ����:
		0 rec6.dat
		1 rec6grm.dat
		... � �.�.

	����� rec6xxx.dat ����������� � ������� ���������:

	gAT_sizeAlphabet[LANG_TOTAL]
	gAT_upper[LANG_TOTAL][kMaxSizeAlphabet]
	gAT_lower[LANG_TOTAL][kMaxSizeAlphabet]
	gAT_vowels[LANG_TOTAL][kMaxSizeAlphabet]

*/

	ClearError();

	// ������� ���� �� ������� ������
	FILE *f = NULL;
	char buf[256] = "";
	int fd;

	fd = open_data_file(rec6AllFilename, O_RDONLY); // Was "rt".
	if(fd == -1) {
	    ERR_LOAD_REC6LIST;
	    return FALSE;
	}
	f = fdopen(fd, "rt");
	if (!f)
		{
		ERR_LOAD_REC6LIST;
		return FALSE;
		}

	while (	fgets(buf,sizeof(buf)-1,f) )
		{
		long language=-1;
		char theName[_MAX_PATH] = "";

		// ������ ������ � ������ ������������,
		// ������������ � ����� � �������, ����������
		char *p = buf;

		while (*p == ' ' || *p == '\t' )
			p++;

		if ( *p == ';' || !*p || *p == 0x0d || *p == 0x0a )
			continue;

		// ����� ����� � ��� ������� rec6xxx.dat
		sscanf(buf,"%d%s", &language, &theName[0]);

		if (language <0 || language >= LANG_TOTAL ||
			!theName[0] ||
			!LoadAlphabet(language, theName)
			)
			{
			fclose(f);
			ERR_LOAD_REC6LIST;
			return FALSE;
			}
		}

	fclose(f);
	return TRUE;
}
//********************************************************************
static BOOL LoadAlphabet(
			long language,
			char *rec6xxxFilename)
{
// �������� ����� REC6.DAT
	FILE *f = NULL;
	int fd;
	char buf[256] = "";
#ifdef WIN32
	const char line_end = '\n';
#else
	const char line_end = '\r';
#endif

	ASSERT (language >= 0 && language < LANG_TOTAL);

	long sizeAlphabet = 0;

	fd = open_data_file(rec6xxxFilename, O_RDONLY);
	if(fd == -1)
	    return FALSE;
	f = fdopen(fd, "rt");
	if (!f)
		return FALSE;

	fgets(buf,sizeof(buf)-1,f);

	sscanf(buf,"%d",&sizeAlphabet);

	if( sizeAlphabet < 1 ||
		sizeAlphabet > kMaxSizeAlphabet
	  )
		{
		fclose(f);
		ERR_LOAD_ALPHABET;
		return FALSE;
		}

	gAT_sizeAlphabet[language] = sizeAlphabet;

	char *upper = gAT_upper[language];
	char *lower = gAT_lower[language];
	char *vowels = gAT_vowels[language];

	fgets(upper,kMaxSizeAlphabet,f);
	fgets(lower,kMaxSizeAlphabet,f);
	fgets(vowels,kMaxSizeAlphabet,f);

	fclose(f);
	f = NULL;

	char *p1 = strchr(upper, line_end);
	char *p2 = strchr(lower, line_end);
	char *p3 = strchr(vowels, line_end);

	if ( p1 ) *p1 = 0;
	if ( p2 ) *p2 = 0;
	if ( p3 ) *p3 = 0;

	if ( (long)strlen(upper) != sizeAlphabet ||
		 (long)strlen(lower) != sizeAlphabet ||
		 (long)strlen(vowels)> sizeAlphabet
		)
		{
		ERR_LOAD_ALPHABET;
		return FALSE;
		}

	return TRUE;
}
//*****************************************************************
static BOOL UpdateActiveAlphabet()
{
/*  ����� ��������.
	������� ���������� �� ������ ����� gLanguage
    �� ������� ���������

	������ ������� ���������� �� SetLanguage().

*/

	if (!gAT_sizeAlphabet[gLanguage] ||
		!gAT_upper[gLanguage] ||
		!gAT_lower[gLanguage] ||
		!gAT_vowels[gLanguage] ||
		!ROUT_SetAlphabet(
			gAT_sizeAlphabet[gLanguage],
			gAT_upper[gLanguage],
			gAT_lower[gLanguage],
			gAT_vowels[gLanguage]
			)
		)
		{
		ERR_UPDATE_ACTIVE_ALPHABET;
		return FALSE;
		}

	return TRUE;
}
//********************************************************************
long ROUT_ListAvailableFormats(PWord8 buf, ULONG sizeBuf)
{
/*
	��������� ������ ��������� �������� ����������
	��� ������� ����������� ��������.
	���������� ���������� �������� ��� -1 ��� ������

	��������� ������� ���������� ��� ������� ������ �� ��������.
	���� �������� �� ���������, ��
	��������������� ������ PAGE_NOT_LOADED
*/

	long count = 0;
	ROUT_ITEM *p = (ROUT_ITEM*)buf;

	ClearError();

	memset(buf, 0, sizeBuf);
	if (sizeBuf < ROUT_FMT_COUNT * sizeof(ROUT_ITEM))
		{
		NO_MEMORY;
		return -1;
		}

	if ( !gPageHandle )
		{
		PAGE_NOT_LOADED;
		return -1;
		}

	// ������� ������ �� ��������
	BOOL haveTables = HaveTablesOnPage();

#define ITEM(a) {\
	p->code = ROUT_FMT_##a;\
	LoadString((HINSTANCE)ghInst_rout, IDS_FMT_##a,\
		p->name,sizeof(p->name));\
	p++; count++;\
		}

	ITEM (Text);
	//ITEM (SmartText);
	if (haveTables )
		{
		ITEM (TableText);
		//ITEM (CSV);
		ITEM (DBF);
		//ITEM (WKS);
		}
	ITEM (HTML);

#undef ITEM

	return count;
}
//********************************************************************
BOOL Static_GetFirstTable(
			Handle hObject,
			long reason	// ��. enum BROWSE_REASON
			)
{
// ����� ������ ������� �� ��������.

	if (reason == BROWSE_TABLE_START)
		return FALSE;	// ��������� �����

	return TRUE;	// ���������� �����
}
//********************************************************************
static BOOL HaveTablesOnPage()
{
// ������� ������ �� ��������
	if ( !gPageHandle )
		return FALSE;

	// ����������� �������� �� ������ �������
	BrowsePage(Static_GetFirstTable,
			TRUE,	// wantSkipTableCells
			TRUE	// wantSkipParagraphs
			);

	return (gHitTables > 0 );

}
//********************************************************************
