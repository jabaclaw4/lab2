#ifndef MUTABLE_LIST_SEQUENCE_H
#define MUTABLE_LIST_SEQUENCE_H

#include "ListSequenceBase.h"

//изменяемая последовательность на базе списка
template <class T>
class MutableListSequence : public ListSequenceBase<T> {
protected:
    //instance() возвращает this
    Sequence<T>* instance() override {
        return this;
    }

    ListSequenceBase<T>* CreateNew() const override {
        return new MutableListSequence<T>();
    }

public:
    //конструкторы
    //пустая последовательность
    MutableListSequence() : ListSequenceBase<T>() {}
    //создать из массива
    MutableListSequence(T* items, int count) : ListSequenceBase<T>(items, count) {}
    //копирующий конструктор
    MutableListSequence(const MutableListSequence<T>& other) : ListSequenceBase<T>(other) {}
};

#endif
