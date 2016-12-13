// Int386w.cpp: implementation of the Int386w class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include "Int386w.hpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


Int386w::Int386w(LPSTR Command, UINT bufferSize, UINT encryption, UINT tickle )
{
	id = 0;
	loadError = 0;
	int temp = LoadProlog( Command, bufferSize, encryption, tickle );

	if( temp > 0 )
	{
		id = temp;
		loadError = 0;
	} else
	{ 
		id = 0;
		loadError = temp;
	}

}

Int386w::~Int386w()
{
	if( id ) HaltProlog( id );
	id = 0;
}


// Setup a goal for this instance
LPSTR Int386w::initGoal( LPSTR Goal )
{
	return InitGoal( id, Goal );
}

// Call a previously setup goal for this instances
LPSTR Int386w::callGoal()
{
	return CallGoal( id );
}


// Exit a goal, bringing the previous goal to the top of the goal stack
BOOL Int386w::exitGoal()
{
	return ExitGoal(id);
}


// Tell a goal
LPSTR Int386w::tellGoal( LPSTR Goal )
{
	return TellGoal( id, Goal );
}