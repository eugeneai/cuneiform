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
#include <stdlib.h>
#include <setjmp.h>

#include "c_types.h"
#include "msgerr.h"
#include "kernel.h"
#include "face_lng.h"

#if MORDA==LANG_ENGLISH
/*=============	English definitions for error messages ========	*/
#define msg_0_1 "Format error."
#define msg_0_2 "Some of recognition tables cannot be found."
#define msg_0_3 "Debug stop."
#define msg_0_4 "Sorry, DEMO version does not permit scanning."
#define msg_0_5 "Dictionary file(s) for the language not found."

#define msg_1_1  "101. FileSys: No enough memory for components file."
#define msg_1_2  "102. FileSys: No place in the components file."
#define msg_1_3  "103. ExtrComp(an): Main number allocation fail."
#define msg_1_4  "104. ExtrComp(an): Unable to exclude large picture."
#define msg_1_5  "105. FileSys: No place in the roots file."
#define msg_1_6  "106. LinesForming: Not enough memory."
#define msg_1_7	 "107. LinesForming: Unable to count page skew."
#define msg_1_8  "108. LinesForming: Empty page."
#define msg_1_9  "109. ExtrComp(mn): No memory for boxes."
#define msg_1_10 "110. FileSys: No place for strings."
#define msg_1_11 "111. FileSys: No strings have been found."
#define msg_1_12 "112. Tools: No place in the kit."
#define msg_1_13 "113. Main: No memory for working area (1Mb)."
#define msg_1_14 "114. Extrcomp(mn): Image is not a fax 100x200 dpi."
#define msg_1_15 "115. Sweeper: Can't create/open work file TEMP.CMP"
#define msg_1_16 "116. Sweeper: No enough space in work file TEMP.CMP"
#define msg_1_17 "117. Sweeper: Error on reading work file TEMP.CMP"

#define msg_2_1 "201. ScanTiff: Unable to access image."
#define msg_2_2 "202. ScanTiff: Error during image read."
#define msg_2_3 "203. ScanTiff: Contradictory image information."
#define msg_2_4 "204. ScanTiff: Resolution of this image isn't into 100dpi - 800dpi range."
#define msg_2_5 "205. ScanDIB: Unable to access DIB."

#define msg_3_1 "301. Scantiff: group-4 format error."
#define msg_3_2 "302. Put page into scaner."

#define msg_4_1 "401. Spelling: cannot find vocabulary."
#define msg_4_2 "402. Spelling: cannot open dynamic vocabulary."
#define msg_4_3 "403. Spelling: the page has been processed by speller."
#define msg_4_4 "404. Spelling: not enough memory."
#define msg_4_5 "405. Spelling: ed-file is corrupted."
#define msg_4_6 "406. Spelling: no ed_file."
#define msg_4_7 "407. Spelling: postrecognition error."

#define msg_6_1 "601. TextSave: Open error."		// only DOS
#define msg_6_2 "602. TextSave: Write error."
#define msg_6_3 "603. TextSave: Out of memory."
#define msg_6_4 "604. TextSave: Cannot open temporary ED-file."
#define msg_6_5 "605. Lineout: Open error in ED-file."	// Only DOS
#define msg_6_6 "606. Lineout: Read error in ED-file."
#define msg_6_7 "607. Lineout: Empty page."
#define msg_6_8 "608. TextSave: Unuseble coding for this language."
#define msg_6_9 "609. RTF: ED-file is corrupted."
#define msg_6_10 "610. Not used."
#define msg_6_11 "611. Lineout: Write error on ED-file."
#define msg_6_12 "612. Not used."
#define msg_6_13 "613. Not used."
#define msg_6_14 "614. Not used."

#define msg_7_1 "701. Very long path name."
#define msg_7_2 "702. User break."
#define msg_7_3 "703. Cannot connect with user."
#define msg_7_4 "704. Cannot process picture. Picture too big."
#define msg_7_5 "705. Open/read/write file error."
#define msg_7_6 "706. Pass II: Out of memory."
#define msg_7_7 "707. Internal error. Please, report to manufacturer."
#define msg_7_8 "708. Read/write file error."
#define msg_7_9 "709. File open fail. "
#define msg_7_10 "710. Pass II: Not enough memory for clusterization."
#define msg_7_11 "711. Recogntion need password. See submenu Password in menu Help."

#define msg_8_1 "801. Edout: Ed-file is not open."
#define msg_8_2 "802. Edout: Fragment's number is wrong."
#define msg_8_3 "803. Edout: String's number is wrong."
#define msg_8_4 "804. Edout: Word's number is wrong."
#define msg_8_5 "805. Edout: Character's number is wrong."

#elif MORDA==LANG_RUSSIAN
/*=============	���᪨� definitions for error messages ========	*/
#define msg_0_1 "�訡�� �ଠ�஢����."
#define msg_0_2 "�� ������� ������� ⠡���� �ᯮ��������."
#define msg_0_3 "Debug stop."
#define msg_0_4 "�����, �� DEMO ����� �� ᪠�����."
#define msg_0_5 "�� ������ ᫮���� ��� ��襣� �몠."

