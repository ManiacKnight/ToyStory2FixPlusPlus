#include "INIReader.h"

int __declspec(dllexport) DummyFunction() { return 0; }

int getConfigValue(const char* KEY, const char* SECTION)
{
	INIReader ini("Config.ini");
	int Switch = ini.GetInteger(SECTION, KEY, 0);
	return Switch;
}
