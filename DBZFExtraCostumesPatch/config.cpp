#include "pch.h"
#include "config.h"

bool config::enableConsole;
bool config::enableCostumes;
bool config::costumeSelectMenu;
bool config::unlockColors;
bool config::PrintBlueprintErrors;

bool config::init()
{
    toml::table config;
    std::string fileString = "";

    try
    {
        std::ifstream file("config.toml");
        std::string str;
        while (std::getline(file, str))
            fileString += str + "\n";

        config = toml::parse(fileString);
    }
    catch (std::exception& exception)
    {
        char text[1024];
        sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
        MessageBoxA(nullptr, text, "File Access Log", MB_OK | MB_ICONERROR);
    }

    enableConsole = config["Enable_Console"].value_or(false);
    enableCostumes = config["Extra_Costumes_Patch"].value_or(true);
    costumeSelectMenu = config["Costume_Select_Menu"].value_or(true);
    unlockColors = config["Unlock_All_Colors"].value_or(true);
    PrintBlueprintErrors = config["Log_Script_Errors"].value_or(true);

    printf("Loading GG Strive Extra Costumes Patch\n");

    printf("Extra Costumes Patch is %s\n", BoolToString(enableCostumes));
    printf("Costume Select Menu is %s\n", BoolToString(costumeSelectMenu));
    printf("All Colors Unlock Patch is %s\n", BoolToString(unlockColors));
    printf("Blueprint Error Logging is %s\n", BoolToString(PrintBlueprintErrors));

    return true;
}

inline const char* const BoolToString(bool b)
{
    return b ? "enabled" : "disabled";
}