struct Point {
	float x;
	float y;
};

enum Menu { POINTS, LINES, LINE_LOOP, POLYGON, CLEAR, EXIT };

class Polygon {

private:

	unsigned long int maxVertices;
	unsigned long int numVertices;
	Point* vertices;

public:
	
	Menu currentMode;
	
	Polygon(int);
	void initPolygon(int); 
	void addVertex(float, float);
	void clearVertices();
	void draw();
	void drawPoints();
	void drawLines();
	void drawLabels();
};
