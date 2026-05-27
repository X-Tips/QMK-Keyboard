# X.Tips V6e Split Keyboard

* Keyboard Maintainer: X.Tips
* URL: www.umux.com

> 3 ways to enter the DFU:
- The Bootmagic is enable, To go to bootloader press 4 or 9 while plugging in.
- If you edit the fireware, please keep the bootmagic feature or set a QK_BOOTLOADER keycode in your keymap file. It can put the keyboard into bootloader mode for flashing.
- Short the BOOT pads on the PCB while plugging in PC.

> There are 3 versions that use different MCU.
> Use the method below to flash the firmware to the left and right sides separately.

**401r: stm32f401rbt6**
- qmk flash -kb xtips/v6e/401r -km vial

**072r: stm32f072r8t6**
- qmk flash -kb xtips/v6e/072r -km vial

**072c: stm32f072c8t6**
- qmk flash -kb xtips/v6e/072c -km vial -bl dfu-util-split-left
- qmk flash -kb xtips/v6e/072c -km vial -bl dfu-util-split-right


---
Optional case designed to fit the V6e Split keyboard.
https://makerworld.com/en/models/2425541-case-for-x-tips-v6-split-keyboard