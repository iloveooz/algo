/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.3. Определение остовных деревьев                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : arc.h                                            *
*  Описание : Описание структуры ребра для алгоритма Крускала  *
***************************************************************/

#ifndef __ARC_H
#define __ARC_H

#include <iostream>

//==============================================================
// Структура ребра для алгоритма Крускала: сравнение ребер
// происходит по их весам
//==============================================================

struct Arc {
  int from, to;
  double weight;

  Arc(int from = 0, int to = 0, double weight = 0) : from(from), to(to), weight(weight) {}
  Arc(const Arc & arc) : from(arc.from), to (arc.to), weight(arc.weight) {}

  Arc & operator = (const Arc & arc) { from = arc.from; to = arc.to; weight = arc.weight; }
  bool operator < (const Arc & arc) { return weight < arc.weight; }
  bool operator <= (const Arc & arc) { return weight <= arc.weight; }
  bool operator > (const Arc & arc) { return weight > arc.weight; }
  bool operator >= (const Arc & arc) { return weight >= arc.weight; }
  bool operator == (const Arc & arc) { return weight == arc.weight; }
  bool operator != (const Arc & arc) { return weight != arc.weight; }
};

std::ostream & operator << (std::ostream & out, const Arc & arc);

#endif
