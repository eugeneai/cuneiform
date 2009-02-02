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

#include <string.h>
#include "rneg.h"
#include "recnegmain.h"
#include "compat_defs.h"

#define MY_IMAGE_ROTATE "RNEG Image Rotate"
#define INF_ROTATE_H 1000

# define INCLINE_FACTOR  2048

# define IDEAL_XY(x, y)   \
         {\
             y = (INT) (y - (LONG) x * nIncline / INCLINE_FACTOR);\
             x = (INT) (x + (LONG) y * nIncline / INCLINE_FACTOR);\
         }

# define REAL_XY(x, y)   \
         {\
             x = (INT) (x - (LONG) y * nIncline / INCLINE_FACTOR);\
             y = (INT) (y + (LONG) x * nIncline / INCLINE_FACTOR);\
		}

/*----------------------------------------------------------------------------*/

//���������

int inf_neg_h;
int inf_neg_w;
double neg_cut_black;
double neg_cut_white;
double neg_cut_str;
int min_let_h;
int min_let_w;
//int max_let_h;
//int max_let_w;
int inf_betw_str_h;
int sup_square;
/*----------------------------------------------------------------------------*/
//���������

int	DPIX;
int	DPIY;
int Height;
int Width;
Word8 ImageName[CPAGE_MAXNAME];
int nIncline;
BOOL dpTime;
BOOL dpPrintResConsole;
BOOL dpNegResD;
BOOL dpNegRecD;
BOOL dpRecOneLetter;
/*----------------------------------------------------------------------------*/
NegImage* pNegImage;





