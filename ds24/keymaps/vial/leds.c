// Light LEDs when keyboard layer is active
bool rgb_matrix_indicators_user(void) {
   if (IS_LAYER_ON(0)) { 
     if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_all(RGB_CYAN);
     }    
   }
   if (IS_LAYER_ON(1)) { 
     rgb_matrix_set_color_all(RGB_WHITE);
   }
   if (IS_LAYER_ON(2)) { 
     rgb_matrix_set_color_all(RGB_RED);
   }
   if (IS_LAYER_ON(3)) { 
     rgb_matrix_set_color_all(RGB_GREEN);
   }
   if (IS_LAYER_ON(4)) { 
     rgb_matrix_set_color_all(RGB_BLUE);
   }
   if (IS_LAYER_ON(5)) { 
     rgb_matrix_set_color_all(RGB_SPRINGGREEN);
   }
   if (IS_LAYER_ON(6)) { 
     rgb_matrix_set_color_all(RGB_CHARTREUSE);
   }
   if (IS_LAYER_ON(7)) { 
     rgb_matrix_set_color_all(RGB_PURPLE);
   }
   if (IS_LAYER_ON(8)) { 
     rgb_matrix_set_color_all(RGB_CORAL);
   }
   return true;
}
