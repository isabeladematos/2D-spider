#pragma once

typedef struct {
	GLfloat posX, posY;
	GLfloat targetX, targetY, distanceThreshold;
	GLfloat angle, angleThreshold;
	GLfloat rotationSpeed, translationSpeed;
	GLfloat abdomenRadius, headRadius;
	GLfloat distanceBetweenLegs;
	int modifierX, modifierY;
	bool rotateClockwise, rotating;
} spider_t;

spider_t* spider_create(GLfloat x, GLfloat y);
void spider_draw(spider_t* spider);
void spider_update(spider_t* spider, int delta);
void spider_set_target(spider_t* spider, GLint x, GLint y);
bool spider_has_target(spider_t* spider);
