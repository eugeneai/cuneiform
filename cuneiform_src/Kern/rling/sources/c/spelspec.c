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

// 08-14-93 03:08pm, Mike
// This file has been modified to use the new stream technology.
//

  #include "spelmode.h"

  #if defined(TURBO_C)
    #include "tc_types.h"
  #elif defined(WATCOM)
    #include "spelwatc.h"
  #elif defined(THINK_C)
    #include "spelthin.h"
  #else
    #error   NO TOOOL SPECIFIED
  #endif

  #include "speldefs.h"
  #include "spelfunc.h"
  #include "tigeremulate.h"
//  #include "iolib.h"


#define SP_ABC_NO    12

typedef struct spec_abc {
		ArtVH           *    hd;
		BYTE    *  *  pref;
		BYTE            *  body;
		BYTE    *  * postf;
} SABC;

SABC          SpABC[SP_ABC_NO];
ArtFH  *        SpABCroot;

/* ------------------------------------------------------------------ */

extern LONG read_all_vtab(INT,CHAR  *);

BYTE  * load_specABC (BYTE  *point, INT Country)
{
  BYTE  *a;
  BYTE  *  *b;
  long  size;
  int i,j;

  SpABCroot = (ArtFH  *)point;

// 08-14-93 03:03pm, Mike
// Reading *.art file ( art-dictionary ).
  size = read_all_vtab( 8, (CHAR *)SpABCroot );
  if (size == -1L ) {
    #ifdef SYSPR_ERROR
      PRINTF("Unable to open %s \n", w);
    #endif
    return NULL;
  }

  for ( i = strlen(ARTFILE_ID) ; i < size ; i++ ) {
    *(point +i) ^= XOR_MASK;
  }

  if ( SpABCroot->voc_no >= SP_ABC_NO ) {
    #ifdef SYSPR_ERROR
      PRINTF("Too many specABC: %d\n", SpABCroot -> voc_no);
    #endif
    return (NULL);
  }

  a = point + sizeof(ArtFH);
  b = (BYTE * *)(point + size);
  for ( i = 0; i < SpABCroot -> voc_no; i++) {
    SpABC[i].hd = (ArtVH *)a;
    a += sizeof (ArtVH);
    SpABC[i].pref = b;
    for ( j = 0; j < SpABC[i].hd->pref_no; j++) {
      *b = a;
      while( *(a++) );
      b++;
    }
    *(b++) = NULL;
    SpABC[i].body = a;
    while( *(a++) );
    SpABC[i].postf = b;
    for ( j = 0 ; j < SpABC[i].hd->post_no ; j++ ) {
      *b = a;
      while( *(a++) );
      b++;
    }
    *(b++) = NULL;
  }

 Country=0;
 return (BYTE *)b;
}


/* ------------------------------------------------------------------ */

INT check_art_dict (CHAR word[], INT * wordlth, INT * vockind)
{

      CHAR                      no;
      CHAR                    pref;
      CHAR                   postf;
      CHAR  CapWord[MAX_WORD_SIZE];
 register PCHAR             body_b;
      PCHAR                 body_e;
 register BYTE             *p;
  word[*wordlth+1]=0;

  for ( p =word,body_b = CapWord; *p  ; p++,body_b++)
                         *body_b = _2cap (*p);
  *body_b = 0;

 /*for ( no= (strcmp ( CapWord, word) != 0 ) ? 2 : 0; no<SP_ABC_NO; no++ )*/

 /** Do not forget about Latyn **/

 /** The first (0) triple is always main dictionary prefs - postfs */

 for (no= 1 ; no <SpABCroot ->voc_no; no++)

    for(pref=0; (p=SpABC[no].pref[pref]) != 0 ;pref++)
    {
      for( body_b=CapWord ; *p && *body_b ; p++,body_b++)
      if( *body_b != *p) break;
      if( (!*p) && (*body_b) )
      {
        for(postf=0; (p=SpABC[no].postf[postf]) != 0 ;postf++)
        { CHAR lth;
          for(body_e=CapWord+(*wordlth), lth=*wordlth+1;
                *p && lth ; p++,body_e--,lth--)
          {
            if(*body_e != *p ) break;
          }
    /*     if((!*p) && lth)                   Lepik -- 08/06/92 04:30pm  */
    /*                                                                   */
    /* This restriction prohibits 1st and 2nd.                             */

    /* The following permits 'TH'                                        */

          if (!*p)
          {
            for( ; body_b <= body_e; body_b++)
            { for(p=SpABC[no].body; *p ; p++)
                if(*body_b==*p) break;
              if (!(*p)) break;
            }
            if( body_b > body_e)
              {  *vockind=no+4;
                return SpABC[no].hd ->relabty;
              }
          }
        }
      }
    }
  return 0;
}

/* ------------------------------------------------------------------ */

INT test_apppostrof (BYTE word[],SWORD *wrd, INT *l, INT *r)
 {
  INT       i, pref, apf, postf;
  BYTE       *p,  *pp;
  CHAR   CapWord[MAX_WORD_SIZE];

  for ( p =word, pp = CapWord ; (*p) != 0  ; p++, pp++)
                         *pp = _2cap (*p);
  *pp = 0;

  *l = 0;
  *r = wrd -> lth;

  for ( apf  = 0; apf < wrd -> lth; apf++)
        if (CapWord[apf] == 0x27)             break;
    //  if (wrd ->pos[apf] ->type_sp & T_APF)             break;
  if (apf == wrd -> lth)
				             	                        return FALSE;

  for(pref =0; (p=SpABC[0].pref[pref]) != 0 ; pref++)
    {
	  for (i = 0; *(p+i) && CapWord[i]; i++)
		 if ( *(p+i) != CapWord[i]) break;
	                                                 /* vowel */
	  if ( (!*(p+i)) &&  (i == apf) &&(i))
		if (IsVowel(CapWord[i+1]))
		  {
		   *l =i + 1;
		   break;
		  }
	}

  for ( i  = wrd -> lth -1; i >apf; i--)
        if (CapWord[i] == 0x27)             break;
      //if (wrd ->pos[i] ->type_sp & T_APF)                  break;

  if ( (i == apf) && *l)                             return TRUE;

  apf = i;

  for(postf =0; (p=SpABC[0].postf[postf]) != 0 ; postf++)
   {
	  for (i = 0; *(p+i) && (wrd -> lth -i-1); i++)
		 if ( *(p+i) != CapWord[wrd ->lth -i -1])          break;
	  if ( (!*(p+i)) &&  (wrd -> lth -i -1 == apf) && (i !=0))
		  {
		   *r =apf;
		   break;
		  }

   }
 return  (*r != wrd -> lth) || (*l);
 }
