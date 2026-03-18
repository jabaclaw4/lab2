#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>
//хранение данных
//T - любой тип чтобы не писать одно и то же для разных типов данных
//снаружи пользователь видит одинаковый интерфейс также есть одинаковый вызов но разная реализация функций
template <class T>
class Node {
public:
    T data;  //данные узла
    Node<T>* next;//указатель на следующий узел

    Node(T data, Node<T>* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

template <class T>
class LinkedList {
private:
    Node<T>* head;//указатель на первый узел
    Node<T>* tail; //указатель на последний узел
    int length; //количество элементов

public:
    //создать пустой список
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }

    //создать из массива
    LinkedList(T* items, int count) {
        if (count < 0) {
            throw std::invalid_argument("Count cannot be negative");
        }
        if (items == nullptr && count > 0) {
            throw std::invalid_argument("Items is null but count > 0");
        }

        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
        for (int i = 0; i < count; i++) {
            Append(items[i]);
        }
    }

    //копирующий конструктор
    LinkedList(const LinkedList<T>& other) {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
        Node<T>* current = other.head;
        while (current != nullptr) {
            Append(current->data);
            current = current->next;
        }
    }

    ~LinkedList() {
        Node<T>* current = this->head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
    //получить первый элемент
    T GetFirst() const {
        if (this->length == 0) {
            throw std::out_of_range("List is empty");
        }
        return this->head->data;
    }

    //получить последний элемент
    T GetLast() const {
        if (this->length == 0) {
            throw std::out_of_range("List is empty");
        }
        return this->tail->data;
    }

    //получить элемент по индексу
    T Get(int index) const {
        if (index < 0 || index >= this->length) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    //получить подсписок (от startIndex до endIndex включительно)
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        // Проверки
        if (startIndex < 0 || startIndex >= this->length) {
            throw std::out_of_range("Start index out of range");
        }
        if (endIndex < 0 || endIndex >= this->length) {
            throw std::out_of_range("End index out of range");
        }
        if (startIndex > endIndex) {
            throw std::invalid_argument("Start index > end index");
        }

        LinkedList<T>* subList = new LinkedList<T>();

        //идём до startIndex
        Node<T>* current = this->head;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        }
        //копируем элементы от startIndex до endIndex
        for (int i = startIndex; i <= endIndex; i++) {
            subList->Append(current->data);
            current = current->next;
        }

        return subList;
    }
    //получить длину списка
    int GetLength() const {
        return this->length;
    }

    //добавить элемент в конец
    void Append(T item) {
        Node<T>* newNode = new Node<T>(item);

        if (this->length == 0) {
            //список пуст - новый узел и первый, и последний
            this->head = newNode;
            this->tail = newNode;
        } else {
            //добавляем в конец
            this->tail->next = newNode;
            this->tail = newNode;
        }

        this->length++;
    }

    //добавить элемент в начало
    void Prepend(T item) {
        Node<T>* newNode = new Node<T>(item, this->head);

        if (this->length == 0) {
            //список пуст
            this->head = newNode;
            this->tail = newNode;
        } else {
            //новый узел становится первым
            this->head = newNode;
        }
        this->length++;
    }

    //вставить элемент на позицию index
    void InsertAt(T item, int index) {
        //проверки
        if (index < 0 || index > this->length) {
            throw std::out_of_range("Index out of range");
        }
        //частные случаи
        if (index == 0) {
            Prepend(item);
            return;
        }

        if (index == this->length) {
            Append(item);
            return;
        }
        // Общий случай: вставка в середину
        // Идём до узла ПЕРЕД позицией вставки
        Node<T>* current = this->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        // Вставляем новый узел между current и current->next
        Node<T>* newNode = new Node<T>(item, current->next);
        current->next = newNode;

        this->length++;
    }

    //объединить два списка
    LinkedList<T>* Concat(LinkedList<T>* other) const {
        LinkedList<T>* result = new LinkedList<T>();
        //копируем элементы из текущего списка
        Node<T>* current = this->head;
        while (current != nullptr) {
            result->Append(current->data);
            current = current->next;
        }
        //копируем элементы из другого списка
        current = other->head;
        while (current != nullptr) {
            result->Append(current->data);
            current = current->next;
        }

        return result;
    }
};

#endif