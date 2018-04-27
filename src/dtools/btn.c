#include "../hwinit/btn.h"
#include "btn.h"

void btn_read_array(u32 readVal, u32 btnArray[3]) { // readVal: to-be-read value from btn.h, btnArray: a 3 element array to store button values
    /* How does this work?
     * As you can see in ../hwinit/btn.h, the results are the pressed down buttons' values OR'd together.
     * This code checks for the bit set in the OR'd result, and sets values in an array, for an easier check in main.
     */

    /* Docs for btnArray:
     * element 0: 1 if the power button is pressed
     * element 1: 1 if VOL- is pressed
     * element 2: 1 if VOL+ is pressed
     * if the button isn't pressed, the default value is 0.
     */

    btnArray[0] = CHECK_BIT(readVal, 0);
    btnArray[1] = CHECK_BIT(readVal, 1);
    btnArray[2] = CHECK_BIT(readVal, 2);
}