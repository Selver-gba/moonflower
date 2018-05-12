#include "utils.h"
#include "hwinit.h"
#include "timers.h"
#include "lib/printk.h"
#include "display/video_fb.h"

#include <stdlib.h>

#include "fuse.h"
#include "hwinit/btn.h"
#include "hwinit/i2c.h"

#include "dtools/btn.h"

#define XVERSION 1

u32 *lfb_base;
volatile void *gpio_loc = (u32 *)0x6000d000;

static void shutdown_using_pmic() // code from rajkosto/biskeydump
{
    const u8 MAX77620_I2C_PERIPH = I2C_5;
    const u8 MAX77620_I2C_ADDR = 0x3C;

    const u8 MAX77620_REG_ONOFFCNFG1 = 0x41;
    //const u8 MAX77620_REG_ONOFFCNFG2 = 0x42;

    //const u8 MAX77620_ONOFFCNFG1_SFT_RST = 1u << 7;
    const u8 MAX77620_ONOFFCNFG1_PWR_OFF = 1u << 1;

    u8 regVal = i2c_recv_byte(MAX77620_I2C_PERIPH, MAX77620_I2C_ADDR, MAX77620_REG_ONOFFCNFG1);
    regVal |= MAX77620_ONOFFCNFG1_PWR_OFF;
    i2c_send_byte(MAX77620_I2C_PERIPH, MAX77620_I2C_ADDR, MAX77620_REG_ONOFFCNFG1, regVal);
}

// --- MISC. RENDERING ---

void screen_reset() {
    video_init(lfb_base);
}

void render_header() {
    printk("                                         ,---.,--.\n        ,--,--,--. ,---.  ,---. ,--,--, /  .-'|  | ,---. ,--.   ,--. ,---. ,--.--. \n        |        || .-. || .-. ||      \\|  `-,|  || .-. ||  |.'.|  || .-. :|  .--'\n        |  |  |  |' '-' '' '-' '|  ||  ||  .-'|  |' '-' '|   .'.   |\\   --.|  |\n        `--`--`--' `---'  `---' `--''--'`--'  `--' `---' '--'   '--' `----'`--'\n");
    printk("                                            v%d\n\n", XVERSION);
}

void render_footer() {
    printk("\n                     fusee gelee by @ktemkin, moonflower by @skiilaa\n");
}

// --- FUSE ---

