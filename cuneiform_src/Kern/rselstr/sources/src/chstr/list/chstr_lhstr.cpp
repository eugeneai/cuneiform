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

#include "lhstr.h"

CHstr* CLhstr::Add()
{
 if(m_root==NULL)
 {
  m_root= new CHstr;
  m_tail=m_root;
  m_root->next=NULL;
  return m_root;
 }
 CHstr* loc=NULL;
 loc= new CHstr;
 if(loc)
 {
  m_tail->next=loc;
  m_tail=loc;
  loc->next=NULL;
 }
 return loc;
}

void CLhstr::DelTail()
{
 if(m_root==m_tail)
 {
	 delete m_root;
	 m_root=m_tail=NULL;
	 return;
 }
 CHstr* str=m_root;
 while(GetNext(str)!=m_tail)
	 str=GetNext(str);
 str->next=NULL;
 delete m_tail;
 m_tail=str;
}

CHstr* CLhstr::GetRoot()
{
	return m_root;
}

CHstr* CLhstr::GetNext(CHstr* hstr)
{
 if(!hstr)
	 return NULL;
 return hstr->next;
}

CLhstr::CLhstr()
{
 m_root=NULL;
 m_tail=NULL;
}

CLhstr::~CLhstr()
{
 CHstr* loc;
 while(m_root!=NULL)
 {
	 loc=m_root->next;
	 delete m_root;
	 m_root=loc;
 }
}


CHstr::CHstr()
{
 ImageName=NULL;
}

CHstr::~CHstr()
{
 delete[] ImageName;
}





CPrepHstr* CLPrepHstr::Add()
{
 if(m_root==NULL)
 {
  m_root= new CPrepHstr;
  m_tail=m_root;
  m_root->next=NULL;
  return m_root;
 }
 CPrepHstr* loc=NULL;
 loc= new CPrepHstr;
 if(loc)
 {
  m_tail->next=loc;
  m_tail=loc;
  loc->next=NULL;
 }
 return loc;
}

void CLPrepHstr::DelTail()
{
 if(m_root==m_tail)
 {
	 delete m_root;
	 m_root=m_tail=NULL;
	 return;
 }
 CPrepHstr* str=m_root;
 while(GetNext(str)!=m_tail)
	 str=GetNext(str);
 str->next=NULL;
 delete m_tail;
 m_tail=str;
}


CPrepHstr* CLPrepHstr::GetRoot()
{
	return m_root;
}

CPrepHstr* CLPrepHstr::GetNext(CPrepHstr* hstr)
{
 if(!hstr)
	 return NULL;
 return hstr->next;
}

CLPrepHstr::CLPrepHstr()
{
 m_root=NULL;
 m_tail=NULL;
}

CLPrepHstr::~CLPrepHstr()
{
 CPrepHstr* loc;
 while(m_root!=NULL)
 {
	 loc=m_root->next;
	 delete m_root;
	 m_root=loc;
 }
}

CPrepHstr::CPrepHstr()
{
 hStrCCOM=0;
 pRc=NULL;
 nRc=0;
 fl_rotate=FALSE;
 begx=NULL;
 movey=NULL;
 flmovey=NULL;
 hi=NULL;
}

CPrepHstr::~CPrepHstr()
{
 if(hStrCCOM)
	 CCOM_DeleteContainer(hStrCCOM);
 delete[] pRc;
 delete[] begx;
 delete[] movey;
 delete[] flmovey;
 delete[] hi;
}

