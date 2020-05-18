/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : boardmarkers.h                                   *
*  Описание : Описание системы распределения и управления      *
*             блоками памяти методом граничных маркеров        *
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
// Класс BiListMemory представляет буферный пул памяти и систему
// управления ею для размещения в ней блоков переменного размера.
// Свободные блоки связаны в двунаправленный упорядоченный список
//==============================================================
class BoardMarkersMemory {
  // Коды граничных маркеров
  static const unsigned char FREE_MARKER = 0xCC;
  static const unsigned char BUSY_MARKER = 0x33;

  // Размеры в байтах элементов управляющей информации
  static const int MARKER_SIZE = sizeof(unsigned char);
  static const int PTR_SIZE = sizeof(char*);
  static const int SIZE_SIZE = sizeof(size_t);

  char * buffer;        // Указатель на буфер
  size_t size;          // Размер буфера в байтах
  // Указатель списка свободных блоков:
  char * freePtr;

public :

  // Конструктор:
  BoardMarkersMemory(size_t n) {
    buffer = new char[size = n];
    clear();
  }

  // Деструктор:
  ~BoardMarkersMemory() { delete[] buffer; }

  // Очистка памяти.
  void clear() {
    // В буфере создается кольцевой список из единственного
    // блока, размер которого равен размеру всего буфера
    freePtr = buffer;

    *freePtr = FREE_MARKER;
    *(size_t*)&freePtr[MARKER_SIZE] = size;
    *(char**)&freePtr[MARKER_SIZE + SIZE_SIZE] = freePtr;
    *(char**)&freePtr[MARKER_SIZE + SIZE_SIZE + PTR_SIZE] = freePtr;

    *(unsigned char *)&freePtr[size - MARKER_SIZE] = FREE_MARKER;
    *(size_t*)&freePtr[size - MARKER_SIZE - SIZE_SIZE] = size;
  }

  // Операция выделения свободного блока памяти заданного размера
  void * get(size_t sz);

  // Операция возврата выделенного блока памяти в систему
  void release(void * ptr);
};

#endif
