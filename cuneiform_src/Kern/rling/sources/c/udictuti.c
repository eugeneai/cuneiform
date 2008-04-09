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

/* ------------------------------------------------------------------ *\
|                                                                      |
|    This module is a set of user dictionary high-level utilities.     |
|                                                                      |
\* ------------------------------------------------------------------ */

//
// 08-13-93 07:27pm, Mike.
// Comments:  Updating for multi-lingual version of CuneiForm ( release
//            28-June-93 ). Release has been received from Joe by FEDERAL
//            mail.
//
// The main target: To use new stream technology : IOLIB.H.
//
// Process indicator:
//  1. Preliminary updation. 08-13-93 06:40pm, Mike
//

  #include "spelmode.h"

  #if defined (TURBO_C)
    #include "tc_types.h"
  #elif defined (BC_FOR_WIN)
    #include "bcwtypes.h"
    typedef long signed int LONG;
  #elif defined (WATCOM)
    #include "spelwatc.h"
  #elif defined(THINK_C)
    #include "spelthin.h"
  #else
    #error No tool has been specified
  #endif

  #include <ctype.h>

  #include "speldefs.h"
  #include "spelfunc.h"
  #include "udicfunc.h"
//  #include "iolib.h"
//  #include "status.h"
  #include "lang.H"
  #include "TigerEmulate.h"

	      /***        P R O T O T Y P E S       ****/

 static INT UserDictRDWR( BYTE * word,voc_state * user_dict,INT weight,INT mode);
 static BOOL ispermitted (BYTE a);
 extern BYTE multy_language;


/* ------------------------------------------------------------------ */

INT AddWordToUserDictionary ( BYTE * word, INT weight,voc_state * user_dict)
{ INT resp;

  resp =UserDictRDWR( word, user_dict, weight, VOC_W);

  if ( resp > 0)               return TRUE;
  else
    switch ( resp )
    {
    case  VOC_MEM_OVERFLOW   : return FALSE;


    case  VOC_ACCNT_OVERFLOW : return TRUE;

    case  VOC_ACCNT_ZERO     :
    default                  : /* printf ("Bolvano...");*/
                               return FALSE;
    }
}

/* ------------------------------------------------------------------ */

INT DeleteWordFromUserDictionary ( BYTE * word, voc_state * user_dict)
{ INT resp;

  resp =UserDictRDWR( word, user_dict,-256, VOC_R);

  switch ( resp )
  {
    case  0             :
    case  VOC_ACCNT_ZERO:                        return   TRUE;
    default             : printf ("Bolvano...");  return   FALSE;
  }
}

/* ------------------------------------------------------------------ */

INT _IsWordInUserDictionary ( BYTE * word, voc_state * user_dict)
{ INT resp;

  resp =UserDictRDWR( word, user_dict,0, VOC_R);
  if( resp >= 0 )                                 return   resp;
  else
    {                     ;                       return     0;}
}

/* ------------------------------------------------------------------ */

INT UserDictRDWR( BYTE * word, voc_state * user_dict, INT weight, INT mode)
{
  LTIMG wrdimg[MAX_WORD_SIZE],*wrddef[MAX_WORD_SIZE+1];
  LT lt[MAX_WORD_SIZE];
  INT i;
  INT lth;
    for ( i = 0; *word ; i ++,word++)
    {
      if ( i == MAX_WORD_SIZE) return 0;
      lt[i].code = *word;
      lt[i].attr = 255;
      wrdimg[i].lt =lt+i;
      wrdimg[i].blank = 0;
      wrddef[i] = wrdimg + i;
    }
  wrddef[i] = NULL;
  lth = i-1;
  user_dict -> lev = -1;
  return voc_(user_dict, wrddef, &lth, weight, mode, NULL);
}

/* ------------------------------------------------------------------ */

/* function splits a word record onto a pair of word and its frequency.
// if record is incorrect, 0 returned.
// if frequency omitted, 1 returned;
// if line is empty -1 returned.
// otherwise frc returned.
*/
INT   SplitWordRecord(BYTE  * str)
{ BYTE *b;
  b = str;
  while((*str) && (*str== ' ')) str++;
  if ((!*str )||(*str == '\n'))               return -1;
  if (!ispermitted(*str))                     return  0;
  if ( b != str)
	       strcpy (b, str);
  b++;
  while( (*b) && ispermitted(*b)) b++ ;
  if (!*b)                                 return 1;
  if(*b == '\n') { *b =0;                  return 1;}
  if( *b != ' ')                           return 0;
  *(b++) = 0;
  while ( ( *b) && (*b == ' '))   b++;
  if ( (!*b)|| (*b == '\n'))               return 1;
  if (!isdigit(*b))                        return 0;
  return atoi(b);
}

/* ------------------------------------------------------------------ */

static byte tab_alphas [256] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // 0
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // 10
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // 20
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // 30
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    // 40
    1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,    // 50
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    // 60
    1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,    // 70
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // 80
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // 90
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // a0
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    // b0
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    // c0
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    // d0
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,    // e0
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1     // f0
};

void init_tab_alpha(BYTE *s1,BYTE *s2,INT num)
{
INT i;
if( language==LANG_RUSSIAN && multy_language || language==LANG_RUSENG)
  MEMSET(&tab_alphas[128],0,128);
else
  MEMSET(tab_alphas,0,256);
for(i=0;i<num;i++)
  tab_alphas[s1[i]] = tab_alphas[s2[i]] = 1;
return;
}

BOOL ispermitted (BYTE a)
{
  return tab_alphas[a];
}
//BOOL ispermitted (BYTE a)
//{
// if ( isalpha (a))                   return TRUE;
// if ( a == '\'')                     return TRUE;
//                                     return FALSE;
//}

/* ------------------------------------------------------------------ */
// 08-13-93 07:26pm, Mike
// Updated to use IOLIB.H.

/* the following function tests file <name> and returns one of the
   following conclusions:
			 - UD_NOTEXIST   - file doesn't exist;
			 - UD_WRONGHEAD  - file is not a CTC user dictionary;
			 - UD_PERMITTED  - file has a CTC user dict header.
*/

INT _IsUserDict (CHAR * name)
{
  CHAR buff[128];
  INT f;
  LONG ret;

  f = TGOPEN( (INT)VC_STREAM, name, (INT)(O_RDONLY|O_BINARY), S_IREAD );
  if ( f ==-1) {
    return UD_NOTEXIST;
  }

  ret = TGREAD (f, buff, sizeof(DYN_DICT_HEADER));
  if ( ret != sizeof(DYN_DICT_HEADER)) {
    return UD_WRONGHEAD;
  }

  buff[sizeof(DYN_DICT_HEADER)] = 0;
  if ( strcmp(buff,DYN_DICT_HEADER) ) {
    return UD_WRONGHEAD;
  }

  TGCLOSE(f);

  return UD_PERMITTED;
}

/* ------------------------------------------------------------------ */




