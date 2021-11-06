/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : fibmember1.cpp                                   *
*  Описание : Реализация поведения объекта-члена суммы первых  *
*             членов последовательности чисел Фибоначчи        *
***************************************************************/

#include "fibmember1.h"
#include "dispatcher.h"
#include "summator.h"
#include <stdlib.h>

//--------------------------------------------------------------
// Генератор порождает сообщение о готовом значении, только если
// номер члена ряда меньше трех или уже готово значение обоих
// предыдущих членов суммы. Сообщение порождается только один раз.
//--------------------------------------------------------------
Message * FibMember1::generate() {
  Message * result = NULL;

  if (number == 0 || number == 1) {
    // Для первых членов суммы значение порождается сразу же
    result = new SumMessage(MemberValue(number, 1));
  } else if (accepted1 && accepted2) {
    // Предыдущие члены суммы уже вычислены;
    // вычисляем значение данного члена суммы на их основе
    result = new SumMessage(MemberValue(number, pred + predPred));
  }
  if (result) {
    Dispatcher::getInstance()->removeGenerator(this);
    Dispatcher::getInstance()->removeHandler(this);
    delete this;
  }
  return result;
}

//--------------------------------------------------------------
// Обработчик принимает значение некоторого члена суммы, и
// если номер этого члена на 1 или 2 меньше собственного
// номера, запоминает его для дальнейшего вычисления.
//--------------------------------------------------------------
bool FibMember1::handle(const Message & msg) {
  // Проверка, не было ли уже запомнено значение предыдущих членов
  if (accepted1 && accepted2) return false;

  // Проверка класса сообщения
  if (msg.getMsgClass() != SumMessage::msgMemberReady) return false;
  const SumMessage & myMsg = (const SumMessage &)msg;

  // Анализ и запоминание параметра сообщения
  MemberValue value = myMsg.getValue();
  if (!accepted1 && value.getNumber() == number-1) {
    pred = (int)value.getValue();
    accepted1 = true;
  } else if (!accepted2 && value.getNumber() == number-2) {
    predPred = (int)value.getValue();
    accepted2 = true;
  }

  // Во всех случаях сообщение передается дальше для анализа его 
  // другими обработчиками.
  return false;
}