#define msg_1_1 "101. FileSys: �� 墠⠥� ����� ��� ᯨ᪠ ���������."
#define msg_1_2 "102. FileSys: ��� ���� � ᯨ᪥ ���������."
#define msg_1_3 "103. ExtrComp(an): Main number allocation fail."
#define msg_1_4 "104. ExtrComp(an): �� ���� 㤠���� ������� ���⨭��."
#define msg_1_5 "105. FileSys: ��� ���� � ��୥��� ᯨ᪥."
#define msg_1_6 "106. LinesForming: �� 墠⠥� ����⨢��� �����."
#define msg_1_7	"107. LinesForming: ����� ��४�� ��࠭���."
#define msg_1_8 "108. LinesForming: ����� ��࠭��."
#define msg_1_9 "109. ExtrComp(mn): ��� ����� ��� ��஡�祪."
#define msg_1_10 "110. FileSys: ��� ���� ��� ��ப�."
#define msg_1_11 "111. FileSys: �� ������� �� ����� ��ப�."
#define msg_1_12 "112. Tools: No place in the kit."
#define msg_1_13 "113. Main: �� 墠⠥� ����⨢��� ����� (1Mb)."
#define msg_1_14 "114. Extrcomp(mn): ��ࠧ ��࠭��� �� 䠪� 100x200 dpi."
#define msg_1_15 "115. Sweeper: �� ���� ᮧ����/������ ࠡ�稩 䠩� TEMP.CMP"
#define msg_1_16 "116. Sweeper: �� 墠⠥� ���� ��� ࠡ�祣� 䠩�� TEMP.CMP"
#define msg_1_17 "117. Sweeper: �訡�� �⥭�� ࠡ�祣� 䠩�� TEMP.CMP"

#define msg_2_1 "201. ScanTiff: ��� ����㯠 � ����ࠦ����."
#define msg_2_2 "202. ScanTiff: �訡�� �� �६� �⥭�� ����ࠦ����."
#define msg_2_3 "203. ScanTiff: ��⨢��稢�� ���ଠ�� �� ����ࠦ����."
#define msg_2_4 "204. ScanTiff: Resolution of this image isn't into 100dpi - 800dpi range."
#define msg_2_5 "205. ScanDIB: Unable to access DIB."

#define msg_3_1 "301. Scantiff: �訡�� �ଠ� group-4."
#define msg_3_2 "302. ������� � ᪠��� ��࠭���."

#define msg_4_1 "401. Spelling: ᫮���� �� ������."
#define msg_4_2 "402. Spelling: �� ���� ������ �������᪨� ᫮����."
#define msg_4_3 "403. Spelling: ��࠭�� �뫠 �⪮�४�஢����."
#define msg_4_4 "404. Spelling: �� 墠⠥� �����."
#define msg_4_5 "405. Spelling: ED-䠩� �ᯮ�祭."
#define msg_4_6 "406. Spelling: ��� ED_䠩��."
#define msg_4_7 "407. Spelling: �訡�� ���ᯮ��������."

#define msg_6_1 "601. TextSave: �訡�� ������."		// only DOS
#define msg_6_2 "602. TextSave: �訡�� �����."
#define msg_6_3 "603. TestSave: �� 墠⠥� �����."
#define msg_6_4 "604. TextSave: �� ���� ������ �६���� ED-䠩�."
#define msg_6_5 "605. Lineout: �訡�� ������ ED-䠩��."	// Only DOS
#define msg_6_6 "606. Lineout: �訡�� �⥭�� ED-䠩��."
#define msg_6_7 "607. Lineout: ����� ��࠭��."
#define msg_6_8 "608. TestSave: ���ᯮ��㥬�� ����஢�� ��� ������� �몠."
#define msg_6_9 "609. RTF: ED-䠩� �ᯮ�祭."
#define msg_6_10 "610. Not used."
#define msg_6_11 "611. Lineout: �訡�� ����� ED-䠩��."
#define msg_6_12 "612. Not used."
#define msg_6_13 "613. Not used."
#define msg_6_14 "614. Not used."

#define msg_7_1 "701. ���誮� ������ ����."
#define msg_7_2 "702. ���뢠��� �� ���짮��⥫�."
#define msg_7_3 "703. �� ���� �易���� � ���짮��⥫��."
#define msg_7_4 "704. ���������� ��ࠡ���� ���������. ���誮� ������ ���⨭��."
#define msg_7_5 "705. �訡�� ������/�⥭��/����� 䠩��."
#define msg_7_6 "706. ��� II: ����㯭�� ������ ���௠��."
#define msg_7_7 "707. ���⥬��� �訡��. ��令��� � �ந�����⥫��."
#define msg_7_8 "708. �訡�� �� �⥭��/����� 䠩�� "
#define msg_7_9 "709. �訡�� ������ 䠩�� "
#define msg_7_10 "710. ��� II: �� 墠⠥� ����� ��� �����ਧ�樨."
#define msg_7_11 "711. ��� �ᯮ�������� ����室�� ��஫�(�. �㭪� ��஫� ���� ������)"

