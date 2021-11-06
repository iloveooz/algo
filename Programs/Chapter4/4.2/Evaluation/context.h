/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : context.h                                        *
*  Описание : Ассоциативная таблица для поиска значений        *
*             переменных                                       *
***************************************************************/

#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "hashtable.h"
#include "expression.h"

class Context : public HashTable<Constant> {
// public :
//   Constant * add(const char * key, Object * obj);
//   Constant * find(const char * key) const;
//   Constant * remove(const char * key);
};

#endif
