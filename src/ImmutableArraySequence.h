#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequenceBase.h"

//неизменяемая последовательность на базе массива
template <class T>
class ImmutableArraySequence : public ArraySequenceBase<T> {
protected:
    //instance() возвращает копию
    Sequence<T>* instance() override {
        return new ImmutableArraySequence<T>(*this);
    }

    ArraySequenceBase<T>* CreateNew(int size) const override {
        return new ImmutableArraySequence<T>(size);
    }

public:
    //конструкторы
    ImmutableArraySequence() : ArraySequenceBase<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequenceBase<T>(items, count) {}
    ImmutableArraySequence(int size) : ArraySequenceBase<T>(size) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequenceBase<T>(other) {}
};

#endif