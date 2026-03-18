#ifndef RESULT_INFO_H
#define RESULT_INFO_H

#include <stdexcept>

//монада для безопасной обработки ошибок
template <class T>
class ResultInfo {
private:
    bool isSuccess;//успех или ошибка
    T value;//значение если успех
    const char* errorMessage;//сообщение если ошибка

    //приватный конструктор чтобы можно было создавать без ошибок
    ResultInfo(bool success, T val, const char* error)
            : isSuccess(success), value(val), errorMessage(error) {}

public:
    //создать успешный результат
    static ResultInfo<T> Success(T val) {
        return ResultInfo<T>(true, val, nullptr);
    }

    //создать ошибку
    static ResultInfo<T> Failure(const char* error) {
        return ResultInfo<T>(false, T(), error);
    }

    bool IsSuccess() const {
        return isSuccess;
    }

    bool IsFailure() const {
        return !isSuccess;
    }

    //получить значение (бросает исключение если ошибка)
    T GetValue() const {
        if (!isSuccess) {
            throw std::runtime_error(errorMessage);
        }
        return value;
    }

    //получить значение или значение по умолчанию
    T GetValueOrDefault(T defaultValue) const {
        return isSuccess ? value : defaultValue;
    }

    //получить сообщение об ошибке
    const char* GetError() const {
        return errorMessage;
    }

    //===== МОНАДИЧЕСКИЕ ОПЕРАЦИИ =====

    //Map: применить функцию к значению (если успех)
    //T -> U
    template<class U>
    ResultInfo<U> Map(U (*func)(T)) const {
        if (isSuccess) {
            return ResultInfo<U>::Success(func(value));
        } else {
            return ResultInfo<U>::Failure(errorMessage);
        }
    }

    //FlatMap: применить функцию, возвращающую ResultInfo
    //T -> ResultInfo<U>
    template<class U>
    ResultInfo<U> FlatMap(ResultInfo<U> (*func)(T)) const {
        if (isSuccess) {
            return func(value);
        } else {
            return ResultInfo<U>::Failure(errorMessage);
        }
    }

    //Filter: проверить условие
    ResultInfo<T> Filter(bool (*predicate)(T), const char* errorMsg) const {
        if (!isSuccess) {
            return *this;  //уже ошибка, возвращаем как есть
        }
        if (predicate(value)) {
            return *this;  //условие выполнено
        } else {
            return ResultInfo<T>::Failure(errorMsg);  //условие не выполнено
        }
    }

    //Recover: восстановление из ошибки
    ResultInfo<T> Recover(T (*recoveryFunc)(const char*)) const {
        if (isSuccess) {
            return *this;
        } else {
            return ResultInfo<T>::Success(recoveryFunc(errorMessage));
        }
    }

    //Match: обработка обоих случаев (успех и ошибка)
    void Match(void (*onSuccess)(T), void (*onFailure)(const char*)) const {
        if (isSuccess) {
            onSuccess(value);
        } else {
            onFailure(errorMessage);
        }
    }

    //===== ДОПОЛНИТЕЛЬНЫЕ УДОБСТВА =====

    //оператор bool для if (result) чтобы использовать ResultInfo с if
    explicit operator bool() const {
        return isSuccess;
    }
};

#endif