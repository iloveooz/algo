/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 7. Обмен сообщениями и обработка сообщений        *
*          7.2. Об одном способе вычисления конечных сумм      *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : generator.h                                      *
*  Описание : Интерфейс с генератором событий                  *
***************************************************************/

#ifndef __GENERATOR_H
#define __GENERATOR_H

#include <stdlib.h>
#include "message.h"

class Generator {
public :
  virtual Message * generate() { return NULL; };
};

#endif
