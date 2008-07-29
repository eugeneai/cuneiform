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

#include <map>
#include <string>
#include <fstream>
#include <algorithm>

#include "internal.h"
#pragma hdrstop

/*#include <windows.h>*/
#include "wmb.h"
#include "std.h"

#include "compat_defs.h"

STD_FUNC( Int32 ) stdMessageBox(
    const char * szMessageText,
    const char * szMessageTitle,
    Int32 nFlags)
{
#if 0
    Int32 nMFlags=0;
    if(nFlags & wMB_OK)
        nMFlags|=MB_OK;
    if((nFlags & wMB_OKCANCEL) == wMB_OKCANCEL)
        nMFlags|=MB_OKCANCEL;
    if((nFlags & wMB_ABORTRETRYIGNORE) == wMB_ABORTRETRYIGNORE)
        nMFlags|=MB_ABORTRETRYIGNORE;
    if((nFlags & wMB_YESNOCANCEL) == wMB_YESNOCANCEL)
        nMFlags|=MB_YESNOCANCEL;
    if((nFlags & wMB_YESNO) == wMB_YESNO)
        nMFlags|=MB_YESNO;
    if((nFlags & wMB_RETRYCANCEL) == wMB_RETRYCANCEL)
        nMFlags|=MB_RETRYCANCEL;
    if((nFlags & wMB_ICONHAND) == wMB_ICONHAND)
        nMFlags|=MB_ICONHAND;
    if((nFlags & wMB_ICONQUESTION) == wMB_ICONQUESTION)
        nMFlags|=MB_ICONQUESTION;
    if((nFlags & wMB_ICONEXCLAMATION) == wMB_ICONEXCLAMATION)
        nMFlags|=MB_ICONEXCLAMATION;
    if((nFlags & wMB_ICONASTERISK) == wMB_ICONASTERISK)
        nMFlags|=MB_ICONASTERISK;
    Int32 nRes=MessageBox(NULL,szMessageText,szMessageTitle,nMFlags);
    switch (nRes)
    {
        case IDABORT:
            return wIDABORT;
        case IDCANCEL:
            return wIDCANCEL;
        case IDIGNORE:
            return wIDIGNORE;
        case IDNO:
            return IDNO;
        case IDOK:
            return wIDOK;
        case IDRETRY:
            return wIDRETRY;
        case IDYES:
            return wIDYES;

    }
    return wIDOK;
#endif
    return 0;
}


#include "resource.h"

#pragma warning(disable:4786)
using namespace std;

static class CRptDlgMap
{
#define RDM_REPEAT                  0x00000000  //show this dlg next time
#define RDM_UNREP_SESS        0x00000100  //don't show dlg in this sess
#define RDM_UNREP_PERM       0x00000200  //don't show dlg always
#define RDM_UNREP			         0x00000300  //don't show dlg always
    typedef map<string,Int32> Tmap;
	Tmap mp;
    public:
    //construction/initialization
    CRptDlgMap() {;}
    ~CRptDlgMap() {;}
    CRptDlgMap(const char* pIniFile)
        {  Initialize(pIniFile); }
    Bool32 Initialize(const char* pIniFile);
    Bool32 Destroy();
    //get/set show props
    Int32 GetShowProps(const char* pDlgKey)
        { return mp[string(pDlgKey)]; }
    void SetShowProps(const char* pDlgKey,Int32 nProps)
        { mp[string(pDlgKey)]=nProps; }
	Bool32 Load(const char* pFileName);
	Bool32 Save(const char* pFileName);
} *pRptMap=NULL;

const char szDlgRptSecBr[]="[Dialog Rpt]";
const char szDlgRptSec[]="Dialog Rpt";

Bool32 CRptDlgMap::Load(const char* pFileName)
{
	try
	{
		char szBuff[1024]; szBuff[0]=0;
		ifstream ifs(pFileName);
		Bool32 bRes=TRUE;
		Bool32 bInSection=FALSE;
		while(ifs.get(szBuff,sizeof(szBuff),'\n') && ifs.get())
		{
			if(!strncmp(szBuff,szDlgRptSecBr,sizeof(szDlgRptSecBr)))
			{
				bInSection=TRUE;
				continue;
			}
			if(bInSection && szBuff[0]=='[')
				break;
			if(!bInSection || szBuff[0]==0)
				continue;
			string curr_str(szBuff);
			string::iterator pEql=find(curr_str.begin(),curr_str.end(),'=');
			if(pEql==curr_str.end())
			{
				bRes=FALSE;
				continue;
			}
			string key_str(curr_str.begin(),pEql);
			++pEql;
			mp[key_str]=atoi((const char*)*pEql);
		};
		return bRes;
	}
	catch(...)
	{
		return FALSE;
	}
}

