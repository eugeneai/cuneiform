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

#include "internal.h"
#pragma hdrstop



#include "_prt.h"

static int gl_iTransaction = 0;
static int  gl_iEventCount = 0;
static int  gl_iLastEventNo = 200;
static int  gl_iTableEventCount = 0;
static time_t gl_szOldTime = {0};

//static stdPrtFILE theFile("a+");
//static stdPrtFILE theFile("a+");
static XStack<StdPrtEventData> xsEventTypeData;

void CPrtTransactionBuffer::FreeBuffer()
{
   m_buffer.clear();
};

static CPrtTransactionBuffer* pTransactionBuffer = NULL;


static StdPrtEvent szStdPrtSysEventList[] = 
   {
      {"��������������� ��� ��������� ����� %03i(%i ����������). ������ ��������� - \"%s\"",SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME,0,0}, // ����������� �������
      {"��������� ���������� �������:\t%s",0,1,0}, // ������ 
      {"%s ����������:\t������-%s\t�������-%s\t������������-%s",SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME,2,0},
      {"",SPE_PUBLIC|SPE_WAIT,3,0},
      {"",SPE_PUBLIC|SPE_WAIT,4,0},
      {"",SPE_PUBLIC|SPE_WAIT,5,0},
      {"",SPE_PUBLIC|SPE_WAIT,6,0},
      {"",SPE_PUBLIC|SPE_WAIT,7,0},
      {"",SPE_PUBLIC|SPE_WAIT,8,0},
      {"�� ������ %s ���������� - %s %s, ������������ - %s",SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME,9,0},
      {"������� %s %s(������ - %s, ������������ - %s)",SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME,10,0},
      {"�������� %s %s ���������� - %s, ������ - %s, ���������� %s",SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME,11,0}
   };

//static CSysDataEventTypeList SysDataToEventTypeList; // ���������� ��������� ��������� � xsEventTypeData

//static CTableEvnFiller *gl_TableEvnCreator = NULL;

