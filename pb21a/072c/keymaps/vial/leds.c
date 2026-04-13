bool rgb_matrix_indicators_user(void) {
    if (IS_LAYER_ON(1)) rgb_matrix_set_color_all(RGB_WHITE);
    else if (IS_LAYER_ON(2)) rgb_matrix_set_color_all(RGB_CYAN);
    else if (IS_LAYER_ON(3)) rgb_matrix_set_color_all(RGB_BLUE);
    else if (IS_LAYER_ON(4)) rgb_matrix_set_color_all(RGB_PURPLE);
    else if (IS_LAYER_ON(5)) rgb_matrix_set_color_all(RGB_ORANGE);
    else if (IS_LAYER_ON(6)) rgb_matrix_set_color_all(RGB_TEAL);
    else if (IS_LAYER_ON(7)) rgb_matrix_set_color_all(RGB_MAGENTA);
    else if (IS_LAYER_ON(8)) rgb_matrix_set_color_all(RGB_GOLD);
    
    if (IS_LAYER_ON(0) && host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_all(RGB_RED);
    }
    
    return true;
}