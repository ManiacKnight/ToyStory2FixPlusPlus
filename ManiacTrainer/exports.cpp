#include "../ManiacTrainer/External/INIReader/INIReader.h"

//Dummy Export to add to the Game's IAT (Import Address Table)
int __declspec(dllexport) DummyFunction() { return 0; }

//Custom Function written to be called from inside the game's code.
//Some trainer functions have been patched directly into the game as assembly code, but still need access to the INI values to turn them on or off.
int getConfigValue(const char* KEY, const char* SECTION)
{
	INIReader ini("Config.ini");
	int Switch = ini.GetInteger(SECTION, KEY, 0);
	return Switch;
}
