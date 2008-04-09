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

/************************************************************************/
/* DIFFRB.C - ������ �㭪樨 ��� ���ਬ����஢ 			*/
/*             ( � Tiger-e �뫨 ����ᠭ� ��� TASM)			*/
/************************************************************************/
/* LeftDistance - ����ﭨ� �� ��ࢮ�� ᫥�� ���			*/
/* RightDistance -����ﭨ� �� ��ࢮ�� �ࠢ� ���			*/
/* SumIntervalBits  - ������� �㬬� ��� (��砫� � ����� - ���� ) 	*/
/* SumBits - ������� �㬬� ��� � ��ப� ���� 				*/
/* VertSum - ������� �㬬� ��� � �⮫��  				*/
/* MinMaxLeft - ���� min � max ����ﭨ� �� ����� ���� 		*/
/* MinMaxRight - ���� min � max ����ﭨ� �� �ࠢ�� ���� 		*/
/* NumHorizInterval - �᫮ ���ࢠ��� � ��ப� 			*/
/* NumVertInterval - �᫮ ���ࢠ��� � �⮫�� 			*/
/* FOOT_A - ���᫨�� ���⨪����� �஥��� ���� 			*/
/* FOOT3 - ���᫨�� �᫮ ��� ( ��������� 3-����� �㪢�) 		*/
/* FOOT - ���᫨�� �᫮ ���  						*/
/* Assym_let - �業��� ���⨪����� �ᨬ����� �㪢�  			*/
/* CenterVertInterval - �।��� ���ࢠ�� � �⮫�� 			*/
/************************************************************************/
/* ��������� :	*********************************************************/
/*           RASTER - 㪠��⥫� �� ��ப� ��� �� ��砫� ࠡ�祭� ���� */
/*           Wx     - �ਭ� �.�.                                       */
/*           NWIDTH - �ਭ� �����窨 � �.�.  ��� ��ப�                */
/*           NHEIGHT- ������⢮ ��ப � �.�.                           */
/*           �olumn - �⮫���                                           */
/************************************************************************/

#include <string.h>
/*
#ifdef __MAC__
#define __WATCOMC__
#endif				*/

#include "nt_types.h"	// ������ ⨯� 		

#include "diskrtab.h"      	// ⠡���� 			

BYTE BUFFER[256];       // ���⨪��쭠� �஥���  
BYTE LOCAL[50];			// ᯨ᮪ 業�஢ ��� 		
BYTE LOCAL_W[50];		// ᯨ᮪ �ਭ   ��� 		
BYTE beg2, end1;		// ��砫� 2-��, ����� 1-�� ���	

#define bytlen(bits)  ((bits+7)>>3)

// EndBlackInterval - ����� ��᫥����� �୮�� ��� 	
// � ��ࢮ� ᫥�� ��窥 ���� ���			
INT EndBlackInterval(BYTE *RASTER, INT NWIDTH)
{
INT i;

for(i=0;i<NWIDTH && (*RASTER)==0;i++,RASTER++); // skip white bytes    

if( i==NWIDTH)
	return(-1);

if( 	i<NWIDTH-1 && ((*RASTER)&0x01)==1 && piece_cnt[*RASTER]==1 &&
	((*(RASTER+1))&0x80)==0x80 )
	{
	RASTER ++;
	i++;
	}
return( (i<<3)+tab_last_black_bit[*RASTER] );
}

/* LeftDistance - ����ﭨ� �� ��ࢮ�� ᫥�� ���			*/
INT LeftDistance(BYTE *RASTER, INT NWIDTH)
{
INT i;

for(i=0;i<NWIDTH && (*RASTER)==0;i++,RASTER++);

if( i==NWIDTH)
	return(-1);

return( (i<<3)+start_pos[*RASTER] );
}

/* RightDistance -����ﭨ� �� ��ࢮ�� �ࠢ� ���			*/
INT RightDistance(BYTE *RASTER, INT NWIDTH)
{
INT i;

RASTER += NWIDTH-1;

for(i=0;i<NWIDTH && (*RASTER)==0;i++,RASTER--);

if( i==NWIDTH)
	return(-1);

return( (i<<3)+last_pos[*RASTER] );
}

/* SumIntervalBits  - ������� �㬬� ��� (��砫� � ����� - ���� ) 	*/
INT SumIntervalBits( BYTE *RASTER, INT n1, INT n2)
{
INT i,d,l;

i=n1>>3;
l=n2>>3;
if( i==l )	/* ��砫� � ����� � ����� ���� */
	return( 3*bit_cnt[ mask_l[n1&7] & RASTER[i] & mask_r[n2&7] ] );

d  = bit_cnt[ RASTER[i] & mask_l[n1&7] ];
d += bit_cnt[ RASTER[l] & mask_r[n2&7] ];
if( l==i+1 )	/* �� 㬥�⨫��� � 2 ����	*/
	return( 3*d );

for(i++;i<l;i++)/* ����� 2-� ����               */
	d += bit_cnt[ RASTER[i] ];
return(3*d);
}

