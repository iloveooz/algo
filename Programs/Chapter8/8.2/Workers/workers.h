/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 8. Функции как носитель информации                *
*          8.2. Задача о расстановке ферзей на шахматной доске *
*               и другие задачи                                *
*                                                              *
*  Автор       : А. Кубенский                                  *
*  Файл        : workers.h                                     *
*  Описание    : Определение класса для функционального        *
*                представления распределения рабочих мест      *
***************************************************************/

#ifndef __WORKERS_H
#define __WORKERS_H

#include <iostream>
#include "smartptr.h"

using namespace std;

typedef double (* fProd)(int, int);

//-------------------------------------------------------------
// Абстрактный тип данных Assignment представляет расстановку
// n рабочих по n рабочим местам. Атрибут output представляет
// функцию, задающую производительность труда работников.
//-------------------------------------------------------------
class Assignment {
protected :
  fProd output;   // Функция, задающая производительность труда

  // Базовый конструктор
  Assignment(fProd output) : output(output) {}

public :
  // Виртуальный деструктор для правильного освобождения памяти
  virtual ~Assignment() {}
  // Доступ к функции, задающей производительность труда
  fProd getOutput() const { return output; }
  // Вычисление суммарной производительности расстановки
  virtual double prod() const = 0;
  // Проверка, свободен ли рабочий с заданным номером i
  virtual bool free(int i) const = 0;
  // Вывод информации о расстановке рабочих в выходной поток
  virtual void print(ostream & os) const = 0;
};

// Функция, вычисляющая лучшую расстановку рабочих
SmartPtr<Assignment> bestAssignment(fProd output, int n);

#endif
