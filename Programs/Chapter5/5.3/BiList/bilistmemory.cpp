/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 5. ��������� ������������� ������                 *
*          5.3. ������������� ������ ������� ���������� �����  *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : bilistmemory.cpp                                 *
*  �������� : ���������� ������� ������������� � ����������    *
*             ������� ������ ����������� �������, ��������-    *
*             ������� � ��������� ��������������� ������       *
***************************************************************/

#include "bilistmemory.h"
#include <iostream>

using namespace std;

// �������� ��������� ���������� ����� ������ ��������� �������
void * BiListMemory::get(size_t sz) {
  // 1. ����� ���������� ����� ���������� �����
  if (freePtr == NULL) throw NoMoreMemoryException();
  FreeBlock * current = freePtr,
            * last = freePtr,
            * found = NULL;
  do {
    if (current->length >= sz + sizeof(BusyBlock)) {
      found = current;    // ��������� ���� ���������� ����� ������
    } else {
      current = current->next; // ������� � ���������� �����
    }
  } while (found == NULL && current != last);
  if (found == NULL) { // ��� ���������� ����� ������ ������� �������!
    throw NoMoreMemoryException();
  }

  // 2. ���� ���� �� ������� �����, �� ���������� �������
  if (found->length < sz + sizeof(BusyBlock) + sizeof(FreeBlock)) {
    FreeBlock * next = found->next,
              * pred = found->pred;
    if (next == found) {  // ��� ��� ��������� ����!
      freePtr = NULL;
    } else {
      next->pred = pred;
      freePtr = pred->next = next;
    }
    return (char*)found + sizeof(BusyBlock);

  // 3. ���� ���� ���������� �����, �� �� ������� �� ���
  } else {
    // ���������� ����� ����� �����:
    found->length -= sz + sizeof(BusyBlock);
    // ���������� ������ ������������� �����:
    char * retAddress = (char*)found + found->length;
    // ������������� ������������ ����������� ����� � ������ ����������:
    ((BusyBlock*)retAddress)->length = sz + sizeof(BusyBlock);
    return (char*)retAddress + sizeof(BusyBlock);
  }
}

// �������� �������� ����������� ����� ������ � �������
void BiListMemory::release(void * ptr) {
  // ������� ��������� ����� ������������� �����
  FreeBlock * releaseBlock = (FreeBlock*)((char*)ptr - sizeof(BusyBlock));
  // 1. ������� ��� �������� ��������� �����, ���� �� ������� ����������
  //    ���������� ����� ������������ ������, � ������ - �����.
  //    ���� � ������� ������� ������� ��� ��������� ������, ��
  //    �������� secondAddr = NULL. ����������, ���� � �������
  //    ������� ������� ��� ��������� ������, �� ������� firstAddr = NULL
  FreeBlock * firstAddr = freePtr,
            * secondAddr = freePtr;
  if (firstAddr != NULL) {
    if (firstAddr > releaseBlock) {
      while (firstAddr > releaseBlock) {
        firstAddr = firstAddr->pred;
        if (firstAddr >= freePtr) break;
      }
      secondAddr = firstAddr->next;
      if (firstAddr > releaseBlock) {
        firstAddr = NULL;
      }
    } else {
      while (secondAddr < releaseBlock) {
        secondAddr = secondAddr->next;
        if (secondAddr <= freePtr) break;
      }
      firstAddr = secondAddr->pred;
      if (secondAddr < releaseBlock) {
        secondAddr = NULL;
      }
    }
  }

  // 2. ������������� ��� ������:
  //    1) ������������ ���� ������� ��������� � ������ ��������� �������;
  //    2) ������������ ���� ������� ��������� � ����� �� �������� ������;
  //    3) �� ���� �� ���������� ����������.
  if (firstAddr != NULL
      && (char*)firstAddr + firstAddr->length == (char*)releaseBlock) {
    // ������ �� ������ ��������� � �������������
    if (secondAddr != NULL
        && (char*)releaseBlock + releaseBlock->length == (char*)secondAddr) {
      // ������ ���� ���� ��������� � ������������� - ������ (1).
      // ������ ���� ������� �� �������, � ������ ���������:
      firstAddr->length += releaseBlock->length + secondAddr->length;
      firstAddr->next = secondAddr->next;
      freePtr = secondAddr->next->pred = firstAddr;
    } else {
      // ������ (2), ������ ���� �����������
      firstAddr->length += releaseBlock->length;
    }
  } else if (secondAddr != NULL
             && (char*)releaseBlock + releaseBlock->length == (char*)secondAddr) {
    // ������ ���� - ������������ �� ����������� � ������������� - ������ (2)
    secondAddr->length += releaseBlock->length;
    secondAddr->pred->next = releaseBlock;
    *releaseBlock = *secondAddr;
    freePtr = releaseBlock->next->pred = releaseBlock;
  } else {
    // ������ (3) - � ������� ���������� ����� ��������� ����.
    if (firstAddr != NULL) {
      releaseBlock->pred = firstAddr;
      releaseBlock->next = firstAddr->next;
      firstAddr->next->pred = releaseBlock;
      firstAddr->next = releaseBlock;
    } else if (secondAddr != NULL) {
      releaseBlock->next = secondAddr;
      releaseBlock->pred = secondAddr->pred;
      secondAddr->pred->next = releaseBlock;
      secondAddr->pred = releaseBlock;
    } else {
      freePtr = releaseBlock->pred = releaseBlock->next = releaseBlock;
    }
  }
}
