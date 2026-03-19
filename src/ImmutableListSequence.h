#ifndef IMMUTABLE_LIST_SEQUENCE_H
#define IMMUTABLE_LIST_SEQUENCE_H

#include "ListSequenceBase.h"

//неизменяемая последовательность на базе списка
template <class T>
class ImmutableListSequence : public ListSequenceBase<T> {
public:
    //конструкторы
    //пустая последовательность
    ImmutableListSequence() : ListSequenceBase<T>() {}
    //создать из массива
    ImmutableListSequence(T* items, int count) : ListSequenceBase<T>(items, count) {}
    //копирующий конструктор
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequenceBase<T>(other) {}
    ListSequenceBase<T>* Clone() const override {
        return new ImmutableListSequence<T>(*this);
    }
    Sequence<T>* Append(T item) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->items->Append(item);
        return copy;
    }

    Sequence<T>* Prepend(T item) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->items->Prepend(item);
        return copy;
    }

    Sequence<T>* InsertAt(T item, int index) override {
        ImmutableListSequence<T>* copy = new ImmutableListSequence<T>(*this);
        copy->items->InsertAt(item, index);
        return copy;
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        //получаем подсписок из LinkedList
        LinkedList<T>* subList = this->items->GetSubList(startIndex, endIndex);

        //создаём новую ListSequence на базе подсписка
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>();
        delete result->items;  //удаляем пустой список
        result->items = subList;  //заменяем на подсписок

        return result;
    }

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        //создаём новую последовательность
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);

        //копируем элементы из другой последовательности
        for (int i = 0; i < other->GetLength(); i++) {
            result->items->Append(other->Get(i));
        }
        return result;
    }
};

#endif