#pragma once
#include "../windows/pch.h"

#include "CPlayer.h"

CPlayer::CPlayer()
{
	std::cout << "CPlayer waiting for initialization." << std::endl;
}

CPlayer::CPlayer(DWORD dwClientBaseAddr, int iId)
{
	// iId = 0 is localPlazer address.
	this->dwPlayerAddr = *(DWORD*)(dwClientBaseAddr + hazedumper::signatures::dwEntityList + (iId - 1) * 0x10);
	this->iId = iId;

	if (!this->update())
	{
		printf("CPlayer [id=%d] is not able to update! [addr=%X]\n", iId, this->dwPlayerAddr);
		return;
	}

	printf("CPlayer [id=%d] successfully initialized! [addr=%X]\n", iId, this->dwPlayerAddr);
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

	printf("Health of Player %d: %d\n", iId, iHealth);

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
