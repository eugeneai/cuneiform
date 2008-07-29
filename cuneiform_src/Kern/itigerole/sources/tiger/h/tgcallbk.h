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

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                                                                          //
//                   T I G E R   O C R   L I B R A R Y                      //
//                                                                          //
//                                                                          //
//           File       :  TGCALLBK.H                                       //
//           Contains   :  External TIGER OCR library definitions           //
//           Written by :  Alexander Talalai, Yuri Panchul                  //
//           Compiler   :  Microsoft C v6.0, WATCOM C/386 v8.5              //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
# ifndef TGCALLBK_H_INCLUDED
# define TGCALLBK_H_INCLUDED
//////////////////////////////////////////////////////////////////////////////
# ifdef __cplusplus
 extern "C"
{
# endif
//////////////////////////////////////////////////////////////////////////////
#pragma pack(push,1)
//////////////////////////////////////////////////////////////////////////////
# ifndef TGCALL_H_INCLUDED
typedef short int INT16;
#include "dlltypes.h"
# endif
//////////////////////////////////////////////////////////////////////////////
//                   Callback functions from TIGER.DLL                      //
//////////////////////////////////////////////////////////////////////////////
//   Obtain image functions set                                             //
//////////////////////////////////////////////////////////////////////////////
struct Tiger_ImageInfo
{
    WORD  wImageHeight;           // Height of the image in lines
    WORD  wImageWidth;            // Width of the image in pixels
    WORD  wImageByteWidth;        // Size of the image line in bytes
    WORD  wImageDisplacement;     // Displacement of the first pixel of
                                  //   image line in pixels, usually 0
    WORD  wResolutionX;           // Resolution by X-axe
    WORD  wResolutionY;           // Resolution by Y-axe
    BYTE  bFotoMetrics;           // White pixel
    BYTE  bUnused;                // not used; for alignment purpose only

    WORD  wAddX;
    WORD  wAddY;
};
//////////////////////////////////////////////////////////////////////////////
typedef struct Tiger_ImageInfo	TIGER_IMAGEINFO;
typedef TIGER_IMAGEINFO TIGERFAR *   LPTIGER_IMAGEINFO;
//////////////////////////////////////////////////////////////////////////////
FNBOOL16               Tiger_Callback_ImageOpen (LPTIGER_IMAGEINFO lpImageInfo);
//////////////////////////////////////////////////////////////////////////////
FNBOOL16            Tiger_Callback_ImageOpen_xy (LPTIGER_IMAGEINFO lpImageInfo,
												 WORD x,
												 WORD y,
												 WORD w,
												 WORD h);
//////////////////////////////////////////////////////////////////////////////
FNDWORD          Tiger_Callback_ProcessPictures (LPSTR buf,
												 DWORD lth);
//////////////////////////////////////////////////////////////////////////////
FNWORD                 Tiger_Callback_ImageRead (LPSTR lpImage,
												 WORD wMaxSize);
//////////////////////////////////////////////////////////////////////////////
FNBOOL16              Tiger_Callback_ImageClose (void);
//////////////////////////////////////////////////////////////////////////////
//   Warrning !!!                                                           //
//   Tiger_Callback_ImageClose could be invoked even                        //
//   if Tiger_Callback_ImageOpen returned                                   //
//   bad status or was not opened at all                                    //
//////////////////////////////////////////////////////////////////////////////
//   Intermediate error message                                             //
//////////////////////////////////////////////////////////////////////////////
FNVOID               Tiger_Callback_ReportError (WORD wStatus,
												 LPSTR lpMessage);
//////////////////////////////////////////////////////////////////////////////
//   Progress Monitor                                                       //
//                                                                          //
//   Each of progress monitor functions return TRUE if TIGER have to        //
//   continue work and FALSE to cancel process                              //
//////////////////////////////////////////////////////////////////////////////
FNBOOL16           Tiger_Callback_ProgressStart (void);
//////////////////////////////////////////////////////////////////////////////
FNBOOL16          Tiger_Callback_ProgressFinish (void);
//////////////////////////////////////////////////////////////////////////////
FNBOOL16         Tiger_Callback_ProgressSetPerc (WORD wPercent);
//////////////////////////////////////////////////////////////////////////////
FNBOOL16        Tiger_Callback_ProgressSetStage (WORD wStageNumber,
												 LPSTR lpStageName,
												 WORD wVolume);
//////////////////////////////////////////////////////////////////////////////
FNBOOL              Tiger_Callback_Get_One_Word (LPSTR Buffer );
//////////////////////////////////////////////////////////////////////////////
FNBOOL16                  Swp_ImageOpen         (LPTIGER_IMAGEINFO lpImageInfo);
//////////////////////////////////////////////////////////////////////////////
FNWORD                    Swp_ImageRead         (LPSTR lpImage,
												 WORD wMaxSize);
//////////////////////////////////////////////////////////////////////////////
FNBOOL16                  Swp_ImageClose        (void);
//////////////////////////////////////////////////////////////////////////////
#ifndef __MSVC__
FNBOOL16                  Tiger_FindLinesInTiff (LPSTR name,
												 WORD x,
												 WORD y,
												 BOOL16 TIGERFUN(*)(LPTIGER_IMAGEINFO),
												 WORD   TIGERFUN(*)(LPSTR *,WORD ),
												 BOOL16 TIGERFUN(*)());
//////////////////////////////////////////////////////////////////////////////
FNVOID                    Tiger_FindLinesClose  (void);
//////////////////////////////////////////////////////////////////////////////
#else
FNBOOL16                  Tiger_FindLinesInTiff (LPSTR name,
												 WORD x,
												 WORD y,
												 BOOL16 (TIGERFUN(*))(LPTIGER_IMAGEINFO),
												 WORD   (TIGERFUN(*))(LPSTR *,WORD ),
												 BOOL16 (TIGERFUN(*))());
//////////////////////////////////////////////////////////////////////////////
FNVOID                    Tiger_FindLinesClose  (void);
#endif
//////////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
//////////////////////////////////////////////////////////////////////////////
# ifdef __cplusplus
}
# endif
//////////////////////////////////////////////////////////////////////////////
# endif
//////////////////////////////////////////////////////////////////////////////
// end of file
