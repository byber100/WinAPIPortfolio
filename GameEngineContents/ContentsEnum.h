#pragma once

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	UI,
	TRAP,
	OBJECT
};

enum class CreateTrap
{
	None,
	Ready,
	Arrangement,
	Complete
};

enum class TrapSpawn
{
	None,
	L_Crack,
	R_Crack,
	L_Hole,
	C_Hole,
	R_Hole,
	LR_Hole,
	L_Seal,
	C_Seal,
	R_Seal,
	L_Random,
	C_Random,
	R_Random,
};