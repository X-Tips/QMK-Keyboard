X.Tips X3s Keyboard

* Keyboard Maintainer: X.Tips
* URL: www.umux.com

Two modes go to bootloader:
1. The Bootmagic is enable, To go to bootloader press and hold the key in the top center while plugging in. If you edit the fireware, please keep the bootmagic feature or set a QK_BOOTLOADER keycode in your keymap file. It can put the keyboard into bootloader mode for flashing.
2. Hold the BOOT switch, while plugging in.

Flash firmware:
1. Download and install QMK Toolbox: https://github.com/qmk/qmk_toolbox/releases
2. Open QMK Toolbox: Load the firmware file (xtips_x3s_v1_vial.bin or xtips_x3s_v2_vial.bin) and select Auto-Flash.
3. Press and hold the Q key while plugging the keyboard in PC, QMK Toolbox will automatically detect the DFU device and begin flashing.