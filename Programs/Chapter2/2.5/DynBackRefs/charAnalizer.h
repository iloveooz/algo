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
  Tree<char>::Node *root;

public :

  // Конструктор получает строку и строит дерево, 
  // записывая его корнеыой узел в root.
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

// Строкове представление символьного дерева должно выглядеть
// следующим образом: (S L R), где S - символ, помещаемый в 
// корень дерева, L - левое поддерево корня, R - правое поддерево.
// Пустое дерево (или поддерево) изображается в виде ()
Tree<char>::Node * CharAnalizer::scan(char * & src) {
  // Дерево должно начинаться со скобки
  if (src == NULL || *src == 0 || *src != '(') return NULL;
  // Продвигаем указатель на один символ
  src++;
  // Проверяем: если далее следует закр. скобка - то это пустое дерево,
  // иначе - следующий символ помещается в корень
  if (*src == 0) return NULL;
  if (*src == ')') { src++; return NULL; }
  // Дерево не пустое - строим корневой узел и помещаем в него очередной символ
  Tree<char>::Node * root = new Tree<char>::Node(*src);
  src++;
  // Теперь строим поддеревья с помощью последовательных рекурсивных вызовов scan.
  root->left = scan(src);
  root->right = scan(src);
  // Пропускаем следующий символ (если он есть) - это должна быть закр. скобка.
  if (*src == 0) return root;
  src++;
  // Возвращаем результат
  return root;
}

#endif

