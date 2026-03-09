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

    //clone - создать копию
    ListSequenceBase<T>* Clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

    //методы изменения - не изменяют этот объект, создают новый
    void Append(T item) override {
        //создаём копию
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);

        //изменяем копию
        result->items->Append(item);

        //подменяем данные
        delete this->items;
        this->items = result->items;
        result->items = nullptr;
        delete result;
    }

    void Prepend(T item) override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);

        result->items->Prepend(item);

        delete this->items;
        this->items = result->items;
        result->items = nullptr;
        delete result;
    }

    void InsertAt(T item, int index) override {
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*this);

        result->items->InsertAt(item, index);

        delete this->items;
        this->items = result->items;
        result->items = nullptr;
        delete result;
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

    Sequence<T>* Concat(Sequence<T>* other) const override {
        //создаём новую последовательность
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>();

        //копируем элементы из текущей последовательности
        for (int i = 0; i < this->GetLength(); i++) {
            result->Append(this->Get(i));
        }

        //копируем элементы из другой последовательности
        for (int i = 0; i < other->GetLength(); i++) {
            result->Append(other->Get(i));
        }

        return result;
    }
};

#endif