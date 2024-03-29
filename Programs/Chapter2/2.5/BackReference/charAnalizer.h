/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.5. Прохождение деревьев                           *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : charAnalizer.h                                   *
*  Описание : Определение класса для построения дерева,        *
*             содержащего символы в узлах, из строкового       *
*             представления                                    *
***************************************************************/

#ifndef __CHAR_ANALIZER_H
#define __CHAR_ANALIZER_H

#include "tree.h"
#include <stdlib.h>

//**************************************************************
// Определение класса CharAnalizer
//**************************************************************

class CharAnalizer : public Tree<char>::Analizer {
  // Исходная строка, содержащая строковое представление дерева
  char * source;
  // Результат анализа строки - построенное дерево
  Tree<char>::Node * root;

public :

  // Конструктор получает строку и строит дерево с обратными 
  // ссылками, записывая его корневой узел в root.
  CharAnalizer(char * src) { root = scan(source = src); }

  // Функция parse на самом деле ничего не анализирует,
  // а просто выдает уже сформированный конструктором результат.
  Tree<char>::Node * parse() { return root; }

private :

  // Рекурсивная функция scan анализирует изображение дерева,
  // начиная с символа, на который указывает src, и продвигает
  // этот указатель на символ, следующий за изображением дерева.
  Tree<char>::Node *scan(char * & src);
};

// Строковое представление символьного дерева должно выглядеть
// следующим образом: (S son1 son2...), где S - символ, помещаемый в 
// корень дерева, son(i) - изображения сыновей (если они есть).
// Пустое дерево изображается в виде пустой строки
Tree<char>::Node * CharAnalizer::scan(char * & src) {
  // Непустое дерево должно начинаться с открывающей скобки
  if (src == NULL || *src == 0 || *src != '(') return NULL;
  // Продвигаем указатель на один символ
  src++;
  // Следующий символ (если он есть) помещается в корень
  if (*src == 0) return NULL;
  // Строим корневой узел и помещаем в него очередной символ
  Tree<char>::Node * root = new Tree<char>::Node(*src);
  src++;
  // Теперь строим поддеревья с помощью последовательных
  // рекурсивных вызовов scan и связываем их в список братьев.
  Tree<char>::Node * pred = NULL;
  Tree<char>::Node * next;
  while (next = scan(src)) {
    if (pred) {
      // присоединение очередного узла в качестве очередного "брата"
      pred->setBrother(next);
    } else {
      // присоединение очередного узла в качестве "старшего сына"
      root->son = next;
    }
    pred = next;
  }
  // устанавливаем обратную ссылку из "младшего сына" на "отца"
  if (pred) pred->brother = root;
  // Пропускаем следующий символ (если он есть) - это должна быть закр. скобка.
  if (*src == 0) return root;
  src++;
  // Возвращаем результат
  return root;
}

#endif

