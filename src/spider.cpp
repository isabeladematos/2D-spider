#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

#include "spider.h"

#define PI 3.1415926535f
#define sign(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)
#define rad_to_deg(radians) ((radians) * 180.0f / PI)
#define deg_to_rad(degrees) ((degrees) * PI / 180.0f)

spider_t* spider_create(GLfloat x, GLfloat y) {
	spider_t* spider = (spider_t*) malloc(sizeof(spider_t));
	spider->rotationSpeed = 200;
	spider->translationSpeed = 1;
	spider->angle = -90;
	spider->angleThreshold = 0.1;
	spider->distanceThreshold = 3;
	spider->posX = x;
	spider->posY = y;
	spider->targetX = NULL;
	spider->targetY = NULL;
	spider->headRadius = 23.0f;
	spider->abdomenRadius = 30.0f;
	spider->distanceBetweenLegs = 5;
	spider->rotating = false;

	return spider;
}

void spider_draw(spider_t* spider) {
	int num_segments = 100;

	glColor4f(0.25f, 0.15f, 0.15f, 1.0f);
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
	glRotatef(spider->angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-spider->posX, -spider->posY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * PI * i / num_segments;
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + spider->headRadius * cos(theta),
			spider->posY + spider->headRadius * sin(theta));
	}
	glEnd();

	glBegin(GL_LINES);
			//P1
			//lado direito
			//primeira perna
	    glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius - 10 ,
			spider->posY  );
	    glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 90 * sin(1.22173),
			spider->posY  + 90 * cos(1.22173));

			glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 90 * sin(1.22173),
		 spider->posY  + 90* cos(1.22173));
		 glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 90 * sin(1.22173) +  35 * sin(0.872665),
		spider->posY  + 90 * cos(1.22173) + 35 * cos(0.872665));

		//segunda perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + 10 - spider->distanceBetweenLegs ,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 * sin(0.349066) - spider->distanceBetweenLegs,
		spider->posY  + 60 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 * sin(0.349066) - spider->distanceBetweenLegs,
		spider->posY + 60 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 * sin(0.349066) + 40 * sin(5.23599) - spider->distanceBetweenLegs,
		spider->posY   + 60 * cos(0.349066) + 40 * cos(5.23599));

		//terceira perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + 10 - 2*spider->distanceBetweenLegs,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 50 * sin(0.349066) - 2*spider->distanceBetweenLegs,
		spider->posY   + 50 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 50 * sin(0.349066) - 2*spider->distanceBetweenLegs,
		spider->posY   + 50 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 50 * sin(0.349066) + 50 * sin(5.23599) - 2*spider->distanceBetweenLegs ,
		spider->posY  + 50 * cos(0.349066) + 50 * cos(5.23599));

		//quarta perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 10 - 3*spider->distanceBetweenLegs,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 40 * sin(0.349066) - 3*spider->distanceBetweenLegs,
		spider->posY   + 40 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 40 * sin(0.349066) - 3*spider->distanceBetweenLegs,
		spider->posY   + 40 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 40 * sin(0.349066) + 120 * sin(5.23599) - 3*spider->distanceBetweenLegs ,
		spider->posY  + 40 * cos(0.349066) + 120 * cos(5.23599));

		//lado esquerda
		//primeira perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius - 10 ,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 90 * sin(1.22173),
		spider->posY  - 90 * cos(1.22173));

		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 90 * sin(1.22173),
		spider->posY  - 90* cos(1.22173));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 90 * sin(1.22173) +  35 * sin(0.872665),
		spider->posY  - 90 * cos(1.22173) - 35 * cos(0.872665));

		//segunda perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + 10 - spider->distanceBetweenLegs ,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 * sin(0.349066) - spider->distanceBetweenLegs,
		spider->posY  - 60 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 * sin(0.349066) - spider->distanceBetweenLegs,
		spider->posY - 60 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 * sin(0.349066) + 40 * sin(5.23599) - spider->distanceBetweenLegs,
		spider->posY   - 60 * cos(0.349066) - 40 * cos(5.23599));

		//terceira perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + 10 - 2*spider->distanceBetweenLegs,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 50 * sin(0.349066) - 2*spider->distanceBetweenLegs,
		spider->posY   - 50 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 50 * sin(0.349066) - 2*spider->distanceBetweenLegs,
		spider->posY   - 50 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 50 * sin(0.349066) + 50 * sin(5.23599) - 2*spider->distanceBetweenLegs ,
		spider->posY  - 50 * cos(0.349066) - 50 * cos(5.23599));

		//quarta perna
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 10 - 3*spider->distanceBetweenLegs,
		spider->posY  );
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 40 * sin(0.349066) - 3*spider->distanceBetweenLegs,
		spider->posY   - 40 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 40 * sin(0.349066) - 3*spider->distanceBetweenLegs,
		spider->posY   - 40 * cos(0.349066));
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 40 * sin(0.349066) + 120 * sin(5.23599) - 3*spider->distanceBetweenLegs ,
		spider->posY  - 40 * cos(0.349066) - 120 * cos(5.23599));


	glEnd();

	/*glBegin(GL_LINES);
	    glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60,
			spider->posY  + 60);
			glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius  + 60 +  50 * sin(5.75959),
		 spider->posY  + 60 + 50 * cos(5.75959));

	glEnd();*/


	/*glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * PI * i / num_segments;
		glVertex2f(spider->posX + spider->abdomenRadius + spider->headRadius + spider->headRadius * cos(theta),
			spider->posY + spider->headRadius * sin(theta));
	}
	glEnd();*/
}

