// g++ -o run main.cpp -framework OpenGL -framework Glut
#include "polygon.cpp"
#include <stdlib.h>

const int screenWidth=640;// width of screen window in pixels
const int screenHeight=480;// height of scrren window in pixels
GLdouble A,B,C,D;// values used for scaling and shifting
const int MAX_NUM_VERTICES = 100;

Polygon p(MAX_NUM_VERTICES);

bool SHOW_POLYGON = false;
bool FILL_POLYGON = false;

enum Menu { POINTS, LINES, LINE_LOOP, POLYGON, CLEAR, EXIT };

Menu currChoice;

void myInit(void) {
	
	glClearColor(1.0, 1.0, 1.0, 0.0); // set whitebackground color
	glColor3f(0.0f,0.0f,1.0f); // set the drawing color(black)
	glPointSize(2.0); // a 'dot' is 4 by 4 pixels
	glMatrixMode( GL_PROJECTION ); // set camera shape
	glLoadIdentity();
	gluOrtho2D( 0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight );
	A = screenWidth/4; // set values used for scaling and shifting
	B = 0;
	C = D = screenHeight/2;
}

void myDisplay(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	if (currChoice == POINTS) p.drawPoints();
	if (currChoice == LINE_LOOP) p.draw(0);
	if (currChoice == LINES) p.drawLines();
	if (currChoice == POLYGON) {
		glColor3f(0.0f,0.0f,1.0f);
		p.draw(1);
	}

	glFlush();
}


void drawText() {
	
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, 'V');
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, 'I');
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, 'N');
	
}

void myKeyHandler( unsigned char key, int x, int y) {

	if (key == 27)
		exit(1);
	
	printf("\n key pressed is %c at (%d, %d)", key , x, y);

}

void myMouseHandler( int button, int state, int x, int y ) {

	if (state == GLUT_DOWN) {
		printf("\nAdding vertex (%d, %d) to polygon", x, screenHeight- y);
		p.addVertex(  x, screenHeight- y);
		//p.drawPoints();
	}
}

void myMenu( int value ) {

	printf("\nSelected menu value = %d", value);
	
	switch (value) {
		
		case 1: currChoice = POINTS;
				break;
				
		case 2: currChoice = LINES;
				break;
		
		case 3: currChoice = LINE_LOOP;
				break;
		
		case 4: currChoice = POLYGON;
				break;
		
		case 5: currChoice = CLEAR;
				p.clearVertices();
				break;
		
		case 6: currChoice = EXIT;
				exit(1);
				break;
			
	}
	
	myDisplay();

}

int main(int argc, char* argv[]) {

	glutInit(&argc,argv);// Initialize  the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// set Display mode
	glutInitWindowSize(640,480);// set window size
	glutInitWindowPosition(100,150);// set window position on screen
	glutCreateWindow("Polygon filling");// open the screen window
	
	glutDisplayFunc(myDisplay);	// redraw function
	glutKeyboardFunc(myKeyHandler); // key press handler
	glutMouseFunc(myMouseHandler); //  mouse click handler

	// set up menu
	const int MenuID = glutCreateMenu( myMenu ); 
	glutAddMenuEntry( "Points", 1 );
	glutAddMenuEntry( "Lines", 2 );
	glutAddMenuEntry( "Line Loop", 3 );
	glutAddMenuEntry( "Polygon", 4 );
	glutAddMenuEntry( "Clear", 5 );
	glutAddMenuEntry( "Exit", 6 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );

	myInit();	
	glutMainLoop();

	return 0;
}

