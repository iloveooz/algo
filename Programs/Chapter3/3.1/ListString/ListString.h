/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 3. Обработка текстов                              *
*          3.1. Способы представления строк                    *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : ListString.h                                     *
*  Описание : Представление строки в виде списка элементов,    *
*             содержащих фрагменты строки                      *
***************************************************************/

#ifndef __LIST_STRING_H
#define __LIST_STRING_H

#include <stdlib.h>
#include <string.h>
#include <exception>
#include <iostream>

using namespace std;

class IndexException : public exception {
  const char * reason;

public:

  IndexException(const char * why) : exception(), reason(why) {}
  IndexException() : exception(), reason("Wrong index") {}
  const char * what() const throw() { return reason; }
};

class ListString {

  friend ostream & operator <<= (ostream & out, const ListString & src);

public :
  #define ITEM_SIZE 16        // максимальный размер элемента

protected :

  //-------------------------------------------------
  // Вспомогательные классы:
  // - StringItem представляет элемент строки,
  //   содержащий от 1 до 16 символов;
  // - SymbolPosition представляет адрес символа внутри 
  //   строки - пару из указателя на элемент и номера
  //   символа внутри элемента.
  //-------------------------------------------------

  struct StringItem {
    char symbols[ITEM_SIZE];  // массив символов
    StringItem *next;         // указатель на следующий элемент
    unsigned short size;      // количество символов

    //--------------------------------------------------
    // Конструктор для создания цепочки элементов строки
    // получает строку, режет ее на фрагменты длиной
    // ITEM_SIZE, и связывает их в список элементов
    //--------------------------------------------------
    StringItem(const char *src, StringItem *nextItem = NULL);
  };

  struct SymbolPosition {
    StringItem *item;      // Элемент строки
    unsigned short pos;    // Позиция внутри элемента строки

    // Простой конструктор
    SymbolPosition(StringItem *i, unsigned short int p) 
      : item(i), pos(p) {}
  };

  // Внутреннее представление строки

  StringItem *first;           // Указатель на первый элемент

public:
 
  //-------------------------------------------------------
  // Конструкторы строк
  //-------------------------------------------------------
  ListString() : first(NULL) {}

  ListString(const ListString & src) : first(NULL) {
    *this = src;
  }

  ListString(const char *s) : first (NULL) {
    if (s != NULL && *s != 0) {
      first = new StringItem(s);
    }
  }
 
  //-------------------------------------------------------
  // Деструктор
  //-------------------------------------------------------
  ~ListString() { destroy(); }

  //-------------------------------------------------------
  // Объявление основных операций над строками
  //-------------------------------------------------------
  
  char & operator [] (int index);
  char operator [] (int index) const;

  ListString & operator = (const ListString & src);
  ListString & operator = (const char * src);

  ListString substr(int begin, int end = -1) const;

  int length() const;

  ListString & operator += (const ListString & src);
  ListString & operator += (const char * src);
  ListString & operator += (char ch);

  ListString & insert (int index, const ListString & src);
  ListString & insert (int index, const char * src);

  operator char* () const;

protected:

  //--------------------------------------------------------------
  // Вспомогательные функции
  //--------------------------------------------------------------

  // освобождает память, занятую элементами строки
  void destroy();

  // ищет последний элемент в представлении строки
  StringItem * getLast() const;

  // ищет позицию символа строки с заданным индексом
  SymbolPosition findPos(int index) const;
};

//-------------------------------------------------------
// Это операция, выдающая в выходной символьный поток
// поэлементную структуру строки (длины элементов)
//-------------------------------------------------------

ostream & operator <<= (ostream & out, const ListString & src);

#endif
