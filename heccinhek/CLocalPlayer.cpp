#pragma once
#include "../windows/pch.h"

#include "CLocalPlayer.h"

CLocalPlayer::CLocalPlayer()
{
	std::cout << "CLocalPlayer waiting for initialization." << std::endl;
}

CLocalPlayer::CLocalPlayer(DWORD dwClientBaseAddr, DWORD dwClientStateAddr)
	: CPlayer(dwClientBaseAddr, 0)
{
	// What is returned from the dwClientState_GetLocalPlayer offset?
	this->dwClientStateAddr = dwClientStateAddr;
	this->updateLocal();
}

bool CLocalPlayer::updateLocal()
{
	if (this->isDormant()) return false;

	fFlags = *(int*)(dwPlayerAddr + hazedumper::netvars::m_fFlags);
	iCrosshairId = *(int*)(dwPlayerAddr + hazedumper::netvars::m_iCrosshairId);
	viewPunchAngle = *(vector2f*)(dwPlayerAddr + hazedumper::netvars::m_viewPunchAngle);
	aimPunchAngle = *(vector2f*)(dwPlayerAddr + hazedumper::netvars::m_aimPunchAngle);
	viewAngles = *(vector2f*)(dwClientStateAddr + hazedumper::signatures::dwClientState_ViewAngles);
	vecVelocity = *(vector3f*)(dwPlayerAddr + hazedumper::netvars::m_vecVelocity);
	flFlashMaxAlpha = *(float*)(dwPlayerAddr + hazedumper::netvars::m_flFlashMaxAlpha);
	return true;
}

bool CLocalPlayer::inAir()
{
	return fFlags == 256 || fFlags == 262 ? true : false;
}

int CLocalPlayer::getCrosshairId()
{
	return iCrosshairId;
}

void CLocalPlayer::setFlashAlpha(float flFlashMaxAlpha)
{
	*(float*)(dwPlayerAddr + hazedumper::netvars::m_flFlashMaxAlpha) = flFlashMaxAlpha;
}

vector2f CLocalPlayer::getViewPunchAngle()
{
	return viewPunchAngle + aimPunchAngle;
}

void CLocalPlayer::setViewAngles(vector2f angles)
{
	*(vector2f*)(dwClientStateAddr + hazedumper::signatures::dwClientState_ViewAngles) = angles;
}

vector2f CLocalPlayer::getViewAngles()
{
	return viewAngles;
}
