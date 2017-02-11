#include <iostream>
#include <assert.h>
#include "BigNumber.h"

using namespace std;

int main()
{
    // Test your class here
    BigNumber a("-20");
    BigNumber b("-12");
    auto c = a / b;
    auto d = a % b;
    cout << a.toString() << " / " << b.toString() << " = " << c.toString() << " ... " << d.toString() << endl;
    return 0;
}