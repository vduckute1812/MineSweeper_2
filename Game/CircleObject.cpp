#include "CircleObject.h"
#include "RetangleObject.h"
#include "Untils.h"
#include <math.h>

CircleObject::CircleObject()
{
}

CircleObject::CircleObject(float radious)
	: m_radius(radious)
{
	m_shape = CIRCLE;
}


CircleObject::~CircleObject()
{
}

void CircleObject::SetRadius(float radious)
{
	m_radius = radious;
}

float CircleObject::GetRadius() const
{
	return m_radius;
}

bool CircleObject::CheckCollision(Object * obj) const
{
	if (obj->GetShape() == CIRCLE)
	{
		float r1 = m_radius;
		float r2 = static_cast<CircleObject*>(obj)->GetRadius();
		
		Position p1 = m_position;
		Position p2 = obj->GetPosition();

		return (r1 + r2)*(r1 + r2) <= MathUntils::FindDistance(p1, p2);
	}
	else if (obj->GetShape() == RECTANGLE)
	{
		RetangleObject* rectangle = static_cast<RetangleObject*>(obj);
		float rectangleAngle = rectangle->GetAngle();
		Position circlePoint = m_position;
		Position rectCenterPoint = obj->GetPosition();

		// Rotate circle's center point back
		float unrotatedCircleX = cos(rectangleAngle) * (circlePoint.x - rectCenterPoint.x) -
									sin(rectangleAngle) * (circlePoint.y - rectCenterPoint.y) + rectCenterPoint.y;
		float unrotatedCircleY = sin(rectangleAngle) * (circlePoint.x - rectCenterPoint.x) -
									cos(rectangleAngle) * (circlePoint.y - rectCenterPoint.y) + rectCenterPoint.y;


		float closestX, closestY;

		// Find the unrotated closest x point from center of unrotated circle
		float minRectX = rectCenterPoint.x - rectangle->GetWidth() / 2.f;
		float maxRectX = minRectX + rectangle->GetWidth();
		if (unrotatedCircleX  < minRectX)
			closestX = minRectX;
		else if (unrotatedCircleX  > maxRectX)
			closestX = maxRectX;
		else
			closestX = unrotatedCircleX;

		// Find the unrotated closest y point from center of unrotated circle
		float minRectY = rectCenterPoint.y - rectangle->GetHeight() / 2.f;
		float maxRectY = minRectY + rectangle->GetHeight();

		if (unrotatedCircleY < minRectY)
			closestY = minRectY;
		else if (unrotatedCircleY > maxRectY)
			closestY = maxRectY;
		else
			closestY = unrotatedCircleY;

		// Determine collision
		float distance = MathUntils::FindDistance(Position(unrotatedCircleX, unrotatedCircleY), Position(closestX, closestY));

		return distance < m_radius;
	}

	return false;
}

