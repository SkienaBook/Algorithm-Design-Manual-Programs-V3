#include <iostream.h>


int main(void) {
    long long a, b, c;

    while (cin >> a >> b) {
        if (b > a) {
            c = b - a;
        } else {
            c = a - b;
        }
        cout << c << endl;
    }

    return 0;
}
