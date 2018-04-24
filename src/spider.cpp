#include <cstdlib>
#include <iostream>
#include <GL/glut.h>

#include "spider.h"

#define PI 3.1415926535f
#define sign(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)
#define rad_to_deg(radians) ((radians) * 180.0f / PI)
#define deg_to_rad(degrees) ((degrees) * PI / 180.0f)

spider_t* spider_create(GLfloat x, GLfloat y) {
	spider_t* spider = (spider_t*) malloc(sizeof(spider_t));
	spider->rotationSpeed = 200;
	spider->translationSpeed = 100;
	spider->angle = 0;
	spider->angleThreshold = 3;
	spider->distanceThreshold = 3;
	spider->posX = x;
	spider->posY = y;
	spider->targetX = NULL;
	spider->targetY = NULL;
	spider->headRadius = 18.0f;
	spider->abdomenRadius = 30.0f;
	spider->definedDirection = false;

	return spider;
}

void spider_draw(spider_t* spider) {
	int num_segments = 100;

	glColor4f(0.35f, 0.15f, 0.15f, 1.0f);
	glPointSize(1.0f);

	glLoadIdentity();
	//glTranslatef(spider->posX, spider->posY, 0.0f);
	//glTranslatef(-spider->posX, -spider->posY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * PI * i / num_segments;
		glVertex2f(spider->posX + spider->abdomenRadius * cos(theta),
			spider->posY + spider->abdomenRadius * sin(theta));
	}
	glEnd();

	glLoadIdentity();
	glTranslatef(spider->posX, spider->posY, 0.0f);
	glRotatef(-spider->angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-spider->posX, -spider->posY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * PI * i / num_segments;
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + spider->headRadius * cos(theta),
			spider->posY + spider->headRadius * sin(theta));
	}
	glEnd();
}

GLfloat dot_product(GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb) {
	return xa * xb + ya * yb;
}

GLfloat angle_difference(GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb) {
	GLfloat magA = sqrt(pow(xa, 2) + pow(ya, 2));
	GLfloat magB = sqrt(pow(xb, 2) + pow(yb, 2));

	return dot_product(xa, ya, xb, yb) - (magA * magB);
}

void spider_update(spider_t* spider, int delta) {
	// Primeiro, rotaciona a aranha
	if (spider_has_target(spider)) {
		if (spider->rotating) {
			GLfloat xa = (spider->abdomenRadius + spider->headRadius) * cos(deg_to_rad(spider->angle));
			GLfloat ya = (spider->abdomenRadius + spider->headRadius) * sin(deg_to_rad(spider->angle));
			GLfloat xb = spider->targetX - spider->posX;
			GLfloat yb = spider->targetY - spider->posY;

			GLfloat difference = angle_difference(xa, ya, xb, yb);

			if (spider->definedDirection == false) {
				spider->definedDirection = true;

				float direction = xb * ya - yb * xa;

				if (direction >= 0)
					spider->rotateClockwise = false;
				else
					spider->rotateClockwise = true;
			}

			if (abs(difference) >= spider->angleThreshold) {
				if (spider->rotateClockwise == true)
					spider->angle += spider->rotationSpeed * delta / 1000;
				else
					spider->angle -= spider->rotationSpeed * delta / 1000;

				if (spider->angle >= 360)
					spider->angle -= 360;
				if (spider->angle < 0)
					spider->angle += 360;
			} else {
				spider->definedDirection = false;
				spider->rotating = false;
			}
		} else {
			/*if(spider->targetX > spider->posX)
				spider->posX += spider->translationSpeed * delta / 1000;
			else
				spider->posX -= spider->translationSpeed * delta / 1000;

			if (spider->targetY > spider->posY)
				spider->posY -= spider->translationSpeed * delta / 1000;
			else
				spider->posY += spider->translationSpeed * delta / 1000;

			if (abs(spider->posX - spider->targetX) <= spider->distanceThreshold ||
				abs(spider->posY - spider->targetY) <= spider->distanceThreshold) {
				spider->targetX = NULL;
				spider->targetY = NULL;
			}*/
		}
	}
}

void spider_set_target(spider_t* spider, GLint x, GLint y) {
	spider->targetX = x;
	spider->targetY = y;
	spider->rotating = true;
}

bool spider_has_target(spider_t* spider) {
	if (spider->targetX != NULL && spider->targetY != NULL)
		return true;

	return false;
}