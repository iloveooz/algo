/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.5. Графы                                          *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListGraph.h                                      *
*  Описание : Определение класса ListGraph с реализацией графа *
*             в виде массива списков дуг                       *
***************************************************************/

#ifndef __LIST_GRAPH_H
#define __LIST_GRAPH_H

#include "Graph.h"
#include <stdlib.h>

class SetGraph;
class ArcGraph;
class ListGraph;

//**************************************************************
// Определение шаблона для класса List вставлено непосредственно
// в файл ListGraph.h
//**************************************************************

template <class T>
class List {
  // Структура списка должна быть доступна для функции преобразования
  friend ArcGraph * convert(const ListGraph & srcGraph);

  // Определение элемента списка
  struct ListItem {
    T item;             // Сам элемент
    ListItem *next;     // Указатель на следующий элемент

    // Конструктор элемента списка
    ListItem(const T &item, ListItem *next = NULL) {
      ListItem::item = item;
      ListItem::next = next;
    }
  };

  // Представление списка: указатели на первый и последний элементы
  ListItem *first, *last;

  // Счетчик числа элементов
  int count;

public:

  // Коснтруктор списка создает новый пустой список
  List() { first = last = NULL; count = 0; }

  // Деструктор списка уничтожает его элементы
  ~List();

  // Метод для добавления элемента к списку
  void add(const T &);

  // Метод для проверки, имеется ли элемент в списке
  bool has(const T &) const;
};

//**************************************************************
// Методы шаблонов класса List
//**************************************************************

// Деструктор
template <class T>
List<T>::~List() {
  ListItem * current = first,
           * pred = NULL;
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
}

// Добавление элемента к списку
template <class T>
void List<T>::add(const T & item) {
  ListItem *newItem = new ListItem(item);
  // новый элемент добавляется в конец списка
  if (last) last->next = newItem; else first = newItem;
  last = newItem;
  count++;
}

// Проверка существования элемента в списке
template <class T>
bool List<T>::has(const T & item) const {
  for (ListItem *current = first; current; current = current->next) {
    if (current->item == item) return true;
  }
  // Элемент не найден!
  return false;
}

//**************************************************************
// Определение класса ListGraph
//**************************************************************

class ListGraph : public Graph {
  // Данные функции преобразования нуждаются в деталях
  // представления L-графа
  friend ListGraph * convert(const SetGraph & srcGraph);
  friend ArcGraph * convert(const ListGraph & srcGraph);

  // Массив списков дуг
  List<int> *graph;

  // Количество вершин графа
  int vertexNumber;

public:

  // Конструктор создает массив пустых списков
  ListGraph(int n) : vertexNumber(n), graph(new List<int>[n]) {}

  // Деструктор уничтожает списки дуг
  ~ListGraph() { delete graph; }

  // Функция подсчета числа вершин просто выдает
  // ранее сохраненное значение
  int vertexCount() const { return vertexNumber; }

  // Основные методы работы с графом
  void addArc(int from, int to);
  bool hasArc(int from, int to) const;
};

#endif
