/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bintwins.h                                       *
*  �������� : �������� ������� ������������� � ����������      *
*             ������� ������ ������� �������� ���������        *
***************************************************************/

#ifndef __BIN_TWINS_H
#define __BIN_TWINS_H

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
// ����� BinTwinsMemory ������������ �������� ��� ������ � �������
// ���������� �� ��� ���������� � ��� ������ ����������� �������.
// ��������� ����� �������� ������� "�������� ���������"
//==============================================================
class BinTwinsMemory {
  static const size_t null = 0xFFFF;

  char * buffer;        // ��������� �� �����
  int power;            // �������� ���������� ������� ������
  // ������ ������� ��������� ������ ������ �������:
  size_t * freeLists;

  // ���������� �������� � ������:
  static int claims;
  static size_t reserved;
  static size_t demanded;

public :

  // �����������:
  BinTwinsMemory(int n) {
    freeLists = new size_t[(power = n) + 1];
    buffer = new char[1 << power];
    clear();
  }

  // ����������:
  ~BinTwinsMemory() {
    delete[] buffer;
    delete[] freeLists;
  }

  // ������� ������.
  void clear() {
    for (int i = 0; i < power; i++) freeLists[i] = null;
    freeLists[power] = 0;
    *(size_t *)buffer = null;
  }

  // �������� ��������� ���������� ����� ������ ��������� �������
  void * get(size_t sz);

  // �������� �������� ����������� ����� ������ � �������
  void release(void * ptr, size_t sz);

  // ������ � ����������
  static int getClaims() { return claims; }
  static size_t getReserved() { return reserved; }
  static size_t getDemanded() { return demanded; }

private :

  size_t getRec(char p);
  void BinTwinsMemory::releaseRec(size_t block, char p);
};

#endif
