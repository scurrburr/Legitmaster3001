#pragma once
#include "windows/pch.h"

#include "Kontrollneger.h"

template <class T>
T readMemory(DWORD addr)
{
	return *(T*)(addr);
}

Kontrollneger::Kontrollneger(DWORD dwClientBaseAddr, DWORD dwEngineBaseAddr)
{
	this->bIsRunning = true;
	std::cout << "--- Nigger started ---\n";

	this->dwClientBaseAddr = dwClientBaseAddr;
	this->dwEngineBaseAddr = dwEngineBaseAddr;
	printf("Client addr assigned:\t0x%X\n", dwClientBaseAddr);
	printf("Engine addr assigned:\t0x%X\n", dwEngineBaseAddr);

	this->dwClientStateAddr = *(DWORD*)(this->dwEngineBaseAddr + hazedumper::signatures::dwClientState);
	printf("State addr assigned:\t0x%X\n", this->dwClientStateAddr);

	this->iCurrentGameState = readMemory<int>(this->dwClientStateAddr + hazedumper::signatures::dwClientState_State);
	printf("Game state detected: %d\n", iCurrentGameState);

	if (iCurrentGameState != 6)
	{
		while(iCurrentGameState != 6)
			{
				std::cout << "\rWaiting to join a game...";
				Sleep(500);
				this->iCurrentGameState = readMemory<int>(this->dwClientStateAddr + hazedumper::signatures::dwClientState_State);
			}
		std::cout << " OK!\n";
	}
	else
	{
		std::cout << "Already ingame, no need to wait.\n";
	}

	std::cout << "Trying to initialize localPlayer." << std::endl;
	this->localPlayer = CLocalPlayer(this->dwClientBaseAddr, this->dwClientStateAddr);

	// TODO: Check if localPlayer is able to be dormant.
	//while(this->localPlayer.isDormant())
	//{
	//	std::cout << "\rWaiting for local player to not be dormant...";
	//	Sleep(500);
	//} std::cout << " OK!\n";

	// TODO: Fix glowObject shit
	// Init Glow object with addr
	// this->glow = Glow(this->dwClientBaseAddr + hazedumper::signatures::dwGlowObjectManager);
	Sleep(500);
	//
	// this->updatePlayers();
	// std::cout << "Players initially updated." << std::endl;
}

void Kontrollneger::updatePlayers()
{
	localPlayer.updateLocal();
	entityList.clear();
	teamIds.clear();
	enemyIds.clear();
	
	for (int i = 1; i < 64; ++i)
	{
		CPlayer temp(this->dwClientBaseAddr, i);
		if (temp.isDormant() || !temp.isAlive()) continue;
	
		if (temp.getTeam() == localPlayer.getTeam())
			teamIds.push_back(i);
		else
			enemyIds.push_back(i);
	
		entityList.insert(std::pair<int, CPlayer>(i, temp));
	}
	
	std::cout << "Entities detected: " << entityList.size() << std::endl;
}

bool Kontrollneger::isCurrentGameStateValid()
{
	this->iCurrentGameState = *(int*)(this->dwClientStateAddr + hazedumper::signatures::dwClientState_State);

	if (this->iCurrentGameState != 6)
	{
		return false;
	}

	if (this->localPlayer.isDormant())
	{
		return false;
	}

	return true;
}

bool Kontrollneger::update()
{
	if (!isCurrentGameStateValid())
	{
		Sleep(500);
		std::cout << "Current game state invalid. Not updating!" << std::endl;
		return false;;
	}

	// input();
	updatePlayers();
	// glow.update(entityList, teamIds, enemyIds);

	return true;
}

void Kontrollneger::input()
{
	if (GetAsyncKeyState(VK_NUMPAD0))
	{
		std::cout << "EXIT" << std::endl;
		this->bIsRunning = false;
		return;
	}

	if (GetAsyncKeyState(VK_SPACE))
		this->bhop();
}

void Kontrollneger::bhop()
{
	if (!localPlayer.inAir() && *pForceJump == 4) {
		*pForceJump = 5;
	}
	else if (localPlayer.inAir() && *pForceJump == 5) {
		*pForceJump = 4;
	}
}

void Kontrollneger::radar()
{
	for (std::map<int, CPlayer>::iterator i = entityList.begin(); i != entityList.end(); ++i)
	{
		if (i->second.getSpotted()) continue;
		if (i->second.getTeam() == localPlayer.getTeam()) continue;
		if (!i->second.isAlive()) continue;

		i->second.setSpotted(true);
	}
}

bool Kontrollneger::isRunning()
{
	return bIsRunning;
}
