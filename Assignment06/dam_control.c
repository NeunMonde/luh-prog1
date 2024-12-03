#include "base.h"

enum water_level {
    Fehler_im_Wasserstandssensor,
    Ausgeschaltet,
    Eine_Pumpe,
    Zwei_Pumpen,
    Notfallventil
};

typedef int water_level;

const water_level height1 = 20;
const water_level height2 = 40;
const water_level height3 = 67.5;

int dam_control(double water_level) {
    if (0 <= water_level && water_level < 20) {return Ausgeschaltet;}
    else if (20 <= water_level && water_level < 40) {return Eine_Pumpe;}
    else if (40 <= water_level && water_level < 67.5) {return Zwei_Pumpen;}
    else if (67.5 <= water_level) {return Notfallventil;}
    return Fehler_im_Wasserstandssensor;
}

int main(void){
    test_equal_i(dam_control(-10), Fehler_im_Wasserstandssensor);
    test_equal_i(dam_control(10), Ausgeschaltet);
    test_equal_i(dam_control(20), Eine_Pumpe);
    test_equal_i(dam_control(30), Eine_Pumpe);
    test_equal_i(dam_control(40), Zwei_Pumpen);
    test_equal_i(dam_control(50), Zwei_Pumpen);
    test_equal_i(dam_control(60), Zwei_Pumpen);
    test_equal_i(dam_control(67.5), Notfallventil);
    test_equal_i(dam_control(70), Notfallventil);
}