RNEG_FUNC(void) RNEG_RecogNeg(CCOM_handle hCCOM, Handle hCPage,Word8* pImageName,int skew)
{

 MainWindowD=NULL;
 MainWindowD=LDPUMA_GetWindowHandle ("����������� ����� ���������");
 if(!MainWindowD)
    MainWindowD=LDPUMA_GetWindowHandle ("Main");

 dpTime=!LDPUMA_Skip(hTime);
 dpPrintResConsole=!LDPUMA_Skip(PrintResConsole);
 dpNegResD=!LDPUMA_Skip(NegResD);
 dpNegRecD=!LDPUMA_Skip(NegRecD);
 dpRecOneLetter=!LDPUMA_Skip(RecOneLetter);

// LDPUMA_ConsoleN("");
 if(dpTime)
     LDPUMA_ConsoleN("�������������� ������� ������ � ������������� ���������");
 int time=clock();
 if(!(LDPUMA_Skip (NegSearch)) )
	 return;

 Word32 code_sersized=(512<<16);
 Word32 code_normd=(512<<17);
 Word32 code_colord=(512<<17)+(512<<16);
 Word32 code_cutd=(512<<18);
 Word32 code_cutstrd=(512<<18)+(512<<16);
 Word32 code_sized=(512<<18)+(512<<17);

 #define NEGA   1<<14
 #define VERTICA 1<<13


 inf_neg_h=30;
 inf_neg_w=100;
 neg_cut_black=.95;
 neg_cut_white=.3;
 neg_cut_str=.8;
 min_let_h=2;
 min_let_w=2;
 inf_betw_str_h=10;
 sup_square=500000;

 PAGEINFO info = {0};
 GetPageInfo(hCPage,&info);
 DPIX=info.DPIX;
 DPIY=info.DPIY;
 inf_neg_h=inf_neg_h*((int)(DPIY)+1)/300;
 inf_neg_w=inf_neg_w*((int)(DPIX)+1)/300;
 inf_betw_str_h=inf_betw_str_h*((int)(DPIY)+1)/300;
 sup_square=(int)(((double)sup_square*(double)(DPIY+1)*(double)(DPIX+1))/90000);
 min_let_w=min_let_w*((int)(DPIX)+1)/300;
 min_let_h=min_let_h*((int)(DPIY)+1)/300;

 if((info.Angle==90)||(info.Angle==270))
 {
	 Height=info.Width;
	 Width=info.Height;
 }
 else
 {
     Height=info.Height;
     Width=info.Width;
 }


 NegList* root=NULL;
 NegList* now;
 NegList* temp;
 int nRC=0;
 int i;
 BOOL fl_del_mas_neg;
 BOOL flag_rotate;
 BOOL flag_rimage_rotate;


 if(!LDPUMA_Skip(SetSkew))
	 skew=Skew;

 for(i=0;i<CPAGE_MAXNAME&&pImageName[i]!='\0';i++)
	 ImageName[i]=pImageName[i];
 if(i<CPAGE_MAXNAME)
	 ImageName[i]='\0';

 if(!InitMyImage())
	 return;

 if(dpTime)
 {
    LDPUMA_ConsoleN("Time prep=%d",clock()-time);
	time=clock();
 }

/* �������������� ����� ���������� � �������� �� �������*/

 if(LDPUMA_Skip (NegSearchSize) )
 {
  fl_del_mas_neg=SearchNegBySize(hCCOM,hCPage,&root,nRC);

  /*���������� ��������� ���������� � �������� �� ��������*/

  if(nRC>0)
  {
	  now=root;
   if(!(LDPUMA_Skip (NegSearchSizeD)) )
   {
	for(i=0;i<nRC;i++)
	{
     NegDrawRect(MainWindowD,code_sersized,RGB(0,0,255),(now->neg).pRc[0]);
     now=now->next;
	}
	LDPUMA_ConsoleN("�� ��������");
    LDPUMA_WaitUserInput (NegSearchSizeD,MainWindowD);
    if(LDPUMA_Skip (NegSearchSizeDC) )
      LDPUMA_DeleteRects (MainWindowD,code_sersized);
   }
  }
 }

 flag_rimage_rotate=IfNeedGlobalRotate(root,skew);

 now=root;
 while(now)
 {
      while((now->neg).pRc[0].top<=0)
		  ((now->neg).pRc[0].top)++;
	  while(((now->neg).pRc[0].bottom+1)>Height )
          ((now->neg).pRc[0].bottom)--;


	  while((now->neg).pRc[0].left<0)
		  ((now->neg).pRc[0].left)++;
	  while( ((now->neg).pRc[0].right+1)>Width )
          ((now->neg).pRc[0].right)--;

      int prewide=(((now->neg).pRc[0].right-(now->neg).pRc[0].left+8)/8)*8;
      if( ((now->neg).pRc[0].left+prewide)>Width )
	    (now->neg).pRc[0].right-=8;
	  now=now->next;
 }

/* �������������� ��������(���� ������) �����, �.�. ����������
          �������� � ������������� ����*/

 if(LDPUMA_Skip (NegNorm) )
 {

/* ������� (���� ���������) ���������*/

  flag_rotate=NegRotate(hCPage,root,nRC,skew);

   now=root;
   for(i=1;i<nRC;i++)
      now=now->next;
   i=nRC-1;
   while(i>=0)
   {
	temp=now->prev;
    NormNeg(hCPage,now,&root,nRC);
    i--;
	now=temp;
   }


/*�������� ��������������*/
   if(flag_rotate)
   {
	  now=root;
	  while(now)
	  {
		   if((now->neg).rot.pmasp)
           {
             RSELSTR_UnRotateRect(-skew,&((now->neg).pRc[0]),1,(now->neg).rot.Rc,(now->neg).rot.begx,(now->neg).rot.movey,(now->neg).rot.flmovey,(now->neg).rot.hi);
             PostRotate(now,skew);
           }
	       DeleteRotateMas(&((now->neg).rot.pmasp),&((now->neg).rot.begx),&((now->neg).rot.movey),&((now->neg).rot.flmovey),&((now->neg).rot.hi));
      now=now->next;
	  }
   }


  /* ���������� ��������������� ���������� � ��������*/

  if(nRC>0)
  {
	  now=root;
   if(!(LDPUMA_Skip (NegNormD)) )
   {
	for(i=0;i<nRC;i++)
	{
     NegDrawRect(MainWindowD,code_normd,RGB(0,255,0),(now->neg).pRc[0]);
     now=now->next;
	}
	LDPUMA_ConsoleN("���������������");
    LDPUMA_WaitUserInput (NegNormD,MainWindowD);
    if(LDPUMA_Skip (NegNormDC) )
      LDPUMA_DeleteRects (MainWindowD,code_normd);
   }
  }
 }



/* ����� ������� ���������*/

 if(LDPUMA_Skip (NegCut) )
 {

/* ������� (���� ���������) ���������*/
 flag_rotate=NegRotate(hCPage,root,nRC,skew);


  CutNeg(hCPage,&root,nRC,skew);


   /* ������� (���� ���������) ���������*/
  flag_rotate=NegRotate(hCPage,root,nRC,skew);


   now=root;
   for(i=1;i<nRC;i++)
      now=now->next;
   i=nRC-1;
   while(i>=0)
   {
	temp=now->prev;
    NormNeg(hCPage,now,&root,nRC);
    i--;
	now=temp;
   }

   /*�������� ��������������*/
   if(flag_rotate)
   {
	   now=root;
       while(now)
	   {
		   if((now->neg).rot.pmasp)
           {
             RSELSTR_UnRotateRect(-skew,&((now->neg).pRc[0]),1,(now->neg).rot.Rc,(now->neg).rot.begx,(now->neg).rot.movey,(now->neg).rot.flmovey,(now->neg).rot.hi);
             PostRotate(now,skew);
           }
	       DeleteRotateMas(&((now->neg).rot.pmasp),&((now->neg).rot.begx),&((now->neg).rot.movey),&((now->neg).rot.flmovey),&((now->neg).rot.hi));
	   now=now->next;
	   }
   }


  /* ���������� ����������� ���������*/

  if(nRC>0)
  {
	  now=root;
   if(!(LDPUMA_Skip (NegCutD)) )
   {
	for(i=0;i<nRC;i++)
	{
     NegDrawRect(MainWindowD,code_cutd,RGB(255,0,0),(now->neg).pRc[0]);
     now=now->next;
	}
	LDPUMA_ConsoleN("�����������");
    LDPUMA_WaitUserInput (NegCutD,MainWindowD);
    if(LDPUMA_Skip (NegCutDC) )
      LDPUMA_DeleteRects (MainWindowD,code_cutd);
   }
  }

 }


  now=root;

 for(i=1;i<nRC;i++)
	 now=now->next;
 int h;
 int w;
 Rect16 Rc;

 /*����� �� �������*/
 if(LDPUMA_Skip (NegSize) )
 {
  while(now)
  {
	   h=(now->neg).pRc[0].bottom-(now->neg).pRc[(now->neg).nRc-1].top+1;
	   w=(now->neg).pRc[0].right-(now->neg).pRc[0].left+1;
	  if( ((h<2*w)&&(w<2*h)) || ((h*w)>sup_square) )
	  {
		  temp=now;
		  if(!temp->prev)
			  root=temp->next;
		  nRC--;
		  now=now->prev;
		  delete temp;
	  }
	  else
		  now=now->prev;
  }

  /* ���������� ��������� �� �������*/

  if(nRC>0)
  {
	  now=root;
   if(!(LDPUMA_Skip (NegSizeD)) )
   {
	for(i=0;i<nRC;i++)
	{
	 Rc.left=(now->neg).pRc[0].left;
	 Rc.right=(now->neg).pRc[0].right;
	 Rc.bottom=(now->neg).pRc[0].bottom;
	 Rc.top=(now->neg).pRc[(now->neg).nRc-1].top;
     NegDrawRect(MainWindowD,code_sized,RGB(255,255,0),Rc);
     now=now->next;
	}
	LDPUMA_ConsoleN("������������� ����������");
    LDPUMA_WaitUserInput (NegSizeD,MainWindowD);
    if(LDPUMA_Skip (NegSizeDC) )
      LDPUMA_DeleteRects (MainWindowD,code_sized);
   }
  }

 }

/* ������� (���� ���������) ���������*/
 flag_rotate=NegRotate(hCPage,root,nRC,skew);


/* �������������� ����� ���������� � �������� �� ������������
            ������� �����*/

 if(LDPUMA_Skip (NegColor) )
 {
  SearchNegByBlack(hCPage,&root,nRC);

  /*���������� ���������� � �������� ����� ������ �� �������� �����*/

  if(nRC>0)
  {
	  now=root;
   if(!(LDPUMA_Skip (NegColorD)) )
   {
	for(i=0;i<nRC;i++)
	{
     NegDrawRect(MainWindowD,code_colord,RGB(0,255,255),(now->neg).pRc[0]);
     now=now->next;
	}
	LDPUMA_ConsoleN("��������� �� �������� �����");
    LDPUMA_WaitUserInput (NegColorD,MainWindowD);
    if(LDPUMA_Skip (NegColorDC) )
      LDPUMA_DeleteRects (MainWindowD,code_colord);
   }
  }
 }

 /* ����� ������������� ���������*/


 if(LDPUMA_Skip (NegCutStr) )
 {
  CutNegStr(hCPage,&root,nRC,skew);


  /* ���������� ����������� ���������*/

  if(nRC>0)
  {
	  now=root;
   if(!(LDPUMA_Skip (NegCutStrD)) )
   {
	while(now)
	{
	 for(i=0;i<(now->neg).nRc;i++)
      NegDrawRect(MainWindowD,code_cutstrd,RGB(255,0,255),(now->neg).pRc[i]);
     now=now->next;
	}
	LDPUMA_ConsoleN("����������� �� ������");
    LDPUMA_WaitUserInput (NegCutStrD,MainWindowD);
    if(LDPUMA_Skip (NegCutStrDC) )
      LDPUMA_DeleteRects (MainWindowD,code_cutstrd);
   }
  }

 }



/*����� ��������������*/

 DelIn(hCPage,&root,nRC);

 int time_stuff=clock();
 if(dpTime)
   LDPUMA_ConsoleN("Time stuff=%d",time_stuff-time);

/* �������������� ������������� �� ������� ����������*/
 if(flag_rimage_rotate)
 {
	 UnRotateNeg(root,skew);
	 ResetMyImage();
	 if(!InitMyImage())
		 return;
	 CheckNega(root);
	 if(!flag_rotate)
		 flag_rotate=NegRotate(hCPage,root,nRC,skew);
 }

 if(LDPUMA_Skip (NegRec) )
 {
  NegRecog(hCPage,&root,nRC,skew);
 }

 if(dpTime)
    LDPUMA_ConsoleN("Time recog=%d",clock()-time_stuff);


 if(!(LDPUMA_Skip (NegPrintFILE) ))
 {
  FILE *f;
  f=fopen("recneg.res","a");
  if(f==NULL)
 	 f=fopen("recneg.res","w+");
  if(f!=NULL)
  {
 	 NegPrintInFile(f,root,nRC);
      fclose(f);
  }
 }

 /* ������ � CPage*/



 now=root;
 if(1/*!(LDPUMA_Skip (PutToCPage) )*/)
 {
 POLY_ block={0};
 Word32 size_poly=sizeof(POLY_);
  while(now)
  {
   if((now->neg).p>inf_prob)
   {
	block.com.Flags=0;
    Rc.left=(now->neg).pRc[0].left;
    Rc.right=(now->neg).pRc[0].right;
    Rc.top=(now->neg).pRc[(now->neg).nRc-1].top;
    Rc.bottom=(now->neg).pRc[0].bottom;
            block.com.type = TYPE_TEXT; //�����, ��������, �������;
			block.com.count = 4;
			block.negative=TYPE_NEGATIVE;
			block.com.Flags=NEGA;

//Andrey: moved from RBLOCK (keyword:TYPE_NEGATIVE)
//------------------------------
			block.alphabet=0;
			block.com.number=0;
//------------------------------

//commented by Andrey
/*          if(Rc.bottom-Rc.top>Rc.right-Rc.left)
			{
                   block.orient=TYPE_DOWNUP;

				   block.com.Flags|=VERTICA;
			}
			else
				block.orient=TYPE_LEFTRIGHT;
*/
            if ((now->neg).Flags&FlVert)
            {
                block.com.Flags |= VERTICA;
                block.orient = (now->neg).Flags&FlDown2Up ? TYPE_DOWNUP : TYPE_UPDOWN;
            }
            else block.orient = TYPE_LEFTRIGHT;

			block.com.Vertex[0].x = Rc.left;
			block.com.Vertex[0].y = Rc.top;
			block.com.Vertex[1].x = Rc.right;
			block.com.Vertex[1].y = Rc.top;
			block.com.Vertex[2].x = Rc.right;
			block.com.Vertex[2].y = Rc.bottom;
			block.com.Vertex[3].x = Rc.left;
			block.com.Vertex[3].y = Rc.bottom;
//Andrey: create TYPE_TEXT block
	CPAGE_CreateBlock(hCPage, TYPE_IMAGE,0,0,&block,size_poly);
//			CPAGE_CreateBlock(hCPage, TYPE_TEXT,0,0,&block,size_poly);
   }
   now=now->next;
  }
 }

 if(!(LDPUMA_Skip (PutToCHSTR) ))
 {
  now=root;

  Word8 Name[CPAGE_MAXNAME];
  for (int j=0; j<CPAGE_MAXNAME; j++)
		Name[j] = ImageName[j];

  if(!(LDPUMA_Skip (TestCHSTR) ))
  {
   CHSTR_Objects Hstr;
   Hstr.Rc.top=TOP;
   Hstr.Rc.bottom=BOTTOM;
   Hstr.Rc.left=LEFT;
   Hstr.Rc.right=RIGHT;
   Hstr.block_number=1000;
   Hstr.ImageName[0]='\0';
   Hstr.type_neg=NEGATIVE;
   Hstr.type_vert=VERTICALE;
   RSELSTR_PutObjects(hCPage,(void*)hCCOM,&Hstr,1);
  }
 }

 PutTempToCPAGE(hCPage,root);

 if( (LDPUMA_Skip (NegSearchSize))&&(fl_del_mas_neg==TRUE) )
 {
	 while(root)
	 {
		 now=root;
		 root=root->next;
		 delete now;
	 }
 }

 ResetMyImage();

// LDPUMA_ConsoleN("Time work RNEG=%d",clock()-time);
}


