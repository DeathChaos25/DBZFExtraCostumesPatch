#include "pch.h"
#include <stdio.h>
#include <intrin.h>
#include "config.h"

bool DEBUG = 0;

// hardcoded max by savedata code
const int MAX_COSTUMES = 9;
const int MAX_COLORS = 59;

// bool HasCostume(int character_id, int costume_id)
// v1.31 = 0x1404ead00
// v1.50 = 0x140509420
void* HasCostume_Sig = sigScan(
    "\x85\xD2\x74\x2A\x83\xFA\x01\x75\x2A\x83\xF9\x23\x0F\x94\xC0\xC3\x32\xC0\xC3\xB0\x01\xC3",
    "xxx?xxxx?xxxxxxxxxxxxx");

// call to HasCostume(character_id, 1) in the random character pick, which then picks costume 0 or 1
// v1.31 = 0x14053a22b
// v1.50 = 0x14055331b
void* RandomPickHasCostumeCall_Sig = sigScan(
    "\xE8\x2A\x2A\x2A\x2A\x84\xC0\x74\x2A\x48\x8B\x05\x2A\x2A\x2A\x2A\x48\x8B\x88\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x44\x8B\xC0\xB8\xAD\x8B\xDB\x68",
    "x????xxx?xxx????xxx????x????xxxxxxxx");

// costume picked when confirming a character in the css
// v1.31 = 0x1403aea00
// v1.50 = 0x1403debe0
void* GetCostumeCSS_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x6C\x24\x2A\x48\x89\x74\x24\x2A\x57\x48\x83\xEC\x20\x8B\xF2\x48\x8B\xF9",
    "xxxx?xxxx?xxxx?xxxxxxxxxx");

// "is the costume button held" part of the customize menu, result is passed to SetCostumeCustomizeMenu2
// v1.31 = 0x14068e160
// v1.50 = 0x1406be680
void* GetCostumeButtonStateCustomizeMenu_Sig = sigScan(
    "\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\xE8\x2A\x2A\x2A\x2A\x84\xC0\x74\x2A\xE8\x2A\x2A\x2A\x2A\x84\xC0\x75\x2A\x48\x8B\xCB\xE8\x2A\x2A\x2A\x2A\x48\x85\xC0\x74\x2A\x4C\x8B\x00\xBA\x00\x00\x04\x00",
    "xxxxxxxxxx????xxx?x????xxx?xxxx????xxxx?xxxxxxxx");

// SetCostumeCustomizeMenu2, where the button is turned into costume 0 or 1
// v1.31 = 0x1406835e7
// v1.50 = 0x1406b5e3b
void* CustomizeMenuButtonToCostume_Sig = sigScan(
    "\xE8\x2A\x2A\x2A\x2A\x84\xC0\x74\x07\x40\x84\xED\x41\x0F\x45\xDC\x44\x8B\xC7\x8B\xD3",
    "x????xxxxxxxxxxxxxxxx");

// player 1's input state
// v1.31 = 0x1406adfe1
// v1.50 = 0x1406d3701
void* GetPlayer1InputState_Sig = sigScan(
    "\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A\xE9\x2A\x2A\x2A\x2A\x48\x3B\x0D\x2A\x2A\x2A\x2A\x0F\x94\xC0\x84\xC0\x74\x2A\x48\x8D\x05\x2A\x2A\x2A\x2A",
    "xxx????x????xxx????xxxxxx?xxx????x????xxx????xxxxxx?xxx????x????xxx????xxxxxx?xxx????x????xxx????xxxxxx?xxx????");

// bool IsColorAvailable(int character_id, int color_id), checks the unlocked colors in the save data
// v1.31 = 0x1404eaca0
// v1.50 = 0x1405093c0
void* IsColorAvailable_Sig = sigScan(
    "\x44\x8B\xC2\x83\xF9\x1B\x77\x2A\xB8\x03\x00\x18\x0C\x0F\xA3\xC8\x73\x2A\x41\x83\xF8\x3A\x74\x2A",
    "xxxxxxx?xxxxxxxxx?xxxxx?");

