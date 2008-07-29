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

/* DIFFR.C : diskrimintion functions for russian language */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "difdefs.h"
#include "dif.h"
#include "minmax.h"
extern  Word8 broken_flag;
  Word8 rec5_flag=1,font_type=0,omni=1;
Int16  NumVertInterval(Word8 *RASTER,Int16 D_X, Int16 dy, Int16 i);
Int16  VertSum(Word8 *rastr,Int16 D_X, Int16 dy, Int16 i);
Int16  SumBits(Word8 *rastr,Int16 D_X);
Int16  NumHorizInterval(Word8 *,Int16);
Int16  FOOT(Word8 *raster,Int16 DX,Word8 dx,Word8 Ly,
    Word8 sign_filter);
Int16 FOOT3( Word8 *RASTER, Int16 Wx, Word8 START, Word8 NWIDTH, Word8 NLENGTH, Int16 SHIFT);
Int16 EndBlackInterval(Word8 *RASTER, Int16 NWIDTH);
Int16 FOOT3_2( Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NLENGTH);
Int16 FOOT_HEI( Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NLENGTH);

Int16 MinMaxLeft( Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NHEIGHT,
		Int16 *Pmin, Int16 *Pmax);
Int16 MinMaxRight( Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NHEIGHT,
		Int16 *Pmin, Int16 *Pmax);
Int16 DiskrRight(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 L);
Int16 Num2Interval(Word8 *r,Int16 D_X,Int16 dx,Int16 dy);
Int16 broken_M(Word8 * r,Int16 D_X,Int16 dy,Int16 left_lim,Int16 ll);
Int16  FOOT_A(Word8 *raster,Int16 DX,Word8 dx,Word8 Ly);
Int16 fill_center_zone(Word8 *raster,Int16 D_X,Int16 dy,
      Int16 beg, Int16 end, Int16 II);
Int16 up_down_hist_M(Word8 *rastr,Int16 D_X, Int16 Dx,Int16 dy);
Int16 small_density(Word8 *RAST,Int16 n,Int16 D_X,Int16 bw);
Int16  LeftDistance(Word8 *RASTER,Int16 dx);
Int16  RightDistance(Word8 *RASTER,Int16 dx);
Int16  SumIntervalBits(Word8 *RASTER,Int16 bx,Int16 ex);
Int16  CenterVertInterval(Word8 *,Int16 ,Int16 ,Int16, Int16 *,Int16 *);
void init_diskrim(Word8* raster,Int16 height ,Int16 width);
Int16 DiskrLeftBig(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy, Int16 L);
Int16 DiskrRightBig(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 L);

static void DiskrIN(Word8 *RASTR,Int16 D_X,Int16 dy, Int16 wb,Int16 dx);
static Int16 DiskrHorizIN(Word8 *RASTR,Int16 D_X,Int16 dy);
Int16 no_serific(Word8 *RASTR,Int16 dy,Int16 dx,Int16 wb);

#define bytlen(bits)  (REC_GW_WORD8(bits))

extern Word8 BUFFER[256];        /* ���⨪��쭠�   ��o����              */
extern Word8 LOCAL[50];          /* ���न����     ���             */
extern Word8 LOCAL_W[50];        /* �ਭ�         ���             */
extern Word8 end1,beg2;          /* ����� 1 � ��砫� 2-�� ��� ���  */
extern broken_ii;		/* 䫠� ���� �����			*/
extern Int16 dnri_hook; // bottom right hook in small russian italic II,III
extern Int16 uple_hook; // bottom left  hook in small russian italic II,III
extern Int16 up_jack  ; // upper jack

static Int16 upper_skip_lines,lower_skip_lines;
static Int16 diskr_f2,diskr_tsh,diskr_ii,
    diskr_sh,diskr_g,diskr_tsh,diskr_ju,diskr_m,diskr_ii,diskr_p,diskr_N,
    diskr_c, diskr_o, diskr_e,diskr_b,diskr_3,
    IN_N_Bonus,IN_equ,IN_P_Bonus,
    IN_I_Bonus,IN_IN_Monus,IN_dis,diskr_i,diskr_n,IN_N,IN_I,IN_M,IN_pics,
    mii;

 Int16 left_dist[4], right_dist[4], num_foot, c_or_e,d_c,d_e,
    right_max,left_max,left_line,right_line,
    left_dist_big[4], right_dist_big[4],lower_long_line;
Int16 av_tl, av_bl,av_br, rotate;
/* g-�, sh-�, b-B, k-K, ju-�, f2-���, tsh-�, ii-�, o-O, c-C, e-E,
   h-�, ja-�, z-�, ee-�, d-�, ce-�  */
Int16 fill_center,up_down_serif,up_down_serif_B,IN_horiz_dis,broken_M_pen;

static Int16 DiskrSymSh( Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NLENGTH);
static Int16 DiskrSh(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 Ly);
static Int16 DiskrLeft(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy, Int16 L);
static Int16 DiskrSh0(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 dx0);
static Int16 DiskrJ0(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 Ly,Int16 lim);
static Int16 DiskrJ(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy);
static Int16 DiskrTsh(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 Dx);
static Int16 average_br_angle(Word8 *RASTER, Int16 D_X, Int16 dx, Int16 dy,Int16 t);
static Int16 average_angle(Word8 *RASTER, Int16 D_X, Int16 dx, Int16 dy,
       Int16  (*Distance)(Word8 *, Int16), Int16 t);
static Int16 DiskrJu(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 Ly);
static Int16 DiskrimM1(Word8 *RAST,Int16 D_X,Int16 dx,Int16 dy);
static Int16 DiskrimM(Word8 *RAST,Int16 D_X,Int16 dx,Int16 dy);
static Int16 whiteMeanBitRight(Word8 *RAST,Int16 D_X,Int16 dx,Int16 meanBit);
static Int16 whiteMeanBitLeft(Word8 *RAST,Int16 D_X,Int16 meanBit);
static Int16 up_down_zones(Word8 *raster, Int16 D_X, Int16 dx, Int16 dx0,
      Int16 start1, Int16 stop1,   Int16 start2, Int16 stop2);
static Int16 DiskrVertCE(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 X,
                        Word8 let, Word8 inc);
static Int16 AngleBottomRight(Word8 *raster,Int16 D_X,Int16 hei);
static Int16 AngleTopRight(Word8 *raster,Int16 D_X,Int16 hei);
static Int16 BonusAnglesCurve(Word8 *raster,Int16 D_X,Int16 dy);
static Bool32 DiskrJuCut(Int16 nfoot, Int16 dx);

/*  clear diskrimination flags */
void init_diskrim(Word8* raster,Int16 height ,Int16 width)
{
Int16 i, D_X=bytlen(width);
Word8* r;

rotate=0;
diskr_f2=diskr_ii=
diskr_N=diskr_sh=diskr_g=diskr_tsh=diskr_ju=diskr_m=diskr_ii=diskr_p=
diskr_c=diskr_o=diskr_e=diskr_b=diskr_3=
left_dist_big[1]= right_dist_big[1]= left_dist[1]= right_dist[1]=
left_dist_big[2]= right_dist_big[2]= left_dist[2]= right_dist[2]=
left_dist_big[3]= right_dist_big[3]= left_dist[3]= right_dist[3]=
num_foot= c_or_e=d_c=d_e=
fill_center=IN_dis=diskr_i=diskr_n=IN_equ=IN_N=IN_I=IN_M=
IN_pics=up_down_serif=up_down_serif_B=IN_horiz_dis=
broken_M_pen=
lower_long_line=right_max=left_max=-1;
av_tl=av_bl=av_br=-1;
mii=-101;

IN_N_Bonus=0;
IN_P_Bonus=0;
IN_I_Bonus=0;
IN_IN_Monus=0;

r = raster;
for(  i=0;i<height && SumBits( r ,D_X)<3;i++,r+=D_X);
upper_skip_lines = i;

r = raster + D_X*(height-1);
for(  i=0;i<2 && SumBits( r ,D_X)<3;i++,r-=D_X);
lower_skip_lines = i;

return;
}

Bool32 LeftHole(Word8 *rastr, Int16 D_X, Int16 Dx, Int16 Hy)
{
int i,n,t, mi, ma;

if( Hy>10 )
    {
    i=Hy>>3;
    Hy-=i;
    }
else
    {
    i=1;
    Hy--;
    }
n=0;
mi=10000; ma=0;
for(;i<Hy;i++,rastr+=D_X)
    {
    t=LeftDistance(rastr,D_X);
    if( t>=0 )
        {
        if( mi>t )
            mi=t;
        if( ma<t )
            ma=t;
        n++;
        }
    }
if( !n )
    return FALSE;
if( Dx<10 )
    return FALSE;
i = 5;
return (mi>Dx/2 && abs(mi-ma)<i);
}

/* Diskrim : diskrimination function for diapason 0-255    */
/* PARAMETRS :                                             */
/*	let    - name of letter                            */
/*	raster - bit map( work raster )                    */
/*	D_X    - whidth of bit map( length bit string )    */
/*	X,Y    - coordinats of first point in raster       */
/*	dx,dy  - whidth and height work raster             */
/*							   */
/*   RETURN :   0 - good letter                            */
/*	       >0 - decreasing code                        */