/*bool ReadFromEvnTable(char* TableName)
{
   if(!TableName)
      RET_FALSE;
   FILE* fl = fopen(TableName,"rt");
   if(!fl)
      RET_FALSE;
   char r_string[1024*4+256] = {0}; // 1024*4 - ����. ������ ������ � �������
   int i = 99;
   while(fgets(r_string,(1024*4+256-1),fl))
   {
      char* n_string = strchr(r_string,'\t'); // ��������� �� ������
      if(!n_string)
        continue;
      *n_string = 0; // ��������� ������ �� ������ ���������
      n_string++;
      char *p = strchr(n_string,'\n');
      if(p)
         *p=0;
      char* p_string = strchr(n_string,'\t');
      if(p_string)
      {
         *p_string = 0;
         p++;
      };
      char f_string[256];
      EvnParseFormat(n_string,f_string);
      int TblEvnNo = atoi(n_string);
      if(TblEvnNo < 100)
         continue;
      m_TableEvnCreator.xsTblEventData[TblEvnNo-100].hEvent = i;
      strcpy(m_TableEvnCreator.xsTblEventData[TblEvnNo-100].szFormat,r_string);
      m_TableEvnCreator.xsTblEventData[TblEvnNo-100].nFlags = (p_string==NULL) ? SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME : atoi(p_string);
      xsEventTypeData[i].iEvnNo = TblEvnNo;
      strcpy(xsEventTypeData[i].FrmtEvnString,f_string);
   };
   fclose(fl);
   return true;
};
*/
CTableEvnFiller::CTableEvnFiller()
{  
   char szString[_MAX_PATH] = {0};
   Int32 size = _MAX_PATH;
   stdGetProfileString(szString,&size,"protocol.ini","Options","EvnTablePath",STD_SETPROF_DIR_PROJECT);
   strcpy(m_szTableName,szString);
   xsTblEventData.erase(xsTblEventData.begin(),xsTblEventData.end());
   if(m_szTableName[0]==0||stdAccess(m_szTableName,0)==-1 )
      RET_VOID;
   //xsTblEventData.Destroy();
   //xsTblEventData.CreateOf(100);
   //xsTblEventData.reserve(100);
   xsTblEventData.resize(100);
   //for(int i = 0 ; i < xsTblEventData.GetCurCnt(); i++)
   for(int i = 0 ; i < xsTblEventData.size(); i++)
   {
      xsTblEventData[i].szFormat = new char[256];
      if(xsTblEventData[i].szFormat)
         memset(xsTblEventData[i].szFormat,0,256);
   }
//   ReadFromEvnTable(m_szTableName);
   
   FILE* fl = fopen(m_szTableName,"rt");
   if(fl)
   {
   //      RET_FALSE;
      char r_string[1024*4+256] = {0}; // 1024*4 - ����. ������ ������ � �������
      int i = 99;
      while(fgets(r_string,(1024*4+256-1),fl))
      {
         char* n_string = strchr(r_string,'\t'); // ��������� �� ������
         if(!n_string)
           continue;
         *n_string = 0; // ��������� ������ �� ������ ���������
         n_string++;
         char *p = strchr(n_string,'\n');
         if(p)
            *p=0;
         char* p_string = strchr(n_string,'\t');
         if(p_string)
         {
            *p_string = 0;
            p++;
         };
         char f_string[256];
         EvnParseFormat(r_string,f_string);
         int TblEvnNo = atoi(n_string);
         if(TblEvnNo < 100)
            continue;
         xsTblEventData[TblEvnNo-100].hEvent = i;
         strcpy(xsTblEventData[TblEvnNo-100].szFormat,r_string);
         xsTblEventData[TblEvnNo-100].nFlags = /*(p_string==NULL) ? */SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME/* : atoi(p_string)*/;
         xsEventTypeData[i].iEvnNo = TblEvnNo;
         strcpy(xsEventTypeData[i].FrmtEvnString,f_string);
         ++i;
      };
      fclose(fl);
   };
};

CTableEvnFiller::~CTableEvnFiller()
{
//   for(int i = 0 ; i < xsTblEventData.GetCurCnt(); i++)
   for(int i = 0 ; i < xsTblEventData.size(); i++)
   {
      char *p = xsTblEventData[i].szFormat;
      if(p)
      {
         delete p;
         xsTblEventData[i].szFormat = NULL;
      }
   }
};
bool CTableEvnFiller::OpenEvnTable(char *TableName)
{
//   return ReadFromEvnTable(TableName);
   if(m_szTableName[0]==0||stdAccess(m_szTableName,0)==-1 )
      RET_FALSE;
   FILE* fl = fopen(m_szTableName,"rt");
   if(fl)
      RET_FALSE;
   char r_string[1024*4+256] = {0}; // 1024*4 - ����. ������ ������ � �������
   int i = 99;
//   for(int ii = 0 ; ii < xsTblEventData.GetCurCnt(); ii++)
   for(int ii = 0 ; ii < xsTblEventData.size(); ii++)
      memset(xsTblEventData[ii].szFormat,0,256);

   while(fgets(r_string,(1024*4+256-1),fl))
   {
      char* n_string = strchr(r_string,'\t'); // ��������� �� ������
      if(!n_string)
        continue;
      *n_string = 0; // ��������� ������ �� ������ ���������
      n_string++;
      char *p = strchr(n_string,'\n');
      if(p)
         *p=0;
      char* p_string = strchr(n_string,'\t');
      if(p_string)
      {
         *p_string = 0;
         p++;
      };
      char f_string[256];
      EvnParseFormat(r_string,f_string);
      int TblEvnNo = atoi(n_string);
      if(TblEvnNo < 100)
         continue;
      xsTblEventData[TblEvnNo-100].hEvent = i;
      strcpy(xsTblEventData[TblEvnNo-100].szFormat,r_string);
      xsTblEventData[TblEvnNo-100].nFlags = (p_string==NULL) ? SPE_PUBLIC|SPE_WAIT|SPE_WITHTIME : atoi(p_string);
      xsEventTypeData[i].iEvnNo = TblEvnNo;
      strcpy(xsEventTypeData[i].FrmtEvnString,f_string);
      ++i;
   };
   fclose(fl);
   return true;
};


