#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequenceBase.h"
//неизменяемая последовательность на базе массива
template <class T>
class ImmutableArraySequence : public ArraySequenceBase<T> {
public:
    //конструкторы
    ImmutableArraySequence() : ArraySequenceBase<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequenceBase<T>(items, count) {}
    ImmutableArraySequence(int size) : ArraySequenceBase<T>(size) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequenceBase<T>(other) {}

    ArraySequenceBase<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }
//не изм данные
    Sequence<T>* Append(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

        int oldSize = copy->items->GetSize();
        copy->items->Resize(oldSize + 1);
        copy->items->Set(oldSize, item);

        return copy;
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

        int oldSize = copy->items->GetSize();
        copy->items->Resize(oldSize + 1);

        for (int i = oldSize; i > 0; i--) {
            copy->items->Set(i, copy->items->Get(i - 1));
        }

        copy->items->Set(0, item);

        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        int size = this->items->GetSize();

        if (index < 0 || index > size) {
            throw std::out_of_range("index out of range");
        }

        ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

        copy->items->Resize(size + 1);

        for (int i = size; i > index; i--) {
            copy->items->Set(i, copy->items->Get(i - 1));
        }

        copy->items->Set(index, item);

        return copy;
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
        ImmutableArraySequence<T>* subSeq = new ImmutableArraySequence<T>(newSize);

        for (int i = 0; i < newSize; i++) {
            subSeq->items->Set(i, this->items->Get(startIndex + i));
        }

        return subSeq;
    }

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        int newSize = this->GetLength() + other->GetLength();
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(newSize);

        for (int i = 0; i < this->GetLength(); i++) {
            result->items->Set(i, this->items->Get(i));
        }

        for (int i = 0; i < other->GetLength(); i++) {
            result->items->Set(this->GetLength() + i, other->Get(i));
        }

        return result;
    }
};

#endif