BOOL NegRotate(Handle hCPage,NegList* root,int nRc,int skew)
{
 BOOL ret=FALSE;
 int oldskew=skew;
 if(skew<0)
	 skew=-skew;
 if(skew>=2048)
	 return FALSE;
 int w;
 int h;
 int bytewide;

 Word8 Data[1000];
 memset (Data, 0, sizeof (Data));
 Word8* pmasp;

 NegList* now=root;
 Rect16 Rc;
 BOOL fl_cont;

 while(now)
 {
  fl_cont=FALSE;
  Rc.top=(now->neg).pRc[0].top;
  Rc.bottom=(now->neg).pRc[0].bottom;
  Rc.left=(now->neg).pRc[0].left;
  Rc.right=(now->neg).pRc[0].right;
  w=Rc.right-Rc.left+1;
  h=Rc.bottom-Rc.top+1;
  bytewide=(w+7)/8;
  if((double)(w*skew)/2048.<(double)(inf_betw_str_h))
  {
	  fl_cont=TRUE;
	  now=now->next;
  }
  if(fl_cont)
	  continue;
  if(!(GetMasP(&Rc,&pmasp)) )
  {
	  fl_cont=TRUE;
	  now=now->next;
  }
  if(fl_cont)
	  continue;
  if(!( (now->neg).rot.pmasp=new Word8[bytewide*h]))
  {
	  fl_cont=TRUE;
	  now=now->next;
  }
  if(fl_cont)
	  continue;
  if(!(InitRotateMas(w,h,&((now->neg).rot.begx),&((now->neg).rot.movey),&((now->neg).rot.flmovey),&((now->neg).rot.hi) )))
  {
	  delete[] ((now->neg).rot.pmasp);
	  (now->neg).rot.pmasp=NULL;
	  now=now->next;
	  fl_cont=TRUE;
  }
  if(fl_cont)
	  continue;
  NegCopy(pmasp,(now->neg).rot.pmasp,bytewide,h);
  (now->neg).rot.Rc.bottom=Rc.bottom;
  (now->neg).rot.Rc.top=Rc.top;
  (now->neg).rot.Rc.left=Rc.left;
  (now->neg).rot.Rc.right=Rc.right;
  if( RSELSTR_RotateRaster((now->neg).rot.pmasp,-oldskew,&((now->neg).pRc[0]),(now->neg).rot.begx,(now->neg).rot.movey,(now->neg).rot.flmovey,inf_betw_str_h) )
      ret=TRUE;
  else
  {
	  DeleteRotateMas(&((now->neg).rot.pmasp),&((now->neg).rot.begx),&((now->neg).rot.movey),&((now->neg).rot.flmovey),&((now->neg).rot.hi));
	  (now->neg).rot.pmasp=NULL;
	  (now->neg).rot.begx=NULL;
	  (now->neg).rot.movey=NULL;
	  (now->neg).rot.flmovey=NULL;
	  (now->neg).rot.hi=NULL;
  }

  now=now->next;
 }



 return ret;
}

