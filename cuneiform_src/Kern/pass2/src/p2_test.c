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

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "nt_types.h"
//#include "struct.h"
#include "lang_def.h"
#include "cstr.h" // OLEG
#include "fon.h"
#include "p2libr.h"

// ���� language
#include "ligas.h"				// 01.06.2001 E.P.
#include "p2.h"					// 01.06.2001 E.P.
extern P2GLOBALS p2globals;		// 01.06.2001 E.P.

#define P_TEST 240
#define P_IN   245      // ������


static Word8 porogSelfTest[256]={
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST, // 128 -
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_IN  ,P_IN  ,P_TEST,P_TEST,P_IN  ,P_TEST,P_IN  ,P_TEST,P_IN  , // 160-
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_IN  ,P_TEST,P_TEST, // 224-
	P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST,P_TEST
};

// � ��� �������� ����� �� ������ �������
static Word8 *testAlts[256]={
	"","","","","","","","","","","","","","","","",
    "","","","","","","","","","","","","","","","",
	"","","","","","","","","","","","","","","","", //32-47
	"\x8e","lI","","\x87","","","\xa1","","B\x82","", // 48 - 57 (0-9)
	"","","","","","", //58-63
	"","","8","","","","","","","1l","","","","","","", // 64-79 @A-O
	"","","","","","","","","","","","","","","","", // 80-95 P-
	"","es","h","","","sa","","","b","","","","1I","","","", // 96-111 `a-o
	"","","","ae","","","","","","","","","","","","", // 112-127 
	"","","8","","","","","3", //128
	"","","","\x8f","\xac","","0","\x8b", //136
    "\xe0","","","\xe3","\xe4","","","","","","","","","","","", // 144
	"\xa2","6","\xa5\xa7\xad\xa0","\xe2","","\xa2\xe1","","\xed\xa2",     // 160 - 167    �-�
	"\xad\xaf","","","\xaf","\x8c","\xa8\xaf\xeb","\xfd","\xa8\xab\xad", // 168 - 175 �-�
	"","","","","","","","","","","","","","","","", // 176
	"","","","","","","","","","","","","","","","", // 192
	"","","","","","","","","","","","","","","","", // 208 
	"\x90","\xa5\xae","\xa3","\x93","\x94","","","",//224-231 �-�
	"\xe9","\xe8","","","","\xa7\xa0","","\xa0", // 232-239   �-�
	"","","","","","","","","","","","","","\xae","",""  //240-255
};
//////////////////

Int32 p2_testSelf(RecRaster *recRast,RecVersions *vers,FonSpecInfo *specInfo,Int32 testSelf)
{
 int nAlt,i;
 Word8 *alts;
 FonTestInfo testInfo[MAXCHECKALT];

    if( !specInfo || !specInfo->nLet )
	  return 0;

	// ��� ������������ �� ���� ?
	if( testSelf > 0 )
	{
		nAlt = 1;
		testInfo[0].prob = (Word8)testSelf;
	}
    else
	{
     nAlt=FONTestChar(recRast,specInfo->nLet,testInfo,specInfo->nInCTB);
	 specInfo->nClust=testInfo[0].nClust;
	}

    if( nAlt <= 0 || testInfo[0].prob <= porogSelfTest[specInfo->nLet] )
			return 0;

	nAlt=1;
	vers->Alt[0].Code=specInfo->nLet;
	vers->Alt[0].Prob=testInfo[0].prob;
	vers->Alt[0].Method = REC_METHOD_FON;
	vers->lnAltCnt=1;

	// ��������� ������ �� ���� ?
	if( specInfo->onlySelf == 1 )
		return vers->lnAltCnt;

	alts=testAlts[specInfo->nLet];

	// 16.07.2001 E.P. �������� � a_bottom_accent_baltic 0xe0 
	if( is_baltic_language(p2globals.language) &&
			(specInfo->nLet==0xe0 || alts[0]==0xe0)
	  )
	  alts="";

	for(;*alts;alts++)
	{
       if(vers->lnAltCnt >= REC_MAX_VERS)
		   break;

       nAlt=FONTestChar(recRast,*alts,testInfo,0);

	   if(nAlt > 0)
	   {
          for(i=0;i<vers->lnAltCnt;i++) 
			  if(testInfo[0].prob > vers->Alt[i].Prob) break;
          if(i < vers->lnAltCnt)
             memmove(vers->Alt+i+1,vers->Alt+i,(vers->lnAltCnt-i)*sizeof(RecAlt));
		  vers->Alt[i].Code   = *alts;
	      vers->Alt[i].Prob   = testInfo[0].prob;
	      vers->Alt[i].Method = REC_METHOD_FON;
	      vers->lnAltCnt++;

		  if(i==0) // the best ?
		   specInfo->nClust=testInfo[0].nClust;
	   }
	}

	return vers->lnAltCnt;
}
//////////////////

Int32 p2_testAccents(CSTR_rast first,CSTR_rast last )
{
 FON_FUNC(Int32) FONRecogBroken(CSTR_rast firLeo,CSTR_rast lasLeo,
							  CSTR_rast firNew,CSTR_rast lasNew,
						      int lang, int porog, int nNaklon, int nRazmaz);
 CSTR_rast rst,rstPrev,rstNext;
 RecVersions     verOld;
 CSTR_rast_attr  attr,attrAcc;
 int  language=p2globals.language;
 int  porog ;  // TRSFINE
 Int32 goodBrok=0;

   if( language==LANG_ENGLISH && p2globals.multy_language )
                  language    = LANG_RUSENG;
//
//
   for(rst=first; rst && rst != last; )
   {
        if( !CSTR_GetAttr(rst,&attr) ||
            !CSTR_GetCollection(rst,&verOld) ) 
                return 0;

		if( !(attr.flg & (CSTR_f_bad|CSTR_f_let)) )
		{
			rst = CSTR_GetNext(rst);
			continue;
		}

		rstNext=CSTR_GetNext(rst);
		if( rstNext == last )
			rstNext = NULL;

		rstPrev=CSTR_GetPrev(rst);

		if( rstPrev )
		{
			CSTR_GetAttr(rstPrev,&attrAcc);
			if( attrAcc.flg & CSTR_f_let )
				rstPrev = NULL;
			else
			{
				if( attrAcc.col + attrAcc.w <= attr.col ||
					attrAcc.col >= attr.col + attr.w
				  )
				  rstPrev = NULL;
			}
		}

		if( rstNext )
		{
			CSTR_GetAttr(rstNext,&attrAcc);
			if( attrAcc.flg & CSTR_f_let )
				rstNext = NULL;
			else
			{
				if( attrAcc.col + attrAcc.w <= attr.col ||
					attrAcc.col >= attr.col + attr.w
				  )
				  rstNext = NULL;
			}
		}

		if( rstPrev == NULL && rstNext == NULL)
		{
			rst = CSTR_GetNext(rst);
			continue;
		}	

		if(verOld.lnAltCnt <= 0 )
			porog = 180;
		else
		    porog = max(180, verOld.Alt[0].Prob-20);

		if( !rstPrev )
			rstPrev = rst;
		if( !rstNext )
			rstNext = rst;

		rstNext = CSTR_GetNext(rstNext);

		if( FONRecogBroken( rstPrev,rstNext,rstPrev, rstNext,  language,
			                porog, p2globals.nIncline,1) > 0 
		   )
			 goodBrok++;

		rst = rstNext;
   }

   return goodBrok;
}
/////////////////////////////////       