Bool32 CRptDlgMap::Save(const char* pFileName)
{
	for(Tmap::iterator it=mp.begin();it!=mp.end();it++)
		if(it->second & RDM_UNREP_PERM)
		{
			stdSetProfileInt(it->second,pFileName,szDlgRptSec,it->first.c_str());
		}
	/*
	try
	{
		ofstream ofs(pFileName);
		Bool32 bRes=TRUE;
		for(Tmap::iterator it=mp.begin();it!=mp.end();it++)
			if(it->second & RDM_UNREP_PERM)
				ofs << it->first << '\t' << it->second << "\n";
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
	*/
	return TRUE;
}

static char szRptStoreFileName[_MAX_PATH]={0};

Bool32 InitRptMap(const char* pFileName)
{
    try
    {
		strcpy(szRptStoreFileName,pFileName);
        pRptMap=new(CRptDlgMap);
        if(pRptMap==NULL)
			throw;
		pRptMap->Load(szRptStoreFileName);
		return TRUE;
    }
    catch(...)
    {
        return FALSE;
    }
}

Bool32 FreeRptMap()
{
    try
    {
		//save map
        if(pRptMap)
        {
			pRptMap->Save(szRptStoreFileName);
            delete(pRptMap);
            pRptMap=NULL;
        }
       return TRUE;
    }
    catch(...)
    {
        return FALSE;
    }
}

#define MB_STYLE( flags ) (flags & 0x0000000f)
#define MB_ICON( flags ) (flags & 0x000000f0)

#define RPD_ENWND_OK            0x00000001
#define RPD_ENWND_CANCEL  0x00000002
#define RPD_ENWND_ABORT    0x00000004
#define RPD_ENWND_RETRY     0x00000008
#define RPD_ENWND_IGNORE  0x00000010
#define RPD_ENWND_YES          0x00000020
#define RPD_ENWND_NO            0x00000040

#define RPD_EDT_WD_ICON         222
#define RPD_EDT_WD_NOICON    264
#define RPD_BUTTON_TOP           42
#define RPD_BUTTON_HGT           14
#define RPD_BUTTON1_WD           76
#define RPD_BUTTON1_LFT          194
#define RPD_BUTTON2_WD           55
#define RPD_BUTTON21_LFT        157
#define RPD_BUTTON22_LFT        216
#define RPD_BUTTON3_WD           46
#define RPD_BUTTON31_LFT        125
#define RPD_BUTTON32_LFT        175
#define RPD_BUTTON33_LFT        225

#define RPD_ENWND_CANCEL  0x00000002
#define RPD_ENWND_ABORT    0x00000004
#define RPD_ENWND_RETRY     0x00000008
#define RPD_ENWND_IGNORE  0x00000010
#define RPD_ENWND_YES          0x00000020
#define RPD_ENWND_NO            0x00000040

#define RPD_DLG_DU_WIDTH       278
#define RPD_DLG_DU_HEIGHT     63
static Bool32 GetDlgUnitsScale(float& fXScale,float& fYScale,HWND hDlg)
{
    RECT rc={0};
    ::GetClientRect(hDlg,&rc);
    fXScale=1000*(rc.right-rc.left)/RPD_DLG_DU_WIDTH;
    fYScale=1000*(rc.bottom-rc.top)/RPD_DLG_DU_HEIGHT;
    fXScale/=1000;
    fYScale/=1000;
    return TRUE;
}

static void SetRptDlgButtonsPlacement(HWND hWnd,Int32 nBtns,HWND* pBtns)
{
#if 0
    float fXScale=1,fYScale=1;
    GetDlgUnitsScale(fXScale,fYScale,hWnd);
    HWND* pWnd=pBtns;
    switch(nBtns)
    {
    case 1:
        ::MoveWindow(pBtns[0],RPD_BUTTON1_LFT*fXScale,RPD_BUTTON_TOP*fYScale,RPD_BUTTON1_WD*fXScale,RPD_BUTTON_HGT*fYScale,TRUE);
        break;
    case 2:
        ::MoveWindow(pBtns[0],RPD_BUTTON21_LFT*fXScale,RPD_BUTTON_TOP*fYScale,RPD_BUTTON2_WD*fXScale,RPD_BUTTON_HGT*fYScale,TRUE);
        ::MoveWindow(pBtns[1],RPD_BUTTON22_LFT*fXScale,RPD_BUTTON_TOP*fYScale,RPD_BUTTON2_WD*fXScale,RPD_BUTTON_HGT*fYScale,TRUE);
        break;
    case 3:
        ::MoveWindow(pBtns[0],RPD_BUTTON31_LFT*fXScale,RPD_BUTTON_TOP*fYScale,RPD_BUTTON3_WD*fXScale,RPD_BUTTON_HGT*fYScale,TRUE);
        ::MoveWindow(pBtns[1],RPD_BUTTON32_LFT*fXScale,RPD_BUTTON_TOP*fYScale,RPD_BUTTON3_WD*fXScale,RPD_BUTTON_HGT*fYScale,TRUE);
        ::MoveWindow(pBtns[2],RPD_BUTTON33_LFT*fXScale,RPD_BUTTON_TOP*fYScale,RPD_BUTTON3_WD*fXScale,RPD_BUTTON_HGT*fYScale,TRUE);
        break;
    }
#endif
}