void NegCopy(Word8* from,Word8* to,int bytewide,int h)
{
	int j=bytewide*h;
	for(int i=0;i<j;i++)
		to[i]=from[i];
}

BOOL InitRotateMas(int w,int h,Int16** ppbegx,Int16** ppmovey,Word8** ppflmovey,int** pphi)
{
	if(!( (*ppbegx)=new Int16[h+1]))
		return FALSE;
	if(!( (*ppmovey)=new Int16[w+1]))
	{
		delete[] (*ppbegx);
		(*ppbegx)=NULL;
		return FALSE;
	}
	if(!( (*ppflmovey)=new Word8[w+1]))
	{
		delete[] (*ppbegx);
		(*ppbegx)=NULL;
		delete[] (*ppmovey);
		(*ppmovey)=NULL;
		return FALSE;
	}
	if(!( (*pphi)=new int[10]))
	{
		delete[] (*ppbegx);
		(*ppbegx)=NULL;
		delete[] (*ppmovey);
		(*ppmovey)=NULL;
		delete[] (*ppflmovey);
		(*ppflmovey)=NULL;
		return FALSE;
	}
	return TRUE;
}

void DeleteRotateMas(Word8** pmasp,Int16** begx,Int16** movey,Word8** flmovey,int** hi)
{
	    delete[] (*pmasp);
		*pmasp=NULL;
		delete[] (*begx);
		*begx=NULL;
		delete[] (*movey);
		*movey=NULL;
		delete[] (*flmovey);
		*flmovey=NULL;
		delete[] (*hi);
		*hi=NULL;
}

