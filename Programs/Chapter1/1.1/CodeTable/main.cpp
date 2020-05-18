/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.1. Массивы                                        *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Пример использования класса CodeTable            *
***************************************************************/

#include <iostream>
#include <string>
#include "codetable.h"

using namespace std;

// Функция кодирования
void doCode(byte* source, byte* dest, CodeTable & codeTable) {
  for (int i = 0; source[i]; i++) {
    dest[i] = codeTable[source[i]];
  }
}

// В проверочной таблице немножко перемешаны 
// коды маленьких латинских букв
int main() {
  CodeTable codeTable(32, 255);
  // Заполняем новые "перевернутые" коды для маленьких латинских букв
  for (int i = 0; i < 13; i++) {
    byte b = codeTable['a' + i];
    codeTable['a' + i] = codeTable['z' - i];
    codeTable['z' - i] = b;
  }

  byte *src = (byte*)"Hello, World!";            // Исходное сообщение
  byte *dst = new byte[strlen((char*)src) + 1];  // Буфер строки назначения
  memset(dst, 0, strlen((char*)src) + 1);
  doCode(src, dst, codeTable);
  cout << "Source string : <" << src << ">\n"
       << "Destination string : <" << dst << ">\n";
  return 0;
}
