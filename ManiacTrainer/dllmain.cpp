#include <Windows.h>
#include <iostream>
#include "../ManiacTrainer/External/INIReader/INIReader.h"
#include <string>

DWORD WINAPI ManiacTrainer(HMODULE hModule)
{

    //INI Parse and Error Checking
    INIReader ini("Config.ini");

    if (ini.ParseError() < 0) 
    {
        MessageBoxA(NULL, "Unable To Open Config.ini", 0, 0);
        exit(-1);
    }

    if (ini.GetInteger("GENERAL", "EnableTrainer", 0) != 1)
        FreeLibraryAndExitThread(hModule, 0);


    /*Debug Stuff
    AllocConsole();
    FILE * file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    std::cout << "The Console has been loaded, hooking into game process! \n";*/


    //Loop to find process window
    HWND hwnd;
    while (true)
    {
        hwnd = FindWindowA(NULL, "Toy2");

        if (hwnd != NULL)
            break;

        Sleep(5);
    }

    //Getting the handle and all
    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    //std::cout << "ProcID : " << handle << std::endl;

    //Storage for key values
    const int SetKey = ini.GetInteger("GENERAL", "SetValueKB", 0x78);
    const int JumpKey = ini.GetInteger("PLAYER", "JumpKey", 0x45);
    const short HP = 14;
    wchar_t Dir[FILENAME_MAX];
    GetCurrentDirectoryW(FILENAME_MAX, Dir);
    /*HANDLE hWait = FindFirstChangeNotificationW((LPCWSTR)Dir, FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
    std::cout << Dir << std::endl;
    std::cout << hWait << std::endl;*/

    while (true)
    {

        if (GetAsyncKeyState(SetKey) & 1)
        {
            INIReader ini("Config.ini");
            short Coins = ini.GetInteger("PLAYER", "Coins", 99);
            short Lives = ini.GetInteger("PLAYER", "Lives", 9);
            short Toys = ini.GetInteger("PLAYER", "ToysCollected", 5);

            WriteProcessMemory(handle, (LPVOID)0x0052F39E, &Coins, sizeof(short), nullptr); //Coins (max 99)
            WriteProcessMemory(handle, (LPVOID)0x0052F39A, &Lives, sizeof(short), nullptr); //Lives (max 9)
            WriteProcessMemory(handle, (LPVOID)0x0052B7D8, &Toys, sizeof(short), nullptr);  //Toys (max 5)

            //std::cout << "coinsFunc_Success : " << Coin << std::endl << "livesFunc_Success : " << Live << std::endl;

            if (ini.GetInteger("TOKENS", "Enable", 0) == 1)
            {
                int j = 1, Address = 0x0052F0D8;
                for (int i = 0; i < 16; i++)
                {
                    byte Tokens = ini.GetInteger("TOKENS", (std::string)"Level"+=std::to_string(j), 0);

                    //The game uses a particular number series to determine the amount of tokens earned by the player
                    switch (Tokens)
                    {
                    default:
                        Tokens = 0;
                        break;

                    case 1:
                        Tokens = 1;
                        break;

                    case 2:
                        Tokens = 3;
                        break;

                    case 3:
                        Tokens = 7;
                        break;

                    case 4:
                        Tokens = 15;
                        break;

                    case 5:
                        Tokens = 31;
                        break;
                    }

                    WriteProcessMemory(handle, (LPVOID)Address, &Tokens, sizeof(byte), nullptr);
                    j++, Address++;
                }
            }           

        }

        if (GetAsyncKeyState(JumpKey) & 1)
        {
            INIReader ini("Config.ini");
            if (ini.GetInteger("PLAYER", "HighJump", 0) == 1)
            {
                const short val = 3;
                WriteProcessMemory(handle, (LPVOID)0x00830CC4, &val, sizeof(byte), nullptr);
            }
        }

        if (GetAsyncKeyState(0x23) & 1)
            break;

        Sleep(5);
    }

    /*fclose(file);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);*/
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ManiacTrainer, hModule, 0, nullptr);
        break;
    }
    return TRUE;
}

/*INI FILE CONFIGURATION
[GENERAL]
EnableTrainer = 0
;Use virtual Keybinds like the one set below (F9 KEY)
SetValueKB = 0x78

[PLAYER]
Invincible    = 1
Coins         = 99 ;Max value is 99
Lives         = 9  ;Max value is 9
ToysCollected = 5  ;(Sheep, Troopers , etc) Max value is 5
InfiniteJump  = 1  ;Spam spacebar/jump key
HighJump      = 1
JumpKey       = 0x45 ;E key

[TOKENS]
;Max Value is 5 throughout, Levels with 1 token are the boss stages
Enable = 0
Level1 = 5
Level2 = 5
Level3 = 1
Level4 = 5
Level5 = 5
Level6 = 1
Level7 = 5
Level8 = 5
Level9 = 1
Level10 = 5
Level11 = 5
Level12 = 1
Level13 = 5
Level14 = 5
Level15 = 1
*/
