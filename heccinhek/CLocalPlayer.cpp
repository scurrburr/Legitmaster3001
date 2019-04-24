#pragma once
#include "../windows/pch.h"

#include "CLocalPlayer.h"

CLocalPlayer::CLocalPlayer()
{
	std::cout << "CLocalPlayer waiting for initialization." << std::endl;
}

CLocalPlayer::CLocalPlayer(DWORD dwClientBaseAddr, DWORD dwClientStateAddr) : CPlayer()
{
	this->iId = 0;
	this->dwClientStateAddr = dwClientStateAddr;

	std::cout << "Getting Player addr. ";
	this->dwPlayerAddr = this->dwClientStateAddr + hazedumper::signatures::dwClientState_GetLocalPlayer;

	printf("ClientState: 0x%X; fFlags: %d", this->dwClientStateAddr, *(int*)(dwClientStateAddr + hazedumper::signatures::dwClientState_GetLocalPlayer + hazedumper::netvars::m_fFlags));
	std::cout << "[" << this->dwPlayerAddr << "]" << std::endl;

	std::cout << "Checking if dormant. " << *(bool*)(this->dwPlayerAddr + hazedumper::signatures::m_bDormant) << std::endl;
	if (this->isDormant()) return;

	std::cout << "Updating local information." << std::endl;
	this->updateLocal();

	std::cout << "Updating general information." << std::endl;
	this->update();

	Sleep(1000);
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
	std::cout << vecVelocity.GetLength() << std::endl;
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