static void VisualizeWindow(HWND hWnd,Bool32 bVisualize)
{
#if 0
    LONG ws=::GetWindowLong(hWnd,GWL_STYLE);
    if(bVisualize)
        ws|=WS_VISIBLE;
    else
        ws&=~WS_VISIBLE;
    ::SetWindowLong(hWnd,GWL_STYLE,ws);
#endif
}

static void EnableRptDlgWindows(HWND hWnd,Int32 nFlags)
{
#if 0
    HWND hWndCtrl=NULL;
    hWndCtrl=::GetDlgItem(hWnd,ID_OK);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_OK);
    hWndCtrl=::GetDlgItem(hWnd,ID_CANCEL);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_CANCEL);
    hWndCtrl=::GetDlgItem(hWnd,ID_ABORT);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_ABORT);
    hWndCtrl=::GetDlgItem(hWnd,ID_RETRY);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_RETRY);
    hWndCtrl=::GetDlgItem(hWnd,ID_IGNORE);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_IGNORE);
    hWndCtrl=::GetDlgItem(hWnd,ID_YES);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_YES);
    hWndCtrl=::GetDlgItem(hWnd,ID_NO);
    if(hWndCtrl)
        VisualizeWindow(hWndCtrl,nFlags & RPD_ENWND_NO);
#endif
}

typedef struct tagDlgProcParms
{
    Int32 nFlags;
    const char* pszTitle;
    const char* pszMessageText;
	Bool32 bNoRepeat;
} TDlgProcParms;

