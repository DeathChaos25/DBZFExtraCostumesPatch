#pragma once

class config
{
public:
	static bool enableConsole;
	static bool enableCostumes;
	static bool unlockColors;
	static bool PrintBlueprintErrors;

	static bool init();
};

FORCEINLINE const char* const BoolToString(bool b);