Bool32 stdPrtConsole::SendTextToConsole(char *text, int len)
{
   if(!hConsoleOutput)
      return 0;
   if(!uiMesasageHandle)
      RET_FALSE;
   HANDLE hMessageText = 0;
   hMessageText = ::GlobalAlloc(GPTR,(len+1)*sizeof(char));
   LPVOID lpText = ::GlobalLock(hMessageText);
   memset(lpText,0,sizeof(char)*(len+1));
   if(!lpText)
      RET_FALSE;
   strcpy((char*)lpText,text);
   ::GlobalUnlock(hMessageText);
   ::PostMessage(hConsoleOutput,uiMesasageHandle,reinterpret_cast<unsigned int>(hMessageText),len);
   return TRUE;
};

Bool32 stdPrtConsole::AllocPrtConsole()
{
   if(hConsoleOutput)
      return TRUE;
   hConsoleOutput = FindWindow( NULL, "PrtConsole");

   bUseConsole = TRUE;
   if(hConsoleOutput)
      return TRUE;
   return FALSE;
};



Bool32 EvnParseFormat(char* in, char* out)
{
   if(!in || !out)
      RET_ZERO;
   char *str = in;
   char out_str[256] = {0};
   Bool startf = FALSE;
   int i = 0; 
   int k = 0;
   char ch = 0;
   while(*str)
   {
      if(*str=='%')
      {
         startf = TRUE;
         out_str[i] = '\t';
         i++;
         k++;
      };

      if(startf)
      {
         out_str[i] = *str;
         i++;
      };

      if(*str == 's' ||
         *str == 'i' ||
         *str == 'd')
         startf = FALSE;
      ch = *str;
      str++;
   };
   strcpy(out,out_str);
   return k;
};

bool CPrtTransactionBuffer::FlushToDisk()
{
   char *buffer = NULL;
   buffer = new char[m_buffer_len+1];
   memset(buffer,0,m_buffer_len+1);
   if(!buffer)
      RET_FALSE;
   for(list<string>::iterator p = m_buffer.begin(); p!=m_buffer.end(); p++)
      strcat(buffer,p->c_str());
   CPrtSendEventToPublic sender;
   Bool32 res = sender(buffer);
   delete buffer;
   if(res)
      return Clear();
   else
      RET_FALSE;
};

bool CPrtTransactionBuffer::Finish()
{
   if(!m_bStart)
      RET_FALSE;
   if(!FlushToDisk())
      RET_FALSE;
   return Clear();
};

bool CPrtTransactionBuffer::Rollback()
{
   return Clear();
};

bool CPrtTransactionBuffer::Start()
{
   if(m_bStart)
      RET_FALSE;
   m_bStart = true;
   return m_bStart;
};

bool CPrtTransactionBuffer::Add(char *str)
{
   m_buffer.push_back(string(str));
   m_buffer_len += strlen(str);
   m_buffer_len++;
   return true;
};