Int16 Diskrim(Word8 let,Word8* raster,
      Int16 D_X,Int16 dx,Int16 dy,Word8 cg_flag, Int16 inc)
{
Int16 P=0,F=0,Dx,Hy,bw, n, r;
Word8 *rastr,*rastr0;
Int16 d_l, d_r;
Int16 X=0, Y=0;
#define  step_diskr 20

rotate= (inc>180) ;
if( upper_skip_lines )
	{
	raster += bytlen(D_X)*upper_skip_lines;
	dy-=upper_skip_lines;
	}
if( lower_skip_lines )
	{
	dy-=lower_skip_lines;
	}

if( dy<8 || dx<3 )
	return(step_diskr*10);

D_X = bytlen(D_X);
Dx = dx + (X&7);
bw = bytlen(Dx);
rastr0= raster + Y*D_X+(X>>3);
rastr = rastr0 + D_X*(dy>>2);
Hy = dy-2*(dy>>2);
d_l = (X&7)+(dx>>2);
d_r = ((bytlen(Dx))<<3)-dx-(X&7)+(dx>>2);

switch( let ){
// russian small & capital E, Ze, 3
case '3' :
case (Word8)'�' :  case (Word8)'�' :
case (Word8)'�' :  case (Word8)'�' :
    if( diskr_3<0 )
       {
       if( LeftHole(rastr, D_X, Dx, Hy) )
            { // need mount on the central zone
            P+=60;
            }

       diskr_3 = P;
       }
       else P = diskr_3;
    break;
// russian small & capital B
case (Word8)'�' :      case (Word8)'�' :
    if( diskr_b<0 )
       {
       if( !DiskrRight(rastr0, D_X, Dx, dy,1) )
            { // need pimple
            //if( BonusAnglesCurve(rastr0,D_X,dy)<2 )
                P+=9*1;
            //else
            //    P+=step_diskr;
            }

       diskr_b = P;
       }
       else P = diskr_b;
    break;
// russian e
case (Word8)'�' :
    if( diskr_e<0 )
       {
       if( (n=DiskrVertCE(rastr0, D_X, dx, dy, X,(Word8)'�',(Word8)inc))>2  )
        P+=(n-2)*step_diskr;
       diskr_e = P;
       }
       else  P = diskr_e;
    break;
// russian o,O
//  case '0' :
  case (Word8)'�' :  case (Word8)'�' :
    if( diskr_o<0 )
       {
       if( DiskrRight(rastr0, D_X, Dx, dy, 2) )
        P = step_diskr;
       diskr_o = P;
       }
       else  P = diskr_o;
    break;
// russian c,C
  case (Word8)'�' :  case (Word8)'�' :
    if( diskr_c<0 )
       {
       if( !DiskrRight(rastr0, D_X, Dx, dy, 2) )
        P = step_diskr;
        if( (n=DiskrVertCE(rastr0, D_X, dx, dy, X,(Word8)'�',(Word8)inc))!=0 )
          P+=n*step_diskr;
       diskr_c = P;
       }
       else  P = diskr_c;
    break;
// capital N
  case (Word8)'N' :
		if( diskr_N<0 )
		{
        Word8 rasterN[4096];
        int i,ii,iii;

        for(iii=D_X*(dy-1),ii=i=0;i<dy;i++,ii+=D_X,iii-=D_X)
            memcpy(rasterN+iii,raster+ii,D_X);
        rastr0= rasterN + Y*D_X+(X>>3);
        rastr = rastr0 + D_X*(dy>>2);
        F = FOOT(rastr, D_X,(Word8)Dx, (Word8)Hy,1);
		if( F!=2 || MIN(LOCAL_W[0],LOCAL_W[1])>3 && beg2-end1<3 )
			{
			if( dy>13 )
				F=FOOT(rastr0+2*D_X, D_X,(Word8)Dx, (Word8)(dy-4),0);
			else
				F=FOOT(rastr0, D_X,(Word8)Dx, (Word8)dy,0);
			}
		if( F!=2 )
			{
			if( small_density(rastr,Hy,D_X,bw) )
				P = 6*step_diskr;
			else
				P += step_diskr;
                        if( F==3 )
				P +=6*step_diskr;
			}
		   else
		   {
           IN_dis=-1;
		   DiskrIN(rastr0,D_X,dy,bw,dx);
		   IN_dis=-1;
           if( 2*LOCAL[0]>5*LOCAL_W[0] && 2*(dx-LOCAL[1])<3*LOCAL_W[1])
            P += 2*step_diskr;
		   if( IN_I<3 )
			P += MIN(2*(7-IN_I+IN_equ) * step_diskr,160)/2;
		   else if( IN_I==3 && IN_equ>2 )
			P += IN_equ*step_diskr;
		   //if( IN_I>10 && IN_M==0 )
            //P += 40;
		   }

      if( inc>0 )  // OLEG : ERECTION conditions : 09-12-95 07:29pm
        P >>= 1;

		diskr_N = P;
		}
		else P=diskr_N;
        IN_dis=-1;
        IN_IN_Monus=0;
        IN_pics=1;
        IN_M=0;
		break;

// capital & small I/I
  case (Word8)'�' :  case (Word8)'�' :
		if( diskr_i<0 )
		{
		F = FOOT(rastr, D_X,(Word8)Dx, (Word8)Hy,1);
        if( F==2 && LOCAL[1]*2<=Dx )
            {
            diskr_i = P=120;
    		break;
            }
		if( F!=2 || MIN(LOCAL_W[0],LOCAL_W[1])>3 && beg2-end1<3 )
			{
			if( dy>13 )
				F=FOOT(rastr0+2*D_X, D_X,(Word8)Dx, (Word8)(dy-4),0);
			else
				F=FOOT(rastr0, D_X,(Word8)Dx, (Word8)dy,0);
			}
		if( F!=2 )
			{
			if( small_density(rastr,Hy,D_X,bw) )
				P = 6*step_diskr;
			else
				P += step_diskr;
                        if( F==3 )
				P +=6*step_diskr;
			}
		   else
		   {
			   /*
       if( rotate && dnri_hook )
        fill_center_zone(rastr+D_X*(Hy>>2),(Int16)D_X,(Int16)(Hy-(Hy>>2)),(Int16)end1,(Int16)beg2,0);
      else
        fill_center_zone(rastr,D_X,Hy,end1,beg2,0);
		*/
		   DiskrIN(rastr0,D_X,dy,bw,dx);
		   /*
		   if( fill_center==0 )
			{
			if( broken_flag )
				{
				if( IN_I<=3 || IN_pics==0 )
					P += 2*step_diskr;
				}
			else
				P += 8*step_diskr;
			}
			*/
           if( 2*LOCAL[0]>5*LOCAL_W[0] )
            P += 2*step_diskr;
		   if( IN_I<3 )
			P += MIN(2*(7-IN_I+IN_equ) * step_diskr,160)/2;
		   else if( IN_I==3 && IN_equ>2 )
			P += IN_equ*step_diskr;
		   /*
      if( IN_I>=9 )
        { // �祭� ����ਧ��⠫쭠� ��४������
        if( (F=up_down_hist_M(rastr0+D_X, (Int16)D_X,(Int16)Dx, (Int16)(dy-2)))>0 )
          P += F*step_diskr>>2;
        if( LOCAL[1]>(Dx>>1) &&
        broken_M(rastr0+2*D_X, D_X,(Int16)(dy-4),(Int16)(LOCAL[0]-LOCAL_W[0]/2),
          (Int16)(LOCAL[1]-LOCAL_W[1]/2)) )
          P += 4*step_diskr;
        }
		   */
		   }

      if( inc>0 )  // OLEG : ERECTION conditions : 09-12-95 07:29pm
        P >>= 1;
      if(     IN_I_Bonus && broken_flag && (broken_ii ||
			!IN_IN_Monus &&
			Num2Interval(rastr0+2*D_X, (Int16)D_X,(Int16)Dx, (Int16)(dy-4))) )
			P =(IN_I_Bonus==2)?-254:-250;

		diskr_i = P;
		}
		else P=diskr_i;
		break;
// capital & small H
  case (Word8)'�' :  case (Word8)'�' :
		if( diskr_n<0 )
		{
		F =FOOT(rastr, D_X,(Word8)Dx, (Word8)Hy,1);
		if( F!=2 || MIN(LOCAL_W[0],LOCAL_W[1])>3 && beg2-end1<3 )
			{
			if( dy>13 )
				F=FOOT(rastr0+2*D_X, D_X,(Word8)Dx,(Word8)(dy-4),0);
			else
				F=FOOT(rastr0, D_X,(Word8)Dx, (Word8)dy,0);
			}
		if( F!=2 )
			P = 6*step_diskr;
		else
		   {
			/*
      if( rotate && dnri_hook )
        fill_center_zone(rastr+D_X*(Hy>>2),(Int16)D_X,(Int16)(Hy-(Hy>>2)),(Int16)end1,(Int16)beg2,0);
      else
        fill_center_zone(rastr,D_X,Hy,end1,beg2,0);
		*/
		   DiskrIN(rastr0,D_X,dy,bw,dx);
		   if( DiskrHorizIN(rastr0,D_X,dy) )
			{   // ��ୠ� ��४������
			IN_N=3;
			IN_I=2;
			}
		   /*
		   if( fill_center==0 )
			{
			if( broken_flag )
				{
				if( IN_N>=3 || IN_pics==0 )
					P += 2*step_diskr;
				}
			else
				P += 8*step_diskr;
			}
		   */
		   if( IN_N>3 )
			P += MIN(IN_N * step_diskr,160)/2;
		   /*
		   if( DiskrRight(rastr0, (Int16)D_X, (Int16)Dx, (Int16)dy,(Int16)(dy>22?3:2)) )
			P += 3*step_diskr;
		   if( omni )
			{
			if( LOCAL_W[0]>(LOCAL_W[1]<<1) &&
			(LOCAL_W[1]>1 || LOCAL_W[1]==1 && LOCAL_W[0]>3 ) )
				P += 2*step_diskr;
			}
			*/
		   }

    if( IN_N_Bonus && broken_flag && (broken_ii ||
			!IN_IN_Monus &&
			Num2Interval(rastr0+2*D_X, (Int16)D_X,(Int16)Dx, (Int16)(dy-4))) )
			P =(IN_N_Bonus==2)?-254:-250;

		diskr_n = P;
		}
		else P=diskr_n;
		break;
// capital & small II
  case (Word8)'�' :  case (Word8)'�' :
    if( diskr_p )
      {
      if( dy>13 )
        F=FOOT(rastr0+2*D_X, D_X,(Word8)Dx, (Word8)(dy-4),0);
      else
        F=FOOT(rastr0, D_X,(Word8)Dx, (Word8)dy,0);
      if( F!=2 )
        P = 6*step_diskr;
      else
        { // F==2
        if( rotate && (dnri_hook/*||dy<22&&up_jack>1*/) )
          fill_center_zone(rastr+D_X*(Hy>>2),D_X,(Int16)(Hy-(Hy>>2)),end1,beg2,1);
        else
          //fill_center_zone(rastr,D_X,Hy,end1,beg2,0);
          fill_center_zone(rastr+D_X*(Hy>>2),D_X,(Int16)(Hy-(Hy>>2)),end1,beg2,1);
        {
        Int16 f_c=fill_center;
        DiskrIN(rastr0,D_X,dy,bw,dx);
        if( !(rotate && (dnri_hook/*||dy<22&&up_jack>1*/)) )
          f_c = fill_center;
        if( f_c==1 )
          P += 8*step_diskr;
        }
      }

      if( (n=up_down_zones(rastr0,D_X,Dx,dx,0,(Int16)(dy>>2),Hy,dy))!=0 )
        {
        if( omni )
        {
        if( n!=1 )
          P += 4*step_diskr*n;
        }
        else
        { /* no omni  */
        if( !broken_flag || n==2 )
          P += 4*step_diskr*n;
        else
          P += 1*step_diskr;
        }
        }

      if(   IN_P_Bonus && broken_flag && (broken_ii ||
        !IN_IN_Monus &&
        Num2Interval(rastr0+2*D_X, D_X,Dx, (Int16)(dy-4))) )
          P =(IN_P_Bonus==2)?-254:-250;

      diskr_p = P;
      }
    else P = diskr_p;
    break;
// capital & small III
  case (Word8)'�' :  case (Word8)'�' :
    if( diskr_sh<0 )
       {
       FOOT(rastr, D_X,(Word8)Dx, (Word8)Hy,0);
       if( rotate ) // OLEG : ERECTION conditions : 09-20-95
        {
/*
        F=FOOT3(rastr, D_X, uple_hook?LOCAL[0]-LOCAL_W[0]/2:0 ,
                            dnri_hook?LOCAL[2]+LOCAL_W[2]/2:Dx, Hy,Hy<10?1:2);
*/
        if( F!=3 )
          P  = 10*step_diskr;
        }
      else
        {
        if( (F=FOOT3(rastr, D_X, 0, (Word8)Dx, (Word8)Hy,2))!=3 )
          P  = 10*step_diskr;
        else
          P += (step_diskr>>1)*DiskrSymSh(rastr, D_X, (Word8)Dx, (Word8)Hy);
        }
       if( inc<=0 && !broken_flag && DiskrSh0(rastr0, D_X, Dx, dy, dx)==0 )
        P +=step_diskr;
       F = FOOT(rastr, D_X,(Word8)Dx, (Word8)Hy,0);
       // OLEG : ERECTION conditions : 09-20-95 08:34pm
       if( inc>0 && dnri_hook )
        {
        if( F>1 && DiskrSh(rastr, D_X, (Int16)(LOCAL[2]+LOCAL_W[2]/2), Hy) )
          P += step_diskr;
        }
       else
        {
        if( F>1 && (n=DiskrSh(rastr, D_X, Dx, Hy))!=0 )
          P += n*step_diskr;
        }
       if( F!=3  )
        P += 12*step_diskr;
       if( DiskrLeft(rastr0, D_X, Dx, dy,2) )
        P += step_diskr/2;
       if( DiskrRight(rastr0, D_X, Dx, dy,2) )
        P += step_diskr/2;
       if( FOOT3_2(rastr0,D_X,(Word8)Dx,(Word8)dy) )
        P += step_diskr*3;
       diskr_sh = P;
       P=MAX(P,0);
       }
       else  P = diskr_sh;
    break;
// capital & small >I<
    case (Word8)'�' :  case (Word8)'�' :
    if( diskr_g<0 )
       {
       if( !DiskrLeftBig(rastr0, D_X, Dx, dy,2) )
        P+=3*step_diskr;
       if( !DiskrRightBig(rastr0, D_X, Dx, dy,2) )
        P+=3*step_diskr;
       F = FOOT(rastr, D_X,(Word8)Dx, (Word8)Hy,0);
       if( F!=3 && (n=DiskrJ0(rastr, D_X, Dx, Hy,(Int16)(dy<18?4:5)))!=0 )
        { /* middle tail have'nt 3-interval lines */
        if( !DiskrJ(rastr0, D_X, Dx, dy) )
          P+=2*n*step_diskr;
        }
       if( F!=3 && (n=DiskrJ0(rastr0, D_X, Dx, Hy,(Int16)(dy<18?2:3)))!=0 )
        { /* upper tail have'nt 3-interval lines  */
        if( !DiskrJ(rastr0, D_X, Dx, dy) )
          P+=2*n*step_diskr;
        }
       diskr_g = P;
       }
       else P = diskr_g;
    break;
// capital & small III,
    case (Word8)'�' :  case (Word8)'�' :
    if( diskr_tsh<0 )
       {
       F= ((Word8)let==(Word8)'�' )?4:2;
       if( (F=FOOT(rastr0+F*D_X, D_X,(Word8)Dx,(Word8)Hy,0))!=3 )
        P = 10*step_diskr;
       else
        {
        P += (step_diskr>>1)*DiskrSymSh(rastr, D_X, (Word8)Dx, (Word8)Hy);
        if( DiskrTsh(rastr0+D_X,D_X,dx,dy,Dx)==1 )
          P += 3*step_diskr ;
        }
      if( average_br_angle(rastr0,D_X,Dx,dy,0)>d_r )
        P += 4*step_diskr;
      P=MAX(P,0);
      diskr_tsh = P;
      }
    else  P = diskr_tsh;
    break;
// capiatl & small IO
    case (Word8)'�' :  case (Word8)'�' :
		//{
		//Int32 ret=DIF_GetNoCutPoint(rastr0, (Word8)dx, (Word8)dy);
		//}
    if( diskr_ju<0 )
       {
       r=FOOT_HEI( rastr0, D_X, (Word8)dx, (Word8)dy);
       if( DiskrJuCut(r,dx) && r>1)
            P += 3*step_diskr;
       if( DiskrLeft(rastr0, D_X, Dx, dy,2) )
            P += 3*step_diskr;
       if( DiskrRight(rastr0, D_X, Dx, dy,2) )
            P += 3*step_diskr;
       if( (n=DiskrJu(rastr, D_X, Dx, Hy)) )
            P += n*step_diskr;
       diskr_ju = P;
       }
       else P = diskr_ju;
    break;
// capital & small M
    case (Word8)'�' :  case (Word8)'�' :
      if( diskr_m<0 )
      {
      if( mii<-100 ){
         if(broken_flag)
            mii = DiskrimM1(rastr0, D_X, dx, dy );
         else
            mii = DiskrimM(rastr0, D_X, dx, dy );
      }
    if(mii>0)
      P+= mii*step_diskr;
    if(mii==0)
             P+= 5*step_diskr;

    if( dy>13 )
      F=FOOT(rastr0+2*D_X, D_X,(Word8)Dx, (Word8)(dy-4),0);
    else
      F=FOOT(rastr0, D_X, (Word8)Dx, (Word8)dy,0);

                   if( F==2 )
      {
      DiskrIN(rastr0,D_X,dy,bw,dx);
      if( LOCAL[0] > dx/4)
        P >>=2 ;
      P += IN_M;
      }

                        diskr_m = P;
      }
    else  P = diskr_m;
    break;
// capital & small bl
    case (Word8)'�' :  case (Word8)'�' :
    if( diskr_ii<0 )
      {
      if( mii<-100 )
          {
          if(broken_flag)
             mii = DiskrimM1(rastr0, D_X, dx, dy );
          else
             mii = DiskrimM(rastr0, D_X, dx, dy );
          }
      if(mii<0)
         P += (-mii)*step_diskr;
      if(mii==0)
         P+= 5*step_diskr;

      diskr_ii = P;
      }
    else  P = diskr_ii;
    break;
 default:
    break;
 }
return(P & 0xFFFF);
}



