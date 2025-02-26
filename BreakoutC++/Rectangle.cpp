#include "Rectangle.h"

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
Rectangle::Rectangle(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

//-----------------------------------------------------------------------------
// Purpose: Check if rectangle contains a 2D vector
//-----------------------------------------------------------------------------
bool Rectangle::Contains(Vector2D& vVec) const
{
	if ((vVec.x >= x) &&
		(vVec.x <= x + w) &&
		(vVec.y >= y) &&
		(vVec.x <= y + h))
	{
		return true;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Purpose: Check if rectangle contains a set of coords
//-----------------------------------------------------------------------------
bool Rectangle::Contains(int x, int y) const
{
	if ((x >= this->x) &&
		(x <= this->x + this->w) &&
		(y >= this->y) &&
		(x <= this->y + this->h))
	{
		return true;
	}
	else
		return false;
}

//-----------------------------------------------------------------------------
// Purpose: Return an empty rectangle
//-----------------------------------------------------------------------------
Rectangle Rectangle::Empty()
{
	return Rectangle();
}

//-----------------------------------------------------------------------------
// Purpose: Get intersection depth between two rectangles
//-----------------------------------------------------------------------------
Vector2D Rectangle::GetIntersectionDepth(const Rectangle& rectA, const Rectangle& rectB)
{
	// Calculate half sizes.
	float halfWidthA = rectA.w / 2.0f;
	float halfHeightA = rectA.h / 2.0f;
	float halfWidthB = rectB.w / 2.0f;
	float halfHeightB = rectB.h / 2.0f;

	// Calculate centers.
	Vector2D centerA(rectA.x + halfWidthA, rectA.y + halfHeightA);
	Vector2D centerB(rectB.x + halfWidthB, rectB.y + halfHeightB);

	// Calculate current and minimum-non-intersecting distances between centers.
	float distanceX = centerA.x - centerB.x;
	float distanceY = centerA.y - centerB.y;
	float minDistanceX = halfWidthA + halfWidthB;
	float minDistanceY = halfHeightA + halfHeightB;

	// If we are not intersecting at all, return (0, 0).
	if (fabs(distanceX) >= minDistanceX || fabs(distanceY) >= minDistanceY)
		return Vector2D::Zero();

	// Calculate and return intersection depths.
	float depthX = distanceX > 0 ? minDistanceX - distanceX : -minDistanceX - distanceX;
	float depthY = distanceY > 0 ? minDistanceY - distanceY : -minDistanceY - distanceY;
	return Vector2D(depthX, depthY);
}

//-----------------------------------------------------------------------------
// Purpose: Gets the position of the center of the bottom edge of the rectangle.
//-----------------------------------------------------------------------------
Vector2D Rectangle::GetBottomCenter(const Rectangle& rect)
{
	return Vector2D((float)(rect.x + rect.w / 2.0f), (float)(rect.y + rect.h));
}

//-----------------------------------------------------------------------------
// Purpose: Gets the position of the center point of a rectangle
//-----------------------------------------------------------------------------
Vector2D Rectangle::GetCenter(const Rectangle& rect)
{
	return Vector2D((float)(rect.x + rect.w / 2.0f), (float)(rect.y + rect.h / 2.0f));
}

//-----------------------------------------------------------------------------
// Purpose: Gets the floating point distance between the center point
//          of one rectangle and the center point of another.
//-----------------------------------------------------------------------------
float Rectangle::GetDistance(const Rectangle& rectA, const Rectangle& rectB)
{
	return Vector2D::Distance(GetCenter(rectA), GetCenter(rectB));
}

//-----------------------------------------------------------------------------
// Purpose: Gets the unit vector from one rectangle to another
//-----------------------------------------------------------------------------
Vector2D Rectangle::GetDirection(const Rectangle& rectA, const Rectangle& rectB)
{
	Vector2D direction = GetCenter(rectA) - GetCenter(rectB);
	direction.Normalize();
	return direction;
}

Rectangle& Rectangle::operator= (const Rectangle& r2)
{
	if (this == &r2)
		return *this;

	x = r2.x;
	y = r2.y;
	w = r2.w;
	h = r2.h;

	return *this;
}

bool Rectangle::operator== (const Rectangle& r2) const
{
	return ((w == r2.w) && (h == r2.h));
}

bool Rectangle::operator!= (const Rectangle& r2) const
{
	return !((w == r2.w) && (h == r2.h));
}