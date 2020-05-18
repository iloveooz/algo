/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : boardmarkers.cpp                                 *
*  �������� : ���������� ������� ������������� � ����������    *
*             ������� ������ ������� ��������� ��������        *
***************************************************************/

#include <iostream>

using namespace std;

#include "boardmarkers.h"

void * BoardMarkersMemory::get(size_t sz) {
  // 1. ����� ���������� ����� ���������� �����
  if (freePtr == NULL) throw NoMoreMemoryException();
  char * current = freePtr,
       * last = freePtr,
       * found = NULL;
  do {
    if (*(size_t*)&current[MARKER_SIZE] >= sz + SIZE_SIZE + 2*MARKER_SIZE) {
      found = current;    // ��������� ���� ���������� ����� ������
    } else {
      // ������� � ���������� �����
      current = *(char**)&current[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
    }
  } while (found == NULL && current != last);
  if (found == NULL) { // ��� ���������� ����� ������ ������� �������!
    throw NoMoreMemoryException();
  }

  // 2. �������� �����
  size_t * pLength = (size_t*)&found[MARKER_SIZE];
  char **  pPred   = (char**)&found[MARKER_SIZE + SIZE_SIZE];
  char **  pNext   = (char**)&found[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
  unsigned char * pEndMarker = (unsigned char *)&found[*pLength - MARKER_SIZE];

  // 3. ���� ���� �� ������� �����, �� ���������� �������
  if (*pLength < sz + 3*SIZE_SIZE + 4*MARKER_SIZE + 2*PTR_SIZE) {
    if (*pNext == found) {  // ��� ��� ��������� ��������� ����
      freePtr = NULL;
    } else {                // ��������� ���� �� ������
      *(char**)(*pPred + MARKER_SIZE + SIZE_SIZE+PTR_SIZE) = freePtr = *pNext;
      *(char**)(*pNext + MARKER_SIZE + SIZE_SIZE) = *pPred;
    }
    // ��������� ���� ��� �������
    *found = *pEndMarker = BUSY_MARKER;
    return found + MARKER_SIZE + SIZE_SIZE;

  // 4. ���� ���� ���������� �����, �� �� ������� �� ���
  } else {
    // ���������� ����� ����� ���������� �����:
    *pLength -= sz + SIZE_SIZE + 2*MARKER_SIZE;
    // �������������� ��������
    char * busyBlock = found + *pLength;
    size_t* busyLength = (size_t*)(busyBlock + MARKER_SIZE);
    unsigned char * pFreeEndMarker = (unsigned char *)(busyBlock - MARKER_SIZE);
    size_t * pEndLength = (size_t*)((char*)pFreeEndMarker - PTR_SIZE);
    // ������������ ������� ������� ������ �����:
    *pEndLength = *pLength;
    *pFreeEndMarker = FREE_MARKER;
    // ��������� ��������� ������ ��������� ������
    freePtr = found;
    // ������������� ������������ ����������� ����� � ������ ����������:
    *busyBlock = *pEndMarker = BUSY_MARKER;
    *busyLength = sz + SIZE_SIZE + 2*MARKER_SIZE;
    return busyBlock + MARKER_SIZE + SIZE_SIZE;
  }
}

void BoardMarkersMemory::release(void * ptr) {
  // ������� ��������� ����� ������������� �����
  char * releaseBlock = (char*)ptr - SIZE_SIZE - MARKER_SIZE;
  // 1. ��������� �������� ����� � ��������� �� ������, ���� ���
  //    ��������� �����. ���������� ���������� ����� ����������
  //    ������ �������.
  char * firstAddr = releaseBlock > buffer && ((unsigned char *)releaseBlock)[-MARKER_SIZE] == FREE_MARKER ?
                     releaseBlock - *(size_t*)&releaseBlock[-MARKER_SIZE - SIZE_SIZE] :
                     NULL,
       * secondAddr = releaseBlock + *(size_t*)&releaseBlock[MARKER_SIZE];
  if (secondAddr == buffer+size || *(unsigned char *)secondAddr != FREE_MARKER) secondAddr = NULL;

  // 2. ������������� ��� ������:
  //    1) ������������ ���� ������� ��������� � ������ ��������� �������;
  //    2) ������������ ���� ������� ��������� � ����� �� �������� ������;
  //    3) �� ���� �� ���������� ����������.
  if (firstAddr != NULL) {
    // ������ �� ������ ��������� � �������������
    if (secondAddr != NULL) {
      // ������ ���� ���� ��������� � ������������� - ������ (1).
      // ������ ���� ������� �� �������, � ������ ���������:
      size_t newLen = (*(size_t*)&firstAddr[MARKER_SIZE] += *(size_t*)&releaseBlock[MARKER_SIZE] + *(size_t*)&secondAddr[MARKER_SIZE]);
      *(size_t*)&firstAddr[MARKER_SIZE] = newLen;
      *(size_t*)&firstAddr[newLen - MARKER_SIZE - SIZE_SIZE] = newLen;
      char * predBlock = *(char**)&secondAddr[MARKER_SIZE + SIZE_SIZE];
      char * nextBlock = *(char**)&secondAddr[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
      *(char**)&predBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = nextBlock;
      *(char**)&nextBlock[MARKER_SIZE + SIZE_SIZE] = predBlock;
    } else {
      // ������ (2), ������ ���� �����������
      size_t newLen = *(size_t*)&firstAddr[MARKER_SIZE] + *(size_t*)&releaseBlock[MARKER_SIZE];
      *(size_t*)&firstAddr[MARKER_SIZE] = newLen;
      firstAddr[newLen - MARKER_SIZE] = FREE_MARKER;
      *(size_t*)&firstAddr[newLen - MARKER_SIZE - SIZE_SIZE] = newLen;
    }
  } else if (secondAddr != NULL) {
    // ������ ���� - ������������ �� ����������� � ������������� - ������ (2)
    *releaseBlock = FREE_MARKER;
    size_t newLen = *(size_t*)&releaseBlock[MARKER_SIZE] + *(size_t*)&secondAddr[MARKER_SIZE];
    *(size_t*)&releaseBlock[MARKER_SIZE] = newLen;
    *(size_t*)&releaseBlock[newLen - MARKER_SIZE - SIZE_SIZE] = newLen;
    char * predBlock = *(char**)&secondAddr[MARKER_SIZE + SIZE_SIZE];
    char * nextBlock = *(char**)&secondAddr[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
    *(char**)&predBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = releaseBlock;
    *(char**)&nextBlock[MARKER_SIZE + SIZE_SIZE] = releaseBlock;
    *(char**)&releaseBlock[MARKER_SIZE + SIZE_SIZE] = predBlock;
    *(char**)&releaseBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = nextBlock;
  } else {
    // ������ (3) - � ������� ���������� ����� ��������� ����.
    *releaseBlock = FREE_MARKER;
    size_t len = *(size_t*)&releaseBlock[MARKER_SIZE];
    releaseBlock[len - MARKER_SIZE] = FREE_MARKER;
    *(size_t*)&releaseBlock[len - MARKER_SIZE - SIZE_SIZE] = len;
    if (freePtr == NULL) {
      *(char**)&releaseBlock[MARKER_SIZE + SIZE_SIZE] = releaseBlock;
      *(char**)&releaseBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = releaseBlock;
      freePtr = releaseBlock;
    } else {
      char * predBlock = *(char**)&freePtr[MARKER_SIZE + SIZE_SIZE];
      *(char**)&releaseBlock[MARKER_SIZE + SIZE_SIZE] = predBlock;
      *(char**)&releaseBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = freePtr;
      *(char**)&freePtr[MARKER_SIZE + SIZE_SIZE] = releaseBlock;
      *(char**)&predBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = releaseBlock;
    }
  }
}
