/*
 * Compile:         make X
 * Run:             ./X
 * Compile and Run: make X && ./X
 */
#include "base.h" // prog1lib

// define constants
const int NORMAL_PRICE = 100;

const int THRESHOLD_ONE = 10;
const int PRICE_REDUCTION_ONE = 90;

const int THRESHOLD_TWO = 50;   
const int PRICE_REDUCTION_TWO = 75;

const int SHIPPING_COST = 500;
const int NO_SHIPPING_THRESHOLD = 2000;



// write function price
/*
This function calculates the total price based on the quantity of items being bought. 
The function will also remove shipping costs if the total price is above a certain threshold.
@param Quantity of the item (Int)
@return Total Price (Int)
*/
int price (int itemQuantity) {
    // Possibility of creating a helper function to add shipping cost instead of calling the function in every case
    int priceTotal;

    if (itemQuantity <= 0) {
        priceTotal = 0;
        return priceTotal;
    }

    else if (itemQuantity < THRESHOLD_ONE) {
        priceTotal = itemQuantity * NORMAL_PRICE;
        if (priceTotal < NO_SHIPPING_THRESHOLD) {  // in case constants get changed
            priceTotal += SHIPPING_COST;
        }
        return priceTotal;
    }

    else if (itemQuantity < THRESHOLD_TWO) {
        priceTotal = itemQuantity * PRICE_REDUCTION_ONE;
        if (priceTotal < NO_SHIPPING_THRESHOLD) {
            priceTotal += SHIPPING_COST;
        }
        return priceTotal;
    }

    else if (itemQuantity >= THRESHOLD_TWO) {
        priceTotal = itemQuantity * PRICE_REDUCTION_TWO;
        if (priceTotal < NO_SHIPPING_THRESHOLD) {
            priceTotal += SHIPPING_COST;
        }
        return priceTotal;
    }

    return 0;
}

// write function price_test
// test returned values of price using test_equal_i
static void price_test () {
    test_equal_i(price(-1),0);
    test_equal_i(price(0),0);
    test_equal_i(price(1),600);
    test_equal_i(price(5),1000);
    test_equal_i(price(10),1400);
    test_equal_i(price(22),2480);
    test_equal_i(price(50),3750);
    test_equal_i(price(100),7500);
}

int main(void) {
    // call price_test function
    price_test();

    int quantity;
    printf("Enter quantity of items: ");
    scanf("%d", &quantity);
    int priceTotal = price(quantity);
    printf("Total price: %d ct\n", priceTotal);

    return 0;
}
