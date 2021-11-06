/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 6. Алгоритмы обработки сетевой информации         *
*          6.1. Обходы и поиск в графах                        *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : circularlist.h                                   *
*  Описание : Описание и реализация кольцевого списка          *
***************************************************************/

#ifndef __CIRCULAR_LIST
#define __CIRCULAR_LIST

#include <stdlib.h>
#include <exception>

//==============================================================
// Класс, определяющий исключительную ситуацию EmptyException,
// которая может возникать при попытках доступа к элементам пустого списка.
//==============================================================

class EmptyException : public exception {
  char * reason;    // Причина прерывания
public:
  EmptyException() : reason("Accessing to element of an empty list") {}
  const char * what() const throw() { return reason; }
};

//==============================================================
// Шаблон классов для определения кольцевого списка.
// Единственное отличие от простых линейных списков состоит в том,
// что последний элемент списка содержит указатель на первый элемент.
//==============================================================

template <class T>
class CircularList {

  //============================================================
  // Элемент списка содержит собственно значение и указатель на 
  // следующий элемент (последний элемент содержит указатель на первый).
  //============================================================
  struct ListItem {
    T item;             // элемент списка
    ListItem *next;     // следующий элемент

    ListItem(const T & item, ListItem *next = NULL) {
      ListItem::item = item;
      ListItem::next = next;
    }
  };

  // Список представлен указателем на последний элемент,
  // содержащий указатель на первый элемент списка.
  // Этот указатель содержит NULL, если список пуст.
  ListItem *last;

public :

  // Конструктор "по умолчанию" создает пустой список.
  CircularList() { last = NULL; }

  // Конструктор копирования реализован с помощью оператора присваивания.
  CircularList(const CircularList<T> & src) { *this = src; }

  // Деструктор должен освобождать паямть, занятую элементами списка.
  virtual ~CircularList() { destroy(); }

  // Новые элементы можно вставлять в начало или в конец списка.
  void insertHead(const T & item);
  void insertTail(const T & item);

  // Первый элемент можно удалять.
  void removeHead();

  // Функция 'empty' проверяет, содержит ли список хоть один элемент. 
  bool empty() const { return last == NULL; }

  // Функции "доступа" реализуют доступ для чтения и/или записи
  // к первому и последнему элементам списка.
  T & head();
  const T & head() const;
  T & tail();
  const T & tail() const;

  // Оператор присваивания
  CircularList<T> & operator = (const CircularList<T> & src);

  // Функция destroy освобождает память, занятую элементами списка
  // и делает список пустым.
  void destroy();
};

// Вставка нового элемента в начало списка
template <class T>
void CircularList<T>::insertHead(const T & item) {
  if (last == NULL) {
    // Новый элемент будет одновременно первым и последним
    last = new ListItem(item);
    last->next = last;
  } else {
    // Новый элемент вставляется за последним
    last->next = new ListItem(item, last->next);
  }
}

// Вставка нового элемента в конец списка
template <class T>
void CircularList<T>::insertTail(const T & item) {
  // Сначала вставляем элемент в начало списка.
  insertHead(item);
  // Чтобы первый элемент стал последним в кольцевом списке
  // достаточно "сдвинуться" вперед на один шаг
  last = last->next;
}

// Удаление элемента из начала списка. Память, занятая элементом, освобождается.
template <class T>
void CircularList<T>::removeHead() {
  if (last == NULL) throw EmptyException();
  if (last->next == last) {
    // удаляется единственный элемент
    delete last;
    last = NULL;
  } else {
    ListItem * itemToDelete = last->next;
    last->next = last->next->next;
    delete itemToDelete;
  }
}

// Функции доступа к началу списка.
template <class T>
T & CircularList<T>::head() {
  if (last == NULL) throw EmptyException();
  return last->next->item;
}

template <class T>
const T & CircularList<T>::head() const {
  if (last == NULL) throw EmptyException();
  return last->next->item;
}

// Функции доступа к концу списка.
template <class T>
T & CircularList<T>::tail() {
  if (last == NULL) throw EmptyException();
  return last->item;
}

template <class T>
const T & CircularList<T>::tail() const {
  if (last == NULL) throw EmptyException();
  return last->item;
}

// Оператор присваивания
template <class T>
CircularList<T> & CircularList<T>::operator = (const CircularList<T> & src) {
  // Если какие-то элементы уже были в списке, то они уничтожаются.
  destroy();
  // Поэлементное копирование и построение нового списка.
  if (!src.empty()) {
    ListItem * current = src.last->next; // First element
    do {
      insertTail(current->item);
      if (current == src.last) break;    // it was the last element!
      current = current->next;
    } while (true);
  }
  return *this;
}

// Функция destroy освобождает память, занятую элементами списка
// с помощью последовательных вызовов функции removeHead.
template <class T>
void CircularList<T>::destroy() {
  while (last) removeHead();
}

#endif
