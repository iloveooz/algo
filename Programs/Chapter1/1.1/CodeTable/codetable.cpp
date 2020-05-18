/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.1. Массивы                                        *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : codetable.cpp                                    *
*  Описание : Реализация методов класса CodeTable              *
***************************************************************/

#include <stdexcept>
#include <string>
#include "codetable.h"

using namespace std;

//*************************************************************
// Реализация методов класса:
//*************************************************************

// Конструктор
CodeTable::CodeTable(byte low, byte high, byte* iniTable) {
  if ((hBound = high) < (lBound = low)) {
    throw out_of_range("CodeTable constructor: lower bound is higher than upper one");
  }
  // Инициализация таблицы. По умолчанию таблица задает
  // "тождественное" кодирование
  array = new byte[high - low + 1];
  for (byte code = lBound; ; code++) {
    array[code - lBound] = code;
    if (code == hBound) break;
  }
  // Таблица, заданная параметром может переопределить 
  // всю таблицу или ее часть
  if (iniTable) {
    for (int ndx = 0; ndx <= high - lBound && iniTable[ndx]; ndx++)
      array[ndx] = iniTable[ndx];
  }
}

// Конструктор копирования
CodeTable::CodeTable(const CodeTable &src) {
  array = new byte [(hBound=src.hBound)-(lBound=src.lBound)+1];
  // Копирование таблицы
  for (byte ndx = lBound; ; ndx++) {
    array[ndx-lBound] = src.array[ndx-lBound];
    if (ndx == hBound) break;
  }
}

// Деструктор
CodeTable::~CodeTable() { delete[] array; }

// Операция индексации как для обычного массива
byte & CodeTable::operator[] (byte i) {
  if (i < lBound || i > hBound) {
    throw out_of_range("Index is out of range");
  }
  return array[i - lBound];
}
