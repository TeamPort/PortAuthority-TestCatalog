
#include <iostream>

int fib(unsigned long long n) {
    if (n < 2) return n;
    
    return fib(n - 1) + fib(n - 2);
}

int main() {
    std::cout << fib(43) << std::endl;
}

