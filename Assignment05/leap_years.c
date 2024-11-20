#include "base.h"

/*Return the number of days in the given year.A leap year has 366 days, a
 non-leap year has 365 days.The input represents any year A. D. as an integer, the
 return value is the number of days.*/
int number_of_days (int year) {
    bool multiple_of_four = false;
    bool multiple_of_hundred = false;
    bool multiple_of_fourhundred = false;
    //Leap Years are any year that can be exactly divided by 4
    if (year % 4 == 0){
        multiple_of_four = true;
    }
    //except if it can be exactly divided by 100, then it isn't
    if (year % 100 == 0){
        multiple_of_hundred = true;
    }
    //except if it can be exactly divided by 400, then it is
    if (year % 400 == 0){
        multiple_of_fourhundred = true;
    }
    if (!multiple_of_four == true || multiple_of_hundred == true && !multiple_of_fourhundred == true) {
        return 365;
    }
    else {
        return 366;
    }
}

int main(void) {
    test_equal_i(number_of_days(3), 365);
    test_equal_i(number_of_days(4), 366);
    test_equal_i(number_of_days(100), 365);
    test_equal_i(number_of_days(400), 366);
}
