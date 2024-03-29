/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : simplifier.h                                     *
*  Описание : Описание посетителя узлов синтаксического        *
*             дерева выражений для его упрощения               *
***************************************************************/

#ifndef __SIMPLIFIER_H
#define __SIMPLIFIER_H

#include "visitor.h"
#include "expressionext.h"

//===============================================================
// Класс Simplifier определяет посетителя, задачей которого
// служит преобразование операций в выражении там, где возможно
// их упрощение.
//===============================================================
class Simplifier : public Visitor {
  Expression * result;     // Результат упрощения
  static Constant * zero;  // Константа - ноль
  static Constant * one;   // Константа - единица

public :
  // Конструктор
  Simplifier() : result(NULL) {}

  // Функция доступа к результату упрощения
  Expression * getResult() const { return result; }

  // Функции посещения узлов
  // Константа упрощению не подлежит:
  void visit(Constant * cNode) { result = cNode; }

  // Переменная также не упрощается:
  void visit(Variable * vNode) { result = vNode; }

  // Оператор можно упростить, если это бинарный оператор
  void visit(Operator * opNode);
};

#endif
