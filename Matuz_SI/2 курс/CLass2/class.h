#include <iostream>
using namespace std;
/*Создание векторных часов размерности N для процесса с номером K.
1) Подпись локального события.
2) Подпись события, соответсвующего получению сообщения с меткой M.

Сравнение двух меток.
Запрет вызова конструктора без парамеров*/

int Max2(int a, int b);

////////////////////
class  VectorClock{
private:
    int indexK_;
    int dimN_;
    unsigned int *data_;
    VectorClock();
public:
    VectorClock(int dimension, int index);
    ~VectorClock();
    void LocalEvent();

    void EventMessage(const VectorClock process);


    void print();
    friend bool operator<(const VectorClock& left, const VectorClock& right);

};


class UserException {
private:
    int code_;
    string message_;
public:
    UserException(int code, string message);
    string message() const;
    int code() const;
};