bool CPrtTransactionBuffer::Clear()
{
   m_buffer.clear();
   m_buffer_len = 0;
   m_bStart = false;
   return true;
};
Bool32 GetTimeString(char* tm_string)
{
   if(!tm_string)
      RET_FALSE;
 	struct tm *newtime;
	time_t long_time;
	time( &long_time );  
	newtime = localtime( &long_time ); 
   sprintf(tm_string,
      "%02i:%02i:%02i %02i.%02i.%04i",
      newtime->tm_hour,
      newtime->tm_min,
      newtime->tm_sec,
      newtime->tm_mday,
		newtime->tm_mon+1,
		newtime->tm_year+1900
      );
   return TRUE;
}
Bool32 CPrtEventSender::SendEvent(StdPrtEvent* pspe, va_list& List)
{
   
   Bool32 res1=TRUE,res2,res3;
   /* ���������� ������ ��������� ��� ���������� � ���������� ������*/
   if(pspe->nFlags&SPE_PUBLIC)
   {
      char service_buf[128] = {0};
      char service_MesBuf[8*1024-128] = {0};
      if(pspe->nFlags&SPE_WITHTIME)
      {
         char szTimer[256] = {0};
         GetTimeString(szTimer);
         sprintf(service_buf,"#%05i\tEvn=%03i\tST=%s",gl_iEventCount,xsEventTypeData[pspe->hEvent].iEvnNo,szTimer);
      }
      else
         sprintf(service_buf,"#%05i\tEvn=%03i",gl_iEventCount,xsEventTypeData[pspe->hEvent].iEvnNo);
      vsprintf(service_MesBuf,xsEventTypeData[pspe->hEvent].FrmtEvnString, List );
      sprintf(MessageBuffer,"%s%s\n",service_buf,service_MesBuf);
      res1 = SendEvent(MessageBuffer,3);
   }
   /**/
   
   /* ���������� ������ ��������� ��� ���������� � ��������� ������*/
   {
      char service_buf[128] = {0};
      char service_MesBuf[8*1024-128] = {0};
      sprintf(service_buf,"#%05i\tEvn=%03i",gl_iEventCount,xsEventTypeData[pspe->hEvent].iEvnNo);
      vsprintf(service_MesBuf,xsEventTypeData[pspe->hEvent].FrmtEvnString, List );
      sprintf(MessageBuffer,"%s%s\n",service_buf,service_MesBuf);
      res2 = SendEvent(MessageBuffer,1);
   };
   /**/

   /* ���������� ������ ��������� ��� ������ �� �������*/
   {
      char service_buf[128] = {0};
      char service_MesBuf[8*1024-128] = {0};
      sprintf(service_buf,"#%05i\tEvn=%03i",gl_iEventCount,xsEventTypeData[pspe->hEvent].iEvnNo);
      vsprintf(service_MesBuf,pspe->szFormat, List );
      sprintf(MessageBuffer,"%s\t%s",service_buf,service_MesBuf);
      res3 = SendEvent(MessageBuffer,2);
   };
   /**/
   ++gl_iEventCount;
   return (res1&&res2&&res3);
}

Bool32 CPrtEventSender::SendEvent(char* EventText,Int32 EvnType)
{
   Bool32 res1 = TRUE;//,res2 = TRUE,res3 = TRUE;
   switch(EvnType)
   {
   case 3:
      if(!gl_iTransaction)
         res1 = SenderToPublic(EventText);
      else
         pTransactionBuffer->Add(EventText);
      break;
   case 2:
      res1 = SenderToConsole(EventText);
      break;
   case 1:
      res1 = SenderToFile(EventText);
      break;
   }
   return res1;//(res1&&res2&&res2);
};
   
Bool32 CPrtSysEventSender::SendSysEvent(Int32 SysEvnNo,...)
{
   if(SysEvnNo >= CUR_SYS_EVN_COUNT || SysEvnNo < 0)
      RET_FALSE;
   va_list List;
   va_start(List, SysEvnNo);
   Bool32 res = FALSE;
   if(SysEvnNo<100)
      res = EventSender.SendEvent(&szStdPrtSysEventList[SysEvnNo-1], List);
   else if(SysEvnNo < 200)
   {
      if(m_TableEvnCreator==NULL)
         m_TableEvnCreator = new CTableEvnFiller;
      res = EventSender.SendEvent(&m_TableEvnCreator->xsTblEventData[SysEvnNo-100], List);
   }
   va_end( List );
   return res;
};

