#ifndef LIST_SEQUENCE_BASE_H
#define LIST_SEQUENCE_BASE_H

#include "Sequence.h"
#include "LinkedList.h"
#include <stdexcept>

//базовый класс с общим кодом для mutable и immutable
template <class T>
class ListSequenceBase : public Sequence<T> {
protected:
    LinkedList<T>* items;

    //конструкторы protected чтобы только наследники могут использовать
    //пустая последовательность
    ListSequenceBase() {
        this->items = new LinkedList<T>();
    }
    //создать из массива
    ListSequenceBase(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
    }
    //копирующий конструктор
    ListSequenceBase(const ListSequenceBase<T>& other) {
        this->items = new LinkedList<T>(*other.items);
    }

    //реализация добавления (общая для Mutable и Immutable)
    Sequence<T>* appendImpl(const T& elem) override {
        this->items->Append(elem);
        return this;
    }

    Sequence<T>* prependImpl(const T& elem) override {
        this->items->Prepend(elem);
        return this;
    }

    Sequence<T>* insertAtImpl(const T& elem, int index) override {
        this->items->InsertAt(elem, index);
        return this;
    }

public:
    virtual ~ListSequenceBase() {
        delete this->items;
    }

    //методы чтения - одинаковые для mutable и immutable
    //LinkedList все сам проверит
    T GetFirst() const override {
        return this->items->GetFirst();
    }

    T GetLast() const override {
        return this->items->GetLast();
    }

    T Get(int index) const override {
        return this->items->Get(index);
    }

    int GetLength() const override {
        return this->items->GetLength();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || startIndex >= this->GetLength()) {
            throw std::out_of_range("start index out of range");
        }
        if (endIndex < 0 || endIndex >= this->GetLength()) {
            throw std::out_of_range("end index out of range");
        }
        if (startIndex > endIndex) {
            throw std::invalid_argument("start index > end index");
        }

        LinkedList<T>* subList = this->items->GetSubList(startIndex, endIndex);

        ListSequenceBase<T>* result = this->CreateNew();
        delete result->items;
        result->items = subList;

        return result;
    }

    Sequence<T>* Concat(const Sequence<T>* other) const override {
        LinkedList<T>* newList = new LinkedList<T>();

        //копируем из this
        for (int i = 0; i < this->items->GetLength(); i++) {
            newList->Append(this->items->Get(i));
        }

        //копируем из other
        for (int i = 0; i < other->GetLength(); i++) {
            newList->Append(other->Get(i));
        }

        ListSequenceBase<T>* result = this->CreateNew();
        delete result->items;
        result->items = newList;

        return result;
    }

protected:
    //вспомогательная функция создать новый об
    virtual ListSequenceBase<T>* CreateNew() const = 0;
};

#endif