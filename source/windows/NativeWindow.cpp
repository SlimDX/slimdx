/*
* Copyright (c) 2007-2014 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "stdafx.h"

#include "../InternalHelpers.h"

#include "NativeWindow.h"

using namespace System;
using namespace System::Drawing;
using namespace System::ComponentModel;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Windows
{
	static const DWORD WindowStyle = WS_OVERLAPPEDWINDOW;
	static const int MouseLeft = 0x1;
	static const int MouseMiddle = 0x2;
	static const int MouseRight = 0x4;
	static const int MouseXButton1 = 0x8;
	static const int MouseXButton2 = 0x10;
	static const int ControlKey = 0x20000;
	static const int AltKey = 0x40000;
	static const int ShiftKey = 0x10000;

	static int GetModiferKeys ()
	{
		int keys = 0;
		if (GetKeyState(VK_SHIFT))
			keys |= ShiftKey;
		if (GetKeyState(VK_CONTROL))
			keys |= ControlKey;
		if (GetKeyState(VK_MENU))
			keys |= AltKey;

		return keys;
	}

	static LRESULT CALLBACK InternalWindowProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		auto ptr = GetWindowLongPtr(hwnd, 0);
		if (ptr == 0)
			return DefWindowProc(hwnd, msg, wparam, lparam);
		else
		{
			auto handle = GCHandle::FromIntPtr(IntPtr(ptr));
			if (!handle.IsAllocated || !handle.Target)
				return DefWindowProc(hwnd, msg, wparam, lparam);

			auto window = (NativeWindow^)handle.Target;
			if (window->Handle.ToPointer() != hwnd)
				return DefWindowProc(hwnd, msg, wparam, lparam);

			return window->HandleMessage(msg, wparam, lparam);
		}
	}

	NativeWindow::NativeWindow ()
	{
		CreateHandle ("NativeWindow", 800, 600);
	}

	NativeWindow::NativeWindow (String^ title)
	{
		CreateHandle (title, 800, 600);
	}

	NativeWindow::NativeWindow (String^ title, int width, int height)
	{
		CreateHandle (title, width, height);
	}

	void NativeWindow::CreateHandle (String^ title, int width, int height) {
		m_title = title;
		m_minimumSize = Size(320, 240);
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(title);

		// setup the window class
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize			= sizeof(WNDCLASSEX);
		wc.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wc.lpfnWndProc		= InternalWindowProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= sizeof(void*);
		wc.hInstance		= 0;
		wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW); 
		wc.hbrBackground	= NULL;
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= L"NativeWindow";
		wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
		
		if (!RegisterClassEx(&wc))
			throw gcnew InvalidOperationException("Failed to register window class: " + GetLastError());

		// adjust the window size for correct device size
		RECT rc = { 0, 0, width, height };
		AdjustWindowRect(&rc, WindowStyle, FALSE);

		// create an instance of the window
		m_hwnd = CreateWindow(
			wc.lpszClassName,
			(LPCWSTR)pinnedName,
			WindowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rc.right - rc.left,
			rc.bottom - rc.top,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		);

		if (!m_hwnd)
			throw gcnew InvalidOperationException("Failed to create window: " + GetLastError());

		// set a handle to ourselves so that the window procedure can hand off messages
		auto handle = GCHandle::Alloc(this, GCHandleType::Weak);
		SetWindowLongPtr(m_hwnd, 0, (LONG_PTR)GCHandle::ToIntPtr(handle).ToPointer());
	}

	void NativeWindow::Show ()
	{
		ShowWindow(m_hwnd, SW_SHOWNORMAL);
	}

	void NativeWindow::Hide ()
	{
		ShowWindow(m_hwnd, SW_HIDE);
	}

	void NativeWindow::Close ()
	{
		if (m_hwnd)
		{
			// save off the final state of the window so that it can be persisted
			m_savedPlacement = GetPlacement();
			DestroyWindow(m_hwnd);
		}

		m_hwnd = nullptr;
	}

	void NativeWindow::ProcessMessages ()
	{
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				m_quit = true;
				return;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	String^ NativeWindow::Title::get ()
	{
		return m_title;
	}

	void NativeWindow::Title::set (String^ value)
	{
		m_title = value;

		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(value);
		SetWindowText(m_hwnd, (LPCWSTR)pinnedName);
	}

	Size NativeWindow::ClientSize::get ()
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		return Size(rc.right - rc.left, rc.bottom - rc.top);
	}

	void NativeWindow::ClientSize::set (Size value)
	{
		RECT rc = { 0, 0, value.Width, value.Height };
		AdjustWindowRect(&rc, WindowStyle, FALSE);

		SetWindowPos(m_hwnd, HWND_TOP, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	}

	IntPtr NativeWindow::Handle::get ()
	{
		return IntPtr(m_hwnd);
	}

	void NativeWindow::ClipCursor::set (bool value)
	{
		m_clipCursor = value;
		if (m_clipCursor)
		{
			RECT rc;
			GetWindowRect(m_hwnd, &rc);
			::ClipCursor(&rc);
		}
		else
			::ClipCursor(NULL);
	}

	NativeWindow::WindowPlacement NativeWindow::GetPlacement ()
	{
		if (m_hwnd == nullptr)
			return m_savedPlacement;

		WINDOWPLACEMENT p;
		memset(&p, 0, sizeof(WINDOWPLACEMENT));
		p.length = sizeof(WINDOWPLACEMENT);

		GetWindowPlacement(m_hwnd, &p);

		auto result = *reinterpret_cast<NativeWindow::WindowPlacement*>(&p);
		result.rcNormalPosition = Rectangle::FromLTRB(p.rcNormalPosition.left, p.rcNormalPosition.top, p.rcNormalPosition.right, p.rcNormalPosition.bottom);
		return result;
	}

	void NativeWindow::SetPlacement(NativeWindow::WindowPlacement placement)
	{
		auto p = *reinterpret_cast<WINDOWPLACEMENT*>(&placement);
		p.length = sizeof(WINDOWPLACEMENT);
		
		SetRect(
			&p.rcNormalPosition,
			placement.rcNormalPosition.Left,
			placement.rcNormalPosition.Top,
			placement.rcNormalPosition.Right,
			placement.rcNormalPosition.Bottom
		);

		SetWindowPlacement(m_hwnd, &p);
	}

	LRESULT NativeWindow::HandleMessage (UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_SIZE)
		{
			if (wparam == SIZE_MINIMIZED)
			{
				m_minimized = true;
				m_maximized = false;
				m_paused = true;

				Minimized(this, EventArgs::Empty);
			}
			else
			{
				RECT rect;
				GetClientRect(m_hwnd, &rect);
				if (rect.bottom - rect.top == 0)
				{
					// Rapidly clicking the task bar to minimize and restore a window
                    // can cause a WM_SIZE message with SIZE_RESTORED when 
                    // the window has actually become minimized due to rapid change
                    // so just ignore this message
				}
				else if (wparam == SIZE_MAXIMIZED)
				{
					if (m_minimized)
					{
						m_paused = false;
						Restored(this, EventArgs::Empty);
					}

					m_minimized = false;
					m_maximized = true;

					SizeChanged(this, EventArgs::Empty);
					UpdateScreen();
				}
				else if (wparam == SIZE_RESTORED)
				{
					if (m_minimized)
					{
						m_paused = false;
						Restored(this, EventArgs::Empty);
					}

					m_minimized = false;
					if (!m_sizeMove && (m_maximized || ClientSize != m_cachedSize))
					{
						m_maximized = false;

						SizeChanged(this, EventArgs::Empty);
						UpdateScreen();
						m_cachedSize = ClientSize;
					}

					m_maximized = false;
				}
			}
		}
		else if (msg == WM_KEYDOWN)
        {
			KeyPressed((int)wparam, GetModiferKeys());
			return 0;
        }
		else if (msg == WM_KEYUP)
        {
            KeyReleased((int)wparam, GetModiferKeys());
            return 0;
        }
		else if (msg == WM_CHAR)
        {
            CharacterEntered((wchar_t)wparam);
            return 0;
        }
		else if (msg == WM_MOUSEMOVE)
        {
            if (!m_trackingMouse)
			{
				TRACKMOUSEEVENT trackData;
				trackData.cbSize = sizeof(TRACKMOUSEEVENT);
				trackData.dwFlags = TME_LEAVE;
				trackData.dwHoverTime = 0;
				trackData.hwndTrack = m_hwnd;
				m_trackingMouse = TrackMouseEvent(&trackData) != 0;
			}

            short x = (short)LOWORD(lparam);
            short y = (short)HIWORD(lparam);
            MouseMoved(x, y);
        }
		else if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK)
			MouseButtonPressed(MouseLeft);
		else if (msg == WM_LBUTTONUP)
			MouseButtonReleased(MouseLeft);
		else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK)
			MouseButtonPressed(MouseRight);
		else if (msg == WM_RBUTTONUP)
			MouseButtonReleased(MouseRight);
		else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK)
			MouseButtonPressed(MouseMiddle);
		else if (msg == WM_MBUTTONUP)
			MouseButtonReleased(MouseMiddle);
		else if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONDBLCLK)
        {
            short button = (short)HIWORD(wparam);
            if (button == 1)
                MouseButtonPressed(MouseXButton1);
            if (button == 2)
                MouseButtonPressed(MouseXButton2);
        }
		else if (msg == WM_XBUTTONUP)
        {
            short button = (short)HIWORD(wparam);
            if (button == 1)
                MouseButtonReleased(MouseXButton1);
            if (button == 2)
                MouseButtonReleased(MouseXButton2);
        }
		else if (msg == WM_MOUSEHWHEEL)
        {
            short ticks = (short)HIWORD(wparam);
            MouseWheelRotated(ticks / 120);
        }
		else if (msg == WM_MOUSELEAVE)
		{
			MouseMoved(-1, -1);
			m_trackingMouse = false;
		}
		else if (msg == WM_PAINT)
		{
			if (m_paused)
				Paint(this, EventArgs::Empty);
		}
		else if (msg == WM_ENTERMENULOOP)
		{
			m_paused = true;
		}
		else if (msg == WM_EXITMENULOOP)
		{
			m_paused = false;
		}
		else if (msg == WM_ENTERSIZEMOVE)
		{
			m_paused = true;
			m_sizeMove = true;
			m_cachedSize = ClientSize;
		}
		else if (msg == WM_EXITSIZEMOVE)
		{
			m_paused = false;
			SizeChanged(this, EventArgs::Empty);
			UpdateScreen();

			m_sizeMove = false;
		}
		else if (msg == WM_GETMINMAXINFO)
		{
			auto info = (MINMAXINFO*)lparam;
			info->ptMinTrackSize.x = MinimumSize.Width;
			info->ptMinTrackSize.y = MinimumSize.Height;
		}
		else if (msg == WM_ACTIVATEAPP)
		{
			if (wparam != 0)
				Activated(this, EventArgs::Empty);
			else
				Deactivated(this, EventArgs::Empty);
		}
		else if (msg == WM_POWERBROADCAST)
		{
			if (wparam == PBT_APMQUERYSUSPEND)
			{
				SystemSuspend(this, EventArgs::Empty);
				return TRUE;
			}
			else if (wparam == PBT_APMRESUMESUSPEND)
			{
				SystemResume(this, EventArgs::Empty);
				return TRUE;
			}
		}
		else if (msg == WM_MENUCHAR)
		{
			// A menu is active and the user presses a key that does not correspond to any mnemonic or accelerator key
            // So just ignore and don't beep
			return MAKELRESULT(0, MNC_CLOSE);
		}
		else if (msg == WM_SYSCOMMAND)
		{
			auto command = wparam & 0xFFF0;
			if (command == SC_MONITORPOWER || command == SC_SCREENSAVE)
			{
				CancelEventArgs^ e = gcnew CancelEventArgs();
				Screensaver(this, e);
				if (e->Cancel)
					return FALSE;
			}
		}
		else if (msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP)
		{
			// don't allow the F10 key to act as a shortcut to the menu bar
			if (wparam == VK_F10)
				return FALSE;
		}
		else if (msg == WM_CLOSE)
		{
			// save off the final state of the window so that it can be persisted
			m_savedPlacement = GetPlacement();
		}
		else if (msg == WM_DESTROY)
		{
			m_hwnd = nullptr;
			PostQuitMessage(0);
		}

		return DefWindowProc(m_hwnd, msg, wparam, lparam);
	}

	void NativeWindow::UpdateScreen()
	{
		auto current = DisplayMonitor::FromWindow(Handle);
		if (m_monitor != nullptr && m_monitor->DeviceName != current->DeviceName)
		{
			m_monitor = current;
			MonitorChanged(this, EventArgs::Empty);
		}

		m_monitor = current;
	}
}
}