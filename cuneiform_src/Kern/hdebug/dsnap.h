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

#ifndef _DSNAP_H_
#define _DSNAP_H_

// Snap
//Allex/////////////////////////
// ��������� ������ � ����� �������� ���
// � ����� �������� ���� �������� ������, ��������� �������������� ��� ���
//
// 1 ����� ���������
#define SNAP_ROOT_							"�������� ��������� ����..."
	#define SNAP_SELECT_DISABLE				"��������/O������� ����..."
	#define SNAP_SELECT_ENABLE				"��������/��������� ����..."
	#define SNAP_CPAGE_STORAGE				"��������� CPAGE"
//
// 2 ��������� ����
#define SNAP_ROOT_STUFF						"�����"
	#define SNAP_STUFF_BINARIZE				"��������� �����������..."
	#define	SNAP_STUFF_AUTOTEMPLATE			"�������������� ����������� ������� �������������."
	#define SNAP_STUFF_VER_LINES			"����������� �����..."
	#define SNAP_ROOT_LINES					"��������� � ������ �����..."
	#define SNAP_STUFF_LINES				"��������� � ������ �����..."
		#define SNAP_PASS1_LINES			"������ ������ �� ������"
		#define SNAP_PASS2_LINES			"������ ������ �� ������"
		#define SNAP_PASS3_LINES			"������ ������ �� ������"
		#define SNAP_STUFF_KILL_LINES			"�������� �����"
			#define SNAP_KILL_LINES_STEP		"������� �� �����"
			#define SNAP_KILL_LINES_DATA		"���� ��������� � ��� ��"
			#define SNAP_KILL_LINES_SHOW_BEFORE	"�������� ���������� �� ������ �����"
			#define SNAP_KILL_LINES_SHOW_AFTER	"�������� ���������� ����� ������ �����"
 		#define SNAP_STUFF_RSL "�������� ��� �������..."

//
// 3 ��������, ��������� ������
#define SNAP_ROOT_LAYOUT					"��������"
 #define SNAP_LAYOUT_SEGMENT				"������ ��������� ����������..."
 #define SNAP_LAYOUT_PICTURES				"��������� ��������..."
 #define SNAP_LAYOUT_NEG	                "����� � ������������� ���������"
 #define SNAP_LAYOUT_FON                    "����� ����� �������"
    #define SNAP_LAYOUT_LAYOUT				"��������� ����������..."
	#define SNAP_ROOT_TABLES				"��������� ������..."
	#define SNAP_LAYOUT_TABLES				"��������� ������..."
	#define SNAP_LAYOUT_POST_LINES			"��������� �����"
		#define SNAP_LAYOUT_SHOR_LINES		"�������� ������������ �����"
			#define SNAP_SHOR_LINES_STEP	"�� �����"
			#define SNAP_SHOR_LINES_DATA	"���� ���������"
	#define SNAP_ROOT_STRINGS				"��������� �����..."
	#define SNAP_LAYOUT_STRINGS				"��������� �����..."
//	#define SNAP_STUFF_RSL "�������� ��� ������� (III ������)"

//
// 4 �������������
#define SNAP_ROOT_RECOGNITION				"�������������"
	#define SNAP_RECG_RECOGNITION			"������������� �����..."
	#define SNAP_RECG_SPELL					"������� � �������������"
//
// 5 ��������������
#define SNAP_ROOT_CONVERTERS				"��������������"
	#define SNAP_FRMT_CONVERTERS			"�������������� � ���������������..."
	#define SNAP_KEGL_CORRECT				"��������� �����..."


//������� �������
#define SNAP_ROOT_MAIN_DEBUG                "������� �������"
//������� ������������
#define SNAP_ROOT_MAIN_TIME_CONTROL         "������� ������������"

#endif
