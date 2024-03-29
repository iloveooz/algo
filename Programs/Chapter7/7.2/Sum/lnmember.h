/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : lnmember.h                                       *
*  Описание : Описание класса объекта-члена суммы ряда для     *
*             приближенного вычисления значения числа ln 2     *
***************************************************************/

#ifndef __LNMEMBER_H
#define __LNMEMBER_H

#include "member.h"
#include "message.h"

//-------------------------------------------------------------
// Класс LnMember описывает поведение объекта-члена суммы ряда
// для приближенного вычисления логарифма двух как участника
// системы обмена сообщениями для суммирования
//-------------------------------------------------------------

class LnMember : public Member {
  int number;      // Номер члена суммы (от нуля до некоторого n)
  bool generated;  // Значение уже сгенерировано?

public :
  // Конструктор запоминает номер
  LnMember(int i = 0) : number(i), generated(false) {}

  LnMember(const LnMember & src)
    : number(src.number), generated(src.generated) {}

  // Реализация операций по обмену сообщениями
  Message * generate();
};

//-------------------------------------------------------------
// Класс LnMemberFactory описывает фабрику для создания объектов-
// членов суммы ряда для приближенного вычисления логарифма двух
//-------------------------------------------------------------

class LnMemberFactory : public MemberFactory {
public :
  Member * createMember(int i) const { return new LnMember(i); }
};

#endif
