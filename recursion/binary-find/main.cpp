//
// Created by liu on 2017/2/20.
//

#include <iostream>

// The numbers to be found
const int array[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

int binary_find(int n, int high, int low)
{

}

int main()
{
    int a, result;
    std::cout << "Enter the integer which you want to search:";
    std::cin >> a;
    result = binary_find(a, 14, 0);
    if (result == -1)
        std::cout << "Not found.";
    else
        std::cout << "The number " << a << " is at " << result;
    return 0;
}
