#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>//для исключений
//хранение данных
template <class T>
class DynamicArray {
private:
    T* data;//указатель на массив данных
    int size;//текущий размер массива
    int capacity;//выделенная память (capacity >= size)

public:
    DynamicArray(int size = 0) {//массив заданного размера
        if (size < 0) {
            throw std::invalid_argument("Size cannot be negative");
        }

        this->size = size;
        this->capacity = size;

        if (size > 0) {
            this->data = new T[size];
            //инициализация нулями
            for (int i = 0; i < size; i++) {
                this->data[i] = T();//вызов конструктора по умолчанию
            }
        } else {
            this->data = nullptr;  //пустой массив
        }
    }

    DynamicArray(T* items, int count) {//из обычного массива
        if (count < 0) {
            throw std::invalid_argument("Count cannot be negative");
        }
        if (items == nullptr && count > 0) {
            throw std::invalid_argument("Items is null but count > 0");
        }

        this->size = count;
        this->capacity = count;

        if (count > 0) {
            this->data = new T[count];
            //копируем элементы из переданного массива
            for (int i = 0; i < count; i++) {
                this->data[i] = items[i];
            }
        } else {
            this->data = nullptr;
        }
    }

//копия другого динамич массива
    DynamicArray(const DynamicArray<T>& other) {
        this->size = other.size;
        this->capacity = other.capacity;

        if (other.size > 0) {
            this->data = new T[other.capacity];

            // Копируем данные
            for (int i = 0; i < other.size; i++) {
                this->data[i] = other.data[i];
            }
        } else {
            this->data = nullptr;
        }
    }
//деструктор
    ~DynamicArray() {
        if (this->data != nullptr) {
            delete[] this->data;
            this->data = nullptr;
        }
    }


    T Get(int index) const {//получить данные по индексу
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range");
        }
        return this->data[index];
    }

    //получить размер массива
    int GetSize() const {
        return this->size;
    }

    //получить вместимость
    int GetCapacity() const {
        return this->capacity;
    }
    //установить элемент по индексу
    void Set(int index, const T& value) {
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range");
        }

        this->data[index] = value;
    }

    //изменить размер массива
    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("New size cannot be negative");
        }
        // если новый размер = текущему, ничего не делаем
        if (newSize == this->size) {
            return;
        }
        //если новый размер = 0, очищаем массив
        if (newSize == 0) {
            if (this->data != nullptr) {
                delete[] this->data;
                this->data = nullptr;
            }
            this->size = 0;
            this->capacity = 0;
            return;
        }
        //создаём новый массив
        T* newData = new T[newSize];
        //копируем данные (сколько поместится)
        int elementsToCopy = (newSize < this->size) ? newSize : this->size;
        for (int i = 0; i < elementsToCopy; i++) {
            newData[i] = this->data[i];
        }
        //если увеличили размер, инициализируем новые элементы
        for (int i = this->size; i < newSize; i++) {
            newData[i] = T();//конструктор по умолчанию
        }
        //удаляем старые данные
        if (this->data != nullptr) {
            delete[] this->data;
        }
        this->data = newData;
        this->size = newSize;
        this->capacity = newSize;
    }
};

#endif