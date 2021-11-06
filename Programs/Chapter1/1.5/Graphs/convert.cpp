/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : convert.h                                        *
*  Описание : Определение функций преобразований графов        *
***************************************************************/

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include "convert.h"

// Преобразование из A-графа в M-граф
MatrixGraph * convert(const ArcGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  MatrixGraph *destGraph = new MatrixGraph(n);
  // Цикл по дугам списка
  for (ArcGraph::Arc * current = srcGraph.first;
       current; current = current->next) {
    // Установить значение "истина" для соответствующего элемента массива
    destGraph->graph[current->begin][current->end] = true;
  }
  return destGraph; 
}

// Преобразование из M-графа в S-граф
SetGraph * convert(const MatrixGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  SetGraph *destGraph = new SetGraph(n);
  for (int i = 0; i < n; i++) {
    bool * srcRow = srcGraph.graph[i];    // Представление строки исходного графа
    Set & destRow = *destGraph->graph[i]; // Соответствующее множество результирующего графа
    for (int j = 0; j < n; j++) {
      // Новая дуга записывается с помощью операции добавления элемента к множеству
      if (srcRow[j]) destRow |= j;
    }
  }
  return destGraph; 
}

// Преобразование из S-графа в L-граф
ListGraph * convert(const SetGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  ListGraph *destGraph = new ListGraph(n);
  for (int i = 0; i < n; i++) {
    Set & srcRow = *srcGraph.graph[i];          // Представление строки исходного графа
    List<int> & destRow = destGraph->graph[i];  // Соответствующий список дуг в результирующем графе
    for (int j = 0; j < n; j++)
      // Новая дуга записывается с помощью операции добавления элемента в список
      if (srcRow.has(j)) destRow.add(j);
  }
  return destGraph; 
}

// Преобразование из L-графа в A-граф
ArcGraph * convert(const ListGraph & srcGraph) {
  int n = srcGraph.vertexCount();
  ArcGraph *destGraph = new ArcGraph(n);
  // Цикл сбора информации обо всех дугах исходного графа
  for (int i = 0; i < n; i++) {
    // Список исследуется непосредственно с использованием знания о его структуре
    List<int>::ListItem *current = srcGraph.graph[i].first;
    while (current) {
      // Новая дуга записывается в граф с помощью операции добавления дуги
      destGraph->addArc(i, current->item);
      current = current->next;
    }
  }
  return destGraph; 
}
