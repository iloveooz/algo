/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bintwins.h                                       *
*  Описание : Описание системы распределения и управления      *
*             блоками памяти методом двоичных близнецов        *
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
// Класс BinTwinsMemory представляет буферный пул памяти и систему
// управления ею для размещения в ней блоков переменного размера.
// Свободные блоки образуют систему "двоичных близнецов"
//==============================================================
class BinTwinsMemory {
  static const size_t null = 0xFFFF;

  char * buffer;        // Указатель на буфер
  int power;            // Двоичный показатель размера буфера
  // Массив списков свободных блоков одного размера:
  size_t * freeLists;

  // Статистика запросов к памяти:
  static int claims;
  static size_t reserved;
  static size_t demanded;

public :

  // Конструктор:
  BinTwinsMemory(int n) {
    freeLists = new size_t[(power = n) + 1];
    buffer = new char[1 << power];
    clear();
  }

  // Деструктор:
  ~BinTwinsMemory() {
    delete[] buffer;
    delete[] freeLists;
  }

  // Очистка памяти.
  void clear() {
    for (int i = 0; i < power; i++) freeLists[i] = null;
    freeLists[power] = 0;
    *(size_t *)buffer = null;
  }

  // Операция выделения свободного блока памяти заданного размера
  void * get(size_t sz);

  // Операция возврата выделенного блока памяти в систему
  void release(void * ptr, size_t sz);

  // Доступ к статистике
  static int getClaims() { return claims; }
  static size_t getReserved() { return reserved; }
  static size_t getDemanded() { return demanded; }

private :

  size_t getRec(char p);
  void BinTwinsMemory::releaseRec(size_t block, char p);
};

#endif
