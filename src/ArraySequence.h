#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"

//класс ArraySequence - реализация Sequence на базе DynamicArray
//ArraySequence обяхан реализовать все функции из Sequence
template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items; //внутри используем DynamicArray

public:
    //создать пустую последовательность
    ArraySequence() {
        this->items = new DynamicArray<T>(0);
    }
    //создать из массива
    ArraySequence(T* items, int count) {
        this->items = new DynamicArray<T>(items, count);
    }
    //создать заданного размера
    ArraySequence(int size) {
        this->items = new DynamicArray<T>(size);
    }
    //копирующий конструктор
    ArraySequence(const ArraySequence<T>& other) {
        this->items = new DynamicArray<T>(*other.items);
    }

    ~ArraySequence() {
        delete this->items;
    }

    T GetFirst() const override {
        if (this->items->GetSize() == 0) {
            throw std::out_of_range("sequence is empty");
        }
        return this->items->Get(0);
    }

    T GetLast() const override {
        if (this->items->GetSize() == 0) {
            throw std::out_of_range("sequence is empty");
        }
        return this->items->Get(this->items->GetSize() - 1);
    }

    T Get(int index) const override {
        return this->items->Get(index);//DynamicArray сам проверит индекс
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

        //создаём новую последовательность нужного размера
        int newSize = endIndex - startIndex + 1;
        ArraySequence<T>* subSeq = new ArraySequence<T>(newSize);

        //копируем элементы
        for (int i = 0; i < newSize; i++) {
            subSeq->items->Set(i, this->items->Get(startIndex + i));
        }

        return subSeq;
    }

    int GetLength() const override {
        return this->items->GetSize();
    }

    void Append(T item) override {
        //увеличиваем размер на 1
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);

        //записываем элемент в конец
        this->items->Set(oldSize, item);
    }

    void Prepend(T item) override {
        //увеличиваем размер на 1
        int oldSize = this->items->GetSize();
        this->items->Resize(oldSize + 1);

        //сдвигаем все элементы вправо
        for (int i = oldSize; i > 0; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        //записываем элемент в начало
        this->items->Set(0, item);
    }
//вставить элемент на index
    void InsertAt(T item, int index) override {
        int size = this->items->GetSize();
        if (index < 0 || index > size) {
            throw std::out_of_range("index out of range");
        }
        //частные случаи
        if (index == 0) {
            Prepend(item);
            return;
        }

        if (index == size) {
            Append(item);
            return;
        }

        //общий случай: вставка в середину
        //увеличиваем размер
        this->items->Resize(size + 1);

        //сдвигаем элементы вправо начиная с index
        for (int i = size; i > index; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        //записываем элемент
        this->items->Set(index, item);
    }
//объединить две последовательности
    Sequence<T>* Concat(Sequence<T>* other) const override {
        //создаём новую последовательность
        int newSize = this->GetLength() + other->GetLength();
        ArraySequence<T>* result = new ArraySequence<T>(newSize);

        //копируем элементы из текущей последовательности
        for (int i = 0; i < this->GetLength(); i++) {
            result->items->Set(i, this->items->Get(i));
        }
        //копируем элементы из другой последовательности
        for (int i = 0; i < other->GetLength(); i++) {
            result->items->Set(this->GetLength() + i, other->Get(i));
        }

        return result;
    }
};

#endif