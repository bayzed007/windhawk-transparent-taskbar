// ==WindhawkMod==
// @id              configurable-transparent-taskbar
// @name            Configurable Transparent Taskbar
// @description     Taskbar is fully transparent when idle, semi-transparent with maximized windows. Adjustable settings.
// @version         1.0
// @author          Bayzed
// @github          (none)
// @customSettings  {
//     "idleAlpha": {
//         "type": "number",
//         "label": "Idle transparency (0-255)",
//         "default": 0
//     },
//     "activeAlpha": {
//         "type": "number",
//         "label": "Active (maximized/fullscreen) transparency (0-255)",
//         "default": 160
//     },
//     "enableBlur": {
//         "type": "boolean",
//         "label": "Enable blur effect",
//         "default": false
//     }
// }
// ==/WindhawkMod==

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

HWND taskbar = nullptr;
UINT timerId = 1;

int idleAlpha, activeAlpha;
bool enableBlur;

void ApplyTaskbarStyle(BYTE alpha) {
    if (!taskbar) return;
    SetWindowLong(taskbar, GWL_EXSTYLE,
                  GetWindowLong(taskbar, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(taskbar, 0, alpha, LWA_ALPHA);

    if (enableBlur) {
        DWM_BLURBEHIND bb = {};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = TRUE;
        DwmEnableBlurBehindWindow(taskbar, &bb);
    }
}

bool IsAnyWindowMaximized() {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd || hwnd == taskbar) return false;

    WINDOWPLACEMENT wp = { sizeof(wp) };
    if (GetWindowPlacement(hwnd, &wp) && wp.showCmd == SW_MAXIMIZE)
        return true;

    RECT winRect, monRect;
    GetWindowRect(hwnd, &winRect);
    MONITORINFO mi = { sizeof(mi) };
    HMONITOR hMon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
    if (GetMonitorInfo(hMon, &mi)) {
        monRect = mi.rcMonitor;
        ret
