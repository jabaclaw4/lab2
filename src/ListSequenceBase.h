#ifndef LIST_SEQUENCE_BASE_H
#define LIST_SEQUENCE_BASE_H

#include "Sequence.h"
#include "LinkedList.h"

//базовый класс с общим кодом для mutable и immutable
template <class T>
class ListSequenceBase : public Sequence<T> {
protected:
    LinkedList<T>* items; //конструкторы protected чтобы только наследники могут использовать
    //пустая последовательность
    ListSequenceBase() {
        this->items = new LinkedList<T>();
    }
    //создать из массива
    ListSequenceBase(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
    }
    //копирующий конструктор
    ListSequenceBase(const ListSequenceBase<T>& other) {
        this->items = new LinkedList<T>(*other.items);
    }

public:
    virtual ~ListSequenceBase() {
        delete this->items;
    }

    //методы чтения - одинаковые для mutable и immutable
    //LinkedList все сам проверит
    T GetFirst() const override {
        return this->items->GetFirst();
    }

    T GetLast() const override {
        return this->items->GetLast();
    }

    T Get(int index) const override {
        return this->items->Get(index);
    }

    int GetLength() const override {
        return this->items->GetLength();
    }

    //вспомогательная функция: создать копию
    virtual ListSequenceBase<T>* Clone() const = 0;
};

#endif