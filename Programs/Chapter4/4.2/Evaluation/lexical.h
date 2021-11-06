/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : lexical.h                                        *
*  Описание : Описание структуры лексем, используемых при      *
*             анализе выражений                                *
***************************************************************/

#ifndef __LEXICAL_H
#define __LEXICAL_H

#include <string>

using namespace std;

//=============================================================
// Абстрактный класс Lexical представляет абстрактную лексему
// и определяет возможные лексические классы для анализатора
//=============================================================
class Lexical {
public :
  // Определяем возможные лексические классы
  enum LexClass {
    NUMBER = 1,
    VARIABLE,
    OPERATOR,
    LEFTPAR,
    RIGHTPAR
  };

  virtual int getLexClass() const = 0;
};

//=============================================================
// Класс LexNumber представляет лексему - целое число
//=============================================================
class LexNumber : public Lexical {
protected :
  int number;     // представляемое число

public :
  // Конструктор лексемы
  LexNumber(int num) : number(num) {}

  // Функция определения класса лексемы
  int getLexClass() const { return Lexical::NUMBER; }
  // Функция доступа
  int getNumber() const { return number; }
};

//=============================================================
// Класс LexVariable представляет лексему - идентификатор
//=============================================================
class LexVariable : public Lexical {
protected :
  string variable;   // представляемый идентификатор

public :
  // Конструктор лексемы
  LexVariable(const string & v) : variable(v) {}

  // Функция определения класса лексемы
  int getLexClass() const { return Lexical::VARIABLE; }
  // Функция доступа
  string getVariable() const { return variable; }
};

//=============================================================
// Класс LexOperator представляет лексему - знак операции или скобку
//=============================================================
class LexOperator : public Lexical {
protected :
  char oper;   // представляемый знак операции или скобка

public :
  // Конструктор лексемы
  LexOperator(char oper) : oper(oper) {}

  // Функция определения класса лексемы
  int getLexClass() const {
    return
      (oper == '(' ? Lexical::LEFTPAR :
       oper == ')' ? Lexical::RIGHTPAR :
       Lexical::OPERATOR);
  }

  // Функция вычисления приоритета операции
  int getPrio() const {
    return (oper == '-' || oper == '+' ? 1 :
            oper == '*' || oper == '/' || oper == '%' ? 2 : 0);
  }

  // Функция доступа
  char getOperSign() const { return oper; }
};

#endif
