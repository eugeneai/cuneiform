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


/****************************************************************************
 *                                                                          *
 *              Cell dump                                                   *
 *                                                                          *
 *              Written in 1992 by Yuri Panchul                             *
 *                                                                          *
 ***************************************************************************/
#include <stdio.h>
#include "nt_types.h"
#include "struct.h"
#include "func.h"
#include "status.h"
#include "msgerr.h"

# define CELLDUMP_SNAP_PASS 'h'

cell *dump_list = NULL;

void setup_dump (void)
{
    dump_list = NULL;
}

void cell_to_dump (cell *c)
{
    /* Convert to '~' */

//    c -> flg &= ~ c_f_bad;
//  c -> flg |=   c_f_let;

    c -> nvers         = 1;
    c -> vers [0].let  = '~';
    c -> vers [0].prob = 254;
    c -> vers [1].let  = 0;

    c -> prev -> next = c -> next;
    c -> next -> prev = c -> prev;

    if (c -> flg & (c_f_let | c_f_bad))
    {
        c -> prevl -> nextl = c -> nextl;
        c -> nextl -> prevl = c -> prevl;
        err_pnlet (c);  // AL 940319
    }

    c->flg = c_f_let;

    if (dump_list != NULL)
        dump_list -> prev = c;

    c -> next  = dump_list;
    c -> prev  = NULL;

    dump_list = c;
}

void dump_to_string (void)
{
    cell *temp;

    if (db_status)
        snap_newpass (CELLDUMP_SNAP_PASS);

    while (dump_list != NULL)
    {
        temp = dump_list -> next;
	insert_cell (dump_list, cell_f ());
	dump_list->left=dump_list->col;
	dump_list->right=dump_list->col+dump_list->w;

        if (db_status && snap_activity (CELLDUMP_SNAP_PASS))
        {
            snap_show_text ("Get from dump");
            snap_newcell (dump_list);
            snap_monitor ();
        }

        dump_list = temp;
    }
}
