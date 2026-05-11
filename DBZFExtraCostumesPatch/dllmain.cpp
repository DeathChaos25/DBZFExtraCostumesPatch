// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include "config.h"

bool DEBUG = 0;

// v1.31 = 0x1403aea00
void* GetCostumeCSS_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x6C\x24\x2A\x48\x89\x74\x24\x2A\x57\x48\x83\xEC\x20\x8B\xF2\x48\x8B\xF9",
    "xxxx?xxxx?xxxx?xxxxxxxxxx");

// v1.31 = 0x140684310
void* SetCostumeCustomizeMenu_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x6C\x24\x2A\x48\x89\x74\x24\x2A\x48\x89\x7C\x24\x2A\x41\x56\x48\x83\xEC\x20\x45\x33\xF6\x48\x8B\xE9",
    "xxxx?xxxx?xxxx?xxxx?xxxxxxxxxxxx");

// v1.31 = 0x140683490
void* SetCostumeCustomizeMenu2_Sig = sigScan(
    "\x40\x55\x56\x57\x48\x83\xEC\x60",
    "xxxxxxxx");

// v1.31 = 0x1406ae83d
// v1.50 = 0x1406d37d1
void* GetPlayer1InputState_Sig = sigScan(
    "\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A",
    "xxx????x????xxx????xxxxxx?xxx????x????xxx????xxxxxx?xxx????x????xxx????xxxxxx?xxx????x????xxx????xxxxxx?xxx????");

// v1.31 = 0x1406ae5bb
void* GetPlayer2InputState_Sig = sigScan(
    "\x4C\x8D\x2D\x2A\x2A\x2A\x2A\x49\x63\x06\x83\xF8\x07",
    "xxx????xxxxxx");

// v1.31 = 0x140439053
void* GetPlayerInputStateKeyboard_Sig = sigScan(
    "\x48\x8D\x0D\x2A\x2A\x2A\x2A\x66\x0F\x1F\x44\x2A\x00\x48\x8D\x80\x2A\x2A\x2A\x2A",
    "xxx????xxxx?xxxx????");

// v1.31 = 0x140682707
void* NOPCheck1_Sig = sigScan(
    "\x88\x04\x2A\x48\xFF\xC3\xFF\xC7\x49\x8D\x04\x2A",
    "xx?xxxxxxxx?");

// v1.31 = 0x140684386
void* NOPCheck2_Sig = sigScan(
    "\x40\x88\xB1\x2A\x2A\x2A\x2A\x48\x8B\x5C\x24\x2A",
    "xxx????xxxx?");

// v1.31 = 0x140684359
void* NOPCheck3_Sig = sigScan(
    "\x41\x0F\x44\xFE\x40\x88\xBC\x2A\x2A\x2A\x2A\x2A",
    "xxxxxxx?????");

// v1.31 = 0x1404ead00
void* hasExtraCostume_isVidel_Sig = sigScan(
    "\x85\xD2\x74\x2A\x83\xFA\x01\x75\x2A\x83\xF9\x23",
    "xxx?xxxx?xxx");

// v1.31 = 0x1406835d1
void* MOVVidelCostume2_Sig = sigScan(
    "\x41\xBC\x01\x00\x00\x00\x41\x8B\xD4\x33\xDB",
    "xxxxxxxxxxx");

// v1.31 = 0x1404e61c0
void* CycleColorsCSS_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x7C\x24\x2A\x4C\x8B\x15\x2A\x2A\x2A\x2A",
    "xxxx?xxxx?xxx????");

// v1.31 = 0x140507470
void* mini_ColorSelectSubtract_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x55\x57\x41\x57\x48\x83\xEC\x20\x45\x8B\xF8",
    "xxxx?xxxxxxxxxxx");

// v1.31 = 0x140507340
void* mini_ColorSelectAdd_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x6C\x24\x2A\x48\x89\x7C\x24\x2A\x41\x56\x48\x83\xEC\x20\x45\x8B\xF0",
    "xxxx?xxxx?xxxx?xxxxxxxxx");

// v1.31 = 0x1405074bc
void* mini_ColorSelectSubtractNOP_Sig = sigScan(
    "\x84\xC0\x75\x2A\x8B\xFD\x48\x89\x74\x24\x2A\x8B\xF5\x4C\x89\x74\x24\x2A",
    "xxx?xxxxxx?xxxxxx?");

