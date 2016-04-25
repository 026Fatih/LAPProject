#pragma once
class Drawable
{
public:
	GLfloat
		xBaseRot,
		xRot,
		yBaseRot,
		yRot,
		zBaseRot,
		zRot;

	Drawable(void);

	virtual void draw() = 0;

	~Drawable(void);
};

