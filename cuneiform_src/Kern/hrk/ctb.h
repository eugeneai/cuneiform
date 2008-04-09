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

#ifndef __CTB_H
   #define __CTB_H

   #include "globus.h"
   #include "ctbdefs.h"
   #include "recdefs.h"
   #include "memfunc.h"

   #include <string.h>
/*   #include <io.h> */
   #include <stdlib.h>

   #ifdef __CTB__
      #define CTB_FUNC  FUN_EXPO
   #else
      #define CTB_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

CTB_FUNC(Int32)   CTB_GetVersion(void );
//***************** open/close function prototypes **********************
CTB_FUNC(Bool32) CTB_create(char *file_name,Word8 *data);
CTB_FUNC(Bool32) CTB_create_gray(char *file_name,Word8 *data);
CTB_FUNC(void)   CTB_done(void );
CTB_FUNC(Bool32) CTB_open(char *file_name,CTB_handle *hnd,char *attr);
CTB_FUNC(void)   CTB_close(CTB_handle *hnd);

//***************** read function prototypes ****************************
CTB_FUNC(Int32)  CTB_volume(CTB_handle *hnd );
CTB_FUNC(Int32)  CTB_volume_all(char *file_name );
CTB_FUNC(Int32)  CTB_read(CTB_handle *hnd, Int32 num , Word8 *ima, Word8 *data );
CTB_FUNC(Bool32) CTB_read_global_data(CTB_handle *hnd,Word8 *data);
CTB_FUNC(Bool32) CTB_read_data(CTB_handle *hnd,Int32 num,Word8 *data);

//***************** write function prototypes ***************************
CTB_FUNC(Bool32) CTB_write( CTB_handle *hnd, Int32 num,Word8 *ima,  Word8 *data);
CTB_FUNC(Bool32) CTB_write_mark( CTB_handle *hnd, Int32 num,Word8 *ima,  Word8 *data, Bool32 mark);
CTB_FUNC(Bool32) CTB_insert( CTB_handle *hnd,Int32 num,Word8 *ima,  Word8 *data);
CTB_FUNC(Bool32) CTB_delete( CTB_handle *hnd,Int32 num);
CTB_FUNC(Bool32) CTB_kill(CTB_handle *hnd,Int32 num);
CTB_FUNC(Bool32) CTB_mark(CTB_handle *hnd, Int32 num);
CTB_FUNC(Bool32) CTB_write_data(CTB_handle *hnd,Int32 num, Word8 *data);
CTB_FUNC(Bool32) CTB_write_global_data(CTB_handle *hnd,Word8 *data);
CTB_FUNC(Bool32) CTB_swap(CTB_handle *hnd,Int32 num1,Int32 num2);

//***************** file/memory convertion functions protoypes ************
CTB_FUNC(Int32)  CTB_compress(char *file_name);
CTB_FUNC(Int32)  CTB_copy(char *newn, char *oldn);
CTB_FUNC(Int32)  CTB_move(char *newn, char *oldn);
CTB_FUNC(Int32)  CTB_rename(char *newn, char *oldn);
CTB_FUNC(void)   CTB_unlink(char *newn);
CTB_FUNC(void)   CTB_align8_lines(Word8 *bin,Int32 w, Int32 h);
CTB_FUNC(void)   CTB_align1_lines(Word8 *bin,Int32 w, Int32 h);
CTB_FUNC(void)   CTB_align8_124lines(Word8 *bin,Int32 w, Int32 h, 
                    Int32 alin,Word8 init_byte);
CTB_FUNC(void)   CTB_align41(Word8 *sbin,Int32 w, Int32 h);
//*************** Gray images    ********* *********************************
CTB_FUNC(Word8)  CTB_BestLevelInGray(Word8 *image,int wx,int wy);
CTB_FUNC(Bool32) CTB_GrayBound(RecRasterEx *PaintRaster,int GLevel);
//*************** access to LEMAN protocol *********************************
CTB_FUNC(Bool32) CTB_prot_open(char *name);
CTB_FUNC(Bool32) CTB_prot_read(unsigned char *PROT_raster,
				  int *PROT_w, int *PROT_h,
				  unsigned char *PROT_let,unsigned char *PROT_data);
CTB_FUNC(void)   CTB_prot_close(void);
CTB_FUNC(Bool32) CTB_prot_write(char *file_name,
                  unsigned char *raster,
				  int Width, int Height,
				  unsigned char  code,int align,
                  unsigned char *PROT_data  );
CTB_FUNC(Bool32) CTB_prot_gray_read(unsigned char *PROT_raster,
            unsigned char *PROT_data);
CTB_FUNC(Bool32) CTB_prot_gray_write(char *file_name,
        unsigned char *PROT_raster,unsigned char let, int w, int h,
        int align);
//**************** CT FormReader data I/O **********************************
CTB_FUNC(Int32) CTB_AddRecRaster(char *fname, RecRaster *r,Word8 let);
CTB_FUNC(Int32) CTB_AddRecRaster_data(char *fname, RecRaster *r,Word8 *data);
CTB_FUNC(Bool32) CTB_ReadRecRaster(CTB_handle *hnd, Int32 num ,
        Word8 *let,RecRaster *r, Word8 *data );
CTB_FUNC(Bool32) CTB_GetRecRaster(char *fname, Int32 id_rast ,
        RecRaster *r);

//***************** error message *****************************
CTB_FUNC(Int32)  CTB_get_error(void);
CTB_FUNC(char *) CTB_get_error_name(char *str);

#define CTB_ERR_NONE			0
#define CTB_ERR_OPEN_CTB		1
#define CTB_ERR_SEEK            2
#define CTB_ERR_SIGN            3
#define CTB_ERR_HEAD            4
#define CTB_ERR_VERS            5
#define CTB_ERR_MEM             6
#define CTB_ERR_OPEN_NDX        7
#define CTB_ERR_READ            8
#define CTB_ERR_NDX             9
#define CTB_ERR_NOT_OPEN        10
#define CTB_ERR_ZERO_DATA       11
#define CTB_ERR_KILLED          12
#define CTB_ERR_UNKNOWN_PACK    13
#define CTB_ERR_WRITE           14
#define CTB_ERR_ALIGN           15
#define CTB_ERR_DIF_VERSION     16

   #ifdef __cplusplus
            }
   #endif

#endif

