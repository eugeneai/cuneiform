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

#define __RNEG__

#include "rneg.h"
#include "recnegmain.h"
#include "compat_defs.h"
/*----------------------------------------------------------------------------*/

//���������

extern int inf_neg_h;
extern int inf_neg_w;
extern double neg_cut_black;
extern double neg_cut_white;
extern double neg_cut_str;
extern int min_let_h;
extern int min_let_w;
extern int inf_betw_str_h;
extern int sup_square;
/*----------------------------------------------------------------------------*/
//���������

extern int	DPIX;
extern int	DPIY;
extern int Height;
extern int Width;
extern Word8 ImageName[CPAGE_MAXNAME];

/*----------------------------------------------------------------------------*/


RNEG_FUNC(Bool32) RNEG_TestForNegative(CCOM_handle hCCOM,Handle hCPage,Word8* pImageName,Rect16 Rc)
{
 MainWindowD=NULL;
 MainWindowD=LDPUMA_GetWindowHandle ("����������� ����� ���������");
 if(!MainWindowD)
    MainWindowD=LDPUMA_GetWindowHandle ("Main");

 inf_neg_h=30;
 inf_neg_w=100;
 neg_cut_black=.95;
 neg_cut_white=.3;
 neg_cut_str=.8;
 min_let_h=2;
 min_let_w=2;
 inf_betw_str_h=10;
 sup_square=500000;

 Word32 code_sersized=(512<<16);
 Word32 code_normd=(512<<17);
 Word32 code_colord=(512<<17)+(512<<16);
 Word32 code_cutd=(512<<18);
 Word32 code_cutstrd=(512<<18)+(512<<16);
 Word32 code_sized=(512<<18)+(512<<17);


 NegList* root=NULL;
 NegList* now;
 NegList* temp;
 int nRC=1;
 int i;
 BOOL flag_rotate;

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


 int skew=info.Incline2048;

 for(i=0;i<CPAGE_MAXNAME&&pImageName[i]!='\0';i++)
	 ImageName[i]=pImageName[i];
 if(i<CPAGE_MAXNAME)
	 ImageName[i]='\0';

 if(!InitMyImage())
	 return FALSE;

 root= new NegList(Rc);
 if(!root)
 {
	 ResetMyImage();
	 return FALSE;
 }

 if(!IsNegSize(root->neg.pRc[0].bottom-root->neg.pRc[0].top-1,root->neg.pRc[0].right-root->neg.pRc[0].left-1))
 {
	 delete root;
	 ResetMyImage();
	 return FALSE;
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
             RSELSTR_UnRotateRect(skew,&((now->neg).pRc[0]),1,(now->neg).rot.Rc,(now->neg).rot.begx,(now->neg).rot.movey,(now->neg).rot.flmovey,(now->neg).rot.hi);
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
             RSELSTR_UnRotateRect(skew,&((now->neg).pRc[0]),1,(now->neg).rot.Rc,(now->neg).rot.begx,(now->neg).rot.movey,(now->neg).rot.flmovey,(now->neg).rot.hi);
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


/* �������������� ������������� �� ������� ����������*/

 if(LDPUMA_Skip (NegRec) )
 {
  NegRecog(hCPage,&root,nRC,skew);
 }

 Bool32 ret=FALSE;
 now=root;
 if(now)
 {
   if((now->neg).p>inf_prob)
     ret=TRUE;
 }

 while(root)
 {
   now=root;
   root=root->next;
   delete now;
 }

 ResetMyImage();

 return ret;
}

