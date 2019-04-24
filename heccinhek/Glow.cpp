#pragma once
#include "../windows/pch.h"

#include "Glow.h"

Glow::Glow()
{
  std::cout << "Glow waiting for initialization." << std::endl;
}

Glow::Glow(DWORD glowObjectManagerAddr)
{
  this->glowObjectManagerAddr = glowObjectManagerAddr;
  printf("glowObject successfully initialized! [addr=%X]", glowObjectManagerAddr);
}

void Glow::setTeamGlow(GlowObjectDefinition_t& glowObject)
{
  glowObject.m_bRenderWhenOccluded = true;
  glowObject.m_bRenderWhenUnoccluded = false;
  glowObject.R = .0118f;
  glowObject.B = .4706f;
  glowObject.G = .651f;
  glowObject.A = .7f;
}

void Glow::setEnemyGlow(GlowObjectDefinition_t& glowObject)
{
  glowObject.m_bRenderWhenOccluded = true;
  glowObject.m_bRenderWhenUnoccluded = false;
  glowObject.R =  .95f;
  glowObject.B =  .318f;
  glowObject.G =  .312f;
  glowObject.A = 1.0f;
}

void Glow::setPropGlow(GlowObjectDefinition_t& glowObject)
{
  // TODO: Specify prop glow.
}

GlowObjectDefinition_t* Glow::getGlowObjPtr(int playerIndex, std::map<int, CPlayer> entities)
{
  int glowIndex = entities.find(playerIndex)->second.getGlowIndex();
  return &(*(GlowObjectDefinition_t*)(glowObjectManagerAddr + (glowIndex * 0x38)));
}

void Glow::update(std::map<int, CPlayer> entities, std::vector<int> teamIds, std::vector<int> enemyIds)
{
  for (int id : enemyIds)
    setTeamGlow(*getGlowObjPtr(id, entities));

  for (int id : teamIds)
    setEnemyGlow(*getGlowObjPtr(id, entities));

  printf("%d enemies and %d teammates are glowing.", enemyIds.size(), teamIds.size());
}
