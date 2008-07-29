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

#include "clinefunc.h"

extern int CLINE_Debug;
extern int CLINE_Debug_2;
extern LIST<CHLine>* pLCont;

BOOL IfExistContainer(CHLine* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
   if(phline==pelem)
	   return TRUE;
 }
 return FALSE;
}


BOOL IfExistLine(CLine* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 CLine* pline=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
  for(pline=phline->m_line.GetRoot();pline;pline=phline->m_line.GetNext(pline))
  {
   if(pline==pelem)
	   return TRUE;
  }
 }
 return FALSE;
}

BOOL IfExistEvent(CEvent* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 CLine* pline=NULL;
 CEvent* pevent=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
  for(pline=phline->m_line.GetRoot();pline;pline=phline->m_line.GetNext(pline))
  {
   for(pevent=pline->m_event.GetRoot();pevent;pevent=pline->m_event.GetNext(pevent))
   {
    if(pevent==pelem)
	    return TRUE;
   }
  }
 }
 return FALSE;
}

BOOL IfExistCutPoint(CCutPoint* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 CLine* pline=NULL;
 CCutPoint* pcupoint=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
  for(pline=phline->m_line.GetRoot();pline;pline=phline->m_line.GetNext(pline))
  {
   for(pcupoint=pline->m_cut_point.GetRoot();pcupoint;pcupoint=pline->m_cut_point.GetNext(pcupoint))
   {
    if(pcupoint==pelem)
	    return TRUE;
   }
  }
 }
 return FALSE;
}

BOOL IfExistComp(CComponent* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 CLine* pline=NULL;
 CComponent* pcomp=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
  for(pline=phline->m_line.GetRoot();pline;pline=phline->m_line.GetNext(pline))
  {
   for(pcomp=pline->m_comp.GetRoot();pcomp;pcomp=pline->m_comp.GetNext(pcomp))
   {
    if(pcomp==pelem)
	    return TRUE;
   }
  }
 }
 return FALSE;
}


BOOL IfExistEventInv(CInterval* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 CLine* pline=NULL;
 CEvent* pevent=NULL;
 CInterval* pinv=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
  for(pline=phline->m_line.GetRoot();pline;pline=phline->m_line.GetNext(pline))
  {
   for(pevent=pline->m_event.GetRoot();pevent;pevent=pline->m_event.GetNext(pevent))
   {
	for(pinv=pevent->m_interval.GetRoot();pinv;pinv=pevent->m_interval.GetNext(pinv))
	{
     if(pinv==pelem)
	     return TRUE;
	}
   }
  }
 }
 return FALSE;
}

BOOL IfExistCutPointInv(CInterval* pelem)
{
 if(!CLINE_Debug_2)
	 return TRUE;
 CHLine* phline=NULL;
 CLine* pline=NULL;
 CCutPoint* pcupoint=NULL;
 CInterval* pinv=NULL;
 for(phline=pLCont->GetRoot();phline;phline=pLCont->GetNext(phline))
 {
  for(pline=phline->m_line.GetRoot();pline;pline=phline->m_line.GetNext(pline))
  {
   for(pcupoint=pline->m_cut_point.GetRoot();pcupoint;pcupoint=pline->m_cut_point.GetNext(pcupoint))
   {
	for(pinv=pcupoint->m_interval.GetRoot();pinv;pinv=pcupoint->m_interval.GetNext(pinv))
	{
     if(pinv==pelem)
	     return TRUE;
	}
   }
  }
 }
 return FALSE;
}



