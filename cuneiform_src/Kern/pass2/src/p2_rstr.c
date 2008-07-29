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

 #include <stdlib.h>

 #include "nt_types.h"
 #include <stdio.h>
 #include <string.h>

 #include "cstr.h"
 #include "p2.h"

// ���������� � �����������/�������� ����� - �� first �� last,
// ��������� ��������� � lineFon
Int32 my_p2_RecogCutGlu( CSTR_rast  first,CSTR_rast last, CSTR_line  lineFon,
						P2GLOBALS *p2glob)
                   {return 0;};

//////////////////////
// ���������� �������, �������������
void  my_p2_SetP2Alphabet(int lang,char *alf)
{
	  memset(alf,0,256);
	  return;
}
BYTE  my_p2_GetCodePage(int lang){return 0;};
void  my_p2_DecodeCode(char *pCode,int let){return;};
//////////////////
// ����
BOOL    my_NoStopSnapLEO(void){return FALSE;};
Bool16	my_snap_monitor_ori(CSTR_line *snap_line, Int32 num_lines){return FALSE;};
Bool16	my_snap_activity(Word8 a){return FALSE;};
Bool16	my_snap_show_text(Word8 *txt){return FALSE;};

Bool32  mySetupField(void *letInfo,Int32 nFont,void *info) {return FALSE;};
Bool32  mySetupPage(void *info) {return FALSE;};
Bool32  mySpecRecog(RecObject *ro) {return FALSE;};
///////////////
// �������� �� �������
BOOL    my_p2_spell(PCHAR s,BYTE lang) {return FALSE;};

///////////////////////////////
// ���������� � �����������/�������� ����� - �� first �� last,
// ��������� ��������� � lineFon
Int32 (*RSTR_p2_RecogCutGlu)( CSTR_rast  first,CSTR_rast last, CSTR_line  lineFon,
							 P2GLOBALS *pglob)=
                   my_p2_RecogCutGlu;

//////////////////////
// ���������� �������, �������������
void  (*RSTR_p2_SetP2Alphabet)(int lang,char *alf)=my_p2_SetP2Alphabet;
BYTE  (*RSTR_p2_GetCodePage)(int lang)=my_p2_GetCodePage;
void  (*RSTR_p2_DecodeCode)(char *pCode,int let)=my_p2_DecodeCode;
//////////////////
// ����
BOOL    (*RSTR_p2_NoStopSnapLEO)(void)=my_NoStopSnapLEO;
Bool16	(*RSTR_p2_snap_monitor_ori)(CSTR_line *snap_line, Int32 num_lines)=my_snap_monitor_ori;
Bool16	(*RSTR_p2_snap_activity)(Word8 a)=my_snap_activity;
Bool16	(*RSTR_p2_snap_show_text)(Word8 *txt)=my_snap_show_text;
///////////////
// �������� �� �������
BOOL    (*RSTR_p2_spell)(PCHAR s,BYTE lang)=my_p2_spell;

// �������������� ������������� (LEO)
Bool32  (*ADDREC_SetupField)(void *letInfo,Int32 nFont,void* fontInfo)=mySetupField;
Bool32  (*ADDREC_SetupPage)(void *info)=mySetupPage;
Bool32  (*ADDREC_Recog)(RecObject* obj)=mySpecRecog;

//Word8	db_status=0;
//Word8   spec_camera=0;

P2_FUNC(void) P2_SetRSTR( Handle RecogCutGlu,
                          Handle setAlpha,Handle GetPage,Handle Decode,
                          Handle NoStopSnapLEO, Handle monitor_ori,
                          Handle activity,     Handle show_text,
                          Handle spell,
						  Handle setupPage,Handle setupField,
						  Handle specRecog)
{
 RSTR_p2_RecogCutGlu = RecogCutGlu;

 RSTR_p2_SetP2Alphabet = setAlpha;
 RSTR_p2_GetCodePage = GetPage;
 RSTR_p2_DecodeCode  = Decode;

 RSTR_p2_NoStopSnapLEO   = NoStopSnapLEO;
 RSTR_p2_snap_monitor_ori= monitor_ori;
 RSTR_p2_snap_activity   = activity;
 RSTR_p2_snap_show_text  = show_text;

 RSTR_p2_spell = spell;

 if(setupPage)
  ADDREC_SetupPage=setupPage;
 if(setupField)
  ADDREC_SetupField=setupField;
 if(specRecog)
  ADDREC_Recog = specRecog;
 return;
}
///////////////