Int16 small_density(Word8 *RAST,Int16 n,Int16 D_X,Int16 bw)
{
Int16 i,l,w,d;
Int16 b = bw << 3;

if( !omni && font_type==0 )
	return(1);

for(l=i=0;i<n;i++,RAST+=D_X)
	{
	w = b - RightDistance(RAST,bw) - LeftDistance(RAST,bw);
	d = SumBits(RAST,bw);
	l += (d>w-2);
	}

return( l<=(n/3) );
}

Int16 no_serific(Word8 *RASTR,Int16 dy,Int16 dx,Int16 wb)
{
Int16 l0=VertSum(RASTR,wb,dy,0);
Int16 l1=VertSum(RASTR,wb,dy,1);
Int16 l2=VertSum(RASTR,wb,dy,2);
Int16 r0=VertSum(RASTR,wb,dy,(Int16)(dx-1));
Int16 r1=VertSum(RASTR,wb,dy,(Int16)(dx-2));
Int16 r2=VertSum(RASTR,wb,dy,(Int16)(dx-3));
dy -= 2;
if( l0<dy && l1<=dy && l1>dy-2 && l2>dy )
	l1=l2;
if( r0<dy && r1<=dy && r1>dy-2 && r2>dy )
	r1=r2;
//return ( l0>dy || l1>dy ) && ( r0>dy || r1>dy ) ;
return 1;
}

Int16 vert_stairs(Int16 arr[], Int16 lim)
{
Int16 i,old,jmp;
for(jmp=0,i=1,old=arr[0];i<lim;i++)
	{
	if( arr[i]==-1 )
		continue;
	if( old<arr[i] )
		jmp++;
	if( old>arr[i] )
		return 0;
	old = arr[i];
	}
return ( jmp );
}

