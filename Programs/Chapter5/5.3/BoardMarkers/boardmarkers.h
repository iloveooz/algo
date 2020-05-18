/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : boardmarkers.h                                   *
*  �������� : �������� ������� ������������� � ����������      *
*             ������� ������ ������� ��������� ��������        *
***************************************************************/

#ifndef __BOARD_MARKERS_H
#define __BOARD_MARKERS_H

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
class BoardMarkersMemory {
  // ���� ��������� ��������
  static const unsigned char FREE_MARKER = 0xCC;
  static const unsigned char BUSY_MARKER = 0x33;

  // ������� � ������ ��������� ����������� ����������
  static const int MARKER_SIZE = sizeof(unsigned char);
  static const int PTR_SIZE = sizeof(char*);
  static const int SIZE_SIZE = sizeof(size_t);

  char * buffer;        // ��������� �� �����
  size_t size;          // ������ ������ � ������
  // ��������� ������ ��������� ������:
  char * freePtr;

public :

  // �����������:
  BoardMarkersMemory(size_t n) {
    buffer = new char[size = n];
    clear();
  }

  // ����������:
  ~BoardMarkersMemory() { delete[] buffer; }

  // ������� ������.
  void clear() {
    // � ������ ��������� ��������� ������ �� �������������
    // �����, ������ �������� ����� ������� ����� ������
    freePtr = buffer;

    *freePtr = FREE_MARKER;
    *(size_t*)&freePtr[MARKER_SIZE] = size;
    *(char**)&freePtr[MARKER_SIZE + SIZE_SIZE] = freePtr;
    *(char**)&freePtr[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = freePtr;

    *(unsigned char *)&freePtr[size - MARKER_SIZE] = FREE_MARKER;
    *(size_t*)&freePtr[size - MARKER_SIZE - SIZE_SIZE] = size;
  }

  // �������� ��������� ���������� ����� ������ ��������� �������
  void * get(size_t sz);

  // �������� �������� ����������� ����� ������ � �������
  void release(void * ptr);
};

#endif
