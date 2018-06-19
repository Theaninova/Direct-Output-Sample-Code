extern "C" {
#include "DirectOutput.h"
}
#include <vector>
#include <iostream>

DWORD LED_FIRE = 0;
DWORD LED_FIRE_A_RED = 1;
DWORD LED_FIRE_A_GREEN = 2;
DWORD LED_FIRE_B_RED = 3;
DWORD LED_FIRE_B_GREEN = 4;
DWORD LED_FIRE_D_RED = 5;
DWORD LED_FIRE_D_GREEN = 6;
DWORD LED_FIRE_E_RED = 7;
DWORD LED_FIRE_E_GREEN = 8;
DWORD LED_TOGGLE_1_2_RED = 9;
DWORD LED_TOGGLE_1_2_GREEN = 10;
DWORD LED_TOGGLE_3_4_RED = 11;
DWORD LED_TOGGLE_3_4_GREEN = 12;
DWORD LED_TOGGLE_5_6_RED = 13;
DWORD LED_TOGGLE_5_6_GREEN = 14;
DWORD LED_POV_2_RED = 15;
DWORD LED_POV_2_GREEN = 16;
DWORD LED_CLUTCH_RED = 17;
DWORD LED_CLUTCH_GREEN = 18;
DWORD LED_THROTTLE = 19;

DWORD MFD_STRING_TOP = 0;
DWORD MFD_STRING_MIDDLE = 1;
DWORD MFD_STRING_BOTTOM = 2;

std::vector<void*> devices;

void __stdcall DirectOutput_Device_Callback(void* hDevice, bool bAdded, void* pvContext) {
    if (bAdded) {
        devices.push_back(hDevice);
    }
    else {

    }
}

void __stdcall DirectOutput_Enumerate_Callback(void* hDevice, void* pvContext) {
    devices.push_back(hDevice);
}

int main()
{
    const wchar_t * name = L"TestApp";
    DirectOutput_Initialize(name);
    DirectOutput_RegisterDeviceCallback(*DirectOutput_Device_Callback, nullptr);
    DirectOutput_Enumerate(*DirectOutput_Enumerate_Callback, nullptr);

    DWORD dwPage = 1;
    const wchar_t * pageDebugName = L"TestPage";
    DirectOutput_AddPage(devices[0], dwPage, pageDebugName, FLAG_SET_AS_ACTIVE);

    DirectOutput_SetLed(devices[0], dwPage, LED_FIRE_A_RED, 1);
    DirectOutput_SetLed(devices[0], dwPage, LED_FIRE_A_GREEN, 1);

    const wchar_t * value = L"Test App";
    DirectOutput_SetString(devices[0], dwPage, 1, 8, value);

    int x;
    std::cin >> x;

    DirectOutput_Deinitialize();

    return 0;
}
