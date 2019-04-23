#pragma once
#include <Windows.h>
#include <cstdint>
// 2019-03-29 10:04:16.304788100 UTC

struct GlowObjectDefinition_t {
	INT_PTR EntityPtr;
	float R;
	float G;
	float B;
	float A;
	BYTE pad14[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	int m_nSplitScreenSlot;
	int m_nNextFreeSlot;
};

namespace SDK
{
	typedef void(*Warning)(const char*, ...);

	//Why 989? "Only 989 characters can be output to the console at once!" ~Valve
	const UINT MSG_SIZE = 989;
};

namespace hazedumper 
{
	constexpr ::std::int64_t timestamp = 1554296346;

	namespace netvars 
	{
		const DWORD cs_gamerules_data = 0x0;
		const DWORD m_ArmorValue = 0xB328;
		const DWORD m_Collision = 0x31C;
		const DWORD m_CollisionGroup = 0x474;
		const DWORD m_Local = 0x2FBC;
		const DWORD m_MoveType = 0x25C;
		const DWORD m_OriginalOwnerXuidHigh = 0x31B4;
		const DWORD m_OriginalOwnerXuidLow = 0x31B0;
		const DWORD m_SurvivalGameRuleDecisionTypes = 0x1320;
		const DWORD m_SurvivalRules = 0xCF8;
		const DWORD m_aimPunchAngle = 0x302C;
		const DWORD m_aimPunchAngleVel = 0x3038;
		const DWORD m_angEyeAnglesX = 0xB32C;
		const DWORD m_angEyeAnglesY = 0xB330;
		const DWORD m_bBombPlanted = 0x99D;
		const DWORD m_bFreezePeriod = 0x20;
		const DWORD m_bGunGameImmunity = 0x3928;
		const DWORD m_bHasDefuser = 0xB338;
		const DWORD m_bHasHelmet = 0xB31C;
		const DWORD m_bInReload = 0x3285;
		const DWORD m_bIsDefusing = 0x3914;
		const DWORD m_bIsQueuedMatchmaking = 0x74;
		const DWORD m_bIsScoped = 0x390A;
		const DWORD m_bIsValveDS = 0x75;
		const DWORD m_bSpotted = 0x93D;
		const DWORD m_bSpottedByMask = 0x980;
		const DWORD m_bStartedArming = 0x33C0;
		const DWORD m_clrRender = 0x70;
		const DWORD m_dwBoneMatrix = 0x26A8;
		const DWORD m_fAccuracyPenalty = 0x3304;
		const DWORD m_fFlags = 0x104;
		const DWORD m_flC4Blow = 0x2990;
		const DWORD m_flDefuseCountDown = 0x29AC;
		const DWORD m_flDefuseLength = 0x29A8;
		const DWORD m_flFallbackWear = 0x31C0;
		const DWORD m_flFlashDuration = 0xA3E0;
		const DWORD m_flFlashMaxAlpha = 0xA3DC;
		const DWORD m_flLastBoneSetupTime = 0x2924;
		const DWORD m_flLowerBodyYawTarget = 0x3A74;
		const DWORD m_flNextAttack = 0x2D70;
		const DWORD m_flNextPrimaryAttack = 0x3218;
		const DWORD m_flSimulationTime = 0x268;
		const DWORD m_flTimerLength = 0x2994;
		const DWORD m_hActiveWeapon = 0x2EF8;
		const DWORD m_hMyWeapons = 0x2DF8;
		const DWORD m_hObserverTarget = 0x3388;
		const DWORD m_hOwner = 0x29CC;
		const DWORD m_hOwnerEntity = 0x14C;
		const DWORD m_iAccountID = 0x2FC8;
		const DWORD m_iClip1 = 0x3244;
		const DWORD m_iCompetitiveRanking = 0x1A84;
		const DWORD m_iCompetitiveWins = 0x1B88;
		const DWORD m_iCrosshairId = 0xB394;
		const DWORD m_iEntityQuality = 0x2FAC;
		const DWORD m_iFOV = 0x31E4;
		const DWORD m_iFOVStart = 0x31E8;
		const DWORD m_iGlowIndex = 0xA3F8;
		const DWORD m_iHealth = 0x100;
		const DWORD m_iItemDefinitionIndex = 0x2FAA;
		const DWORD m_iItemIDHigh = 0x2FC0;
		const DWORD m_iMostRecentModelBoneCounter = 0x2690;
		const DWORD m_iObserverMode = 0x3374;
		const DWORD m_iShotsFired = 0xA370;
		const DWORD m_iState = 0x3238;
		const DWORD m_iTeamNum = 0xF4;
		const DWORD m_lifeState = 0x25F;
		const DWORD m_nFallbackPaintKit = 0x31B8;
		const DWORD m_nFallbackSeed = 0x31BC;
		const DWORD m_nFallbackStatTrak = 0x31C4;
		const DWORD m_nForceBone = 0x268C;
		const DWORD m_nTickBase = 0x342C;
		const DWORD m_rgflCoordinateFrame = 0x444;
		const DWORD m_szCustomName = 0x303C;
		const DWORD m_szLastPlaceName = 0x35B0;
		const DWORD m_thirdPersonViewAngles = 0x31D8;
		const DWORD m_vecOrigin = 0x138;
		const DWORD m_vecVelocity = 0x114;
		const DWORD m_vecViewOffset = 0x108;
		const DWORD m_viewPunchAngle = 0x3020;
	}

