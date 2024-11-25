#include "base.h"

int f (int i) {
    printf (" called f\n");
    if(i < 0) {
        return - i;
    }
    else {
        return 3 * i;
    }
}

int main(void) {
    printiln(f(2));
    printiln(f(-2));
}