/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.2. Распределение памяти блоками постоянной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : treedictionary.cpp                               *
*  Описание : Реализация простого словаря на базе бинарного    *
*             дерева поиска с хранением элементов в системе    *
*             распределения памяти с блоками постоянной длины  *
***************************************************************/

#include "treedictionary.h"
#include "printer.h"

// Функция добавления нового слова в словарь просто обращается
// к рекурсивному варманту функции с тем же именем
void TreeDictionary::addWord(string w) {
  addWord(w, &root);
}

// Внутренний итератор слов в порядке возрастания основан на
// левостороннем обходе с помощью рекурсивной функции traverse
void TreeDictionary::intIterator(Actor & actor) {
  traverse(root, actor);
}

// Рекурсивная функция добавления нового слова в словарь
void TreeDictionary::addWord(const string & w, TreeItem ** root) {
  if (*root == NULL) {
    // Достигнут лист дерева. Новый узел создается в памяти,
    // выделяемой системой управления памяти memoryManagement
    TreeItem *item = new (memoryManagement->get()) TreeItem(w);
    *root = item;
  } else if (w < (*root)->word) {
    // Слово добавляется в левое поддерево
    addWord(w, &(*root)->left);
  } else {
    // Слово добавляется в правое поддерево
    addWord(w, &(*root)->right);
  }
}

// Рекурсивная функция левостороннего обхода дерева
void TreeDictionary::traverse(TreeDictionary::TreeItem * root, Actor & actor) {
  if (root) {
    traverse(root->left, actor);  // обход левого поддерева
    actor.act(root->word);        // обход корня
    traverse(root->right, actor); // обход правого поддерева
  }
}

// Функция вывода словаря в выходной поток обращается к итератору узлов дерева
ostream & operator << (ostream & out, TreeDictionary & dict) {
  Printer p(& out);    // Действие, выполняемое во время итерации
  dict.intIterator(p); // Вызов итератора
  return out;
}
