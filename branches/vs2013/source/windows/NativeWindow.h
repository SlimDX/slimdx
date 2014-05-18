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
#pragma once

#include "DisplayMonitor.h"

namespace SlimDX
{
	namespace Windows
	{
		public ref class NativeWindow
		{
		public:
			NativeWindow ();
			NativeWindow (System::String^ title);
			NativeWindow (System::String^ title, int width, int height);

			void Show ();
			void Hide ();
			void Close ();
			void ProcessMessages ();

			property System::String^ Title
			{
				System::String^ get();
				void set(System::String^ value);
			}

			property System::Drawing::Size ClientSize
			{
				System::Drawing::Size get();
				void set(System::Drawing::Size value);
			}

			property System::Drawing::Size MinimumSize
			{
				System::Drawing::Size get() { return m_minimumSize; }
				void set(System::Drawing::Size value) { m_minimumSize = value; }
			}

			property bool ClipCursor
			{
				bool get() { return m_clipCursor; }
				void set(bool value);
			}

			property System::IntPtr Handle
			{
				System::IntPtr get();
			}

			property DisplayMonitor^ Monitor
			{
				DisplayMonitor^ get() { return m_monitor; }
			}

			property bool QuitRequested
			{
				bool get() { return m_quit; }
			}

			event System::EventHandler^ Paint;
			event System::EventHandler^ SizeChanged;
			event System::EventHandler^ Minimized;
			event System::EventHandler^ Restored;
			event System::EventHandler^ MonitorChanged;
			event System::EventHandler^ Activated;
			event System::EventHandler^ Deactivated;
			event System::EventHandler^ SystemSuspend;
			event System::EventHandler^ SystemResume;
			event System::ComponentModel::CancelEventHandler^ Screensaver;
			event System::Action<int, int>^ KeyPressed;
			event System::Action<int, int>^ KeyReleased;
			event System::Action<wchar_t>^ CharacterEntered;
			event System::Action<int>^ MouseButtonPressed;
			event System::Action<int>^ MouseButtonReleased;
			event System::Action<int, int>^ MouseMoved;
			event System::Action<int>^ MouseWheelRotated;

			[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
			value struct WindowPlacement
			{
				int length;
				int flags;
				int showCmd;
				System::Drawing::Point ptMinPosition;
				System::Drawing::Point ptMaxPosition;
				System::Drawing::Rectangle rcNormalPosition;
			};

			WindowPlacement GetPlacement ();
			void SetPlacement (WindowPlacement placement);

		internal:
			LRESULT HandleMessage (UINT msg, WPARAM wparam, LPARAM lparam);

		private:
			WindowPlacement m_savedPlacement;
			DisplayMonitor^ m_monitor;
			System::Drawing::Size m_cachedSize;
			System::Drawing::Size m_minimumSize;
			HWND m_hwnd;
			System::String^ m_title;
			bool m_sizeMove;
			bool m_minimized;
			bool m_maximized;
			bool m_paused;
			bool m_trackingMouse;
			bool m_quit;
			bool m_clipCursor;

			void CreateHandle (System::String^ caption, int width, int height);
			void UpdateScreen();
		};
	}
}