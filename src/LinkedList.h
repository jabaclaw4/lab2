#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>

// ═══════════════════════════════════════════════════════════
// УЗЕЛ СПИСКА (Node)
// ═══════════════════════════════════════════════════════════

template <class T>
class Node {
public:
    T data;           // Данные узла
    Node<T>* next;    // Указатель на следующий узел

    // Конструктор
    Node(T data, Node<T>* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

// ═══════════════════════════════════════════════════════════
// СВЯЗНЫЙ СПИСОК (LinkedList)
// ═══════════════════════════════════════════════════════════

template <class T>
class LinkedList {
private:
    Node<T>* head;  // Указатель на первый узел
    Node<T>* tail;  // Указатель на последний узел
    int length;     // Количество элементов

public:
    // ═══════════════════════════════════════════════════════
    // КОНСТРУКТОРЫ
    // ═══════════════════════════════════════════════════════

    // Создать пустой список
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }

    // Создать из массива
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

        // Добавляем элементы по одному
        for (int i = 0; i < count; i++) {
            Append(items[i]);
        }
    }

    // Копирующий конструктор
    LinkedList(const LinkedList<T>& other) {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;

        // Копируем все элементы
        Node<T>* current = other.head;
        while (current != nullptr) {
            Append(current->data);
            current = current->next;
        }
    }

    // ═══════════════════════════════════════════════════════
    // ДЕСТРУКТОР
    // ═══════════════════════════════════════════════════════

    ~LinkedList() {
        // Удаляем все узлы
        Node<T>* current = this->head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // ═══════════════════════════════════════════════════════
    // ПОЛУЧЕНИЕ ДАННЫХ
    // ═══════════════════════════════════════════════════════

    // Получить первый элемент
    T GetFirst() const {
        if (this->length == 0) {
            throw std::out_of_range("List is empty");
        }
        return this->head->data;
    }

    // Получить последний элемент
    T GetLast() const {
        if (this->length == 0) {
            throw std::out_of_range("List is empty");
        }
        return this->tail->data;
    }

    // Получить элемент по индексу
    T Get(int index) const {
        if (index < 0 || index >= this->length) {
            throw std::out_of_range("Index out of range");
        }

        // Идём по списку до нужного индекса
        Node<T>* current = this->head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    // Получить подсписок (от startIndex до endIndex включительно)
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

        // Идём до startIndex
        Node<T>* current = this->head;
        for (int i = 0; i < startIndex; i++) {
            current = current->next;
        }

        // Копируем элементы от startIndex до endIndex
        for (int i = startIndex; i <= endIndex; i++) {
            subList->Append(current->data);
            current = current->next;
        }

        return subList;
    }

    // Получить длину списка
    int GetLength() const {
        return this->length;
    }

    // ═══════════════════════════════════════════════════════
    // ИЗМЕНЕНИЕ ДАННЫХ
    // ═══════════════════════════════════════════════════════

    // Добавить элемент в конец
    void Append(T item) {
        Node<T>* newNode = new Node<T>(item);

        if (this->length == 0) {
            // Список пуст - новый узел и первый, и последний
            this->head = newNode;
            this->tail = newNode;
        } else {
            // Добавляем в конец
            this->tail->next = newNode;
            this->tail = newNode;
        }

        this->length++;
    }

    // Добавить элемент в начало
    void Prepend(T item) {
        Node<T>* newNode = new Node<T>(item, this->head);

        if (this->length == 0) {
            // Список пуст
            this->head = newNode;
            this->tail = newNode;
        } else {
            // Новый узел становится первым
            this->head = newNode;
        }

        this->length++;
    }

    // Вставить элемент на позицию index
    void InsertAt(T item, int index) {
        // Проверки
        if (index < 0 || index > this->length) {
            throw std::out_of_range("Index out of range");
        }

        // Частные случаи
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

    // Объединить два списка (concat)
    LinkedList<T>* Concat(LinkedList<T>* other) const {
        LinkedList<T>* result = new LinkedList<T>();

        // Копируем элементы из текущего списка
        Node<T>* current = this->head;
        while (current != nullptr) {
            result->Append(current->data);
            current = current->next;
        }

        // Копируем элементы из другого списка
        current = other->head;
        while (current != nullptr) {
            result->Append(current->data);
            current = current->next;
        }

        return result;
    }
};

#endif // LINKED_LIST_H