void fuse_render() {
    // don't worry, i didn't type these in by hand.
    printk("FUSE_PRODUCTION_MODE: %08x\n", FUSE_CHIP_REGS->FUSE_PRODUCTION_MODE);
    printk("FUSE_SKU_INFO: %08x\n", FUSE_CHIP_REGS->FUSE_SKU_INFO);
    printk("FUSE_CPU_SPEEDO_0: %08x\n", FUSE_CHIP_REGS->FUSE_CPU_SPEEDO_0);
    printk("FUSE_CPU_IDDQ: %08x\n", FUSE_CHIP_REGS->FUSE_CPU_IDDQ);
    printk("FUSE_FT_REV: %08x\n", FUSE_CHIP_REGS->FUSE_FT_REV);
    printk("FUSE_CPU_SPEEDO_1: %08x\n", FUSE_CHIP_REGS->FUSE_CPU_SPEEDO_1);
    printk("FUSE_CPU_SPEEDO_2: %08x\n", FUSE_CHIP_REGS->FUSE_CPU_SPEEDO_2);
    printk("FUSE_SOC_SPEEDO_0: %08x\n", FUSE_CHIP_REGS->FUSE_SOC_SPEEDO_0);
    printk("FUSE_SOC_SPEEDO_1: %08x\n", FUSE_CHIP_REGS->FUSE_SOC_SPEEDO_1);
    printk("FUSE_SOC_SPEEDO_2: %08x\n", FUSE_CHIP_REGS->FUSE_SOC_SPEEDO_2);
    printk("FUSE_SOC_IDDQ: %08x\n", FUSE_CHIP_REGS->FUSE_SOC_IDDQ);
    printk("FUSE_FA: %08x\n", FUSE_CHIP_REGS->FUSE_FA);
    printk("FUSE_PUBLIC_KEY 0-3: %08x %08x %08x %08x\n", FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[0], FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[1], FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[2], FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[3]);
    printk("FUSE_PUBLIC_KEY 4-7: %08x %08x %08x %08x\n", FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[4], FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[5], FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[6], FUSE_CHIP_REGS->FUSE_PUBLIC_KEY[7]);
    printk("FUSE_TSENSOR_1: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_1);
    printk("FUSE_TSENSOR_2: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_2);
    printk("FUSE_CP_REV: %08x\n", FUSE_CHIP_REGS->FUSE_CP_REV);
    printk("FUSE_TSENSOR_0: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_0);
    printk("FUSE_FIRST_BOOTROM_PATCH_SIZE_REG: %08x\n", FUSE_CHIP_REGS->FUSE_FIRST_BOOTROM_PATCH_SIZE_REG);
    printk("FUSE_SECURITY_MODE: %08x\n", FUSE_CHIP_REGS->FUSE_SECURITY_MODE);
    printk("FUSE_PRIVATE_KEY: %08x%08x%08x%08x\n", FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[0], FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[1], FUSE_CHIP_REGS->FUSE_PRIVATE_KEY[2]);
    printk("FUSE_DEVICE_KEY: %08x\n", FUSE_CHIP_REGS->FUSE_DEVICE_KEY);
    printk("FUSE_RESERVED_SW: %08x\n", FUSE_CHIP_REGS->FUSE_RESERVED_SW);
    printk("FUSE_VP8_ENABLE: %08x\n", FUSE_CHIP_REGS->FUSE_VP8_ENABLE);
    printk("FUSE_RESERVED_ODM: %08x%08x%08x%08x%08x%08x%08x%08x\n", FUSE_CHIP_REGS->FUSE_RESERVED_ODM[0], FUSE_CHIP_REGS->FUSE_RESERVED_ODM[1], FUSE_CHIP_REGS->FUSE_RESERVED_ODM[2], FUSE_CHIP_REGS->FUSE_RESERVED_ODM[3], FUSE_CHIP_REGS->FUSE_RESERVED_ODM[4], FUSE_CHIP_REGS->FUSE_RESERVED_ODM[5], FUSE_CHIP_REGS->FUSE_RESERVED_ODM[6]);
    printk("FUSE_SKU_USB_CALIB: %08x\n", FUSE_CHIP_REGS->FUSE_SKU_USB_CALIB);
    printk("FUSE_SKU_DIRECT_CONFIG: %08x\n", FUSE_CHIP_REGS->FUSE_SKU_DIRECT_CONFIG);
    printk("FUSE_VENDOR_CODE: %08x\n", FUSE_CHIP_REGS->FUSE_VENDOR_CODE);
    printk("FUSE_FAB_CODE: %08x\n", FUSE_CHIP_REGS->FUSE_FAB_CODE);
    printk("FUSE_LOT_CODE_0: %08x\n", FUSE_CHIP_REGS->FUSE_LOT_CODE_0);
    printk("FUSE_LOT_CODE_1: %08x\n", FUSE_CHIP_REGS->FUSE_LOT_CODE_1);
    printk("FUSE_WAFER_ID: %08x\n", FUSE_CHIP_REGS->FUSE_WAFER_ID);
    printk("FUSE_X_COORDINATE: %08x\n", FUSE_CHIP_REGS->FUSE_X_COORDINATE);
    printk("FUSE_Y_COORDINATE: %08x\n", FUSE_CHIP_REGS->FUSE_Y_COORDINATE);
    printk("FUSE_SATA_CALIB: %08x\n", FUSE_CHIP_REGS->FUSE_SATA_CALIB);
    printk("FUSE_GPU_IDDQ: %08x\n", FUSE_CHIP_REGS->FUSE_GPU_IDDQ);
    printk("FUSE_TSENSOR_3: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_3);
    printk("FUSE_OPT_SUBREVISION: %08x\n", FUSE_CHIP_REGS->FUSE_OPT_SUBREVISION);
    printk("FUSE_TSENSOR_4: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_4);
    printk("FUSE_TSENSOR_5: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_5);
    printk("FUSE_TSENSOR_6: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_6);
    printk("FUSE_TSENSOR_7: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_7);
    printk("FUSE_OPT_PRIV_SEC_DIS: %08x\n", FUSE_CHIP_REGS->FUSE_OPT_PRIV_SEC_DIS);
    printk("FUSE_PKC_DISABLE: %08x\n", FUSE_CHIP_REGS->FUSE_PKC_DISABLE);
    printk("FUSE_TSENSOR_COMMON: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_COMMON);
    printk("FUSE_DEBUG_AUTH_OVERRIDE: %08x\n", FUSE_CHIP_REGS->FUSE_DEBUG_AUTH_OVERRIDE);
    printk("FUSE_TSENSOR_8: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_8);
    printk("FUSE_RESERVED_CALIB: %08x\n", FUSE_CHIP_REGS->FUSE_RESERVED_CALIB);
    printk("FUSE_TSENSOR_9: %08x\n", FUSE_CHIP_REGS->FUSE_TSENSOR_9);
    printk("FUSE_USB_CALIB_EXT: %08x\n", FUSE_CHIP_REGS->FUSE_USB_CALIB_EXT);
    printk("FUSE_SPARE_BIT: %08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x\n", FUSE_CHIP_REGS->FUSE_SPARE_BIT[0], FUSE_CHIP_REGS->FUSE_SPARE_BIT[1], FUSE_CHIP_REGS->FUSE_SPARE_BIT[2], FUSE_CHIP_REGS->FUSE_SPARE_BIT[3], FUSE_CHIP_REGS->FUSE_SPARE_BIT[4], FUSE_CHIP_REGS->FUSE_SPARE_BIT[5], FUSE_CHIP_REGS->FUSE_SPARE_BIT[6], FUSE_CHIP_REGS->FUSE_SPARE_BIT[7], FUSE_CHIP_REGS->FUSE_SPARE_BIT[8], FUSE_CHIP_REGS->FUSE_SPARE_BIT[9], FUSE_CHIP_REGS->FUSE_SPARE_BIT[10], FUSE_CHIP_REGS->FUSE_SPARE_BIT[11], FUSE_CHIP_REGS->FUSE_SPARE_BIT[12], FUSE_CHIP_REGS->FUSE_SPARE_BIT[13], FUSE_CHIP_REGS->FUSE_SPARE_BIT[14],FUSE_CHIP_REGS->FUSE_SPARE_BIT[15], FUSE_CHIP_REGS->FUSE_SPARE_BIT[16], FUSE_CHIP_REGS->FUSE_SPARE_BIT[17], FUSE_CHIP_REGS->FUSE_SPARE_BIT[18], FUSE_CHIP_REGS->FUSE_SPARE_BIT[19], FUSE_CHIP_REGS->FUSE_SPARE_BIT[20], FUSE_CHIP_REGS->FUSE_SPARE_BIT[21], FUSE_CHIP_REGS->FUSE_SPARE_BIT[22], FUSE_CHIP_REGS->FUSE_SPARE_BIT[23], FUSE_CHIP_REGS->FUSE_SPARE_BIT[24], FUSE_CHIP_REGS->FUSE_SPARE_BIT[25], FUSE_CHIP_REGS->FUSE_SPARE_BIT[26], FUSE_CHIP_REGS->FUSE_SPARE_BIT[27], FUSE_CHIP_REGS->FUSE_SPARE_BIT[28], FUSE_CHIP_REGS->FUSE_SPARE_BIT[29], FUSE_CHIP_REGS->FUSE_SPARE_BIT[30]);
}

// --- GPIO ---

u8 gpio_read(u8 bank)
{
    // --- INVALID BANK CHECK --- //
    if (bank > 7) // there are only 8 GPIO banks (GPIO_0, GPIO_1...), for gpio_read specify them zero-based
    {
        return 0xE7; // 0xE7 = 11100111, so if you see that in your info, you'll know why.
    }

    // --- READ FROM IN0 --- //
    volatile u8 *in0_loc = (u8 *)gpio_loc + (bank * 0x100) + 0x30; // volatile = compile expects the value pointed to change

    return *in0_loc;
}

void gpio_render() {
    char gpioBinary[9];
    printk("             "); // centering
    for (int x = 0; x < 8; x++) { // GPIO banks
        memset(gpioBinary, 0x00, sizeof(char) * 9);
        itoa(gpio_read(x), gpioBinary, 2); // number to binary string
        for (int i = 0; i < 8-strlen(gpioBinary); i++) { // 0 padding for binary string
            printk("0");
        }
        printk("%s", gpioBinary);
    }
    printk("\n");
}

u32 btnArray[3] = {0x0, 0x0, 0x0}; // button data
u8 screen = 0; // which screen are we on

#define MAX_ZEROSELECTION 2
u8 zeroSelection = 0; // which item is selected on the 0th screen
char zeroSelectionOptions[MAX_ZEROSELECTION+1][5] = { // selections in text
    "Fuse",
    "GPIO",
    "Quit"
};

int drawUI(u32 btnReading) { // UI rendering
    screen_reset();

    render_header(); // moonflower ascii art, vsomething
    
    // --- BUTTONS --- //

    btn_read_array(btnReading, btnArray);

    if (btnArray[0]) { // Power button
        return 1;
    }

    if (btnArray[1]) { // VOL-
        if (screen == 0) { // Menu, enter selection
            switch (zeroSelection) {
                case MAX_ZEROSELECTION: // Quit
                    return 1;
                    break;
                default:
                    screen = zeroSelection+1;
                    break;
            }
        } else { // Back to menu
            screen = 0;
        }
    }

    if (btnArray[2]) { // VOL+
        if (screen == 0) { // Menu, scroll selection down
            zeroSelection++;
            if (zeroSelection > MAX_ZEROSELECTION) { // wrap-around
                zeroSelection = 0;
            }
        }
    }

    // --- SCREEN RENDERING --- //

    if (screen == 0) { // Menu rendering
        printk("Controls:\n\tVOL+ : scroll/refresh\n\tVOL- : select/back\n\tPOWER - quit\n\n");
        for (u8 i = 0; i <= MAX_ZEROSELECTION; i++) {
            if (i == zeroSelection) { // selection rendering
                printk(">");
            } else {
                printk(" ");
            }

            printk(" %s\n", zeroSelectionOptions[i]);
        }// printk("OUT OF ORDER\n");
    } else if (screen == 1) { // Fuse rendering
        fuse_render();
    } else if (screen == 2) { // GPIO rendering
        gpio_render();
    } else {
        printk("Unknown screen %u\n", screen);
    }

    render_footer(); // fusee gelee by @ktemkin, blah blah blah

    return 0;
}

int main(void) {
    u32 btnReading = 0x0;
    u32 prevBR = 0x0;

    nx_hwinit();
    display_init();

    // Set up the display, and register it as a printk provider.
    lfb_base = display_init_framebuffer();
    video_init(lfb_base);

    drawUI(btnReading);

    while (true) {
        while ((btnReading = btn_read()) == prevBR);
        if (btnReading != 0x00) {
            if (drawUI(btnReading) == 1) break;
        }
        prevBR = btnReading;
    }

    // Reset.
    shutdown_using_pmic();

    /* Do nothing for now */
    return 0;
}
