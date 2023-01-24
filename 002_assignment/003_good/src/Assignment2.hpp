#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * A subclass of AbstractGame for the purposes of executing the first assignment.
 */

#endif // MGEDEMO_HPP
class Assignment2 : public AbstractGame
{
	//PUBLIC FUNCTIONS

public:
	Assignment2();
	virtual ~Assignment2();

	//override initialize so we can add a DebugHud
	virtual void initialize();

protected:
	//override so we can construct the actual scene
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

private:
	DebugHud* _hud;                   //hud display

	void _updateHud();

	Assignment2(const Assignment2&);
	Assignment2& operator=(const Assignment2&);
};

