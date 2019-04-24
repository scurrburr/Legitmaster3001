#pragma once

#include "CPlayer.h"

class CLocalPlayer : public CPlayer
{
private:
	DWORD dwClientStateAddr;
	int fFlags;								// Player in air, crouching, ...
	int iCrosshairId;						// Aiming on emeny, mate, ...
	vector2f viewPunchAngle;
	vector2f aimPunchAngle;
	vector2f viewAngles;
	vector3f vecVelocity;
	float flFlashMaxAlpha;

public:
	CLocalPlayer();
	CLocalPlayer(DWORD dwClientBaseAddr, DWORD dwClientStateAddr);
	bool updateLocal();
	bool inAir();
	int getCrosshairId();
	void setFlashAlpha(float flFlashMaxAlpha);
	vector2f getViewPunchAngle();
	void setViewAngles(vector2f angles);
	vector2f getViewAngles();
};
