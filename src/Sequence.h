#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <stdexcept>
//virtual = "эта функция может работать по-разному в зависимости от реального типа объекта"
//Компилятор смотрит на реальный объект, а не на тип переменной
//mutable изменяет объект, immutable возвращает новый объект

//изначально у нас было только mutable но потом переделала в immutable и mutable структуры. тк методы чтения не меняют объект они будут одиннаковые
//и для immutable и для mutable => их добавим в arraysequenceBase а объекты изменения в immutable и mutable
template <class T>
class Sequence {
public:
    virtual ~Sequence() {}

    //существующие методы (чтение)
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

    //существующие методы (изменение)
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;

    //новые методы с Option (Try-семантика)

    //попытка получить первый элемент (без исключения если пусто)
    virtual Option<T> TryGetFirst() const {
        if (this->GetLength() == 0) {
            return Option<T>::None();
        }
        return Option<T>::Some(this->GetFirst());
    }

    //попытка получить последний элемент
    virtual Option<T> TryGetLast() const {
        if (this->GetLength() == 0) {
            return Option<T>::None();
        }
        return Option<T>::Some(this->GetLast());
    }

    //попытка получить элемент по индексу
    virtual Option<T> TryGet(int index) const {
        if (index < 0 || index >= this->GetLength()) {
            return Option<T>::None();
        }
        return Option<T>::Some(this->Get(index));
    }

    //найти первый элемент, удовлетворяющий условию
    virtual Option<T> TryFind(bool (*predicate)(T)) const {
        for (int i = 0; i < this->GetLength(); i++) {
            T item = this->Get(i);
            if (predicate(item)) {
                return Option<T>::Some(item);
            }
        }
        return Option<T>::None();
    }

    //найти индекс первого элемента, удовлетворяющего условию
    virtual Option<int> TryFindIndex(bool (*predicate)(T)) const {
        for (int i = 0; i < this->GetLength(); i++) {
            if (predicate(this->Get(i))) {
                return Option<int>::Some(i);
            }
        }
        return Option<int>::None();
    }

};

#endif