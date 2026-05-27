# X.Tips V6a Split Keyboard

* Keyboard Maintainer: X.Tips
* URL: www.umux.com

> 3 ways to enter the DFU:
- The Bootmagic is enable, To go to bootloader press 4 or 9 while plugging in.
- If you edit the fireware, please keep the bootmagic feature or set a QK_BOOTLOADER keycode in your keymap file. It can put the keyboard into bootloader mode for flashing.
- Short the BOOT pads on the PCB while plugging in PC.

> Use the method below to flash the firmware to the left and right sides separately.
**MCU: stm32f072c8t6**
- qmk flash -kb xtips/v6a/072c -km vial
- qmk flash -kb xtips/v6a/072c -km vial
