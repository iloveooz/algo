/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.2. Распределение памяти блоками постоянной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : blockbuffer.h                                    *
*  Описание : Реализация системы распределения и управления    *
*             блоками постоянного размера                      *
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
// Класс BlockBuffer представляет буферный пул памяти и систему
// управления ею для размещения в ней блоков постоянного размера
//==============================================================
template <int blockSize>
class BlockBuffer {
  char * buffer;        // Указатель на буфер
  int size;             // Размер буфера в блоках
  // Указатели свободных блоков:
  void * freePtr;       // в списке свободных блоков
  int freeArea;         // в области нераспределенной памяти

public :

  // Конструктор:
  BlockBuffer(int n) {
    buffer = new char[(size = n) * blockSize];
    if (buffer == NULL) {
      throw NoMoreMemoryException();
    }
    clear();
  }

  // Деструктор:
  ~BlockBuffer() { delete[] buffer; }

  // Очистка памяти.
  void clear() {
    freePtr = NULL;
    freeArea = 0;
  }

  // Операция выделения элемента свободной части буфера
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
