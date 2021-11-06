/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.4. Итераторы                                      *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : Actor.h                                       *
*  Описание    : Абстрактный класс для задания действия        *
*                с элементом списка при итерации               *
***************************************************************/

#ifndef __ACTOR_H
#define __ACTOR_H

//**************************************************************
// Описание класса Actor
//**************************************************************

class Actor {
public:
  virtual void action(int & element) = 0;
};

#endif