Bool32 CPrtSysEventSender::SendSysEvent(Int32 SysEvnNo, va_list& List)
{
   if(SysEvnNo<100)
      return EventSender.SendEvent(&szStdPrtSysEventList[SysEvnNo-1], List);
   else if(SysEvnNo < 200)
   {
      if(m_TableEvnCreator==NULL)
         m_TableEvnCreator = new CTableEvnFiller;
      if(m_TableEvnCreator->xsTblEventData.size() == 0)
         RET_FALSE;
      return EventSender.SendEvent(&m_TableEvnCreator->xsTblEventData[SysEvnNo-100], List);
   }
   //return EventSender.SendEvent(&szStdPrtSysEventList[SysEvnNo-1], List);
   RET_FALSE;
};

Bool32 CPrtSysEventSender::SendEvent(StdPrtEvent* pspe)
{
   SendTimerEvent();
   if(!pspe->hEvent)
   {
      SendEnvRegistrationEvent(pspe);
   };
   return TRUE;
};

Bool32 CPrtSysEventSender::SendEnvRegistrationEvent(StdPrtEvent* pspe)
{
   StdPrtEventData szEvnData = {0};
   Int32 res = EvnParseFormat(pspe->szFormat,szEvnData.FrmtEvnString);
   if(!res)
      RET_FALSE;
   szEvnData.iEvnNo = ++gl_iLastEventNo;
   xsEventTypeData.Push(&szEvnData,&(pspe->hEvent));
   //vector<StdPrtEventData>::iterator p = xsEventTypeData.insert(xsEventTypeData.end(),szEvnData);//,&(pspe->hEvent));
   //pspe->hEvent = (xsEventTypeData.begin()-p)/sizeof(StdPrtEventData);
   //pspe->hEvent = xsEventTypeData.GetCurCnt();//xsEventTypeData.size();
   //pspe->hEvent++;
   return SendSysEvent(0, szEvnData.iEvnNo ,res , pspe->szFormat);
};

Bool32 CPrtSysEventSender::SendTimerEvent()
{
   time_t new_time;
   time(&new_time);
   localtime( &new_time );
   struct tm *date;
   date = localtime( &new_time );
   if(!gl_szOldTime || ((new_time-gl_szOldTime) > TIMER_DELTA*60))
   {
      char datetime[128] = {0};
      strcpy(datetime,asctime(date));
      SendSysEvent(1, datetime);
      gl_szOldTime = new_time;
   };
   return TRUE;   
};

void CPrtSysEventSender::Destroy()
{
   if(m_TableEvnCreator)
   {
      /*m_TableEvnCreator->xsTblEventData.erase(m_TableEvnCreator->xsTblEventData.begin(),
         m_TableEvnCreator->xsTblEventData.end());*/
      delete m_TableEvnCreator;
      m_TableEvnCreator = NULL;
   }

};


STD_FUNC(Bool32) stdPrtStartConsole()
{
   Bool32 res = stdPrtConsole.AllocPrtConsole();
   return res;
};

STD_FUNC(void) stdPrtStopConsole()
{
   stdPrtConsole.FreePrtConsole();
};

STD_FUNC(Int32) stdPrt( StdPrtEvent* pspe, ... )
{
   if (NULL==(FILE*)theFile)
      RET_ZERO;
   va_list List;
   va_start(List, pspe);
   CPrtSendEvent Event;
   Int32 res = Event(pspe,List);
   va_end( List );
   return res;
};

static CPrtSysEventSender SysEvent;

STD_FUNC(Int32) stdSysPrt( Int32 EvnNo, ... )
{
   if (NULL==(FILE*)theFile)
      RET_ZERO;
   va_list List;
   va_start(List, EvnNo);
// CPrtSysEventSender Event;
   Int32 res = SysEvent.SendSysEvent(EvnNo,List);
   va_end( List ); 
   return res;
};

STD_FUNC(Int32) stdSysPrt( Int32 EvnNo, va_list& List )
{
   if (NULL==(FILE*)theFile)
      RET_ZERO;
// CPrtSysEventSender Event;
   Int32 res = SysEvent.SendSysEvent(EvnNo,List);
   return res;
};

