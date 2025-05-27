/*
 * display.c
 *
 *  Created on: Jan 30, 2025
 *      Author: akila
 */

#include  "include\macros.h"




void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}
