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

#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "ctiimage.h"
#include "cpage.h"
#include "lns.h"
#include "rline.h"
#include "dpuma.h"
#include "CTDIB.h"
#include "Rstuff.h"
#include "RSFunc.h"
#include "Cfio.h"
#include "pumadef.h"
#include "cline.h"


extern int move;
extern Handle OrtMove;
void CopyMove(Word8* newpmasp,Word8* oldpmasp,int newbytewide,int oldbytewide,int num_str,int move);
void MasCopy(Word8* oldpmasp,Word8* pmasp,int oldbytewide,int num_str);
void* MyMemAlloc(Word32 size);
void MyMemDelete(void* mem);
void *  MyMemLock(void* mem);
void MyMemUnLock(void* mem);
void CleanImage(Word8* pmasp,int bytewide,int num_str,int wide);



Bool32 OrtoMove(PRSPreProcessImage Image)
{
 if(!LDPUMA_Skip(OrtMove))
	 return TRUE;

// LDPUMA_ConsoleN("�������������� ���������");
// int time=clock();
 Handle hCPage=Image->hCPAGE;
 PAGEINFO info = {0};
 Word8 OldImage[CPAGE_MAXNAME];
 GetPageInfo(hCPage,&info);
 
 move=info.SkewLocVerLin2048;
 if(!move)
	 return TRUE;

 for(int i=0;i<CPAGE_MAXNAME;i++)
	 OldImage[i]=info.szImageName[i];

 char* ImageName=PUMA_IMAGE_ORTOMOVE;


 Handle lpDIB;
 if(!CIMAGE_ReadDIB(OldImage,&lpDIB,1))
	  return FALSE;
   
 CTDIB* olddib = new CTDIB;
 if(!(olddib->SetDIBbyPtr (lpDIB)) )
 {
	 delete olddib;
	 return FALSE;
 }
 int oldbytewide=olddib->GetLineWidthInBytes();
 int num_str=olddib->GetLinesNumber ();
 Word8* pmasp=(Word8*)(olddib->GetPtrToBitFild());

 int oldwide=(int)(olddib->GetLineWidth());
// Word8* oldpmasp=NULL;
// oldpmasp=new Word8[oldbytewide*num_str];
// if(!oldpmasp)
// {
//  olddib->ResetDIB();
//  delete olddib;
// }
 
// MasCopy(oldpmasp,pmasp,oldbytewide,num_str);
// olddib->ResetDIB();
// delete olddib;

 int max_move=abs((num_str*move)/2048);
 if(!max_move)
 {
  olddib->ResetDIB();
  delete olddib;
  return TRUE;
 }
 CTDIB* newdib = new CTDIB;
 int newwide=oldwide+max_move;
 lpDIB=NULL;
 if(!(newdib->SetExternals(&MyMemAlloc,&MyMemDelete,&MyMemLock,&MyMemUnLock)))
 {
  olddib->ResetDIB();
  delete olddib;
  delete newdib;
  return TRUE;
 }
 lpDIB=newdib->CreateDIBBegin(newwide,num_str,info.BitPerPixel);
 if(!lpDIB)
 {
	 olddib->ResetDIB();
     delete olddib;
	 delete newdib;
	 return TRUE;
 }
 Word32 X_DPM=0;
 Word32 Y_DPM=0;
 olddib->GetResolutionDPM(&X_DPM,&Y_DPM);
 newdib->SetResolutionDPI(info.DPIX,info.DPIY);
 newdib->SetResolutionDPM(X_DPM,Y_DPM);
 if(!(newdib->CreateDIBEnd()))
 {
	 olddib->ResetDIB();
     delete olddib;
	 delete newdib;
	 return TRUE;
 }
 int newbytewide=newdib->GetLineWidthInBytes();
 Word8* newpmasp=(Word8*)(newdib->GetPtrToBitFild());
 if(newwide>(int)(newdib->GetLineWidth()))
 {
	 olddib->ResetDIB();
     delete olddib;
	 newdib->DestroyDIB();
	 delete newdib;
	 return TRUE;
 }  
 CleanImage(pmasp,oldbytewide,num_str,(int)(olddib->GetLineWidth()));
 CopyMove(newpmasp,pmasp,newbytewide,oldbytewide,num_str,move);
     

 if(CIMAGE_WriteDIB((Word8*)ImageName,lpDIB,0))
 {
	 BITMAPINFOHEADER * lp = NULL ;
	 if(CIMAGE_ReadDIB((PWord8)ImageName,(Handle*)&lp,TRUE))
	 {
	  Handle hwnd = LDPUMA_CreateWindow(NAME_IMAGE_ORTOMOVE,lp);
	  info.Images|=IMAGE_ORTOMOVE;
	  strcpy((char*)info.szImageName,PUMA_IMAGE_ORTOMOVE);
	  SetPageInfo(hCPage,info);
	 }
	 else
	 {
      olddib->ResetDIB();
      delete olddib;
      newdib->DestroyDIB();
      delete newdib;
		 return FALSE;
	 }

     olddib->ResetDIB();
     delete olddib;
     newdib->DestroyDIB();
     delete newdib;

 //����� ������� ����������
	 if(!ExtractComponents(FALSE,NULL,(Word8*)PUMA_IMAGE_ORTOMOVE,Image))
		 return FALSE;
 //������� �����
	 CLINE_Reset();
	 if(!SearchLines(Image))
		 return FALSE;
 //����� ���� �������
	 if(!CalcIncline(Image))
		 return FALSE;
 }
 else
 {
     olddib->ResetDIB();
     delete olddib;
     newdib->DestroyDIB();
     delete newdib;
	 return FALSE;
 }



// time=clock()-time;
// LDPUMA_ConsoleN("Time work=%d",time);
 return TRUE;
}


