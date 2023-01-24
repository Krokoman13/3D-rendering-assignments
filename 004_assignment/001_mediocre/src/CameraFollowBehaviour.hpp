#pragma once
#include "FollowBehaviour.hpp"
#include "glm.hpp"

class CameraFollowBehaviour : public FollowBehaviour
{
public:
	CameraFollowBehaviour(GameObject* pTarget);
	CameraFollowBehaviour(GameObject& pTarget);
	virtual void update(float pStep) override;
	virtual void setOwner(GameObject* pGameObject) override;

protected:
	void rotateAroundTarget(float xValue, float yValue);
	void changeDistance(float distanceChange);

	float _turnSpeedX = 0.01f;
	float _turnSpeedY = 0.01f;

	bool zoomingIn = false;
	float zoomMax = 10.0f;
	float zoomMin = 1.0f;
	float zoomSpeed = 0.2f;
};

