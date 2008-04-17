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

extern   Word32 bit_cnt[];

//
//       DWORD   MMX_anding (int32 * images, int32 * etalon, int32 limit)
//
MMX_FUNC(Bool32) MMX_anding(Int32 *image,Word16 *etalons,Int32 L)
{
#ifdef WIN32
_asm    {
        
        mov     edx,    etalons
		xor     eax,    eax			; accounter of bits
		
;CYKL 0
        movq    mm0,    [edx]       ;   mm0 = etalon

        movq    mm1,    mm0     
;IF     ARG EQ 0 
        pand    mm0,    mm2
        pandn   mm1,    mm3  
;ENDIF

;IF     ARG EQ 1
;        pand    mm0,    mm4
;        pandn   mm1,    mm5  
;ENDIF		 

;IF     ARG EQ 2
;        pand    mm0,    mm6
;        pandn   mm1,    mm7  
;ENDIF

;IF     ARG EQ 3
;		mov     edx,    image
;        pand    mm0,    [edx+24]
;        pandn   mm1,    [edx+8*4+24]
;ENDIF
;   mm0 = tmp & (image   = iobraz)
;   mm1 =~tmp & (image+8 = iobraz2)
;IF     ARG EQ 0 
		sub		eax,	L
;ENDIF        
        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    0-15
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    0-15
		jge			retur

        psrlq   mm0,    32
		add     eax,    dword ptr bit_cnt[edi*4]  ;    16-31
        psrlq   mm1,    32
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    16-31
		jge			retur

        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    32-47
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    32-47
		jge			retur

		add     eax,    dword ptr bit_cnt[edi*4]  ;    48-63
		add     edx,    8
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    48-63
;IF     ARG NE 3
		jge			retur
;ENDIF

;        CYKL 1
        movq    mm0,    [edx]       ;   mm0 = etalon

        movq    mm1,    mm0     
;IF     ARG EQ 0 
;        pand    mm0,    mm2
;        pandn   mm1,    mm3  
;ENDIF

;IF     ARG EQ 1
        pand    mm0,    mm4
        pandn   mm1,    mm5  
;ENDIF		 

;IF     ARG EQ 2
;        pand    mm0,    mm6
;        pandn   mm1,    mm7  
;ENDIF

;IF     ARG EQ 3
;		mov     edx,    image
;        pand    mm0,    [edx+24]
;        pandn   mm1,    [edx+8*4+24]
;ENDIF
;   mm0 = tmp & (image   = iobraz)
;   mm1 =~tmp & (image+8 = iobraz2)
;IF     ARG EQ 0 
;		sub		eax,	L
;ENDIF        
        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    0-15
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    0-15
		jge			retur

        psrlq   mm0,    32
		add     eax,    dword ptr bit_cnt[edi*4]  ;    16-31
        psrlq   mm1,    32
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    16-31
		jge			retur

        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    32-47
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    32-47
		jge			retur

		add     eax,    dword ptr bit_cnt[edi*4]  ;    48-63
		add     edx,    8
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    48-63
;IF     ARG NE 3
		jge			retur
;ENDIF        
 
;       CYKL 2
        movq    mm0,    [edx]       ;   mm0 = etalon

        movq    mm1,    mm0     
;IF     ARG EQ 0 
;        pand    mm0,    mm2
;        pandn   mm1,    mm3  
;ENDIF

;IF     ARG EQ 1
;        pand    mm0,    mm4
;        pandn   mm1,    mm5  
;ENDIF		 

;IF     ARG EQ 2
        pand    mm0,    mm6
        pandn   mm1,    mm7  
;ENDIF

;IF     ARG EQ 3
;		mov     edx,    image
;        pand    mm0,    [edx+24]
;        pandn   mm1,    [edx+8*4+24]
;ENDIF
;   mm0 = tmp & (image   = iobraz)
;   mm1 =~tmp & (image+8 = iobraz2)
;IF     ARG EQ 0 
;		sub		eax,	L
;ENDIF        
        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    0-15
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    0-15
		jge			retur

        psrlq   mm0,    32
		add     eax,    dword ptr bit_cnt[edi*4]  ;    16-31
        psrlq   mm1,    32
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    16-31
		jge			retur

        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    32-47
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    32-47
		jge			retur

		add     eax,    dword ptr bit_cnt[edi*4]  ;    48-63
		add     edx,    8
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    48-63
;IF     ARG NE 3
		jge			retur
;ENDIF
        
;       CYKL 3
        movq    mm0,    [edx]       ;   mm0 = etalon

        movq    mm1,    mm0     
;IF     ARG EQ 0 
;        pand    mm0,    mm2
;        pandn   mm1,    mm3  
;ENDIF

;IF     ARG EQ 1
;        pand    mm0,    mm4
;        pandn   mm1,    mm5  
;ENDIF		 

;IF     ARG EQ 2
;        pand    mm0,    mm6
;        pandn   mm1,    mm7  
;ENDIF

;IF     ARG EQ 3
		mov     edx,    image
        pand    mm0,    [edx+24]
        pandn   mm1,    [edx+8*4+24]
;ENDIF
;   mm0 = tmp & (image   = iobraz)
;   mm1 =~tmp & (image+8 = iobraz2)
;IF     ARG EQ 0 
;		sub		eax,	L
;ENDIF        
        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    0-15
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    0-15
		jge			retur

        psrlq   mm0,    32
		add     eax,    dword ptr bit_cnt[edi*4]  ;    16-31
        psrlq   mm1,    32
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    16-31
		jge			retur

        movd   esi,    mm0
		mov		edi,	esi
		and		esi,	0ffffh
        movd   ebx,    mm1
		shr		edi,	16
		mov		ecx,	ebx
		and		ebx,	0ffffh
		shr		ecx,	16
        add     eax,    dword ptr bit_cnt[esi*4]  ;    32-47
		
		add     eax,    dword ptr bit_cnt[ebx*4]  ;    32-47
		jge			retur

		add     eax,    dword ptr bit_cnt[edi*4]  ;    48-63
		add     edx,    8
        add     eax,    dword ptr bit_cnt[ecx*4]  ;    48-63
;IF     ARG NE 3
;		jge			retur
;ENDIF
retur:
		add		eax,	L
        }
        
#endif  
}        
        

MMX_FUNC(void) MMX_open( Int32 *image)
{
#ifdef WIN32
_asm    {
		mov     edx,    image
		movq	mm2,	[edx]	     ;   MM2 = (image   = iobraz)
		movq	mm3,	[edx+8*4]    ;   MM3 = (image+8 = iobraz2)
		movq	mm4,	[edx+8]	     ;   MM4 = (image   = iobraz)
		movq	mm5,	[edx+8*4+8]  ;   MM5 = (image+8 = iobraz2)
		movq	mm6,	[edx+16]	 ;   MM6 = (image   = iobraz)
    	movq	mm7,	[edx+8*4+16] ;   MM7 = (image+8 = iobraz2)
        }
#endif
}

MMX_FUNC(void) MMX_close(void)
{
#ifdef WIN32
_asm		EMMS
#endif
}
