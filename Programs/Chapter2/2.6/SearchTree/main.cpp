/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.6. Бинарные деревья поиска                        *
*                                                              *
*  Автор    : A.Koubenski                                      *
*  Файл     : main.cpp                                         *
*  Описание : Функция проверки работы функции поиска в дереве  *
*             по ключу.                                        *
***************************************************************/

#include "tree.h"
#include <iostream>
#include "iterator.h"
#include "words.h"

using namespace std;

// Функция поиска целого ключа в дереве поиска с целыми ключами
void binSearch(Tree<int> & t, int key) {
  int * keyFound = t.search(key);
  cout << "Key " << key
       << (keyFound ? " found successfully" : " not found")
       << " in the tree" << endl;
}

// Функция вывода слов текста в выходной поток
// в лексикографическом (алфавитном) порядке.
void sortWords(char * source, ostream & out) {
  Tree<Word> words;
  char * delimeters = ",.?!;:-\'\" \t\n\r\f";
  for (char * nextToken = strtok(source, delimeters);
       nextToken;
       nextToken = strtok(NULL, delimeters)) {
    words.insertLeaf(Word(nextToken));
  }
  out << words << endl;
}

int main() {
  // Строим дерево из чисел
  Tree<int> t;
  t.insertLeaf(10);
  t.insertLeaf(3);
  t.insertLeaf(20);
  t.insertLeaf(15);
  t.insertLeaf(30);
  t.insertLeaf(2);
  t.insertLeaf(5);
  t.insertLeaf(32);
  t.insertLeaf(22);
  // Вывод узлов дерева в выходной поток в порядке левостороннего обхода
  cout << t << endl;

  // Поиск в дереве по ключу
  binSearch(t, 15);    // поиск должен быть успешным
  binSearch(t, 23);    // поиск должен быть неудачным

  // Добавляем в корень дерева новый элемент 17...
  t.insertLeaf(17);
  // ...и проверяем, что ничего не потеряли
  cout << t << endl;

  // Теперь удаляем узлы сначала из листа...
  t.remove(22);
  // ...потом из узла с единственным поддеревом...
  t.remove(20);
  // ...и, наконец, из корня
  t.remove(17);

  // Проверяем, что получилось
  cout << t << endl;

  sortWords("Jackdaws love my big sphinx of quartz. "
            "A quick brown fox jumps over the lazy dog", cout);

  return 0;
}
