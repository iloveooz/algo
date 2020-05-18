/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bintwins.cpp                                     *
*  �������� : ���������� ������� ������������� � ����������    *
*             ������� ������ ������� �������� ���������        *
***************************************************************/

#include <iostream>

using namespace std;

#include "bintwins.h"

// ���������� �������� � ������:
int BinTwinsMemory::claims = 0;
size_t BinTwinsMemory::reserved = 0;
size_t BinTwinsMemory::demanded = 0;

// �������� ��������� ���������� ����� ������ ��������� �������
void * BinTwinsMemory::get(size_t sz) {
  sz += sizeof(char);   // ���� ���� ������������� �������������
  // ���������� ����������� �����, ������� ���������� ���������������
  char p = 2;
  while (sz != (1 << p) && (~((1u << p)-1) & sz) != 0) p++;
  // ��������� � ����������� �������, �������� �������� ���������� �����
  size_t request = getRec(p);
  if (request == null) throw NoMoreMemoryException();
  // �������������� ��������
  claims++;
  demanded += sz - sizeof(char);
  reserved += 1 << p;
  // � ������ ����� �������� ��� ����������� � ������ �����
  char * block = buffer + request;
  *block = p;
  return block + sizeof(char);
}

// ����������� ������� ��������� ���������� ����� ������
size_t BinTwinsMemory::getRec(char p) {
  // 1. ��������: ���� ������������� ���� ������� �������� �������,
  //    ������, ��������� ������ ������ ���
  if (p > power) return null;
  // 2. ��������� ������ ��������� ������ ������� �������
  if (freeLists[p] == null) {
    // ������ ����; ����������� ����� ������� ����.
    size_t doubleBlock = getRec(p + 1);
    // ���� ������ ���������� ��������, �� ���������� ������ ���������.
    if (doubleBlock == null) return null;
    // ���� ����� �������� ������� ������� �������;
    // ����� �����-�������� ������������ � ��������������� ������
    size_t twinBlock = doubleBlock + (1 << p);
    *(size_t *)(buffer + twinBlock) = null;
    freeLists[p] = twinBlock;
    return doubleBlock;
  } else {
    // ��������� ���� ������� ������� ������; �� �����������
    // �� ������ � ��� ����� �������� � �������� ����������
    size_t result = freeLists[p];
    freeLists[p] = *(size_t *)(buffer + freeLists[p]);
    return result;
  }
}

// �������� �������� ����������� ����� ������ � �������
void BinTwinsMemory::release(void * ptr) {
  // ��������� ����� ����� � ��� ����������� p
  char * block = (char*)ptr - sizeof(char);
  char p = *block;
  // ���������� � ����������� ������� �������� ����� � �������
  releaseRec(block - buffer, p);
}

// ����������� ������� �������� ����������� ����� ������ � �������
void BinTwinsMemory::releaseRec(size_t block, char p) {
  // ��������� ����� ��������
  size_t twinBlock = (1 << p) ^ block;
  // ���������� ����� �����-�������� � ������ ��������� ������
  size_t* ptr = &freeLists[p];
  while (*ptr != null && *ptr != twinBlock) {
    ptr = (size_t*)(buffer + *ptr);
  }

  if (*ptr == null) {
    // ����� �������� �� ������ � ���� �������������� � ������
    *(size_t*)(buffer + block) = freeLists[p];
    freeLists[p] = block;
  } else {
    // ����-������� ����������� �� ������ ��������� ������
    *ptr = *(size_t*)(buffer + *ptr);
    // ����������� ����� ��� ������������ ����� ���������� �������
    releaseRec(block & ~(1u << p), p+1);
  }
}