/***************************************************************************/
/*                                                                         */
/*  �����頥�   �業�� �����⠭�� �।�� ���ࢠ��� ��ફ����� ��       */
/*                                                                         */
/***************************************************************************/
static void DiskrIN(Word8 *RASTR,Int16 D_X,Int16 dy,Int16 bw,Int16 dx)
/***************************************************************************/
/****     *RASTR     㪠��⥫�   ��  ���ᨢ                         ********/
/****	   dy        k�����⢮  ��ப                              ********/
/****      D_X       ������⢮  ���⮢  �  ��ப�                  ********/
/***************************************************************************/
{  Word8  n[256],hist[256];
   Int16   ua[256],da[256];
   Int16  i,n2=dy-2*(dy>>2),n4,mean,fine;
   Int16  incr,decr,old,neue,equ;
   Int16  l=beg2-end1-1,l_real,t,jump,rmin,rmax;
   Int16  ol=1,or=1;  /* ����� ᫥�� � �ࠢ� */
   Word8 *RAST ,*R;


n4 = MAX(dy/4,(LOCAL_W[0]+LOCAL_W[1])/4);
if( n4>dy/3 ) n4=dy/4;
n2 = dy - (n4<<1);
RAST = RASTR+D_X*n4;

if( IN_dis>0 )
	return;
IN_IN_Monus=0;
IN_pics=1;
IN_M=0;

if( l+ol+or<2 && dy>19 )
	{
	if( small_density(RAST,n2,D_X,bw) )
		{			/* ��� ������� */
		IN_N=4;
		IN_I=2;
		}
	else
		{			/* �������	*/
		IN_N=4;
		IN_I=3;
		}
	IN_dis=1;
	IN_equ=0;
	return;
	}

memset(hist,0,dy);
if( l<3 )
	{	/* �⬥���� ������ */
	or=ol=0;
	l=beg2-end1+1-ol-or;
	}
if( l>3 )
{
Int16 up_space=-1, down_space=-1;
Int16 up_fill=0,down_fill=0,d;
for(R=RAST,i=n4;i<=dy-2;i++,R+=D_X)
	{
	d=SumIntervalBits(R,(Int16)(end1+ol),(Int16)(beg2-or+1))/3;
	hist[i]=(Word8)d;
	if( d==l && !up_fill )
		up_fill=i;
	if( d==l && i<n4+n2 )
		down_fill=i;
	}

if( up_fill && down_fill && up_fill>n4 &&
	(hist[up_fill-1]==0||hist[up_fill-2]==0) &&
	(hist[down_fill+1]==0||hist[down_fill+2]==0) )
	{
	IN_N=3;
	IN_I= 2;
	IN_dis=1;
	IN_equ=1;
	return;
	}

for( old=hist[n4],i=n4+1;i<=n2;i++)
	{
	neue = hist[i];
	if( up_space==-1 )
	if( old==1 && neue>=l && hist[i+1]>=l ||
	    old==0 && neue>=l-1 && hist[i+1]>=l )
	    {
	    if( NumHorizInterval(RASTR+D_X*(i+1),bw)==1 )
        {
        Int16 j,d;
        up_space = (neue==l ? 0 : 1);

        for(j=i+1;j<dy-2 && hist[j]>=l-1;j++);
        if( j<dy-2 )
          {
          for(d=0;j<dy-2;j++)
            d+=(hist[j]<hist[j-1]);
          if( d>2 )
            {
            up_space=-1;
            break;
            }
          if( d<3 )
            {
            down_space=0;
            break;
            }
          }
      }
  }
	if( down_space==-1 )
	if( neue==1 && old>=l && hist[i-2]>=l ||
	    neue==0 && old>=l-1 && hist[i-2]>=l )
	    {
	    if( NumHorizInterval(RASTR+D_X*(i-2),bw)==1 )
        down_space = (old==l ? 0 : 1);
	    }
	old = neue;
	}

if( up_space!=-1 && down_space!=-1 )
	{
	IN_N=3;
	IN_I= MIN(up_space,down_space);
	IN_dis=1;
	IN_equ=2;
	return;
	}
memset(hist,0,dy<<1);
} /* end of horiz study */

if( no_serific(RASTR,dy,dx,bw) )
	{
	n4 = dy>17 ? 4 : 2;
	n2 = dy - (n4<<1);
	RAST = RASTR+D_X*n4;
	}
memset(ua,0xFF,dy<<1);
memset(da,0xFF,dy<<1);
i = end1+ol-1;
n[i] =(Word8) CenterVertInterval( RAST, D_X, n2, i,&ua[i],&da[i] );
				/* ����᭮� ���� ����� 		*/
for(mean=l_real=0,i=end1+ol;i<=beg2-or;i++)
	{	/* ⠡��� ���⮢ �।�� ���⨪����� ���ࢠ��� 	*/
	n[i] =(Word8)CenterVertInterval( RAST, D_X, n2, i,&ua[i],&da[i] );
	mean += n[i];
	if( n[i] )              /* mean	  - �㬬�   ����⮢		*/
		l_real++;	/* l_real - �᫮ ���㫥��� ����⮢ 	*/
	}
n[i] = (Word8)CenterVertInterval( RAST, D_X, n2, i,&ua[i],&da[i]);
				/* ����᭮� ����� 			*/
if( l!=l_real && (l_real==2 || (n[end1]|n[end1+1]) && (n[beg2]|n[beg2-1])) )
	{           	/* ������⢨� ��४������ 			*/
	IN_N_Bonus=2;
	IN_I_Bonus=2;
	if( l_real==2 )
		IN_P_Bonus=1;
	}
if( l_real<=1 && ((n[end1]==0&&n[end1+1]==0) || (n[beg2]==0&&n[beg2-1]==0)) )
	{           	/* ������⢨� ��४������ 			*/
	IN_N_Bonus=1;
	IN_P_Bonus=1;
	IN_I_Bonus=1;
	if( n[end1]==0 && n[end1+1]==0 && n[beg2]==0 && n[beg2-1]==0 )
		{
		IN_P_Bonus=2;
		IN_N_Bonus=1;
		IN_I_Bonus=1;
		}
	}

if( no_serific(RASTR,dy,dx,bw) )
	{	/* ����� ������ � ���ࢠ� ���� [dy/4,dy-dy/4] */
  Int16 nn4,nn2,h;
	nn4 = MAX(dy>>2,(LOCAL_W[0]+LOCAL_W[1])>>1);
  if( nn4>dy/3 ) nn4=dy/4;
  nn2 = dy - (nn4<<1);
  RAST = RASTR+D_X*n4;
	for(mean=l_real=0,i=end1;i<=beg2;i++)
		{
		h = n2+n4-(n[i]>>1);
		if( h<nn4 || h>nn4+nn2 )
			n[i]=0;
		else
			{
			n[i] += ((nn2+nn4-n2-n4)<<1);
			if( n[i]>=(nn2<<1) )
				n[i]=0;
			else if( n[i] &&
				 (i!=end1||i==end1&&ol==0) &&
				 (i!=beg2||i==beg2&&or==0) )
				{
        mean += n[i];
				l_real++;
				}
			}
		}
	n2=nn2;
	n4=nn4;
	}
if( l_real<4 )
	 {
	 i = beg2-or+1;
	 if( or && n[i] && VertSum(RAST, D_X, n2, i)<n2-1 &&
		NumVertInterval(RAST, D_X, n2, i)==1 )
		{	/* ���뢠�� ��᫥���� ����� */
		mean += n[i];
		or--;
		l_real++;
		l++;
		}
	 i = end1+ol-1;
	 if( ol && n[i] && VertSum(RAST, D_X, n2, i)<n2-1 &&
		NumVertInterval(RAST, D_X, n2, i)==1 )
		{	/* ���뢠�� ��᫥���� ����� */
		mean += n[i];
		ol--;
		l_real++;
		l++;
		}
	 }
if( l_real<=1 )
{
Int16 dy1=n2/*dy>>1*/,nn,mm,mm1,minup,mindown,zaz;
Word8 *rrrr,*rrrr1;
zaz = beg2 - end1;
for(	minup=mindown=zaz, rrrr=RASTR, rrrr1=RASTR+(dy-1)*D_X, i=0;
	i<3;	i++, rrrr+=D_X, rrrr1-=D_X)
	{
	mm = zaz-SumIntervalBits(rrrr,end1,beg2)/3;
	if( minup>mm )
		minup = mm;
	mm1 = zaz-SumIntervalBits(rrrr1,end1,beg2)/3;
	if( mindown>mm1 )
		mindown = mm1;
	nn=dx-SumBits(rrrr,bw);
	if( nn<2 )
		break;
	}
if( i<3 || (minup*2<mindown && minup*3<zaz && zaz>3) )
	{ /* ���� ������ ���誠 */
	IN_N_Bonus=IN_I_Bonus=1;IN_P_Bonus=2;
	}
else
	{
	if( (nn=n[end1+ol])>0 )
		{
		IN_N_Bonus=IN_I_Bonus=IN_P_Bonus=1;
		if( abs(nn-dy1)<3 )
			IN_N_Bonus=2;
		else if( nn<dy1-2 )
			IN_I_Bonus=2;
		}
	else	if( (nn=n[beg2-or])>0 )
		{
		IN_N_Bonus=IN_I_Bonus=IN_P_Bonus=1;
		if( abs(nn-dy1)<3 )
			IN_N_Bonus=2;
		else if( nn>dy1+2 )
			IN_I_Bonus=2;
		}
	}
}
{
Int16 z=beg2-end1+1;
if( z>4 && l_real*2>z )
	IN_IN_Monus=1;	/* � ��४������ ࠧ�� � �����쪨� ! */
if( 	l_real>4 	|| 	l-l_real<=3 && l>5 ||
	l_real==4 && fill_center ||
	l_real<2 && z<4 && n4<6 ||
	z>10 && l_real<3 )
	{
    if( l_real>1 )
	    IN_P_Bonus=0;
    /*IN_P_Bonus=*/IN_I_Bonus=IN_N_Bonus=0;
	}

}

if( l_real>1 )
	{
	for(i=end1+ol;i<=beg2-or;i++)
		if( (neue=n[i])!=0 )
			hist[ neue ]++;

	mean=mean/l_real+((mean%l_real)>(l_real>>1));
				/* mean	  - �।��� �����		*/

	if( hist[mean-1]>l_real-2 )
		mean--;
	if( hist[mean+1]>l_real-2 )
		mean++;

if( l_real!=l && !(l_real==l-1 && (n[end1]==0||n[beg2]==0) ) )
if( !fill_center && l_real<=4 || l_real<=3 )
	{
  Int16 an[2],en[2],ll,dy1=n2,san[2],sen[2],z;
	/* ���� ���饩 �� '�' �� �।��� ����� */
	an[0]=n[end1];
	an[1]=n[end1+1];
	en[0]=n[beg2-1];
	en[1]=n[beg2];
	for(ll=i=0;i<2;i++)
		{
		sen[i]=n[beg2-i];
		san[i]=n[end1+i];
		if( an[i]>0 )
			{
			if( abs(an[i]-dy1)>2 )
				an[i]=-1;
			else
				n[end1+i]=(Word8)dy1,ll++;
			}
		if( en[i]>0 )
			{
			if( abs(en[i]-dy1)>2 )
				en[i]=-1;
			else
				n[beg2-i]=(Word8)dy1,ll++;
			}
		}
	if( IN_I_Bonus==2 && ll==1 )
		IN_I_Bonus=1;
	if( ll>2 || ll==2 && broken_flag )
		{
		for(i=0;i<2;i++)
			{
			if( an[i]>0 )
				n[end1+i]=(Word8)dy1;
			if( en[i]>0 )
				n[beg2-i]=(Word8)dy1;
			}
		mean =  dy1;
		fill_center=1;
		IN_N_Bonus=2;
		IN_P_Bonus=IN_I_Bonus=0;
		}
	else
		{
		for(i=0;i<2;i++)
			{
			n[beg2-i]=(Word8)sen[i];
			n[end1+i]=(Word8)san[i];
			}
	/* ���� ���饩 �� '�' �� ࠧ�� ��஭� �� �।��� ����� */
		an[0]=n[end1];
		an[1]=n[end1+1];
		en[0]=n[beg2-1];
		en[1]=n[beg2];
		for(ll=i=0;i<2;i++)
			{
			z=VertSum(RAST, D_X, n2, (Int16)(end1+i));
			if( an[i]>0 && an[i]<dy1-2 && z<n4 )
				ll++;
			z=VertSum(RAST, D_X, n2, (Int16)(beg2-i));
			if( en[i]>0 && en[i]>dy1+2 && z<n4)
				ll++;
			}
#ifndef Int16ERSEPTOR
    if( ll>2 || ll==2 && broken_flag && !rotate)
#else
    if( ll>3 || ll==2 && broken_flag && !rotate)
#endif
			{
			fill_center=1;
			IN_I_Bonus=2;
			IN_P_Bonus=IN_N_Bonus=0;
			}
		}
	}
else
{
if( fill_center && l_real>l-3 && l>2 )
{
Int16 lim = (beg2-or-end1+ol)>>1;
for(t=0,i=end1+ol;i<=lim;i++)
	if( n[i]>((n2-2)<<1) )
		t++;
	if( t>=MAX(2,(l_real>>1)) )
	{		/* ��४������ ᫨誮� ��᮪� 			*/
	fill_center=0;	/* ���४�� ���� �� �������⢨� ��४������ 	*/
	IN_N=4;
	IN_I=1;
	IN_dis=1;
	return;
	}
}

if( fill_center && l_real<2 && l>4 )
	{               /* ������ ������⢨� ��४������ 		*/
	fill_center=0;	/* ���४�� ���� �� �������⢨� ��४������ 	*/
	IN_N=4;
	IN_I=1;
	IN_dis=1;
	return;
	}
}


for(old=incr=decr=fine=0,i=end1+ol,rmin=dy,rmax=0;i<=beg2-or;i++)
	if( (neue=n[i])!=0 )
		{	/* fine - �㬬� ����ﭨ� �� �।���� 	*/
		if( old==0 )
			old = neue;/* ���� ���㫥��� �����	*/
		if( neue>rmax )
			rmax=neue;
		if( neue<rmin )
			rmin=neue;
		if( neue>mean )
			fine += neue - mean;
		else
			fine += mean-neue;
		if( neue>old )
			incr++;   /* �᫮ ᪠窮� �����⠭�� 	*/
		else if( neue<old )
			decr++;   /* �᫮ ᪠窮� �뢠��� 	*/
		old = neue;
		}
if( fine && rmax-rmin<=2 && !(l_real==3 && incr==2) )
	fine=0;	/* �� ������ � 2-� ������ */
if( fine && l_real==3 && incr==2 )
	fine+=2;	/* 2 ᪠窠 � 3-� �⮫��� */

if( omni ){
Int16 fin=fine,inc=incr,dec=decr;

neue = n[end1];
if( ol && neue && neue<n[end1+1] )
	{
	if( neue>mean )
		fin += neue - mean;
	else
		fin += mean-neue;
	inc++;   /* �᫮ ᪠窮� �����⠭�� 	*/
	}

neue = n[beg2];
if( or && neue && neue>n[beg2-1])
	{
	if( neue>mean )
		fin += neue - mean;
	else
		fin += mean-neue;
	inc++;   /* �᫮ ᪠窮� �����⠭�� 	*/
	}
/* ����讥 �室�⢮ � '�' */
if( fin>10 && inc>3 && dec<1  && LOCAL[0] <= dx/4)
	IN_M=80;
else if( fin>10 && inc>2 && dec==0 && LOCAL[0] <= dx/4)
	IN_M=80;
else
	IN_M=0;
	}
if( 	abs(incr-decr)<2 && 	/* ������� ���祭�� ᪠窮� 	*/
	(incr>1 &&              /* ����� 1 �����⠭��		*/
	decr>1 ||		/* ����� 1 �뢠���		*/
	incr && decr && incr+decr<4 ) &&	/* ���� ᪠窮� */
	fine<=l			/* ����� ��ᯥ���		*/
  )
		fine=0;
if( incr<2   &&            /* ������� �����⠭��   */
    l_real>4 &&            /* �� �ப�� ��४������ */
    decr && incr+decr<4 )  /* ᪠窮� �������        */
 fine=0;
if( incr*2<decr && l_real>4 ) /* too many incr */
    fine = 0;
	if( fine>2 && incr<2 && decr>1 && l>3 )
		fine -= 2;		/* �ᥣ� 1 �����⠭��		*/
	t = (incr<=1)&&(decr<=1);
	for(i=end1+ol; n[i]==0 && i<=beg2-or;i++); /* skip empty columns */
	for(equ=incr=0,old=n[i++];i<=beg2-or;i++)
		{
		if( n[i] )
			neue=n[i];
		else
			continue;
		if( neue>old )
			incr += neue-old;
		old = neue;
		}
	if( t==0 )              /* ����� 1-�� �����⠭�� ��� �뢠��� 	*/
		fine += incr ;	/* �������� ���� �� �����⠭��	*/
	for(t=equ=i=0;i<dy;i++)
		if( hist[i]>equ )
			equ=hist[(t=i)];
	if( 	fine>1 && equ>2 && t==mean && or==0 && ol==0 &&
		n[end1]<mean && mean<n[beg2] && equ+2==l_real )
			fine=0;	/* 1-� � ��᫥���� ᪠窨 �	*/
				/* ࠧ�ࢠ���� ����, ���ࢠ�	*/
				/* ������⢠ ����� 3		*/
	if( equ>1 && fine<6 )
		{
    Int16 fineold=fine;
		t = n4 + n2 - (t>>1);
		for( RAST=RASTR+D_X*(t-2),i=t-2;i<=t+2;i++,RAST+=D_X)
			if( SumIntervalBits(RAST,end1,(Int16)(beg2+1))==
				(beg2-end1+1)*3 )
				{		/* ���� ��४������ */
				fine=0;
				break;
				}
		if( equ==2 && (ol&&n[end1+ol] || or&&n[beg2-or]) )
			fine=fineold;
		}

	if( l_real<5 && equ>2 )
		fine=0;		/* 3 �� 4(��� <4) ᮢ������ 		*/
	if( l_real>4 && equ>l_real-2 )
		fine = 0;	/* ᮢ������ l-1 �� l ����⮢		*/
	jump=0;
	if( equ==l-1 )
		{		/* �����⢥��� �ᯫ��			*/
		i=end1+ol;
		if( n[i]!=0 && n[i]<n[i+1] && n[i+2]==n[i+1] )
			{
			fine=0;	/* �����⢥��� ���� �ᯫ��		*/
			jump=1;
			}
		else
			{
			i=beg2-or;
			if( n[i-1]!=0 && n[i]>n[i-1] && n[i-2]==n[i-1] )
				{
				fine=0;
				/* �����⢥��� �ࠢ� �ᯫ��		*/
				jump=1;
				}
			}
		}
if( l_real>2 )
	{		/* ��ନ஢�� ������������ ���� 	*/
	fine <<= 5;     /* *32 ?????????????			*/
	fine /= l_real; /* ��⨭��� �ਭ� 			*/
	fine /= n2;     /* ����				*/
	}

	}
else
	{
	fine=0; 	/* l_real<2 : �� ����� �業��� ��ࠧ 	*/
	IN_dis=1;
	IN_equ=IN_N=0;
	IN_I=3;
	IN_pics=0;
	if( fill_center && l>2 )
		fill_center=0;	/* ���४�� ���� �� �������⢨� ��४������ */
	if( 	!fill_center && l_real==1 &&
		(NumVertInterval(RAST, D_X, n2, end1)==1 &&
		 VertSum(RAST,D_X,n2,end1)<n4 &&
		 n[end1] && abs(n[end1]-(dy>>1))<3 ||
		 NumVertInterval(RAST, D_X, n2, beg2)==1 &&
		 VertSum(RAST,D_X,n2,beg2)<n4 &&
		 n[beg2] && abs(n[beg2]-(dy>>1))<3) )
		fill_center=2;

	return;
	}

IN_N=IN_I = fine;	/*           ���� �� �����⠭�� 	*/
if( incr<2 && l_real>5 && decr>4 )
	{
	if( fine>6 )
		IN_N=5;
	IN_I=1;   /* similar to N */
  }
if( incr<1 && l_real>3 && decr>l_real/2 )
	{
    IN_N=6;
	IN_I=1;   /* similar to N */
    }
if( !fine && IN_M==0 && l_real>3 && decr>=l_real/3 && decr>1 )
    {
    IN_N=6;
	IN_I=1;   /* similar to M */
    }
if( fine==0 && jump )
	IN_I=3;
if( !fill_center && (l_real>3 || l_real>l-3) && l>2 && mean*4<dy*3 )
	{
	if( l_real>2 || n[end1] && n[beg2] )
#ifdef Int16ERSEPTOR
  if( l_real>5 )
#endif
  if( !rotate || l_real>3 )
  fill_center=1;  /* ���४�� ���� �� �������⢨� ��४������ */
	}
if( fine>5 && l_real==2 && !broken_flag && incr==0 && decr==1 )
	{
	IN_N=4;
	IN_I=2;
	fill_center=0;
	}
IN_dis=1;
equ -= l-2;
IN_equ = (equ>0)?2+equ:0;	/* IN_equ -���� �� ������⢮ */

if( DiskrHorizIN(RASTR,D_X,dy) )
			{   /* ��ୠ� ��४������ */
			IN_N=3;
			IN_I=2;
			}
if( omni )
	{	/* '�' ��⠥��� � '�' */
  Int16 i,le,ri,nnn=(beg2+end1+ol-or)/2;
	if( fine>15 && decr>3 || fine>20 && decr>2 ||
	    fine>10 && incr<1 && decr>3 ) //RUS_ENG_LANG
		IN_I=1;
	if( l_real>4 && fine>9 )
	{
	for(old=n[end1+ol],le=0,i=end1+ol;i<nnn;i++)
		{
		neue = n[i];
		if( neue )
			{
			if( neue<old )
				le++;
			old=neue;
			}
		}
	for(old=n[i],ri=0;i<beg2-or;i++)
		{
		neue = n[i];
		if( neue )
			{
			if( neue>old )
				ri++;
			old=neue;
			}
		}
	if( le>3 && ri>3 )
		IN_I=1;
	}
	}

{
Int16 up_skip=vert_stairs(&ua[end1],(Int16)(beg2-end1+1));
Int16 down_skip=vert_stairs(&da[end1],(Int16)(beg2-end1+1));

if( IN_I<=3 )
if( up_skip>3 && down_skip>3 ||
    up_skip>1 && down_skip>1 && up_skip+down_skip>4 )
	{
	IN_N=4;
	IN_I= 4;
	IN_dis=1;
	IN_equ=0;
	return;
	}
}

return;
} 			/* 		DiskrIN 		*/

