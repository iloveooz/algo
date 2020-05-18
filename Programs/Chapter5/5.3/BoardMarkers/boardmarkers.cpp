/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : boardmarkers.cpp                                 *
*  Описание : Реализация системы распределения и управления    *
*             блоками памяти методом граничных маркеров        *
***************************************************************/

#include <iostream>

using namespace std;

#include "boardmarkers.h"

void * BoardMarkersMemory::get(size_t sz) {
  // 1. Поиск свободного блока подходящей длины
  if (freePtr == NULL) throw NoMoreMemoryException();
  char * current = freePtr,
       * last = freePtr,
       * found = NULL;
  do {
    if (*(size_t*)&current[MARKER_SIZE] >= sz + SIZE_SIZE + 2*MARKER_SIZE) {
      found = current;    // свободный блок подходящей длины найден
    } else {
      // переход к следующему блоку
      current = *(char**)&current[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
    }
  } while (found == NULL && current != last);
  if (found == NULL) { // нет свободного блока памяти нужного размера!
    throw NoMoreMemoryException();
  }

  // 2. Разметка блока
  size_t * pLength = (size_t*)&found[MARKER_SIZE];
  char **  pPred   = (char**)&found[MARKER_SIZE + SIZE_SIZE];
  char **  pNext   = (char**)&found[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
  unsigned char * pEndMarker = (unsigned char *)&found[*pLength - MARKER_SIZE];

  // 3. Если блок не слишком велик, он выделяется целиком
  if (*pLength < sz + 3*SIZE_SIZE + 4*MARKER_SIZE + 2*PTR_SIZE) {
    if (*pNext == found) {  // Это был последний свободный блок
      freePtr = NULL;
    } else {                // Исключаем блок из списка
      *(char**)(*pPred + MARKER_SIZE + SIZE_SIZE+PTR_SIZE) = freePtr = *pNext;
      *(char**)(*pNext + MARKER_SIZE + SIZE_SIZE) = *pPred;
    }
    // Маркируем блок как занятый
    *found = *pEndMarker = BUSY_MARKER;
    return found + MARKER_SIZE + SIZE_SIZE;

  // 4. Если блок достаточно велик, то он делится на два
  } else {
    // вычисление новой длины свободного блока:
    *pLength -= sz + SIZE_SIZE + 2*MARKER_SIZE;
    // дополнительная разметка
    char * busyBlock = found + *pLength;
    size_t* busyLength = (size_t*)(busyBlock + MARKER_SIZE);
    unsigned char * pFreeEndMarker = (unsigned char *)(busyBlock - MARKER_SIZE);
    size_t * pEndLength = (size_t*)((char*)pFreeEndMarker - PTR_SIZE);
    // формирование верхней границы нового блока:
    *pEndLength = *pLength;
    *pFreeEndMarker = FREE_MARKER;
    // Переносим указатель списка свободных блоков
    freePtr = found;
    // окончательное формирование выдаваемого блока и выдача результата:
    *busyBlock = *pEndMarker = BUSY_MARKER;
    *busyLength = sz + SIZE_SIZE + 2*MARKER_SIZE;
    return busyBlock + MARKER_SIZE + SIZE_SIZE;
  }
}

void BoardMarkersMemory::release(void * ptr) {
  // Сначала вычисляем адрес возвращаемого блока
  char * releaseBlock = (char*)ptr - SIZE_SIZE - MARKER_SIZE;
  // 1. Проверяем соседние блоки и вычисляем их адреса, если это
  //    свободные блоки. Отсутствие свободного блока помечается
  //    пустой ссылкой.
  char * firstAddr = releaseBlock > buffer && ((unsigned char *)releaseBlock)[-MARKER_SIZE] == FREE_MARKER ?
                     releaseBlock - *(size_t*)&releaseBlock[-MARKER_SIZE - SIZE_SIZE] :
                     NULL,
       * secondAddr = releaseBlock + *(size_t*)&releaseBlock[MARKER_SIZE];
  if (secondAddr == buffer+size || *(unsigned char *)secondAddr != FREE_MARKER) secondAddr = NULL;

  // 2. Рассматриваем три случая:
  //    1) возвращаемый блок удается соединить с обоими соседними блоками;
  //    2) возвращаемый блок удается соединить с одним из соседних блоков;
  //    3) ни одно из соединений невозможно.
  if (firstAddr != NULL) {
    // Первый из блоков примыкает к возвращаемому
    if (secondAddr != NULL) {
      // Второй блок тоже примыкает к возвращаемому - случай (1).
      // Второй блок удаляем из системы, а первый расширяем:
      size_t newLen = (*(size_t*)&firstAddr[MARKER_SIZE] += *(size_t*)&releaseBlock[MARKER_SIZE] + *(size_t*)&secondAddr[MARKER_SIZE]);
      *(size_t*)&firstAddr[MARKER_SIZE] = newLen;
      *(size_t*)&firstAddr[newLen - MARKER_SIZE - SIZE_SIZE] = newLen;
      char * predBlock = *(char**)&secondAddr[MARKER_SIZE + SIZE_SIZE];
      char * nextBlock = *(char**)&secondAddr[MARKER_SIZE + SIZE_SIZE + PTR_SIZE];
      *(char**)&predBlock[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = nextBlock;
      *(char**)&nextBlock[MARKER_SIZE + SIZE_SIZE] = predBlock;
    } else {
      // Случай (2), первый блок расширяется
      size_t newLen = *(size_t*)&firstAddr[MARKER_SIZE] + *(size_t*)&releaseBlock[MARKER_SIZE];
      *(size_t*)&firstAddr[MARKER_SIZE] = newLen;
      firstAddr[newLen - MARKER_SIZE] = FREE_MARKER;
      *(size_t*)&firstAddr[newLen - MARKER_SIZE - SIZE_SIZE] = newLen;
    }
  } else if (secondAddr != NULL) {
    // Второй блок - единственный из примыкающих к возвращаемому - случай (2)
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
    // Случай (3) - в системе появляется новый свободный блок.
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