#define msg_8_1 "801. Edout: ED-䠩� �� �����."
#define msg_8_2 "802. Edout: �� ���४�� ����� �ࠣ����."
#define msg_8_3 "803. Edout: �� ���४�� ����� ��ப�."
#define msg_8_4 "804. Edout: �� ���४�� ����� ᫮��."
#define msg_8_5 "805. Edout: �� ���४�� ����� ᨬ����."
#endif

/*============== Messages groups structure ====================	*/

static PCHAR format_msg[]={msg_0_1,msg_0_2,msg_0_3,msg_0_4,msg_0_5};
static PCHAR comp_msg[]={msg_1_1,msg_1_2,msg_1_3,msg_1_4,msg_1_5,
	                     msg_1_6,msg_1_7,msg_1_8,msg_1_9,msg_1_10,
						 msg_1_11,msg_1_12,msg_1_13,msg_1_14,msg_1_15,
						 msg_1_16,msg_1_17};
static PCHAR image_msg[]={msg_2_1,msg_2_2,msg_2_3,msg_2_4,msg_2_5};
static PCHAR run_msg[]={msg_3_1,msg_3_2};
static PCHAR voc_msg[]={msg_4_1,msg_4_2,msg_4_3,msg_4_4,msg_4_5,
			            msg_4_6,msg_4_7};
static PCHAR rtf_msg[]={msg_6_1,msg_6_2,msg_6_3,msg_6_4,msg_6_5,
                        msg_6_6,msg_6_7,msg_6_8,msg_6_9,msg_6_10,
						msg_6_11,msg_6_12,msg_6_13,msg_6_14};
static PCHAR kernel_msg[]={msg_7_1,msg_7_2,msg_7_3,msg_7_4,msg_7_5,
                           msg_7_6,msg_7_7,msg_7_8,msg_7_9,msg_7_10,
						   msg_7_11};
static PCHAR edout_msg[]={msg_8_1,msg_8_2,msg_8_3,msg_8_4,msg_8_5};

#ifndef DEMO
static PCHAR copyr_msg[]={
"\n\n     \n"
  };
#endif

#ifdef DEMO
static PCHAR copyr_msg[]={
"\n\n"
  "       ����  ������   ����           �����     ����   ������    \n"
  "      ��       ��    ��             ��   ��   ��      ��   ��   \n"
  "      ��       ��    ��             ��   ��   ��      ������    \n"
  "      ��       ��    ��             ��   ��   ��      �� ��     \n"
  "       ����    ��     ����           �����     ����   ��  ��    \n\n"
  "                     D E M O   V E R S I O N                    \n\n\n"
  };
#endif

PCHAR * message_groups[]={format_msg,comp_msg,image_msg,run_msg,
			voc_msg,copyr_msg,rtf_msg,kernel_msg,edout_msg};

//---------------------- Errors processing ------------------
extern jmp_buf fatal_error_exit;
static WORD status_code = 0;
static CHAR mess[512],add_mess[256];
//	Fatal error break processing

static void msg_err (INT group, INT element)
{
    status_code = 1000 + group * 100 + element;
    Tiger_ReportError (status_code, get_message (status_code));
}

void error_exit (INT group, INT element)
{
 extern void FreeAllData(void);

    //MsgBox("msgerr");
    FreeAllData();
    add_mess[0]='\0';
    msg_err (group,element);                    /* show message */
    longjmp (fatal_error_exit, element);
    //MsgBox("longjump done");

}

void error_exit_str(INT group, INT element,PCHAR s)
{
 extern void FreeAllData(void);

    FreeAllData();
    strcpy(add_mess,s);
    msg_err (group,element); /* show message */
    longjmp (fatal_error_exit, element);
}

void error_exit_asm (INT element)
{
    error_exit (ERR_comp,element);
}

//	External manipulation with error status
PCHAR get_message (WORD code)
{
    PCHAR c=mess;
    if (code == 0) return "OK.";
    strcpy(mess,*(message_groups [(code - 1000)/100] + code%100 - 1));  /* ptr to message */
    strcat(mess,add_mess);
#ifdef __MAC__
// ��४���஢���� ��� Windows ���� � WINCV\DLL_MAIN.c
// � �ணࠬ�� ��� DOS � WINDOWS ᮡ�ࠥ��� �� ����� �������樨
        {
        extern char decode_ASCII_to_[];
        INT i;
        for(i=0;*(c+i);i++)
                *(c+i)=decode_ASCII_to_[(BYTE)(*(c+i))];
        }
#endif
    return c;
}

WORD get_error_status()
{
    return status_code;
}

void clear_error_status()
{
    status_code = 0; add_mess[0]='\0';
}

BOOL bool_status()
{
    return ((status_code) ? FALSE : TRUE);
}

void set_error_status (WORD group, WORD element)
{
    msg_err (group, element);
}