/***************************************************************************/
Int16 DiskrHorizIN(Word8 *RASTR,Int16 D_X,Int16 dy)
/***************************************************************************/
/****     *RASTR     㪠��⥫�   ��  ���ᨢ                         ********/
/****	   dy        k�����⢮  ��ப                              ********/
/****      D_X       ������⢮  ���⮢  �  ��ப�                  ********/
/***************************************************************************/
{  Word8 n[256];
   Int16  i,j,n2=dy-2*(dy>>2),n4=dy>>2,imax,nmax,kmax;
   Int16 l = beg2 - end1 ,h;
   Word8 *RAST = RASTR+D_X*n4;


if( IN_horiz_dis>=0 )
	return(IN_horiz_dis);

if( l<4 )
	{ /* ����� ����ﭨ� */
	IN_horiz_dis=0;
	return(IN_horiz_dis);
	}

for(imax=nmax=kmax=-1,i=n4,j=0;j<=n2;j++,i++,RAST+=D_X)
	{	/* ������� ����� 	*/
	n[i] = SumIntervalBits(RAST,end1,beg2)/3;
	if( n[i]>nmax )
		{
		nmax = n[i];
		imax = i;
		kmax=1;
		}
	else if( n[i]==nmax )
		kmax++;
	}

if( imax>0 && nmax==l && kmax>1 )
	{
	for(i=imax;n[i]==nmax;i--);
	h = ( n[i-1]==0 && n[i]<3 || n[i]<2 ) ;
	for(i=imax;n[i]==nmax;i++);
	l = ( n[i+1]==0 && n[i]<3 || n[i]<2 ) ;
	}
else
	l=h=0;

return (IN_horiz_dis= (h&&l) ) ;
} 			/* 		DiskrHorizIN 		*/

Int16 fill_center_zone(Word8 *raster,Int16 D_X,Int16 dy,
      Int16 beg, Int16 end, Int16 II)
{
Int16 i,num,l,ny,d=((end-beg)>>1),p, white, w;
Word8 *r=raster;

#ifdef INTERSEPTOR
end--;beg++;
d=((end-beg)>>1);
#endif

if( fill_center>=0 )
	return( fill_center );

p = (end-beg>3 );
if( rotate )    p=0; // OLEG : ERECTION CONDITION
white=end+p-beg+1;

for(ny=num=i=0;i<dy;i++,r+=D_X)
	{
	l = SumIntervalBits(r,beg,(Int16)(end+p))/3;
	if( i==0 && l>=d )
		continue;
    w = end+p-beg-l;
	if( white>w )
        white=w;
    if( l )
		{
		num += l;   // SUM of black bits in critical lines
        //if( l>d )
		//	num+=l;
        ny++;       // num of critical lines
		}
	}

if( ny  )
	{
  if( !(rotate && (dnri_hook||II) ) )
		{
		if( end - beg < 5 )
			fill_center = ( num>ny ) ;
		else
			fill_center = ( num>(ny<<1) );
		}
	else
		{
		fill_center = 0;
    if( rotate )
      {
      if( white<2 && dnri_hook )
        fill_center = 1;
      else if( d>2 && white<d )
        fill_center = 1;
      }
		}
	}
else
	fill_center = 0;
return( fill_center );
}

Int16 up_down_hist_M(Word8 *rastr,Int16 D_X, Int16 Dx,Int16 dy)
{
Int16 i,j,d,h=dy>>1,s,t,n;
Word8 *r;

Dx =  bytlen(Dx);
for(s=j=0,i=0,r=rastr+i*D_X;i<h;j++,i++,r+=D_X)
	{
	n = NumHorizInterval( r, Dx ) ;
	s += (n==2);
	if( s>2 )               break;
	if( j>3 && s==0 )       break;
	}
if( s<2 )			return(0);

for(t=d=j=0,i=dy-1,r=rastr+i*D_X; i>=h;i--,j++,r-=D_X)
	{
	n = NumHorizInterval( r, Dx ) ;
	t += (n==3);
	d += (n==2);
	if( d>2 )		break;
	if( t>2 )   		break;
	if( j>3 && t==0 )	break;
	}

if( t<2 )			return(0);

if( s>3 && t>3 )		return( 8 );
return(4);
}

