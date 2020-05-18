/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.1. Еще о представлении множеств                   *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : intset.h                                      *
*  Описание    : Описание абстрактного множества целых         *
***************************************************************/

#ifndef __INTSET_H
#define __INTSET_H

#include "iterator.h"
#include "smartptr.h"

class IntSet {
protected :
  //-----------------------------------------------------------
  //  Внутренний класс IntSetIterator реализует итератор
  //  элементов множества с помощью функции contains.
  //-----------------------------------------------------------
  class IntSetIterator : public Iterator<int> {
    int currentElement;         // Текущий проверяемый элемент
    const IntSet * currentSet;  // Итерируемое множество

  public :
    // Конструктор
    IntSetIterator(const IntSet * set)
      : currentElement(0), currentSet(set) {}

    // Функция hasMoreElements всегда возвращает true, так как
    // множество, вообще говоря, предполагается бесконечным
    bool hasMoreElements() const { return true; }

    // Оператор * возвращает текущий элемент множества,
    // если он есть. Если в множестве на самом деле нет больше
    // элементов, то эта функция может зациклиться.
    int operator *() {
      findNext();    // Зацикливается, если элементов больше нет
      return currentElement;
    }

    // Оператор ++ осуществляет переход к следующему элементу,
    // если он есть. Если в множестве на самом деле нет больше
    // элементов, то эта функция может зациклиться
    Iterator<int> & operator ++() {
      findNext();    // Зацикливается, если элементов больше нет
      currentElement++;
      return *this;
    }

  private :
    // Функция пробует определить текущий элемент множества
    void findNext();
  };

public :
  // Виртуальный деструктор требуется описать для того,
  // чтобы правильно работали деструкторы всех наследников
  // при уничтожении объектов, представляющих множества
  virtual ~IntSet() {}

  // Операция contains - характеристическая функция множества.
  // Она выдает значение true, если элемент n принадлежит
  // множеству, и false в противном случае.
  virtual bool contains(int n) const = 0;

  // Операция elements выдает итератор элементов множества.
  // Поскольку множество потенциально бесконечно, причем
  // проверить этот факт перебором всех элементов невозможно,
  // то, как правило, метод hasMoreElements этого итератора
  // будет всегда выдавать значение true.
  virtual Iterator<int> * elements() const {
    return new IntSetIterator(this);
  }
};

//------------------------------------------------------------------
//  Класс SetPlusElement реализует понятие множества с добавленным
//  элементом
//------------------------------------------------------------------
class SetPlusElement : public IntSet {
  SmartPtr<IntSet> oldSet;       // множество
  int newElement;                // и добавленный к нему элемент

public :

  // Конструктор множества запоминает, какой элемент добавлен
  SetPlusElement(const SmartPtr<IntSet> & set, int n)
    : oldSet(set), newElement(n)
  {}

