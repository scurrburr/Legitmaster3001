#pragma once
#include "../windows/pch.h"

#include "Aimbot.h"

Aimbot::Aimbot()
{
	std::cout << "Aimbot waiting for initialization." << std::endl;
}

Aimbot::Aimbot(int aimMode)
{
	this->aimMode = aimMode;
	// 1 = Closest target to crosshair
	// 2 = Closest target by distance

	std::cout << "Aimbot initialized." << std::endl;
}

void Aimbot::update(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities)
{
	if (!localPlayer.isAlive()) return;
	if (!selectTarget(aimTargets, localPlayer, entities)) return;

	vector3f localPlayerEyePos = localPlayer.getCameraPosition();
	vector3f targetBonePos = aimTargetMapIt->second.getBonePosition(8);

	vector2f currentAngles = localPlayer.getViewAngles();
	vector2f targetAngles = calcAngles(localPlayerEyePos, targetBonePos) - localPlayer.getViewPunchAngle() * 1.8f;
	vector2f diffToTargetAngles = targetAngles - currentAngles;

	// Don't smooth if difference in angles is too small.
	if (diffToTargetAngles.GetLength() < .2f)
	{
		localPlayer.setViewAngles(targetAngles);
		return;
	}

	// Aimbot did not yet lock onto a target.
	if (!this->isLocking)
	{
		ticksToTarget = (int)diffToTargetAngles.GetLength() * 3;
		ticksSinceLocking = 0;
		isLocking = true;
		currentTargetId = aimTargetMapIt->first;
	}

	if (++this->ticksSinceLocking > ticksToTarget || currentTargetId != aimTargetMapIt->first)
	{
		this->isLocking = false;
		return;
	}

	localPlayer.setViewAngles(currentAngles +
		getBezierPoint(diffToTargetAngles, (float)ticksSinceLocking / (float)ticksToTarget));
}

bool Aimbot::changeAimMode(int newAimMode)
{
	if (newAimMode > 2 || newAimMode < 1)
		return false;

	this->aimMode = newAimMode;
	return true;
}

bool Aimbot::selectTarget(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities)
{
	switch (this->aimMode) {
		case 1:
			return this->selectClosestTargetToCrosshair(aimTargets, localPlayer, entities);
		case 2:
			return this->selectClosestTarget(aimTargets, localPlayer, entities);
		default:
			return this->selectClosestTargetToCrosshair(aimTargets, localPlayer, entities);
	}
}

vector2f Aimbot::calcAngles(const vector3f src, const vector3f dst)
{
	vector2f angles;
	vector3f delta = src - dst;

	float hyp = delta.GetLength();

	angles.x = (asin(delta.z / hyp) * (180.f/(float)M_PI));
	angles.y = (atan(delta.y / delta.x) * (180.f/(float)M_PI));

	if (angles.x < -89.0f) angles.x = -89.0f;
	if (angles.x > 89.0f) angles.x = 89.0f;

	if (delta.x >= 0.0) angles.y += 180.0f;

	while (angles.y < -180.0f) angles.y += 360.0f;
	while (angles.y > 180.0f) angles.y -= 360.0f;

	return angles;
}

vector2f Aimbot::pointBetween(const vector2f start, const vector2f end, const float perc)
{
	vector2f diff = end - start;
	return start + diff * perc;
}

vector2f Aimbot::getBezierPoint(vector2f diffToTarget, float percentage)
{
	// Corner point for bezier calculation.
	vector2f cornerPoint = vector2f(sqrt(diffToTarget.x), 0.f);
	// Line from origin to corner point.
	vector2f originToCorner = pointBetween(vector2f(0.f, 0.f), cornerPoint, percentage);
	// Line from corner point to target point.
	vector2f cornerToTarget = pointBetween(cornerPoint, diffToTarget, percentage);
	// Quadratic bezier point.
	return pointBetween(originToCorner, cornerToTarget, percentage);
}

bool Aimbot::selectClosestTarget(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities)
{
	if (aimTargets.empty()) return false;

	// <Distance to target, ID of target>
	std::map<float, int> targetDistanceList;
	vector3f selfPosition = localPlayer.getCameraPosition();

	for (int i : aimTargets)
	{
		CPlayer iterPlayer = entities.at(i);
		targetDistanceList.insert(std::make_pair(abs((iterPlayer.getCameraPosition() - selfPosition).GetLength()), i));
	}

	if (targetDistanceList.empty()) return false;

	this->aimTargetMapIt = entities.find(targetDistanceList.begin()->second);
	return true;
}

bool Aimbot::selectClosestTargetToCrosshair(std::vector<int> aimTargets, CLocalPlayer localPlayer, std::map<int, CPlayer> entities)
{
	if (entities.empty()) return false;

	std::map<float, int> targetDistanceList;
	vector2f currentViewAngles = localPlayer.getViewAngles();
	vector3f currentEyePos = localPlayer.getCameraPosition();

	for (std::vector<int>::iterator i = aimTargets.begin(); i != aimTargets.end(); ++i)
	{
		CPlayer iterPlayer = entities.at(*i);

		if (iterPlayer.getID() == localPlayer.getID())
			continue;

		vector3f targetBonePos = iterPlayer.getBonePosition(8);
		vector2f targetAngles = calcAngles(currentEyePos, targetBonePos);

		float yDiff = fabs(currentViewAngles.y - targetAngles.y);
		float xDiff = fabs(currentViewAngles.x - targetAngles.x);

		if (xDiff > 15 || yDiff > 4) continue;

		targetDistanceList.insert(std::pair<float, int>(xDiff + yDiff, *i));
	}

	if (targetDistanceList.empty()) return false;

	this->aimTargetMapIt = entities.find(targetDistanceList.begin()->second);
	return true;
}
