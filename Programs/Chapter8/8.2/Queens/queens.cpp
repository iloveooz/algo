/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : queens.cpp                                    *
*  Описание    : Традиционные алгоритмы решения задачи         *
*                о расстановке ферзей на шахматной доске       *
***************************************************************/

#include <stdlib.h>

// Функция correct проверяет, представляет ли заданная перестановка чисел
// от 1 до n корректную расстановку ферзей на шахматной доске
bool correct(int * pos, int n) {
  // Перебираем всевозмолжные пары двух различных ферзей
  for (int i = 0;  i < n;  i++) {
    for (int j = i+1;  j < n;  j++) {
      if (abs(i-j) == abs(pos[i]-pos[j]))
        // Ферзи стоят на одной диагонали
        return false;
    }
  }
  // Проверка завершена успешно, ни одной пары ферзей,
  // стоящих на одной диагонали, не найдено.
  return true;
}

// Функция recQueen находит правильную расстановку ферзей на доске
// размером n x n при условии, что первые k ферзей уже расставлены,
// так что переставлять можно только числа, находящиеся в элементах с
// индексами, большими k. Если такая расстановка существует, то функция
// выдает ее в качестве результата. Если расстановки с такими начальными 
// данными не существует, функция выдает NULL.
int * recQueen(int * pos, int k, int n) {
  // проверяем расстановку на корректность
  if (!correct(pos, k)) return NULL;
  // проверяем, не расставлены ли уже все ферзи?
  if (k == n) {
    return pos;
  }
  // находим всевозможные перестановки элементов с индексами
  // от k до n-1
  for (int i = k;  i < n;  i++) {
    // Переставляем местами i-ый и k-ый элементы
    int c = pos[k];  pos[k] = pos[i];  pos[i] = c;
    // Пытаемся найти расстановку с фиксированными k+1 ферзями
    int * per = recQueen(pos, k+1, n);
    if (per) return per;
  }
  // Ничего не найдено
  return NULL;
}

// Главная функция поиска расстановки n ферзей на доске размером n x n
int * queen(int n) {
  int * pos = new int[n];
  // Формирование начальной расстановки
  for (int i = 0;  i < n;  i++) {
    pos[i] = i+1;
  }
  // Вызов основной рекурсивной процедуры
  return recQueen(pos, 0, n);
}

// Функция recQueen находит правильную расстановку ферзей на доске
// размером n x n при условии, что первые k ферзей уже расставлены и
// друг друга не атакуют, так что расставлять нужно только ферзей с 
// номерами, большими k. Если такая расстановка существует, то функция
// выдает ее в качестве результата. Если расстоновки с такими начальными 
// данными не существует, функция выдает NULL.
int * rec_Queen(int * pos, int k, int n) {
  if (k == n) return pos;       // Все ферзи уже расставлены корректно
  for (int j = 1;  j <= n;  j++) {
    // Пробуем поставить k+1-го ферзя последовательно на все вертикали
    bool correct = true;        // Признак корректной расстановки
    for (int i = 0;  i < k;  i++) {
      // Проверяем, не атакует ли новый ферзь уже поставленных
      if (pos[i] == j || k - i == abs(j - pos[i])) {
        // Если новый ферзь находится на одной вертикали или диагонали
        // с некоторым i-ым ферзем, то расстановка некорректна
        correct = false;
        break;
      }
    }
    if (correct) {
      pos[k] = j;
      // Установили ферзя в свою позицию и пробуем расставить
      // остальных ферзей с помощью рекурсивного вызова функции
      int * pos1 = rec_Queen(pos, k+1, n);
      if (pos1)      // Расстановка найдена!
        return pos1;
    }
  }
  // Перебрали все варианты постановки k+1-го ферзя, но ничего не нашли!
  return NULL;
}

// Главная функция поиска расстановки n ферзей на доске размером n x n
int * queen1(int n) {
  return rec_Queen(new int[n], 0, n);
}