/* SumBits - ������� �㬬� ��� � ��ப� ���� 				*/
INT SumBits( BYTE *RASTER, INT NWIDTH)
{
INT i,s;

for(i=s=0;i<NWIDTH;i++,RASTER++)
	s += bit_cnt[*RASTER];
return(s);
}

/* VertSum - ������� �㬬� ��� � �⮫��  				*/
INT VertSum( BYTE *RASTER, INT Wx, INT NHEIGHT, INT Column)
{
INT i,d;
BYTE mask=mask_byte[Column&7];

RASTER += (Column>>3);

for(i=d=0;i<NHEIGHT;i++,RASTER+=Wx)
	d += (((*RASTER)&mask)!=0);
return(d);
}


/* MinMaxLeft - ���� min � max ����ﭨ� �� ����� ���� 		*/
INT MinMaxLeft( BYTE *RASTER, INT Wx, BYTE NWIDTH, BYTE NHEIGHT,
		INT *Pmin, INT *Pmax)
{
INT maxr=0,minr=100,r,i;

NWIDTH= bytlen(NWIDTH);
for( i=0;i<NHEIGHT;i++,RASTER+=Wx)
	{
	r = LeftDistance(RASTER,NWIDTH);
	if( minr>r )
		minr = r;
	if( maxr<r )
		maxr = r;
	}

*Pmin = minr;
*Pmax = maxr;
return(0);
}

/* MinMaxRight - ���� min � max ����ﭨ� �� �ࠢ�� ���� 		*/
INT MinMaxRight( BYTE *RASTER, INT Wx, BYTE NWIDTH, BYTE NHEIGHT,
		INT *Pmin, INT *Pmax)
{
INT maxr=0,minr=100,r,i;

NWIDTH= bytlen(NWIDTH);
for( i=0;i<NHEIGHT;i++,RASTER+=Wx)
	{
	r = RightDistance(RASTER,NWIDTH);
	if( minr>r )
		minr = r;
	if( maxr<r )
		maxr = r;
	}

*Pmin = minr+1;
*Pmax = maxr+1;
return(0);
}

/* NumHorizInterval - �᫮ ���ࢠ��� � ��ப� 			*/
INT NumHorizInterval( BYTE *RASTER, INT NWIDTH)
{
INT i,d;
BYTE c,old;

for( i=d=old=0;i<NWIDTH;i++,RASTER++)
	{
	c = *RASTER;
	d += piece_cnt[c];
	if( (c&0x80) && old )
		d--;	/* �த������� */
	old = ((c&0x01)!=0) ;	/* ��᫥���� ��� �।��饣� ���� */
	}

return(d);
}

/* NumVertInterval - �᫮ ���ࢠ��� � �⮫�� 			*/
INT NumVertInterval( BYTE *RASTER, INT Wx, INT NHEIGHT, INT Column)
{
INT i,d;
BYTE c,old,mask=mask_byte[Column&7];

RASTER += (Column>>3);

for( d=1,i=old=0;i<NHEIGHT;i++,RASTER+=Wx)
	{
	c = (((*RASTER)&mask)!=0);
	if( c^old )
		d++;	/* ᪠箪 */
	old = c ;	/* �।��騩 ���� */
	}
if( old )
	d++;
d>>=1;

return(d);
}

/* FOOT_A - ���᫨�� ���⨪����� �஥��� ���� 			*/
INT FOOT_A( BYTE *RASTER, INT Wx, BYTE NWIDTH, BYTE NLENGTH)
{
INT i,j,k,d;
BYTE *p,c;

d=bytlen(NWIDTH);
memset(BUFFER,0,NWIDTH);
for(i=0;i<NLENGTH;i++,RASTER+=Wx)
	{
	p=RASTER;
	for(k=j=0;j<d;j++)
		{
		c=*p++;

#ifndef __MAC__
		*((DWORD *)&BUFFER[k])   += tab_4bits_to_DWORD[c>>4];
		*((DWORD *)&BUFFER[k+4]) += tab_4bits_to_DWORD[c&15];

#else
		BUFFER[k+7] += ((c&0x01)!=0);
		BUFFER[k+6] += ((c&0x02)!=0);
		BUFFER[k+5] += ((c&0x04)!=0);
		BUFFER[k+4] += ((c&0x08)!=0);
		BUFFER[k+3] += ((c&0x10)!=0);
		BUFFER[k+2] += ((c&0x20)!=0);
		BUFFER[k+1] += ((c&0x40)!=0);
		BUFFER[k  ] += ((c&0x80)!=0);
#endif
                k+=8;
		}
	} /* �஥��� */
return(0);
}


