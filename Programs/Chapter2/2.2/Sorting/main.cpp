/***************************************************************
*  Структуры и алгоритмы обработки данных:                     *
*  объектно-ориентированный подход и реализация на C++         *
*      Глава 2. Базовые алгоритмы                              *
*          2.2. Сортировка и поиск в массивах                  *
*                                                              *
*  Автор    : А.Кубенский                                      *
*  Файл     : main.cpp                                         *
*  Описание : Тестовая функция, проверяющая работу алгоритмов  *
*             сортировки и поиска                              *
***************************************************************/

#include <iostream>
#include <string>
#include "binsearch.h"
#include "insertsort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "quicksort.h"
#include "digitsort.h"

using namespace std;

template <class Element>
void printArray(Element * array, int low, int high) {
  for (int i = low; i <= high; i++) {
    cout << array[i] << ", ";
  }
  cout << endl;
}

class IntKey {
  friend ostream & operator << (ostream & out, const IntKey & v);

  int value;
public :
  IntKey(int v = 0) : value(v) {}
  IntKey(const IntKey & key) : value(key.value) {}
  int getValue() { return value; }
  int length() { return 8; }
  int power() { return 16; }
  int operator [] (int i) const { return (value >> (4*(7-i))) & 15; }
};

ostream & operator << (ostream & out, const IntKey & v) {
  return out << v.value;
}

