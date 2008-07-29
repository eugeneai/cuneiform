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

#ifndef __BACKUP_H__
#define __BACKUP_H__

#define __CPAGE__
//#define DPUMA_ON 1

#include "page.h"

class BACKUPPAGE : public PAGE
{
public:
	PtrList<PAGE> BackUpPage;
	Handle		  hCurBackUp;

public:
	BACKUPPAGE();
	~BACKUPPAGE();

	void Clear();
	Handle BackUp(Handle backup = NULL);
	Bool32 Redo(Handle backup);
	Bool32 Undo(Handle backup);

	Bool32 Save(Handle to);
	Bool32 SaveCompress(Handle to);
	Bool32 Restore(Handle from);
	Bool32 RestoreCompress(Handle from);

	BACKUPPAGE & operator = (BACKUPPAGE & Page);
	inline Word32 GetCurPos(){ return BackUpPage.GetPos(hCurBackUp);};

};

#ifdef _DEBUG
// for debug functions
#endif

 void   SetReturnCode_cpage(Word16 rc);
 Word16 GetReturnCode_cpage();

void DefConvertInit();
Word32 DefConvertBlock( Word32 dwContext,
					Word32 TypeIn,void * lpDataIn,Word32 SizeIn,
					Word32 TypeOut,void * LpDataOut, Word32 SizeOut);
Word32 DefConvertPage( Word32 dwContext,
					Word32 TypeIn,void * lpDataIn,Word32 SizeIn,
					Word32 TypeOut,void * LpDataOut, Word32 SizeOut);
void CleanData(Word32 Type,void * lpData,Word32 Size);
Bool32 ComplianceVersions(Word32 Type, char ** lpData, Word32 *Size);
Bool32 Compress(char * lpData, Word32 Size, char ** compressedData, Word32 * compressedSize);
Bool32 Decompress(char * lpData, Word32 Size, char ** decomData, Word32 * decomSize);

Word32 TYPE_DESK_to_CPAGE_TABLE(TABLE_DESC * lpDataIn,Word32 SizeIn,CPAGE_TABLE * LpDataOut,Word32 SizeOut);
Word32 CPAGE_TABLE_to_TYPE_DESK( CPAGE_TABLE * lpDataIn,Word32 SizeIn,TABLE_DESC * LpDataOut,Word32 SizeOut);
Word32 TYPE_PICTURE_to_CPAGE_PICTURE(POLY_ * lpDataIn,Word32 SizeIn,CPAGE_PICTURE * LpDataOut,Word32 SizeOut);
Word32 CPAGE_PICTURE_to_TYPE_PICTURE( CPAGE_PICTURE * lpDataIn,Word32 SizeIn,POLY_ * LpDataOut,Word32 SizeOut);

#ifdef DPUMA_ON
	Handle	ProfileProlog();
	void	ProfileEpilog(Handle prev);

	#define PROLOG Handle	hProfile = ProfileProlog()
	#define EPILOG ProfileEpilog(hProfile)

#else

	#define PROLOG
	#define EPILOG

#endif


#endif
