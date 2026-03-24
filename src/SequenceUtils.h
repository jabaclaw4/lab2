#ifndef SEQUENCE_UTILS_H
#define SEQUENCE_UTILS_H

#include <iostream>
#include "Sequence.h"

//cout << seq
//выводит в формате [1, 2, 3]
template <class T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {//ostream& = ссылка на поток
    os << "[";
    for (int i = 0; i < seq.GetLength(); i++) {
        os << seq[i];
        if (i < seq.GetLength() - 1) {//везде запятая кроме последнего
            os << ", ";
        }
    }
    os << "]";
    return os;//для цепочек
}

#endif