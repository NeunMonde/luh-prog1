/*
Compile: make weights
Run: ./weights
*/

#include "base.h"

// 1 lb = 0.45359237 kg

typedef enum unit_e {
    G,
    KG,
    T,
    LB
} Unit;

typedef struct weight_s {
    double amount;
    Unit unit;
} Weight;

Weight make_weight(double amount, Unit unit) {
    Weight weight;
    weight.amount = amount;
    weight.unit = unit;
    return weight;
}

bool test_within_weight(int line, Weight a, Weight e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.unit, e.unit);
    return x && u;
}

void print_weight(Weight w) {
    double number = round(w.amount * 100) / 100;
    printf("%.2f%", number);
    prints(" ");
    switch (w.unit) {
        case G:
            printsln("G");
            break;
        case KG:
            printsln("KG");
            break;
        case T:
            printsln("T");
            break;
        case LB:
            printsln("lbs");
            break;
    }
}

void print_weight_test() {
    print_weight(make_weight(1234, G));
    print_weight(make_weight(4.749, KG));
    print_weight(make_weight(3.1001, T));
    print_weight(make_weight(5.40006, LB));
}

// Weight, Unit -> Weight
// Convert weight to the given target unit.
Weight to_unit(Weight w, Unit target_unit) {
    double number = w.amount;
    switch(w.unit) {
        case G:
            number = w.amount / 1000;
            break;
        case T:
            number = w.amount * 1000;
            break;
        case LB:
            number = w.amount * 0.45359237;
            break;
    }
    w.unit = target_unit;
    switch (w.unit) {
        case G:
            number = number * 1000;
            break;
        case T:
            number = number / 1000;
            break;
        case LB:
            number = number / 0.45359237;
            break;
    }
    w.amount = number;
    return w;
}

void to_unit_test(void) {
    test_within_weight(__LINE__, to_unit(make_weight(1000, G), KG), make_weight(1, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1000, KG), T), make_weight(1, T), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1000000, G), T), make_weight(1, T), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1, LB), KG), make_weight(0.45359237, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(333333, G), KG), make_weight(333.333, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1000, KG), KG), make_weight(1000, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(0.01, KG), G), make_weight(10, G), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(0.01, G), KG), make_weight(0.00001, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1000, G), KG), make_weight(1, KG), 1e-6);
}

// Weight, Weight -> int
// Compares two weights. Returns 0 if the two weights are equal,
// -1 if w is smaller than v and +1 otherwise.
int compare(Weight w, Weight v) {
    w = to_unit(w, v.unit);
    if(w.amount == v.amount) {
        return 0;
    }
    else if(w.amount > v.amount) {
        return 1;
    }
    else {
        return -1;
    }
}

void compare_test(void) {
    test_equal_i(compare(make_weight(1000, G), make_weight(1, KG)), 0);
    test_equal_i(compare(make_weight(1001, G), make_weight(1, KG)), 1);
    test_equal_i(compare(make_weight(1, KG), make_weight(1, T)), -1);
    test_equal_i(compare(make_weight(1, KG), make_weight(1, LB)), 1);
    test_equal_i(compare(make_weight(1, T), make_weight(1000000, G)), 0);
    test_equal_i(compare(make_weight(0.1, KG), make_weight(1, G)), 1);
}

int main(void) {
    print_weight_test();
    to_unit_test();
    compare_test();
    return 0;
}

