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

//////////////////////////////////////////////////
// Set of useful C++ routines at level of ANSI C++

#ifndef ___ANSIPP_H
#define ___ANSIPP_H

//////////////////////////////////////////////////
// class TNew<T> - automatizes C++ new-delete pair
//
template < class T >
class TNew
{
   T* t_ptr;
   public:
      TNew(){  t_ptr = new T;
               if (t_ptr)
                  memset( t_ptr, 0, sizeof(T) );
            };
      virtual ~TNew()
      {  if (t_ptr)
            delete t_ptr;
         t_ptr = NULL;
      };
      operator T* () const { return t_ptr; };
      operator T& () const { return *t_ptr; };
      T* GetPtr() const    { return t_ptr; };

};
   /////////////////////////////////////////////////////
   // example of TNew usage
   // void MyFunc()
   // {
   //    TNew<MyStruct> mstr; // makes instance of MyStruct on the heap
   //    if (mstr.GetPtr()==NULL) ...// new() failed
   //    mstr->..
   //    ............
   //    // on exit mstr automatically deleted
   // }

template < class FuncType >
class CallWhenDestruct
{
   FuncType func;
   public:
      CallWhenDestruct( FuncType _func ): func(_func) {};
      ~CallWhenDestruct(){ func(); };
};

template < class FuncType, class ArgType >
class CallWhenDestruct1
{
   FuncType func;
   ArgType  arg;
   public:
      CallWhenDestruct1( FuncType _func, ArgType _arg ): func(_func),arg(_arg){};
      ~CallWhenDestruct1(){ func(arg); };
};

template < class FuncType, class ArgType1, class ArgType2 >
class CallWhenDestruct2
{
   FuncType func;
   ArgType1 arg1;
   ArgType2 arg2;
   public:
      CallWhenDestruct2( FuncType _func, ArgType1 _arg1 ):
         func(_func),arg1(_arg1),arg2(_arg2){};
      ~CallWhenDestruct2(){ func(arg1,arg2); };
};

#endif   // __ANSIPP_H
