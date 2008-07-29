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

/*#include <windows.h>*/

#define __CPAGE__

#include "globus.h"
#include "cpage.h"
#include "backup.h"
#include "polyblock.h"
#include "resource.h"

void CleanData(Word32 Type,void * lpData,Word32 Size)
// �������������� ����� �������� ��������� ������ ��� ������ ��������
{
    if(Type == TYPE_TEXT || Type == TYPE_IMAGE)
	{
		POLY_ *poly = (POLY_ *)lpData;
		COMMON *com = &poly->com;
		int maxnum=MaxNum;
		memset(&com->Vertex[com->count],0,(char*)&com->Vertex[maxnum]-(char*)&com->Vertex[com->count]);
		memset(&poly->mark[com->count],0,(char*)&poly->mark[maxnum]-(char*)&poly->mark[com->count]);
	}
	else
    if(Type == TYPE_TABLE)
	{
		TABLE_ *table = (TABLE_ *)lpData;
		COMMON *com = &table->com;
		memset(&com->Vertex[com->count],0,(char*)&com->Vertex[MaxNum]-(char*)&com->Vertex[com->count]);
		Int32 *line=table->LineY;
		memset(&line[table->num_rows+1],0,(char*)&line[MaxHorLines-1]-(char*)&line[table->num_rows+1]);
		line=table->LineX;
		memset(&line[table->num_colons+1],0,(char*)&line[MaxVerLines-1]-(char*)&line[table->num_colons+1]);
		for (Int32 j=0; j<MaxVerLines; j++)
			for (Int32 i=0; i<MaxHorLines; i++)
				if (i>=table->num_rows || j>=table->num_colons)
					table->Visible[i][j][0]=table->Visible[i][j][1]=table->TypeCell[i][j]=0;
	}
}

Bool32 ComplianceVersions(Word32 Type, char ** lpData, Word32 *Size)
//���������� ������ ����� ������ � �������� ���������;
// ���� ��������� ������ - ����������� ������, ���� ������ - ������
{
	Word32 NewSize=*Size;
	if (Type==TYPE_TEXT  ||  Type==TYPE_IMAGE)
		 NewSize = sizeof(POLY_);
	else
	if (Type==TYPE_TABLE)
		 NewSize = sizeof(TABLE_);
	if (NewSize < *Size)
		return FALSE;
	if (NewSize > *Size)
	{
		char *lpNewData = new char[NewSize];
		if (!lpNewData)
			return FALSE;
		memcpy(lpNewData,*lpData,*Size);
		memset(lpNewData+(*Size),0,NewSize-(*Size));
		delete *lpData;
		*lpData=lpNewData; 	*Size=NewSize;
	}
	return TRUE;
}

Bool32 Compress(char * lpData, Word32 Size, char ** compressedData, Word32 * compressedSize)
{
// �������� ������ �� �� ����� MIN_REPEAT ���������� �������� �� ������� ����������
#define MIN_REPEAT 2*sizeof(CompressHeader)

	if (Size==0)
		return FALSE;

   char *newData = new char[Size+sizeof(CompressHeader)]; //������ ������ �����, ���� ��������� �� ����������,
   if (!newData)										  //����� - �� ������ ���������
	   return FALSE;
   char *lpNewData = newData;

	// ������� ���� - ������� �������� � ��������, ����������� ����������� ���������;
	// ����� ��� ����������
	char * ordinary=lpData,	  //������� ��������
		 * end=ordinary+Size;
	do
	{
		Word32 count=1;
		char * current=ordinary+1,
			 * repeating=ordinary; //��������, ����������� ����������� ���������;
		while (current<end)
		{
			if (*current != *repeating)
			{
				if (current-repeating>=MIN_REPEAT)  break;
				repeating=current;
			}
			current++;
		}
		count=current-repeating;

		if (count<MIN_REPEAT)  //����� �� �����, � ���������� ���� - ���������
		{
			repeating += count;  count=0;
		}
		if (repeating>ordinary)  //������� ��������
		{
			CompressHeader head={0};
			head.bCompressed=FALSE;
			head.wCount=repeating-ordinary;
			memcpy(lpNewData,&head,sizeof(head));    lpNewData += sizeof(head);
			memcpy(lpNewData,ordinary,head.wCount); lpNewData += head.wCount;
		}
		if (count)				 //��������, ����������� �������� (*repeated)
		{
			CompressHeader head={0};
			head.bCompressed=TRUE;
			head.cRepeater=*repeating;
			head.wCount=count;
			memcpy(lpNewData,&head,sizeof(head));    lpNewData += sizeof(head);
		}
		ordinary=current;
	}
	while(ordinary<end);
	*compressedData = newData;  *compressedSize = lpNewData-newData;
	return TRUE;
}

//#################################
Bool32 Decompress(char * lpData, Word32 Size, char ** decomData, Word32 * decomSize)
{
	if (Size==0)
		return FALSE;

	char * old=lpData, *end=lpData+Size;

	//���������� ������ ����� ������������
	Word32 newSize=0;
	while (old<end)
	{
		CompressHeader *head = (CompressHeader *)old;
		old += sizeof(CompressHeader);
		if (!head->bCompressed) old += head->wCount;
		newSize += head->wCount;
	}

	//�������������
	char *newData = new char[newSize], *modern=newData;
	if (!newData)
		return FALSE;

	old=lpData;
	while (old<end)
	{
		CompressHeader *head = (CompressHeader *)old;
		old += sizeof(CompressHeader);
		if (head->bCompressed)
			memset(modern,head->cRepeater,head->wCount);
		else
		{
			memcpy(modern,old,head->wCount);
			old += head->wCount;
		}
		modern += head->wCount;
	}
	*decomData=newData;  *decomSize=newSize;
	return TRUE;
}