void CopyMove(Word8* newpmasp,Word8* oldpmasp,int newbytewide,int oldbytewide,int num_str,int move)
{
 int max_move=abs((num_str*move)/2048);
 int spusk=(num_str+max_move-1)/max_move;
 int nowmove=0;
 int realspusk=spusk>>1;
 int bytemove=0;
 int newnowbyte;
 int oldnowbyte;
 int stopbyte;
 int newstopbyte;

 if(move>0)
 {
  stopbyte=num_str*oldbytewide-1;
  newstopbyte=num_str*newbytewide-1;
  oldnowbyte=stopbyte-oldbytewide+1;
  newnowbyte=newstopbyte-newbytewide+1;
  for(int i=num_str-1;i>=0;i--)
  {
   for(int k=0;k<bytemove;k++)
   {
	   newpmasp[newnowbyte]=255;
	   newnowbyte++;
   }
   
   newpmasp[newnowbyte]=~(255>>nowmove);

   while((oldnowbyte<stopbyte)&&(newnowbyte<newstopbyte-1))
   {
    newpmasp[newnowbyte]|=(oldpmasp[oldnowbyte]>>nowmove);
	newnowbyte++;
	newpmasp[newnowbyte]=(oldpmasp[oldnowbyte]<<(7-nowmove));
	oldnowbyte++;
   }
   newpmasp[newnowbyte]|=(255>>nowmove);
   newnowbyte++;
   while(newnowbyte<newstopbyte)
   {
	   newpmasp[newnowbyte]=255;
	   newnowbyte++;
   }

   stopbyte-=oldbytewide;
   newstopbyte-=newbytewide;
   oldnowbyte=stopbyte-oldbytewide+1;
   newnowbyte=newstopbyte-newbytewide+1;
   realspusk--;
   if(!realspusk)
   {
	   realspusk=spusk;
	   nowmove++;
	   if(nowmove==8)
	   {
		   nowmove=0;
		   bytemove++;
	   }
   }
  }
 }
 else
 {
  stopbyte=oldbytewide-1;
  newstopbyte=newbytewide-1;
  oldnowbyte=0;
  newnowbyte=0;
  for(int i=0;i<num_str;i++)
  {
   for(int k=0;k<bytemove;k++)
   {
	   newpmasp[newnowbyte]=255;
	   newnowbyte++;
   }
   
   newpmasp[newnowbyte]=~(255>>nowmove);

   while((oldnowbyte<stopbyte)&&(newnowbyte<newstopbyte-1))
   {
    newpmasp[newnowbyte]|=(oldpmasp[oldnowbyte]>>nowmove);
	newnowbyte++;
	newpmasp[newnowbyte]=(oldpmasp[oldnowbyte]<<(7-nowmove));
	oldnowbyte++;
   }
   newpmasp[newnowbyte]|=(255>>nowmove);
   newnowbyte++;
   while(newnowbyte<newstopbyte)
   {
	   newpmasp[newnowbyte]=255;
	   newnowbyte++;
   }

   stopbyte+=oldbytewide;
   newstopbyte+=newbytewide;
   oldnowbyte=stopbyte-oldbytewide+1;
   newnowbyte=newstopbyte-newbytewide+1;
   realspusk--;
   if(!realspusk)
   {
	   realspusk=spusk;
	   nowmove++;
	   if(nowmove==8)
	   {
		   nowmove=0;
		   bytemove++;
	   }
   }
  }
 }
}


