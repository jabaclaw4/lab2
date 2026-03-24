#ifndef IMMUTABLE_LIST_SEQUENCE_H
#define IMMUTABLE_LIST_SEQUENCE_H

#include "ListSequenceBase.h"

//неизменяемая последовательность на базе списка
template <class T>
class ImmutableListSequence : public ListSequenceBase<T> {
protected:
    //instance() возвращает копию
    Sequence<T>* instance() override {
        return new ImmutableListSequence<T>(*this);
    }

    ListSequenceBase<T>* CreateNew() const override {
        return new ImmutableListSequence<T>();
    }

public:
    //конструкторы
    //пустая последовательность
    ImmutableListSequence() : ListSequenceBase<T>() {}
    //создать из массива
    ImmutableListSequence(T* items, int count) : ListSequenceBase<T>(items, count) {}
    //копирующий конструктор
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequenceBase<T>(other) {}
};

#endif