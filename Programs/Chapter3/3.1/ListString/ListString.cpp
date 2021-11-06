/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.1. Способы представления строк                    *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListString.cpp                                   *
*  Описание : Представление строки в виде списка элементов,    *
*             содержащих фрагменты строки: реализация операций *
***************************************************************/

#include "ListString.h"

//--------------------------------------------------
// Конструктор для создания цепочки элементов строки
// получает строку, режет ее на фрагменты длиной
// ITEM_SIZE, и связывает их в список элементов
//--------------------------------------------------
ListString::StringItem::StringItem(const char *src, StringItem *nextItem) {
  // считаем, что строка содержит хотя бы один символ
  int len = strlen(src);
  if (len > ITEM_SIZE) {
    // Рекурсивный вызов конструктора:
    nextItem = new StringItem(src + ITEM_SIZE, nextItem);
  }
  // Реальная длина строки или ее начального сегмента
  size = (len < ITEM_SIZE ? len : ITEM_SIZE);
  // Сохранение символов
  strncpy(symbols, src, size);
  next = nextItem;
}

//-------------------------------------------------------------
// Функция освобождения памяти, занятой элементами строки,
// и обнуления строки
//-------------------------------------------------------------
void ListString::destroy() {
  StringItem * current = first, // текущий элемент списка
             * pred = NULL;     // предыдущий элемент списка
  // цикл по элементам списка
  while (current) {
    pred = current;
    current = current->next;
    delete pred;
  }
  // обнуление строки
  first = NULL;
}

//-------------------------------------------------------------
// Функция поиска последнего элемента в представлении строки
//-------------------------------------------------------------
ListString::StringItem * ListString::getLast() const {
  StringItem * current = first, // текущий элемент списка
             * pred = NULL;     // предыдущий элемент списка
  // цикл по элементам списка
  while (current) {
    pred = current;
    current = current->next;
    // Проверим, нельзя ли осуществить слияние элементов pred и current
    while (current && pred->size + current->size <= ITEM_SIZE) {
      // копирование символов
      strncpy(pred->symbols + pred->size, current->symbols, current->size);
      // коррекция элемента pred
      pred->size += current->size;
      pred->next = current->next;
      StringItem *toDelete = current;
      current = current->next;
      // Уничтожение лишнего элемента
      delete toDelete;
    }
  }
  // возврат результата
  return pred;
}

//-------------------------------------------------------------
// Функция поиска позиции символа строки с заданным индексом
//-------------------------------------------------------------
ListString::SymbolPosition ListString::findPos(int index) const {
  if (index < 0) {
    throw IndexException("String indexing with index < 0");
  }

  // количество символов, которые надо еще отсчитать:
  unsigned short curIndex = (unsigned short)index;

  // указатель на текущий элемент:
  StringItem * current = first;  

  // Цикл по элементам списка
  while (current && current->size <= curIndex) {
    curIndex -= current->size;
    current = current->next;
  }

  if (current == NULL) { // строка кончилась, а индекс еще не достигнут
    throw IndexException("String indexing with index greater than string length");
  }
  // Выдача результата:
  return SymbolPosition(current, curIndex);
}

//-------------------------------------------------------------
// Функция преобразования строки в стандартное представление Си
//-------------------------------------------------------------
ListString::operator char* () const {
  // Буфер для записи символов строки:
  char * res = new char[this->length() + 1];
  // Указатель текущего места для записи символов
  char * ptr = res;

  // Цикл по элементам строки
  for (StringItem * current = first; current; current = current->next) {
    // Запись в буфер символов из очередного элемента
    strncpy(ptr, current->symbols, current->size);
    ptr += current->size;
  }
  *ptr = 0;
  return res;
}

//-------------------------------------------------------------
// Функция вычисления длины строки
//-------------------------------------------------------------
int ListString::length() const {
  int length = 0;  // переменная для вычисления длины
  // Цикл по элементам строки
  for (StringItem * current = first; current; current = current->next) {
    length += current->size;
  }
  return length;
}

//-------------------------------------------------------------
// Операция индексации строки
//-------------------------------------------------------------
char & ListString::operator [] (int index) {
  // Вычисление позиции символа в строке с помощью функции findPos
  SymbolPosition sp = findPos(index);
  // выдача символа с использованием вычисленной позиции
  return sp.item->symbols[sp.pos];
}

//-------------------------------------------------------------
// Операция индексации строки
//-------------------------------------------------------------
char ListString::operator [] (int index) const {
  // Вычисление позиции символа в строке с помощью функции findPos
  SymbolPosition sp = findPos(index);
  // выдача символа с использованием вычисленной позиции
  return sp.item->symbols[sp.pos];
}

//-------------------------------------------------------------
// Операция присваивания с копированием строки
//-------------------------------------------------------------
ListString & ListString::operator = (const ListString & src) {
  // Сначала операция приведения к типу char* скопирует все
  // символы строки в символьный буфер, а потом оператор
  // присваивания построит новые элементы строки.
  destroy();
  return *this = (char*)src;
}

//-------------------------------------------------------------
// Операция присваивания с копированием строки
//-------------------------------------------------------------
ListString & ListString::operator = (const char * src) {
  destroy();
  if (src && src[0]) {
    first = new StringItem(src);
  }
  return *this;
}

