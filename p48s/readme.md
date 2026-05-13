X.Tips P48 Keyboard

* Keyboard Maintainer: X.Tips
* URL: www.umux.com

Two modes go to bootloader:
1. The Bootmagic is enable, To go to bootloader press and hold the key in the top left corner while plugging in. If you edit the fireware, please keep the bootmagic feature or set a QK_BOOTLOADER keycode in your keymap file. It can put the keyboard into bootloader mode for flashing.
2. Hold the RESET switch, then hold the BOOT switch, release RESET, release BOOT.

Flash firmware:
1. Download and install QMK Toolbox: https://github.com/qmk/qmk_toolbox/releases
2. Open QMK Toolbox: Load the firmware file (xtips_p48e_v2_vial.bin) and select Auto-Flash.
3. Press and hold the Q key while plugging the keyboard in PC, QMK Toolbox will automatically detect the DFU device and begin flashing.