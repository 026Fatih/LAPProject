#pragma once
class Drawable
{
public:
	Drawable(void);

	virtual void draw() = 0;

	~Drawable(void);
};

