#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"
#include "Line.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include <termios.h>
#include <unistd.h>

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <iostream>


using namespace std;
static struct termios oldT, newT;
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &oldT); /* grab oldT terminal i/o settings */
  newT = oldT; /* make new settings same as oldT settings */
  newT.c_lflag &= ~ICANON; /* disable buffered i/o */
  newT.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &newT); /* use these new terminal i/o settings now */
}

/* Restore oldT terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &oldT);
}

char getch_(int echo) {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

char getch(void) {
	return getch_(0);	
}

char getche(void) {
	return getch_(1);	
}


int main(int argc, char *argv[]) {
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(0, 20, 30);
    sb.backgroundColor = Color(0, 20, 30);

    ShapeGroup Logothesims("Diamond",510,200,70);
    int position = 0;
    int translation = 2;
    while(true){
    	if (position > 20){
    		translation *= -1;
    	}
    	if (position < -20){
    		translation *= -1;
    	}
    	Logothesims.translate(0,translation,0);
    	position += translation;
    	Logothesims.rotateY(3,510,200,0);
	    // for(int i = 0; i < Logothesims.shapes.size(); i++){
	    // 	cout<<i<<endl;
	    // 	for (int j = 0; j < Logothesims.shapes[i].points.size(); j++){
	    // 		cout<<"x: "<<Logothesims.shapes[i].points[j].x<<" y: "<<Logothesims.shapes[i].points[j].y<<" z: "<<Logothesims.shapes[i].points[j].z<<endl;
	    // 	}
	    // }
	    //Logothesims.translate(-20,-20,0);
	    sb.clear();

	    Logothesims.draw(sb,510,200);

	    fb.draw(sb);
	    usleep(50000);
	}

    return 0;
}
