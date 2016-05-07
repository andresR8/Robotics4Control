/* LedRGB.h
*
* Created: 26/03/2015
* Author: Universidad de los Andes Designed by: Andrés Rengifo
* This work is licensed under a: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* http://creativecommons.org/licenses/by-nc-sa/4.0/
*/


#include <avr/io.h>

#ifndef LEDRGB_H
#define LEDRGB_H
  #define COLOR_RED     (1<<PD5)
  #define COLOR_GREEN   (1<<PD6)
  #define COLOR_BLUE    (1<<PD7)
  #define COLOR_WHITE   0xE0
  #define COLOR_CYAN    0xC0
  #define COLOR_MAGENTA 0xA0
  #define COLOR_YELLOW  0x60
  #define COLOR_OFF     0x1F
  
  void initLedRGB();
  void set_color(char color);  
#endif