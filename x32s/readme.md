# X.Tips X32s Split Keyboard

- Keyboard Maintainer: X.Tips
- URL: www.umux.com


> 3 ways to enter the DFU:
- The Bootmagic is enable, To go to bootloader press and hold the key in the top left corner while plugging in PC.
- If you edit the fireware, please keep the bootmagic feature or set a QK_BOOTLOADER keycode in your keymap file. It can put the keyboard into bootloader mode for flashing.
- Short the BOOT pads on the PCB while plugging in PC.


> Use the method below to flash the firmware to the left and right sides separately.
- qmk flash -kb xtips/x32s/072c -km vial -bl dfu-util-split-left
- qmk flash -kb xtips/x32s/072c -km vial -bl dfu-util-split-right
