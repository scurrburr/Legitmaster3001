#pragma once

#include "heccinhek/CPlayer.h"
#include "heccinhek/CLocalPlayer.h"
#include "heccinhek/Glow.h"
#include "heccinhek/Aimbot.h"
#include <map>
#include <vector>

class Kontrollneger
{
	private:
		DWORD dwClientBaseAddr;
		DWORD dwEngineBaseAddr;
		DWORD dwClientStateAddr;
		int iCurrentGameState;
		bool bIsRunning;
		std::map<int, CPlayer> entityList;
		std::vector<int> teamIds;
		std::vector<int> enemyIds;
		DWORD* pForceJump;
		DWORD* pForceAttack;
		CLocalPlayer localPlayer;
		Glow glow;
		Aimbot aimbot;

	public:
		Kontrollneger(DWORD clientbase, DWORD enginebase);
		void updatePlayers();
		bool update();
		bool isCurrentGameStateValid();
		void input();
		void bhop();
		void radar();
		bool isRunning();
};
