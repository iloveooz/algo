/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.2. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : blockbuffer.h                                    *
*  �������� : ���������� ������� ������������� � ����������    *
*             ������� ����������� �������                      *
***************************************************************/

#ifndef __BLOCK_BUFFER_H
#define __BLOCK_BUFFER_H

#include <exception>
#include <alloc.h>

using namespace std;

class NoMoreMemoryException : public exception {
  char * reason;
public :
  NoMoreMemoryException(char * message = "No nore free memory") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// ����� BlockBuffer ������������ �������� ��� ������ � �������
// ���������� �� ��� ���������� � ��� ������ ����������� �������
//==============================================================
template <int blockSize>
class BlockBuffer {
  char * buffer;        // ��������� �� �����
  int size;             // ������ ������ � ������
  // ��������� ��������� ������:
  void * freePtr;       // � ������ ��������� ������
  int freeArea;         // � ������� ���������������� ������

public :

  // �����������:
  BlockBuffer(int n) {
    buffer = new char[(size = n) * blockSize];
    if (buffer == NULL) {
      throw NoMoreMemoryException();
    }
    clear();
  }

  // ����������:
  ~BlockBuffer() { delete[] buffer; }

  // ������� ������.
  void clear() {
    freePtr = NULL;
    freeArea = 0;
  }

  // �������� ��������� �������� ��������� ����� ������
  void * get() {
    if (freePtr) {
      void * ret = freePtr;
      freePtr = *(void **)freePtr;
    } else if (freeArea < size) {
      void * ptr = buffer + freeArea*blockSize;
      freeArea++;
      return ptr;
    } else {
      throw NoMoreMemoryException();
    }
  }

  void release(void * ptr) {
    *(void **)ptr = freePtr;
    freePtr = ptr;
  }
};

#endif
