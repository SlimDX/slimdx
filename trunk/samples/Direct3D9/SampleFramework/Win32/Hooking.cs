using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SampleFramework
{
    #region HookType

    enum HookType
    {
        WH_JOURNALRECORD = 0,
        WH_JOURNALPLAYBACK = 1,
        WH_KEYBOARD = 2,
        WH_GETMESSAGE = 3,
        WH_CALLWNDPROC = 4,
        WH_CBT = 5,
        WH_SYSMSGFILTER = 6,
        WH_MOUSE = 7,
        WH_HARDWARE = 8,
        WH_DEBUG = 9,
        WH_SHELL = 10,
        WH_FOREGROUNDIDLE = 11,
        WH_CALLWNDPROCRET = 12,
        WH_KEYBOARD_LL = 13,
        WH_MOUSE_LL = 14
    }

    #endregion

    #region KBDLLHOOKSTRUCT

    [StructLayout(LayoutKind.Sequential)]
    class KBDLLHOOKSTRUCT
    {
        #region Fields

        public int vkCode;
        public int scanCode;
        public int flags;
        public int time;
        public IntPtr dwExtraInfo;

        #endregion
    }

    #endregion

    #region LowLevelKeyboardProc

    delegate int LowLevelKeyboardProc(int nCode, int wParam, KBDLLHOOKSTRUCT lParam);

    #endregion
}
