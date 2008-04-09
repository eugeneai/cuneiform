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

#ifndef __LEO_FUNC_H__

#define __LEO_FUNC_H__
// functions from module leo.c
void    leo_kill(RecVersions *v,Word8 *kill_list);
void    leo_reduce_typefaces(RecVersions *v);
void    leo_clear( RecVersions *v);
int     leo_sort_vers_prob(RecVersions *v);
int     leo_sort_vers_info(RecVersions *v);
void    leo_compress( RecVersions *v);
void    leo_decode_to_ansi( RecVersions *v);
void    leo_decode_to_acsii( RecVersions *v);
void    LeoAddPVers(int Probs[],RecVersions *v);
void    leoProbsToVer_expert(int Probs[],RecVersions *v,RecVersions *mod);
void    LeoProbsToVer(int Probs[],RecVersions *v);
Bool32  leo_add_vers(RecVersions *dst, RecVersions *src);
int     leo_exist_code(RecVersions *ver, Word8 code);
void    leo_set_max_vers(RecVersions *v,int p);
int     leo_comp_codes(Word8 c1, Word8 c2);
Word8 * leo_strchr_codes(Word8 *c1, Word8 c2);
Word8 * leo_strchr_codes_ansi(Word8 *c1, Word8 c2);
void    leo_over( RecVersions *ver, RecVersions *alph);
int     leo_exist_codes(RecVersions *ver, Word8 *codes);
void    add_to_prob_array(Word8 prob[],RecVersions *v);
void    VersToAlph(RecVersions *ver,Word8 alphabet0[]);
void    leo_expert_prob( RecVersions *v,Word16 *v3x5, RecRaster *r ,
                         Word8 prob_3x5[], Word8 prob_iva[], Int32 prn, 
                         Bool32 bonus, Bool32 enable5x3);

/// functions from module leo_stick
int     leo_get_global_incline(void);
void    leo_set_simple_sticks_group(RecVersions *v,unsigned char al[],Int32 nose);
Bool32  leo_small_object(RecObject *object,int wlim, int hlim);
Int32   leo_wide_object(RecObject *object);
Bool32  leo_big_object(RecObject *object,int wlim, int hlim);
Bool32  leoRecogSimpleStick( RecObject*  object );
void    leo_add_inc(RecObject*  object);
void    leo_clear_stat(void);
Int32   leo_stick_horiz_hist(int h);
Bool32  leo_is_stick(RecObject*  object);
void    leo_setup_inc(RecObject*  object);
void    leo_erect(RecObject* object,int inc);
void    leo_set_sticks_group(   RecVersions *v, Int32 ret,
                                unsigned char alph[], Int32 simple_st, Int32 nose_1);
Int32   leo_recog_stick(Word16 *lpool, int w, int h);
void    leo_diskrim_stick(RecVersions *ver);
Int32   leo_int_sqrt (Word32 n);

/// functions from module leo_cont
void    leo_close_cont(void);
Bool32  leo_cont_new_page(Int32 id_page);
Int16   leo_cont_store(RecRaster *r,Word8 let, Word8 nLns,Rect16 *rect, Word8 IsPrn,
		Word8 Prob, Word8 Valid, RecVersions *ver,Word8 control);
Bool32  leo_cont_restore(RecRaster *r, Int32 id_page, Int16 id_rast, Word8 *nLns,Rect16 *rect, Word8 *IsPrn,Word8 *datao);
void    leo_close_cont_temp(void);
int     leo_open_cont_temp(void);
Bool32  leo_cont_set_valid(Int32 id_page, Int16 id_rast,Word8 code, Word8 valid,Word8 control);
Bool32  leo_cont_del_final(Int32 id_page, Int16 id_rast);
Bool32  leo_cont_store_collection(RecVersions *ver);

/// functions from module leo_prn
Bool32  leoRecogPrintChar( RecObject*  object );
Bool32 leoRecogCharPRN_expert(RecRaster*  recRaster, RecVersions* over);


// functions from module LEO_DLL.C
void    leo_snapChar(RecVersions *ver, char *tit, int enable);
void    leo_snapChar3x5(RecVersions *ver, char *tit, int enable);
void    leo_snapRes2Str(RecVersions *ver, char *buf);
Bool32  leoSnpInRect( Rect16* pRect, Int32 nSkew );

void    leo_cuneiform(RecObject *rec);
void    leo_SnpLog(char *tmp);
void    leo_snapRaster(RecObject* object, SnpTreeNode *stnRecog);
void    leo_snapSimpleKey(char *str, SnpTreeNode *stnRecog);
Bool32  leo_init_prn(void);

// function from module LEO_SIZE.C
Word8 leo_proport_penalty(Word8 let,Word8 prob, Int32 w, Int32 h);
Word8 leo_sizes_penalty( Int32 w, Int32 h);
void  leo_sizes_init_stat(void);
#endif