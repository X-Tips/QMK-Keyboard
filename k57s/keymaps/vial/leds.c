// Light LEDs when keyboard layer is active
bool rgb_matrix_indicators_user(void) {
   if (IS_LAYER_ON(0)) { 
     if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_all(RGB_CYAN);
     }    
   }
   if (IS_LAYER_ON(1) || IS_LAYER_ON(2)) { 
     rgb_matrix_set_color_all(RGB_WHITE);
   }
   if (IS_LAYER_ON(3)) { 
     rgb_matrix_set_color_all(RGB_WHITE);
   }
   if (IS_LAYER_ON(4)) { 
     rgb_matrix_set_color_all(RGB_WHITE);
   }
   if (IS_LAYER_ON(5)) { 
     rgb_matrix_set_color_all(RGB_WHITE);
   }
   if (IS_LAYER_ON(6)) { 
     rgb_matrix_set_color_all(RGB_WHITE);
   }
   if (IS_LAYER_ON(7)) { 
     rgb_matrix_set_color_all(RGB_PURPLE);
   }
   if (IS_LAYER_ON(8)) { 
     rgb_matrix_set_color_all(RGB_PURPLE);
   }
   if (IS_LAYER_ON(1) || IS_LAYER_ON(2) || IS_LAYER_ON(5)) { 
     if (!host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(1, RGB_RED);
     }    
     if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(0, RGB_RED);
     }    
   }
   return true;
}
 