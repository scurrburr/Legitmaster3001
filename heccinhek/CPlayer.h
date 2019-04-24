#pragma once

#include "../math/Vectors.h"
#include "../haze/csgo.h"
#include "../fmt/core.h"
#include "../fmt/format.h"

class CPlayer
{
	protected:
		DWORD dwPlayerAddr;
		DWORD dwBoneMatrixAddr;
		int iId;
		int iHealth;
		int iTeamNum;
		int iLifeState;
		int iGlowIndex;
		vector3f vecOrigin;
		vector3f vecViewOffset;
		char szLastPlaceName;
		bool bDormant;
		bool bSpotted;
		bool bImmune;

	public:
		CPlayer();
		CPlayer(DWORD dwClientBaseAddr, int iId);
		bool update();

		bool getSpotted();
		void setSpotted(bool bSpotted);

		bool isDormant();
		bool isAlive();
		bool isImmune();

		int getTeam();
		int getID();
		int getGlowIndex();

		vector3f getCameraPosition();
		vector3f getBonePosition(int iBone);
};
