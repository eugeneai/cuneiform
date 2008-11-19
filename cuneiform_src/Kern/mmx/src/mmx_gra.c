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

#include"mmx.h"

MMX_FUNC(void) MMX_addshab_cykl(int * src, int cg, signed char * dst, int num)
{
#ifdef _MSC_VER
_asm    {
		mov         edx,        cg
		movd        mm6,        edx
		mov         eax,        src
		psllq       mm6,        32
		movd        mm7,        edx
		mov         ecx,        dst
		paddd       mm7,        mm6         ;;  mm7=((Int32)cg,(Int32)cg)
        mov         edx,        num
		pxor        mm6,        mm6
        mov         ebx,        edx
		movq        mm0,        [ecx]
        shr         edx,        3
        and         ebx,        7
        }


label0:; // process 8 elems
_asm{
        movq        mm1,        mm0
		pcmpgtb     mm6,    	mm0         ;;  signums
		punpckHbw   mm1,    	mm6         ;;	a7,a6,a5,a4
		punpckLbw   mm0,    	mm6         ;;	a3,a2,a1,a0
		movq	    mm3,    	mm1
		movq	    mm2,    	mm0
		punpckHwd   mm0,    	mm6         ;;	a3,a2
		punpckLwd   mm2,    	mm6         ;;	a1,a0
		movq	    mm4,    	[eax]
		pmaddwd	    mm2,    	mm7         ;;  (a1,a0)*cg
		movq	    mm5,    	[eax+8]
		pmaddwd	    mm0,    	mm7	        ;;  (a3,a2)*cg
		punpckHwd   mm1,    	mm6	        ;;	a7,a6
		punpckLwd   mm3,    	mm6	        ;;	a5,a4
		paddd	    mm4,    	mm2         ;;  (g1,g0)+=(a1,a0)*cg
		paddd	    mm5,    	mm0         ;;  (g3,g2)+=(a3,a2)*cg
		movq	    [eax],		mm4
		movq	    [eax+8],	mm5
		movq	    mm4,	    [eax+16]
		pmaddwd	    mm3,    	mm7         ;;  (a5,a4)*cg
		movq	    mm5,	    [eax+24]
		pmaddwd	    mm1,	    mm7         ;;  (a7,a6)*cg
		add		    ecx,	    8
		add		    eax,	    32
        dec         edx
		paddd	    mm4,	    mm3         ;;  (g5,g4)+=(a5,a4)*cg
		paddd	    mm5,	    mm1         ;;  (g7,g6)+=(a7,a6)*cg
        pxor        mm6,        mm6         ;;  mm6 = 0
        movq	    [eax-16],	mm4
        movq	    [eax-8],	mm5
        movq	    mm0,	    [ecx]
        jnz         label0
}

_asm{
    EMMS
    }
return;
#endif
}

MMX_FUNC(void) MMX_addshab(int * src, int cg, signed char * dst)
{
#ifdef _MSC_VER
_asm    {
		mov		edx,	cg
		movd	mm6,	edx
		mov     eax,    src
		psllq	mm6,	32
		movd	mm7,	edx
		mov     ecx,    dst
		paddd	mm7,	mm6   // mm7=((Int32)cg,(Int32)cg)
		pxor	mm6,	mm6
        }


// 4*0
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*1
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*2
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*3
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}

// 4*4
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*5
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*6
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*7
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}

// 4*8
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*9
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*10
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
    add   ecx,  8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}
// 4*11
_asm{
		movq	mm0,	[ecx]
		movq	mm1,	mm0
		pcmpgtb	mm6,	mm0
		punpckHbw	mm1,	mm6			;;	a7,a6,a5,a4
		punpckLbw	mm0,	mm6			;;	a3,a2,a1,a0
		movq	mm3,	mm1
		movq	mm2,	mm0
		punpckHwd	mm0,	mm6			;;	a3,a2
		punpckLwd	mm2,	mm6			;;	a1,a0
		movq	mm4,	[eax]
		pmaddwd	mm2,	mm7				;;  (a1,a0)*cg
		movq	mm5,	[eax+8]
		pmaddwd	mm0,	mm7				;;  (a3,a2)*cg
		punpckHwd	mm1,	mm6			;;	a7,a6
		punpckLwd	mm3,	mm6			;;	a5,a4
		paddd	mm4,	mm2				;;  (g1,g0)+=(a1,a0)*cg
		paddd	mm5,	mm0				;;  (g3,g2)+=(a3,a2)*cg
		movq	[eax],		mm4
		movq	[eax+8],	mm5
		movq	mm4,	[eax+16]
		pmaddwd	mm3,	mm7			;;  (a5,a4)*cg
		movq	mm5,	[eax+24]
		pmaddwd	mm1,	mm7			;;  (a7,a6)*cg
		mov		edx,	eax
		add		ecx,	8
		add		eax,	32
		paddd	mm4,	mm3			;;  (g5,g4)+=(a5,a4)*cg
		paddd	mm5,	mm1			;;  (g7,g6)+=(a7,a6)*cg
    pxor  mm6,  mm6
		movq	[edx+16],	mm4
		movq	[edx+24],	mm5
}

// last portion 48 = 4*12
_asm{
    movq	mm0,	[ecx]
    movq	mm1,	mm0
    pcmpgtb     MM6,	MM0
    punpckHbw	mm1,	mm6
    punpckLbw	mm0,	mm6
    movq	mm3,	mm1
    movq	mm2,	mm0
    punpckHwd	mm0,	mm6
    punpckLwd	mm2,	mm6
    movq	mm4,	[eax]
    pmaddwd	mm2,	mm7
    movq	mm5,	[eax+8]
    pmaddwd	mm0,	mm7
    punpckHwd	mm1,	mm6
    punpckLwd	mm3,	mm6
    paddd	mm4,	mm2
    paddd	mm5,	mm0
    movq	[eax],		mm4
    movq	[eax+8],	mm5

    EMMS
    }
#endif
}
