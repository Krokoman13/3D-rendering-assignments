#include "FollowBehaviour.hpp"
#include "FollowBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <iostream>

FollowBehaviour::FollowBehaviour(GameObject& pTarget) : FollowBehaviour(&pTarget)
{
}

FollowBehaviour::FollowBehaviour(GameObject* pTarget) : AbstractBehaviour()
{
	setTarget(pTarget);
}

FollowBehaviour::~FollowBehaviour()
{
	delete target;
}

void FollowBehaviour::update(float pStep)
{
	_owner->setLocalPosition(target->getLocalPosition() + offset);
}

void FollowBehaviour::setOwner(GameObject* pGameObject)
{
	AbstractBehaviour::setOwner(pGameObject);

	if (target == nullptr || _owner == nullptr) return;

	if (target->getParent() != _owner->getParent())
	{
		target = nullptr;
		std::cout << "Invalid target, does not share same parent as owner: " << _owner->getName() << '\n';
		return;
	}

	resetOffset();
}

void FollowBehaviour::setTarget(GameObject* pTarget)
{
	if (pTarget == nullptr) return;
	target = pTarget;

	if (_owner == nullptr) return;

	if (target->getParent() != _owner->getParent())
	{
		target = nullptr;
		std::cout << "Invalid target, does not share same parent as owner: " << _owner->getName() << '\n';
		return;
	}

	resetOffset();
}

void FollowBehaviour::setOffset(glm::vec3 pOffset)
{
}

void FollowBehaviour::resetOffset()
{
	offset = _owner->getWorldPosition() - target->getWorldPosition();
}
