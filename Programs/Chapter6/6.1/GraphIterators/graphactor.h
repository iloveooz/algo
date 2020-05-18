/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.1. Обходы и поиск в графах                        *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : graphactor.h                                  *
*  Описание    : Описание абстрактного посетителя элементов    *
*                графа                                         *
***************************************************************/

#ifndef __GRAPH_ACTOR_H
#define __GRAPH_ACTOR_H

class GraphActor {
public :
  virtual void vertexIn(int vertex) {}
  virtual void vertexOut(int vertex) {}
  virtual void arcForward(int begin, int end, bool newVertex) {}
  virtual void arcBackward(int begin, int end) {}
  virtual void newSelection(int vertex) {}
};

#endif
