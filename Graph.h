#include "Arduino.h"



class Graph {
  private:

  int x, y;
  int width, height;

  bool dots;

  float dataXMin, dataXMax;
  float dataYMin, dataYMax;

  float* dataX;
  float* dataY;
  unsigned int firstDataPoint, lastDataPoint, dataSize;
  float dataXOffset; //used for time graphs
  float timeOffset; //used for time graphs

  public:
  Graph(int x, int y, int width, int height, float dataXMin, float dataXMax, float dataYMin, float dataYMax, int dataSize);
  ~Graph();
  void addPoint(float dataX, float dataY);
  void overridePoint(float dataX, float dataY, int index);
  void display_graph();
  void makeLines(); // make  sure points are sorted as sorting is not implemented

  void makeTimeGraph(float currentTime, float timeWidth); // in this mode make sure inputed points are sorted ; DO IT BEFORE ADDING POINTS
  void updateTime(float currentTime); // updates the axis and deletes old data points
};
