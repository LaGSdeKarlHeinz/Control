#include <iostream>

typedef void(*callbackType)(uint8_t, uint8_t*, uint32_t);

template<typename T>
class B {
public:
    B(void (T::*func)(), T* tptr) : functionT(func), tptr(tptr) {}
    B(void (*func)()) : function(func), tptr(nullptr) {}
    void work() {
        /*T t; // debug
        int result = (t.*function)(2); // debug
        int result2 = ((*tptr).*function)(2); // debug
        int result3 = (tptr->*function)(2); // debug */
        //std::cout << "R = " <<  << std::endl;
        ((tptr)?(tptr->*functionT)():function());
    }
private:
    void (T::*functionT)();
    void (*function)();
    T* tptr;
};

class A {
public:
    A();
    void method() {
        std::cout << "miaou" << std::endl;
        //return arg*x;
    }
    void work() {
        b.work();
    }
private:
    B<A> b;
    int x;
};

A::A() : b(&A::method, this), x(2) {}

int main() {
    A myA;
    myA.work();

    return 0;
}
