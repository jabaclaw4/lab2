#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdexcept>
//virtual = "эта функция может работать по-разному в зависимости от реального типа объекта"
//Компилятор смотрит на тип переменной, а не на реальный объект

template <class T>
class Sequence {
public:
    virtual ~Sequence() {}
    //получить первый элемент
    virtual T GetFirst() const = 0;

    //получить последний элемент
    virtual T GetLast() const = 0;

    //получить элемент по индексу
    virtual T Get(int index) const = 0;

    //получить подпоследовательность
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    //получить длину
    virtual int GetLength() const = 0;

    //добавить элемент в конец
    virtual void Append(T item) = 0;

    //дообавить элемент в начало
    virtual void Prepend(T item) = 0;

    //вставить элемент на позицию
    virtual void InsertAt(T item, int index) = 0;

    //объединить последовательности
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;
};

#endif