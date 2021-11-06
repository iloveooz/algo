/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : MatrixGraph.h                                    *
*  Описание : Определение класса MatrixGraph с реализацией     *
*             графа в виде матрицы логических значений         *
***************************************************************/

#ifndef __MATRIX_GRAPH_H
#define __MATRIX_GRAPH_H

#include <iostream>
#include <exception>
#include "graphweight.h"
#include "infinity.h"

class IncompatibleSizes : public std::exception {
  char * reason;
public :
  IncompatibleSizes(char * message = "Incompatible sizes of matrices") : reason(message) {}
  const char * what() const throw() { return reason; }
};

//**************************************************************
// Определение класса MatrixGraph графа,
// представленного матрицей смежности
//**************************************************************

class MatrixGraph {

  friend MatrixGraph mult(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
  friend MatrixGraph add(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
  friend MatrixGraph closure(const MatrixGraph & G);
  friend void FloydWarshall(MatrixGraph & G);
  friend void getMaxPaths(const MatrixGraph & G, const GraphWeight & w, double ** & P, int ** & D);

  // двумерный массив логических значений
  bool **graph;

  // Число вершин графа
  int vertexNumber;

public:

  // Конструкторы
  MatrixGraph(int n);
  MatrixGraph(const MatrixGraph & src);

  // Деструктор
  ~MatrixGraph();

  // Операция присваивания графов
  MatrixGraph & operator = (const MatrixGraph & src);

  // Функция подсчета числа вершин просто выдает
  // ранее сохраненное значение
  int vertexCount() const { return vertexNumber; }

  // Основные методы работы с графом
  void addArc(int from, int to);
  void removeArc(int from, int to);
  bool hasArc(int from, int to) const;
};

// Вывод матрицы смежности графа в выходной поток

std::ostream & operator << (std::ostream &out, const MatrixGraph & matrix);

MatrixGraph mult(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
MatrixGraph add(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes);
MatrixGraph closure(const MatrixGraph & G);
void FloydWarshall(MatrixGraph & G);
void getMinPaths(const MatrixGraph & G, const GraphWeight & w, double ** & P, int ** & D);

#endif