bool same_direction(GLfloat threshold, GLfloat xa, GLfloat ya, GLfloat xb, GLfloat yb) {
	GLfloat magA = sqrt(pow(xa, 2) + pow(ya, 2));
	GLfloat magB = sqrt(pow(xb, 2) + pow(yb, 2));

	xa = xa / magA;
	ya = ya / magA;
	xb = xb / magB;
	yb = yb / magB;

	//std::cout << abs(xa - xb) << ", " << abs(ya - yb) << std::endl;
	if (abs(xa - xb) <= threshold && abs(ya - yb) <= threshold)
		return true;

	return false;
}

void spider_update(spider_t* spider, int delta) {
	if (spider_has_target(spider)) {
		if (spider->rotating) {
			// Rotate first
			GLfloat xa = (spider->abdomenRadius + spider->headRadius) * cos(deg_to_rad(spider->angle));
			GLfloat ya = (spider->abdomenRadius + spider->headRadius) * sin(deg_to_rad(spider->angle));
			GLfloat xb = spider->targetX - spider->posX;
			GLfloat yb = spider->targetY - spider->posY;

			if(!same_direction(spider->angleThreshold, xa, ya, xb, yb)){
				if (spider->rotateClockwise == true)
					spider->angle += spider->rotationSpeed * delta / 1000;
				else
					spider->angle -= spider->rotationSpeed * delta / 1000;

				if (spider->angle >= 360)
					spider->angle -= 360;
				if (spider->angle < 0)
					spider->angle += 360;
			} else {
				spider->rotating = false;
			}
		} else {
			// Move after rotation is done
			float distanceX = abs(spider->targetX - spider->posX);
			float distanceY = abs(spider->targetY - spider->posY);

			if (distanceX >= spider->distanceThreshold)
				spider->posX += distanceX * spider->modifierX * spider->translationSpeed * delta / 1000;

			if(distanceY >= spider->distanceThreshold)
				spider->posY += distanceY * spider->modifierY * spider->translationSpeed * delta / 1000;

			if (distanceX <= spider->distanceThreshold && distanceY <= spider->distanceThreshold) {
				spider->targetX = NULL;
				spider->targetY = NULL;
			}
		}
	}
}

void spider_set_target(spider_t* spider, GLint x, GLint y) {
	spider->targetX = x;
	spider->targetY = y;
	spider->rotating = true;

	GLfloat xa = (spider->abdomenRadius + spider->headRadius) * cos(deg_to_rad(spider->angle));
	GLfloat ya = (spider->abdomenRadius + spider->headRadius) * sin(deg_to_rad(spider->angle));
	GLfloat xb = spider->targetX - spider->posX;
	GLfloat yb = spider->targetY - spider->posY;

	float direction = xb * ya - yb * xa;
	(direction >= 0) ? spider->rotateClockwise = false : spider->rotateClockwise = true;

	(spider->targetX > spider->posX) ? spider->modifierX =  1 : spider->modifierX = -1;
	(spider->targetY > spider->posY) ? spider->modifierY =  1 : spider->modifierY = -1;
}

bool spider_has_target(spider_t* spider) {
	if (spider->targetX != NULL && spider->targetY != NULL)
		return true;

	return false;
}
