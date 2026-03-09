#ifndef MUTABLE_LIST_SEQUENCE_H
#define MUTABLE_LIST_SEQUENCE_H

#include "ListSequenceBase.h"

//изменяемая последовательность на базе списка
template <class T>
class MutableListSequence : public ListSequenceBase<T> {
public:
    //конструкторы

    //пустая последовательность
    MutableListSequence() : ListSequenceBase<T>() {}

    //создать из массива
    MutableListSequence(T* items, int count) : ListSequenceBase<T>(items, count) {}

    //копирующий конструктор
    MutableListSequence(const MutableListSequence<T>& other) : ListSequenceBase<T>(other) {}

    //clone - создать копию
    ListSequenceBase<T>* Clone() const override {
        return new MutableListSequence<T>(*this);
    }

    //методы изменения - изменяют этот объект
    void Append(T item) override {
        this->items->Append(item);
    }

    void Prepend(T item) override {
        this->items->Prepend(item);
    }

    void InsertAt(T item, int index) override {
        this->items->InsertAt(item, index);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        //получаем подсписок из LinkedList
        LinkedList<T>* subList = this->items->GetSubList(startIndex, endIndex);

        //создаём новую ListSequence на базе подсписка
        MutableListSequence<T>* result = new MutableListSequence<T>();
        delete result->items;  //удаляем пустой список
        result->items = subList;  //заменяем на подсписок

        return result;
    }

    Sequence<T>* Concat(Sequence<T>* other) const override {
        //создаём новую последовательность
        MutableListSequence<T>* result = new MutableListSequence<T>();

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