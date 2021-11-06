/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.3. Преобразование формул                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : context.h                                        *
*  Описание : Ассоциативная таблица для замены переменных      *
*             в выражении                                      *
***************************************************************/

#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "hashtable.h"
#include "expression.h"

class Context : public HashTable<Expression> {
// public :
//   Expression * add(const char * key, Object * obj);
//   Expression * find(const char * key) const;
//   Expression * remove(const char * key);
};

#endif
