/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А. Кубенский                                     *
*  Файл     : graphweight.h                                    *
*  Описание : Абстрактный тип данных, задающий нагрузку на     *
*             ребра графа                                      *
***************************************************************/

#ifndef __GRAPH_WEIGHT_H
#define __GRAPH_WEIGHT_H

class GraphWeight {
public :
  virtual double arcLength(int from, int to) const = 0;
};

#endif
