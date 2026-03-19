#ifndef MUTABLE_ARRAY_SEQUENCE_H
#define MUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequenceBase.h"
//изменяемая последовательность на базе массива
template <class T>
class MutableArraySequence : public ArraySequenceBase<T> {
public:
    //конструкторы
    MutableArraySequence() : ArraySequenceBase<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequenceBase<T>(items, count) {}
    MutableArraySequence(int size) : ArraySequenceBase<T>(size) {}
    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequenceBase<T>(other) {}

    ArraySequenceBase<T>* Clone() const override {
        return new MutableArraySequence<T>(*this);
    }

    //методы изменения
    Sequence<T>* Append(T item) override {
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);
        this->items->Set(oldSize, item);
        return this;
    }

    Sequence<T>* Prepend(T item) override {
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);

        for (int i = oldSize; i > 0; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        this->items->Set(0, item);
        return this;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        int size = this->items->GetSize();

        if (index < 0 || index > size) {
            throw std::out_of_range("index out of range");
        }

        this->items->Resize(size + 1);

        for (int i = size; i > index; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        this->items->Set(index, item);
        return this;
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

        int newSize = endIndex - startIndex + 1;
        MutableArraySequence<T>* subSeq = new MutableArraySequence<T>(newSize);

        for (int i = 0; i < newSize; i++) {
            subSeq->items->Set(i, this->items->Get(startIndex + i));
        }

        return subSeq;
    }

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        MutableArraySequence<T>* result = new MutableArraySequence<T>(*this);

        //расширяем копию
        int oldSize = result->GetLength();
        int newSize = oldSize + other->GetLength();
        result->items->Resize(newSize);

        //добавляем элементы other в копию
        for (int i = 0; i < other->GetLength(); i++) {
            result->items->Set(oldSize + i, other->Get(i));
        }
        return result;  //возвращаем копию
    }
};

#endif