STD_FUNC(Int32) stdPrt( StdPrtEvent* pspe,  va_list& List)
{
   if (NULL==(FILE*)theFile)
      RET_ZERO;
   CPrtSendEvent Event;
   Int32 res = Event(pspe,List);
   return res;
};

STD_FUNC(Bool32) stdPrtStartTransaction(char* user_name,char* prog_id)
{
   pTransactionBuffer->Start();
   gl_iTransaction++;
   char comp_name[MAX_COMPUTERNAME_LENGTH+1];
	DWORD sz=sizeof(comp_name);
	GetComputerName(comp_name,&sz);
   stdSysPrt(3,"������",comp_name,prog_id,user_name);
   return TRUE;
};

STD_FUNC(Bool32) stdPrtRollback()
{
   if(gl_iTransaction)
   {
      if(!pTransactionBuffer->Rollback())
         RET_FALSE;
      gl_iTransaction--;
      return TRUE;
   }
   else
      RET_FALSE;
};

STD_FUNC(Bool32) stdPrtEndTransaction(char* user_name,char* prog_id)
{
   if(gl_iTransaction)
   {
      char comp_name[MAX_COMPUTERNAME_LENGTH+1];
      DWORD sz=sizeof(comp_name);
	   GetComputerName(comp_name,&sz);
      stdSysPrt(3,"����������",comp_name,prog_id,user_name);
      if(!pTransactionBuffer->Finish())
         RET_FALSE;
      gl_iTransaction--;
      return TRUE;
   }
   else
      RET_FALSE;
};

static char*   pParamsString = NULL;
static int     iParamsStringLen = 0;
static XStack<int>  xsParamsShift;
//vector<xsParamsShift>
static StdPrtEvent szCurEvn = {0};
typedef XStack<char> XString; 

static stdPrtFILE theParaseFile;



bool PrtLoad()
{
   StdPrtEventData szStdPrtSysEventDataList[] =
   {
      {"\tEvnNo=%03i\tEvnPar=%i\t%s",1},
      {"\t%s",2},
      {"\tTransaction\t%s\t%s\t%s",3},
      {"",4},
      {"",5},
      {"",6},
      {"",7},
      {"",8},
      {"",9},
      {"\t%s\t%s\t%s\t%s",10},
      {"\t%s\t%s\t%s\t%s",11},
      {"\t%s\t%s\t%s\t%s\t%s",12}
   };

//   xsEventTypeData.reserve(200);
   theFile = new stdPrtFILE("a+");
   xsEventTypeData.Create(200,200);
   pTransactionBuffer = new CPrtTransactionBuffer;
   long i;
   for(i = 0; i < CUR_SYS_EVN_COUNT; i++)
      xsEventTypeData[i] = szStdPrtSysEventDataList[i];
   return true;
};
void PrtUnload()
{
//   xsEventTypeData.erase(xsEventTypeData.begin(),xsEventTypeData.end());
//   XString.Destroy();
   xsParamsShift.Destroy();
   delete pTransactionBuffer;//.FreeBuffer();
   pTransactionBuffer = NULL;
   xsEventTypeData.Destroy();
   //xsEventTypeData.clear();
   //xsEventTypeData.~vector();
   SysEvent.Destroy();
   delete theFile;
   theFile = NULL;
};



Int32 ReadEventString(FILE* fl, char* str)
{
   XString xsString; 
   if(!fl)
      RET_ZERO;
   char ch;
   for(int i = 0; (ch=getc(fl))!=EOF &&
                  (ch!='#' && i!=0); i++)
   {
      if(ch=='\n')
         ch=' ';
      if(ch=='\r')
         ch=0;
      if(ch)
         xsString.Push(ch);
   };
   str = new char[xsString.GetCurCnt()+1];
   memset(str,0,(xsString.GetCurCnt()+1)*sizeof(char));
   strcpy(str,xsString.GetPtr());
   return xsString.GetCurCnt();
};

