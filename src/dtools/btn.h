#ifndef DTOOLS_BTN_H

#ifndef CHECK_BIT
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#endif

void btn_read_array(u32 readVal, u32 btnArray[3]);

#endif