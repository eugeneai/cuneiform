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

#include"MMX.h"

//       Word32   MMX_scalarUni (Int16 * _EAX, Int16 * _EDX, Int32 num)
//		return  0 if num<=0
MMX_FUNC(Word32)   MMX_scalarUni (Int16 * _EAX, Int16 * _EDX, Int32 num)
{
_asm{
	mov eax, _EAX
	mov edx, _EDX
	mov ecx, num
	
	PXOR	MM0,	MM0
	cmp		ecx,	0
	jle		save_res
	mov	ebx,	ecx
	and	ebx,	3
	je	zero_skip
	sub	ebx,	4
	neg	ebx
	shl	ebx,	4
zero_skip:
	sub	ecx,	4
	MOVD	MM3,	EBX
	jl	end_loop
_loop:
	MOVQ    MM2,    [EAX] ;; mm0 = (a4, a3, a2, a1)           4 words
	MOVQ    MM1,    [EDX] ;; mm1 = (b4, b3, b2, b1)           4 words
	sub	ecx,	4
	add	eax,	8
	add	ebx,	8	
	PMADDWD MM2,    MM1       ;; mm0 = (a4*b4+a3*b3, a2*b2+a1*b1) 2 dwords
	cmp	ecx,	0
	PADDD	MM0,	MM2
	jg	_loop

	jl	save_res
end_loop:	
	MOVQ    MM2,    [EAX] ;; mm0 = (a4, a3, a2, a1)           4 words
	MOVQ    MM1,    [EDX] ;; mm1 = (b4, b3, b2, b1)           4 words
	PSLLQ	MM2,	MM3
	PSLLQ	MM1,	MM3
	PMADDWD MM2,    MM1       ;; mm0 = (a4*b4+a3*b3, a2*b2+a1*b1) 2 dwords
	PADDD	MM0,	MM2
	
save_res:	
	MOVQ    MM2,    MM0       ;; mm2 = ( s1, s2 )
	PSRLQ   MM2,    32        ;; mm2 = ( 0,  s1 )
	PADDD   MM0,    MM2       ;; mm0 = ( s1, s1+s2) = (..., sum )
	MOVD   EAX,    MM0  	  ;; eax = sum

	EMMS
    }
}

//
//       Word32   MMX_scalar16 (Int16 * _EAX, Int16 * _EDX)
//
MMX_FUNC(Word32) MMX_scalar16 (Int16 * _EAX, Int16 * _EDX)
{
_asm{
	mov eax, _EAX
	mov edx, _EDX

	MOVQ    MM0,    [EAX]     ;; mm0 = (a4, a3, a2, a1)           4 words
	MOVQ    MM1,    [EDX]     ;; mm1 = (b4, b3, b2, b1)           4 words

	MOVQ    MM2,    [EAX+8]   ;; mm2 = (a8, a7, a6, a5)           4 words
	PMADDWD MM0,    MM1       ;; mm0 = (a4*b4+a3*b3, a2*b2+a1*b1) 2 dwords
	MOVQ    MM3,    [EDX+8]   ;; mm3 = (b8, b7, b6, b5)           4 words

	MOVQ    MM4,    [EAX+16]  ;; mm4 = (a12, a11, a10, a9)        4 words
	PMADDWD MM2,    MM3       ;; mm2 = (a8*b8+a7*b7, a6*b6+a5*b5) 2 dwords
	MOVQ    MM5,    [EDX+16]  ;; mm5 = (b12, b11, b10, b9)        4 words

	MOVQ    MM6,    [EAX+24]  ;; mm6 = (a16, a15, a14, a13)       4 words
	PMADDWD MM4,    MM5       ;; mm4 = (a12*b12+a11*b11, a10*b10+a9*b9) 2 dwords
	MOVQ    MM7,    [EDX+24]  ;; mm7 = (b16, b15, b14, b13)       4 words
	PADDD   MM0,    MM2
	PADDD   MM0,    MM4
	PMADDWD MM6,    MM7       ;; mm6 = (a15*b15+a16*b16, a13*b13+a14*b14) 2 dwords
	PADDD   MM0,    MM6       ;; mm0 = ( s1, s2 )                 2 dwords

	MOVQ    MM2,    MM0       ;; mm2 = ( s1, s2 )
	PSRLQ   MM2,    32        ;; mm2 = ( 0,  s1 )
	PADDD   MM0,    MM2       ;; mm0 = ( s1, s1+s2) = (..., sum )
	MOVD   EAX,    MM0  	  ;; eax = sum

	EMMS
    }
}