	namespace signatures 
	{
		const DWORD clientstate_choked_commands = 0x4D28;
		const DWORD clientstate_delta_ticks = 0x174;
		const DWORD clientstate_last_outgoing_command = 0x4D24;
		const DWORD clientstate_net_channel = 0x9C;
		const DWORD convar_name_hash_table = 0x2F0F8;
		const DWORD dwClientState = 0x58BCFC;
		const DWORD dwClientState_GetLocalPlayer = 0x180;
		const DWORD dwClientState_IsHLTV = 0x4D40;
		const DWORD dwClientState_Map = 0x28C;
		const DWORD dwClientState_MapDirectory = 0x188;
		const DWORD dwClientState_MaxPlayer = 0x388;
		const DWORD dwClientState_PlayerInfo = 0x52B8;
		const DWORD dwClientState_State = 0x108;
		const DWORD dwClientState_ViewAngles = 0x4D88;
		const DWORD dwEntityList = 0x4CE34DC;
		const DWORD dwForceAttack = 0x3114BA4;
		const DWORD dwForceAttack2 = 0x3114BB0;
		const DWORD dwForceBackward = 0x3114BF8;
		const DWORD dwForceForward = 0x3114BD4;
		const DWORD dwForceJump = 0x5186978;
		const DWORD dwForceLeft = 0x3114BEC;
		const DWORD dwForceRight = 0x3114C10;
		const DWORD dwGameDir = 0x631F70;
		const DWORD dwGameRulesProxy = 0x51F8CB4;
		const DWORD dwGetAllClasses = 0xCF6BC4;
		const DWORD dwGlobalVars = 0x58BA00;
		const DWORD dwGlowObjectManager = 0x5223730;
		const DWORD dwInput = 0x512E4F0;
		const DWORD dwInterfaceLinkList = 0x8B0A24;
		const DWORD dwLocalPlayer = 0xCD2764;
		const DWORD dwMouseEnable = 0xCD82B0;
		const DWORD dwMouseEnablePtr = 0xCD8280;
		const DWORD dwPlayerResource = 0x3112F3C;
		const DWORD dwRadarBase = 0x511821C;
		const DWORD dwSensitivity = 0xCD814C;
		const DWORD dwSensitivityPtr = 0xCD8120;
		const DWORD dwSetClanTag = 0x896A0;
		const DWORD dwViewMatrix = 0x4CD4EF4;
		const DWORD dwWeaponTable = 0x512EFB8;
		const DWORD dwWeaponTableIndex = 0x323C;
		const DWORD dwYawPtr = 0xCD7F10;
		const DWORD dwZoomSensitivityRatioPtr = 0xCDD150;
		const DWORD dwbSendPackets = 0xD259A;
		const DWORD dwppDirect3DDevice9 = 0xA6030;
		const DWORD force_update_spectator_glow = 0x38DF82;
		const DWORD interface_engine_cvar = 0x3E9EC;
		const DWORD is_c4_owner = 0x39A070;
		const DWORD m_bDormant = 0xED;
		const DWORD m_pStudioHdr = 0x294C;
		const DWORD m_pitchClassPtr = 0x51184D0;
		const DWORD m_yawClassPtr = 0xCD7F10;
		const DWORD model_ambient_min = 0x58ED1C;
		const DWORD set_abs_angles = 0x1C7C70;
		const DWORD set_abs_origin = 0x1C7AB0;
	}
}