int main() {
  // Массив test1 уже упорядочен. Он содержит 25
  // элементов, и еще два места зарезервировано для
  // новых ключей.
  int test1[] = {
     0,  4,  5,  6,  9, 12, 19, 20, 29, 32,
    37, 40, 43, 44, 46, 52, 58, 65, 67, 70,
    73, 76, 77, 88, 89,  0,  0
  };
  int len1 = sizeof(test1)/sizeof(int);

  // Вывод массива test1
  printArray<int>(test1, 0, len1-3);

  // Осуществляем поиск в упорядоченном массиве значения 58
  // и выводим результирующий индекс - должен быть равен 16.
  cout << binSearch<int>(test1, 0, len1-3, 58) << endl << endl;

  // Осуществляем вставку в упорядоченный массив 
  // двух новых значений : 10 и 95
  insert<int>(test1, 0, len1-3, 10);
  insert<int>(test1, 0, len1-2, 95);
  // Вывод массива test1 после вставки
  printArray<int>(test1, 0, len1-1); cout << endl;

  // Массив для сортировки:
  int len2 = 25;
  int *test2 = new int[len2];

  // Заполненяем массив test2 случайными значениями и выводим их
  int seed = 13;
  for (int i = 0; i < len2; i++) {
    test2[i] = (seed = (837*seed + 1079) % 2313) % 1000;
  }
  printArray<int>(test2, 0, len2-1);

  // Сортируем массив методом простых вставок и выводим результат
  insertSort<int>(test2, 0, len2-1);
  printArray<int>(test2, 0, len2-1);

  // Снова заполненяем массив test2 случайными значениями и выводим их
  for (int i=0; i < len2; i++) {
    test2[i] = (seed = (837*seed + 1079) % 213) % 100;
  }
  printArray<int>(test2, 0, len2-1);

  // Сортируем массив методом двоичных вставок и выводим результат
  binInsertSort<int>(test2, 0, len2-1);
  printArray<int>(test2, 0, len2-1); cout << endl;

  // Для слияния подготовим два массива строк длиной 30 и 26 элементов
  // и буфер длиной 56 элементов.
  string sTest1[] = {
    "the", "final", "step", "in", "the",
    "deployment", "process", "occurs", "when", "the",
    "software", "is", "installed", "on", "individual",
    "user", "system.", "installation", "consists", "of",
    "copying", "software", "onto", "the", "user\'s",
    "system,", "then", "configuring", "the", "user\'s"
  };
  int lenT1 = sizeof(sTest1)/sizeof(string);

  string sTest2[] = {
    "system", "to", "support", "that", "software.",
    "you", "should", "ensure", "that", "your",
    "installation", "procedure", "does", "not", "overwrite",
    "existing", "jre", "installations", "as", "they",
    "may", "be", "required", "by", "other",
    "applications" 
  };
  int lenT2 = sizeof(sTest2)/sizeof(string);

  string *sTest = new string[lenT1+lenT2];

  // Отсортируем и напечатаем исходные массивы, а затем выполним
  // над ними процедуру слияния и напечатаем результат.
  
  binInsertSort<string>(sTest1, 0, lenT1-1);
  printArray<string>(sTest1, 0, lenT1-1); cout << endl;
  binInsertSort<string>(sTest2, 0, lenT2-1);
  printArray<string>(sTest2, 0, lenT2-1); cout << endl;

  merge<string>(sTest1, 0, lenT1-1, sTest2, 0, lenT2-1, sTest, 0);
  printArray<string>(sTest, 0, lenT1+lenT2-1); cout << endl;

  // Следующий массив сортируется методом сортировки слянием
  string sMerge[] = {
    "we", "are", "pleased", "to", "announce",
    "a", "new", "release", "of", "hugs98",
    "an", "interpreter", "and", "programming", "environment",
    "for", "developing", "haskell", "programs", "sources",
    "and", "binaries", "are", "freely", "available",
    "on", "the", "world", "wide", "web"
  };
  int lenMerge = sizeof(sMerge)/sizeof(string);

  mergeSort<string>(sMerge, 0, lenMerge-1);
  printArray<string>(sMerge, 0, lenMerge-1); cout << endl;

  // Теперь сортируем массив методом пирамидальной сортировки
  string sHeap[] = {
    "the", "java", "runtime", "environment", "contains",
    "the", "java", "virtual", "machine", "runtime",
    "class", "libraries", "and", "java", "application",
    "launcher", "that", "are", "necessary", "to",
    "run", "programs", "written", "in", "the",
    "java", "programming", "language", "it", "is",
    "not", "a", "development", "environment", "and",
    "does", "not", "contain", "development", "tools",
    "such", "as", "compilers", "or", "debuggers",
    "for", "development", "tools", "see", "the",
    "java", "sdk", "standard", "edition"
  };
  int lenHeap = sizeof(sHeap)/sizeof(string);

  heapSort<string>(sHeap, 0, lenHeap-1);
  printArray<string>(sHeap, 0, lenHeap-1); cout << endl;

  // Наконец, сортируем массив методом "быстрой" сортировки
  string sQuick[] = {
    "when", "you", "register", "we", "ask",
    "for", "information", "such", "as", "your",
    "name", "email", "address", "birth", "date",
    "gender", "zip", "code", "occupation", "industry",
    "and", "personal", "interests", "for", "some",
    "financial", "products", "and", "services", "we",
    "may", "also", "ask", "for", "your",
    "address", "social", "security", "number", "and",
    "information", "about", "your", "assets", "once",
    "you", "register", "with", "yahoo!", "and",
    "sign", "in", "to", "our", "services",
    "you", "are", "not", "anonymous", "to", "us"
  };
  int lenQuick = sizeof(sQuick)/sizeof(string);

  quickSort<string>(sQuick, 0, lenQuick-1);
  printArray<string>(sQuick, 0, lenQuick-1); cout << endl;

  // Заполненяем массив test3 случайными значениями и выводим их
  const int len3 = 100;
  IntKey test3[len3];
  seed = 13;
  for (int i = 0; i < len3; i++) {
    test3[i] = IntKey(seed = (837*seed + 1079) & 0x7FFFFFFF);
  }
  printArray<IntKey>(test3, 0, len3-1);
  cout << endl;

  // Сортируем массив методом цифровой сортировки и выводим результат
  digitSort<IntKey>(test3, 0, len3-1);
  printArray<IntKey>(test3, 0, len3-1);

  return 0;
}
