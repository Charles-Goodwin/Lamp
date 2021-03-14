#ifndef XY_H
#define XY_H
/*  
 *  The Neopixel matrix we are dealing with is somewhat irregular and
 *  so I have built this function to return the serial
 *  position of the neopixel based on the X,Y coordinates
 *  provided.
 *  
 *  The matrix is consttructed by a strip wound in a spiral fashion round a cylinder
 *  The spiral comences at column zero with 4 additional columns completing one full rotation
 *  Each column has 30 leds. Unwrapping the columns of leds we have a matrix of 5 columns and 30 rows(rings) 
 *  
 *  The number of neopixels for each length are defined by:
 *    LEDNUM_COLUMN and
 *    LEDNUM_ROW
 *  
 *  A response of -1 is returned for any coordinate that does not have a coresponding neopixel   
 *  
 */
 
uint16_t XY(uint8_t x, uint8_t y) {
  //Declare how many pixels are in each length
  
  int s;
 
  if (x >= NUM_LEDS_COLUMN) return -1;;
  if (y >= NUM_LEDS_ROW)  return -1;
  s =  x + (y * 5);
 
  return s;
}

uint16_t XYwrap(uint8_t x, uint8_t y) {
  x = x % NUM_LEDS_COLUMN;
  y = y % NUM_LEDS_ROW;
  if (x<0) x+= NUM_LEDS_COLUMN;
  if (y<0) y+= NUM_LEDS_ROW;
  
  return XY(x,y);
}

#endif
