/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : substitutor.h                                    *
*  Описание : Описание посетителя узлов синтаксического        *
*             дерева выражений для вычисления его значения     *
***************************************************************/

#ifndef __SUBSTITUTOR_H
#define __SUBSTITUTOR_H

#include "visitor.h"

//===============================================================
// Класс Substitutor определяет посетителя, задачей которого
// служит подстановка в выражение вместо переменных из заданного
// контекста заданных в нем выражений.
//===============================================================
class Substitutor : public Visitor {
  Context * context;     // Контекст вычисления
  Expression * result;   // Результат вычисления

public :
  // Конструктор:
  Substitutor(Context * ctx) : context(ctx), result(NULL) {}
  // Выдача результата
  Expression * getResult() const { return result; }
  // Операции посещения узлов
  void visit(Constant * cNode) { result = cNode; }
  void visit(Variable * varNode) {
    Expression * substitution = context->find(varNode->getVariable());
    result = substitution ? substitution : varNode;
  }
  void visit(Operator * opNode);
};

#endif
