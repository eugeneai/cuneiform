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

#include <stdio.h>
/*#include <windows.h>*/
#include "recdefs.h"
#include "ccom.h"
#include "cpage.h"

#define MAX_STR_COUNT 100

class CHstr;

class CHstr
{
 public:
  CHstr* next;
  Word8* ImageName;
  int m_num_frag;
  BOOL vertical;
  BOOL neg;
  int left;
  int top;
  int w;
  int h;

 public:
  CHstr();
  ~CHstr();
};


class CLhstr
{
  CHstr* m_root;
  CHstr* m_tail;
  
 public:
  
  CLhstr();
  ~CLhstr();
  CHstr* Add();
  void DelTail();
  CHstr* GetRoot();
  CHstr* GetNext(CHstr*);
};

class CPrepHstr;

class CPrepHstr
{
 public:
  CPrepHstr* next;
  Word8 ImageName[CPAGE_MAXNAME];
  int m_num_frag;
  BOOL vertical;
  BOOL neg;
  int left;
  int oldleft;
  int top;
  int w;
  int h;
  CCOM_handle hStrCCOM;
  Rect16* pRc;
  Rect16 prc[MAX_STR_COUNT];
  int nRc;
  BOOL fl_rotate;
  int* hi;
  Int16 phi[MAX_STR_COUNT];
  Rect16 unrotRc;
  Int16* begx;
  Int16* movey;
  Word8* flmovey;

 public:
  CPrepHstr();
  ~CPrepHstr();
};


class CLPrepHstr
{
  CPrepHstr* m_root;
  CPrepHstr* m_tail;
  
 public:
  
  CLPrepHstr();
  ~CLPrepHstr();
  CPrepHstr* Add();
  void DelTail();
  CPrepHstr* GetRoot();
  CPrepHstr* GetNext(CPrepHstr*);
};

struct MATRIX
{
 int a11;
 int a12;
 int a21;
 int a22;
};
