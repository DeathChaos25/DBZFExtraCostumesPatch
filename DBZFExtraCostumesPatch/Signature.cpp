#pragma once

#include "pch.h"
#include "Signature.h"
#include <Psapi.h>

FORCEINLINE void* sigScan(const char* signature, const char* mask, size_t sigSize, void* memory, const size_t memorySize)
{
    if (sigSize == 0)
        sigSize = strlen(mask);

    for (size_t i = 0; i < memorySize; i++)
    {
        char* currMemory = (char*)memory + i;

        size_t j;
        for (j = 0; j < sigSize; j++)
        {
            if (mask[j] != '?' && signature[j] != currMemory[j])
                break;
        }

        if (j == sigSize)
            return currMemory;
    }

    return nullptr;
}

MODULEINFO moduleInfo;

const MODULEINFO& getModuleInfo()
{
    if (moduleInfo.SizeOfImage)
        return moduleInfo;

    ZeroMemory(&moduleInfo, sizeof(MODULEINFO));
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(MODULEINFO));

    return moduleInfo;
}

FORCEINLINE void* sigScan(const char* signature, const char* mask, void* hint)
{
    const MODULEINFO& info = getModuleInfo();
    const size_t sigSize = strlen(mask);

    // Ensure hint address is within the process memory region so there are no crashes.
    if ((hint >= info.lpBaseOfDll) && ((char*)hint + sigSize <= (char*)info.lpBaseOfDll + info.SizeOfImage))
    {
        void* result = sigScan(signature, mask, sigSize, hint, sigSize);

        if (result)
            return result;
    }

    return sigScan(signature, mask, sigSize, info.lpBaseOfDll, info.SizeOfImage);
}

FORCEINLINE uint64_t GetCurrentBaseAddress( void )
{
    return (uint64_t)getModuleInfo().lpBaseOfDll;
}

FORCEINLINE void hexDump(const char* desc, void* addr, u32 len)
{
    int i;
    unsigned char buff[17];
    unsigned char* pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf("%s:\n", desc);

    // Process every byte in the data.
    for (i = 0; i < len; i++)
    {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0)
        {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf("  %s\n", buff);

            // Output the offset.
            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
        {
            buff[i % 16] = '.';
        }
        else
        {
            buff[i % 16] = pc[i];
        }

        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0)
    {
        printf("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf("  %s\n", buff);
}

FORCEINLINE u64 GetAddressFromGlobalRef(u64 a1)
{
    int opd = *(int*)(a1 + 3);
    return (a1 + opd + 7);
}

FORCEINLINE u64 GetAddressFromFuncCall(u64 a1)
{
    int opd = *(int*)(a1 + 1);
    return (a1 + opd + 5);
}

FORCEINLINE u64 GetAddressFromMOV(u64 a1)
{
    int opd = *(int*)(a1 + 2);
    return (a1 + opd + 7);
}
