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
#include "nt_types.h"
#include "tuner.h"
#include "lang.h"

#include "struct.h"
#include "func.h"
#include "status.h"
#include "msgerr.h"
#include "ligas.h"
#include "linutil.h"
#include "ukr.h"
#include "minmax.h"

strucI workI;


void dif_II( void )
{
   c_comp *cp;
   lnhead *lp;
   INT  h=workI.c->h/2,ii=0;

   if( !workI.twoDot && workI.ld == NULL && workI.rd && workI.rh > 0 ){
      workI.c->vers[1].prob -= 20;
      goto  ret_dif;
   }
   if( workI.ld && workI.rd && /*workI.c->prevl->vers[0].let != UKR_i &&  */
       abs(workI.lh-workI.rh) >= 2 &&
       (workI.lw > 2*workI.rw || workI.rw > 2*workI.lw) ){
      workI.c->vers[1].prob -= 20;
      goto  ret_dif;
   }
   if( workI.ld && workI.rd && workI.lh > 0  && workI.rh > 0 ){
      workI.c->vers[0].prob -= 20;
      goto  ret_dif;
   }

   cp = workI.c->env;
   for(;cp!=NULL;cp=cp->next){
      lp = (lnhead *)((PBYTE)cp + cp->lines + sizeof(WORD));
      while( lp->lth != 0 ){
         if( lp->row <= workI.c->h/8 ){
            ii++;
            if( h > lp->h )
              h = lp->h;
         }
         lp = (lnhead *)((PBYTE)lp + lp->lth);
      }
   }
   workI.c->vers[0].prob -= 24*workI.twoDot;
   if( ii >= 2 && h >= 2 ){
      if( !workI.twoDot )
        workI.c->vers[0].prob -= 20;
   }
   else
      workI.c->vers[1].prob -= 20;

ret_dif:
   sort_vers(workI.c);

   return;
}/*dif_II*/


BOOL  proc_UKR_I( cell *c )
{
   cell  *cc,*clist[3];
   BYTE  one,Ione,let;
   INT   i,ii=0;

   if( c->flg & (c_f_dust|c_f_punct) )
     return  FALSE;

   if( c->vers[0].let == '|' || c->vers[0].let == liga_i ){
      c->vers[0].let = 'i';
   }

   if( ((let=c->vers[0].let)=='i' || let=='I' || let=='1') ){
      workI.c = c;
      workI.ld = NULL;
      workI.rd = NULL;
      workI.twoDot = 0;
      one = Ione = 0;
      for(i=0;i<c->nvers;i++){
         if( c->vers[i].let == '1' )
           one = c->vers[i].prob;
         if( c->vers[i].let == 'I' )
           Ione = c->vers[i].prob;
      }

      cc = dot_ij(c);

      ii = 0;
      if( workI.ld ){
         ii++;
         clist[ii] = workI.ld;
         if( 2*clist[ii]->w > 3*clist[ii]->h && 3*clist[ii]->w > 2*c->w )
           workI.twoDot = 1;
         else if( clist[ii]->w > c->w && clist[ii]->w > clist[ii]->h )
           workI.twoDot = 1;
      }
      if( workI.rd ){
         ii++;
         clist[ii] = workI.rd;
         if( 2*clist[ii]->w > 3*clist[ii]->h && 3*clist[ii]->w > 1+2*c->w )
           workI.twoDot = 1;
         else if( clist[ii]->w > 1+c->w && clist[ii]->w > 1+clist[ii]->h )
           workI.twoDot = 1;
      }

      if( ii ){
         clist[0]=c;
         compose_cell((INT)(ii+1),clist,c);
      }
      if( let != 'i' ){ // upper
         c->vers[0].let = UKR_I;
         c->vers[1].let = UKR_II;
         c->vers[1].prob = c->vers[0].prob;
         c->nvers = 2;
         dif_II();
         if( one ){
            INT  i,dl=0,dr=0;

            c->vers[c->nvers].let = 0;
            c->vers[c->nvers].prob = 0;
            promote('b',c,'1',0);
            if( c->prevl->flg & c_f_let ){
               for(i=0;i<c->prevl->nvers;i++)
                  if( is_digit(c->prevl->vers[i].let) && c->prevl->vers[i].prob > 100 ){
                     dl = 1;
                     break;
                  }
            }
            if( c->nextl->flg & c_f_let ){
               for(i=0;i<c->nextl->nvers;i++)
                  if( is_digit(c->nextl->vers[i].let) && c->nextl->vers[i].prob > 100 ){
                     dr = 1;
                     break;
                  }
            }
            if( dr == 0 && dl == 0 ){
               promote('b',c,'1',-10);
            }
            else{
               promote('b',c,UKR_I,-10);
               promote('b',c,UKR_II,-10);
            }
            if( (INT)Ione-one < 0 ){
               promote('b',c,UKR_I,(INT)(Ione-one));
               promote('b',c,UKR_II,(INT)(Ione-one));
            }
         }
      }
      else{ // lower
            c->vers[0].let = UKR_i;
            c->vers[1].let = UKR_ii;
            c->vers[1].prob = c->vers[0].prob;
            c->nvers = 2;
            dif_II();
            if( c->prevl->vers[0].let == UKR_i || c->prevl->vers[0].let == UKR_ii ){
               INT  ldis,rdis,mdis;

               ldis = c->prevl->col - c->prevl->prevl->col - c->prevl->prevl->w;
               rdis = c->nextl->col - c->col - c->w;
               mdis = c->col - c->prevl->col - c->prevl->w;
               if( mdis < 2*MIN(ldis,rdis) ){
                  if(  2*ldis <= rdis ){
                     promote('b',c->prevl,UKR_ii,-30);
                     promote('b',c       ,UKR_i, -30);
                  }
                  else{
                     if( 4*MIN(ldis,rdis) > c->w ){
                        promote('b',c->prevl,UKR_i,-30);
                        promote('b',c       ,UKR_i,-30);
                     }
                  }
               }
            }
      }
      c->vers[c->nvers].let = 0;
      c->vers[c->nvers].prob = 0;
      if( db_status && snap_activity('b') ){
         snap_newcell(c);
         snap_show_text("delete dot for UKR i");
         snap_monitor();
      }
   }

   return  FALSE;
}/*proc_UKR_I*/


void proc_Ukr( void )
{
   cell *c;

   if (db_status)
     snap_newpass('b');

   for (c = cell_f(); c != cell_l(); c = c -> next){
      proc_UKR_I(c);
   }
}/*proc_Ukr*/