//-------------------------------------------------------------
// Операция выделения подстроки с ее копированием
//-------------------------------------------------------------
ListString ListString::substr(int begin, int end) const {
  // Проверяем правильность задания аргументов
  int len = length();
  if (begin < 0 || begin > len) {
    throw IndexException("Wrong start index in substr");
  } else if (end > len || end < begin) {
    end = len;
  }

  // Цикл копирования символов строки в промежуточный буфер
  int leftSymbols = end - begin;

  // Сначала проверяем, надо ли вообще что-то копировать
  if (leftSymbols == 0) return ListString();

  // Находим начальную позицию для копирования и организуем буфер
  SymbolPosition startPos = findPos(begin);
  char * buffer = new char[leftSymbols+1];
  char * ptr = buffer;

  // Цикл продолжается, пока еще есть что копировать
  while (leftSymbols) {
    // Вычисляем, сколько символов можно взять из текущего элемента
    int lenToCopy = startPos.item->size - startPos.pos;
    if (leftSymbols < lenToCopy) lenToCopy = leftSymbols;

    // Копируем символы
    strncpy(ptr, startPos.item->symbols + startPos.pos, lenToCopy);
    ptr += lenToCopy;
    leftSymbols -= lenToCopy;

    // Продвигаемся к следующему элементу
    startPos.item = startPos.item->next;
    startPos.pos = 0;
  }
  // Записываем в буфер маркер конца строки
  *ptr = 0;

  // Создаем новую строку из символов, записанных в буфер
  ListString result(buffer);
  // Уничтожаем буфер
  delete buffer;
  // Возвращаем результат
  return result;
}

//-------------------------------------------------------------
// Добавление символа в конец строки
//-------------------------------------------------------------
ListString & ListString::operator += (char ch) {
  StringItem * last = getLast();  // последний элемент списка
  if (last == NULL) {
    // Новый элемент становится первым и единственным в списке
    first = new StringItem(&ch);
  } else if (last->size < ITEM_SIZE) {
    // Символ просто добавляется в последний элемент списка
    last->symbols[last->size++] = ch;
  } else {
    // Новый элемент присоединяется к концу списка
    last->next = new StringItem(&ch);
  }
  return *this;
}

//-------------------------------------------------------------
// Добавление нового списка элементов в конец строки
// ВНИМАНИЕ: элементы исходной строки не копируются!
//-------------------------------------------------------------
ListString & ListString::operator += (const ListString & src) {
  StringItem * last = getLast();  // последний элемент списка
  if (last == NULL) {
    // Копируется указатель на первый элемент списка
    first = src.first;
  } else {
    // Новые элементы присоединяются в конец списка
    last->next = src.first;
  }
  return *this;
}

//-------------------------------------------------------------
// Добавление новых символов в конец строки
//-------------------------------------------------------------
ListString & ListString::operator += (const char * src) {
  return *this += *(new ListString(src));
}

//-------------------------------------------------------------
// Вставка элементов строки внутрь данной
//-------------------------------------------------------------
ListString & ListString::insert (int index, const ListString & src) {
  if (index < 0) {
    throw IndexException("insert: negative insertion index");
  }
  // Определяем позицию элемента с заданным индексом
  // примерно так же, как в операции findPos
  StringItem * current = first;  // указатель на текущий элемент
  StringItem * pred = NULL;      // указатель на предыдущий элемент
  int curIndex = index;          // переменная для отсчета символов
  while (current && current->size <= curIndex) {
    curIndex -= current->size;
    pred = current;
    current = current->next;
  }
  // проверка правильности задания индекса
  if (current == NULL && curIndex != 0) {
    throw IndexException("insert: insertion index is too big");
  }
  if (src.first == NULL) {
    // Собственно, и вставлять-то было нечего!
    // Но правильность индекса надо было проверить все равно
    return * this;
  }
  // Последний элемент вставляемого фрагмента:
  StringItem * lastInSource = src.getLast();

  if (curIndex > 0) {
    // Найденный элемент надо разрезать на две части.
    // Формируем вторую из этих частей
    char * buffer = new char[current->size - curIndex + 1];
    strncpy(buffer, current->symbols + curIndex, current->size - curIndex);
    buffer[current->size - curIndex] = 0;
    StringItem * newItem = new StringItem(buffer, current->next);
    // Теперь формируем длину первой части
    current->size = (unsigned short)curIndex;
    // Вставляем новый участок списка между этими двумя частями
    current->next = newItem;
    pred = current;
    current = newItem;
  }
  // Окончательное формирование указателей в списке:
  if (pred == NULL) {
    first = src.first;
  } else {
    pred->next = src.first;
  }
  lastInSource->next = current;
  return *this;
}

//-------------------------------------------------------------
// Вставка строки в стандартном представлении внутрь данной
//-------------------------------------------------------------
ListString & ListString::insert (int index, const char * src) {
  return insert(index, *(new ListString(src)));
}

//-------------------------------------------------------
// Это операция, выдающая в выходной символьный поток
// поэлементную структуру строки (длины элементов)
//-------------------------------------------------------

ostream & operator <<= (ostream & out, const ListString & src) {
  ListString::StringItem * current = src.first;
  out << '[';
  while (current) {
    out << current->size;
    if (current = current->next) {
      out << ", ";
    }
  }
  return out << ']';
}
