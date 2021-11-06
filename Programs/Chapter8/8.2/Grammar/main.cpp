/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Примеры применения функционального описания      *
*             грамматик                                        *
***************************************************************/

#include "grammar.h"
#include <iostream>

using namespace std;

// Множество слов, представленных одной гласной буквой.
// В этом примере гласными считаются буквы 'a', 'o' и 'e'
class Vowel : public Lang {
public :
  bool contains(const string & word) const {
    return word == "a" || word == "o" || word == "e";
  }
};

// Множество слов, представленных одной согласной буквой.
// В этом примере согласными считаются буквы 'b', 'c' и 'd'
class Consonant : public Lang {
public :
  bool contains(const string & word) const {
    return word == "b" || word == "c" || word == "d";
  }
};

// Функция info предназначена для вывода информации о том,
// входит ли заданное слово w в заданный язык lang.
void info(const Lang & lang, const string & w) {
  cout << w << " - a "
       << (lang.contains(w) ? "write" : "wrong")
       << " word\n";
}

//--------------------------------------------------------------
// Класс Digit представляет язык для слов,
// состоящих из единственного символа - цифры
//--------------------------------------------------------------
class Digit : public Lang {
public :
  bool contains(const string & s) const {
    return s.length() == 1 && s[0] >= '0' && s[0] <= '9';
  }
};

int main() {
  SmartPtr<Lang> vow(new Vowel);
  SmartPtr<Lang> cons(new Consonant);

  // Множество слов, представляющих открытый слог английского языка.
  // В этом примере считаем, что открытый слог состоит из одной согласной
  // и одной или двух гласных букв
  SmartPtr<Lang> cyllable = (cons & vow) | (cons & vow & vow);
  SmartPtr<Lang> word = ~cyllable;

  info(*word, "do");
  info(*word, "bee");
  info(*word, "bead");
  info(*word, "coca");
  info(*word, "cola");
  info(*word, "boodoo");

  cout << endl;

  SmartPtr<Lang> plus(new OneLetterLang('+'));    // Знак "+"
  SmartPtr<Lang> minus(new OneLetterLang('-'));   // Знак "-"
  SmartPtr<Lang> point(new OneLetterLang('.'));   // Десятичная точки
  SmartPtr<Lang> digit(new Digit);                // Десятичная цифры

  // Построение сложных грамматик на базе простых:
  SmartPtr<Lang> sign = plus | minus;               // Знак числа
  SmartPtr<Lang> pos_sign = +sign;                  // Знак или пусто
  SmartPtr<Lang> unSigned = ~digit;                 // Беззнаковое целое
  SmartPtr<Lang> integral = pos_sign & unSigned;    // Целое со знаком
  SmartPtr<Lang> fraction = point & unSigned;       // Дробная часть числа
  SmartPtr<Lang> pos_fraction = +fraction;          // Дробная часть или пусто
  SmartPtr<Lang> number = integral & pos_fraction;  // Десятичное число

  // Проверяем построенную грамматику числа на примерах:
  string testNumbers[] = {"+12", "-22222222222.33333333333333", "3.141693", "", "333-", "-11111+222222"};
  for (int i = 0; i < sizeof(testNumbers)/sizeof(string); i++) {
    string nextWord = testNumbers[i];
    cout << "<" << nextWord << "> ";
    // Проверяем, принадлежит ли заданное слово грамматике числа
    cout << (number->contains(nextWord) ? "Number" : "Not number") << endl;
  }
  cout << endl;

  return 0;
}
