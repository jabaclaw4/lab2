#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"

//класс ListSequence - реализация Sequence на базе LinkedList
template <class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;

public:
//пустая последть
    ListSequence() {
        this->items = new LinkedList<T>();
    }

    //создать из массива
    ListSequence(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
    }

    //копирующий конструктор
    ListSequence(const ListSequence<T>& other) {
        this->items = new LinkedList<T>(*other.items);
    }

    ~ListSequence() {
        delete this->items;
    }
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

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        //получаем подсписок из LinkedList
        LinkedList<T>* subList = this->items->GetSubList(startIndex, endIndex);

        //создаём новую ListSequence на базе подсписка
        ListSequence<T>* result = new ListSequence<T>();
        delete result->items;//удаляем пустой список
        result->items = subList;//заменяем на подсписок

        return result;
    }

    int GetLength() const override {
        return this->items->GetLength();
    }

    void Append(T item) override {
        this->items->Append(item);
    }

    void Prepend(T item) override {
        this->items->Prepend(item);
    }

    void InsertAt(T item, int index) override {
        this->items->InsertAt(item, index);
    }

    Sequence<T>* Concat(Sequence<T>* other) const override {
        //создаём новую последовательность
        ListSequence<T>* result = new ListSequence<T>();

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