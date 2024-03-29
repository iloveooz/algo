/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.2. Стеки и очереди                                *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Функция для тестирования реализаций операций над *
*             абстрактной очередью                             *
***************************************************************/

#include <iostream>
#include "queue.h"
#include "queuefactory.h"

using namespace std;

// Переменная представляет абстрактную фабрику стеков
extern QueueFactory<int> * factory;

int main() {
  // Создаем очередь из целых чисел
  Queue<int> * q = factory->newQueue();

  // Добавляем в конец очереди несколько элементов
  for (int i = 0; i < 10; i += 3) {
    q->enqueue(i);
    cout << "next item enqueued: " << q->tail() << endl;
  }

  // Удаляем элементы из очереди и распечатываем
  // их содержимое в процессе удаления
  cout << "Now in the queue:" << endl;
  for (int j = 0; j < 10; j += 3) {
    cout << q->head() << "; ";
    q->dequeue();
  }
  cout << endl;

  // Уничтожаем очередь
  delete q;

  return 0;
}
