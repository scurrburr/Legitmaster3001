#pragma once

#include "CPlayer.h"
#include <algorithm>

class Glow
{
	private:
		DWORD glowObjectManagerAddr;

		void setTeamGlow(GlowObjectDefinition_t& glowObject);
		void setEnemyGlow(GlowObjectDefinition_t& glowObject);
		void setPropGlow(GlowObjectDefinition_t& glowObject);
		GlowObjectDefinition_t * getGlowObjPtr(int playerIndex, std::map<int, CPlayer> entities);

	public:
		Glow();
		Glow(DWORD glowObjectManagerAddr);
		void update(std::map<int, CPlayer> entities, std::vector<int> teamIds, std::vector<int> enemyIds);
};
