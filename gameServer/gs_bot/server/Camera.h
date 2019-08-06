#ifndef CAMERA_H
#define CAMERA_H
#include "Singleton.h"
#include "Box2D/Box2D.h"


class Camera : public Singleton<Camera>
{
public:
	virtual void Init() override;

	void	SetCameraSize(int32 width, int32 height);
	b2Vec2	GetCameraSize() const;

	b2Vec2	ConvertScreenToWorld(const b2Vec2& screenPoint);
	b2Vec2	ConvertWorldToScreen(const b2Vec2& worldPoint);
	void	BuildProjectionMatrix(float32* m, float32 zBias);


private:
	b2Vec2	m_center;
	float32 m_zoom;

	int32	m_width;
	int32	m_height;
};

#endif