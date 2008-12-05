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

#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "lst3_win.h"

#include "wind32.h"

#include "compat_defs.h"

LONG filelength_m(FILE *stream)
{
   long pos=fseek(stream, 0L, SEEK_END);
   fseek(stream, 0L, SEEK_SET);
   return pos;
}

static uint cr=13,lf=10;
/*==Return:
    -1 - END_OF_FILE,
    -2 - LONG STRING,
    >=0 - ����� ������,���� NULL_STRING,=0 (������. �����)
  ���������:
    str - ����� ������,
    max_len - ����������� �� ����� ������
    f - ������������� ����� (����������)*/
int fgets_m(char *str,int max_len,FILE *f)
/*=========*/
{ int len=-1;
  while(++len < max_len)
  { str[len]=get_kod(f);
    if(str[len]==0) return -1; /*END FILE*/
    if(len && (uint)str[len-1] == cr && (uint)str[len] == lf)
      { str[--len]=0; return len; }
  }
  str[len-1]=0; return -2; /*LONG STRING*/
}
/*=========Return: >0 - ��� �������, 0 - END_OF_FILE*/
char get_kod(FILE *f)
/*=========*/
{ char sym;
  if(fread(&sym,1,1,f) == 0) return 0; /*END FILE*/
  return sym;
}
/*==Return:
    -1 - END_OF_FILE,
    -2 - LONG STRING,
    >=0 - ����� ������,���� NULL_STRING,=0 (������. �����)
  ���������:
    str - ����� ������,
    max_len - ����������� �� ����� ������
    f - ������������� ����� (����������)*/
int fgets1_m(char *str,int max_len,FILE *f)
/*=========*/
{ int len=-1;
  if(f==NULL) { get1_kod(f); return 0; }
  while(++len < max_len)
  { str[len]=get1_kod(f);
    if(str[len]==0) return -1; /*END FILE*/
    if(len && (uint)str[len-1] == cr && (uint)str[len] == lf)
      { str[--len]=0; return len; }
  }
  str[len-1]=0; return -2; /*LONG STRING*/
}
#define SIZE_BLOC 512
/*=========Return: >0 - ��� �������, 0 - END_OF_FILE*/
char get1_kod(FILE *f)
/*=========*/
{ static char *b; static int len=-1,pos=-1;
  if(f==NULL)
   { if(len!=-1 || pos!=-1) free(b); len=-1,pos=-1; return 0; }
  if(pos >= len)
  { if(pos == -1) b=(char*)malloc(SIZE_BLOC);
    if((len=fread(b,1,SIZE_BLOC,f)) == 0) {free(b);return 0;/*END FILE*/}
    pos=0;
  }
  return b[pos++];
}
/*=���������:
   str   - ������� ������,
   param - ������, ���������� ������� ���������� ��������(����������� - ������),
   max_len-��������. ����� ������ � ���������.
   Return: ��������� �� ������, �� ������� ������� ����� ���������,
           ���� �������� �� ������� ��������, ������������ NULL STRING
*/
char *get_param(char *str,char *param,int max_len)
/*=========*/
{ int len;
  len=-1; while(str[++len]==' '); str+=len;/*������� ������� ����� �� ���������*/
  len=-1;
  while(++len < max_len && str[len] != ' ') /*����� ������� ������� ������*/
  { if( (param[len]=str[len]) == 0) break; /*Detect END STRING*/
    if(len && (uint)str[len-1] == cr && (uint)str[len] == lf) /*Detect <cr><lf>*/
      { --len; break; }
  }
  /*���� �������� ����� �������, ���������� ������� ��� ���������*/
  if(len < max_len-1) param[len]=0; else param[len=0]=0;
  return str+len;
}
