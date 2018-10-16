#include "Graph.h"

#include "FT8_commands.h"
#include "FT8.h"
#include "FT8_config.h"

Graph::Graph(int x, int y, int width, int height, float dataXMin, float dataXMax, float dataYMin, float dataYMax, int dataSize){
  // (x,y) is top left point
	/// does y increase from top to bottom?
	///dataSize is a bit ambiguos, maybe maxDataCountOnScreen?
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->dataXMin = dataXMin;
  this->dataXMax = dataXMax;
  this->dataYMin = dataYMin;
  this->dataYMax = dataYMax;
  this->dataSize = dataSize;
  this->firstDataPoint = 0;
  this->lastDataPoint = -1;
  this->dataXOffset = 0;
  this->timeOffset = 0;
  this->dots = true;
  ///add new class for data set
  this->dataX = new float[dataSize];
  this->dataY = new float[dataSize];
  
}

Graph::~Graph(){
  delete [] dataX;
  delete [] dataY;
}

void Graph::addPoint(float dataX, float dataY){
  //calculates the coordinates on the screen for the point
  this->lastDataPoint++;
  if(this->lastDataPoint == this->dataSize) this->lastDataPoint = 0;
  if((this->lastDataPoint + 1)%this->dataSize == this->firstDataPoint) {	/// ??
    this->firstDataPoint++;
    if(this->firstDataPoint == this->dataSize) this->firstDataPoint=0;
  }
  this->dataX[this->lastDataPoint] = (int)(this->x + this->width*(dataX - this->dataXMin)/(this->dataXMax - this->dataXMin));
  this->dataY[this->lastDataPoint] = (int)(this->y + this->height - this->height*(dataY - this->dataYMin)/(this->dataYMax - this->dataYMin));
}

void Graph::overridePoint(float dataX, float dataY, int index){
  //calculates the coordinates on the screen for the point
	///what happens when the data count has overflown and lastDataPoint is reset to 0? How would we use this then?
  this->dataX[index] = (int)(this->x + width*(dataX - this->dataXMin)/(this->dataXMax - this->dataXMin));
  this->dataY[index] = (int)(this->y + height - height*(dataY - this->dataYMin)/(this->dataYMax - this->dataYMin));
}

void Graph::display_graph(){
  FT8_cmd_dl(DL_COLOR_RGB | COLOR_RGB(defDrawColorR,defDrawColorG,defDrawColorB));
  
	///could be worth refactoring
  if(dots){
    FT8_cmd_dl(DL_BEGIN | FT8_POINTS);
	
    if(this->firstDataPoint <= this->lastDataPoint){
      for(int i = this->firstDataPoint ; i <= this->lastDataPoint; i++){
        FT8_cmd_dl(VERTEX2F((int)((this->dataX[i] - dataXOffset) * 16) , (int)((this->dataY[i]) * 16) ));
      }
    }else{
      for(int i = this->firstDataPoint ; i < this->dataSize; i++){
        FT8_cmd_dl(VERTEX2F((int)((this->dataX[i] - dataXOffset) * 16) , (int)((this->dataY[i]) * 16) ));
      }
      for(int i = 0 ; i <= this->lastDataPoint; i++){
        FT8_cmd_dl(VERTEX2F((int)((this->dataX[i] - dataXOffset) * 16) , (int)((this->dataY[i]) * 16) ));
      }
    }
  }else{
    FT8_cmd_dl(DL_BEGIN | FT8_LINE_STRIP);
    if(this->firstDataPoint <= this->lastDataPoint){
      for(int i = this->firstDataPoint ; i <= this->lastDataPoint; i++){
        FT8_cmd_dl(VERTEX2F((int)((this->dataX[i] - dataXOffset) * 16) , (int)((this->dataY[i]) * 16) ));
      }
    }else{
      for(int i = this->firstDataPoint ; i < this->dataSize; i++){
        FT8_cmd_dl(VERTEX2F((int)((this->dataX[i] - dataXOffset) * 16) , (int)((this->dataY[i]) * 16) ));
      }
      for(int i = 0 ; i <= this->lastDataPoint; i++){
        FT8_cmd_dl(VERTEX2F((int)((this->dataX[i] - dataXOffset) * 16) , (int)((this->dataY[i]) * 16) ));
      }
    }
  }

  
  FT8_cmd_dl(DL_END);
  
  FT8_cmd_dl(DL_BEGIN | FT8_LINE_STRIP);
  FT8_cmd_dl(VERTEX2F(x * 16 , y * 16 ));
  FT8_cmd_dl(VERTEX2F(x * 16 , (y + height) * 16 ));
  FT8_cmd_dl(VERTEX2F((x + width) * 16 , (y + height) * 16 ));
  FT8_cmd_dl(DL_END);

  FT8_cmd_number(x - 2, y + height, 22, FT8_OPT_RIGHTX, dataYMin);
  FT8_cmd_number(x + 4, y + height, 22, 0, dataXMin + timeOffset);
  FT8_cmd_text(x - 1, y + height, 22, 0, ";");
  FT8_cmd_number(x + width, y + height, 22, FT8_OPT_RIGHTX, dataXMax + timeOffset);
  FT8_cmd_number(x, y - 20, 22, 0, dataYMax);
}

void Graph::makeLines(){
	///this is not as clearly indicated in the word document
  // in lines mode the points array needs to be sorted - CURRENTLY NOT IMPLEMENTED
  dots = false;
}

void Graph::makeTimeGraph(float currentTime, float timeWidth){
  this->dataXMax = currentTime;
  this->dataXMin = currentTime - timeWidth;
}

void Graph::updateTime(float currentTime){
	///do we need 4 lines for this?
  float timeDifference = currentTime - this->dataXMax;
  float xDifference = width*timeDifference/(this->dataXMax - this->dataXMin);
  this->timeOffset = timeDifference;
  this->dataXOffset = xDifference;

	///this should be made clearer
  while(this->dataX[this->firstDataPoint] - this->x < this->dataXOffset){
    this->firstDataPoint++;
    if(this->firstDataPoint == this->dataSize) this->firstDataPoint = 0;
    if(this->firstDataPoint == this->lastDataPoint) break;
  }

}
