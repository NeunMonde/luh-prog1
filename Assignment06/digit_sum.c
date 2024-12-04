#include "base.h"

/*
Diese Funktion berechnet die (alternierende) Quersumme einer Zahl
@param1 Zahl aus der die Quersumme berechnet werden soll
@param2 Boolean, der zwischen normaler und alternierender Quersumme unterscheidet
@return (alternierende) Quersumme der Zahl
*/
int digit_sum(unsigned number, bool alternating) {
    // left in due to weird behavior of "unsigned number"
    number = abs(number);

    int num_length = 0;
    if (number == 0) {
        num_length = 1;
    }
    else {
        num_length = (int)log10(number) + 1;
    };
    
    int num_array[num_length];
    for (int i = 1; i <= num_length; i++) {
        num_array[num_length - i] = number % 10;
        number /= 10;
    };

    int sum = 0;
    for (int i = 0; i < num_length; i++) {
        if (alternating) {
            if (i % 2 == 0) {
                sum += num_array[i];
            } else {
                sum += -num_array[i];
            }
        } else {
            sum += num_array[i];
        }
    };
    return sum;
}


bool divisible_by_eleven(unsigned number) {
    if(digit_sum(number, true) == 0){
        return true;
    }
    else{
        while (number >= 11) {
            number += -11;
        }
        return (number == 0);
    }
}

void digit_sum_test() {
    test_equal_i(digit_sum(10, false), 1);
    test_equal_i(digit_sum(333, false), 9);
    test_equal_i(digit_sum(-1234, false), 10);
    test_equal_i(digit_sum(0, false), 0);
    test_equal_i(digit_sum(14072000, false), 14);
    test_equal_i(digit_sum(10, true), 1);
    test_equal_i(digit_sum(333, true), 3);
    test_equal_i(digit_sum(-1234, true), -2);
    test_equal_i(digit_sum(567512, true), 0);
    test_equal_i(digit_sum(0, true), 0);
    test_equal_i(digit_sum(11, true), 0);
    test_equal_i(digit_sum(121, true), 0);
    test_equal_i(digit_sum(6969, true), -6);

    test_equal_i(divisible_by_eleven(12), false);
    test_equal_i(divisible_by_eleven(11), true);
    test_equal_i(divisible_by_eleven(759), true);
    test_equal_i(divisible_by_eleven(0), true);
    test_equal_i(divisible_by_eleven(-11), true);
    test_equal_i(divisible_by_eleven(-12), false);
}

int main(void) {
    digit_sum_test();
    return 0;
}
