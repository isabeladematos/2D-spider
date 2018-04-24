#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include "spider.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

void init();
void draw();
void update(int value);
void on_click(GLint button, GLint action, GLint x, GLint y);

int delta = 1000 / 60;
spider_t* spider;

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	GLint screen_width = glutGet(GLUT_SCREEN_WIDTH);
	GLint screen_height = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
	glutCreateWindow("Spider 2D");

	init();
	glutDisplayFunc(draw);
	glutMouseFunc(on_click);
	glutTimerFunc(delta, update, NULL);

	glutMainLoop();
	return EXIT_SUCCESS;
}

void init() {
	spider = spider_create(300, 300);
	glClearColor(0.0f, 0.6f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void draw() {
	// Desenhar a aranha
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	spider_draw(spider);
	glFlush();
}

void update(int value) {
	// Atualizar posição da aranha
	spider_update(spider, delta);
	glutPostRedisplay();
	glutTimerFunc(delta, update, NULL);
}

void on_click(GLint button, GLint action, GLint x, GLint y) {
	// Configurar a posição de destino
	switch (button) {
		case GLUT_LEFT_BUTTON:
		case GLUT_RIGHT_BUTTON:
			if (action == GLUT_UP) {
				std::cout << "Click on X = " << x << ", Y = " << y << ".\n";
				spider_set_target(spider, x, y);
			}
			break;

		default:
			break;
	}
}
