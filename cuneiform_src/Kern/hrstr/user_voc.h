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

static BYTE *english_voc[]={
  "at"  ,          "on"  ,
  "pro" ,          "more",
  "an"  ,          "mr"  ,
  "many",          "him" ,
  "ran" ,          "any" ,
  "or"  ,          "open",
  "one" ,          "once",
  "be"  ,          "can" ,
  "of"  ,          "we"  ,
  "the" ,          "him" ,
  "are" ,          "it"  ,
  "dos" ,          "ocr" ,
  "ibm" ,          "group",
  "by"  ,          "is"  ,
  "in"  ,          "if"  ,
  "very",          "cdrom",
  "fax",           "cd",
  "rom",           "new",
  "old",           "svga",
  "vga",           "computer",
  "multimedia",    "hp",
  "ascii",         "soft",
  "copy",          "sorry",
  "as",            "system",
  "isn",           "samsung",
  "infoseek",      "rtf",
  "dbf",           "odbc",
  "api",           "sdk",
  "csv",           "xls",
  "html",          "pci",
  "pentium",       "ide",
  "vesa",          "cisco",
  "scsi",          "eisa",
  "cashe",
  "\0" // end of word list
};
static BYTE *russian_voc[]={
  "���",            "���",
  "��",             "⠪",
  "��",             "��",
  "��",             "��",
  "��",             "���",
  "���",            "�",
  "�",             "��",
  "�",              "�ᥩ",
  "��",             "����",
  "��",             "��",
  "��",            "�",
  "祣�",           "�",
  "ᥡ�",           "��",
  "����",         "����",
  "��",            "��",
  "�஥",           "��",
  "��",             "���",             
  "�����",          "���",
  "��",
  "\0" // end of word list
};
static BYTE *english_voc_all[]={
"for",
"ole",
"win",
"\0"
};
static BYTE *russian_voc_all[]={
"���",
"���",
"���",
"���",
"���",
"���",
"��",
"�",
"��",
"���",
"���",
"\0"
};

static BYTE *russian_voc_short[]={
"���",
"���",
"���",
"���",
"\0"
};