#if 0
static Int32 bNoRepeat=-1;
static HICON hIcon=NULL;
static BOOL WINAPI DialogProc( HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    float fXScale=1,fYScale=1;
    GetDlgUnitsScale(fXScale,fYScale,hwndDlg);
    HWND hWndCtrl=NULL;
    HWND hWnds[10]={0};
    TDlgProcParms* pParm;
	HWND hChk=NULL;
	HDC hDC=NULL;
	switch (uMsg)
	{
    case WM_INITDIALOG:
        pParm=(TDlgProcParms*)lParam;
        //set texts
        ::SetWindowText(hwndDlg,pParm->pszTitle);
        ::SetWindowText(::GetDlgItem(hwndDlg,IDC_RDLG_MSGTEXT),pParm->pszMessageText);
        //enable/disable specific buttons
        switch (MB_STYLE(pParm->nFlags))
        {
        case MB_OK:
            EnableRptDlgWindows(hwndDlg,RPD_ENWND_OK);
            hWnds[0]=::GetDlgItem(hwndDlg,ID_OK);
            SetRptDlgButtonsPlacement(hwndDlg,1,hWnds);
            break;
        case MB_OKCANCEL:
            EnableRptDlgWindows(hwndDlg,RPD_ENWND_OK | RPD_ENWND_CANCEL);
            hWnds[0]=::GetDlgItem(hwndDlg,ID_OK);
            hWnds[1]=::GetDlgItem(hwndDlg,ID_CANCEL);
            SetRptDlgButtonsPlacement(hwndDlg,2,hWnds);
            break;
        case MB_ABORTRETRYIGNORE:
            EnableRptDlgWindows(hwndDlg,RPD_ENWND_ABORT | RPD_ENWND_RETRY | RPD_ENWND_IGNORE);
            hWnds[0]=::GetDlgItem(hwndDlg,ID_ABORT);
            hWnds[1]=::GetDlgItem(hwndDlg,ID_RETRY);
            hWnds[2]=::GetDlgItem(hwndDlg,ID_IGNORE);
            SetRptDlgButtonsPlacement(hwndDlg,3,hWnds);
            break;
        case MB_YESNOCANCEL:
            EnableRptDlgWindows(hwndDlg,RPD_ENWND_YES | RPD_ENWND_NO | RPD_ENWND_CANCEL);
            hWnds[0]=::GetDlgItem(hwndDlg,ID_YES);
            hWnds[1]=::GetDlgItem(hwndDlg,ID_NO);
            hWnds[2]=::GetDlgItem(hwndDlg,ID_CANCEL);
            SetRptDlgButtonsPlacement(hwndDlg,3,hWnds);
            break;
        case MB_YESNO:
            EnableRptDlgWindows(hwndDlg,RPD_ENWND_YES | RPD_ENWND_NO);
            hWnds[0]=::GetDlgItem(hwndDlg,ID_YES);
            hWnds[1]=::GetDlgItem(hwndDlg,ID_NO);
            SetRptDlgButtonsPlacement(hwndDlg,2,hWnds);
            break;
        case MB_RETRYCANCEL:
            EnableRptDlgWindows(hwndDlg,RPD_ENWND_RETRY | RPD_ENWND_CANCEL);
            hWnds[0]=::GetDlgItem(hwndDlg,ID_RETRY);
            hWnds[1]=::GetDlgItem(hwndDlg,ID_CANCEL);
            SetRptDlgButtonsPlacement(hwndDlg,2,hWnds);
            break;
        }
		switch (MB_ICON(pParm->nFlags))
        {
			case 0: //no icon
				hIcon=NULL; break;
			case MB_ICONHAND:
				hIcon=LoadIcon(NULL,IDI_ERROR); break;
			case MB_ICONQUESTION:
				hIcon=LoadIcon(NULL,IDI_QUESTION); break;
			case MB_ICONEXCLAMATION:
				hIcon=LoadIcon(NULL,IDI_EXCLAMATION); break;
			case MB_ICONASTERISK:
				hIcon=LoadIcon(NULL,IDI_ASTERISK); break;
		}
		if(hIcon)
			::MoveWindow(GetDlgItem(hwndDlg,IDC_RDLG_MSGTEXT),23*fXScale,12*fYScale,244*fXScale,22*fYScale,TRUE);
		else
			::MoveWindow(GetDlgItem(hwndDlg,IDC_RDLG_MSGTEXT),7*fXScale,12*fYScale,260*fXScale,22*fYScale,TRUE);
        break;
    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
        case ID_OK:
			EndDialog(hwndDlg, IDOK); break;
		case ID_CANCEL:	case IDCANCEL:
			EndDialog(hwndDlg, IDCANCEL); break;
        case ID_ABORT:
			EndDialog(hwndDlg, IDABORT); break;
        case ID_RETRY:
			EndDialog(hwndDlg, IDRETRY); break;
        case ID_IGNORE:
			EndDialog(hwndDlg, IDIGNORE); break;
        case ID_YES:
			EndDialog(hwndDlg, IDYES); break;
        case ID_NO:
			EndDialog(hwndDlg, IDNO); break;
		}
		hChk=::GetDlgItem(hwndDlg,IDC_RDLG_CHK_REPEAT);
		if(hChk)
			bNoRepeat=(BOOL)::SendMessage(hChk, BM_GETCHECK, 0, 0);
		break;
    case WM_PAINT:
		{
			if(hIcon)
			{
				hDC=::GetDC(hwndDlg);
				if(hDC)
				{
					::DrawIcon(hDC,7*fXScale,16*fYScale,hIcon);
					::ReleaseDC(hwndDlg,hDC);
				}
			}
		}
	}

	return FALSE;
}
#endif

STD_FUNC( Int32 ) stdRptMessageBox(
  const char * szMessageText,
  const char * szMessageTitle,
  Int32 nFlags,
  const char * szKey)
{
#if 0
    TDlgProcParms parms={nFlags,szMessageTitle,szMessageText};
    HINSTANCE hModule=::GetModuleHandle("std32.dll");
	bNoRepeat=-1;
	if(pRptMap->GetShowProps(szKey ? szKey : szMessageText) & RDM_UNREP)
		return pRptMap->GetShowProps(szKey ? szKey : szMessageText) & ~RDM_UNREP;
    int nRes=::DialogBoxParam(hModule,
        MAKEINTRESOURCE(IDD_REP_DLG),
        ::GetActiveWindow(),&DialogProc,(LONG)&parms);
	if(hIcon)
		::DestroyIcon(hIcon);
	if(bNoRepeat==1)
		pRptMap->SetShowProps(szKey ? szKey : szMessageText,RDM_UNREP_PERM | nRes);
    return nRes;
#endif
    return 0;
}

