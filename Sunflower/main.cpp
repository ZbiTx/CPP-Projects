#include <GL/glut.h>
#include <cmath>
#include <string>
#include <iostream>
#include <atomic>
#include <thread>

std::atomic<bool> input(false);
std::string user_input;
std::string response = "love";
int love_points = 0;
int hateCounter = 0;
bool blink = false;

void init() {
	glClearColor(0.0, 0.5, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);	
}
void drawCentre(float radius) {
	const double pi = 3.141592653589793238462643383279502884197f;
	glColor3f(0.55f, 0.27f, 0.07f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	int numSegments = 100;
	for (int i=0; i<=numSegments; ++i) {
		double angle = 2.0 * pi * i / numSegments;
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		glVertex2f((float)x,(float)y);
	}
	glEnd();
}
void drawPetal(float scaleX, float scaleY) {
	const double pi = 3.141592653589793238462643383279502884197f;
	glColor3f(1.0f, 0.85f, 0.1f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	int numSegments = 20;
	for (int i=0; i<= numSegments; ++i) {
		double angle = pi * (i/(float)numSegments);
		float x = scaleX * cosf(angle);
		float y = scaleY * sinf(angle);
		glVertex2f((float)x,(float)y);
	}
	glEnd();
}
void drawAllPetals(int count) {
	for(int i=0; i<count; ++i) {
		float angle = (360.0f/count)*i;
		glPushMatrix();
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		drawPetal(0.1f, 0.4f);
		glPopMatrix();
	}
}	
void drawStem(float thickness, float length) {
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	float half_thickness = thickness / 2.0f;

	glBegin(GL_QUADS);
		glVertex2f(-half_thickness, 0.0f);
		glVertex2f(half_thickness, 0.0f);
		glVertex2f(half_thickness, length);
		glVertex2f(-half_thickness, length);
	glEnd();
	glPopMatrix();
}
void drawLeaf(float scaleX, float scaleY, float offsetX, float offsetY, float rotation) {
	const double pi = 3.141592653589793238462643383279502884197;
	const float numSegments = 100;

	glPushMatrix();

	glTranslatef(offsetX, offsetY, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glScalef(scaleX, scaleY, 1.0f);

	glColor3f(0.0f, 0.6f, 0.0f);

	glBegin(GL_POLYGON);
	// Right half
	for (int i=0; i<=numSegments; ++i) {
		double t = pi * (i/numSegments);
		float x = cos(t);
		float y = sin(t) * (1-0.5f*cos(t));
		glVertex2f(x,y);
	}
	// Left half
	for (int i=numSegments; i>=0; --i) {
		float t = pi * (float)i/numSegments;
		float x = -cos(t);
		float y = sin(t) * (1-0.5f*cos(t));
		glVertex2f(x,y);
	}
	glEnd();

	// Leaf vein
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
	glEnd();
	glLineWidth(1.0f);

	// Leaf side veins
	glColor3f(0.0f, 0.0f, 0.0f);
	float angleDeg = 30.0f;
	float length = 0.2f;
	float spacing = 0.1f;

	int count = (int)(1.0f/spacing);
	for (int i=1; i<count; i++) {
		float y = i*spacing;
		double theta = (double)angleDeg * pi / 180.0f;
		float dx = length * cos(theta);
		float dy = length * sin(theta);

		glBegin(GL_LINES);
		// Left vein
		glVertex2f(0.0f, y);
		glVertex2f(-dx, y+dy);

		// Right vein
		glVertex2f(0.0f, y);
		glVertex2f(dx, y + dy);
		glEnd();
	}
	glPopMatrix();
}
void drawEye(float centreX, float centreY, float scaleX, float scaleY) {
	const double pi = 3.141592653589793238462643383279502884197;
	const int numSegments = 100;
	
	// Eyeball
	if (!blink) {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else {
		glColor3f(0.55f, 0.27f, 0.07f);
	}
	glBegin(GL_POLYGON);
	for(int i=0; i<=numSegments; ++i) {
		double theta = i * 2.0 * pi/numSegments;
		float x = scaleX * cos((float)theta);
		float y = scaleY * sin((float)theta);

		glVertex2f(centreX+x, centreY+y);
	}
	glEnd();	

	// Pupil
	if (!blink) {
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	else {
		glColor3f(0.55f, 0.27f, 0.07f);
	}
	float pupilScale = 0.4f;

	glBegin(GL_POLYGON);
	for (int i=0; i<=numSegments/2; ++i) {
		double theta = (pi-i*pi) / (numSegments/3);
		float x = scaleX * pupilScale * cos((float)theta);
		float y = (scaleY) * pupilScale * sin((float)theta);
		glVertex2f(centreX+x, (centreY/7)+y);
	}
	glEnd();
}
void drawMouth(float centreX, float centreY, float radius) {
	const double pi = 3.141592653589793238462643383279502884197;
	const int numSegments = 50;
	
	glPushMatrix();
	glTranslatef(centreX, centreY, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_STRIP);
	for (int i=0; i<=numSegments; ++i) {
		if (response == "love") {
			double theta = pi + (pi * static_cast<float>(i)) / static_cast<float>(numSegments);
			float x = radius * cos((float)theta);
			float y = radius * sin((float)theta);
			glVertex2f(x,y);
		}
		else if (response == "hate") {
			double theta = (pi * static_cast<float>(i)) / static_cast<float>(numSegments);
			float x = radius * cos((float)theta);
			float y = radius * sin((float)theta);
			glVertex2f(x,y);
		}
	}

	glEnd();
	glPopMatrix();		
}
void drawSun(float radius, float offsetX, float offsetY) {
	const double pi = 3.141592653589793238462643383279502884197f;
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	int numSegments = 100;
	for (int i=0; i<=numSegments; ++i) {
		double angle = 2.0 * pi * i / numSegments;
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		glVertex2f(offsetX+(float)x, offsetY+(float)y);
	}
	glEnd();
}
void drawBlush(float centreX, float centreY, float scaleX, float scaleY, std::string response) {
	const double pi = 3.141592653589793238462643383279502884197f; 
	const int numSegments = 100;
	const float radius = 0.02f;	

	if (love_points >= 3 && love_points < 6) {
		glColor3f(1.0f, 0.6f, 0.7f);
	}
	else if (love_points >= 6 && love_points < 9) {
		glColor3f(1.0f, 0.4f, 0.5f);
	}
	else if (love_points >= 9) {
		glColor3f(0.8f, 0.0f, 0.1f);
	}
	else {
		glColor3f(0.55f, 0.27f, 0.07f);
	}
	
	glBegin(GL_POLYGON);
	for (int i=0; i<=numSegments; ++i) {
		double theta = i * pi/numSegments;
		float x = radius * cosf((float)theta) * scaleX;
		float y = radius * sinf((float)theta) * scaleY;
		glVertex2f(centreX+x, centreY+y);
	}
	glEnd();
}
void drawTear(float radius, float offsetX, float offsetY, std::string response) {
	const double pi = 3.141592653589793238462643383279502884197f;
	
	if (hateCounter >= 3) {
		glColor3f(0.0f, 0.3f, 1.0f);
	}
	else {
		glColor3f(0.55f, 0.27f, 0.07f);
	}
	glPushMatrix();
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	int numSegments = 100;
	for (int i=0; i<=numSegments; ++i) {
		double angle = 2.0 * pi * i / numSegments;
		float x = radius * cosf(angle/1.5);
		float y = radius * sinf(angle);
		glVertex2f(offsetX+(float)x, offsetY+(float)y);
	}
	glEnd();
	glPopMatrix();
		
}
void blinkToggle(int value) {
	blink = !blink;
	glutPostRedisplay();

	if (blink) {
		glutTimerFunc(300, blinkToggle, 0);
	} else {
		glutTimerFunc(3000, blinkToggle, 0);
	}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawLeaf(0.05f, 0.10f, 0.08f, -0.6f, -40.0f); // rear leaf on stem
	drawLeaf(0.05f, 0.10f, 0.08f, -0.6f, 140.0f);	

	drawStem(0.05f, 1.0f);

	drawAllPetals(16);
	drawCentre(0.25f);
	drawEye(-0.1f, 0.04f, -0.08f, 0.1f);
	drawEye(0.1f, 0.04f, -0.08f, 0.1f);

	drawBlush(-0.1f, -0.08f, 1.4f, 0.6f, response);
	drawBlush(0.1f, -0.08f, 1.4f, 0.6f, response);

	drawTear(0.02f, -0.15f, 0.05f, response);
	drawTear(0.02f, -0.03f, -0.15f, response);
	drawTear(0.02f, -0.2f, 0.05f, response);

	if (response == "love") {
		drawMouth(0.0f, -0.1f, 0.1f);
	}
	else if (response == "hate") {
		drawMouth(0.0f, -0.18f, 0.1f);
	}

	drawLeaf(0.05f, 0.10f, -0.08f, -0.5f, 45.0f); // front leaf on stem
	drawLeaf(0.05f, 0.10f, -0.08f, -0.5f, -135.0f);	

	drawLeaf(0.12f, 0.3f, 0.03f, -0.9f, 120.0f); // leaf on stem base
	drawLeaf(0.12f, 0.3f, -0.03f, -0.9f, -120.0f);

	drawSun(0.25f, 0.8f, 1.0f);

	glutSwapBuffers();

	if (input) {
		if (user_input == "I love you") {	
			response = "love";
			love_points++;
			hateCounter = 0;
			std::cout<<"🌻: I love you too!"<<std::endl;
			std::cout<<"Love points: "<<love_points<<std::endl;
		}
		else if (user_input == "I hate you") {
			response = "hate";
			love_points = 0;
			hateCounter++;
			std::cout<<"🌻: Oh no! 😢"<<std::endl;
			std::cout<<"Love points: "<<love_points<<std::endl;
		}
		else {
			std::cout<<"🌻: I don't understand..."<<std::endl;
			std::cout<<"Love points: "<<love_points<<std::endl;
		}
		std::cout<<"\n";
		user_input.clear();

		input = false;
	}
	glFlush();
}
void inputThread() {
	while(1) {
		if (!input) {
			std::cout<<"Enter: "<<std::flush;
			std::getline(std::cin, user_input);
			input = true;
		}
	}	
}
int main(int argc, char** argv) {
	std::thread(inputThread).detach();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sunflower");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(3000, blinkToggle, 0);
	
	glutMainLoop();
	glutIdleFunc([](){glutPostRedisplay(); });
	
	return 0;
}	