/* FOOT3_2 - ���᫨�� �᫮ ��� ( ��������� 3-����� �㪢�)     */
/*           � ���孥� � ������ ���������                       */
INT FOOT3_2( BYTE *RASTER, INT Wx, BYTE NWIDTH, BYTE NLENGTH)
{
INT i,old,du,dd;
BYTE c;
FOOT_A(RASTER,Wx,NWIDTH,(BYTE)(NLENGTH/2)); /* �஥��� */

for(i=0;i<NWIDTH;i++)
  BUFFER[i] = (BUFFER[i]>0); /* ����ਧ��� */

for(old=du=i=0;i<NWIDTH;i++)
	{
	c=BUFFER[i];
	if( old^c )
    du++;
	old=c;
	}
if( old )
  du++;
du >>= 1;  /* du - �᫮ ᪠窮� ������ */

  FOOT_A(RASTER+(NLENGTH/2)*Wx,Wx,NWIDTH,(BYTE)(NLENGTH/2)); /* �஥��� */

for(i=0;i<NWIDTH;i++)
  BUFFER[i] = (BUFFER[i]>0); /* ����ਧ��� */

for(old=dd=i=0;i<NWIDTH;i++)
	{
	c=BUFFER[i];
	if( old^c )
    dd++;
	old=c;
	}
if( old )
  dd++;
dd >>= 1;  /* du - �᫮ ᪠窮� ������ */
return(dd==3&&du!=3);
}

/* FOOT3 - ���᫨�� �᫮ ��� ( ��������� 3-����� �㪢�)     */
INT FOOT3( BYTE *RASTER, INT Wx, BYTE START, BYTE NWIDTH, BYTE NLENGTH, INT SHIFT)
{
INT i,old,d;
BYTE c;
FOOT_A(RASTER,Wx,NWIDTH,NLENGTH);	/* �஥��� */

d=NLENGTH;
d = (d>>SHIFT); /* 1/4 */
for(i=0;i<NWIDTH;i++)
	BUFFER[i] = (BUFFER[i]>=d); /* ����ਧ��� */

for(old=d=0,i=START;i<NWIDTH;i++)
	{
	c=BUFFER[i];
	if( old^c )
		d++;
	old=c;
	}
if( old )
	d++;
d >>= 1;  /* d - �᫮ ᪠窮� */
return(d);
}

/* Assym_let - �業��� ���⨪����� �ᨬ����� �㪢�  			*/
INT Asymm_let( BYTE *RASTER, INT Wx, BYTE NWIDTH, BYTE NLENGTH, INT TW)
{
INT i,i1,i2,t1,t2;

FOOT_A(RASTER,Wx,NWIDTH,NLENGTH);	/* �஥��� */

for(i1=0; BUFFER[i1]==0 && i1<NWIDTH; i1++);/* �ய�� ����� �㫥��� ����  */
if( i1==NWIDTH )
	return(0);

for(i2=NWIDTH-1;BUFFER[i2]==0;i2--); 	    /* �ய�� �ࠢ�� �㫥��� ���� */
i = (i1+i2)>>1;
for(t1=0;i1<i;i1++)
	t1 += BUFFER[i1];
for(t2=0;i1<i2;i1++)
	t2 += BUFFER[i1];

return( TW ? (t1>2*t2) : (t1>t2) );
}

