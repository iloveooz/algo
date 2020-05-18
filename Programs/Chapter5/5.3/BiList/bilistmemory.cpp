/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bilistmemory.cpp                                 *
*  Описание : Реализация системы распределения и управления    *
*             блоками памяти переменного размера, организо-    *
*             ванными в кольцевой двунаправленный список       *
***************************************************************/

#include "bilistmemory.h"
#include <iostream>

using namespace std;

// Операция выделения свободного блока памяти заданного размера
void * BiListMemory::get(size_t sz) {
  // 1. Поиск свободного блока подходящей длины
  if (freePtr == NULL) throw NoMoreMemoryException();
  FreeBlock * current = freePtr,
            * last = freePtr,
            * found = NULL;
  do {
    if (current->length >= sz + sizeof(BusyBlock)) {
      found = current;    // свободный блок подходящей длины найден
    } else {
      current = current->next; // переход к следующему блоку
    }
  } while (found == NULL && current != last);
  if (found == NULL) { // нет свободного блока памяти нужного размера!
    throw NoMoreMemoryException();
  }

  // 2. Если блок не слишком велик, он выделяется целиком
  if (found->length < sz + sizeof(BusyBlock) + sizeof(FreeBlock)) {
    FreeBlock * next = found->next,
              * pred = found->pred;
    if (next == found) {  // Это был последний блок!
      freePtr = NULL;
    } else {
      next->pred = pred;
      freePtr = pred->next = next;
    }
    return (char*)found + sizeof(BusyBlock);

  // 3. Если блок достаточно велик, то он делится на два
  } else {
    // вычисление новой длины блока:
    found->length -= sz + sizeof(BusyBlock);
    // вычисление адреса возвращаемого блока:
    char * retAddress = (char*)found + found->length;
    // окончательное формирование выдаваемого блока и выдача результата:
    ((BusyBlock*)retAddress)->length = sz + sizeof(BusyBlock);
    return (char*)retAddress + sizeof(BusyBlock);
  }
}

// Операция возврата выделенного блока памяти в систему
void BiListMemory::release(void * ptr) {
  // Сначала вычисляем адрес возвращаемого блока
  FreeBlock * releaseBlock = (FreeBlock*)((char*)ptr - sizeof(BusyBlock));
  // 1. Находим два соседних свободных блока, один из которых расположен
  //    расположен перед возвращаемым блоком, а другой - после.
  //    Если в области больших адресов нет свободных блоков, то
  //    полагаем secondAddr = NULL. Аналогично, если в области
  //    меньших адресов нет свободных блоков, то считаем firstAddr = NULL
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

  // 2. Рассматриваем три случая:
  //    1) возвращаемый блок удается соединить с обоими соседними блоками;
  //    2) возвращаемый блок удается соединить с одним из соседних блоков;
  //    3) ни одно из соединений невозможно.
  if (firstAddr != NULL
      && (char*)firstAddr + firstAddr->length == (char*)releaseBlock) {
    // Первый из блоков примыкает к возвращаемому
    if (secondAddr != NULL
        && (char*)releaseBlock + releaseBlock->length == (char*)secondAddr) {
      // Второй блок тоже примыкает к возвращаемому - случай (1).
      // Второй блок удаляем из системы, а первый расширяем:
      firstAddr->length += releaseBlock->length + secondAddr->length;
      firstAddr->next = secondAddr->next;
      freePtr = secondAddr->next->pred = firstAddr;
    } else {
      // Случай (2), первый блок расширяется
      firstAddr->length += releaseBlock->length;
    }
  } else if (secondAddr != NULL
             && (char*)releaseBlock + releaseBlock->length == (char*)secondAddr) {
    // Второй блок - единственный из примыкающих к возвращаемому - случай (2)
    secondAddr->length += releaseBlock->length;
    secondAddr->pred->next = releaseBlock;
    *releaseBlock = *secondAddr;
    freePtr = releaseBlock->next->pred = releaseBlock;
  } else {
    // Случай (3) - в системе появляется новый свободный блок.
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
