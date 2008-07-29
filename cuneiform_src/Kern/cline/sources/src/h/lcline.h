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

#include <stddef.h>
#include "templ.h"
#include "cline.h"


class CInterval;

class CInterval
{
public:
  DInterval data;

  CInterval* next;

  CInterval(){next=NULL;}
  ~CInterval(){};

};


class CEvent;

class CEvent
{
public:
  DEvent data;

  LIST<CInterval> m_interval;

  CEvent* next;

  CEvent(){next=NULL;};
  ~CEvent(){};

};


#define DirectedUpwards       0  //defines for Direction
#define DirecteDownwards      1
#define DirectedForBothSides  2

class CCutPoint;

class CCutPoint
{
public:
  DCutPoint data;

  LIST<CInterval>  m_interval;

  CCutPoint* next;

  CCutPoint(){next=NULL;};
  ~CCutPoint(){};
};

#define  InitialPointHasCrossPoint  1  //defines for Component
#define  MiddleHasCrossPoint        2
#define  EndPointHasCrossPoint      4

class CComponent;

class CComponent
{
public:
  DComponent data;

  CComponent* next;

  CComponent(){next=NULL;};
  ~CComponent(){};
};


class CLine;

class CLine
{
public:
  DLine data;

  LIST<CEvent>     m_event;                 // ���������
  LIST<CCutPoint>  m_cut_point;             // ����� ����������� � �������������� �������
  LIST<CComponent> m_comp;                  // ���������� ����� � ���������� ����� �����������

 CLine* next;

CLine(){next=NULL;};
~CLine(){};

};


class CHLine;

class CHLine
{
public:
	LIST<CLine>                   m_line;

	CHLine* next;
	Word32 reserv;

	CHLine(){next=NULL;}
	~CHLine(){}
};

class CInvMem;

class CMem
{
public:
	void* lp;
	CMem* next;
	CMem(){next=NULL;lp=NULL;}
	~CMem(){}
};

class CAllMem
{
public:
 LIST<CMem> pInvMas;
 LIST<CMem> pEventMas;
 LIST<CMem> pCompMas;
 LIST<CMem> pCupointMas;
 LIST<CMem> pLineMas;
 LIST<CMem> pHLineMas;
 CAllMem(){};
 ~CAllMem(){};
};



