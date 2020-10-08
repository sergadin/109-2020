#include <iostream>
#include <string>
#include "vector_clock.h"

int main(){
    try{
        vector_clock x(10, 1);
        x.print_vector_clock();
        vector_clock y(10, 2);
        y.print_vector_clock();
        x.sign();
        x.print_vector_clock();
        y.sign();
        y.print_vector_clock();
        x.message(y);
        x.print_vector_clock();
        bool a = (y < x);
        std::cout << a << std::endl;
    }
    catch(error_vector_clock &err){
        std::cout << "Ошибка: " << err.get_reason() << std::endl;
    }
}
