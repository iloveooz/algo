/***************************************************************
*  ��������� � ��������� ��������� ������:                     *
*  ��������-��������������� ������ � ���������� �� C++         *
*      ����� 3. ��������� �������                              *
*          3.3. �������, �������������� �������� � ���������   *
*                                                              *
*  �����    : �.���������                                      *
*  ����     : trie.h                                           *
*  �������� : ������� ������������� � ���� "����"              *
***************************************************************/

#ifndef __TRIE_H
#define __TRIE_H

#include <string>
#include "iterator.h"
#include "pair.h"

//==============================================================
// ����� ������������ ����� ���������� ����
//==============================================================
template <class Object>
class Trie {
private :
  //============================================================
  // ����� TrieNode �������� ������� ������� ��� ���� ��������
  // ����� ����� ����: ����-����� � ����-��������
  //============================================================
  struct TrieNode {
    TrieNode *brother;  // ��������� �� ��������� ���� ���� �� ������

    // ����������� ����:
    TrieNode(TrieNode *brother = NULL) : brother(brother) {}

    // ������� �������� ���� ����
    virtual bool terminal() = 0;
  };

  //============================================================
  // ��� ������ LetterNode � TerminalNode ������������ ���
  // ���� ����� ����: ����-����� � ����-�������� ��������������
  //============================================================
  struct LetterNode : TrieNode {
    char letter;       // ��������� �����
    TrieNode *son;     // ��������� �� ��������� �������

    // ����������� ����:
    LetterNode(char letter,
               TrieNode *son = NULL,
               TrieNode *brother = NULL)
      : TrieNode(brother), letter(letter), son(son) {}

    bool terminal() { return false; }
  };

  struct TerminalNode : TrieNode {
    Object obj;       // ��������� �� ������ ������

    // ����������� ����:
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

  TrieNode *root;      // ������ ����

public :

  // �����������
  Trie() { root = NULL; }

  // ������� ���������� �����. ��������� - ��������, ������� ����
  // ������� � ���� ������ ������, ��� NULL, ���� �������� �� ����.
  Object * add(string key, const Object & value);

  // ������� ������ ���������� ������� �� �����
  Object * find(string key);

  // �������� ��� (����, ��������)
  Iterator<Pair<Object> > * iterator() { return new TrieIterator(root); }

  // ������ ��������� � �����������
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
    // ���������� ������� ����, ����������� ��������� �����,
    // � ������������� ������ ����� ���������� ������
    while (*current && ((*current)->terminal() || c > ((LetterNode*)(*current))->letter)) {
      current = &(*current)->brother;
    }
    if (*current == NULL || c < ((LetterNode*)(*current))->letter) {
      // ����� ����� ��� �� ����, ��������� ����� ����
      LetterNode * newLetter = new LetterNode(c, NULL, *current);
      *current = newLetter;
    }
    // ��������� �� ��������� �������
    current = &((LetterNode*)(*current))->son;
  }
  Object * result = NULL;
  if (*current && (*current)->terminal()) {
    // ����� � ���� ������ ��� ��� ������ ��������� ������
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
  TrieNode *curNode = root;     // ������� ����������� ���� ����

  // ���� ������ �� ��������� �����
  for (int i = 0; i < key.length(); i++) {
    // ���� ��������� ����� � ������� ������ ����
    while (curNode && (curNode->terminal() || 
           key[i] > ((LetterNode*)curNode)->letter)) {
      curNode = curNode->brother;
    }
    if (curNode == NULL || key[i] != ((LetterNode*)curNode)->letter) {
      return NULL;      // ����� �� �������
    }
    curNode = ((LetterNode*)curNode)->son; // ������� �� ��������� �������
  }

  // ��� ����� ����� �������. ������ ���� ������ ���������
  // �� ������ ������, ���� �� ����������
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
