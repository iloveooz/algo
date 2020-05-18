/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 5. Алгоритмы распределения памяти                 *
*          5.3. Распределение памяти блоками переменной длины  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : bintwins.cpp                                     *
*  Описание : Реализация системы распределения и управления    *
*             блоками памяти методом двоичных близнецов        *
***************************************************************/

#include <iostream>

using namespace std;

#include "bintwins.h"

// Статистика запросов к памяти:
int BinTwinsMemory::claims = 0;
size_t BinTwinsMemory::reserved = 0;
size_t BinTwinsMemory::demanded = 0;

// Операция выделения свободного блока памяти заданного размера
void * BinTwinsMemory::get(size_t sz) {
  sz += sizeof(char);   // один байт разервируется дополнительно
  // Вычисление размерности блока, который необходимо зарезервировать
  char p = 2;
  while (sz != (1 << p) && (~((1u << p)-1) & sz) != 0) p++;
  // Обращение к рекурсивной функции, выдающей смещение свободного блока
  size_t request = getRec(p);
  if (request == null) throw NoMoreMemoryException();
  // Статистические подсчеты
  claims++;
  demanded += sz - sizeof(char);
  reserved += 1 << p;
  // В начало блока помещаем его размерность и выдаем адрес
  char * block = buffer + request;
  *block = p;
  return block + sizeof(char);
}

// Рекурсивная функция выделения свободного блока памяти
size_t BinTwinsMemory::getRec(char p) {
  // 1. Проверка: если запрашивается блок слишком большого размера,
  //    значит, свободной памяти больше нет
  if (p > power) return null;
  // 2. Проверяем список свободных блоков нужного размера
  if (freeLists[p] == null) {
    // Список пуст; запрашиваем вдвое больший блок.
    size_t doubleBlock = getRec(p + 1);
    // Если запрос закончился неудачно, то возвращаем пустой указатель.
    if (doubleBlock == null) return null;
    // Блок вдвое большего размера делится пополам;
    // адрес блока-близнеца записывается в соответствующий список
    size_t twinBlock = doubleBlock + (1 << p);
    *(size_t *)(buffer + twinBlock) = null;
    freeLists[p] = twinBlock;
    return doubleBlock;
  } else {
    // Свободный блок нужного размера найден; он исключается
    // из списка и его адрес выдается в качестве результата
    size_t result = freeLists[p];
    freeLists[p] = *(size_t *)(buffer + freeLists[p]);
    return result;
  }
}

// Операция возврата выделенного блока памяти в систему
void BinTwinsMemory::release(void * ptr) {
  // Вычисляем адрес блока и его размерность p
  char * block = (char*)ptr - sizeof(char);
  char p = *block;
  // Обращаемся к рекурсивной функции возврата блока в систему
  releaseRec(block - buffer, p);
}

// Рекурсивная функция возврата выделенного блока памяти в систему
void BinTwinsMemory::releaseRec(size_t block, char p) {
  // Вычисляем адрес близнеца
  size_t twinBlock = (1 << p) ^ block;
  // Организуем поиск блока-близнеца в списке свободных блоков
  size_t* ptr = &freeLists[p];
  while (*ptr != null && *ptr != twinBlock) {
    ptr = (size_t*)(buffer + *ptr);
  }

  if (*ptr == null) {
    // Адрес близнеца не найден – блок присоединяется к списку
    *(size_t*)(buffer + block) = freeLists[p];
    freeLists[p] = block;
  } else {
    // Блок-близнец исключается из списка свободных блоков
    *ptr = *(size_t*)(buffer + *ptr);
    // Рекурсивный вызов для освобождения блока удвоенного размера
    releaseRec(block & ~(1u << p), p+1);
  }
}
