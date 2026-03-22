#ifndef BIT_SEQUENCE_H
#define BIT_SEQUENCE_H

#include "Sequence.h"
#include <stdexcept>

//класс Bit - абстракция для одного бита
//реализуется для экономии памяти

class Bit {
private:
    bool value;

public:
    //конструкторы
    Bit() : value(false) {}
    Bit(bool val) : value(val) {}
    Bit(int val) : value(val != 0) {}

    //получить значение
    bool GetValue() const {
        return this->value;
    }
    //установить значение
    void SetValue(bool val) {
        this->value = val;
    }
    //преобразование в bool
    operator bool() const {
        return this->value;
    }
    //операторы сравнения
    bool operator==(const Bit& other) const {
        return this->value == other.value;
    }
    bool operator!=(const Bit& other) const {
        return this->value != other.value;
    }
};

//класс BitSequence - последовательность битов

class BitSequence : public Sequence<Bit> {
private:
    unsigned char* data;//массив байтов (каждый байт = 8 бит)
    int bitCount; //количество бит
    int byteCount;//количество байтов (bitCount/8 округление вверх)

    //вспомогательная функция: получить индекс байта и бита внутри байта
    void GetByteAndBitIndex(int bitIndex, int& byteIndex, int& bitInByte) const {
        byteIndex = bitIndex / 8;//номер байта
        bitInByte = bitIndex % 8;//номер бита внутри байта (0-7)
    }

    //получить бит по индексу (внутренняя функция)
    bool GetBitInternal(int index) const {
        if (index < 0 || index >= this->bitCount) {
            throw std::out_of_range("bit index out of range");
        }

        int byteIndex, bitInByte;
        GetByteAndBitIndex(index, byteIndex, bitInByte);

        //извлекаем бит: сдвигаем байт вправо на bitInByte позиций и берём младший бит
        return (this->data[byteIndex] >> bitInByte) & 1;
    }

    //установить бит по индексу (внутренняя функция)
    void SetBitInternal(int index, bool value) {
        if (index < 0 || index >= this->bitCount) {
            throw std::out_of_range("bit index out of range");
        }

        int byteIndex, bitInByte;
        GetByteAndBitIndex(index, byteIndex, bitInByte);

        if (value) {
            //установить бит в 1: побитовое ИЛИ с маской
            this->data[byteIndex] |= (1 << bitInByte);
        } else {
            //установить бит в 0: побитовое И с инвертированной маской
            this->data[byteIndex] &= ~(1 << bitInByte);
        }
    }

public:
    //конструктор: создать битовую последовательность заданной длины
    BitSequence(int length) {
        if (length < 0) {
            throw std::invalid_argument("length must be non-negative");
        }

        this->bitCount = length;
        this->byteCount = (length + 7) / 8;  //округление вверх
        //выделяем память и инициализируем нулями
        this->data = new unsigned char[this->byteCount];
        for (int i = 0; i < this->byteCount; i++) {
            this->data[i] = 0;
        }
    }

    //конструктор: создать из массива битов
    BitSequence(Bit* bits, int count) {
        if (count < 0) {
            throw std::invalid_argument("count must be non-negative");
        }

        this->bitCount = count;
        this->byteCount = (count + 7) / 8;
        this->data = new unsigned char[this->byteCount];

        //инициализируем нулями
        for (int i = 0; i < this->byteCount; i++) {
            this->data[i] = 0;
        }

        //устанавливаем биты
        for (int i = 0; i < count; i++) {
            SetBitInternal(i, bits[i].GetValue());
        }
    }

    //копирующий конструктор
    BitSequence(const BitSequence& other) {
        this->bitCount = other.bitCount;
        this->byteCount = other.byteCount;
        this->data = new unsigned char[this->byteCount];

        //копируем данные
        for (int i = 0; i < this->byteCount; i++) {
            this->data[i] = other.data[i];
        }
    }

    //деструктор
    ~BitSequence() {
        delete[] this->data;
    }

    //методы Sequence
    Bit GetFirst() const override {
        if (this->bitCount == 0) {
            throw std::out_of_range("bit sequence is empty");
        }
        return Bit(GetBitInternal(0));
    }

    Bit GetLast() const override {
        if (this->bitCount == 0) {
            throw std::out_of_range("bit sequence is empty");
        }
        return Bit(GetBitInternal(this->bitCount - 1));
    }

    Bit Get(int index) const override {
        return Bit(GetBitInternal(index));
    }

    int GetLength() const override {
        return this->bitCount;
    }

