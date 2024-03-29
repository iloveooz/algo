/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : fibmember1.h                                     *
*  Описание : Описание класса объекта-члена суммы первых       *
*             членов последовательности чисел Фибоначчи        *
***************************************************************/

#ifndef __FIBMEMBER1_H
#define __FIBMEMBER1_H

#include "member.h"
#include "message.h"

//-------------------------------------------------------------
// Класс FibMember описывает поведение объекта-члена суммы
// последовательности чисел Фибоначчи как участника системы
// обмена сообщениями для суммирования
//-------------------------------------------------------------

class FibMember1 : public Member {
  int number;      // Номер члена суммы (от нуля до некоторого n)
  int pred;        // Запомненное значение предыдущего члена
  int predPred;    // Запомненное значение пред-предыдущего члена
  bool accepted1;  // Предыдущее значение получено?
  bool accepted2;  // Пред-предыдущее значение получено?

public :
  // Конструктор запоминает номер
  FibMember1(int i = 0)
    : number(i), accepted1(false), accepted2(false)
  {}

  FibMember1(const FibMember1 & src)
    : number(src.number), pred(src.pred), predPred(src.predPred),
      accepted1(src.accepted1), accepted2(src.accepted2)
  {}

  // Реализация операций по обмену сообщениями
  Message * generate();
  bool handle(const Message & msg);
};

//-------------------------------------------------------------
// Класс FibMemberFactory описывает фабрику для создания объектов-
// членов суммы последовательности первых n чисел Фибоначчи
//-------------------------------------------------------------

class FibMemberFactory1 : public MemberFactory {
public :
  Member * createMember(int i) const { return new FibMember1(i); }
};

#endif
