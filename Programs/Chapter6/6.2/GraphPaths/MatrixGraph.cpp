/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.2. Поиск кратчайших путей                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : MatrixGraph.cpp                                  *
*  Описание : Реализация методов класса MatrixGraph            *
***************************************************************/

#include "MatrixGraph.h"

// Конструктор
MatrixGraph::MatrixGraph(int n) {
  graph = new bool*[vertexNumber = n];
  for (int i=0; i<n; i++) {
    // создание строки
    bool *row = graph[i] = new bool[n];
    // инициализация элементов строки
    for (int j = 0; j < n; j++) {
      row[j] = false;
    }
  }
}

// Конструктор копирования
MatrixGraph::MatrixGraph(const MatrixGraph & src) {
  int n = src.vertexCount();
  graph = new bool*[vertexNumber = n];
  for (int i=0; i<n; i++) {
    // создание строки
    bool *row = graph[i] = new bool[n];
    bool *srcRow = src.graph[i];
    // инициализация элементов строки
    for (int j = 0; j < n; j++) {
      row[j] = srcRow[j];
    }
  }
}

// Деструктор
MatrixGraph::~MatrixGraph() {
  for (int i = 0; i < vertexNumber; i++) {
    delete graph[i];
  }
  delete graph;
}

// Оператор копирования
MatrixGraph & MatrixGraph::operator = (const MatrixGraph & src) {
  // Копирование структуры:
  int n;
  if (vertexNumber != (n = src.vertexCount())) {
    this->~MatrixGraph();
    graph = new bool*[vertexNumber = n];
    for (int i = 0; i < n; i++) {
      // создание строки
      bool *row = graph[i] = new bool[n];
    }
  }

  // Копирование элементов
  for (int i = 0; i < n; i++) {
    bool * row = graph[i];
    bool * srcRow = src.graph[i];
    for (int j = 0; j < n; j++) {
      row[j] = srcRow[j];
    }
  }
}

// Добавление дуги - элемент массива устанавливается в true
void MatrixGraph::addArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // Неправильно задана дуга
  graph[from][to] = true;
}

// Удаление дуги - элемент массива устанавливается в false
void MatrixGraph::removeArc(int from, int to) {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return;    // Неправильно задана дуга
  graph[from][to] = false;
}

// Проверка существования дуги
bool MatrixGraph::hasArc(int from, int to) const {
  if (from < 0 || from >= vertexNumber || to < 0 || to >= vertexNumber)
    return false;    // Неправильно задана дуга
  return graph[from][to];
}

std::ostream & operator << (std::ostream &out, const MatrixGraph & matrix) {
  for (int i = 0; i < matrix.vertexCount(); i++) {
    for (int j = 0; j < matrix.vertexCount(); j++) {
      out << (matrix.hasArc(i, j) ? " 1" : " 0");
    }
    out << std::endl;
  }
  return out;
}

MatrixGraph mult(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes) {
  int n;
  MatrixGraph result(n = G1.vertexCount());
  if (n != G2.vertexCount()) {
    throw IncompatibleSizes();
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (G1.graph[i][k] && G2.graph[k][j]) {
          result.addArc(i, j);
          break;
        }
      }
    }
  }
  return result;
}

MatrixGraph add(const MatrixGraph & G1, const MatrixGraph & G2) throw(IncompatibleSizes) {
  int n;
  MatrixGraph result(n = G1.vertexCount());
  if (n != G2.vertexCount()) {
    throw IncompatibleSizes();
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result.graph[i][j] = G1.graph[i][j] || G2.graph[i][j];
    }
  }
  return result;
}

MatrixGraph closure(const MatrixGraph & G) {
  MatrixGraph Gi = G;
  for (int i = 0; i < G.vertexCount(); i++) {
    Gi = add(mult(Gi, G), G);
  }
  return Gi;
}

void FloydWarshall(MatrixGraph & G) {
  int n = G.vertexCount();
  for (int k = 1; k < n; k++) {
    for (int i = 0;  i < n;  i++) {
      for (int j = 0;  j < n;  j++) {
        if (i != k-1 && !G.graph[i][j]) {
          G.graph[i][j] = G.graph[i][k-1] && G.graph[k-1][j];
        }
      }
    }
  }
}

void getMinPaths(const MatrixGraph & G,   // Исходный граф
                 const GraphWeight & w,   // Нагрузка на дуги
                 double ** & P,           // Переменные для матрицы путей
                 int ** & D               // ...и для матрицы направлений
                ) {
  int n = G.vertexCount();      // Число вершин графа

  // Инициализация матриц.
  // В матрицу длин путей записываются длины дуг исходного графа:
  P = new double*[n];
  for (int i = 0; i < n; i++) {
    double * row = P[i] = new double[n];
    for (int j = 0; j < n; j++) {
      row[j] = w.arcLength(i, j);
    }
  }
  // В матрицу направлений записывается информация о направлениях
  // дуг исходного графа (-1, если направление не определено):
  D = new int*[n];
  for (int i = 0; i < n; i++) {
    int * row = D[i] = new int[n];
    for (int j = 0; j < n; j++) {
      row[j] = (G.hasArc(i, j) ? j : -1);
    }
  }

  // Вычисление кратчайших путей и направлений
  // по алгоритму Флойда-Уоршалла
  for (int k = 1; k < n; k++) {
    for (int i = 0;  i < n;  i++) {
      for (int j = 0;  j < n;  j++) {
        if (i != k-1 && P[i][k-1] < INFINITY && P[k-1][j] < INFINITY &&
            P[i][j] > P[i][k-1] + P[k-1][j]) {
          P[i][j] = P[i][k-1] + P[k-1][j];
          D[i][j] = D[i][k-1];
        }
      }
    }
  }
}
