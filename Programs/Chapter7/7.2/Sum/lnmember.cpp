/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : lnmember.cpp                                     *
*  Описание : Реализация поведения члена суммы ряда для        *
*             приближенного вычисления значения числа ln 2     *
***************************************************************/

#include "lnmember.h"
#include "summator.h"
#include <stdlib.h>

//--------------------------------------------------------------
// Генератор порождает сообщение о готовом значении,
// сразу вычисляя его по номеру члена ряда.
// Сообщение порождается только один раз.
//--------------------------------------------------------------
Message * LnMember::generate() {
  // Проверка, не было ли уже порождено сообщение
  if (generated) return NULL;

  generated = true;
  double value = 1.0 / (number + 1);
  if (number & 1) value = -value;
  return new SumMessage(MemberValue(number, value));
}
