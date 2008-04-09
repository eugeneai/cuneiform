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


//	TIGER run options
#define RUN_SPELLER          1
#define FORCE_ONE_COLUMN     2
#define NO_FORMATING	     4
#define FAX100               8
#define DOTMATRIX           16
#define BCRFLAG             32
#define BCRLOUT             64
#define CUTLEFT            128
#define CUTRIGHT           256
#define SPACE_CORRECTION   512

//	Kernel functions
BOOL kernel_init(void);
BOOL bcr_init(void);
void kernel_run_options (WORD options);
BOOL recognize (PBYTE ed_file_name);
BOOL page_analysis (void);
BOOL final_recognition (PBYTE ed_file_name);
BOOL spelling_checker (PBYTE ed_file_name);
BOOL kernel_reset (void);
BOOL kernel_reload_vocs ( void);
BOOL kernel_set_temp_dir ( BYTE *tmp_dir);
BOOL kernel_set_windows_dir ( BYTE *tmp_dir);
BOOL kernel_valid_version ( INT , INT );
BOOL kernel_set_enable_table_recog(BYTE table_recog);
BOOL kernel_set_user_dict(BYTE *user_dict);

//  Error status functions
PCHAR get_message (WORD code);
WORD get_error_status (void);
BOOL bool_status (void);
void set_error_status (WORD group, WORD element);
void clear_error_status (void);

//	Convetrt to text
BOOL convert_to_text
  (PBYTE edfile, PBYTE textfile, WORD options, WORD codepage, BYTE badchar);
#define SAVE_TEXT_ED            0x01
#define SAVE_TEXT_ASCII         0x02
#define SAVE_TEXT_SMART_ASCII   0x04
#define SAVE_TEXT_RTF           0x08
#define SAVE_TEXT_ANSI          0x10 // Pit 8.26.94
#define SAVE_TEXT_SMART_ANSI    0x20 // Pit

#define SAVE_TEXT_APPEND            128  //  0x'80'
#define SAVE_TEXT_ASCII_APP         (SAVE_TEXT_ASCII + SAVE_TEXT_APPEND)
#define SAVE_TEXT_SMART_ASCII_APP   (SAVE_TEXT_SMART_ASCII + SAVE_TEXT_APPEND)
#define SAVE_TEXT_RTF_APP           (SAVE_TEXT_RTF + SAVE_TEXT_APPEND)

#define SAVE_TABLE_TXT		0x0100
#define SAVE_TABLE_CSV		0x0200
#define SAVE_TABLE_DBF		0x0400
#define SAVE_TABLE_ODBC 	0x0800
#define SAVE_TABLE_WKS		0x1000
#define SAVE_HTML               0x2000

// wCodePage options... Piter
#define SAVE_TEXT               SAVE_TEXT_ASCII
#define SAVE_TEXT_SMART         SAVE_TEXT_SMART_ASCII

# define TIGER_CODE_UNKNOWN     0x0000
# define TIGER_CODE_ASCII       0x0001
# define TIGER_CODE_ANSI        0x0002
# define TIGER_CODE_KOI8        0x0004
# define TIGER_CODE_ISO         0x0008

void write_text (BYTE);


//-------------------- Callback functions -------------------------

//	Image read functions

struct AttrImage
 {
  WORD PixelHeight;
  WORD PixelWidth;
  WORD ByteWidth;
  WORD LeftDisplacement;
  WORD Resolution_X;
  WORD Resolution_Y;
  BYTE FotoMetrics;
  BYTE bUnused;
  WORD AddX;
  WORD AddY;
 };

BOOL  Tiger_ImageOpen    (struct AttrImage * p);
BOOL  Tiger_ImageOpen_xy (struct AttrImage * p,WORD x,WORD y,WORD w,WORD h);
BOOL  Tiger_ImageClose 		(void);
INT   Tiger_ImageRead 		(PBYTE buffer, WORD lth);
DWORD Tiger_ProcessPictures 	(PBYTE buffer,DWORD lth);

//	Immediate error report
void Tiger_ReportError (WORD status, PBYTE message);

// Progress Monitor
BOOL Tiger_ProgressStart (void);
BOOL Tiger_ProgressFinish (void);
BOOL Tiger_ProgressSetPercentage (WORD wPercent);
BOOL Tiger_ProgressSetStage (WORD wStageNumber, PBYTE pStageName, WORD wVolume);