/* FOOT - ���᫨�� �᫮ ���  						*/
INT FOOT( BYTE *RASTER, INT Wx, BYTE NWIDTH, BYTE NLENGTH,
		BYTE HARD_FILTER)
{
INT i,old,d,l,k;
BYTE c,curr,first,second;
memset(LOCAL,0,50);
memset(LOCAL_W,0,50);
FOOT_A(RASTER,Wx,NWIDTH,NLENGTH);       /* �஥��� */

d=NLENGTH;
d -= (d>>3);	/* 7/8 */
for(i=0;i<NWIDTH;i++)
	BUFFER[i] = (BUFFER[i]>=d); /* ����ਧ��� */

for(old=d=i=0;i<NWIDTH;i++)
	{
	c=BUFFER[i];
	if( old==0 && c==1 )
		d++;
	old=c;
	}         /* d - �᫮ ��� */

if( HARD_FILTER==0 || d<=2 && HARD_FILTER!=2 )
	{ /* ᫠�� 䨫��� */
	first =BUFFER[0];
	second=BUFFER[1];
	for(i=2;i<NWIDTH;i++)
		{
		curr=BUFFER[i];
		if( first==1 && second==0 && curr==1 )
			BUFFER[i-1]=1;
		first  =  second;
		second = curr;
		}
	}
else
	{ /* ᨫ�� 䨫��� */
	first =BUFFER[0];
	second=BUFFER[1];
	for(i=2;i<NWIDTH;i++)
		{
		curr=BUFFER[i];
		if( first==1 && second==0 && curr==1 )
			BUFFER[i-1]=1;
		if( first==0 && second==1 && curr==0 )
			BUFFER[i-1]=0;
		first  =  second;
		second =  curr;
		}
	}
	/* ��䨫��஢��� */

for(old=k=l=i=0;i<NWIDTH;i++)
	{
	c=BUFFER[i];
	if( old^c )
		{
                if( c )
			l=i;			/* �ୠ�  : ��砫� ���� */
		else
			LOCAL_W[k++]=i-l;	/* ����� : �ਭ� ���� 	 */
		}
	old=c;
	}
if( old  )
	LOCAL_W[k++]=i-l;   /* ��᫥���� �窠 �ୠ� : �ਭ� ���� */

for(old=d=l=k=i=0;i<NWIDTH;i++)
	{
	c=BUFFER[i];
	if( old^c )
		{
		d++;
		if( d%2 )
			l=i;			/* ��砫� ���� 	*/
		else
			{
			LOCAL[k++]=(l+i)>>1;   /* ����� ���� 	*/
			}
		}
	old=c;
	}
if( old )
        {
	LOCAL[k++]=(l+i)>>1;   /* ����� ��᫥���� ���� */
        d++;
        }
d >>= 1;  /* d - �᫮ ᪠窮� */

if( d!=2 )
	return(d);

/* 2 ���� */
for(i=1;i<NWIDTH;i++)
	if( BUFFER[i]==0 && BUFFER[i-1]==1 )
		break;
end1 = (BYTE)i;	 /* ����� 1-�� ���� */
for(i=NWIDTH-2;i>=0;i--)
	if( BUFFER[i]==0 && BUFFER[i+1]==1 )
		break;
beg2 = (BYTE)i;	 /* ��砫� 2-�� ���� */

return(2);
}

/* CenterVertInterval - �।��� ���ࢠ�� � �⮫�� 			*/
INT CenterVertInterval( BYTE *RASTER, INT Wx, INT NHEIGHT, INT Column,
			INT *up, INT *down)
{
BYTE mask = mask_byte[Column&7], c, old;
INT i,num,center,up_center;

*up=*down=-1;
RASTER += (Column>>3);
for(i=0;i<NHEIGHT && ((*RASTER)&mask);i++,RASTER+=Wx);
if( i==NHEIGHT )
	{
	*up=NHEIGHT;
        *down=0;
	return(0);			/* ���� �⮫��� ��� */
	}
else
	up_center = i?i:(NHEIGHT<<1);	/* �।��� ���孥�� ���ࢠ�� */

for(num=old=0;i<NHEIGHT;i++,RASTER+=Wx)
	{
	c = (((*RASTER)&mask)!=0);
	if( old^c )
		switch( num++)
			{
			case 0 :	/* ��砫� */
				*up 	= NHEIGHT - i;
				center 	= i;
				break;
			case 1 :      	/* ����� */
				*down  	= NHEIGHT - i;
				center += i;
				break;
			default:
				return(0);	/* ����� 2 */
			}
	old = c;
	}

switch( num )
	{
	case 0 :	/* ���孨� ���ࢠ� */
		center = up_center;
		if( *up==-1 )   *up  = NHEIGHT-0;
		if( *down==-1 ) *down= NHEIGHT-up_center;
		break;
	case 1 :	/* ������ ���ࢠ� */
		center += NHEIGHT;
		if( *up==-1 )   *up=NHEIGHT-up_center;
		if( *down==-1 )	*down=NHEIGHT-NHEIGHT;
		break;
	}

return( (NHEIGHT<<1)-center);	/* 㤢������ ����ﭨ� �� ���� ���� */
}

INT LinesWithNumIntervals(BYTE *rastr,INT Wx, INT NLENGHT, INT num)
{
INT i,n;
for(n=i=0;i<NLENGHT;i++,rastr+=Wx)
  n += (NumHorizInterval(rastr,Wx)==num);
return n;
}

INT LeftEdgeOfRightmostInt( BYTE *rst, INT Wdth)
{
INT i,j;
BYTE c,old;
BYTE         fl=0;
for( i = Wdth, rst =rst +Wdth -1, c = *rst;
     i > 0;
     i--,      rst --,             c=*rst)
     {if((!c)&& (!fl)) continue;
      for(j = 8, old = 0x01;        j>0;      j--, old = old<<1)
      {
	if ((c & old) &&(!fl)) {fl =1; continue;}
	if ((!(c&old)) &&(fl))      return 8*(i-1)+j;
      }
     };
 return (fl) ? 0 : -1;
}

