#pragma once
#include "windows/pch.h"

#include "Kontrollneger.h"

Kontrollneger::Kontrollneger(DWORD dwClientBaseAddr, DWORD dwEngineBaseAddr)
{
	this->bIsRunning = true;
	std::cout << "--- Nigger started ---\n";

	this->dwClientBaseAddr = dwClientBaseAddr;
	this->dwEngineBaseAddr = dwEngineBaseAddr;
	std::cout << "Client addr assigned: " << dwClientBaseAddr << std::endl;
	std::cout << "Engine addr assigned: " << dwEngineBaseAddr << std::endl;

	Sleep(500);

	this->dwClientStateAddr = *(DWORD*)(this->dwEngineBaseAddr + hazedumper::signatures::dwClientState);
	this->iCurrentGameState = *(int*)(this->dwClientStateAddr + hazedumper::signatures::dwClientState_State);
	std::cout << "Current game state: " << iCurrentGameState << std::endl;

	while(iCurrentGameState != 6)
	{
		std::cout << "\rWaiting to join a game...";
		Sleep(500);
		this->iCurrentGameState = *(int*)(this->dwClientStateAddr + hazedumper::signatures::dwClientState_State);
	} std::cout << " OK!\n";

	// Init local player with addr
	this->localPlayer = CLocalPlayer(this->dwClientBaseAddr, this->dwClientStateAddr);
	Sleep(500);

	while(this->localPlayer.isDormant())
	{
		std::cout << "Waiting for local player to not be dormant...\r";
		Sleep(500);
		std::cout << " OK!\n";
	}

	// Init Glow object with addr
	this->glow = Glow(this->dwClientBaseAddr + hazedumper::signatures::dwGlowObjectManager);
	Sleep(500);

	this->updatePlayers();
	std::cout << "Players initially updated." << std::endl;
}

void Kontrollneger::updatePlayers()
{
	localPlayer.update();
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
		return false;;
	}

	input();
	updatePlayers();
	glow.update(entityList, teamIds, enemyIds);

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
