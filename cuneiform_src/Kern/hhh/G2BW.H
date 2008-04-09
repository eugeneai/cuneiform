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

#ifndef __G2BW_H
#define __G2BW_H

#include "globus.h"
#include "imgaccs_gbw.h"

#ifndef GBW_FUNC
        #define GBW_FUNC FUN_IMPO
#endif

enum TBinEnum {VIA_DEZA,VIA_KRONROD};


#ifdef __cplusplus
 extern "C"
  {
#endif
/*
	���������.
1. ������ ���� ���������� �� ���������� ���������� �� ��������� ImageInfo.
2. ������ ������ ����������� (� ������) ����� ImageInfo->wImageWidth. 
3. ������ ����������� �� ����������� ����������� �� ������� (ImageInfo->wImageWidth+7)/8 (��� �����!!!).
4. ����������� ���� ����������� ImageInfo->bFotoMetrics		
5. fGetGreyBlock ����� ��� ���������: ����� ���� ���������� �����, ��������� ������, ����� ������������� �����
*/

GBW_FUNC( Bool ) OpenBinarizator  (enum TBinEnum benum,
								   LPTIGER_IMAGEINFO ImageInfo,
									TImageGetBlock fGetGreyBlock
//#ifdef gbwMANUBRI      // version with manual Image Intensity flag
		 ,
		  short int ImageInty   // 0 - "weak", 1- "normal", 2 -"dirty"
//#endif
					   );
GBW_FUNC( Word16 ) Binarize  ( PWord8 lpBuff, Word16 Lth);
/*
	lpBuff - �����, ���� ������ �����-�����
	lth    - ����� ���� 
���������� 0, ���� ����������� ���������.
*/
GBW_FUNC( void )   CloseBinarizator (void);

#ifdef WIN32
	#include "windows.h"
/*
	�������������� ������ 8 ������� DIB ����������� � �.�. DIB.
	���������:
		benum - ��� ����������� (�� ����)
		ImageInty - �������� ����������� (�� ����)
		hInMemory - handle ���������� ������ �� ����� DIB
	���������� NULL � ������ ������ ��� handle ���������� ������ �� �.�. DIB.
	��� ������������ ������ ���� ������� GlobalFree(<�.�. DIB>).


*/
//  hInMemory - 8 pixel-gray image DIB 
//  Return B/W image DIB or NULL if error.	 
GBW_FUNC( HGLOBAL ) GreyToMono(enum TBinEnum benum,short int ImageInty,HGLOBAL hInMemory);
GBW_FUNC( void    ) DestroyMono(HGLOBAL hInMemory);

GBW_FUNC(Word16)	Grey_open(enum TBinEnum benum,Word16 Width, Word16 Height);
GBW_FUNC(Word16)	Grey_to(PWord8 pTo);
GBW_FUNC(void)		Grey_from(PWord8 pFrom);
GBW_FUNC(void)		Grey_close(void);

#ifndef DPITODPM
	#define DPITODPM(a) ((long)a * 254L / 10000L)
	#define DPMTODPI(a) ((long)a * 10000L / 254L)
#endif

#endif // WIN32

#ifdef __cplusplus
};
#endif

#endif   // __G2BW_H
