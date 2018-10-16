#include "Arduino.h"

#include "FT8_commands.h"
#include "FT8.h"  //default values for draw and background color can be found in FT8.h
#include "FT8_config.h"



// write this function at the beginning of every frame - clears previous frame and handles default values
void startFrame(){
  FT8_cmd_dl(CMD_DLSTART); /* start the display list */
  FT8_cmd_dl(DL_CLEAR_RGB | COLOR_RGB(backgroundColorR,backgroundColorG,backgroundColorB)); /* set the default clear the background color */
  FT8_cmd_dl(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG); /* clear the screen - this and the previous prevent artifacts between lists, Attributes are the color, stencil and tag buffers */
}

// write this function at the end of every frame - handles end of frame data prottocols to force screen update and flush buffer
void endFrame(){
  FT8_cmd_dl(DL_DISPLAY); /* instruct the graphics processor to show the list */
  FT8_cmd_dl(CMD_SWAP); /* make this list active */
  FT8_cmd_execute();
}



void display_number(int x, int y, int font, int number){
  //displays number at given coordinates and font(size)
  //(x,y) set the TOP LEFT point of the number
  //color is the default draw color
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(defDrawColorR,defDrawColorG,defDrawColorB));
  FT8_cmd_number(x, y, font, 0, number);
}

void display_numberColor(int x, int y, int font, int number, byte R, byte G, byte B){
  //displays number at given coordinates and font(size)
  //(x,y) set the TOP LEFT point of the number
  //color is set by the input arguments
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(R,G,B));
  FT8_cmd_number(x, y, font, 0, number);
}

void display_numberRight(int x, int y, int font, int number){
  //displays number at given coordinates and font(size)
  //(x,y) set the TOP RIGHT point of the number
  //color is the default draw color
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(defDrawColorR,defDrawColorG,defDrawColorB));
  FT8_cmd_number(x, y, font, FT8_OPT_RIGHTX, number);
}

void display_numberColorRight(int x, int y, int font, int number, byte R, byte G, byte B){
  //displays number at given coordinates and font(size)
  //(x,y) set the TOP RIGHT point of the number
  //color is set by the input arguments
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(R,G,B));
  FT8_cmd_number(x, y, font, FT8_OPT_RIGHTX, number);
}



void display_text(int x, int y, int font, const char* text){
  //displays text at given coordinates and font(size)
  //(x,y) set the TOP LEFT point of the text
  //color is the default draw color
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(defDrawColorR,defDrawColorG,defDrawColorB));
  FT8_cmd_text(x, y, font, 0, text);
}

void display_textColor(int x, int y, int font, const char* text, byte R, byte G, byte B){
  //displays text at given coordinates and font(size)
  //(x,y) set the TOP LEFT point of the text
  //color is set by the input arguments
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(R,G,B));
  FT8_cmd_text(x, y, font, 0, text);
}

void display_textRight(int x, int y, int font, const char* text){
  //displays text at given coordinates and font(size)
  //(x,y) set the TOP RIGHT point of the text
  //color is the default draw color
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(defDrawColorR,defDrawColorG,defDrawColorB));
  FT8_cmd_text(x, y, font, FT8_OPT_RIGHTX, text);
}

void display_textColorRight(int x, int y, int font, const char* text, byte R, byte G, byte B){
  //displays text at given coordinates and font(size)
  //(x,y) set the TOP RIGHT point of the text
  //color is set by the input arguments
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(R,G,B));
  FT8_cmd_text(x, y, font, FT8_OPT_RIGHTX, text);
}



void display_text_number(int x, int y, int font, const char* text, int number){
  //displays text next to the number (in this order)
  //(x,y) set the top of the line between the text and the number => BE CAREFULL with alignment
  //color is the default draw color
  display_textRight(x, y, font, text);
  display_number(x, y, font, number);
}

void display_text_numberColor(int x, int y, int font, const char* text, int number, byte R, byte G, byte B){
  //displays text next to the number (in this order)
  //(x,y) set the top of the line between the text and the number => BE CAREFULL with alignment
  //color is set by the input arguments
  display_textColorRight(x, y, font, text, R, G, B);
  display_numberColor(x, y, font, number, R, G, B);
}
