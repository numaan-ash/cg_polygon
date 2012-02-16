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

	p.draw();

	glFlush();
}


void drawText() {
	
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, 'V');
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, 'I');
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, 'N');
	
}

void myKeyHandler( unsigned char key, int x, int y) {

	printf("\nKey pressed is %c at (%d, %d)", key , x, y);

	switch (key) {
		
		case '1': p.currentMode = POINTS; break;
		case '2': p.currentMode = LINES; break;
		case '3': p.currentMode = LINE_LOOP; break;
		case '4': p.currentMode = POLYGON; break;
		case 'c': 
		case 'C': p.currentMode = CLEAR; p.clearVertices(); break;
		case 27: exit(1); break;
	}
	
	myDisplay();
	
}

void myMouseHandler( int button, int state, int x, int y ) {

	if (state == GLUT_DOWN) {
		printf("\nAdding vertex (%d, %d) to polygon", x, screenHeight- y);
		p.addVertex(  x, screenHeight- y);
		myDisplay();
	}
}

void myMenu( int value ) {

	printf("\nSelected menu value = %d", value);
	
	switch (value) {
		
		case 1: p.currentMode = POINTS;
				break;
				
		case 2: p.currentMode = LINES;
				break;
		
		case 3: p.currentMode = LINE_LOOP;
				break;
		
		case 4: p.currentMode = POLYGON;
				break;
		
		case 5: p.currentMode = CLEAR;
				p.clearVertices();
				break;
		
		case 6: p.currentMode = EXIT;
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
	glutCreateWindow("POLYGON");// open the screen window
	
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
	p.currentMode = POINTS;
	glutMainLoop();

	return 0;
}