//
//     Word32   MMX_scalar36 (Int16 * _EAX, Int16 * _EDX)
//
MMX_FUNC(Word32) MMX_scalar36 (Int16 * _EAX, Int16 * _EDX)
{
_asm{
	mov eax, _EAX
	mov edx, _EDX
	; 1 - 16
	MOVQ    MM0,    [EAX]     ;; mm0 = (a4, a3, a2, a1)           4 words
	MOVQ    MM1,    [EDX]     ;; mm1 = (b4, b3, b2, b1)           4 words

	MOVQ    MM2,    [EAX+8]   ;; mm2 = (a8, a7, a6, a5)           4 words
	PMADDWD MM0,    MM1       ;; mm0 = (a4*b4+a3*b3, a2*b2+a1*b1) 2 dwords
	MOVQ    MM3,    [EDX+8]   ;; mm3 = (b8, b7, b6, b5)           4 words

	MOVQ    MM4,    [EAX+16]  ;; mm4 = (a12, a11, a10, a9)        4 words
	PMADDWD MM2,    MM3       ;; mm2 = (a8*b8+a7*b7, a6*b6+a5*b5) 2 dwords
	MOVQ    MM5,    [EDX+16]  ;; mm5 = (b12, b11, b10, b9)        4 words

	MOVQ    MM6,    [EAX+24]  ;; mm6 = (a16, a15, a14, a13)       4 words
	PMADDWD MM4,    MM5       ;; mm4 = (a12*b12+a11*b11, a10*b10+a9*b9) 2 dwords
	MOVQ    MM7,    [EDX+24]  ;; mm7 = (b16, b15, b14, b13)       4 words
	PADDD   MM0,    MM2
	PADDD   MM0,    MM4
	PMADDWD MM6,    MM7       ;; mm6 = (a15*b15+a16*b16, a13*b13+a14*b14) 2 dwords
	PADDD   MM0,    MM6       ;; mm0 = ( s1, s2 )                 2 dwords
	; 17 - 32
	MOVQ    MM6,    [EAX+32]  ;; mm6 = (a20, a19, a18, a17)       4 words
	MOVQ    MM7,    [EDX+32]  ;; mm7 = (b20, b19, b18, b17)       4 words

	MOVQ    MM2,    [EAX+40]  ;; mm2 = (a24, a23, a22, a21)       4 words
	PMADDWD MM6,    MM7       ;; mm6 = (a20*b20+a19*b19, a18*b18+a17*b17)
	MOVQ    MM3,    [EDX+40]  ;; mm3 = (b24, b23, b22, b21)       4 words

	MOVQ    MM4,    [EAX+48]  ;; mm4 = (a28, a27, a26, a25)        4 words
	PADDD   MM0,    MM6
	PMADDWD MM2,    MM3       ;; mm2 = (a24*b24+a23*b23, a22*b22+a21*b21)
	MOVQ    MM5,    [EDX+48]  ;; mm5 = (b28, b27, b26, b25)        4 words

	MOVQ    MM6,    [EAX+56]  ;; mm6 = (a32, a31, a30, a29)       4 words
	PMADDWD MM4,    MM5       ;; mm4 = (a28*b28+a27*b27, a26*b26+a25*b25)
	MOVQ    MM7,    [EDX+56]  ;; mm7 = (b32, b31, b30, b29)       4 words
	PADDD   MM0,    MM2
	PADDD   MM0,    MM4
	PMADDWD MM6,    MM7       ;; mm6 = (a32*b32+a31*b31, a30*b30+a29*b29) 2 dwords
	PADDD   MM0,    MM6       ;; mm0
        ; 32-36
	MOVQ    MM2,    [EAX+64]  ;; mm2 = (a36, a35, a34, a33)       4 words
	MOVQ    MM3,    [EDX+64]  ;; mm3 = (b36, b35, b34, b33)       4 words

	PMADDWD MM2,    MM3       ;; mm2 = (a36*b36+a35*b35, a34*b34+a33*b33)
	PADDD   MM0,    MM2

	MOVQ    MM2,    MM0       ;; mm2 = ( s1, s2 )
	PSRLQ   MM2,    32        ;; mm2 = ( 0,  s1 )
	PADDD   MM0,    MM2       ;; mm0 = ( s1, s1+s2) = (..., sum )
	MOVD   EAX,    MM0  	  ;; eax = sum

	EMMS
    }
}


