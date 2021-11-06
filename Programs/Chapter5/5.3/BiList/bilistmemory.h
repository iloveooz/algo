/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bilistmemory.h                                   *
*  Описание : Описание системы распределения и управления      *
*             блоками памяти переменного размера               *
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
// Класс BiListMemory представляет буферный пул памяти и систему
// управления ею для размещения в ней блоков переменного размера.
// Свободные блоки связаны в двунаправленный упорядоченный список
//==============================================================
class BiListMemory {
  // Структура свободного блока памяти:
  struct FreeBlock { 
    size_t length;
    FreeBlock * next, * pred;
  };

  // Структура выделенного блока памяти:
  struct BusyBlock { 
    size_t length;
  };

  char * buffer;        // Указатель на буфер
  size_t size;             // Размер буфера в байтах
  // Указатель списка свободных блоков:
  FreeBlock * freePtr;

public :

  // Конструктор:
  BiListMemory(size_t n) {
    buffer = new char[size = n];
    clear();
  }

  // Деструктор:
  ~BiListMemory() { delete[] buffer; }

  // Очистка памяти.
  void clear() {
    // В буфере создается кольцевой списко из единственного
    // блока, размер которого равен размеру всего буфера
    freePtr = (FreeBlock *)buffer;
    freePtr->length = size;
    freePtr->next = freePtr->pred = freePtr;
  }

  // Операция выделения свободного блока памяти заданного размера
  void * get(size_t sz);

  // Операция возврата выделенного блока памяти в систему
  void release(void * ptr);
};

#endif
