#include "CameraFollowBehaviour.hpp"
#include "glm.hpp"
#include <glm/gtx/matrix_decompose.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window.hpp>
#include <iostream>

CameraFollowBehaviour::CameraFollowBehaviour(GameObject* pTarget) : FollowBehaviour(pTarget)
{
	
}

CameraFollowBehaviour::CameraFollowBehaviour(GameObject& pTarget) : FollowBehaviour(pTarget)
{
}

void CameraFollowBehaviour::update(float pStep)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		if (_turnSpeedX < 0.1f) _turnSpeedX += 0.001f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		if (_turnSpeedX > 0.01f) _turnSpeedX -= 0.001f;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		if (zoomingIn)
		{
			changeDistance(-zoomSpeed);
			if (glm::length(offset) < zoomMin) zoomingIn = false;
		}

		else if (!zoomingIn)
		{
			changeDistance(zoomSpeed);
			if (glm::length(offset) > zoomMax) zoomingIn = true;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		float turnSpeedX = 0.0f; //default if no keys
		float turnSpeedY = 0.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			turnSpeedX = +_turnSpeedX;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			turnSpeedX = -_turnSpeedX;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			turnSpeedY = +_turnSpeedY;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			turnSpeedY = -_turnSpeedY;
		}

		rotateAroundTarget(turnSpeedX, turnSpeedY);
	}
	
	FollowBehaviour::update(pStep);
}

void CameraFollowBehaviour::setOwner(GameObject* pGameObject)
{
	FollowBehaviour::setOwner(pGameObject);
	rotateAroundTarget(0.0f, 0.0f);

	zoomMax = glm::length(offset) * 3;
	zoomMin = glm::length(offset) / 2;
}

void CameraFollowBehaviour::rotateAroundTarget(float xValue, float yValue)
{	
	glm::vec3 xAxis = glm::vec3(-1, 0, 0);
	glm::vec3 yAxis = glm::vec3(0, -1, 0);
	
	float vertRotation = acos(_owner->getTransform()[1].y);
	yAxis = glm::rotate(yAxis, -vertRotation, xAxis);

	_owner->rotate(xValue, yAxis);
	
	_owner->rotate(yValue, xAxis);
	{
		vertRotation = acos(_owner->getTransform()[1].y);

		if (vertRotation > glm::radians(45.0f) || vertRotation < glm::radians(-45.0f))	//If it rotates out of bounds, reverse that rotation
		{
			_owner->rotate(-yValue, xAxis);
		}
	}
		
	offset = glm::normalize(_owner->getTransform()[2]) *= glm::length(offset);
}

void CameraFollowBehaviour::changeDistance(float distanceChange)
{
	offset = glm::normalize(_owner->getTransform()[2]) *= (glm::length(offset) + distanceChange);
}

/*
	glm::vec3 xAxis = _owner->getParent()->getTransform()[0];
	glm::vec3 yAxis = _owner->getParent()->getTransform()[1];

	glm::vec3 position = _owner->getLocalPosition();

	glm::mat4 matr = glm::mat4();
	matr[3].x = position.x;
	matr[3].y = position.y;
	matr[3].z = position.z;

	matr = glm::rotate(matr, xValue, yAxis);
	matr = glm::rotate(matr, yValue, xAxis);
	glm::mat3 rotationMatrix = glm::mat3(matr[0], matr[1], matr[2]);

	offset = offset * rotationMatrix;
*/
