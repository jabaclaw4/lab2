#ifndef MUTABLE_ARRAY_SEQUENCE_H
#define MUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequenceBase.h"
////добавить комментария для личного понимания вспоминания
//изменяемая последовательность на базе массива
template <class T>
class MutableArraySequence : public ArraySequenceBase<T> {
public:
    //конструкторы
    MutableArraySequence() : ArraySequenceBase<T>() {}

    MutableArraySequence(T* items, int count) : ArraySequenceBase<T>(items, count) {}

    MutableArraySequence(int size) : ArraySequenceBase<T>(size) {}

    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequenceBase<T>(other) {}

    //clone - создать копию
    ArraySequenceBase<T>* Clone() const override {
        return new MutableArraySequence<T>(*this);
    }

    //методы ИЗМЕНЕНИЯ - изменяют ЭТОТ объект
    void Append(T item) override {
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);
        this->items->Set(oldSize, item);
    }

    void Prepend(T item) override {
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);

        for (int i = oldSize; i > 0; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        this->items->Set(0, item);
    }

    void InsertAt(T item, int index) override {
        int size = this->items->GetSize();

        if (index < 0 || index > size) {
            throw std::out_of_range("index out of range");
        }

        if (index == 0) {
            Prepend(item);
            return;
        }

        if (index == size) {
            Append(item);
            return;
        }

        this->items->Resize(size + 1);

        for (int i = size; i > index; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        this->items->Set(index, item);
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

    Sequence<T>* Concat(Sequence<T>* other) const override {
        int newSize = this->GetLength() + other->GetLength();
        MutableArraySequence<T>* result = new MutableArraySequence<T>(newSize);

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