// v1.31 = 0x1404e61c0
// v1.50 = 0x140502330
void* CycleColorsCSS_Sig = sigScan(
    "\x48\x89\x5C\x24\x2A\x48\x89\x7C\x24\x2A\x4C\x8B\x15\x2A\x2A\x2A\x2A",
    "xxxx?xxxx?xxx????");

// FFrame::KismetExecutionMessage
// v1.50 = 0x140b94fc0
void* KismetExecuteMessage_v150_Sig = sigScan(
    "\x40\x53\x48\x83\xEC\x50\x33\xC0\x48\x8B\xD9\x48\x89\x44\x24\x30\x89\x44\x24\x38\x48\x89\x44\x24\x40\x80\xFA\x01\x75",
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

// v1.31 = 0x140b66f90
void* KismetExecuteMessage_Sig = KismetExecuteMessage_v150_Sig ? KismetExecuteMessage_v150_Sig : sigScan(
    "\x80\xFA\x01\x75\x2A\x53\x48\x83\xEC\x30\x48\x8B\xD9",
    "xxxx?xxxxxxxx");

// color select step of the css (AREDGameState_CharaSelect_S3)
// v1.50 = 0x1403ea980
void* ColorSelectStepCSS_Sig = sigScan(
    "\x40\x56\x57\x48\x83\xEC\x48\x48\x8B\xF9\x48\x63\xF2\xB9\x5B\x00\x00\x00\xE8\x2A\x2A\x2A\x2A\xF6\x80\xCD\x02\x00\x00\x02\x0F\x85\x2A\x2A\x2A\x2A\x48\x89\x6C\x24\x68\x48\x8B\xCF\x4C\x89\x6C\x24\x40",
    "xxxxxxxxxxxxxxxxxxx????xxxxxxxxx????xxxxxxxxxxxxx");

// FText LocalizeText(const wchar_t* key, bool)
// v1.50 = 0x1405036b0
void* LocalizeText_Sig = sigScan(
    "\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x4C\x89\x64\x24\x20\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\xB9\x48\x81\xEC\xB0\x00\x00\x00\x45\x84\xC0\x48\x8D\x05",
    "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

// offsets into AREDGameState_CharaSelect_S3 and its widget, v1.50
const int CSS_WIDGET = 0xBA0;
const int CSS_WIDGET_COLOR_SELECT = 0x270; // per side in the widget, starts with the index of the team member being edited
const int CSS_WIDGET_COLOR_SELECT_SIZE = 0x80;
const int CSS_STEP_REQUEST = 0xBD9; // per side, the step a side moves to on the next frame
const int CSS_SLOTS = 0xBEC; // per side, 3 team members of { ?, character, costume, color, ... }
const int CSS_SIDE_SIZE = 0x6C;
const int CSS_SLOT_SIZE = 0x14;

const u8 CSS_STEP_ASSIST = 3;
const u8 CSS_STEP_COLOR = 4;
const u8 CSS_STEP_READY = 7;

// genuine bullshit happening here dont worry about it
bool IsColorSelectStepKnown()
{
    // MOV R14, [RDI + 0xBA0]; MOV RCX, RSI; SHL RCX, 7; ADD R14, 0x270; ADD R14, RCX; MOV EBP, EAX; IMUL R13, RSI, 0x6C
    const u8 widgetAndSide[] = { 0x4c, 0x8b, 0xb7, 0xa0, 0x0b, 0x00, 0x00, 0x48, 0x8b, 0xce, 0x48, 0xc1, 0xe1, 0x07, 0x49, 0x81, 0xc6, 0x70, 0x02, 0x00, 0x00, 0x4c, 0x03, 0xf1, 0x8b, 0xe8, 0x4c, 0x6b, 0xee, 0x6c };
    // MOV byte ptr [RDI + R13 + 0xBD9], 3 and 7
    const u8 cancelToAssist[] = { 0x42, 0xc6, 0x84, 0x2f, 0xd9, 0x0b, 0x00, 0x00, 0x03 };
    const u8 confirmToReady[] = { 0x42, 0xc6, 0x84, 0x2f, 0xd9, 0x0b, 0x00, 0x00, 0x07 };

    // LEA RBP, [RDI + 0xBEC]; LEA RCX, [RAX + RAX*4] (slot size 0x14 = 5 * 4); MOVZX EBX, [RBP + 3]; MOVZX EAX, [RBP + 2]
    const u8 slots[] = { 0x48, 0x8d, 0xaf, 0xec, 0x0b, 0x00, 0x00 };
    const u8 slotSize[] = { 0x48, 0x8d, 0x0c, 0x80 };
    const u8 slotColor[] = { 0x0f, 0xb6, 0x5d, 0x03 };
    const u8 slotCostume[] = { 0x0f, 0xb6, 0x45, 0x02 };

    u8* step = (u8*)ColorSelectStepCSS_Sig;

    return step
        && memcmp(step + 0x75, widgetAndSide, sizeof(widgetAndSide)) == 0
        && memcmp(step + 0x116, cancelToAssist, sizeof(cancelToAssist)) == 0
        && memcmp(step + 0x13E, confirmToReady, sizeof(confirmToReady)) == 0
        && memcmp(step + 0x26E, slots, sizeof(slots)) == 0
        && memcmp(step + 0x27D, slotSize, sizeof(slotSize)) == 0
        && memcmp(step + 0x28F, slotColor, sizeof(slotColor)) == 0
        && memcmp(step + 0x2B0, slotCostume, sizeof(slotCostume)) == 0
        && step[0xD3] == 0xE8 && step[0xE1] == 0xE8 && step[0x2C7] == 0xE8 && step[0x2EF] == 0xE8;
}

void* GetColorSelectStepCallee(int callOffset)
{
    if (!IsColorSelectStepKnown()) return nullptr;

    return (void*)GetAddressFromFuncCall((u64)ColorSelectStepCSS_Sig + callOffset);
}

// functions called by the color select step
// v1.50 = 0x14082eff0, 0x14082f070, 0x1403e44c0, 0x1403dee90
void* AssistIconOpenAnim1PCSS_Addr = GetColorSelectStepCallee(0xD3);
void* AssistIconOpenAnim2PCSS_Addr = GetColorSelectStepCallee(0xE1);
void* RefreshPreviewPawnCSS_Addr = GetColorSelectStepCallee(0x2C7);
void* FillColorSelectParamCSS_Addr = GetColorSelectStepCallee(0x2EF);

UE4PlayerInput* PlayerInput1;
UE4PlayerInput* PlayerInput2;

bool (__fastcall* IsWidgetInputFocusOwner)(void* widget);
bool (__fastcall* IsCustomizeMenuInputBlocked)();

// LocalizeText, used to build the costume labels
UE4String* (__cdecl* FStringPrintf)(UE4String* out, const wchar_t* format, ...);
void* (__fastcall* FTextFromString)(void* outText, UE4String* string);
void (__fastcall* FStringDestroy)(UE4String* string);

// costume select state, we run it twice per side and the first run picks costumes
bool isCostumeSelectEnabled = false;
bool isCostumePass[2] = { true, true };
bool isCostumeAndColorSwapped[2];
int colorSelectStepSide = -1; // side the color select step is currently running for
u8* costumeLabelState; // set while the labels of a costume pass are being built
int costumeLabelSide = -1;
int costumeLabelMember;

uint64_t CurrentBaseAddress = GetCurrentBaseAddress();
uint64_t baseAddressGhidra = 0x140000000;

bool IsSignatureValid(void* signature, const char* name)
{
    if (!signature)
    {
        printf("Signature %s broken!\n", name);
        return false;
    }

    if (DEBUG) printf("Signature %s found at 0x%llx\n", name, ((u64)signature - CurrentBaseAddress) + baseAddressGhidra);

    return true;
}

int GetCostumeFromPlayerInput(void)
{
    const int keyMap[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    for (int i = 0; i < MAX_COSTUMES; i++)
    {
        if (GetAsyncKeyState(keyMap[i]) & 0x8000)
        {
            // Keyboard input
            return i;
        }
    }

    int result = 0;

    if (!PlayerInput1) return result;

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

// costume validation used by the css, customize menu, save data and match setup
HOOK(bool, __fastcall, hook_HasCostume, HasCostume_Sig,
    int character_id, int costume_id)
{
    // random pick would roll costume 2 for every character, leave it to the original check
    if (RandomPickHasCostumeCall_Sig && _ReturnAddress() == (u8*)RandomPickHasCostumeCall_Sig + 5)
    {
        return orig_hook_HasCostume(character_id, costume_id);
    }

    return (u32)costume_id < MAX_COSTUMES;
}

HOOK(int, __fastcall, hook_GetCostumeCSS, GetCostumeCSS_Sig,
    u64 a1, int side, int character_id)
{
    int costume = GetCostumeFromPlayerInput();

    printf("CSS: Picking Costume %d\n", costume + 1);

    return costume;
}

// originally returns 1 while the costume button is held, the patched SetCostumeCustomizeMenu2 uses it as costume index
HOOK(u8, __fastcall, hook_GetCostumeButtonStateCustomizeMenu, GetCostumeButtonStateCustomizeMenu_Sig,
    void* widget)
{
    if (!IsWidgetInputFocusOwner(widget) || IsCustomizeMenuInputBlocked())
    {
        return 0;
    }

    return (u8)GetCostumeFromPlayerInput();
}

HOOK(bool, __fastcall, hook_IsColorAvailable, IsColorAvailable_Sig,
    int character_id, int color_id)
{
    if ((u32)color_id < MAX_COLORS)
    {
        return true;
    }

    return orig_hook_IsColorAvailable(character_id, color_id);
}

// the original skips colors with an inlined copy of IsColorAvailable, so it is replaced entirely
HOOK(int, __fastcall, hook_CycleColorsCSS, CycleColorsCSS_Sig,
    int character_id, int color_id, char reverse) // color_id is what color you're cycling from
{
    int count = MAX_COLORS;

    if (colorSelectStepSide >= 0 && isCostumeAndColorSwapped[colorSelectStepSide])
    {
        count = MAX_COSTUMES; // costume pass, color_id is a costume
    }
    else if (!config::unlockColors)
    {
        return orig_hook_CycleColorsCSS(character_id, color_id, reverse);
    }

    if (reverse)
    {
        return color_id <= 0 ? count - 1 : color_id - 1;
    }

    return color_id >= count - 1 ? 0 : color_id + 1; // result is what color you cycle to
}

u8* GetSlotCSS(u8* state, int side, int member)
{
    return state + CSS_SLOTS + side * CSS_SIDE_SIZE + member * CSS_SLOT_SIZE;
}

// the color select step only knows how to edit the color, so during a costume pass it is given the costumes in its place
void SwapCostumeAndColorCSS(u8* state, int side)
{
    for (int member = 0; member < 3; member++)
    {
        u8* slot = GetSlotCSS(state, side, member);
        u8 costume = slot[2];

        slot[2] = slot[3];
        slot[3] = costume;
    }

    isCostumeAndColorSwapped[side] = !isCostumeAndColorSwapped[side];
}

// builds the three labels of the color select panel, one per team member
HOOK(void, __fastcall, hook_FillColorSelectParamCSS, FillColorSelectParamCSS_Addr,
    u8* state, int side)
{
    if (side < 0 || side > 1)
    {
        return orig_hook_FillColorSelectParamCSS(state, side);
    }

    // the only caller besides the step itself is the function entering the step, which always starts with costumes
    if (colorSelectStepSide != side)
    {
        isCostumePass[side] = true;
    }

    // the swatch next to each label is always the member's real color
    bool wasSwapped = isCostumeAndColorSwapped[side];

    if (wasSwapped) SwapCostumeAndColorCSS(state, side);

    if (isCostumePass[side])
    {
        costumeLabelState = state;
        costumeLabelSide = side;
        costumeLabelMember = 0;
    }

    orig_hook_FillColorSelectParamCSS(state, side);

    costumeLabelSide = -1;

    if (wasSwapped) SwapCostumeAndColorCSS(state, side);
}

HOOK(void*, __fastcall, hook_LocalizeText, LocalizeText_Sig,
    void* outText, const wchar_t* key, char a3)
{
    // the color select panel asks for COLOR_%d once per team member, in order
    if (costumeLabelSide >= 0 && costumeLabelMember < 3 && key && wcsncmp(key, L"COLOR_", 6) == 0)
    {
        int costume = GetSlotCSS(costumeLabelState, costumeLabelSide, costumeLabelMember++)[2];

        UE4String label;

        FStringPrintf(&label, L"COSTUME %d", costume + 1);
        FTextFromString(outText, &label);
        FStringDestroy(&label);

        return outText;
    }

    return orig_hook_LocalizeText(outText, key, a3);
}

HOOK(void, __fastcall, hook_RefreshPreviewPawnCSS, RefreshPreviewPawnCSS_Addr,
    u8* state, int side, int member, int character_id, int color_id, int costume_id)
{
    if (colorSelectStepSide >= 0 && isCostumeAndColorSwapped[colorSelectStepSide])
    {
        return orig_hook_RefreshPreviewPawnCSS(state, side, member, character_id, costume_id, color_id);
    }

    return orig_hook_RefreshPreviewPawnCSS(state, side, member, character_id, color_id, costume_id);
}

// the color select step only plays these when it is cancelled, which goes back to the costume pass instead of the assists
HOOK(int, __fastcall, hook_AssistIconOpenAnim1PCSS, AssistIconOpenAnim1PCSS_Addr,
    void* widget, bool open)
{
    if (colorSelectStepSide >= 0 && !isCostumePass[colorSelectStepSide])
    {
        return 0;
    }

    return orig_hook_AssistIconOpenAnim1PCSS(widget, open);
}

HOOK(int, __fastcall, hook_AssistIconOpenAnim2PCSS, AssistIconOpenAnim2PCSS_Addr,
    void* widget, bool open)
{
    if (colorSelectStepSide >= 0 && !isCostumePass[colorSelectStepSide])
    {
        return 0;
    }

    return orig_hook_AssistIconOpenAnim2PCSS(widget, open);
}

// select -> assist -> costume -> color, the costume select is the color select step run a first time on the costumes
HOOK(void, __fastcall, hook_ColorSelectStepCSS, ColorSelectStepCSS_Sig,
    u8* state, int side)
{
    if (side < 0 || side > 1)
    {
        return orig_hook_ColorSelectStepCSS(state, side);
    }

    u8* stepRequest = state + CSS_STEP_REQUEST + side * CSS_SIDE_SIZE;

    if (*stepRequest != CSS_STEP_COLOR)
    {
        return orig_hook_ColorSelectStepCSS(state, side);
    }

    bool costumePass = isCostumePass[side];

    colorSelectStepSide = side;

    if (costumePass) SwapCostumeAndColorCSS(state, side);

    orig_hook_ColorSelectStepCSS(state, side);

    if (isCostumeAndColorSwapped[side]) SwapCostumeAndColorCSS(state, side);

    bool costumesConfirmed = costumePass && *stepRequest == CSS_STEP_READY;
    bool colorsCancelled = !costumePass && *stepRequest == CSS_STEP_ASSIST;

    if (costumesConfirmed || colorsCancelled)
    {
        // stay in the step and switch pass, starting from the first team member like entering the step does
        *stepRequest = CSS_STEP_COLOR;
        isCostumePass[side] = colorsCancelled;
        *(s32*)(*(u8**)(state + CSS_WIDGET) + CSS_WIDGET_COLOR_SELECT + side * CSS_WIDGET_COLOR_SELECT_SIZE) = 0;
        implOfhook_FillColorSelectParamCSS(state, side);
    }

    colorSelectStepSide = -1;
}

HOOK(void, __stdcall, hook_KismetExecuteMessage, KismetExecuteMessage_Sig, const wchar_t* Message, u8 Verbosity)
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
            if (IsSignatureValid(GetPlayer1InputState_Sig, "GetPlayer1InputState"))
            {
                u64 inputBase = GetAddressFromGlobalRef((u64)GetPlayer1InputState_Sig);

                PlayerInput1 = (UE4PlayerInput*)inputBase;
                PlayerInput2 = (UE4PlayerInput*)(inputBase + 0x20);
                printf("Player 1 Input Address at 0x%p\n", PlayerInput1);
                printf("Player 2 Input Address at 0x%p\n", PlayerInput2);
            }

            if (IsSignatureValid(HasCostume_Sig, "HasCostume"))
            {
                IsSignatureValid(RandomPickHasCostumeCall_Sig, "RandomPickHasCostumeCall");
                INSTALL_HOOK(hook_HasCostume);

                if (IsSignatureValid(GetCostumeCSS_Sig, "GetCostumeCSS")) // called when a character is selected in the css
                {
                    INSTALL_HOOK(hook_GetCostumeCSS);
                }

                // called when a character is selected in the customize menu
                if (IsSignatureValid(GetCostumeButtonStateCustomizeMenu_Sig, "GetCostumeButtonStateCustomizeMenu") &&
                    IsSignatureValid(CustomizeMenuButtonToCostume_Sig, "CustomizeMenuButtonToCostume"))
                {
                    u64 buttonState = (u64)GetCostumeButtonStateCustomizeMenu_Sig;

                    IsWidgetInputFocusOwner = (bool(__fastcall*)(void*))GetAddressFromFuncCall(buttonState + 0x9);
                    IsCustomizeMenuInputBlocked = (bool(__fastcall*)())GetAddressFromFuncCall(buttonState + 0x12);

                    // TEST BPL, BPL; CMOVNZ EBX, R12D -> MOVZX EBX, BPL; use the button state as costume instead of costume 2
                    WRITE_MEMORY((u64)CustomizeMenuButtonToCostume_Sig + 0x9, u8, 0x40, 0x0f, 0xb6, 0xdd, 0x90, 0x90, 0x90);
                    INSTALL_HOOK(hook_GetCostumeButtonStateCustomizeMenu);
                }

                // costume select between the assist and color select of the css
                if (config::costumeSelectMenu &&
                    IsSignatureValid(CycleColorsCSS_Sig, "CycleColorsCSS") &&
                    IsSignatureValid(ColorSelectStepCSS_Sig, "ColorSelectStepCSS") &&
                    IsSignatureValid(LocalizeText_Sig, "LocalizeText"))
                {
                    u8* localizeText = (u8*)LocalizeText_Sig;

                    // CALL FString::Printf; ...; CALL FText::FromString; ...; CALL FString::~FString
                    if (IsColorSelectStepKnown() && localizeText[0x17E] == 0xE8 && localizeText[0x18A] == 0xE8 && localizeText[0x193] == 0xE8)
                    {
                        FStringPrintf = (UE4String*(__cdecl*)(UE4String*, const wchar_t*, ...))GetAddressFromFuncCall((u64)localizeText + 0x17E);
                        FTextFromString = (void*(__fastcall*)(void*, UE4String*))GetAddressFromFuncCall((u64)localizeText + 0x18A);
                        FStringDestroy = (void(__fastcall*)(UE4String*))GetAddressFromFuncCall((u64)localizeText + 0x193);

                        INSTALL_HOOK(hook_ColorSelectStepCSS);
                        INSTALL_HOOK(hook_FillColorSelectParamCSS);
                        INSTALL_HOOK(hook_RefreshPreviewPawnCSS);
                        INSTALL_HOOK(hook_AssistIconOpenAnim1PCSS);
                        INSTALL_HOOK(hook_AssistIconOpenAnim2PCSS);
                        INSTALL_HOOK(hook_LocalizeText);

                        isCostumeSelectEnabled = true;
                    }
                    else
                    {
                        printf("Costume select menu is not supported on this version of the game!\n");
                    }
                }
            }
        }

        // colors in the customize menu and everything that validates a selected color
        if (config::unlockColors && IsSignatureValid(IsColorAvailable_Sig, "IsColorAvailable"))
        {
            INSTALL_HOOK(hook_IsColorAvailable);
        }

        // cycling colors in css, the costume select cycles costumes through it as well
        if ((config::unlockColors || isCostumeSelectEnabled) && IsSignatureValid(CycleColorsCSS_Sig, "CycleColorsCSS"))
        {
            INSTALL_HOOK(hook_CycleColorsCSS);
        }

        if (config::PrintBlueprintErrors && IsSignatureValid(KismetExecuteMessage_Sig, "KismetExecuteMessage"))
        {
            INSTALL_HOOK(hook_KismetExecuteMessage);
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
