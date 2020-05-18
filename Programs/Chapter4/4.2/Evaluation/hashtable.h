/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 4. Символьные преобразования                      *
*          4.2. Вычисления по формулам                         *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : hashtable.h                                      *
*  Описание : Хеш-таблица объектов произвольного типа с ключом *
*             поиска типа "строка". Фактически в таблице       *
*             хранятся ссылки на хранимые объекты              *
***************************************************************/

#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <string>
#include <exception>

using namespace std;

class NullValueException : public exception {
  const char * reason;

public :
  NullValueException(const char * why = "Null value is not valid")
    : reason(why) {}
  const char * what() const throw() { return reason; }
};

//=============================================================
// Класс, представляющий хеш-таблицу пар (ключ, значение),
// причем ключом является строка, а значением может быть
// произвольный объект. В таблице хранятся не сами эти объекты,
// а ссылки на них.
//=============================================================
template <class Object>
class HashTable {

protected:

#ifndef P
#define P        557
#endif
#ifndef Q
#define Q        811
#endif
#ifndef LENGTH
#define LENGTH   1000
#endif

  //============================================================
  // Элемент списка, содержащий ключ и связанный с ним объект
  //============================================================
  struct ListElem {
    string key;        // ключ
    Object *obj;       // связанный объект
    ListElem *next;    // ссылка на следующий элемент

    // Простой конструктор для создания элементов списка
    ListElem(const string & k, Object *o, ListElem *n) {
      key = k;
      obj = o;
      next = n;
    }
  };

  // Массив списков, содержащих слова словаря
  ListElem * dict[LENGTH];

public:

  //============================================================
  // Конструктор
  //============================================================
  HashTable() { memset(dict, 0, sizeof(dict)); }

  //============================================================
  // Деструктор
  //============================================================
  virtual ~HashTable() { destroy(); }

  //============================================================
  // Функция расстановки, основанная на сложении кодов символов
  //============================================================
  static int hash(const string str);

  //============================================================
  // Функция добавления нового объекта по ключу. Если объект,
  // связанный с этим ключом, уже содержится в словаре,
  // то новый объект замещает собою старый, а старое значение
  // возвращается в качестве результата работы функции.
  //============================================================
  Object * add(const string key, Object * obj);

  //============================================================
  // Функция поиска объекта по ключу. Если ключ не найден,
  // то функция возвращает пустую ссылку
  //============================================================
  Object * find(const string key) const;

  //============================================================
  // Функция удаления объекта по заданному ключу.
  // Результат функции - указатель на удаляемый объект.
  // Если ключ не найден, то функция возвращает пустую ссылку
  //============================================================
  Object * remove(const string key);

protected :
  //============================================================
  // Эта функция полностью разрушает таблицу для работы
  // деструктора. Объекты, хранящиеся в таблице, также разрушаются.
  //============================================================
  void destroy();
};

template <class Object>
int HashTable<Object>::hash(const string str) {
  int sum = 0;
  for (int i = 0; str[i]; i++) {
    sum += str[i] + i;
  }
  return ((P * sum + Q) & 0x7FFF) % LENGTH;
}

template <class Object>
Object * HashTable<Object>::add(const string key, Object * obj) {
  if (key == "" || obj == NULL) {
    throw NullValueException();
  }

  int index = hash(key);            // Значение hash-функции
  ListElem *current = dict[index];  // Текущий элемент списка

  // Поиск ключа в словаре:
  while (current && key != current->key) {
    current = current->next;
  }

  Object * result = NULL;
  if (current) {                    // Ключ уже есть в словаре
    result = current->obj;
    current->obj = obj;
  } else {
    // Создаем новый элемент списка и добавляем в начало списка
    ListElem * newElem = new ListElem(key, obj, dict[index]);
    dict[index] = newElem;
  }
  return result;
}

template <class Object>
Object * HashTable<Object>::find(const string key) const {
  if (key == "") {
    throw NullValueException();
  }

  int index = hash(key);            // Значение hash-функции
  ListElem *current = dict[index];  // Текущий элемент списка

  // Поиск ключа в словаре:
  while (current && key != current->key) {
    current = current->next;
  }
  if (current == NULL) return NULL;  // Ключ не найден
  return current->obj;
}

template <class Object>
Object * HashTable<Object>::remove(const string key) {
  if (key == "") {
    throw NullValueException();
  }

  int index = hash(key);            // Значение hash-функции
  ListElem *current = dict[index];  // Текущий элемент списка
  ListElem *pred = NULL;            // Предыдущий элемент списка

  // Поиск ключа в словаре:
  while (current && key != current->key) {
    pred = current;
    current = current->next;
  }
  if (current == NULL) return NULL;  // Ключ не найден
  // Исключение элемента из списка:
  if (pred == NULL) {
    dict[index] = current->next;
  } else {
    pred->next = current->next;
  }
  // Возврат результата:
  Object * result = current->obj;
  delete current;
  return result;
}

template <class Object>
void HashTable<Object>::destroy() {
  for (int i = 0; i < LENGTH; i++) {
    ListElem * current = dict[i];
    ListElem * pred = NULL;
    while (current) {
      delete current->obj;
      pred = current;
      current = current->next;
      delete pred;
    }
    dict[i] = NULL;
  }
}

#endif
