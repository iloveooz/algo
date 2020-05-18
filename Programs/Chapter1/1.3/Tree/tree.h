/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 1. Способы представления структур данных          *
*          1.3. Деревья                                        *
*                                                              *
*  Автор    : A.Кубенский                                      *
*  Файл     : tree.h                                           *
*  Описание : Определение шаблона классов для представления    *
*             деревьев                                         *
***************************************************************/

#ifndef __TREE_H
#define __TREE_H

//**************************************************************
// Tree class definition
//**************************************************************

template <class T>
class Tree {
  // Описание структуры узла со ссылками на сына и брата
  struct Node {
    T item;         // значение, содержащееся в узле
    Node *son;      // указатель на сына
    Node *brother;  // указатель на брата

    // Конструктор узла
    Node(T i, Node *s = NULL, Node *b = NULL) {
      item = i; son = s; brother = b;
    }
  };

  // Дерево реализовано в виде указателя на корневой узел.
  Node *root;

public :

  // Конструктор "по умолчанию" создает пустое дерево
  Tree() { root = NULL; }

  // Деструктор должен освободить память, занятую узлами дерева
  ~Tree() { deleteSubtree(root); }

  // Вычисление высоты
  int height() { return height(root); }

  // Функция для вычисления количества узлов,
  // находящихся в дереве на заданном уровне
  int nodesOnLevel(int level) { return nodesOnLevel(root, level); }

  // Функция для добавления узлов в дерево - 
  // используется только в тестовых целях.
  void add(const T &elem) { add(root, elem); }

private :

  //-----------------------------------------------------------
  // Следующие рекурсивные функции представляют собой 
  // рекурсивные тела основных интерфейсных методов
  //-----------------------------------------------------------

  // Рекурсивная функция для добавления узлов
  void add(Node *&node, const T &elem);

  // Рекурсивная функция для освобождения памяти
  void deleteSubtree(Node *node);

  // Рекурсивная функция вычисления высоты дерева
  int height(Node *node);

  // Рекурсивная функция вычисления количества узлов на заданном уровне
  int nodesOnLevel(Node *node, int level);
}; // конец класса Tree

// Тела методов класса

// Рекурсивная функция для освобождения памяти
template <class T>
void Tree<T>::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->son);
    deleteSubtree(node->brother);
    delete node;
  }
}

// Рекурсивная функция вычисления высоты дерева
template <class T>
int Tree<T>::height(Node *node) {
  if (node == NULL) return 0;
  int max = 0;
  for (Node *current = node->son; current; current = current->brother) {
    int curHeight = height(current);
    if (curHeight > max) max = curHeight;
  }
  return max + 1;
}

// Рекурсивная функция вычисления количества узлов на заданном уровне
template <class T>
int Tree<T>::nodesOnLevel(Node *node, int level) {
  if (node == NULL) return 0;     // Дерево пусто - узлов нет
  if (level <= 0) return 0;       // Нет такого уровня!
  // В противном случае проверяем потомков и братьев данного узла
  return nodesOnLevel(node->son, level-1) +   // вычисление для потомков первого узла
         (level == 1) +                       // сам узел добавляется к сумме только если level==1
         nodesOnLevel(node->brother, level);  // вычисление для следующих братьев
}

// Рекурсивная функция для добавления узлов
template <class T>
void Tree<T>::add(Node *&node, const T &item) {
  if (node == NULL) {
    // Узла по этой ссылке нет - создаем новый узел и 
    // присоединяем его к дереву в указанном месте.
    node = new Node(item);
  } else if (item < node->item) {
    // добавляем узел в самое левое поддерево
    add(node->son, item);
  } else {
    // узел добавляется куда-то к братьям заданного узла
    add(node->brother, item);
  }
}

#endif

