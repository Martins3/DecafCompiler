#include <iostream>
using namespace std;
class A{
public:
    static int s;
    int ns;

};

class B : public A{

};

int A::s = 12;

int main(){
//    REOPEN_READ
//   REOPEN_WRITE

    cout << A::s << endl;
    cout << B::s << endl;
    B::s = 123;
    cout << A::s << endl;
    cout << B::s << endl;

    return 0;
}
