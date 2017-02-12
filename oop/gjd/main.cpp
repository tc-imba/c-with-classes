#include <iostream>
#include <assert.h>
#include "BigNumber.h"

using namespace std;

int main()
{
    // Test your class here
    BigNumber a("0");
    BigNumber b("0");
    auto c = a + b;
    auto d = a - b;
    cout << a.toString() << " / " << b.toString() << " = " << c.toString() << " ... " << d.toString() << endl;
    return 0;
}