  // Новая функция contains отличается от старой только тем, что
  // выдает информацию о добавленном элементе
  bool contains(int n) const {
    return n == newElement || oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс SetPlusRange реализует понятие множества с добавленными
//  элементами из заданного диапазона
//------------------------------------------------------------------
class SetPlusRange : public IntSet {
  SmartPtr<IntSet> oldSet; // множество
  int minElement;          // минимальный из добавленных к нему элементов
  int maxElement;          // максимальный из добавленных к нему элементов

public :

  // Конструктор множества запоминает, какие элементы добавлены
  SetPlusRange(const SmartPtr<IntSet> & set, int min, int max)
    : oldSet(set), minElement(min), maxElement(max)
  {}

  // Новая функция contains отличается от старой только тем, что
  // выдает информацию о добавленных элементах
  bool contains(int n) const {
    return (n >= minElement && n <= maxElement) || oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс SetMinusElement реализует понятие множества с удаленным
//  элементом
//------------------------------------------------------------------
class SetMinusElement : public IntSet {
  SmartPtr<IntSet> oldSet;       // множество
  int remElement;                // и удаленный из него элемент

public :

  // Конструктор множества запоминает, какой элемент удаляется
  SetMinusElement(const SmartPtr<IntSet> & set, int n)
    : oldSet(set), remElement(n)
  {}

  // Новая функция contains отличается от старой только тем, что
  // выдает информацию об удаленном элементе
  bool contains(int n) const {
    return n != remElement && oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс SetMinusRange реализует понятие множества с удаленными
//  элементами из заданного диапазона
//------------------------------------------------------------------
class SetMinusRange : public IntSet {
  SmartPtr<IntSet> oldSet; // множество
  int minElement;          // минимальный из удаленных из него элементов
  int maxElement;          // максимальный из удаленных из него элементов

public :

  // Конструктор множества запоминает, какие элементы удаляются
  SetMinusRange(const SmartPtr<IntSet> & set, int min, int max)
    : oldSet(set), minElement(min), maxElement(max)
  {}

  // Новая функция contains отличается от старой только тем, что
  // выдает информацию об удаленных элементах
  bool contains(int n) const {
    return (n < minElement || n > maxElement) && oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс Conjunction реализует понятие множества, образованного
//  пересечением двух других множеств
//------------------------------------------------------------------
class Conjunction : public IntSet {
  SmartPtr<IntSet> s1;    // Первое из пересекаемых множеств
  SmartPtr<IntSet> s2;    // Второе пересекаемое множество

public :

  // Конструктор запоминает пересекаемые множества
  Conjunction(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2)
    : s1(s1), s2(s2) {}

  // Элемент содержится в пересечении, если он содержится в обоих
  // пересекаемых множествах
  bool contains(int n) const {
    return s1->contains(n) && s2->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс Disjunction реализует понятие множества, образованного
//  объединением двух других множеств
//------------------------------------------------------------------
class Disjunction : public IntSet {
  SmartPtr<IntSet> s1;     // Первое из объединяемых множеств
  SmartPtr<IntSet> s2;     // Второе объединяемое множество

public :

  // Конструктор запоминает объединяемые множества
  Disjunction(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2)
    : s1(s1), s2(s2) {}

  // Элемент содержится в объединении, если он содержится хотя бы
  // в одном из объединяемых множеств
  bool contains(int n) const {
    return s1->contains(n) || s2->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс Inversion реализует понятие множества, образованного
//  дополнением другого множества
//------------------------------------------------------------------
class Inversion : public IntSet {
  SmartPtr<IntSet> oldSet;     // Инвертируемое множество

public :

  // Конструктор запоминает инвертируемое множество
  Inversion(const SmartPtr<IntSet> & s) : oldSet(s) {}

  // Элемент содержится в инверсии, если он не содержится
  // в исходном множестве
  bool contains(int n) const {
    return n >= 0 && !oldSet->contains(n);
  }
};

//------------------------------------------------------------------
//  Класс Difference реализует понятие множества, образованного
//  разностью двух других множеств
//------------------------------------------------------------------
class Difference : public IntSet {
  SmartPtr<IntSet> s1;       // Уменьшаемое
  SmartPtr<IntSet> s2;       // Вычитаемое

public :

  // Конструктор запоминает вычитаемые множества
  Difference(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2)
    : s1(s1), s2(s2) {}

  // Элемент содержится в разности, если он содержится в
  // уменьшаемом, но не содержится в вычитаемом
  bool contains(int n) const {
    return s1->contains(n) && !s2->contains(n);
  }
};

//-------------------------------------------------------------
// Два полезных класса, реализующих понятия пустого и
// универсального (содержащего все элементы) множеств
//-------------------------------------------------------------

class EmptySet : public IntSet {
public :
  bool contains(int n) const { return false; }
};

class UniversalSet : public IntSet {
public :
  bool contains(int n) const { return n >= 0; }
};

// Функция add возвращает множество с добавленным элементом
SmartPtr<IntSet> add(const SmartPtr<IntSet> & set, int n);

// Функция addRange возвращает множество с добавленными элементами
SmartPtr<IntSet> addRange(const SmartPtr<IntSet> & set, int min, int max);

// Функция remove возвращает множество с удаленным элементом
SmartPtr<IntSet> remove(const SmartPtr<IntSet> & set, int n);

// Функция removeRange возвращает множество с удаленными элементами
SmartPtr<IntSet> removeRange(const SmartPtr<IntSet> & set, int min, int max);

// Функция conjunct возвращает пересечение двух множеств
SmartPtr<IntSet> conjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2);

// Функция disjunct возвращает объединение двух множеств
SmartPtr<IntSet> disjunct(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2);

// Функция inverse возвращает дополнение множества
SmartPtr<IntSet> inverse(const SmartPtr<IntSet> & s);

// Функция diff выдает разность двух заданных множеств
SmartPtr<IntSet> diff(const SmartPtr<IntSet> & s1, const SmartPtr<IntSet> & s2);

#endif
