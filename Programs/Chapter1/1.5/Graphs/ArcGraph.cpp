/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ArcGraph.cpp                                     *
*  Описание : Реализация методов класса ArcGraph               *
***************************************************************/

#include "ArcGraph.h"

// Деструктор
ArcGraph::~ArcGraph() {
  Arc * current = first,
      * pred = NULL;
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
}

// Добавление дуги к списку
void ArcGraph::addArc(int from, int to) {
  if (from < 0 || to < 0 || from >= vertexNumber || to >= vertexNumber)
    return;      // Неправильно задана дуга
  Arc *newArc = new Arc(from, to);
  // Новая дуга добавляется в конец списка
  if (last) last->next = newArc; else first = newArc;
  last = newArc;
  arcCount++;
}

// Проверка существования дуги в графе
bool ArcGraph::hasArc(int from, int to) const {
  // Цикл, перебирающий элементы списка дуг
  for (Arc *current = first; current; current = current->next) {
    if (current->begin == from && current->end == to) {
      // Дуга найдена
      return true;
    }
  }
  // Дуга не найдена:
  return false;
}
