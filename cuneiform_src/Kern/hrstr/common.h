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

#define OLEG_DIS 1   //���������������� �������� � Leo

//FIELD_INFO - ���� ������ �� �������� ����. ������������ � Rcm.cpp.
//��� ������������� � ������ ������ ������ ���� ��������� ���
//           extern "C" FIELD_INFO FieldInfo;

typedef Word8 ALPHA_TABLE[256];

typedef struct tagFIELD_INFO
{
  Bool LINret;          //����: ������� ����� ���������� LINDefineLines
  Bool HandRec;         //���������� �������������
  Word32 Style;
#define FIS_DONT_GLUE      1  //�� ������
#define FIS_DONT_CUT       2  //�� ������
#define FIS_PRINTED        4  //�������� ����
#define FIS_NDX            8  //��������� ����
#define FIS_OBLIGATORY    16  //���� �� ����� ���� ������
#define FIS_DIGIT         32  //�������� �������
#define FIS_PASPORT       64  //���� "�������"
#define FIS_PUNCT        128  //����������� ����������
#define FIS_MATRIX       256  //��������� (DOS) �������
#define FIS_DIRTY        512  //������� ����
#define FIS_FUSE        1024  //����������� ����
#define FIS_MIX         2048  //����� ���� �������� �� ���� ��� ����������
#define FIS_SPACED      4096  //������� ��������� ���������
  ALPHA_TABLE  AlphaTable;    //�������
  Int32 LetWidth;             //������ ��� ������ �����
  Int32 MinLetWidth;
  Int32 MaxLetWidth;
  Int32 BigLetHeight;         //������ ��� ������ ������� �����
  Int32 SmallLetHeight;       // �� �� ��� ���������
  Int32 MaxWidthHeight;        //������������ ��������� 64*w/h

//�� FrhFieldSetup
  Rect16   compRect;         // calculated rect in ideal coords
  Int32    nMinLetWidth;
  Int32    nMaxLetWidth;
  Int32    nMinLetHeight; // letters excluding '-','.',...
  Int32    nMaxLetHeight;
  Int32    nMinChars;     // minimum count of chars (including dots, ...)
  Int32    nMaxChars;     // maximum count of chars, 0 - not restricted;
  Int32    xFlags;
} FIELD_INFO;

#define not_glue        (FieldInfo.Style & FIS_DONT_GLUE)
#define not_cut         (FieldInfo.Style & FIS_DONT_CUT)
#define printField      (FieldInfo.Style & FIS_PRINTED)
#define bIndexField     (FieldInfo.Style & FIS_NDX)
#define not_empty_field (FieldInfo.Style & FIS_OBLIGATORY)

#define digitField    (FieldInfo.Style & FIS_DIGIT)
#define pasportField  (FieldInfo.Style & FIS_PASPORT)
#define PunctPresence (FieldInfo.Style & FIS_PUNCT)
#define smatrix        (FieldInfo.Style & FIS_MATRIX)
#define dirty_field   (FieldInfo.Style & FIS_DIRTY)
#define fuse_field    (FieldInfo.Style & FIS_FUSE)

#define HandRecog   (FieldInfo.HandRec)
#define Presence(x) (FieldInfo.AlphaTable[x])
#define linOK       (FieldInfo.LINret)