BOOL IfNeedGlobalRotate(NegList* root,int& skew)
{
 NegList* now=root;
 Rect16 Rc;
 int w;
 int h;
 BOOL fl_break=FALSE;
 int modskew=skew;
 if(modskew<0)
	 modskew=-modskew;
 int sum_sq=0;

 while(now)
 {
  Rc.top=(now->neg).pRc[0].top;
  Rc.bottom=(now->neg).pRc[0].bottom;
  Rc.left=(now->neg).pRc[0].left;
  Rc.right=(now->neg).pRc[0].right;
  w=Rc.right-Rc.left+1;
  h=Rc.bottom-Rc.top+1;
  if((double)(w*modskew)/2048.>=(double)(inf_betw_str_h))
  {
	  sum_sq+=w*h;
  }

  now=now->next;
 }

 if(sum_sq<pNegImage->Wide*pNegImage->Height)
	 return FALSE;


 Rc.top=0;
 Rc.left=0;
 Rc.right=pNegImage->Wide-1;
 Rc.bottom=pNegImage->Height-1;
 w=pNegImage->Wide;
 h=pNegImage->Height;

 Word8* newlpdata=pNegImage->GetPmasp(&Rc);
 if(!newlpdata)
	 return FALSE;

 NegImage* pRotImage = new NegImage;
 if(!pRotImage)
	 return FALSE;

  if(!(InitRotateMas(w,h,&(pRotImage->rotate.begx),&(pRotImage->rotate.movey),&(pRotImage->rotate.fl_movey),&(pRotImage->rotate.hi) )))
  {
	  delete pRotImage;
	  return FALSE;
  }

  pRotImage->rotate.Rc.left=0;
  pRotImage->rotate.Rc.top=0;
  pRotImage->rotate.Rc.right=pNegImage->Wide-1;
  pRotImage->rotate.Rc.bottom=pNegImage->Height-1;

  if(! RSELSTR_RotateRaster(newlpdata,-skew,&Rc,pRotImage->rotate.begx,pRotImage->rotate.movey,pRotImage->rotate.fl_movey,inf_betw_str_h))
  {
	  delete pRotImage;
	  return FALSE;
  }

 Height=Rc.bottom+1;
 Width=Rc.right+1;
 const int bytewide=(Width+7)/8;
 int i;
 Word8* lptemp = new Word8[bytewide];
 if(!lptemp)
 {
	 delete pRotImage;
	 return FALSE;
 }

 Word8* to=newlpdata;
 Word8* from=newlpdata+(Height-1)*bytewide;
 for(i=Height>>1;i>0;i--,to+=bytewide,from-=bytewide)
 {
	 memcpy(lptemp,to,bytewide);
	 memcpy(to,from,bytewide);
	 memcpy(from,lptemp,bytewide);
 }
 delete[] lptemp;

 if(!pRotImage->SetDibPtr(newlpdata,Width,Height,bytewide))
 {
	 delete pRotImage;
	 return FALSE;
 }
 pNegImage->pmasp=NULL;
 pRotImage->fl_delete=TRUE;

 delete pNegImage;
 pNegImage=pRotImage;

 now=root;
 nIncline=skew;
 while(now)
 {
//Andrey 06.03.2003 - ��-����� ��� �����: �� ����� left ����������� ��� �������� �� ��������� ������������� ����
/*  if(nIncline>=0)
  {
	  now->neg.pRc->left-=pNegImage->rotate.begx[now->neg.pRc->top];
	  now->neg.pRc->right-=pNegImage->rotate.begx[now->neg.pRc->bottom];
	  if(now->neg.pRc->left<0)
		  now->neg.pRc->left=0;
	  if(now->neg.pRc->right>=pNegImage->Wide)
		  now->neg.pRc->right=pNegImage->Wide-1;
	  now->neg.pRc->top-=(Int16)((int)(now->neg.pRc->right)*nIncline/2048);
	  now->neg.pRc->bottom-=(Int16)((int)(now->neg.pRc->left)*nIncline/2048);
	  if(now->neg.pRc->top<0)
		  now->neg.pRc->top=0;
	  if(now->neg.pRc->bottom>=pNegImage->Height)
		  now->neg.pRc->bottom=pNegImage->Height-1;
  }
  else
  {
	  now->neg.pRc->left-=pNegImage->rotate.begx[now->neg.pRc->bottom];
	  now->neg.pRc->right-=pNegImage->rotate.begx[now->neg.pRc->top];
	  if(now->neg.pRc->left<0)
		  now->neg.pRc->left=0;
	  if(now->neg.pRc->right>=pNegImage->Wide)
		  now->neg.pRc->right=pNegImage->Wide-1;
	  now->neg.pRc->top-=(pNegImage->Wide-now->neg.pRc->left)*(-nIncline)/2048;
	  now->neg.pRc->bottom-=(pNegImage->Wide-now->neg.pRc->right)*(-nIncline)/2048;
	  if(now->neg.pRc->top<0)
		  now->neg.pRc->top=0;
	  if(now->neg.pRc->bottom>=pNegImage->Height)
		  now->neg.pRc->bottom=pNegImage->Height-1;
  }
*/
  if(nIncline>=0)
  {
	  now->neg.pRc->left+=pNegImage->rotate.begx[now->neg.pRc->top];
	  now->neg.pRc->right+=pNegImage->rotate.begx[now->neg.pRc->bottom];
	  if(now->neg.pRc->left<0)
		  now->neg.pRc->left=0;
	  if(now->neg.pRc->right>=pNegImage->Wide)
		  now->neg.pRc->right=pNegImage->Wide-1;
	  now->neg.pRc->top-=(Int16)((int)(now->neg.pRc->left)*nIncline/2048);
	  now->neg.pRc->bottom-=(Int16)((int)(now->neg.pRc->right)*nIncline/2048);
	  if(now->neg.pRc->top<0)
		  now->neg.pRc->top=0;
	  if(now->neg.pRc->bottom>=pNegImage->Height)
		  now->neg.pRc->bottom=pNegImage->Height-1;
  }
  else
  {
	  now->neg.pRc->left-=pNegImage->rotate.begx[now->neg.pRc->bottom];
	  now->neg.pRc->right-=pNegImage->rotate.begx[now->neg.pRc->top];
	  if(now->neg.pRc->left<0)
		  now->neg.pRc->left=0;
	  if(now->neg.pRc->right>=pNegImage->Wide)
		  now->neg.pRc->right=pNegImage->Wide-1;
	  now->neg.pRc->top-=now->neg.pRc->right*nIncline/2048;
	  now->neg.pRc->bottom-=now->neg.pRc->left*nIncline/2048;
	  if(now->neg.pRc->top<0)
		  now->neg.pRc->top=0;
	  if(now->neg.pRc->bottom>=pNegImage->Height)
		  now->neg.pRc->bottom=pNegImage->Height-1;
  }

//Andrey 08.04.2002
  if (now->neg.pRc->right < 0) now->neg.pRc->right = 0;
  if (now->neg.pRc->left > now->neg.pRc->right) now->neg.pRc->left = now->neg.pRc->right;
  if (now->neg.pRc->bottom < 0) now->neg.pRc->bottom = 0;
  if (now->neg.pRc->top > now->neg.pRc->bottom) now->neg.pRc->top = now->neg.pRc->bottom;

  now=now->next;
 }
 skew=0;

 return TRUE;
}

