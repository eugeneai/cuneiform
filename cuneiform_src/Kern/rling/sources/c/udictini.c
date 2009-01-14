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

/*

�����������������������������������������������������������������������������ͻ
�        This module is a set  user dictionary initialisation utilities       �
�����������������������������������������������������������������������������ͼ
*/
 #include "spelmode.h"
/////// #include <dos.h>
#if defined (WATCOM)
  #include "spelwatc.h"
#elif defined (BC_FOR_WIN)
  #include "bcwtypes.h"
  typedef long signed int LONG;
#elif defined(TURBO_C)
 #include "tc_types.h"
#else
 #error No tool specified
#endif

 #include "speldefs.h"
 #include "spelfunc.h"
 #include "udicfunc.h"

 #include "tigeremulate.h"

#include "compat_defs.h"

DWORD        LoadUserDict( CHAR      *DictName,
                           CHAR      *pool,
			               DWORD     pool_size,
			               voc_state *user_dict)
 {
   LONG      size;
   pool_size = pool_size;
   if (_IsUserDict(DictName)!= UD_PERMITTED)     return 0;

#ifdef TURBO_C
 if(TEST_PRPH(pool))
    pool=ALI_PR(pool);
#endif

  user_dict -> vocseg = (BYTE *)SET_VOC_ROOT(pool);

  {
    INT Fh;
    CHAR nm[128];
    strcpy (nm, DictName);
    Fh = TGOPEN (VC_STREAM, nm, (INT)(O_RDONLY | O_BINARY), S_IREAD);
    if (Fh == -1)
        return 0;
    if (TGFILELTH(Fh) > MAX_VOC_SIZE)
    {
      TGCLOSE(Fh);
      return   0;
    }
    size = TGREAD(Fh, V_POINT(user_dict -> vocseg,0), TGFILELTH(Fh));
    TGCLOSE (Fh);
   }
  if ( size <=0)                      return 0;
   else
      { voc_open(user_dict);
        user_dict -> vocfree = (WORD)size;
      }
  return MAX_VOC_SIZE;
  }

DWORD InitializeNewUserDict ( CHAR *pool, DWORD pool_size, voc_state *user_dict)
{
#ifdef TURBO_C
 if(TEST_PRPH(pool))
    pool=ALI_PR(pool);
#endif

  if ( pool_size < MAX_VOC_SIZE)                   return 0;

  user_dict -> vocseg = SET_VOC_ROOT(pool);
  voc_init(user_dict);

  return MAX_VOC_SIZE;
}

 void ResetUserDict(voc_state * user_dict)
 {
  user_dict ->lev = -1;
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
 BOOL CloseUserDictionary (BYTE * DictName, voc_state *user_dict)
{
	if ( user_dict -> state & VOC_CHANGED)
	{
		char w[80];
		LONG size;
		INT h;

		strcpy (w,DictName);
		h = TGOPEN (VC_STREAM,w,O_CREAT, S_IREAD);

		if ( h == -1)
		{
			/* MsgBox("failed to open"); */
			return FALSE;
		}

		size = TGWRITE (h,V_POINT(user_dict ->vocseg,0), user_dict ->vocfree  );
		TGCLOSE(h);

		if ( size != (LONG)user_dict->vocfree )
		{
			/* MsgBox("wrong size"); */
			return  FALSE;
		}

		user_dict -> state &= (~VOC_CHANGED);
	}
	return     TRUE;
}
