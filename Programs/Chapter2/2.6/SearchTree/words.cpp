/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.6. Бинарные деревья поиска                        *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : words.cpp                                        *
*  Описание : Реализация операторов сравнения слов и вывода    *
*             слова в символьный выходной поток                *
***************************************************************/

#include "words.h"

bool operator < (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) < 0;
}

bool operator == (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) == 0;
}

bool operator > (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) > 0;
}

bool operator <= (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) <= 0;
}

bool operator >= (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) >= 0;
}

bool operator != (const Word & s1, const Word & s2) {
  return stricmp(s1.src, s2.src) != 0;
}

ostream & operator << (ostream & out, const Word & w) {
  return out << w.src;
}