// v1.31 = 0x14050739e
void* mini_ColorSelectAddNOP_Sig = sigScan(
    "\x84\xC0\x75\x2A\x8B\xFD\x48\x89\x74\x24\x2A\x8B\xF5\x39\x6B\x2A",
    "xxx?xxxxxx?xxxx?");

// v1.31 = 0x14050739e
void* KismetExecuteMessage_Sig = sigScan(
    "\x80\xFA\x01\x75\x2A\x53",
    "xxxx?x");

// v1.50 = 0x1406b6b01
void* ForceColor1_Sig = sigScan(
    "\xC6\x81\x2A\x2A\x2A\x2A\x01\x48\x83\xC4\x20\x41\x5E",
    "xx????xxxxxxx");

bool isChangeCostume = false;

UE4PlayerInput* PlayerInput1;
UE4PlayerInput* PlayerInput2;

uint64_t CurrentBaseAddress = GetCurrentBaseAddress();
uint64_t baseAddressGhidra = 0x140000000;

#include <windows.h>

int GetCostumeFromPlayerInput(void)
{
    const int keyMap[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    for (int i = 0; i < 9; i++)
    {
        if (GetAsyncKeyState(keyMap[i]) & 0x8000)
        {
            // Keyboard input
            return i;
        }
    }
    
    int result = 0;

    // controller input
    if (PlayerInput1->L1 || PlayerInput2->L1)
    {
        result = 1; // Costume 2
    }
    else if (PlayerInput1->R1 || PlayerInput2->R1)
    {
        result = 2; // Costume 3
    }
    else if (PlayerInput1->L2 || PlayerInput2->L2)
    {
        result = 3; // Costume 4
    }
    else if (PlayerInput1->R2 || PlayerInput2->R2)
    {
        result = 4; // Costume 5
    }

    return result;
}

HOOK(int, __fastcall, hook_GetCostumeCSS, GetCostumeCSS_Sig,
    u64 a1, int a2, int a3)
{
    int costume = orig_hook_GetCostumeCSS(a1, a2, a3);

    costume = GetCostumeFromPlayerInput();

    printf("CSS: Picking Costume % d\n", costume + 1);

    return costume;
}

HOOK(void, __fastcall, hook_SetCostumeCustomizeMenu, SetCostumeCustomizeMenu_Sig,
    css_info_struct* a1, int costume, int a3)
{
    if (isChangeCostume)
    {
        costume = GetCostumeFromPlayerInput();

        a1->ptr1->ptr2[a3]->costume_id = costume;
        // a1->ptr_final[a3].costume_ID = costume;
        // printf("SetCostumeCustomizeMenu: Selecting Costume %02d on Slot %d\n\n", costume + 1, a3);

        isChangeCostume = false;
    }

    return orig_hook_SetCostumeCustomizeMenu(a1, costume, a3);
}

HOOK(void, __fastcall, hook_SetCostumeCustomizeMenu2, SetCostumeCustomizeMenu2_Sig,
    css_info_struct* a1, u8 a2, u8 a3, u8 a4, u8 a5, u8 a6)
{
    if ( a3 == 0 && a5 == 0 )
    {
        isChangeCostume = true;
        // a1->ptr1->ptr2[a3]->field9_0x284 = 1;

        u8 costume = GetCostumeFromPlayerInput();

        printf("Picking Costume %d\n", costume + 1);
    }
    
    orig_hook_SetCostumeCustomizeMenu2(a1, a2, a3, a4, a5, a6);

    return;
}

HOOK(bool, __fastcall, hook_isVidelHasCostume, hasExtraCostume_isVidel_Sig,
    int character_id, int color_id)
{
    bool result = false;

    if (color_id == 0) 
    {
        result = true;
    }
    else if (color_id == 1 && character_id == 35)
    {
        result = true;
    }
    else result = false;

    int costumeID = GetCostumeFromPlayerInput();

    if (costumeID > 0) result = true;

    return result;
}

HOOK(int, __fastcall, hook_CycleColorsCSS, CycleColorsCSS_Sig,
    int a1, int a2, int a3) // is what color you're cycling from
{
    int result = orig_hook_CycleColorsCSS(a1, a2, a3);

    if (a2 == 0 && a3 == 1)
    {
        result = 58;
    }
    else if (a2 == 58 && a3 == 0)
    {
        result = 0;
    }
    else if (a3 == 1)
    {
        result = a2 - 1;
    }
    else if (a3 == 0)
    {
        result = a2 + 1;
    }

    return result; // result is what color you cycle to
}

HOOK(u64, __fastcall, hook_ColorUp, mini_ColorSelectAdd_Sig,
    color_select_mini_struct* a1, int a2, int a3)
{
    // printf("hook_ColorUp called; a1->field08 = %d\n", a1->field08);

    if (a1->field08 == 60 || a1->field08 == 59) // only affect color select
    {
        WRITE_MEMORY((u64)mini_ColorSelectAddNOP_Sig - 2, u8, 0xb0);
        WRITE_MEMORY((u64)mini_ColorSelectAddNOP_Sig - 1, u8, 0x00); // MOV AL, 0
        a1->field08 = 59; // set color limit to 59 from 60
    }
    else // write original instruction
    {
        WRITE_MEMORY((u64)mini_ColorSelectAddNOP_Sig - 2, u8, 0xff);
        WRITE_MEMORY((u64)mini_ColorSelectAddNOP_Sig - 1, u8, 0x10);
    }

    u64 result = orig_hook_ColorUp(a1, a2, a3);

    //if (a1->field08 == 59) a1->color_id = a1->color_id_next;

    return result;
}

HOOK(u64, __fastcall, hook_ColorDown, mini_ColorSelectSubtract_Sig,
    color_select_mini_struct* a1, int a2, int a3)
{
    // printf("hook_ColorDown called; a1->field08 = %d\n", a1->field08);
    
    if (a1->field08 == 60 || a1->field08 == 59) // only affect color select
    {
        WRITE_MEMORY((u64)mini_ColorSelectSubtractNOP_Sig - 2, u8, 0xb0);
        WRITE_MEMORY((u64)mini_ColorSelectSubtractNOP_Sig - 1, u8, 0x00); // MOV AL, 0
        a1->field08 = 59; // set color limit to 59 from 60
    }
    else // write original instruction
    {
        WRITE_MEMORY((u64)mini_ColorSelectSubtractNOP_Sig - 2, u8, 0xff);
        WRITE_MEMORY((u64)mini_ColorSelectSubtractNOP_Sig - 1, u8, 0x10);
    }

    u64 result = orig_hook_ColorDown(a1, a2, a3);

    // if (a1->field08 == 59) a1->color_id = a1->color_id_next;

    return result;
}

HOOK(void, __stdcall, hook_KismetExecuteMessage, KismetExecuteMessage_Sig, u64* Message, u8 Verbosity)
{
    printf("[Script Msg] %S\r\n", Message);
    return orig_hook_KismetExecuteMessage(Message, Verbosity);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        config::init();

        if ( config::enableConsole ) // open console output
        {
            AllocConsole();
            AttachConsole(GetCurrentProcessId());
            freopen("CON", "w", stdout);
        }

        if (config::enableCostumes)
        {
            if (GetPlayer1InputState_Sig)
            {
                u64 inputBase = GetAddressFromGlobalRef((u64)GetPlayer1InputState_Sig);
                
                PlayerInput1 = (UE4PlayerInput*)inputBase;
                PlayerInput2 = (UE4PlayerInput*)(inputBase + 0x20);
                printf("Player 1 Input Address at 0x%p\n", (u64)PlayerInput1);
                printf("Player 2 Input Address at 0x%p\n", (u64)PlayerInput2);
                if (DEBUG) printf("All input state signatures successful\n");
            }
            else
            {
                if (!GetPlayer1InputState_Sig) printf("Signature GetPlayer1InputState broken!\n");
            }

            if (GetCostumeCSS_Sig) // called when a character is selected in the css
            {
                INSTALL_HOOK(hook_GetCostumeCSS);
                if (DEBUG) printf("Signature for GetCostumeCSS found at 0x%llx\n", GetCostumeCSS_Sig);
            }
            else
            {
                if (DEBUG) printf("Signature for GetCostumeCSS broken!\n");
            }

            if (SetCostumeCustomizeMenu_Sig) // called when selecting from customize menu
            {
                INSTALL_HOOK(hook_SetCostumeCustomizeMenu);
                if (DEBUG) printf("Signature for SetCostumeCustomizeMenu found at 0x%llx\n", SetCostumeCustomizeMenu_Sig);
            }
            else
            {
                if (DEBUG) printf("Signature SetCostumeCustomizeMenu broken!\n");
            }

            if (NOPCheck1_Sig)
            {
                WRITE_NOP(NOPCheck1_Sig, 3);
                if (DEBUG) printf("Signature NOPCheck1_Sig found at 0x%llx\n", NOPCheck1_Sig);
            }
            else
            {
                if (DEBUG) printf("Signature NOPCheck1_Sig broken!\n");
            }

            if (NOPCheck3_Sig)
            {
                WRITE_NOP(NOPCheck3_Sig, 4);

                if (DEBUG) printf("Signature NOPCheck3 found at 0x%llx\n", NOPCheck3_Sig);
            }
            else
            {
                if (!NOPCheck3_Sig) printf("Signature NOPCheck3 broken!\n");
            }

            if (ForceColor1_Sig)
            {
                WRITE_NOP(ForceColor1_Sig, 7);

                if (DEBUG) printf("Signature ForceColor1_Sig found at 0x%llx\n", ForceColor1_Sig);
            }
            else
            {
                if (!ForceColor1_Sig) printf("Signature ForceColor1_Sig broken!\n");
            }

            if (SetCostumeCustomizeMenu2_Sig) // called when selecting from customize menu
            {
                INSTALL_HOOK(hook_SetCostumeCustomizeMenu2);
                if (DEBUG) printf("Signature for SetCostumeCustomizeMenu2 found at 0x%llx\n", SetCostumeCustomizeMenu2_Sig);
            }
            else
            {
                if (!SetCostumeCustomizeMenu2_Sig) printf("Signature SetCostumeCustomizeMenu2 broken!\n");
            }

            if (hasExtraCostume_isVidel_Sig) // self explanatory name
            {
                INSTALL_HOOK(hook_isVidelHasCostume);
                if (DEBUG) printf("Signature for hook_isVidelHasCostume found at 0x%llx\n", hasExtraCostume_isVidel_Sig);
            }
            else
            {
                if (!hasExtraCostume_isVidel_Sig) printf("Signature hasExtraCostume_isVidel broken!\n");
            }
        }
        
        if (config::unlockColors)
        {
            if (CycleColorsCSS_Sig) // cycling colors in css
            {
                INSTALL_HOOK(hook_CycleColorsCSS);
                if (DEBUG) printf("Signature for CycleColorsCSS found at 0x%llx\n", CycleColorsCSS_Sig);
            }
            else
            {
                if (!CycleColorsCSS_Sig) printf("Signature CycleColorsCSS broken!\n");
            }

            if (mini_ColorSelectSubtractNOP_Sig) // cycling colors in customize menu
            {
                INSTALL_HOOK(hook_ColorDown);
                if (DEBUG) printf("Signature for mini_ColorSelectSubtractNOP found at 0x%llx\n", mini_ColorSelectSubtractNOP_Sig);
            }
            else
            {
                if (!mini_ColorSelectSubtractNOP_Sig) printf("Signature mini_ColorSelectSubtract broken!\n");
            }

            if (mini_ColorSelectAddNOP_Sig) // cycling colors in customize menu
            {
                INSTALL_HOOK(hook_ColorUp);
                if (DEBUG) printf("Signature for mini_ColorSelectAddNOP found at 0x%llx\n", mini_ColorSelectAddNOP_Sig);
            }
            else
            {
                if (!mini_ColorSelectAddNOP_Sig) printf("Signature mini_ColorSelectAddNOP broken!\n");
            }
        }

        if (KismetExecuteMessage_Sig && config::PrintBlueprintErrors)
        {
            if (DEBUG) printf("Signature for KismetExecuteMessage fount at 0x%p, real address at 0x%p\n", ((u64)KismetExecuteMessage_Sig - CurrentBaseAddress) + baseAddressGhidra, ((u64)KismetExecuteMessage_Sig - CurrentBaseAddress) + baseAddressGhidra);
            INSTALL_HOOK(hook_KismetExecuteMessage);
        }
        else
        {
            if (DEBUG) printf("Signature for KismetExecuteMessage_Sig broken!\n");
        }

        config::init(); // repeat for messages

        return TRUE;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}