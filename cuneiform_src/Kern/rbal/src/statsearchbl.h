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

// StatSearchBL.h : header file
//
#ifndef __STAT_SEARCH_BL_H__

#include "cttypes.h"
#include "nt_types.h"
#include "cstr.h"

#ifdef __cplusplus
	extern "C" {
#endif

///////
typedef struct tagROW_STRUCT
{
	Int16 globMax;		//���������� ��������
	Int16 ValGM;		//�������� ����������� ���������
	Int16 AltGM;		//�������� ������������ (1-� ��� 2-� ��)

	Int16 rightLocMax;
	Int16 ValRLM;
	Int16 AltRLM;
	Float32 rightCoeff;

	Int16 leftLocMax;
	Int16 ValLLM;
	Int16 AltLLM;
	Float32 leftCoeff;

}	ROW_STRUCT;

//////
Int16 stat_Mode_diff_b2_b3(Int32 line_number, Int16 diff, Int16 fl_b2_or_b1);
Int16 stat_Mode_diff_b2_b1(Int32 line_number, Int16 diff_b3_b2);
Int16 stat_Mode_diff_b3_b4(Int32 line_number, Int16 diff_b3_b2);
//////

//////
Int16 stat_Hypothesis(Int32 line_number, Int16 diff_b3_bsl);
//////

//////
Int16 stat_Right_diff_from_max(Int16 *p_FreqArr, Int16 max_FreqArr);
Int16  stat_Left_diff_from_max(Int16 *p_FreqArr, Int16 max_FreqArr);
//////

//////
void stat_def_b3_b4(CSTR_line line, CSTR_attr *p_attr, Int16 *pY2Arr, 
			   Int16 *pFreqY2Arr, Int16 *Ns3, Int16 *Ns4);
void stat_def_b1_b2(CSTR_line line, CSTR_attr *p_attr, Int16 *pY1Arr, 
			   Int16 *pY2Arr, Int16 *pFreqY1Arr, Int16 *Ns1, Int16 *Ns2);
void stat_def_imaginary_bl(CSTR_attr *p_attr, Int16 *Ns1, Int16 *Ns2, Int16 *Ns4);
//////

//////
BOOL               stat_interp_bsl(CSTR_line line, CSTR_attr *p_attr, ROW_STRUCT *row_str);
BOOL stat_interp_bsl_by_solid_recog(CSTR_line line, Int16 ln_row, Int16 b3, 
																	   ROW_STRUCT *row_str);
BOOL		  stat_interp_bsl_by_b4(CSTR_line line, Int16 ln_row, Int16 b3, Int16 b4, 
																	   ROW_STRUCT *row_str);
BOOL       stat_interp_bsl_by_boxes(CSTR_line line, Int16 ln_row, Int16 b3, Int16 b4,
																	   ROW_STRUCT *row_str);
//////

//////
BOOL	  stat_control_t_level(CSTR_line line, Int16 ln_row, Int16 b3, Int16 b4);
Int16 stat_control_b3_by_recog(CSTR_line line, Int16 ln_row, ROW_STRUCT *row_str);
BOOL  stat_control_semilevel(CSTR_line line, Int16 ln_row, Int16 b4);
//////

//////
void stat_FormArrays(CSTR_line line, Int16 row, Int16 *pY1Arr, Int16 *pY2Arr);
BOOL stat_FormCSTR_attrArray(Int32 line_start, Int32 line_stop, CSTR_attr *pCSTR_attrArr);
Int16 stat_LineLength(CSTR_line line);
//////

//////
void StatSearchBL(CSTR_line line, CSTR_attr *p_attr,
				  Int16 *Ns1, Int16 *Ns2, Int16 *Ns3, Int16 *Ns4);
//////

#ifdef __cplusplus
	}
#endif

#define	 __STAT_SEARCH_BL_H__
#endif              /* Ends #ifndef __STAT_SEARCH_BL_H__  */



