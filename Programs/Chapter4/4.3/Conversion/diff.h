/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : diff.h                                           *
*  Описание : Описание посетителя узлов синтаксического        *
*             дерева выражений для его дифференцирования       *
***************************************************************/

#ifndef __DIFF_H
#define __DIFF_H

#include "visitor.h"
#include "expressionext.h"

//===============================================================
// Класс Diff определяет посетителя, задачей которого служит
// вычисление первой производной выражения по заданной переменной.
//===============================================================
class Diff : public Visitor {
  string variable;         // Переменная, по которой берется производная
  Expression * result;     // Результат упрощения
  static Constant * zero;  // Константа - ноль
  static Constant * one;   // Константа - единица

public :
  // Конструктор
  Diff(const string & var) : variable(var), result(NULL) {}

  // Функция доступа к результату упрощения
  Expression * getResult() const { return result; }

  // Функции посещения узлов
  // Производная константы равна нулю:
  void visit(Constant * cNode) { result = zero; }

  // Производная переменной равна нулю либо единице в зависимости
  // от того, та ли это переменная, по которой берется производная
  void visit(Variable * vNode) {
    result = vNode->getVariable() == variable ? one : zero;
  }

  // Наиболее сложная работа выпоняется при посещении бинарной операции
  void visit(Operator * opNode);
};

#endif
