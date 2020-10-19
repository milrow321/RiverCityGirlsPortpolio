#include "stdafx.h"
#include "PlayGround.h"

#include "MainScene.h"
#include "StageScene.h"

#include <string>

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	GameNode::init(true);

	// 모든 이미지 IMAGE_MANAGER에 등록
	
	// * Object
	// ** DESK
	IMAGE_MANAGER->addImage("OBJECT_DESK01",						L"resources/images/object/03_Detention_OBJ_Desks_01.png");
	IMAGE_MANAGER->addImage("OBJECT_DESK02",						L"resources/images/object/03_Detention_OBJ_Desks_02.png");
	IMAGE_MANAGER->addImage("OBJECT_DESK03",						L"resources/images/object/03_Detention_OBJ_Desks_03.png");
	// *** DESK_ENEMY
	IMAGE_MANAGER->addFrameImage("OBJECT_DESK_boy_idle01",			L"resources/images/object/sit_enemy/boy_sit_idle01.png", 4, 1);
	IMAGE_MANAGER->addImage("OBJECT_DESK_boy_idle02",				L"resources/images/object/sit_enemy/boy_sit_idle02.png");
	IMAGE_MANAGER->addFrameImage("OBJECT_DESK_boy_getUp",			L"resources/images/object/sit_enemy/boy_desk_getup.png", 6, 1);
	IMAGE_MANAGER->addFrameImage("OBJECT_DESK_girl_idle01",			L"resources/images/object/sit_enemy/girl_sit_idle01.png", 2, 1);
	IMAGE_MANAGER->addImage("OBJECT_DESK_girl_idle02",				L"resources/images/object/sit_enemy/girl_sit_idle02.png");
	IMAGE_MANAGER->addFrameImage("OBJECT_DESK_girl_getUp",			L"resources/images/object/sit_enemy/girl_desk_getup.png", 5, 1);
	// ** BOX
	IMAGE_MANAGER->addImage("OBJECT_BOX",							L"resources/images/object/wood_crate.png");
	// *** BOX_PIECE
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE01",					L"resources/images/object/wood_crate_piece0001.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE02",					L"resources/images/object/wood_crate_piece0002.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE03",					L"resources/images/object/wood_crate_piece0003.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE04",					L"resources/images/object/wood_crate_piece0004.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE05",					L"resources/images/object/wood_crate_piece0005.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE06",					L"resources/images/object/wood_crate_piece0006.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE07",					L"resources/images/object/wood_crate_piece0007.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE08",					L"resources/images/object/wood_crate_piece0008.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE09",					L"resources/images/object/wood_crate_piece0009.png");
	IMAGE_MANAGER->addImage("OBJECT_BOX_PIECE10",					L"resources/images/object/wood_crate_piece0010.png");
	// ** TEACHER_TABLE
	IMAGE_MANAGER->addImage("OBJECT_TEACHER_TABLE",					L"resources/images/object/L3_teacher_table.png");
	// ** TABLE
	IMAGE_MANAGER->addImage("OBJECT_TABLE01",						L"resources/images/object/cafeteria_l3_table_1.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE02",						L"resources/images/object/cafeteria_l3_table_2.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE03",						L"resources/images/object/cafeteria_l3_table_3.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE04",						L"resources/images/object/cafeteria_l3_table_4.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE05",						L"resources/images/object/cafeteria_table1.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE06",						L"resources/images/object/cafeteria_table2.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE07",						L"resources/images/object/cafeteria_table3.png");
	IMAGE_MANAGER->addImage("OBJECT_TABLE08",						L"resources/images/object/cafeteria_table4.png");
	// ** CHAIR
	IMAGE_MANAGER->addImage("OBJECT_CHAIR01",						L"resources/images/object/05_Detention_Chair_2.png");
	IMAGE_MANAGER->addImage("OBJECT_CHAIR02",						L"resources/images/object/05_Detention_Chair_3.png");
	IMAGE_MANAGER->addImage("OBJECT_CHAIR03",						L"resources/images/object/cafeteria_l3_chair_1.png");
	IMAGE_MANAGER->addImage("OBJECT_CHAIR04",						L"resources/images/object/cafeteria_l3_chair_2.png");
	// ** FOOD
	IMAGE_MANAGER->addImage("OBJECT_FOOD_APPLE",					L"resources/images/object/RCG_Consumables_apple.png");
	IMAGE_MANAGER->addImage("OBJECT_FOOD_CHILI",					L"resources/images/object/RCG_Consumables_chili.png");
	IMAGE_MANAGER->addImage("OBJECT_FOOD_CHIKEN",					L"resources/images/object/RCG_Consumables_hen.png");
	// ** MONEY
	IMAGE_MANAGER->addFrameImage("OBJECT_MOVE_COIN_SILVER",			L"resources/images/object/money/fx_coin_anim_silver.png", 4, 4);
	IMAGE_MANAGER->addFrameImage("OBJECT_MOVE_COIN_GOLD",			L"resources/images/object/money/fx_gold_coin_spin.png", 4, 4);
	IMAGE_MANAGER->addFrameImage("OBJECT_MOVE_MONEY_BLUE",			L"resources/images/object/money/fx_money_blue_4x4.png", 4, 4);
	IMAGE_MANAGER->addFrameImage("OBJECT_MOVE_MONEY_GREEN",			L"resources/images/object/money/fx_money_green_4x4.png", 4, 4);
	IMAGE_MANAGER->addFrameImage("OBJECT_MOVE_MONEY_PURPLE",		L"resources/images/object/money/fx_money_purple_4x4.png", 4, 4);
	// ** SNACKMACHINE
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_RIGHT",			L"resources/images/object/cafeteria_snackmachine_right.png");
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_RIGHT_BROKEN",		L"resources/images/object/cafeteria_snackmachine_right_broken.png");
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_LEFT",				L"resources/images/object/cafeteria_snackmachine_left.png");
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_LEFT_BROKEN",		L"resources/images/object/cafeteria_snackmachine_left_broken.png");
	// *** SNACKMACHINE_PIECE
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_PIECE01",			L"resources/images/object/breakMachine_piece01.png");
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_PIECE02",			L"resources/images/object/breakMachine_piece02.png");
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_PIECE03",			L"resources/images/object/breakMachine_piece03.png");
	IMAGE_MANAGER->addImage("OBJECT_SNACKMACHINE_PIECE04",			L"resources/images/object/breakMachine_piece04.png");
	// ** PILLAR
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_RIGHT",					L"resources/images/object/lobby_l3_pillar_3.png");
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_LEFT",					L"resources/images/object/lobby_l3_pillar_1.png");
	// *** PILLAR_INVISIBLE
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_INVISIBLE_RIGHT",		L"resources/images/object/L3_pillar4 #318076.png");
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_INVISIBLE_LEFT",			L"resources/images/object/L3_pillar4 #317999.png");
	// *** PILLAR_PIECE
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_PIECE01",				L"resources/images/object/fx_rock_for_pillar_01.png");
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_PIECE02",				L"resources/images/object/fx_rock_for_pillar_02.png");
	IMAGE_MANAGER->addImage("OBJECT_PILLAR_PIECE03",				L"resources/images/object/fx_rock_for_pillar_03.png");
	// ** MrRudis
	IMAGE_MANAGER->addFrameImage("OBJECT_MrRudis_idle",				L"resources/images/object/objectHuman_update/RCG_MrRudis_idle_update.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_MrRudis_reaction",			L"resources/images/object/objectHuman_update/RCG_MrRudis_reaction_update.png", 5, 2);
	// ** schoolBoyA
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyA_idle01",		L"resources/images/object/objectHuman_update/schoolBoyA_idle.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyA_idle02",		L"resources/images/object/objectHuman_update/schoolBoyA_idle02.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyA_reaction",		L"resources/images/object/objectHuman_update/schoolboyA_react.png", 3, 2);
	// ** schoolBoyB
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyB_idle01",		L"resources/images/object/objectHuman_update/schoolBoyB_idleA.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyB_idle02",		L"resources/images/object/objectHuman_update/schoolBoyB_idleB.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyB_reaction",		L"resources/images/object/objectHuman_update/schoolboyB_react.png", 3, 2);
	// ** schoolBoyE
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyE_idle01",		L"resources/images/object/objectHuman_update/schoolBoyE_idleA.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyE_idle02",		L"resources/images/object/objectHuman_update/schoolBoyE_idleB.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolBoyE_reaction",		L"resources/images/object/objectHuman_update/schoolboyE_react.png", 3, 2);
	// ** schoolGirlA
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlA_idle01",	 	L"resources/images/object/objectHuman_update/schoolgirlA_idleA.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlA_idle02",		L"resources/images/object/objectHuman_update/schoolgirlA_idleB.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlA_reaction",	 	L"resources/images/object/objectHuman_update/schoolgirlA_react.png", 3, 2);
	// ** schoolGirlB
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlB_idle01",		L"resources/images/object/objectHuman_update/schoolgirlB_idleA.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlB_idle02",	    L"resources/images/object/objectHuman_update/schoolgirlB_idleB.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlB_reaction",     L"resources/images/object/objectHuman_update/schoolgirlB_react.png", 3, 2);
	// ** schoolGirlE
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlE_idle01",       L"resources/images/object/objectHuman_update/schoolgirlE_idleA.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlE_idle02",       L"resources/images/object/objectHuman_update/schoolgirlE_idleB.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_schoolGirlE_reaction",     L"resources/images/object/objectHuman_update/schoolgirlE_react.png", 3, 2);
	// ** workingFemaleA
	IMAGE_MANAGER->addFrameImage("OBJECT_workingFemaleA_idle01",    L"resources/images/object/objectHuman_update/WorkingFemaleA_idle.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_workingFemaleA_reaction",	L"resources/images/object/objectHuman_update/WorkingFemaleA_react.png", 3, 2);
	// ** workingMaleD
	IMAGE_MANAGER->addFrameImage("OBJECT_workingMaleD_idle01",		L"resources/images/object/objectHuman_update/WorkingMaleD_idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("OBJECT_workingMaleD_reaction",	L"resources/images/object/objectHuman_update/WorkingMaleD_react.png", 3, 2);

	// * Player
	IMAGE_MANAGER->addFrameImage("Kyoko_battle_start", L"resources/images/characters/kyoko/Kyoko_battle_start.png", 26, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_idle", L"resources/images/characters/kyoko/Kyoko_idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_walk", L"resources/images/characters/kyoko/Kyoko_walk.png",12,2);
	IMAGE_MANAGER->addFrameImage("Kyoko_run", L"resources/images/characters/kyoko/Kyoko_run.png", 16, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_jump", L"resources/images/characters/kyoko/Kyoko_jump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_walljump", L"resources/images/characters/kyoko/Kyoko_walljump.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_attack1", L"resources/images/characters/kyoko/Kyoko_qc1.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_attack2", L"resources/images/characters/kyoko/Kyoko_qc2.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_attack3", L"resources/images/characters/kyoko/Kyoko_qc3.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_backelbow", L"resources/images/characters/kyoko/Kyoko_backelbow.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_buttbump", L"resources/images/characters/kyoko/Kyoko_buttbump.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_gethit", L"resources/images/characters/kyoko/Kyoko_gethits.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_axekick", L"resources/images/characters/kyoko/Kyoko_axekick.png", 13, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_dive", L"resources/images/characters/kyoko/Kyoko_dive.png", 21, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_airstep", L"resources/images/characters/kyoko/Kyoko_airstep.png", 11, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_guard", L"resources/images/characters/kyoko/Kyoko_guard.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_standup", L"resources/images/characters/kyoko/Kyoko_standup.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_knockout", L"resources/images/characters/kyoko/Kyoko_knockout.png", 24, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_stun", L"resources/images/characters/kyoko/Kyoko_stun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("Kyoko_gameover", L"resources/images/characters/kyoko/Kyoko_gameover.png", 26, 2);

	//Enemy 이미지 
    //schoolBoy
	IMAGE_MANAGER->addFrameImage("schoolboy_attack1", L"resources/images/characters/enemy_schoolboy/SchoolBoyAttack1.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_attack2", L"resources/images/characters/enemy_schoolboy/SchoolBoyAttack2.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_attack3", L"resources/images/characters/enemy_schoolboy/SchoolBoyAttack3.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_begging", L"resources/images/characters/enemy_schoolboy/SchoolBoybegging.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_block", L"resources/images/characters/enemy_schoolboy/SchoolBoyBlock.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_getHit", L"resources/images/characters/enemy_schoolboy/SchoolBoyGetHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_groundHit", L"resources/images/characters/enemy_schoolboy/SchoolBoyGroundHit.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_heldHit", L"resources/images/characters/enemy_schoolboy/SchoolBoyHeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_heldRelease", L"resources/images/characters/enemy_schoolboy/SchoolBoyHeldRelease.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_idle", L"resources/images/characters/enemy_schoolboy/SchoolBoyIdle.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_jump", L"resources/images/characters/enemy_schoolboy/SchoolBoyJump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_jumpAttack", L"resources/images/characters/enemy_schoolboy/SchoolBoyJumpPunch.png", 6, 2);
	//IMAGE_MANAGER->addFrameImage("schoolboy_groundDown", L"resources/images/characters/enemy_schoolboy/SchoolBoyKcockDown.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_knockDown", L"resources/images/characters/enemy_schoolboy/schoolBoyKnockDown2.png", 24, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_standUp", L"resources/images/characters/enemy_schoolboy/schoolBoyStandUp2.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_run", L"resources/images/characters/enemy_schoolboy/SchoolBoyRun.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_skill", L"resources/images/characters/enemy_schoolboy/SchoolBoySandToss.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_stun", L"resources/images/characters/enemy_schoolboy/SchoolBoyStun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_walk", L"resources/images/characters/enemy_schoolboy/SchoolBoyWalk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("schoolboy_runAttack", L"resources/images/characters/enemy_schoolboy/SchoolDashAttack.png", 7, 2);
	//schoolGirl
	//IMAGE_MANAGER->addFrameImage("schoolgirl_groundDown", L"resources/images/characters/enemy_schoolgirl/blowBack.png", 33, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_knockDown", L"resources/images/characters/enemy_schoolgirl/knockDown.png", 23, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_standUp", L"resources/images/characters/enemy_schoolgirl/standUP.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_getHit", L"resources/images/characters/enemy_schoolgirl/getHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_heldHit", L"resources/images/characters/enemy_schoolgirl/HeldHit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_heldRelease", L"resources/images/characters/enemy_schoolgirl/잡기 풀기.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_idle", L"resources/images/characters/enemy_schoolgirl/Idle.png", 10, 2);	
	IMAGE_MANAGER->addFrameImage("schoolgirl_stun", L"resources/images/characters/enemy_schoolgirl/stun.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_walk", L"resources/images/characters/enemy_schoolgirl/Walk.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_run", L"resources/images/characters/enemy_schoolgirl/run.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_block", L"resources/images/characters/enemy_schoolgirl/가드.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_groundHit", L"resources/images/characters/enemy_schoolgirl/그라운드 히트.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_attack1", L"resources/images/characters/enemy_schoolgirl/잽.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_attack2", L"resources/images/characters/enemy_schoolgirl/니킥.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_attack3", L"resources/images/characters/enemy_schoolgirl/발차기.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_skill", L"resources/images/characters/enemy_schoolgirl/회전킥.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_jump", L"resources/images/characters/enemy_schoolgirl/점프.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("schoolgirl_begGing", L"resources/images/characters/enemy_schoolgirl/항복.png", 3, 2);
	//치어걸
	IMAGE_MANAGER->addFrameImage("cheergirl_block", L"resources/images/characters/enemy_cheergirl/block.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_groundHit", L"resources/images/characters/enemy_cheergirl/groundhit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_idle", L"resources/images/characters/enemy_cheergirl/idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_attack1", L"resources/images/characters/enemy_cheergirl/japAttack.png", 6, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_jump", L"resources/images/characters/enemy_cheergirl/jump.png", 3, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_run", L"resources/images/characters/enemy_cheergirl/run.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_attack2", L"resources/images/characters/enemy_cheergirl/spinpoom.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_begGing", L"resources/images/characters/enemy_cheergirl/begging.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_blownBack", L"resources/images/characters/enemy_cheergirl/blownback.png", 23, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_skill", L"resources/images/characters/enemy_cheergirl/cartwheel.png", 15, 2); // 치어걸은 회피스킬
	IMAGE_MANAGER->addFrameImage("cheergirl_getHit", L"resources/images/characters/enemy_cheergirl/gethits.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_heldRelease", L"resources/images/characters/enemy_cheergirl/grab_release.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_groundUp", L"resources/images/characters/enemy_cheergirl/groundup.png", 11, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_stun", L"resources/images/characters/enemy_cheergirl/stun.png", 5, 2);
	IMAGE_MANAGER->addFrameImage("cheergirl_walk", L"resources/images/characters/enemy_cheergirl/walk.png", 12, 2);	
	IMAGE_MANAGER->addFrameImage("cheergirl_jumpAttack", L"resources/images/characters/enemy_cheergirl/divekick.png", 13, 2);
	//보스
	IMAGE_MANAGER->addFrameImage("boss_block", L"resources/images/characters/boss_misuzu/Misuzu_block.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("boss_walk", L"resources/images/characters/boss_misuzu/MizusuWalk.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("boss_laugh", L"resources/images/characters/boss_misuzu/RCG_Misuzu_taunt_update.png", 23, 2);
	IMAGE_MANAGER->addFrameImage("boss_powerAttack", L"resources/images/characters/boss_misuzu/MizusuWUPunch.png", 27, 2);
	IMAGE_MANAGER->addFrameImage("boss_blownBack", L"resources/images/characters/boss_misuzu/RCG_Misuzu_blownback.png", 22, 2);
	IMAGE_MANAGER->addFrameImage("boss_roar", L"resources/images/characters/boss_misuzu/RCG_Misuzu_roar.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("boss_defeat", L"resources/images/characters/boss_misuzu/RCG_Misuzu_defeat.png", 13, 2);
	IMAGE_MANAGER->addFrameImage("boss_dizzy", L"resources/images/characters/boss_misuzu/RCG_Misuzu_dizzy.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("boss_attack1", L"resources/images/characters/boss_misuzu/RCG_Misuzu_elbow.png", 11, 2);
	IMAGE_MANAGER->addFrameImage("boss_attack2", L"resources/images/characters/boss_misuzu/RCG_Misuzu_slap.png", 14, 2);
	IMAGE_MANAGER->addFrameImage("boss_getHit", L"resources/images/characters/boss_misuzu/RCG_Misuzu_GetHit.png", 9, 2);
	IMAGE_MANAGER->addFrameImage("boss_knockdown", L"resources/images/characters/boss_misuzu/RCG_Misuzu_knockdown.png", 10, 2);
	IMAGE_MANAGER->addFrameImage("boss_getup", L"resources/images/characters/boss_misuzu/RCG_Misuzu_getup3.png", 15, 2);	
	IMAGE_MANAGER->addFrameImage("boss_groundHit", L"resources/images/characters/boss_misuzu/RCG_Misuzu_groundhit.png", 4, 2);
	IMAGE_MANAGER->addFrameImage("boss_idle", L"resources/images/characters/boss_misuzu/RCG_Misuzu_idle.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("boss_falling", L"resources/images/characters/boss_misuzu/RCG_Misuzu_meteor_falling.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("boss_fallingmiss", L"resources/images/characters/boss_misuzu/RCG_Misuzu_meteor_landed_miss.png", 19, 2);
	IMAGE_MANAGER->addFrameImage("boss_jump", L"resources/images/characters/boss_misuzu/RCG_Misuzu_meteor_jump.png", 8, 2);
	IMAGE_MANAGER->addFrameImage("boss_faseupdate", L"resources/images/characters/boss_misuzu/RCG_Misuzu_roar.png", 12, 2);
	IMAGE_MANAGER->addFrameImage("boss_tackle_init", L"resources/images/characters/boss_misuzu/RCG_Misuzu_tackle_initial.png", 5, 2);
	IMAGE_MANAGER->addFrameImage("boss_tackle_loop", L"resources/images/characters/boss_misuzu/RCG_Misuzu_tackle_loop.png", 11, 2);
	IMAGE_MANAGER->addFrameImage("boss_electric", L"resources/images/characters/boss_misuzu/electric.png", 2, 2);
	IMAGE_MANAGER->addFrameImage("boss_groundbreak", L"resources/images/characters/boss_misuzu/groundbreak.png", 1, 1);


	// * 스테이지
	// ** 스테이지 배경 이미지 추가
	IMAGE_MANAGER->addImage("STAGE_1", L"resources/images/stages/stage_1.png");
	IMAGE_MANAGER->addImage("STAGE_2", L"resources/images/stages/stage_2.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_BEFORE", L"resources/images/stages/stage_boss_before.png");
	IMAGE_MANAGER->addImage("STAGE_BOSS_AFTER", L"resources/images/stages/stage_boss_after.png");
	IMAGE_MANAGER->addImage("screenBorder", L"resources/images/UI/blackBorder.png");			// 플레이화면 테두리


	// * UI
	IMAGE_MANAGER->addImage("blackScreen", L"resources/images/UI/blackScreen.png");				// 검은 화면입니다.

	IMAGE_MANAGER->addFrameImage("loading", L"resources/images/UI/loadingFrame.png", 4, 1);

	IMAGE_MANAGER->addFrameImage("chainLock_top"	, L"resources/images/UI/lock/chain_top_lock.png"	, 1, 13);	// 위 사슬 잠금
	IMAGE_MANAGER->addFrameImage("chainLock_bot"	, L"resources/images/UI/lock/chain_bot_lock.png"	, 1, 13);	// 밑 사슬 잠금
	IMAGE_MANAGER->addFrameImage("chainLock_left"	, L"resources/images/UI/lock/chain_left_lock.png"	, 13, 1);	// 좌 사슬 잠금
	IMAGE_MANAGER->addFrameImage("chainLock_right"	, L"resources/images/UI/lock/chain_right_lock.png"	, 13, 1);	// 우 사슬 잠금

	IMAGE_MANAGER->addFrameImage("chainUnlock_top"	, L"resources/images/UI/lock/chain_top_unlock.png"	, 1, 3);	// 위 사슬 언락
	IMAGE_MANAGER->addFrameImage("chainUnlock_bot"	, L"resources/images/UI/lock/chain_bot_unlock.png"	, 1, 3);	// 밑 사슬 언락
	IMAGE_MANAGER->addFrameImage("chainUnlock_left"	, L"resources/images/UI/lock/chain_left_unlock.png"	, 3, 1);	// 좌 사슬 언락
	IMAGE_MANAGER->addFrameImage("chainUnlock_right", L"resources/images/UI/lock/chain_right_unlock.png", 3, 1);	// 우 사슬 언락

	IMAGE_MANAGER->addFrameImage("lock_4", L"resources/images/UI/lock/lock_1.png",  7, 1);	// 자물쇠 잠금 4단계
	IMAGE_MANAGER->addFrameImage("lock_3", L"resources/images/UI/lock/lock_2.png",  7, 1);	// 자물쇠 잠금 3단계
	IMAGE_MANAGER->addFrameImage("lock_2", L"resources/images/UI/lock/lock_3.png",  8, 1);	// 자물쇠 잠금 2단계
	IMAGE_MANAGER->addFrameImage("lock_1", L"resources/images/UI/lock/lock_4.png", 10, 1);	// 자물쇠 잠금 1단계
	IMAGE_MANAGER->addFrameImage("lock_0", L"resources/images/UI/lock/lock_5.png",  9, 1);	// 자물쇠 잠금 부서짐

	IMAGE_MANAGER->addImage("playerBackBar"	, L"resources/images/UI/kyoko_HP_backFrame.png"	);	// 플레이어 프레임 뒤
	IMAGE_MANAGER->addImage("playerDigit"	, L"resources/images/UI/kyoko_hp_digit.png"		);	// 플레이어 체력 앞
	IMAGE_MANAGER->addImage("playerExpFront", L"resources/images/UI/kyoko_exp_frontBar.png"	);	// 플레이어 경험치 앞
	IMAGE_MANAGER->addImage("playerExpBack"	, L"resources/images/UI/kyoko_exp_backBar.png"	);	// 플레이어 경험치 뒤
	IMAGE_MANAGER->addImage("playerHpFrame"	, L"resources/images/UI/kyoko_frontFrame.png"	);	// 플레이어 체력 프레임	
	IMAGE_MANAGER->addImage("bossBackBar"	, L"resources/images/UI/boss_hp_backBar.png"	);	// 보스 체력 뒤
	IMAGE_MANAGER->addImage("bossFrontBar"	, L"resources/images/UI/boss_hp_frontBar.png"	);	// 보스 체력 앞
	IMAGE_MANAGER->addImage("bossHpFrame"	, L"resources/images/UI/boss_HP_frame.png"		);	// 보스 체력 프레임
	IMAGE_MANAGER->addImage("unlockDoor"	, L"resources/images/UI/door_unlock.png"		);	// 열린 문
	IMAGE_MANAGER->addImage("lockDoor"		, L"resources/images/UI/door_lock.png"			);	// 닫힌 문
	IMAGE_MANAGER->addImage("shopDoor"		, L"resources/images/UI/door_shop.png"			);	// 상점 문
	IMAGE_MANAGER->addImage("heart"			, L"resources/images/UI/closeHeart.png"			);	// 마무리 하트
	IMAGE_MANAGER->addImage("shopFrame"		, L"resources/images/UI/shop/backGround.png"	);	// 상점 프레임
	IMAGE_MANAGER->addImage("shopSelectBar"	, L"resources/images/UI/shop/selectionBar.png"	);	// 상점 아이템 선택
	IMAGE_MANAGER->addImage("shop_BuyButton", L"resources/images/UI/shop/buy_button.png"	);	// 구매 버튼
	IMAGE_MANAGER->addImage("item_1"		, L"resources/images/UI/shop/item_1.png"		);	// 아이템 1번
	IMAGE_MANAGER->addImage("item_2"		, L"resources/images/UI/shop/item_2.png"		);	// 아이템 2번
	IMAGE_MANAGER->addImage("item_3"		, L"resources/images/UI/shop/item_3.png"		);	// 아이템 3번
	IMAGE_MANAGER->addImage("item_4"		, L"resources/images/UI/shop/item_4.png"		);	// 아이템 4번

	IMAGE_MANAGER->addFrameImage("levelUp"	, L"resources/images/UI/level_up.png", 4, 1		);	// 레벨업!!
	// 다이얼로그 이미지입니다.
	IMAGE_MANAGER->addImage("kyokoName"		, L"resources/images/UI/dialogue/Kyoko_name.png"	);	// 쿄코 이름
	IMAGE_MANAGER->addImage("misakoName"	, L"resources/images/UI/dialogue/Misako_name.png"	);	// 미사코 이름
	IMAGE_MANAGER->addImage("misuzuName"	, L"resources/images/UI/dialogue/Misuzu_name.png"	);	// 미스즈 이름
	IMAGE_MANAGER->addImage("skipFront"		, L"resources/images/UI/dialogue/skip_full.png"		);	// 스킵 막대 앞
	IMAGE_MANAGER->addImage("skipBack"		, L"resources/images/UI/dialogue/skip_fill.png"		);	// 스킵 막대 뒤	

	// 모든 사운드 SOUND_MANAGER에 등록

	// * BGM
	SOUND_MANAGER->addSound("BGM_Classroom",				"resources/sound/Classroom.mp3", false, true);
	SOUND_MANAGER->addSound("BGM_Hall",						"resources/sound/Hall.mp3", false, true);
	// * UI_Sound
	SOUND_MANAGER->addSound("UI_cancel",					"resources/sound/UISound/cancel.mp3", false, false);
	SOUND_MANAGER->addSound("UI_characterSelect",			"resources/sound/UISound/characterSelect.mp3", false, false);
	SOUND_MANAGER->addSound("UI_confirm",					"resources/sound/UISound/confirm.mp3", false, false);
	SOUND_MANAGER->addSound("UI_PhoneMenu",					"resources/sound/UISound/PhoneMenu.mp3", false, false);
	SOUND_MANAGER->addSound("UI_scroll",					"resources/sound/UISound/scroll.mp3", false, false);
	SOUND_MANAGER->addSound("UI_lock",						"resources/sound/UISound/lock.mp3", false, false);
	
	// * Stage_Sound
	SOUND_MANAGER->addSound("STAGE_getEXP",					"resources/sound/stageSound/getEXP.mp3", false, false);
	SOUND_MANAGER->addSound("STAGE_getMoney",				"resources/sound/stageSound/getMoney.mp3", false, false);
	SOUND_MANAGER->addSound("STAGE_HitSound1",				"resources/sound/stageSound/HitSound.mp3", false, false);
	SOUND_MANAGER->addSound("STAGE_HitSound2",				"resources/sound/stageSound/HitSound2.mp3", false, false);
	SOUND_MANAGER->addSound("STAGE_HitSound3",				"resources/sound/stageSound/HitSound3.mp3", false, false);
	SOUND_MANAGER->addSound("GameOver",                     "resources/sound/stageSound/gameOver.mp3", false, false);
	// * Kyoko
	
	SOUND_MANAGER->addSound("KYOKO_BackElbow1",				"resources/sound/stageSound/Kyoko/KyokoBackElbow.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_BackElbow2",				"resources/sound/stageSound/Kyoko/KyokoBackElbow2.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Chop1",					"resources/sound/stageSound/Kyoko/KyokoChop.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Chop2",					"resources/sound/stageSound/Kyoko/KyokoChop2.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Chop3",					"resources/sound/stageSound/Kyoko/KyokoChop3.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Combo",					"resources/sound/stageSound/Kyoko/KyokoCombo3.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Dive1",					"resources/sound/stageSound/Kyoko/KyokoDive.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Dive2",					"resources/sound/stageSound/Kyoko/KyokoDive2.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GameOver1",               "resources/sound/stageSound/Kyoko/KyokoGameOver1.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GameOver2",               "resources/sound/stageSound/Kyoko/KyokoGameOver2.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GetHit1",				"resources/sound/stageSound/Kyoko/KyokoGetHit.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GetHit2",				"resources/sound/stageSound/Kyoko/KyokoGetHit2.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Grab",					"resources/sound/stageSound/Kyoko/KyoKoGrab.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GrabHit1",				"resources/sound/stageSound/Kyoko/KyokoGrabHit.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GrabHit2",				"resources/sound/stageSound/Kyoko/KyokoGrabHit2.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_GrabHit3",				"resources/sound/stageSound/Kyoko/KyokoGrabHit3.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_HeavyAtkKick",			"resources/sound/stageSound/Kyoko/KyokoHeavyAtkKick.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_HipAttack1",				"resources/sound/stageSound/Kyoko/KyokoHipAttack.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_HipAttack2",	            "resources/sound/stageSound/Kyoko/KyokoHipAttackWithoutVoice.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Jump",					"resources/sound/stageSound/Kyoko/KyokoJump.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_JumpKick",				"resources/sound/stageSound/Kyoko/KyokoJumpKick.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_LevelUP",				"resources/sound/stageSound/Kyoko/KyokoLevelUP.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Run",					"resources/sound/stageSound/Kyoko/KyokoRun.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_Jump",                   "resources/sound/stageSound/Kyoko/KyokoJump.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_StageUp",				"resources/sound/stageSound/Kyoko/KyokoStageUp.mp3", false, false);
	SOUND_MANAGER->addSound("KYOKO_StandUp",				"resources/sound/stageSound/Kyoko/KyokoStandUp.mp3", false, false);
	
	// * BOSS_Misuzu
	SOUND_MANAGER->addSound("Boss_TalkingBGM",				"resources/sound/stageSound/Boss/talking.mp3", false, true);
	SOUND_MANAGER->addSound("Boss_Speek",					"resources/sound/stageSound/Boss/bossSpeek.mp3", false, false);
	SOUND_MANAGER->addSound("Boss_Talk",					"resources/sound/stageSound/Boss/bossTalk.mp3", false, false);
	SOUND_MANAGER->addSound("Boss_StageBGM",				"resources/sound/stageSound/Boss/Effect/BossStageBGM.mp3", false, true);
	// ** BOSS_Effect
	SOUND_MANAGER->addSound("Boss_Effect_2Phase",			"resources/sound/stageSound/Boss/Effect/Boss2PaceSound.mp3", false, false);
	SOUND_MANAGER->addSound("Boss_Effect_3Phase",			"resources/sound/stageSound/Boss/Effect/Boss3PaceSound.mp3", false, false);
	SOUND_MANAGER->addSound("Boss_Effect_DropSound",		"resources/sound/stageSound/Boss/Effect/BossDropSound.mp3", false, false);
	SOUND_MANAGER->addSound("Boss_Effect_Jump",				"resources/sound/stageSound/Boss/Effect/BossJump.mp3", false, false);
	SOUND_MANAGER->addSound("Boss_Effect_WUPunch",			"resources/sound/stageSound/Boss/Effect/BossWUPunch.mp3", false, false);
	// ** BOSS_Voice
	SOUND_MANAGER->addSound("BOSS_Voice_2Phase",			"resources/sound/stageSound/Boss/voice/Boss2Pace.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_3Phase",			"resources/sound/stageSound/Boss/voice/Boss3PaceSound.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Chop",				"resources/sound/stageSound/Boss/voice/BossChop.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Drop",				"resources/sound/stageSound/Boss/voice/BossDrop.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Elbow",				"resources/sound/stageSound/Boss/voice/BossElbow.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Elbow2",			"resources/sound/stageSound/Boss/voice/BossElbow2.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_GetHit",			"resources/sound/stageSound/Boss/voice/BossGetHit.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_GroundShotGun",		"resources/sound/stageSound/Boss/voice/BossGroundShotGun.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Laugh1",			"resources/sound/stageSound/Boss/voice/BossLaugh.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Laugh2",			"resources/sound/stageSound/Boss/voice/BossLaugh2.mp3", false, false);
	SOUND_MANAGER->addSound("BOSS_Voice_Scream",			"resources/sound/stageSound/Boss/voice/BossScream.mp3", false, true);
	// * CheerLeader
	SOUND_MANAGER->addSound("CheerLeader_Attack1",			"resources/sound/stageSound/cheerLeader/cheerAttack.mp3", false, false);
	SOUND_MANAGER->addSound("CheerLeader_Attack2",			"resources/sound/stageSound/cheerLeader/cheerAttack2.mp3", false, false);
	SOUND_MANAGER->addSound("CheerLeader_Attack3",			"resources/sound/stageSound/cheerLeader/cheerAttack3.mp3", false, false);
	SOUND_MANAGER->addSound("CheerLeader_Begging",			"resources/sound/stageSound/cheerLeader/cheerBegging.mp3", false, true);
	SOUND_MANAGER->addSound("CheerLeader_Jap",				"resources/sound/stageSound/cheerLeader/cheerJap.mp3", false, false);
	SOUND_MANAGER->addSound("CheerLeader_JumpAtk",			"resources/sound/stageSound/cheerLeader/cheerJumpAtk.mp3", false, false);
	SOUND_MANAGER->addSound("CheerLeader_Wow",				"resources/sound/stageSound/cheerLeader/cheerWow.mp3", false, false);
	// * SchoolBoy
	SOUND_MANAGER->addSound("SchoolBoy_Attack",				"resources/sound/stageSound/SchoolBoy/schoolBoyAttack.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolBoy_Begging",			"resources/sound/stageSound/SchoolBoy/schoolBoyBegging.mp3", false, true);
	SOUND_MANAGER->addSound("SchoolBoy_GetHit1",			"resources/sound/stageSound/SchoolBoy/schoolBoyGetHit.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolBoy_GetHit2",			"resources/sound/stageSound/SchoolBoy/schoolBoyGetHit2.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolBoy_GetHit3",			"resources/sound/stageSound/SchoolBoy/schoolBoyGetHit3.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolBoy_GetHit4",			"resources/sound/stageSound/SchoolBoy/schoolBoyGetHit4.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolBoy_SandToss",			"resources/sound/stageSound/SchoolBoy/schoolBoySandToss.mp3", false, false);
	// * SchoolGirl
	SOUND_MANAGER->addSound("SchoolGirl_Attack1",			"resources/sound/stageSound/schoolGirl/SchoolGirlAttack.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolGirl_Attack2",			"resources/sound/stageSound/schoolGirl/SchoolGirlAttack2.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolGirl_Attack3",			"resources/sound/stageSound/schoolGirl/SchoolGirlAttack3.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolGirl_Begging",			"resources/sound/stageSound/schoolGirl/SchoolGirlBegging.mp3", false, true);
	SOUND_MANAGER->addSound("SchoolGirl_GetHit2",			"resources/sound/stageSound/schoolGirl/SchoolGirlGetHit2.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolGirl_GetHit3",			"resources/sound/stageSound/schoolGirl/SchoolGirlGetHit3.mp3", false, false);
	SOUND_MANAGER->addSound("SchoolGirl_tornado",			"resources/sound/stageSound/schoolGirl/SchoolGirltornado.mp3", false, false);

	for (int i = 1; i <= 6; i++)
	{
		string file;
		wstring fileW = L"";
		// 쿄코
		if (i <= 5)
		{
			file = "resources/images/UI/dialogue/Kyoko_" + to_string(i) + ".png";
			fileW = L"";
			fileW.assign(file.begin(), file.end());
			IMAGE_MANAGER->addImage("kyoko_" + to_string(i), fileW);
		}
		// 미사코
		file = "resources/images/UI/dialogue/Misako_" + to_string(i) + ".png";
		fileW = L"";
		fileW.assign(file.begin(), file.end());
		IMAGE_MANAGER->addImage("misako_" + to_string(i), fileW);

		// 미스즈
		file = "resources/images/UI/dialogue/Misuzu_" + to_string(i) + ".png";
		fileW = L"";
		fileW.assign(file.begin(), file.end());
		IMAGE_MANAGER->addImage("misuzu_" + to_string(i), fileW);
	}	

	// * 이펙트
	// 이미지 매니저에 이펙트 이미지 미리 추가해놓고
	IMAGE_MANAGER->addFrameImage("effect_1", L"resources/images/effect/effect_1.png",  5, 1);	
	IMAGE_MANAGER->addFrameImage("effect_2", L"resources/images/effect/effect_2.png", 15, 1);
	IMAGE_MANAGER->addFrameImage("effect_3", L"resources/images/effect/effect_3.png",  4, 4);
	IMAGE_MANAGER->addFrameImage("effect_4", L"resources/images/effect/effect_4.png",  5, 3);
	IMAGE_MANAGER->addFrameImage("effect_5", L"resources/images/effect/effect_5.png", 7, 2);
	IMAGE_MANAGER->addFrameImage("effect_explosion", L"resources/images/effect/explosion.png",  4, 4);
	IMAGE_MANAGER->addFrameImage("effect_guard", L"resources/images/effect/effect_guard.png",  5, 8);
	IMAGE_MANAGER->addFrameImage("effect_spark", L"resources/images/effect/effect_spark.png", 4, 1);
	IMAGE_MANAGER->addFrameImage("effect_faseChange", L"resources/images/effect/faseChange.png", 3, 1);
	IMAGE_MANAGER->addFrameImage("effect_standUpEffect", L"resources/images/effect/standUpEffect.png", 8, 1);
	IMAGE_MANAGER->addFrameImage("effect_dashAttackEffect", L"resources/images/effect/dashAttackEffect.png", 7, 1);
	IMAGE_MANAGER->addFrameImage("effect_strongPunch", L"resources/images/effect/boss_strong_attack_effect.png", 24, 2);


	IMAGE_MANAGER->addFrameImage("effect_eat", L"resources/images/effect/particle-effects-png.png", 8, 6);

	IMAGE_MANAGER->addFrameImage("effect_stun", L"resources/images/effect/effect_stun.png", 4, 1);

	// 이펙트 매니저에 등록
	for (int i = 1; i < 5; i++)
	{
		string name = "effect_" + to_string(i);
		Image* img = IMAGE_MANAGER->findImage(name);
		EFFECT_MANAGER->addEffect(name, name.c_str(), 40, 10);
	}		

	EFFECT_MANAGER->addEffect("effect_electric", "boss_electric", 30, 10);
	EFFECT_MANAGER->addEffect("effect_explosion", "effect_explosion", 20, 10);
	EFFECT_MANAGER->addEffect("effect_guard", "effect_guard", 50, 20);
	EFFECT_MANAGER->addEffect("effect_spark", "effect_spark", 20, 10);
	//EFFECT_MANAGER->addEffect("effect_faseChange", "boss_faseChange", 30, 10);
	//EFFECT_MANAGER->addEffect("effect_standUpEffect", "boss_standUpEffect", 30, 10);
	//EFFECT_MANAGER->addEffect("effect_dashAttackEffect", "boss_dashAttackEffect", 30, 10);
	EFFECT_MANAGER->addEffect("effect_faseChange", "effect_faseChange", 30, 10);
	EFFECT_MANAGER->addEffect("effect_standUpEffect", "effect_standUpEffect", 30, 10);
	EFFECT_MANAGER->addEffect("effect_dashAttackEffect", "effect_dashAttackEffect", 30, 10);
	EFFECT_MANAGER->addEffect("effect_eat", "effect_eat", 50, 20);
	EFFECT_MANAGER->addEffect("effect_stun", "effect_stun", 5, 10);
	EFFECT_MANAGER->addEffect("effect_strongPunch", "effect_strongPunch", 50, 10);

	D2D_RENDERER->addTextFormat(L"메이플스토리");		// 폰트 갖고옴	
	
	// 모든 씬 SCENE_MANAGER에 등록
	SCENE_MANAGER->addScene("MAIN", new MainScene);
	SCENE_MANAGER->addScene("STAGE", new StageScene);
	SCENE_MANAGER->changeScene("STAGE");	


	return S_OK;
}

//메모리 해제
void playGround::release()
{
	GameNode::release();
}

//연산
void playGround::update()
{

	GameNode::update();

	SCENE_MANAGER->update();
	DEBUG_MANAGER->update();
	
}

//그리기 전용
void playGround::render()
{	
	D2D_RENDERER->beginRender(D2D1::ColorF::Black);
	{
		// _kyoko->render();
		SCENE_MANAGER->render();		
	}
	//백버퍼에 그린 내용들을 화면에 뿌려라~
	D2D_RENDERER->endRender();
}
