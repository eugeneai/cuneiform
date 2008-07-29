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

#ifndef __STDPRT_H
#define __STDPRT_H

#include "std.h"

typedef Int32 HEvent32;
typedef struct tagStdPrtEvent
{
   char*  szFormat;  // printf like format
   Int32    nFlags;
#define SPE_PUBLIC   0x0001 // �������� � ����� ���������
#define SPE_WAIT     0x0002 // ��������� ���������� ������ �������
#define SPE_WITHTIME 0x0004 // ���������� ����� �������
   HEvent32 hEvent;  // ����� ������, ����������� ������ stdPrt.cpp, ���������� 0
   Int32    nFileNo; // ��������� ��� ����������� ���� � ����� � ����� �������
} StdPrtEvent;


//STD_FUNC(HEvent32) stdPrtRegister( StdPrtEventType* pStdPrtEventType );
   // returns registered number of event type; 0 - failed
//STD_FUNC(Int32) stdPrt( HEvent32 nEvent, ... );
   // returns number of event if was successfully accepted, 0 - failed

STD_FUNC(Int32) stdPrt( StdPrtEvent* pspe, ... );
STD_FUNC(Int32) stdPrt( StdPrtEvent* pspe,  va_list& list);
   // returns number of event if was successfully accepted, 0 - failed
STD_FUNC(Bool32) stdSysPrt( Int32 EvnNo, ... );
   // returns true if sysevent is succesfully accepted
//STD_FUNC(Bool32) stdPrtRestore( n, ... );
STD_FUNC(Int32) stdSysPrt( Int32 EvnNo, va_list& list );
STD_FUNC(Bool32) stdPrtStartConsole();
STD_FUNC(void) stdPrtStopConsole();

STD_FUNC(Bool32) stdPrtStartTransaction(char* user_name,char* prog_id);
STD_FUNC(Bool32) stdPrtRollback();
STD_FUNC(Bool32) stdPrtEndTransaction(char* user_name,char* prog_id);

#endif