void CleanImage(Word8* pmasp,int bytewide,int num_str,int wide)
{
	int realbytewide=((wide+7)>>3);
	int stop=num_str*bytewide;
	int nowbyte=bytewide-1;
	int nowbyte1=bytewide-2;
	int nowbyte2=bytewide-3;
	switch(bytewide-realbytewide)
	{
	case 0:break;
	case 1:
	       while(nowbyte<stop)
		   {
			   pmasp[nowbyte]=255;
			   nowbyte+=bytewide;
		   }
		   break;
	case 2:  
	       while(nowbyte1<stop)
		   {
			   pmasp[nowbyte]=255;
			   pmasp[nowbyte1]=255;
			   nowbyte+=bytewide;
			   nowbyte1+=bytewide;
		   }
		   break;
	case 3:
	       while(nowbyte2<stop)
		   {
			   pmasp[nowbyte]=255;
			   nowbyte+=bytewide;
			   pmasp[nowbyte1]=255;
			   nowbyte1+=bytewide;
			   pmasp[nowbyte2]=255;
			   nowbyte2+=bytewide;
		   }
	}
	int move=(realbytewide<<3)-wide;
	if(!move)
		return;
	move=7-move;
	nowbyte=realbytewide-1;
	while(nowbyte<stop)
	{
		pmasp[nowbyte]|=255>>move;
		nowbyte+=bytewide;
	}
}


void  MasCopy(Word8* oldpmasp,Word8* pmasp,int oldbytewide,int num_str)
{
	int j=oldbytewide*num_str;
	for(int i=0;i<j;i++)
		oldpmasp[i]=pmasp[i];
}

void* MyMemAlloc(Word32 size)
{
	return new char[size];
}

void MyMemDelete(void* mem)
{
	delete[] mem;
}

void *  MyMemLock(void* mem)
{

	return mem;
}

void MyMemUnLock(void* mem)
{
	return;
}

/*
switch(bytemove)
   {
   case 0:break;
   case 1:newpmasp[newnowbyte]=255;
	      newnowbyte++;
		  break;
   case 2:newpmasp[newnowbyte]=255;
	      newnowbyte++;
	      newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 3:newpmasp[newnowbyte]=255;
          newnowbyte++;
	      newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 4:newpmasp[newnowbyte]=255;
	      newnowbyte++;
	      newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 5:newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 6:newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 7:newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 8:newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   case 9:newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  newpmasp[newnowbyte]=255;
		  newnowbyte++;
		  break;
   }
   */