    Sequence<Bit>* Append(Bit item) override {
        BitSequence* result = new BitSequence(*this);

        int newBitCount = result->bitCount + 1;
        int newByteCount = (newBitCount + 7) / 8;
        unsigned char* newData = new unsigned char[newByteCount];

        for (int i = 0; i < result->byteCount; i++) {
            newData[i] = result->data[i];
        }

        for (int i = result->byteCount; i < newByteCount; i++) {
            newData[i] = 0;
        }

        delete[] result->data;
        result->data = newData;
        result->bitCount = newBitCount;
        result->byteCount = newByteCount;

        result->SetBitInternal(result->bitCount - 1, item.GetValue());

        return result;
    }

    Sequence<Bit>* Prepend(Bit item) override {
        BitSequence* newSeq = new BitSequence(this->bitCount + 1);
        newSeq->SetBitInternal(0, item.GetValue());

        for (int i = 0; i < this->bitCount; i++) {
            newSeq->SetBitInternal(i + 1, GetBitInternal(i));
        }

        return newSeq;
    }

    Sequence<Bit>* InsertAt(Bit item, int index) override {
        if (index < 0 || index > this->bitCount) {
            throw std::out_of_range("index out of range");
        }

        BitSequence* newSeq = new BitSequence(this->bitCount + 1);

        for (int i = 0; i < index; i++) {
            newSeq->SetBitInternal(i, GetBitInternal(i));
        }

        newSeq->SetBitInternal(index, item.GetValue());

        for (int i = index; i < this->bitCount; i++) {
            newSeq->SetBitInternal(i + 1, GetBitInternal(i));
        }

        return newSeq;
    }

    Sequence<Bit>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || startIndex >= this->bitCount) {
            throw std::out_of_range("start index out of range");
        }
        if (endIndex < 0 || endIndex >= this->bitCount) {
            throw std::out_of_range("end index out of range");
        }
        if (startIndex > endIndex) {
            throw std::invalid_argument("start index > end index");
        }
        int newLength = endIndex - startIndex + 1;
        BitSequence* result = new BitSequence(newLength);
        for (int i = 0; i < newLength; i++) {
            result->SetBitInternal(i, GetBitInternal(startIndex + i));
        }
        return result;
    }

    Sequence<Bit>* Concat(const Sequence<Bit>* other) const override {
        int newLength = this->bitCount + other->GetLength();
        BitSequence* result = new BitSequence(newLength);

        for (int i = 0; i < this->bitCount; i++) {
            result->SetBitInternal(i, GetBitInternal(i));
        }

        for (int i = 0; i < other->GetLength(); i++) {
            result->SetBitInternal(this->bitCount + i, other->Get(i).GetValue());
        }

        return result;
    }

    //побитовые операции
    //побитовое and
    BitSequence* BitwiseAnd(const BitSequence& other) const {
        if (this->bitCount != other.bitCount) {
            throw std::invalid_argument("bit sequences must have same length for AND");
        }

        BitSequence* result = new BitSequence(this->bitCount);

        //применяем AND к каждому байту
        for (int i = 0; i < this->byteCount; i++) {
            result->data[i] = this->data[i] & other.data[i];
        }

        return result;
    }

    //побитовое or
    BitSequence* BitwiseOr(const BitSequence& other) const {
        if (this->bitCount != other.bitCount) {
            throw std::invalid_argument("bit sequences must have same length for OR");
        }

        BitSequence* result = new BitSequence(this->bitCount);

        for (int i = 0; i < this->byteCount; i++) {
            result->data[i] = this->data[i] | other.data[i];
        }

        return result;
    }

    //побитовое xor
    BitSequence* BitwiseXor(const BitSequence& other) const {
        if (this->bitCount != other.bitCount) {
            throw std::invalid_argument("bit sequences must have same length for XOR");
        }

        BitSequence* result = new BitSequence(this->bitCount);

        for (int i = 0; i < this->byteCount; i++) {
            result->data[i] = this->data[i] ^ other.data[i];
        }

        return result;
    }

    //побитовое not (инверсия)
    BitSequence* BitwiseNot() const {
        BitSequence* result = new BitSequence(this->bitCount);

        for (int i = 0; i < this->byteCount; i++) {
            result->data[i] = ~this->data[i];
        }

        //обнуляем лишние биты в последнем байте
        if (this->bitCount % 8 != 0) {
            int validBits = this->bitCount % 8;
            unsigned char mask = (1 << validBits) - 1;
            result->data[this->byteCount - 1] &= mask;
        }

        return result;
    }
};

#endif