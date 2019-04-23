#pragma once

#include "../math/Vectors.h"
#include "CLocalPlayer.h"
#include <cmath>
#include <vector>

class Aimbot
{
	public:
		Aimbot();
		Aimbot(int aimMode);
		void update(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities);

	private:
		int aimMode;
		int ticksSinceLocking;
		int ticksToTarget;
		int currentTargetId;

		float percentage;
		vector2f lastAimPoint;
		vector2f lastDiffToTarget;

		vector2f fov;
		std::map<int, CPlayer>::iterator aimTargetMapIt;
		bool isLocking;

		bool changeAimMode(int newAimMode);
		bool selectTarget(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities);
		vector2f calcAngles(const vector3f src, const vector3f dst);
		vector2f pointBetween(const vector2f start, const vector2f end, const float time);
		vector2f getBezierPoint(vector2f diffToTarget, float percentage);
		bool selectClosestTarget(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities);
		bool selectClosestTargetToCrosshair(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities);
};
