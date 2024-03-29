/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.2. Сортировка и поиск в массивах                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : digitsort.h                                      *
*  Описание : Функции сортировки элементов массива методом     *
*             цифровой сортировки                              *
***************************************************************/

#ifndef __DIGIT_SORT_H
#define __DIGIT_SORT_H

//==============================================================
// Класс Elem представляет элемент списка ключей,
// формируемого для выполнения цифровой сортировки.
//==============================================================
template <class Key>
struct Elem {
  Key value;     // Сам элемент
  int next;      // Индекс следующего элемента в пуле памяти
  
  // Конструкторы:
  Elem() { next = -1; }     // Остутствие следующего элемента 
                            // отмечается значением -1 в поле next
  Elem(const Elem<Key> & src) : value(src.value), next(src.next)
  {}

  Elem(const Key & val, int n = -1) : value(val), next(n) {}

  // Оператор присваивания:
  Elem & operator = (const Elem<Key> & src) {
    value = src.value; next = src.next;
    return *this;
  }
};

//==============================================================
// Класс ListBuffer представляет буферный пул памяти для 
// организации в нем списков ключей (для цифровой сортировки).
//==============================================================
template <class Key>
class ListBuffer {
  Elem<Key> * buffer;   // Указатель на буфер
  int size;             // Размер буфера
  int freePtr;          // Указатель первого свободного элемента

public :

  // Конструктор:
  ListBuffer(int n) {
    buffer = new Elem<Key>[size = n];
    clear();
  }

  // Деструктор:
  ~ListBuffer() { delete [] buffer; }

  // Очистка памяти формирует список свободных
  // элементов из всех элементов буфера.
  void clear() {
    freePtr = 0;
  }

  // Операция доступа к элементам
  Elem<Key> & operator [] (int i) { return buffer[i]; }

  // Операция выделения элемента свободной части буфера
  int get() {
    return freePtr++;
  }
};

//==============================================================
// Класс KeyList представляет список ключей, хранящийся в
// буферном пуле памяти, который передается конструктору списка.
//==============================================================
template <class Key>
class KeyList {
  ListBuffer<Key> * buffer;  // Пул памяти
  int first;                 // Указатель на первый элемент списка
  int last;                  // Указатель на послений элемент списка

public :

  // Конструктор получает в качестве аргумента указатель на пул памяти
  KeyList(ListBuffer<Key> * buf) : buffer(buf), first(-1), last(-1) {}

  // Операция добавления нового элемента в конец списка
  void addKey(const Key & key) {
    // Запрашиваем свободный элемент у пула памяти buffer
    int nextElem = buffer->get();
    // Записываем новое значение в этот элемент
    (*buffer)[nextElem] = Elem<Key>(key);
    // Присоединяем новый элемент к уже имеющемуся списку
    if (first == -1) {
      first = nextElem;
    } else {
      (*buffer)[last].next = nextElem;
    }
    last = nextElem;
  }

  // Операция toArray переносит все элементы списка во фрагмент
  // массива array, начиная с элемента с индексом from.
  // В качестве результата функция выдает индекс первого элемента
  // массива, следующего за перенесенным фрагментом
  int toArray(Key * array, int from) {
    // Организуем просмотр элементов с помощью указателя ptr.
    int ptr = first;
    while (ptr != -1) {
      array[from++] = (*buffer)[ptr].value;
      ptr = (*buffer)[ptr].next;
    }
    return from;
  }

  // Функция очистки списка просто "заземляет" указатели
  // на первый и последний элементы списка.
  void clear() { first = last = -1; }
};

//-------------------------------------------------------------
// Шаблон digitSort задает функцию сортировки элементов
// массива методом цифровой сортировки.
//   - Key - класс, задающий тип элементов массива;
//   - array - упорядочиваемый массив;
//   - low, high - индексы, задающие диапазон сортировки;
//-------------------------------------------------------------

template <class Key>
void digitSort(Key * array, int low, int high) {
  // Предполагается, что в начале работы low <= high
  // В результате сортировки получается упорядоченный фрагмент
  // массива в диапазоне от low до high
  int n = high - low + 1;               // Длина массива
  int listNumber = array[low].power();  // Количество списков ключей
  int passes = array[low].length();     // Количество проходов по массиву
  ListBuffer<Key> buffer(n);            // Буфер для списков ключей

  // Организуем массив списков ключей с использованием буфера buffer:
  KeyList<Key> * lists = new KeyList<Key>[listNumber](&buffer);

  // Цикл по проходам по массиву (digit - номер "цифры"):
  for (int digit = passes-1; digit >= 0; digit--) {
    // Помещение ключей из массива в соответствующие списки
    for (int i = low; i <= high; i++) {
      lists[array[i][digit]].addKey(array[i]);
    }
    // Обратное слияние списков в массив и очищение списков
    int start = low;
    for (int i = 0; i < listNumber; i++) {
      start = lists[i].toArray(array, start);
      lists[i].clear();
    }
    // Очистка буфера
    buffer.clear();
  }
}

#endif
