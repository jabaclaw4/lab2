#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequenceBase.h"
//добавить комментария для личного понимания вспоминания
//неизменяемая последовательность на базе массива
template <class T>
class ImmutableArraySequence : public ArraySequenceBase<T> {
public:
    //конструкторы
    ImmutableArraySequence() : ArraySequenceBase<T>() {}

    ImmutableArraySequence(T* items, int count) : ArraySequenceBase<T>(items, count) {}

    ImmutableArraySequence(int size) : ArraySequenceBase<T>(size) {}

    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequenceBase<T>(other) {}

    //clone - создать копию
    ArraySequenceBase<T>* Clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }

    //методы ИЗМЕНЕНИЯ - НЕ изменяют этот объект, возвращают НОВЫЙ!
    void Append(T item) override {
        //создаём копию
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);

        //изменяем копию
        int oldSize = result->items->GetSize();
        result->items->Resize(oldSize + 1);
        result->items->Set(oldSize, item);

        //подменяем внутренние данные этого объекта на новые
        delete this->items;
        this->items = result->items;
        result->items = nullptr;
        delete result;
    }

    void Prepend(T item) override {
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);

        int oldSize = result->items->GetSize();
        result->items->Resize(oldSize + 1);

        for (int i = oldSize; i > 0; i--) {
            result->items->Set(i, result->items->Get(i - 1));
        }

        result->items->Set(0, item);

        delete this->items;
        this->items = result->items;
        result->items = nullptr;
        delete result;
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

        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*this);

        result->items->Resize(size + 1);

        for (int i = size; i > index; i--) {
            result->items->Set(i, result->items->Get(i - 1));
        }

        result->items->Set(index, item);

        delete this->items;
        this->items = result->items;
        result->items = nullptr;
        delete result;
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

    Sequence<T>* Concat(Sequence<T>* other) const override {
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