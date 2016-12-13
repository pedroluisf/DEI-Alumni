// INT386W.hpp: interface for the Int386w class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LPAIS_H__8EC8CA7C_860D_4C62_89D3_C71E326DA12B__INCLUDED_)
#define AFX_LPAIS_H__8EC8CA7C_860D_4C62_89D3_C71E326DA12B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern "C"
{
	int   WINAPI LoadProlog( LPSTR, UINT, UINT, UINT );
	BOOL  WINAPI HaltProlog( UINT );

	LPSTR WINAPI InitGoal( UINT, LPSTR );
	LPSTR WINAPI CallGoal( UINT );
	BOOL  WINAPI ExitGoal( UINT );
	LPSTR WINAPI TellGoal( UINT, LPSTR );

}

const  int isERR_ENCODE = -1;
const  int isERR_TICKLE = -2;
const  int isERR_CMUTEX = -3;
const  int isERR_WMUTEX = -4;
const  int isERR_LOCATE = -5;
const  int isERR_CREATE = -6;
const  int isERR_MAPFIL = -7;
const  int isERR_MODULE = -8;
const  int isERR_PROLOG = -9;
const  int isERR_ACTIVE = -10;
const  int isERR_WINDOW = -11;


class Int386w
{
public:
	int loadError;
	int id;

	Int386w(LPSTR Command="", UINT bufferSize = 0, UINT encryption = 0, UINT tickle = 0 );
	virtual ~Int386w();


	LPSTR initGoal(LPSTR Goal);
	LPSTR callGoal();
	BOOL  exitGoal();
	LPSTR tellGoal( LPSTR Goal );
};

#endif // !defined(AFX_LPAIS_H__8EC8CA7C_860D_4C62_89D3_C71E326DA12B__INCLUDED_)
