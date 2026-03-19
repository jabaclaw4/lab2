#ifndef ARRAY_SEQUENCE_BASE_H
#define ARRAY_SEQUENCE_BASE_H

#include "Sequence.h"
#include "DynamicArray.h"
//класс ArraySequence - реализация Sequence на базе DynamicArray
//ArraySequence обяхан реализовать все функции из Sequence
//базовый класс с общим кодом для mutable и immutable
template <class T>
class ArraySequenceBase : public Sequence<T> {
protected:
    DynamicArray<T>* items; //внутри используем DynamicArray
    //конструкторы protected - только наследники могут использовать
    //создать пустую последовательность
    ArraySequenceBase() {
        this->items = new DynamicArray<T>(0);
    }
    //создать из массива
    ArraySequenceBase(T* items, int count) {
        this->items = new DynamicArray<T>(items, count);
    }
    //создать заданного размера
    ArraySequenceBase(int size) {
        this->items = new DynamicArray<T>(size);
    }
    //копирующий конструктор
    ArraySequenceBase(const ArraySequenceBase<T>& other) {
        this->items = new DynamicArray<T>(*other.items);
    }

public:
    virtual ~ArraySequenceBase() {
        delete this->items;
    }

    //одинаковые для mutable и immutable
    T GetFirst() const override {
        if (this->items->GetSize() == 0) {
            throw std::out_of_range("sequence is empty");
        }
        return this->items->Get(0);
    }

    T GetLast() const override {
        if (this->items->GetSize() == 0) {
            throw std::out_of_range("sequence is empty");
        }
        return this->items->Get(this->items->GetSize() - 1);
    }

    T Get(int index) const override {
        return this->items->Get(index);
    }

    int GetLength() const override {
        return this->items->GetSize();
    }

    //вспомогательная функция создать копию
    virtual ArraySequenceBase<T>* Clone() const = 0;
};

#endif