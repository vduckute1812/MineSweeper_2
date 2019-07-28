#include "RetangleObject.h"
#include "CircleObject.h"
#include "Untils.h"


RetangleObject::RetangleObject()
{
	m_shape = RECTANGLE;
}


RetangleObject::~RetangleObject()
{
}

void RetangleObject::SetSize(Size size)
{
	m_size = size;
}

Size RetangleObject::GetSize() const
{
	return m_size;
}

float RetangleObject::GetWidth() const
{
	return m_size.width;
}

float RetangleObject::GetHeight() const
{
	return m_size.height;
}

float RetangleObject::GetAngle()
{
	return m_angle;
}

bool RetangleObject::CheckCollision(Object * obj) const
{
	if (obj->GetShape() == CIRCLE)
	{
		CircleObject* circleObj = static_cast<CircleObject*>(obj);

		Position circlePoint = obj->GetPosition();

		// Rotate circle's center point back
		float unrotatedCircleX = cos(m_angle) * (circlePoint.x - m_position.x) -
			sin(m_angle) * (circlePoint.y - m_position.y) + m_position.y;
		float unrotatedCircleY = sin(m_angle) * (circlePoint.x - m_position.x) -
			cos(m_angle) * (circlePoint.y - m_position.y) + m_position.y;


		float closestX, closestY;

		// Find the unrotated closest x point from center of unrotated circle
		float minRectX = m_position.x - GetWidth() / 2.f;
		float maxRectX = minRectX + GetWidth();
		if (unrotatedCircleX  < minRectX)
			closestX = minRectX;
		else if (unrotatedCircleX  > maxRectX)
			closestX = maxRectX;
		else
			closestX = unrotatedCircleX;

		// Find the unrotated closest y point from center of unrotated circle
		float minRectY = m_position.y - GetHeight() / 2.f;
		float maxRectY = minRectY + GetHeight();

		if (unrotatedCircleY < minRectY)
			closestY = minRectY;
		else if (unrotatedCircleY > maxRectY)
			closestY = maxRectY;
		else
			closestY = unrotatedCircleY;

		// Determine collision
		float circleRadius = circleObj->GetRadius();
		float distance = MathUntils::FindDistance(Position(unrotatedCircleX, unrotatedCircleY), Position(closestX, closestY));

		return distance < circleRadius;
	}
	else if (obj->GetShape() == RECTANGLE)	// In this case, no need to check collision with 2 rotated rectangle because only bullet has rotated angle
	{
		return false;
	}

	return false;
}