void UnRotateNeg(NegList* root,int& skew)
{
 NegList* now;
 now=root;
 while(now)
 {
//Andrey 06.03.2003 - ��-����� ��� �����: �� ����� left ����������� ��� �������� �� ���������� �������������� �����
/*  if(nIncline>=0)
  {
	  for(int i=0;i<now->neg.nRc;i++)
	  {
	   now->neg.pRc[i].top+=(Int16)((int)(now->neg.pRc[i].left)*nIncline/2048);
	   now->neg.pRc[i].bottom+=(Int16)((int)(now->neg.pRc[i].right)*nIncline/2048);
	   if(now->neg.pRc[i].left<0)
		  now->neg.pRc[i].left=0;
	   if(now->neg.pRc[i].right>pNegImage->rotate.Rc.right)
		  now->neg.pRc->right=pNegImage->rotate.Rc.right;
	   now->neg.pRc[i].left+=pNegImage->rotate.begx[now->neg.pRc[i].bottom];
	   now->neg.pRc[i].right+=pNegImage->rotate.begx[now->neg.pRc[i].top];
	  }
  }
  else
  {
	  for(int i=0;i<now->neg.nRc;i++)
	  {
	   now->neg.pRc[i].top+=(pNegImage->Wide-now->neg.pRc[i].right)*(-nIncline)/2048;
	   now->neg.pRc[i].bottom+=(pNegImage->Wide-now->neg.pRc[i].left)*(-nIncline)/2048;
	   if(now->neg.pRc[i].left<0)
		  now->neg.pRc[i].left=0;
	   if(now->neg.pRc[i].right>pNegImage->rotate.Rc.right)
		  now->neg.pRc->right=pNegImage->rotate.Rc.right;
	   now->neg.pRc[i].left+=pNegImage->rotate.begx[now->neg.pRc[i].top];
	   now->neg.pRc[i].right+=pNegImage->rotate.begx[now->neg.pRc[i].bottom];
	  }
  }
*/
  if(nIncline>=0)
  {
	  for(int i=0;i<now->neg.nRc;i++)
	  {
	   now->neg.pRc[i].top+=(Int16)((int)(now->neg.pRc[i].left)*nIncline/2048);
	   now->neg.pRc[i].bottom+=(Int16)((int)(now->neg.pRc[i].right)*nIncline/2048);
	   now->neg.pRc[i].left-=pNegImage->rotate.begx[now->neg.pRc[i].top];
	   now->neg.pRc[i].right-=pNegImage->rotate.begx[now->neg.pRc[i].bottom];

	   if(now->neg.pRc[i].left<0)
		  now->neg.pRc[i].left=0;
	   if(now->neg.pRc[i].right>pNegImage->rotate.Rc.right)
		  now->neg.pRc->right=pNegImage->rotate.Rc.right;
	  }
  }
  else
  {
	  for(int i=0;i<now->neg.nRc;i++)
	  {
	   now->neg.pRc[i].top+=now->neg.pRc[i].right*nIncline/2048;
	   now->neg.pRc[i].bottom+=now->neg.pRc[i].left*nIncline/2048;
	   now->neg.pRc[i].left+=pNegImage->rotate.begx[now->neg.pRc[i].bottom];
	   now->neg.pRc[i].right+=pNegImage->rotate.begx[now->neg.pRc[i].top];

	   if(now->neg.pRc[i].left<0)
		  now->neg.pRc[i].left=0;
	   if(now->neg.pRc[i].right>pNegImage->rotate.Rc.right)
		  now->neg.pRc->right=pNegImage->rotate.Rc.right;
	  }
  }
  now=now->next;
 }
 skew=nIncline;
}