Int16 broken_M(Word8 * r,Int16 D_X,Int16 dy,Int16 left_lim,Int16 ll)
{
Int16 i,old,neue,dest,sign,fc,maxd,incr;
Word8 *rr;
if( broken_M_pen>=0 )
	return broken_M_pen;
old=RightDistance(r,D_X);
for(rr=r+D_X,i=1;i<dy;i++,rr+=D_X)
	{
	neue=RightDistance(rr,D_X);
	if( abs(neue-old)>1 )
		return (broken_M_pen=0);/* ����אַ� �ࠢ� ���� */
	old=neue;
	}
/* ��אַ� �ࠢ� ���� */
old=LeftDistance(r,D_X);
dest=old;

for(maxd=fc=sign=incr=0,dest=old,rr=r+D_X,i=1;i<dy;i++,rr+=D_X)
	{
	neue=LeftDistance(rr,D_X);
	if( neue<old )
		{
		if( neue==old-1 )
			{
			if( sign )	return (broken_M_pen=0);
			else		sign=1;
			}
		else
		return(broken_M_pen=0);/* ������⮭����� ������ ���� */
		}
	if( neue>=ll )	fc++;
	if( maxd<neue )
		maxd=neue;
  if( neue>=old  ) incr++;
	old=neue;
	}
dest = neue - dest;		/* ᪠箪 ����⮭���� ������ ���� */
if( left_lim==ll )
	left_lim=3;
return(broken_M_pen= ((dest>left_lim ||
  (dest>left_lim-2&&left_lim>5||dest==left_lim&&left_lim>4)&&incr>dy/2)
			&& fc<3 && maxd>3) );
}


Int16 Num2Interval(Word8 *r,Int16 D_X,Int16 dx,Int16 dy)
{
Int16 i,n2,p,d;
d = bytlen(dx);
for(i=1;i<3;i++)
if( 	(p=NumHorizInterval(r-D_X*i,d))==1 &&
	(n2=SumBits(r-D_X*i,d))>dx-2 )
	return(0);
for(n2=i=0;i<dy; i++, r+=D_X )
	{
	p=NumHorizInterval(r,d);
	/*  NumHorizInterval : number of intervals in line  */
	n2 += (p==2 );
	}
return ( n2==dy );
}
/* DiskrRight : check left hole */
Int16 DiskrRight(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 L)
{
Int16 sum,p,x,dl,Ly,i,p_old,curr_sum,h;
Int16 minr,maxr,ddy;
Word8 *RASTER=RASTR+D_X*(dy>>2),*R;
if( right_dist[L]>=0 )
	return( right_dist[L] );

Ly=dy-2*(dy>>2);
h=Ly;
R=RASTER;

dl=(((dx+7)>>3)<<3);
ddy = dy>30 ? (dy>>3):(dy>>2);
MinMaxRight(RASTER,D_X,(Word8)dx,(Word8)Ly,&minr,&maxr);
x = maxr - minr;
if( maxr-((dx&7)?(8-(dx&7)):0)>(dx>>1) )
	{
  right_max = maxr-minr;
  right_line=0;
	return( (right_dist[L]=1) );
	}
right_dist[L] = ( x>=L );
if( right_dist[L] )       /* big hole */
	{
	right_line=0;
	if( dy>17 )
	while( VertSum(R,D_X,h,(Int16)(dl-minr))<ddy && minr<maxr)minr++;
	for(p_old=-1,sum=curr_sum=0,i=minr ; i<=maxr ; i++ )
		{
		p = NumVertInterval(R, D_X, h, (Int16)(dl-i));
		if( p>=2 )
			{          /* ��begin 2-intervals�series of columns */
			if( p_old<2 )
				curr_sum=1;
			else curr_sum++;  /* ��account width of hole */
			if( curr_sum>L )break;
                        }
		else if( p_old>=2 )
			{      /* end 2-intervals�series of columns */
			if(  curr_sum>sum )
				sum=curr_sum;
			if( sum>=L )break;
			}
		p_old=p;
		}
  if( sum==0 && curr_sum )
		sum = curr_sum;
	right_dist[L]=( sum>=L); /* hole */
	}
else
	right_line=1;

right_max = maxr-minr;
return( right_dist[L] );
}


static Int16 DiskrSymSh( Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NLENGTH)
{
  Int16 i,old,l,k,d;
  Word8 c,w,minw=255,maxw=0;

  FOOT_A(RASTER,Wx,NWIDTH,NLENGTH);   /* projection to horiz axes */

d=(NLENGTH+1)>>1;
for(i=0;i<NWIDTH;i++)
  BUFFER[i] = (BUFFER[i]>=d); /* binarazing */

for(old=l=k=i=0;i<=NWIDTH;i++)
  {
    c = (i<NWIDTH) ? BUFFER[i] : 0;
  if( old^c )
    {
        if( c )
      l=i;      /* black : ��begin of foot */
    else
            {               /* white   : end of foot  */
            w=i-l;
            if (w>maxw)  maxw=w;
            if (w<minw)  minw=w;
            LOCAL_W[k]=w;    /* width of foot   */
            LOCAL[k]=(l+i);  /* center+1/2. Accuracy 1/2 pixel� */
            k++;
      }
    }
  old=c;
  }

  if ( k != 3 || maxw-minw>1 )
    return(0);    // enigmatic image
  i=LOCAL[2]+LOCAL[0]-(LOCAL[1]<<1);          //�assimetry
  if (i==0)
    return (-2);
  if (i<0) i=-i;
  if( i<3 && NWIDTH>22 )  i=1;  //Oleg:02-13-96: too small for wide image
  i=(i<<6)/(32+NWIDTH);
  if (i==1)
     i=0;
  return(i);
}

static Int16 DiskrSh(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 Ly)
{
Word8 *RASTER=RASTR;
Int16 i,num,n2,p,ddx;
ddx = bytlen(dx);
for(n2=num=i=0;i<Ly; i++, RASTER+=D_X )
  {
  p=NumHorizInterval(RASTER,ddx);
  /*  NumHorizInterval : number of intervals in line */
  num += ( p!=3 );
  n2 += (p==2 );
  }

if( n2 )
{ /* 2-interval lines are exist */
Int16 b=(LOCAL[0]+LOCAL[1])/2,dd=(LOCAL[1]-LOCAL[0])+(LOCAL_W[1]+LOCAL_W[0])/2;
i = Ly<<1;
i = Ly/3-(Ly>>2);
Ly -= i;
for(RASTER=RASTR+D_X*i;i<Ly;i++, RASTER+=D_X)
  {
  p =  SumIntervalBits(RASTER,b,dx)/3;
  if( p>=dd && NumHorizInterval(RASTER,ddx)==2 )
    return 4;
  }
}
return( num>2?num-2:0 );
}

/* for letters III */
static Int16 DiskrSh0(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 dx0)
{
Word8 *RASTER=RASTR+D_X*(dy-(dy>>2));
Int16 i,num,l=dx0-(dx0>>2);
if( lower_long_line<0 )
{
dx = bytlen(dx);
for(num=0,i=dy-(dy>>2);i<dy; i++, RASTER+=D_X )
  num += ( NumHorizInterval(RASTER,dx)==1 && SumBits(RASTER, dx)>l );
    /*  num : number of lines haved one long interval */
lower_long_line=num;   /* number of filled lines */
}
return( lower_long_line );
}

/*  DiskrLeft : check left hole */
Int16 DiskrLeft(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy, Int16 L)
{
Int16 sum,p,x,i,Ly,p_old,curr_sum,h;
Int16 minr,maxr;
Word8 *RASTER=RASTR+D_X*(dy>>2),*R;
if( left_dist[L]>=0 )
  return( left_dist[L] );
Ly=dy-2*(dy>>2);
h=Ly;
R=RASTER;

MinMaxLeft(RASTER,D_X,(Word8)dx,(Word8)Ly,&minr,&maxr);
if( minr && maxr )
  {
  minr--; maxr--;
  }
x = maxr - minr;
if( minr>(dx>>1) )
  {
  left_max = maxr-minr;
  left_line=0;
  return( (left_dist[L]=1) );
  }
left_dist[L]=(x>=L);
if( left_dist[L] )              /* big hole */
  {
        left_line=0;
  if( dy>17 )
  while( VertSum(R,D_X,h,minr)<(dy>>2) && minr<maxr)minr++;
  for(p_old=-1,curr_sum=sum=0,i=minr ; i<=maxr ; i++ )
    {
    p = NumVertInterval(R, D_X, h, i);
    if( p>=2 )
      {          /* begin 2-intervals�series of columns */
      if( p_old!=2 )
        curr_sum=1;
      else curr_sum++;  /* ��account width of hole */
      if( curr_sum>L )break;
                        }
    else if( p_old>=2 )
      {      /* end 2-intervals�series of columns */
      if(  curr_sum>sum )
        sum=curr_sum;
      if( sum>=L )break;
      }
    p_old=p;
    }
  if( sum==0 && curr_sum )
    sum = curr_sum;
  left_dist[L]=( sum>=L); /* hole */
  }
else
  left_line=1;
left_max = maxr-minr;
return( left_dist[L] );
}

/*  DiskrLeftBig : check big left hole� */
Int16 DiskrLeftBig(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy, Int16 L)
{
Int16 sum,p,x,i,Ly,p_old,curr_sum,h;
Int16 minr,maxr;
Word8 *RASTER=RASTR+D_X,*R;
if( left_dist_big[L]>=0 )
  return( left_dist_big[L] );

Ly=dy-2;
h =  dy ;
R =  RASTR;

MinMaxLeft(RASTER,D_X,(Word8)dx,(Word8)Ly,&minr,&maxr);
if( minr && maxr )
  {
  minr--; maxr--;
  }
x = maxr - minr;
left_dist_big[L]=(x>=L);
if( left_dist_big[L] )              /* big hole */
  {
  if( dy>17 )
  while( VertSum(R,D_X,h,minr)<(dy>>2) && minr<maxr)minr++;
  for(p_old=-1,curr_sum=sum=0,i=minr ; i<=maxr ; i++ )
    {
    p = NumVertInterval(R, D_X, h, i);
    if( p>=2 )
      {          /* ��begin 2-intervals�series of columns */
      if( p_old!=2 )
        curr_sum=1;
      else curr_sum++;  /* ��account width of hole */
      if( curr_sum>L )break;
      }
    else if( p_old>=2 )
      {      /* end 2-intervals�series of columns */
      if(  curr_sum>sum )
        sum=curr_sum;
      if( sum>=L )break;
      }
    p_old=p;
    }
  if( sum==0 && curr_sum )
    sum = curr_sum;
  left_dist_big[L]=( sum>=L); /* hole */
  }

return( left_dist_big[L] );
}

/*  DiskrRightBig : check big right hole */
Int16 DiskrRightBig(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 L)
{
Int16 sum,p,x,dl,Ly,i,p_old,curr_sum,h;
Int16 minr,maxr;
Word8 *RASTER=RASTR+D_X,*R;
if( right_dist_big[L]<0 )
{
Ly=dy-2;
h =  dy ;
R =  RASTR;

dl=(((dx+7)>>3)<<3);
MinMaxRight(RASTER,D_X,(Word8)dx,(Word8)Ly,&minr,&maxr);
x = maxr - minr;
right_dist_big[L] = ( x>=L );
if( right_dist_big[L] )       /* big hole */
  {
  if( dy<13 || VertSum(RASTR, D_X, dy, (Int16)(dl-minr))<dy-2)
  {
  if( dy>17 )
  while( VertSum(R,D_X,h,(Int16)(dl-minr))<(dy>>2) && minr<maxr)minr++;
  for(p_old=-1,sum=curr_sum=0,i=minr ; i<=maxr ; i++ )
    {
    p = NumVertInterval(R, D_X, h, (Int16)(dl-i));
    if( p>=2 )
      {          /* begin 2-intervals�series of columns */
      if( p_old<2 )
        curr_sum=1;
      else curr_sum++;  /* account width of hole */
                        if( curr_sum>L )
                          {
                          sum = curr_sum;
                          break;
                          }
                        }
    else if( p_old>=2 )
      {      /* end 2-intervals�series of columns */
      if(  curr_sum>sum )
        sum=curr_sum;
      if( sum>=L )break;
      }
    p_old=p;
    }
        if( sum==0 && curr_sum )
    sum = curr_sum;
  right_dist_big[L]=( sum>=L); /* hole */
  }
  else   right_dist_big[L]=0;  /* no hole - vert line */
  }

} /* calc right_dist */
return( right_dist_big[L] );
}