Int32 GetNextEvnFld(char *evn_str,char* str)
{
   char buf[256] = {0};
   int i = 0;
   while(*evn_str && *evn_str!='\t')
   {
      buf[i]=*evn_str;
      str++;
      i++;
   };
   strcpy(evn_str,buf);
   // ���������� '\t'
   if(*evn_str=='\t')
      evn_str++;
   return i;
}

Int32 ParseEventString(char* evn_str,Int32 iEvnSize)
{
   
   char *str = evn_str;
   Int32 iEvnSqNo = 0;
   char buf[256] = {0};
   int i = 0;
   // ��������� ������ ������� � ���������
   GetNextEvnFld(str,buf);
   iEvnSqNo = atoi(buf);
   memset(buf,0,255);
   
   // ��������� ������ ���� �������
   int iEvnNo = 0;
   GetNextEvnFld(str,buf);
   char *p = strstr(buf,"Evn=");
   if(!p)
      RET_ZERO;
   iEvnNo = atoi(p+4);
   XString xString;
   int k = 0;
   xsParamsShift.Destroy();
   while(*str)
   {
      if(*str!='\t')
         xString.Push(*str);
      else
      {
         Int32 shift = k+1;
         xsParamsShift.Push(&shift);
         char ch = 0;
         xString.Push(ch);
      }
      str++;
      k++;
   }
   iParamsStringLen = xString.GetCurCnt()+1;
   pParamsString = new char[iParamsStringLen];
   memset(pParamsString ,0 ,iParamsStringLen*sizeof(char));
   memcpy(pParamsString ,xString.GetPtr() ,xString.GetCurCnt());
   return iEvnNo;
};

STD_FUNC(Int32) stdPrtStartParsePrt(char *file_name)
{
   stdPrtFILE theParseFile(file_name,"rt");
   if((FILE*)(theParseFile)==NULL)
      RET_ZERO;
   xsParamsShift.Destroy();
   if(pParamsString)
   {
      delete pParamsString;
      pParamsString = NULL;
      iParamsStringLen = 0;   
   };
   return 1;
};

STD_FUNC(Int32) stdPrtGetNextEvent(StdPrtEvent* pspe)
{
   xsParamsShift.Destroy();
   if(pParamsString)
   {
      delete pParamsString;
      pParamsString = NULL;
      iParamsStringLen = 0;
   };
   RET_ZERO;
};


#ifdef __PRTTEST__

int myfunc()
{
SendMessage
static StdPrtEvent spe1= { "���� %s ��������� �� ����� %s" };

"{{%s}} {{%s}}"


static StdPrtEvent spe2= { "���� %s ��������� �� ����� %s", SPE_PUBLIC | SPE_WAIT };

   stdPrt(&spe1, "myfile.tif", "SZV1_1");

   StdPrtEvent spe3= { "������ ��� ������ �� ����� %s" };
   StdPrtEvent spe4= { "������ ��� ������� ������ ������� %d" };

   return 0;
}


---------------------


#185 Evn=1    EvnNo=101 ���� %s ��������� �� ����� %s 0 
#185 Evn=101  myfile1.tif SZV1_1
#185 Evn=101  myfile2.tif SZV1_1
#185 Evn=101  myfile3.tif SZV1_1
#185 Evn=101  myfile4.tif SZV1_1
#185 Evn=101  myfile5.tif SZV1_1
#185 Evn=101  myfile6.tif SZV1_1
....
#185 Evn=2 12.57
#186 Evn=101  myfile.tif  SZV1_1   


/*Bool32 SendTimerEvent()
{
   time_t new_time;
   time(&new_time);
   localtime( &new_time );
   struct tm *date;
   date = localtime( &new_time );
   if(!gl_szOldTime || ((new_time-gl_szOldTime) > TIMER_DELTA*60))
   {
      char buff[512] = {0};
      sprintf( buff, szStdPrtSysEventList[1].szFormat ,gl_iEventCount , asctime(date));
      fprintf(theFile,"%s\n",buff);
      SendEvnToConsole(buff);
      gl_szOldTime = new_time;
   };
   return TRUE;   
};*/

