#include <iostream>

unsigned long gcd(unsigned long a, unsigned long b)
{

}

int main()
{
    int m, n, factor;
    std::cout << "Input two integers(m>n):";
    std::cin >> m >> n;
    if (m > n)
        factor = gcd(m, n);
    else
        factor = gcd(n, m);
    std::cout << "The greatest common divisor of " << m << " and " << n << " is " << factor;
    return 0;
}