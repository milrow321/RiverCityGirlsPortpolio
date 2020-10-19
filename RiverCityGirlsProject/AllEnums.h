#pragma once

enum class OBJECT_TEAM : int
{
	PLAYER,
	ENEMY,
	OBJECT,
	BOSS
};

enum class DIRECTION : int
{
	RIGHT,
	LEFT
};

enum class ATTACK_TYPE : int
{
	HIT1,
	HIT2,
	STUN,
	KNOCKDOWN
};

enum class DEBUG_TYPE : int
{
	PLAYER = 0,
	ENEMY = 1,
	OBJECT = 2,
	STAGE = 3,
	END = 4
};

enum class OBJECT_TYPE
{
	DESK01, DESK02, DESK03, DESK04, DESK05, BOX, FALL_CHAIR01, FALL_CHAIR02, TABLE_CHAIR01, TABLE_CHAIR02,
	TEACHER_TABLE,
	TABLE01, TABLE02, TABLE03, TABLE04, TABLE05, TABLE06, TABLE07, TABLE08,
	PILLAR, SNACKMACHINE,
	mrRudis, schoolBoyA_idle01, schoolBoyA_idle02,
	schoolBoyB_idle01, schoolBoyB_idle02,
	schoolBoyE_idle01, schoolBoyE_idle02,
	schoolGirlA_idle01, schoolGirlA_idle02,
	schoolGirlB_idle01, schoolGirlB_idle02,
	schoolGirlE_idle01, schoolGirlE_idle02,
	workingFemaleA, workingMaleD
};

enum class PARTICLE_TYPE
{
	PIECE_PILLAR, PIECE_SNACKMACHINE
};