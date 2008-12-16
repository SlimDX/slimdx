/*
* Copyright (c) 2007-2008 SlimDX Group
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

namespace SlimDX
{
	namespace Windows
	{
		public ref class RenderWindow : System::Windows::Forms::NativeWindow, System::IDisposable
		{
		private:
			System::Windows::Forms::Control^ control;
			bool ignoreSizeChanges;
			bool keepCurrentSize;

			bool isMinimized;
			bool isMaximized;
			System::IntPtr monitor;
			System::Windows::Forms::Screen^ screen;
			System::Drawing::Size cachedSize;
			bool inSizeMove;

			int windowedWidth;
			int windowedHeight;
			int fullscreenWidth;
			int fullscreenHeight;
			WINDOWPLACEMENT *windowedPlacement;
			long windowedStyle;
			bool savedTopmost;

			bool hasOldSettings;
			bool oldWindowed;
			int oldWidth;
			int oldHeight;

			bool currentWindowed;
			int currentWidth;
			int currentHeight;

			void UpdateScreen();
			void Destruct();
			void HandleCreated( System::Object^ sender, System::EventArgs^ e );
			void HandleDestroyed( System::Object^ sender, System::EventArgs^ e );

		public:
			RenderWindow( System::Windows::Forms::Control^ control );
			~RenderWindow() { Destruct(); }
			!RenderWindow() { Destruct(); }

			void StartDeviceChange( bool windowed, int backBufferWidth, int backBufferHeight );
			bool EndDeviceChange();

			property System::Drawing::Size WindowedSize
			{
				System::Drawing::Size get() { return System::Drawing::Size( windowedWidth, windowedHeight ); }
			}

			property System::Drawing::Size FullscreenSize
			{
				System::Drawing::Size get() { return System::Drawing::Size( fullscreenWidth, fullscreenHeight ); }
			}

			property System::IntPtr Monitor
			{ 
				System::IntPtr get() { return monitor; } 
			}

			property System::Windows::Forms::Screen^ Screen 
			{ 
				System::Windows::Forms::Screen^ get() { return screen; }
			}

			property bool IsMinimized
			{ 
				bool get() { return isMinimized; }
			}

			property bool IsMaximized 
			{ 
				bool get() { return isMaximized; }
			}

			property System::Windows::Forms::Control^ Control
			{
				System::Windows::Forms::Control^ get() { return control; }
			}

			event System::EventHandler^ SizeChanged;
			event System::EventHandler^ MonitorChanged;
			event System::EventHandler^ Suspend;
			event System::EventHandler^ Resume;
			event System::EventHandler^ ApplicationActivated;
			event System::EventHandler^ ApplicationDeactivated;
			event System::EventHandler^ SystemSuspend;
			event System::EventHandler^ SystemResume;
			event System::ComponentModel::CancelEventHandler^ Screensaver;

		protected:
			virtual void OnSizeChanged( System::EventArgs^ e );
			virtual void OnMonitorChanged( System::EventArgs^ e );
			virtual void OnSuspend( System::EventArgs^ e );
			virtual void OnResume( System::EventArgs^ e );
			virtual void OnApplicationActivated( System::EventArgs^ e );
			virtual void OnApplicationDeactivated( System::EventArgs^ e );
			virtual void OnSystemSuspend( System::EventArgs^ e );
			virtual void OnSystemResume( System::EventArgs^ e );
			virtual void OnScreensaver( System::ComponentModel::CancelEventArgs^ e );

			virtual void WndProc( System::Windows::Forms::Message% m ) override;
		};
	}
}