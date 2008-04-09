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

#ifndef __WMB_H
#define __WMB_H

/*
 * windows.h compatible Dialog Box Command IDs
 */
#define wIDOK            1
#define wIDCANCEL        2
#define wIDABORT         3
#define wIDRETRY         4
#define wIDIGNORE        5
#define wIDYES           6
#define wIDNO            7
#if(WINVER >= 0x0400)
#define wIDCLOSE         8
#define wIDHELP          9
#endif /* WINVER >= 0x0400 */
/*
 * windows.h compatible MessageBox() Flags
 */
#define wMB_OK                       0x00000000L
#define wMB_OKCANCEL                 0x00000001L
#define wMB_ABORTRETRYIGNORE         0x00000002L
#define wMB_YESNOCANCEL              0x00000003L
#define wMB_YESNO                    0x00000004L
#define wMB_RETRYCANCEL              0x00000005L

#define wMB_ICONHAND                 0x00000010L
#define wMB_ICONQUESTION             0x00000020L
#define wMB_ICONEXCLAMATION          0x00000030L
#define wMB_ICONASTERISK             0x00000040L

#if(WINVER >= 0x0400)
#define wMB_ICONWARNING              wMB_ICONEXCLAMATION
#define wMB_ICONERROR                wMB_ICONHAND
#endif /* WINVER >= 0x0400 */

#define wMB_ICONINFORMATION          wMB_ICONASTERISK
#define wMB_ICONSTOP                 wMB_ICONHAND

#define wMB_DEFBUTTON1               0x00000000L
#define wMB_DEFBUTTON2               0x00000100L
#define wMB_DEFBUTTON3               0x00000200L
#if(WINVER >= 0x0400)
#define wMB_DEFBUTTON4               0x00000300L
#endif /* WINVER >= 0x0400 */

#define wMB_APPLMODAL                0x00000000L
#define wMB_SYSTEMMODAL              0x00001000L
#define wMB_TASKMODAL                0x00002000L
#if(WINVER >= 0x0400)
#define wMB_HELP                     0x00004000L // Help Button
#define wMB_RIGHT                    0x00080000L
#define wMB_RTLREADING               0x00100000L
#endif /* WINVER >= 0x0400 */

#define wMB_NOFOCUS                  0x00008000L
#define wMB_SETFOREGROUND            0x00010000L
#define wMB_DEFAULT_DESKTOP_ONLY     0x00020000L
#define wMB_SERVICE_NOTIFICATION     0x00040000L

#define wMB_TYPEMASK                 0x0000000FL
#if(WINVER >= 0x0400)
#define wMB_USERICON                 0x00000080L
#endif /* WINVER >= 0x0400 */
#define wMB_ICONMASK                 0x000000F0L
#define wMB_DEFMASK                  0x00000F00L
#define wMB_MODEMASK                 0x00003000L
#define wMB_MISCMASK                 0x0000C000L

#endif


