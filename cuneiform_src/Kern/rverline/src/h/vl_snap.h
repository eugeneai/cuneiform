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

/**********  ���������  **********/
/*  Author     :  Alexander Mikhailov                                        */
/*  Last Edit  :  13.10.99                                                   */
/*  Source     :  'RLT_Snap.H'                                               */
/*  ���������� :  ��������� ��������������� �������.                         */
/*  ���������� :  ������������ �����������.                                  */
/*---------------------------------------------------------------------------*/
#include "cttypes.h"
/*------------own functions--------------------------------------------------*/
void RLTDraw_O_VerifLines (void *vLti, int Code1, int Code2, Handle myWindow);
void RLTDraw_VL_R_Zhertvy (void **vvZher, int nZher, Handle myWindow, int Code);
void RLTDraw_I_PrimBoxes (Rect16 *pRc, int *pNote, int nRc, Handle myWindow, int Code);
void RLTDrawTalk_I_PrimUkazy (void *vWhere, void *vStyle, Handle myWindow);
void RLTDraw_D_PrimLines (void *vB, Bool RealLine, Handle myWindow);
void RLTTalk_R_PrepSyri_AnalLine (void *vLinePool);
void RLTDraw_F_PrepSyri_AnalLine (void *vLinePool, Handle myWindow);
void RLTDraw_Negatives (void *vB, Int32 SkewReg);
void RLTDraw_RoughLayout (void *vB, Int32 SkewReg);
void RLTTalk_R_MakeDing_FromLine (void *vDingPool);
void RLTDraw_F_MakeDing_FromLine (void *vDingPool, Handle myWindow);
void RLTTalk_R_ReviDing (void *vDingPool);
void RLTDraw_F_ReviDing (void *vDingPool, Handle myWindow);
void RLTTalk_R_MakeCard (void *vCard);
void RLTDraw_F_MakeCard (void *vCard, void *vDingPool, Handle myWindow);
void RLTDraw_O_FoundTables (void *vTable, Handle myWindow);
void RLTDraw_O_FoundTexts (void *vTexts, Handle myWindow);
void RLTDraw_O_FoundForms (void *vForms, Handle myWindow);
void RLTDraw_O_TableLines (void *vLti, Handle myWindow);
void MyErrorNoMem (char* str);
void MyErrorNoComment (char* str);
void DrawLineOfSviazka (void *vTable, int kL, Bool HoriLine, Bool OldLine, Handle myMainWindow);
void CleanDrawingLineOfSviazka (Handle myMainWindow);
/*---------------------------------------------------------------------------*/
