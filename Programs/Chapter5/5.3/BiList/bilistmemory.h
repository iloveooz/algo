/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bilistmemory.h                                   *
*  �������� : �������� ������� ������������� � ����������      *
*             ������� ������ ����������� �������               *
***************************************************************/

#ifndef __BILIST_MEMORY_H
#define __BILIST_MEMORY_H

#include <exception>
#include <mem.h>

using namespace std;

class NoMoreMemoryException : public exception {
  char * reason;
public :
  NoMoreMemoryException(char * message = "No nore free memory") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ����� BiListMemory ������������ �������� ��� ������ � �������
// ���������� �� ��� ���������� � ��� ������ ����������� �������.
// ��������� ����� ������� � ��������������� ������������� ������
//==============================================================
class BiListMemory {
  // ��������� ���������� ����� ������:
  struct FreeBlock { 
    size_t length;
    FreeBlock * next, * pred;
  };

  // ��������� ����������� ����� ������:
  struct BusyBlock { 
    size_t length;
  };

  char * buffer;        // ��������� �� �����
  size_t size;             // ������ ������ � ������
  // ��������� ������ ��������� ������:
  FreeBlock * freePtr;

public :

  // �����������:
  BiListMemory(size_t n) {
    buffer = new char[size = n];
    clear();
  }

  // ����������:
  ~BiListMemory() { delete[] buffer; }

  // ������� ������.
  void clear() {
    // � ������ ��������� ��������� ������ �� �������������
    // �����, ������ �������� ����� ������� ����� ������
    freePtr = (FreeBlock *)buffer;
    freePtr->length = size;
    freePtr->next = freePtr->pred = freePtr;
  }

  // �������� ��������� ���������� ����� ������ ��������� �������
  void * get(size_t sz);

  // �������� �������� ����������� ����� ������ � �������
  void release(void * ptr);
};

#endif
