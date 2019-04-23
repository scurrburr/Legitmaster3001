#pragma once
#include "../windows/pch.h"

#include "CPlayer.h"

CPlayer::CPlayer()
{
	std::cout << "CPlayer waiting for initialization." << std::endl;
}

CPlayer::CPlayer(DWORD dwClientBaseAddr, int iId)
{
	this->dwPlayerAddr = *(DWORD*)(dwClientBaseAddr + hazedumper::signatures::dwEntityList + iId * 0x10);
	this->iId = iId;

	if (this->isDormant()) 
	{
		std::cout << "Constructed Player Nr.: " << iId << " is dormant.";
		return;
	}

	this->update();

	std::cout << "CPlayer initialized." << std::endl;
}

bool CPlayer::update()
{
	if (this->isDormant()) return false;

	dwBoneMatrixAddr = *(DWORD*)(dwPlayerAddr + hazedumper::netvars::m_dwBoneMatrix);
	iHealth = *(int*)(dwPlayerAddr + hazedumper::netvars::m_iHealth);
	iTeamNum = *(int*)(dwPlayerAddr + hazedumper::netvars::m_iTeamNum);
	iGlowIndex = *(int*)(dwPlayerAddr + hazedumper::netvars::m_iGlowIndex);
	iLifeState = *(int*)(dwPlayerAddr + hazedumper::netvars::m_lifeState);
	vecOrigin = *(vector3f*)(dwPlayerAddr + hazedumper::netvars::m_vecOrigin);
	vecViewOffset = *(vector3f*)(dwPlayerAddr + hazedumper::netvars::m_vecViewOffset);
	szLastPlaceName = *(char*)(dwPlayerAddr + hazedumper::netvars::m_szLastPlaceName);
	bSpotted = *(bool*)(dwPlayerAddr + hazedumper::netvars::m_bSpotted);
	bImmune = *(bool*)(dwPlayerAddr + hazedumper::netvars::m_bGunGameImmunity);
	return true;
}

bool CPlayer::getSpotted()
{
	return bSpotted == 1 ? true : false;
}

void CPlayer::setSpotted(bool bSpotted)
{
	if (bSpotted)
		*(bool*)(dwPlayerAddr + hazedumper::netvars::m_bSpotted) = 1;
	else
		*(bool*)(dwPlayerAddr + hazedumper::netvars::m_bSpotted) = 0;
}

bool CPlayer::isDormant()
{
	std::cout << this->iId << " Player addr: " << this->dwPlayerAddr << "; " << *(bool*)(this->dwPlayerAddr + hazedumper::signatures::m_bDormant) << std::endl;
	return *(bool*)(this->dwPlayerAddr + hazedumper::signatures::m_bDormant);
}

int CPlayer::getTeam()
{
	return iTeamNum;
}

int CPlayer::getID()
{
	return iId;
}

int CPlayer::getGlowIndex()
{
	return iGlowIndex;
}

bool CPlayer::isAlive()
{
	return iHealth > 0 ? true : false;
}

vector3f CPlayer::getCameraPosition()
{
	return (vector3f)(vecOrigin + vecViewOffset);
}

bool CPlayer::isImmune()
{
	return (bImmune) ? true : false;
}

vector3f CPlayer::getBonePosition(int boneNr)
{
	vector3f bonePos;

	bonePos.x = *(float*)(dwBoneMatrixAddr + (0x30 * boneNr) + 0x0C);
	bonePos.y = *(float*)(dwBoneMatrixAddr + (0x30 * boneNr) + 0x1C);
	bonePos.z = *(float*)(dwBoneMatrixAddr + (0x30 * boneNr) + 0x2C);

	return bonePos;
}