void CheckNega(NegList* root)
{
 NegList* now;
 now=root;
 while(now)
 {
	 for(int i=0;i<now->neg.nRc;i++)
	 {
	  if(now->neg.pRc[i].left<0)
		  now->neg.pRc[i].left=0;
	  if(now->neg.pRc[i].right>=pNegImage->Wide)
		  now->neg.pRc[i].right=pNegImage->Wide-1;
	  if(now->neg.pRc[i].top<0)
		  now->neg.pRc[i].top=0;
	  if(now->neg.pRc[i].bottom>=pNegImage->Height)
		  now->neg.pRc[i].bottom=pNegImage->Height-1;
	 }
  now=now->next;
 }
}

BOOL InitMyImage()
{
	Handle lpDIB;
	if(!CIMAGE_ReadDIB(ImageName,&lpDIB,1))
		return FALSE;

	CTDIB* ctdib = new CTDIB;
	if(!ctdib)
		return FALSE;

    if(!ctdib->SetDIBbyPtr (lpDIB))
	{
		delete ctdib;
		return FALSE;
	}

    const int bytewide=ctdib->GetLineWidthInBytes();
    const int num_str=ctdib->GetLinesNumber ();
	const int w=ctdib->GetImageWidth();
    Word8* pmasp=(Word8*)(ctdib->GetPtrToBitFild());

	pNegImage = new NegImage;
	if(!pNegImage)
	{
		ctdib->ResetDIB ();
		delete ctdib;
		return FALSE;
	}

	if(!pNegImage->SetDibPtr(pmasp,w,num_str,bytewide))
	{
		ctdib->ResetDIB ();
		delete ctdib;
		delete pNegImage;
		pNegImage=NULL;
		return FALSE;
	}

	ctdib->ResetDIB();
	delete ctdib;

	Height=num_str;
	Width=w;

	return TRUE;
}

void ResetMyImage()
{
 delete pNegImage;
 pNegImage=NULL;
}
