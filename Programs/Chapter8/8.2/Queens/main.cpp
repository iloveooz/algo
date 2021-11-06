/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : main.cpp                                      *
*  Описание    : Проверка различных алгоритмов решения задачи  *
*                о расстановке ферзей на шахматной доске       *
***************************************************************/

#include <iostream>
#include <time.h>
#include "queens.h"
#include "position.h"

using namespace std;

const int POS_LEN = 28;

void printPos(int * pos, int n) {
  if (pos) {
    // Распечатываем найденную позицию в удобном виде
    // Это цикл по всем горизонталям, начиная с первой
    for (int i = 0;  i < POS_LEN;  i++) {
      // Печать одной горизонтали:
      int queenPos = pos[i];
      for (int k = 1;  k < queenPos;  k++) {
        cout << ". ";
      }
      cout << "Q ";
      for (int k = queenPos+1;  k <= POS_LEN;  k++) {
        cout << ". ";
      }
      cout << endl;
    }
  } else {
    cout << "No correct position found!" << endl;
  }
}

int main() {
  cout << "Starting..." << endl;

  // Алгоритм расстановки ферзей с помощью генерации перестановок
  long t = time(0);
  int * pos = queen(POS_LEN);
  t = time(0) - t;
  printPos(pos, POS_LEN);
  cout << endl << "Total time = " << t << endl << endl;

  // Алгоритм расстановки ферзей с помощью перебора с возвратом
  t = time(0);
  pos = queen1(POS_LEN);
  t = time(0) - t;
  printPos(pos, POS_LEN);
  cout << endl << "Total time = " << t << endl << endl;

  // Функциональный способ представления позиции
  t = time(0);
  SmartPtr<Position> p = queen2(POS_LEN);
  t = time(0) - t;
  if (p) {
    cout << *p;
  } else {
    cout << "No correct position found!\n";
  }
  cout << endl << "Total time = " << t << endl;

  return 0;
}