/* for letters >|< */
static Int16 DiskrJ0(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 Ly,Int16 lim)
{
Word8 *RASTER=RASTR;
Int16 i,three,n,all,ret,one;

dx = bytlen(dx);
for(one=all=three=i=0;i<Ly; i++, RASTER+=D_X )
  {
  n = NumHorizInterval(RASTER,dx);
  /*  NumHorizInterval : number of intervals in line */
  three += ( n==3 );
  all   += ( n>=3 );
  one   += ( n==1 );
  }

if( Ly>9 )
        {
  ret = (three<lim)?lim-three:0 ;
  if( all==Ly && lim>3 )  /* on middle */
                ret = 2;
        }
else
  { /* small >|< */
  if( three>=lim )
    ret = 0;
  else
    ret = (all<lim)?lim-all:0 ;
  }
if( lim<=3 && ret && one+all>Ly-3 )
  ret=0;
return( ret );
}

static Int16 DiskrJ(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy)
{
Int16 i,t,tu,td,Ly=dy>>2,ly=dy-2*Ly,p,l=dy>>1;
dx = bytlen(dx);
for(tu=i=0;i<Ly; i++, RASTR+=D_X )
  tu += ( NumHorizInterval(RASTR,dx)==3 );
for(td=t=0;i<ly; i++, RASTR+=D_X )
        {
        p = NumHorizInterval(RASTR,dx);
  t += (p==1);
  if( i<l )
    tu += (p==3);
        if( i>l )
                td += (p==3);
        }
for(;i<dy; i++, RASTR+=D_X )
  td += ( NumHorizInterval(RASTR,dx)==3 );
    /*  NumHorizInterval : number of intervlas in line */
return  (
  tu>3 && t>=2 && td>3 ||
  tu>1 && t>2 && td>1 && tu+td>3
  );
}

//***************************************************************************
//*   return       1 if stick glued to rusian D, otherwise 0                *
//***************************************************************************
static Int16 DiskrTsh(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 Dx)
{  Word8  j,n4=dy>>2,bool_foot=1;
   Word8  bit0,bit1,bit2;
   Int16            i,fine=0;
   Word8  *RAST;

//****************   check existance two hooks  ******************


   for (RAST=RASTR+(dy-3)*D_X,i=dy-3;;i--,RAST-=D_X){
      j=SumIntervalBits( RAST,(Int16)0,(Int16)dx )/3 ;
      if(  (j > 5*D_X) || (i<2*n4) ) break;
      j=(Word8)NumHorizInterval( RAST, D_X );
      if( j > 1 )  fine+=20;
   }
   if( fine < 30 ){     return ( 0 );   }

//****************    foots configuration       ******************

   bit0 = LOCAL[0] ;
   bit1 = LOCAL[1] ;
   bit2 = LOCAL[2] ;

//************   check gluing in upper left angle gluing  *************

fine=0;
   for (RAST=RASTR,i=0;i<n4;i++,RAST+=D_X){
      j=SumIntervalBits(RAST,(Int16)bit0,(Int16)bit1)/3;
      if( j >  3*(bit1-bit0)/5 )    fine+=20;
      if( j == (bit1-bit0) )        goto end;
   }
   if( fine < 40 )   { goto   bbb;}//* breaking

//******************  make histogramm   ********************************

   FOOT_A(RASTR, D_X, (Word8)Dx, (Word8)n4); bool_foot=0;

   for(i=bit0+1;i<bit1+1;i++){
      if(BUFFER[i]==0)  goto   bbb;//* breaking
   }
   goto   end;//* gluing

//************   check gluing on upper right angle ************

bbb:fine=0;
   for (RAST=RASTR,i=0;i<n4;i++,RAST+=D_X){
      j=SumIntervalBits(RAST,(Int16)bit1,(Int16)bit2)/3;
      if( j >  3*(bit2-bit1)/5 )     fine+=20;
      if( j == (bit2-bit1) )             {  return(1); }
   }
   if( fine < 40 )   goto   end;// breaking

//******************  make histogramm  ********************************

   if( bool_foot ) FOOT_A(RASTR, D_X, (Word8)Dx, (Word8)n4);
   for(i=bit1+1;i<bit2+1;i++){
      if(BUFFER[i]==0)  goto   end; // breaking
   }
   return( 1 );// gluing

end: return ( 0 );

}  // DiskrTsh


static Int16 average_br_angle(Word8 *RASTER, Int16 D_X, Int16 dx, Int16 dy,
        Int16 t)
{
if( av_br<0 )
  av_br=average_angle(RASTER+D_X*(dy-(dy>>2)),
    D_X,dx,(Int16)(dy>>2),RightDistance,t);
return(av_br);
}

static Int16 average_angle(Word8 *RASTER, Int16 D_X, Int16 dx, Int16 dy,
       Int16  (*Distance)(Word8 *, Int16), Int16 t)
{
Int16 i=0,n,p,H;
if( t==0 )
{       /* cut long lines for finding corners */
while( SumBits(RASTER,(Int16)(bytlen(dx)))>(dx>>1) && i<dy )
  {
  i++;
  RASTER+=D_X;  /* black strings */
  }
}
for(H=n=0;i<dy; i++,RASTER+=D_X)
  if( (p=Distance(RASTER,(Int16)(bytlen(dx))))>=0 )
    {
    H++;
    n+=p; /* nonzero string */
    }
return(H?n/H:-1);
}

static Int16 DiskrJu(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 Ly)
{
Word8 *RASTER=RASTR;
Int16 i,ret,r,s2,s3,n;
dx = bytlen(dx);

for(n=s2=s3=i=0;i<Ly; i++, RASTER+=D_X,n++ )
  {
  r =  NumHorizInterval(RASTER,dx);
  s2 += (r==2);
  s3 += (r==3);
  }
  // NumHorizInterval : �᫮ ���ࢠ��� � ��ப�

n = Ly/3;
ret = 0 ;
if( s3<n ) ret += n - s3;
if( !broken_flag && s2==0 ) ret += 2;
return  (ret) ;
}

static Int16 DiskrimM1(Word8 *RAST,Int16 D_X,Int16 dx,Int16 dy)
{
   Int16    n2,n4=dy>>2,meanBit=dx>>1; /* Oleg & Vova 09.03.94 */
   Int16    i,j,k,up=0,down=0,cUp=0,cDown=0;
   Int16    prev=0,byte=0;
   Word8   *r;

/*  calculate  mean  of  hole  */
   for(r=RAST+D_X,i=0;i<n4;i++,r+=D_X){
      j = NumHorizInterval( r, D_X );
      if( j == 2 ){
   if( ( j = NumHorizInterval( r+D_X, D_X ) ) ==2 ){
      r += D_X;
   }
   for(k=0;k<dx;k++){
      byte=k>>3;
      byte=*(r+byte);
      byte >>= ( 7- (k % 8) );
      byte &= 0x1;
      if( !byte && prev  && !down )  down = k;
      if(  byte && !prev && down )   up   = k;
      prev = byte;
   }
   meanBit = ( up+down+(dx>>1) )/3;
   /* for  no  wide  letters */
   if( (up-down < 5) || (dx<dy) )  meanBit = ( up+down )/2;
   break;
      }
   }

/*  calculate  heigth  of  hole  */
   r=RAST+D_X;
   byte = 0;
   prev = whiteMeanBitLeft(r,D_X,meanBit);
   for(i=1;i<dy-1;i++,r+=D_X){
      j = whiteMeanBitLeft(r,D_X,meanBit);
      if( (j == 0) && (i > n4+1) ){  break;  }
      byte += (prev-j);
      /* for  'bl */
      if( (byte < 1) && (i > n4+2) ){
   break;
      }
      prev = j;
   }
   if( i > dy-2 )  i = 2*dy/3;
   n4 = i>>1;  n2 = 2*n4;

/*  calculate  symetry  of  hole  */
   down = up = byte = 0;
   r=RAST+D_X;
   prev = whiteMeanBitLeft(r,D_X,meanBit);
   for(i=1;i<=n2;i++,r+=D_X){
      j = whiteMeanBitLeft(r,D_X,meanBit);
      if( i<=n4 ){  up   += j;  cUp++;    }
      else       {  down += j;  cDown++;  }
      /* too  wide  hole */
      if( (i>n4) && (j>dx/5) ){
   if( (cUp==0) || (cDown==0) )  return(0);
   if( up*cDown <= down*cUp )    return(4);  /* bl - too  wide  hole */
   if( byte < 1 )                return(3);  /* bl - too  wide  hole */
      }
      byte += (prev-j);
      if( (prev-j > 3) && (i>n4) )  return(5);      /* bl - too  big  jump */
      if( (byte > 1+dx/8) && (i>n4) )  return( -6 ); /* M - too  big  angle  for  cursive */
      prev = j;
   }

   if( (cUp != cDown) && (cDown) ){  down *= cUp;  down /= cDown;  }
   if( down >= up )  return(5);  /* bl - wide  hole on  the  bottom */
   if( down < up )  return(-5); /* M - wide  hole on  the  top */
   if( !cDown )  return(6);  /* bl - hole is absent */

   return(0);
}  /* DiskrM1 */

static Int16 DiskrimM(Word8 *RAST,Int16 D_X,Int16 dx,Int16 dy)
{
   Int16    n2,n4=dy>>2,meanBit=dx>>1; /* Oleg & Vova 09.03.94 */
   Int16    i,j,k,up=0,down=0,cUp=0,cDown=0;
   Int16    prev=0,byte=0;
   Word8   *r;

/*  calculate  mean  of  hole  */
   for(r=RAST+D_X,i=0;i<n4;i++,r+=D_X){
      j = NumHorizInterval( r, D_X );
      if( j == 2 ){
   for(k=0;k<dx;k++){
      byte=k>>3;
      byte=*(r+byte);
      byte >>= ( 7- (k % 8) );
      byte &= 0x1;
      if( !byte && prev  && !down )  down = k;
      if(  byte && !prev && down )   up   = k;
      prev = byte;
   }
   meanBit = ( up+down+(dx>>1) )/3;
   /* for  no  wide  letters */
   if( (up-down < 5) || (dx<dy) )  meanBit = ( up+down )/2;
   break;
      }
   }
if( down==0 && up==0 )  return(2); /* M - hole is absent */

/*  calculate  heigth  of  hole  */
   r=RAST+D_X;
   byte = 0;
   prev = whiteMeanBitLeft(r,D_X,meanBit) +
    whiteMeanBitRight(r,D_X,dx,meanBit);
   for(i=1;i<dy-1;i++,r+=D_X){
      j = whiteMeanBitLeft(r,D_X,meanBit) +
    whiteMeanBitRight(r,D_X,dx,meanBit);
      if( (j == 0) && (i > n4+1) ){  break;  }
      byte += (prev-j);
      /* for  'bl' */
      if( (byte < 2) && (i > n4+2) ){
         break;
      }
      prev = j;
   }
   if( i > dy-2 )  i = 2*dy/3;
   n4 = i>>1;  n2 = 2*n4;
/*  calculate  symetry  of  hole  */
   down = up = byte = 0;
   r=RAST+D_X;
   prev = whiteMeanBitLeft(r,D_X,meanBit) +
          whiteMeanBitRight(r,D_X,dx,meanBit);
   for(i=1;i<=n2;i++,r+=D_X){
      j = whiteMeanBitLeft(r,D_X,meanBit) +
    whiteMeanBitRight(r,D_X,dx,meanBit);
      if( i<=n4 ){  up   += j;  cUp++;    }
      else       {  down += j;  cDown++;  }
      /* too  wide  hole */
      if( (i>n4) && (j>dx/3) ){
   if( (cUp==0) || (cDown==0) )  return(0);
   if( up*cDown <= down*cUp )    return(4);  /* bl - too  wide  hole */
   if( byte < 3 )                return(3);  /* bl - too  wide  hole */
      }
      byte += (prev-j);
      if( (prev-j > 3) && (i>n4) )  return(5);      /* bl - too  big  jump */
      if( (byte >= dx/4) && (i>n4) )  return( -6 ); /* M - too  big  angle  for  cursive */
      prev = j;
   }

   if( (cUp != cDown) && (cDown) ){  down *= cUp;  down /= cDown;  }
   if( down >= up )  return(5);  /* bl - wide  hole on  the  bottom */
   if( down < up )  return(-5); /* M - wide  hole on  the  top */
   if( !cDown )  return(6);  /* bl - hole is absent */

   return(0);
}  /* DiskrM */


