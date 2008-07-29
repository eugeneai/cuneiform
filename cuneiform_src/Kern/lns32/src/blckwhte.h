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

/* Black/White pixel-bit definition.
	Link with "bit_data.c"
 */
#ifndef __BLCKWHTE_H
# define __BLCKWHTE_H
	//= interface =================================//
	// please, comment one of the next...
	#define BLACK_IS_ZERO
	//#define WHITE_IS_ZERO

	//= implementation ============================//
	#ifndef __BIT_FUNC_H
   #	include "bit_func.h"
   #endif
	/*
	extern const word bit_word[16];
	extern const first_bit0_pos[256];
	extern const first_bit1_pos[256];
   */

	#ifdef BLACK_IS_ZERO

		#ifdef WHITE_IS_ZERO
		#	error Both WHITE_IS_ZERO and BLACK_IS_ZERO defined
		#endif

//		#define BLACK 0
//		#define WHITE 1
		#define BBYTE 0x00
		#define WBYTE 0xFF
      #define BWord16 0x0000
      #define WWord16 0xFFFF

      #define BLACK_Word16( ww )          ( ww == BWord16 )
      #define WHITE_Word16( ww )          ( ww == WWord16 )
		#define BLACK_BIT( ww, i )        ( (~ww) & lbit_word[i] )
		#define WHITE_BIT( ww, i )        ( ww & lbit_word[i]    )
		#define FIRST_WHITE_BIT( ww )                               \
			(                                                        \
				(left_byte(ww)) 	? 												\
					first_bit1_pos[ left_byte(ww) ]   						\
					: 8+first_bit1_pos[ right_byte(ww) ] 					\
			)
		#define FIRST_BLACK_BIT( ww )     									\
			(                                                        \
				(left_byte(ww)==WBYTE) ?                              \
					8+first_bit0_pos[ right_byte(ww) ] :  					\
					first_bit0_pos[ left_byte(ww) ]  						\
			)
		#define FIRST_BLACK_BIT_IN_BYTE( bb )								\
			(                                                        \
					first_bit0_pos[ bb ]  										\
			)

		#define MAKE_BIT_WHITE( ww_bb, num )                        \
			( ww_bb |= lbit_word[ num ] )
	#endif

	#ifdef WHITE_IS_ZERO
		#ifdef BLACK_IS_ZERO
		#	error Both WHITE_IS_ZERO and BLACK_IS_ZERO defined
		#endif
//		#define BLACK 1
//		#define WHITE 0
		#define BBYTE 0xFF
		#define WBYTE 0x00
      #define BWord16 0xFFFF
      #define WWord16 0x0000

      #define BLACK_Word16( ww )          ( ww == BWord16 )
      #define WHITE_Word16( ww )          ( ww == WWord16 )
		#define BLACK_BIT( ww, i )        ( ww & lbit_word[i]    )
		#define WHITE_BIT( ww, i )        ( (~ww) & lbit_word[i] )
		#define FIRST_WHITE_BIT( ww )     									\
			(                                                        \
				(left_byte(ww)==0xBBYTE) ?                            \
					8+first_bit0_pos( right_byte(ww) ) :  					\
					first_bit0_pos( left_byte(ww) )  						\
			)
		#define FIRST_BLACK_BIT( ww )
			(                                                        \
				(left_byte(ww)) 	? 												\
					first_bit1_pos( left_byte(ww) )   						\
					: 8+first_bit1_pos( right_byte(ww)  					\
			)
		#define FIRST_BLACK_BIT_IN_BYTE( bb )								\
			(                                                        \
					first_bit1_pos[ bb ]  										\
			)

		#define MAKE_BIT_WHITE( bb, num )                           \
			( bb &= lbit_word[ num ] )
	#endif

	#ifndef BLACK_IS_ZERO
	#	ifndef WHITE_IS_ZERO
	#		error Neither WHITE_IS_ZERO nor BLACK_IS_ZERO defined
	#	endif
	#endif


#endif
