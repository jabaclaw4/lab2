#ifndef ARRAY_SEQUENCE_BASE_H
#define ARRAY_SEQUENCE_BASE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include <stdexcept>

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

    //реализация добавления (общая для Mutable и Immutable)
    Sequence<T>* appendImpl(const T& elem) override {
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);
        this->items->Set(oldSize, elem);
        return this;
    }

    Sequence<T>* prependImpl(const T& elem) override {
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);
        for (int i = oldSize; i > 0; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }
        this->items->Set(0, elem);
        return this;
    }

    Sequence<T>* insertAtImpl(const T& elem, int index) override {
        if (index < 0 || index > this->items->GetSize()) {
            throw std::out_of_range("index out of range");
        }

        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);

        for (int i = oldSize; i > index; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }
        this->items->Set(index, elem);
        return this;
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

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || startIndex >= this->items->GetSize()) {
            throw std::out_of_range("start index out of range");
        }
        if (endIndex < 0 || endIndex >= this->items->GetSize()) {
            throw std::out_of_range("end index out of range");
        }
        if (startIndex > endIndex) {
            throw std::invalid_argument("start index > end index");
        }

        int size = endIndex - startIndex + 1;
        ArraySequenceBase<T>* result = this->CreateNew(size);

        for (int i = 0; i < size; i++) {
            result->items->Set(i, this->items->Get(startIndex + i));
        }

        return result;
    }

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        ArraySequenceBase<T>* result = this->CreateNew(this->items->GetSize() + other->GetLength());

        for (int i = 0; i < this->items->GetSize(); i++) {
            result->items->Set(i, this->items->Get(i));
        }

        for (int i = 0; i < other->GetLength(); i++) {
            result->items->Set(this->items->GetSize() + i, other->Get(i));
        }

        return result;
    }

protected:
    //вспомогательная функция создать новый экземпляр (реализуется в наследниках)
    virtual ArraySequenceBase<T>* CreateNew(int size) const = 0;
};

#endif