static Int16 whiteMeanBitLeft(Word8 *RAST,Int16 D_X,Int16 meanBit)
{
   Int16    meanByte, byte;
   Int16    i,counter=0;

   for(i=meanBit;i>=0;i--){
      meanByte = i>>3;
      byte = *(RAST+meanByte);
      byte >>= ( 7- (i % 8) );
      byte &= 0x1;
      if(byte){
         meanByte = (i-1)>>3;
   byte = *(RAST+meanByte);
   byte >>= ( 7- ((i-1) % 8) );
   byte &= 0x1;
   if(byte)  break;
   else{
      meanByte = i>>3;
      byte = *(RAST+D_X+meanByte);
      byte >>= ( 7- (i % 8) );
      byte &= 0x1;
            if(byte)  break;
      else{
         meanByte = i>>3;
         byte = *(RAST-D_X+meanByte);
         byte >>= ( 7- (i % 8) );
         byte &= 0x1;
         if(byte)  break;
         else      counter++;
      }
         }
      }
      else  counter++;
   }

   return( counter );
}  /* whiteMeanBitLeft */

static Int16 whiteMeanBitRight(Word8 *RAST,Int16 D_X,Int16 dx,Int16 meanBit)
{
   Int16    meanByte, byte;
   Int16    i,counter=0;

   for(i=meanBit+1;i<dx;i++){
      meanByte = i>>3;
      byte = *(RAST+meanByte);
      byte >>= ( 7- (i % 8) );
      byte &= 0x1;
      if(byte){
   meanByte = (i+1)>>3;
   byte = *(RAST+meanByte);
   byte >>= ( 7- ((i+1) % 8) );
   byte &= 0x1;
   if(byte)  break;
   else{
      meanByte = i>>3;
      byte = *(RAST+D_X+meanByte);
      byte >>= ( 7- (i % 8) );
      byte &= 0x1;
            if(byte)  break;
      else{
         meanByte = i>>3;
         byte = *(RAST-D_X+meanByte);
         byte >>= ( 7- (i % 8) );
         byte &= 0x1;
         if(byte)  break;
         else      counter++;
      }
         }
      }
      else  counter++;
   }

   return( counter );
}  /* whiteMeanBitRight */

// check gluing roof and down zone for russian capital & small II
Int16 up_down_zones(Word8 *raster, Int16 D_X, Int16 dx, Int16 dx0,
      Int16 start1, Int16 stop1,
      Int16 start2, Int16 stop2)
{
Int16 i,num1,num2,l=dx0-(dx0>>3);
Word8 *r=raster;
if( up_down_serif>=0 )
  return( up_down_serif );

l = MIN(l,dx0-2);
dx = bytlen(dx);
for(r=raster+start1*D_X,num1=0,i=start1;i<stop1;i++,r+=D_X)
  {
  num1 += ( NumHorizInterval(r,dx)==1 && SumBits(r, dx)>=l );
    /*  num1 : �᫮ ��ப � ����� ������ ���ࢠ��� �� ���� */
  }

for(r=raster+start2*D_X,num2=0,i=start2;i<stop2;i++,r+=D_X)
  {
  num2 += ( NumHorizInterval(r,dx)==1 && SumBits(r, dx)>=l );
    /*  num2 : �᫮ ��ப � ����� ������ ���ࢠ��� ����� */
  }

if( num1==0 && num2>=1   ) /* ������ ���� ᫨�����, � ���� ࠧ�ࢠ�� */
  return( (up_down_serif=2) );
if( num1==0 && num2==0   ) /* ��� ����� */
  return( (up_down_serif=1) );

return( (up_down_serif=0) );
}

/* for letters 'C','c','e' */
static Int16 DiskrVertCE(Word8 *RASTR,Int16 D_X,Int16 dx,Int16 dy,Int16 X,
                        Word8 let, Word8 inc)
{
Word8 *RASTER=RASTR;
Int16 i,p,n,s3,d=dx>>2,wid=bytlen(dx);
Int16 ody=dy>>2;
  Word8 *r=RASTR+ody*D_X;
  Int16 t1,t2,t3,num1,num2,num3,minnum,n2;
  Int16 l = dy -(ody<<1),num,z=dx-(dx>>3);
  Int16 nn[7];

if( c_or_e<0 )
  {
  d_c=0;
  /* ��ਧ��⠫�� ��᫥�������  */
  for(minnum=dx,n2=num=num1=num2=num3=0,i=ody;i<l; i++, r+=D_X )
    {
    t1=NumHorizInterval(r,wid);
    t2=SumBits(r, wid);
    if( t1==2 )
      {

      t3 = (wid<<3) - LeftDistance(r,wid)  -
          RightDistance(r,wid) - t2;
      if( n2>0 )
        {
        if( dx>10 && t3<3 )
          num3++;
        if( minnum>t3 )
          minnum=t3;
        }
      n2++;
      }
    num  += (t1==1 && t2>=z);
    num1 += (t1==1 && t2>=z-1);
    num2 += (t2>=z);
    }
    /*  num : �᫮ ��ப � ����� ������ ���ࢠ��� */
  if( num>1 || num1>2 || num2>3 || num3>1 )
    {   /* ���� �����뢭�� ��४������ */
    c_or_e = 1;     /* ��� ����� ������� ��ப       */
    d_e = 0;
    d_c = num;
    if( num3 ) d_c += (minnum==1?4:3);
    return( (let==(Word8)'�')?d_e:d_c );
    }
if( num==0 && num1==0  && num2==0 && dy<24 )
{       /* ��� ���� ����⨢ ���� �ࠢ��� ண� */
r=RASTR+ody*D_X;
t2 = dx>>1;
for(i=ody;i<l; i++, r+=D_X )
    {
    num1=SumIntervalBits(r,t2,dx);

    if( i>ody && num!=0 && num1==0 )
      break;
    num = num1;
    }
i -= 4;
r = RASTR+i*D_X;
for(t3=t2=0;t2<7;t2++,i++,r+=D_X)
  {
  nn[t2]=EndBlackInterval(r,wid);
  t3+=(NumHorizInterval(r,wid)==2);
  }
for(t1=t2=nn[0],num=0,num1=1;num1<7;num1++)
  {
  if( t1>nn[num1] && nn[num1]>=0 )
    t1=nn[num1];
  if( t2<nn[num1] )
    t2=nn[(num=num1)];
  if( t2==nn[num1] && num==0 )
    num=num1;
  }
for(num1=num-1;num1>=0;num1--)
  if( nn[num1]<t2 )
    break;
for(num2=num+1;num2<7;num2++)
  if( nn[num2]<t2 )
    break;
if( inc && t2-t1<3 )
  t2=t1;  // Oleg : ERECTION conditions : 09-08-95 09:47pm
if( t3>2 && t2>t1 && num1>=0 && num2<7 )
  { /* ��� ���騪 */
  c_or_e = 1;     /* ��� ����� ������� ��ப       */
  d_e = 0;
  d_c = 1+t2-t1;
  if( (let==(Word8)'�') )
  return( d_e );
  }
}
  /* ����� ���⨪���� ��᫥�������  */

  dx-=d;
  X &= 7;
  for(n=s3=0,i=d;i<dx; i++)
    {
    p = NumVertInterval(RASTER, D_X, dy, (Int16)(i+X));
    s3 += ( p==3 );
    if( p==3 || p==2 )n++;
    }
    /*  NumVertInterval : �᫮ ����� � �⮫�� */
  p =  n;
  n *= 4;
  n /= 10;  /* 40 % */
  p -= n;   /* 60 % */

  c_or_e = 1;
  d_e = (s3<p)?p-s3:0;
  if( s3==0 && d_e<3 )
    d_e = 4;
  d_c = MAX(d_c,(s3>n)?s3-n+1:0);
  }
return( (let==(Word8)'�')?d_e:d_c );
}


Int16 AngleBottomRight(Word8 *raster,Int16 D_X,Int16 hei)
{
int i,old,neue,inc;
Word8 *r;

raster += D_X * (hei-2);
hei >>= 2;

old=RightDistance(raster,D_X);
for(inc=0,r=raster-D_X,i=1;i<hei;i++,r-=D_X)
  {
  neue = RightDistance(r,D_X);
  if( neue<old )    inc++;
  if( neue>old )    break;
  old  = neue;
  }
return inc;
}

Int16 AngleTopRight(Word8 *raster,Int16 D_X,Int16 hei)
{
int i,old,neue,inc;
Word8 *r;

raster += D_X;
hei >>= 2;

old=RightDistance(raster,D_X);
for(inc=0,r=raster+D_X,i=1;i<hei;i++,r+=D_X)
  {
  neue = RightDistance(r,D_X);
  if( neue<old )    inc++;
  if( neue>old )    break;
  old  = neue;
  }
return inc;
}

Int16 BonusAnglesCurve(Word8 *raster,Int16 D_X,Int16 hei)
{
int pen=0,inc;

inc = AngleTopRight(raster,D_X,hei);
if( inc>3 || hei<23 && inc>2 ) pen++;

inc = AngleBottomRight(raster,D_X,hei);
if( inc>3 || hei<23 && inc>2 ) pen++;

return pen;
}

Bool32 DiskrJuCut(Int16 nfoot, Int16 dx)
{
int i,l,d;
l = dx*3/4;
d = dx/5;
for(i=0;i<nfoot;i++)
if( LOCAL[i]>l && LOCAL_W[i]>d )
    return TRUE;
return FALSE;
}

DIF_FUNC(Int16) DIF_GetNoCutPoint(Word8 *RASTER, Int16 Wx, Word8 NWIDTH, Word8 NLENGTH)
{
Int16 f=FOOT_HEI( RASTER, Wx, NWIDTH, NLENGTH);
if( f!=2 || f==2 && (LOCAL[0]-(LOCAL_W[0]+1)/2)>(LOCAL_W[0]+1)/2 )
	return 0;
return LOCAL[1]+(LOCAL_W[1]+1)/2;
}
