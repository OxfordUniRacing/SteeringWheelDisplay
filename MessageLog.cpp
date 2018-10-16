#include "MessageLog.h"
#include <math.h>

MessageLog::MessageLog(int x, int y, int font, int numberOfLines, int widthChar, int lineSpacing){
	///same as the data set comment
  this->x = x;
  this->y = y;
  this->font = font;
  this->lineSpacing = lineSpacing;
  this->numberOfLines = numberOfLines;	///lineCount?
  this->widthChar = widthChar;	///this is ambiguous
  this->currentCharIndex=0;	///not consistent with following line
  this->currentLine=0;
  messages = new char*[numberOfLines];
  for(int i=0;i<numberOfLines;i++) messages[i] = new char[widthChar];
  for(int i=0;i<numberOfLines;i++) {
    for(int j =0; j <widthChar-1; j++) messages[i][j] = ' ';
    messages[i][widthChar-1] = '\0';
  }
}

MessageLog::~MessageLog(){
  for(int i=0;i<this->numberOfLines;i++) delete [] messages[i];
  delete [] messages;
}

void MessageLog::newLine(const char* text){
  this->currentLine++;
  this->currentCharIndex = 0;
  if(this->currentLine == this->numberOfLines) this->currentLine = 0;
  for(this->currentCharIndex; text[this->currentCharIndex] != '\0' && this->currentCharIndex < this->widthChar - 1 ; this->currentCharIndex++){
    this->messages[this->currentLine][this->currentCharIndex] = text[this->currentCharIndex];
  }
  for(int i = this->currentCharIndex; i < this->widthChar - 1 ; i++) messages[this->currentLine][i] = ' ';
}

void MessageLog::addText(const char* text){ // add text to the same line
  int offset = this->currentCharIndex;
  for(this->currentCharIndex; text[this->currentCharIndex - offset] != '\0' && this->currentCharIndex < this->widthChar - 1 ; this->currentCharIndex++){
    this->messages[this->currentLine][this->currentCharIndex] = text[this->currentCharIndex - offset];
  }
}

void MessageLog::addNumber(float num){ // add number to the same line
  dtostrf(num, 3, 2, messages[this->currentLine] + this->currentCharIndex);
  messages[this->currentLine][widthChar-1] = '\0';
}

void MessageLog::addNumberPrecision(float num, int precision){ // add number to the same line with a set precision
  dtostrf(num, 3, precision, messages[this->currentLine] + this->currentCharIndex);
  messages[this->currentLine][widthChar-1] = '\0';
}

void MessageLog::display_messageLog(){
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(defDrawColorR,defDrawColorG,defDrawColorB));
  for(int i = this->currentLine + 1; i<this->numberOfLines;i++){
    FT8_cmd_text(this->x, this->y + (i - this->currentLine - 1) * this->lineSpacing, this->font, 0, this->messages[i]);
  }
  for(int i = 0; i<= this->currentLine ; i++){
    FT8_cmd_text(this->x, this->y + (i - this->currentLine + this->numberOfLines - 1) * this->lineSpacing, this->font, 0, this->messages[i]);
  }
}
