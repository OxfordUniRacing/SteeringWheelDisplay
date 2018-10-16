#include <SPI.h>

#include "Graph.h"
#include "MessageLog.h"
#include "DisplayNumbersAndText.h"

Graph graphTest(50,150,150,100,   1,5  ,0,100, 15);
Graph graphTest2(250,150,150,100,   1,5  ,0,100, 150);

MessageLog messageLogTest(350,10 , 22, 5,15, 20);

void setup() {
  digitalWrite(FT8_CS, HIGH);
  pinMode(FT8_CS, OUTPUT);
  digitalWrite(FT8_PDN, HIGH);
  pinMode(FT8_PDN, OUTPUT);

  SPI.begin();
  
  FT8_init();

  graphTest.addPoint(2.5 ,50);
  graphTest.addPoint(3,10);
  graphTest.addPoint(5,90);

  graphTest2.makeTimeGraph(0,10);
  graphTest2.addPoint(-5, 50);
  graphTest2.makeLines();

  messageLogTest.newLine("12345");//line 1
  messageLogTest.newLine("abcde");//line 2
  messageLogTest.newLine("line");//line 3
    messageLogTest.addNumber(12345.67);
  messageLogTest.newLine("line 4");
    messageLogTest.addText("sth");
  messageLogTest.newLine("12345678901234567890");// line 5
  messageLogTest.newLine("line 6");
}

float currentFrame  = 0;
void loop() {
  
  delay(10);
  startFrame();

  // test text functions
  display_text(50,10,22,"asdf");
  display_textColor(50,30,22,"blue",0,0,255);
  display_textRight(50,50,22,"fdsa");
  display_textColorRight(50,70,22,"re+gr",255,255,0);

  //test number functions
  display_number(150,10,22,00155);
  display_numberColor(150,30,22,245,0,255,0);
  display_numberRight(150,50,22,22432);
  display_numberColorRight(150,70,22,765432,255,0,0);

  // test text_number functions
  display_text_number(250,10,22,"speed ",120);
  display_text_numberColor(250,30,22,"place: ",2,100,255,100);


  // test graph
  graphTest.display_graph();
  graphTest2.display_graph();

  // test message log
  messageLogTest.display_messageLog();
  
  endFrame();

  // update graph
  currentFrame++;
  graphTest2.updateTime(currentFrame/15);
  graphTest2.addPoint(currentFrame/15,75 + 20*sin(currentFrame/15));


  //update message log
  if(currentFrame == 100)  messageLogTest.newLine("new line 7");
  if(currentFrame == 300)  messageLogTest.newLine("new line 8");
  if(currentFrame == 600)  messageLogTest.newLine("new line 9");
  if(currentFrame == 900)  messageLogTest.newLine("new line 10");
  if(currentFrame == 1200) messageLogTest.newLine("new line 11");
  if(currentFrame == 1500) messageLogTest.newLine("new line 12");
}