/*
Bool32 SendEvnToConsole(StdPrtEvent* pspe,va_list& List)
{
   if((HANDLE)(stdPrtConsole) == NULL)
      return FALSE;
   
   char buf[4097*2] = {0};
   char buff1[4097] = {0};
   char buff2[4097] = {0};
   Int32 nBytesWritten=sprintf( buff1,"#%05i\tEvn=%03i",gl_iEventCount,xsEventTypeData[(pspe->hEvent-1)].iEvnNo);
   nBytesWritten+=vsprintf( buff2, pspe->szFormat, List );
   nBytesWritten=sprintf(buf,"%s\t%s",buff1,buff2);
   unsigned long nRBytesWritten = 0;
   stdPrtConsole.SendTextToConsole(buf, strlen(buf));
   //WriteConsole((HANDLE)stdPrtConsole,buf,nBytesWritten,&nRBytesWritten,NULL);
   return TRUE;
};

Bool32 SendEvnToConsole(char *evn_str)
{
   if((HANDLE)(stdPrtConsole) == NULL)
      return FALSE;
   stdPrtConsole.SendTextToConsole(evn_str, strlen(evn_str));
   //unsigned long nBytesWritten = 0;
   //WriteConsole(stdPrtConsole,evn_str,strlen(evn_str),&nBytesWritten,NULL);
   return TRUE;
};
*/


/*
STD_FUNC(Int32) stdPrt( StdPrtEvent* pspe, ... )
{
   if (NULL==(FILE*)theFile)
      return 0;
   int nBytesWritten=0;
   
   if(pspe->hEvent)
   {
    
      va_list List;
      va_start(List, pspe);
      nBytesWritten=fprintf(theFile,"#%05i\tEvn=%03i",gl_iEventCount,xsEventTypeData[(pspe->hEvent-1)].iEvnNo);
      nBytesWritten=vfprintf( theFile, xsEventTypeData[(pspe->hEvent-1)].FrmtEvnString, List );
      fprintf(theFile,"\n");
      fflush(theFile);
      SendEvnToConsole(pspe,List);
      //nBytesWritten = SendEvn(xsEventTypeData[pspe->hEvent],List);
      //nBytesWritten=fprintf( theFile, pspe->szFormat, List );
      va_end( List );
   }
   else
   {
      va_list List;
      va_start(List, pspe);
          
      StdPrtEventData szEvnData = {0};
      Int32 res = EvnParseFormat(pspe->szFormat,szEvnData.FrmtEvnString);
      if(!res)
         RET_FALSE;
      szEvnData.iEvnNo = ++gl_iLastEventNo;
      nBytesWritten=fprintf( theFile, "#%05i\tEvn=001\tEvnNo=%03i\tEvnPar=%i\t%s\n" ,gl_iEventCount ,szEvnData.iEvnNo ,res , pspe->szFormat);
      char buffer[4097] = {0};
      sprintf(buffer,"#%05i\tEvn=001\tEvnNo=%03i\tEvnPar=%i\t%s" ,gl_iEventCount ,szEvnData.iEvnNo ,res , pspe->szFormat);
      //char buffer2[4097] = {0};
      //OemToChar(buffer,buffer2);
      SendEvnToConsole(buffer);
      gl_iEventCount++;
      xsEventTypeData.Push(&szEvnData,&(pspe->hEvent));
      //pspe->hEvent++;
      //pspe->hEvent = szEvnData.iEvn No-100;

      nBytesWritten = fprintf(theFile,"#%05i\tEvn=%03i",gl_iEventCount,szEvnData.iEvnNo);
      nBytesWritten=vfprintf( theFile, szEvnData.FrmtEvnString, List );
      fprintf(theFile,"\n\r");
      fflush(theFile);
      SendEvnToConsole(pspe,List);
            
      va_end( List );
   }

   return nBytesWritten ? ++gl_iEventCount : 0;
};

*/
#endif