#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdexcept>
#include <iostream>
#include "ResultInfo.h"  //✅ ДОБАВИЛИ

//базовый абстрактный класс для всех последовательностей
//virtual = функция может работать по-разному в зависимости от реального типа объекта
//= 0 означает "чисто виртуальная" - ОБЯЗАТЕЛЬНО должна быть реализована в наследниках
//const после функции = функция НЕ изменяет объект (можно вызывать на константных объектах)

template <class T>
class Sequence {
public:
    virtual ~Sequence() {}

    //===== МЕТОДЫ ЧТЕНИЯ (чисто виртуальные) =====

    //получить первый элемент (бросает исключение если пусто)
    virtual T GetFirst() const = 0;

    //получить последний элемент (бросает исключение если пусто)
    virtual T GetLast() const = 0;

    //получить элемент по индексу (бросает исключение если неверный индекс)
    virtual T Get(int index) const = 0;

    //получить длину последовательности
    virtual int GetLength() const = 0;

    //получить подпоследовательность от startIndex до endIndex (включительно)
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    //===== МЕТОДЫ ИЗМЕНЕНИЯ (чисто виртуальные) =====
    //✅ ОСТАВЛЯЕМ void (БЕЗ ЦЕПОЧЕК!)

    //добавить элемент в конец
    virtual void Append(T item) = 0;

    //добавить элемент в начало
    virtual void Prepend(T item) = 0;

    //вставить элемент на позицию index
    virtual void InsertAt(T item, int index) = 0;

    //объединить с другой последовательностью
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;

    //===== TRY-МЕТОДЫ (возвращают ResultInfo вместо исключений) =====

    //попытка получить первый элемент (без исключения если пусто)
    virtual ResultInfo<T> TryGetFirst() const {
        if (this->GetLength() == 0) {
            return ResultInfo<T>::Failure("Sequence is empty");
        }
        return ResultInfo<T>::Success(this->GetFirst());
    }

    //попытка получить последний элемент (без исключения если пусто)
    virtual ResultInfo<T> TryGetLast() const {
        if (this->GetLength() == 0) {
            return ResultInfo<T>::Failure("Sequence is empty");
        }
        return ResultInfo<T>::Success(this->GetLast());
    }

    //попытка получить элемент по индексу (без исключения если неверный индекс)
    virtual ResultInfo<T> TryGet(int index) const {
        if (index < 0 || index >= this->GetLength()) {
            return ResultInfo<T>::Failure("Index out of range");
        }
        return ResultInfo<T>::Success(this->Get(index));
    }

    //найти первый элемент, удовлетворяющий условию (без исключения если не найден)
    virtual ResultInfo<T> TryFind(bool (*predicate)(T)) const {
        for (int i = 0; i < this->GetLength(); i++) {
            T item = this->Get(i);
            if (predicate(item)) {
                return ResultInfo<T>::Success(item);
            }
        }
        return ResultInfo<T>::Failure("Element not found");
    }

    //найти индекс первого элемента, удовлетворяющего условию (без исключения если не найден)
    virtual ResultInfo<int> TryFindIndex(bool (*predicate)(T)) const {
        for (int i = 0; i < this->GetLength(); i++) {
            if (predicate(this->Get(i))) {
                return ResultInfo<int>::Success(i);
            }
        }
        return ResultInfo<int>::Failure("Element not found");
    }

    //===== ПЕРЕГРУЗКА ОПЕРАТОРОВ =====

    //оператор доступа по индексу: seq[i]
    //позволяет писать seq[5] вместо seq->Get(5)
    virtual T operator[](int index) const {
        return this->Get(index);
    }

    //оператор сравнения: seq1 == seq2
    //возвращает true если последовательности одинаковые
    virtual bool operator==(const Sequence<T>& other) const {
        //разная длина -> не равны
        if (this->GetLength() != other.GetLength()) {
            return false;
        }
        //сравниваем каждый элемент
        for (int i = 0; i < this->GetLength(); i++) {
            if (this->Get(i) != other.Get(i)) {
                return false;
            }
        }
        return true;
    }

    //оператор неравенства: seq1 != seq2
    virtual bool operator!=(const Sequence<T>& other) const {
        return !(*this == other);
    }

    //оператор конкатенации: seq1 + seq2
    //возвращает новую последовательность [элементы seq1, элементы seq2]
    virtual Sequence<T>* operator+(const Sequence<T>& other) const {
        //const_cast нужен потому что Concat принимает неконстантный указатель
        return this->Concat(const_cast<Sequence<T>*>(&other));
    }
};

//===== ОПЕРАТОР ВЫВОДА В ПОТОК (вне класса!) =====

//оператор вывода: cout << seq
//выводит последовательность в формате [1, 2, 3]
template <class T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
    os << "[";
    for (int i = 0; i < seq.GetLength(); i++) {
        os << seq[i];
        if (i < seq.GetLength() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif