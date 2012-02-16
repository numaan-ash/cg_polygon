#include <stdio.h>
#include <GLUT/glut.h>
#include "polygon.h"

Polygon::Polygon(int maxVertices) {
		this->initPolygon(maxVertices);
}

void Polygon::initPolygon( int maxVertices ) {

	this->maxVertices = maxVertices;
	this->vertices = new Point[maxVertices];
	this->numVertices = 0;

}

void Polygon::addVertex( float x, float y ) {

	if (numVertices <= maxVertices) {
		vertices[numVertices].x = x;
		vertices[numVertices].y = y;
		numVertices++;
	}
	else 
		printf("\n Cant add mode vertices...");

}

void Polygon::clearVertices() {
	this->numVertices = 0;
	this->currentMode = POINTS;
	printf("\n Vertices cleared...");
}

void Polygon::draw() {
	
	switch (this->currentMode) {
		
		case POINTS: glBegin(GL_POINTS); break;
		case LINES: glBegin(GL_LINE_STRIP); break;
		case LINE_LOOP: glBegin(GL_LINE_LOOP); break;
		case POLYGON: glBegin(GL_POLYGON); break;
		
	}

	glColor3f(0.0f,0.0f,1.0f);

	for (int vertexIndex = 0; vertexIndex < numVertices; vertexIndex++ )
		glVertex2f(  vertices[vertexIndex].x, vertices[vertexIndex].y );
		
	glEnd();

}

void Polygon::drawLabels() {

	for(int vertexIndex =0; vertexIndex < numVertices; vertexIndex++ ) {
	
	//	glPushMatrix();
	//	glTranslatef(vertices[vertexIndex].x, vertices[vertexIndex].y,0.0 );

		glRasterPos2f(vertices[vertexIndex].x, vertices[vertexIndex].y);
		//glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_10, vertexIndex + 'A');
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, vertexIndex + 'A');

	//	glPopMatrix();
	}

}

