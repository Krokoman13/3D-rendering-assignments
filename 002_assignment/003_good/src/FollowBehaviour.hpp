#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

class FollowBehaviour : public AbstractBehaviour
{
	public:
		FollowBehaviour(GameObject& pTarget);
		FollowBehaviour(GameObject* pTarget);
		virtual ~FollowBehaviour();
		virtual void update(float pStep);
		virtual void setOwner(GameObject* pGameObject);
		void setTarget(GameObject* pTarget);
		void setOffset(glm::vec3 pOffset);
		void resetOffset();

	protected:
		GameObject* target;
		glm::vec3 offset;
};

