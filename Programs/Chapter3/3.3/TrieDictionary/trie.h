/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.3. Словари, представленные списками и деревьями   *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : trie.h                                           *
*  Описание : Словарь организованый в виде "бора"              *
***************************************************************/

#ifndef __TRIE_H
#define __TRIE_H

#include <string>
#include "iterator.h"
#include "pair.h"

//==============================================================
// Класс представляет собой реализацию бора
//==============================================================
template <class Object>
class Trie {
private :
  //============================================================
  // Класс TrieNode является базовым классом для двух основных
  // типов узлов бора: узел-буква и узел-терминал
  //============================================================
  struct TrieNode {
    TrieNode *brother;  // указатель на следующий узел того же уровня

    // Конструктор узла:
    TrieNode(TrieNode *brother = NULL) : brother(brother) {}

    // Функция проверки типа узла
    virtual bool terminal() = 0;
  };

  //============================================================
  // Два класса LetterNode и TerminalNode представляют два
  // типа узлов бора: узел-буква и узел-терминал соответственно
  //============================================================
  struct LetterNode : TrieNode {
    char letter;       // очередная буква
    TrieNode *son;     // указатель на следующий уровень

    // Конструктор узла:
    LetterNode(char letter,
               TrieNode *son = NULL,
               TrieNode *brother = NULL)
      : TrieNode(brother), letter(letter), son(son) {}

    bool terminal() { return false; }
  };

  struct TerminalNode : TrieNode {
    Object obj;       // связанный со словом объект

    // Конструктор узла:
    TerminalNode(const Object & obj,
                 TrieNode *brother = NULL)
      : TrieNode(brother), obj(obj) {}

    bool terminal() { return true; }
  };

  class PNodeStack {
    struct StackElement {
      LetterNode * item;
      StackElement * next;
      StackElement(LetterNode * item, StackElement * next = NULL)
        : item(item), next(next) {}
    };

    StackElement * top;

  public :

    PNodeStack() : top(NULL) {}
    void push(LetterNode * node) { top = new StackElement(node, top); }
    void pop() {
      if (top) {
        StackElement * toDelete = top;
        top = top->next;
        delete toDelete;
      }
    }
    bool empty() { return top == NULL; }
    LetterNode * operator *() { return (top ? top->item : NULL); }
  };

  class TrieIterator : public Iterator<Pair<Object> > {
    PNodeStack stack;
    string currentKey;
    TrieNode * currentNode;

  public :
    TrieIterator(TrieNode *root) : currentNode(root) { downToTerminal(); }
    bool hasMoreElements() const { return currentNode != NULL; }
    Iterator<Pair<Object> > & operator ++();
    const Pair<Object> & operator *() const { 
      return *new Pair<Object>(currentKey, ((TerminalNode*)currentNode)->obj);
    }
    Pair<Object> & operator *() {
      return *new Pair<Object>(currentKey, ((TerminalNode*)currentNode)->obj);
    }
  private :
    void downToTerminal();
  };

  TrieNode *root;      // корень бора

public :

  // Конструктор
  Trie() { root = NULL; }

  // Функция добавления слова. Результат - значение, которое было
  // связано с этим словом раньше, или NULL, если такового не было.
  Object * add(string key, const Object & value);

  // Функция поиска связанного объекта по ключу
  Object * find(string key);

  // Итератор пар (ключ, значение)
  Iterator<Pair<Object> > * iterator() { return new TrieIterator(root); }

  // Печать структуры и содержимого
  void print() { print("", root); }

private :
  void print(string key, TrieNode * start);
};

template <class Object>
void Trie<Object>::TrieIterator::downToTerminal() {
  if (currentNode == NULL) return;
  while (!currentNode->terminal()) {
    LetterNode * currentLetter = (LetterNode*) currentNode;
    currentKey += currentLetter->letter;
    stack.push(currentLetter);
    currentNode = currentLetter->son;
  }
}

template <class Object>
Iterator<Pair<Object> > & Trie<Object>::TrieIterator::operator ++() {
  if (currentNode) {
    if ((currentNode = currentNode->brother) == NULL) {
      while (!stack.empty()) {
        LetterNode * stackTop = *stack;
        currentKey = currentKey.substr(0, currentKey.length()-1);
        currentNode = stackTop->brother;
        stack.pop();
        if (currentNode) break;
      }
    }
    downToTerminal();
  }
  return *this;
}

template <class Object>
Object * Trie<Object>::add(string key, const Object & value) {
  TrieNode ** current = &root;
  for (int i = 0; i < key.length(); i++) {
    char c = key[i];
    // Производим вставку узла, содержащего очередную букву,
    // в упорядоченный список узлов следующего уровня
    while (*current && ((*current)->terminal() || c > ((LetterNode*)(*current))->letter)) {
      current = &(*current)->brother;
    }
    if (*current == NULL || c < ((LetterNode*)(*current))->letter) {
      // Такой буквы еще не было, вставляем новый узел
      LetterNode * newLetter = new LetterNode(c, NULL, *current);
      *current = newLetter;
    }
    // Переходим на следующий уровень
    current = &((LetterNode*)(*current))->son;
  }
  Object * result = NULL;
  if (*current && (*current)->terminal()) {
    // Ранее с этим словом уже был связан некоторый объект
    result = &((TerminalNode*)(*current))->obj;
    ((TerminalNode*)(*current))->obj = value;
  } else {
    TerminalNode * newNode = new TerminalNode(value, *current);
    *current = newNode;
  }
  return result;
}

template <class Object>
Object * Trie<Object>::find(string key) {
  TrieNode *curNode = root;     // текущий исследуемый узел бора

  // Цикл поиска по очередной букве
  for (int i = 0; i < key.length(); i++) {
    // Ищем очередную букву в текущем уровне бора
    while (curNode && (curNode->terminal() || 
           key[i] > ((LetterNode*)curNode)->letter)) {
      curNode = curNode->brother;
    }
    if (curNode == NULL || key[i] != ((LetterNode*)curNode)->letter) {
      return NULL;      // буква не найдена
    }
    curNode = ((LetterNode*)curNode)->son; // переход на следующий уровень
  }

  // Все буквы ключа найдены. Теперь надо выдать связанный
  // со словом объект, если он существует
  return (curNode && curNode->terminal() ? &((TerminalNode*)curNode)->obj : NULL);
}

template <class Object>
void Trie<Object>::print(string prefix, TrieNode * start) {
  TrieNode * current = start;
  while (current) {
    cout << prefix;
    if (current->terminal()) {
      cout << '(' << ((TerminalNode*)current)->obj << ")\n";
    } else {
      cout << ((LetterNode*)current)->letter << endl;
      print(prefix + "  ", ((LetterNode*)current)->son);
    }
    current = current->brother;
  }
}

#endif
