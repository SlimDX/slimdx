/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include <windows.h>

#include "../InternalHelpers.h"
#include "RenderWindow.h"

using namespace System;
using namespace System::Windows::Forms;

namespace SlimDX
{
namespace Windows
{
	RenderWindow::RenderWindow( System::Windows::Forms::Control^ control )
	{
		this->control = control;
		AssignHandle( control->Handle );

		control->HandleCreated += gcnew EventHandler( this, &RenderWindow::HandleCreated );
		control->HandleDestroyed += gcnew EventHandler( this, &RenderWindow::HandleDestroyed );

		cachedSize = control->Size;

		windowedPlacement = NULL;
		screen = System::Windows::Forms::Screen::FromHandle( Handle );
	}

	void RenderWindow::Destruct()
	{
		if( windowedPlacement != NULL )
			delete windowedPlacement;
		windowedPlacement = NULL;

		ReleaseHandle();
	}

	void RenderWindow::StartDeviceChange( bool windowed, int backBufferWidth, int backBufferHeight )
	{
		HWND hwnd = static_cast<HWND>( Handle.ToPointer() );
		ignoreSizeChanges = true;
		keepCurrentSize = ( backBufferWidth == 0 && backBufferHeight == 0 );

		oldWindowed = currentWindowed;
		oldWidth = currentWidth;
		oldHeight = currentHeight;

		currentWindowed = windowed;
		currentWidth = backBufferWidth;
		currentHeight = backBufferHeight;

		if( windowed )
		{
			if( hasOldSettings && !oldWindowed )
				SetWindowLong( hwnd, GWL_STYLE, windowedStyle );
		}
		else
		{
			if( !hasOldSettings || oldWindowed )
			{
				savedTopmost = ( GetWindowLong( hwnd, GWL_EXSTYLE ) & WS_EX_TOPMOST ) != 0;
				LONG style = GetWindowLong( hwnd, GWL_STYLE );
				style &= ~WS_MAXIMIZE & ~WS_MINIMIZE;
				windowedStyle = style;

				memset( windowedPlacement, 0, sizeof( WINDOWPLACEMENT ) );
				windowedPlacement->length = sizeof( WINDOWPLACEMENT );
				GetWindowPlacement( hwnd, windowedPlacement );
			}

			ShowWindow( hwnd, SW_HIDE );
			SetWindowLong( hwnd, GWL_STYLE, WS_POPUP | WS_SYSMENU );

			WINDOWPLACEMENT placement;
            memset( &placement, 0, sizeof( WINDOWPLACEMENT ) );
            placement.length = sizeof( WINDOWPLACEMENT );
            GetWindowPlacement( hwnd, &placement );
            if( ( placement.flags & WPF_RESTORETOMAXIMIZED ) != 0 )
            {
                // restore the window to normal if the window was maximized then minimized.  This causes the 
                // WPF_RESTORETOMAXIMIZED flag to be set which will cause SW_RESTORE to restore the 
                // window from minimized to maxmized which isn't what we want
                placement.flags &= ~WPF_RESTORETOMAXIMIZED;
                placement.showCmd = SW_RESTORE;
                SetWindowPlacement( hwnd, &placement );
            }
		}

		if( windowed )
		{
			if( hasOldSettings && !oldWindowed )
			{
				fullscreenWidth = oldWidth;
				fullscreenHeight = oldHeight;
			}
		}
		else
		{
			if( hasOldSettings && oldWindowed )
			{
				windowedWidth = oldWidth;
				windowedHeight = oldHeight;
			}
		}
	}

	bool RenderWindow::EndDeviceChange()
	{
		HWND hwnd = static_cast<HWND>( Handle.ToPointer() );

		if( hasOldSettings && !oldWindowed && currentWindowed )
		{
			SetWindowPlacement( hwnd, windowedPlacement );

			HWND insertAfter = savedTopmost ? HWND_TOPMOST : HWND_NOTOPMOST;
			SetWindowPos( hwnd, insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE );
		}

		if( currentWindowed && !keepCurrentSize )
		{
			int clientWidth;
			int clientHeight;

			if( IsIconic( hwnd ) )
			{
				// window is currently minimized. To tell if it needs to resize, 
				// get the client rect of window when its restored the 
				// hard way using GetWindowPlacement()
				WINDOWPLACEMENT wp;
				memset( &wp, 0, sizeof( WINDOWPLACEMENT ) );
				wp.length = sizeof( WINDOWPLACEMENT );
				GetWindowPlacement( hwnd, &wp );

				if( ( wp.flags & WPF_RESTORETOMAXIMIZED ) != 0 && wp.showCmd == SW_SHOWMINIMIZED )
				{
					// WPF_RESTORETOMAXIMIZED means that when the window is restored it will
					// be maximized.  So maximize the window temporarily to get the client rect 
					// when the window is maximized.  GetSystemMetrics( SM_CXMAXIMIZED ) will give this 
					// information if the window is on the primary but this will work on multimon.
					ShowWindow( hwnd, SW_RESTORE );
					RECT rect;
					GetClientRect( hwnd, &rect );
					clientWidth = rect.right - rect.left;
					clientHeight = rect.bottom - rect.top;
					ShowWindow( hwnd, SW_MINIMIZE );
				}
				else
				{
					// use wp.rcNormalPosition to get the client rect, but wp.rcNormalPosition 
					// includes the window frame so subtract it
					RECT frame = {0};
					AdjustWindowRect( &frame, windowedStyle, false );
					LONG frameWidth = frame.right - frame.left;
					LONG frameHeight = frame.bottom - frame.top;
					clientWidth = wp.rcNormalPosition.right - wp.rcNormalPosition.left - frameWidth;
					clientHeight = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top - frameHeight;
				}
			}
			else
			{
				// window is restored or maximized so just get its client rect
				RECT client;
				GetClientRect( hwnd, &client );
				clientWidth = client.right - client.left;
				clientHeight = client.bottom - client.top;
			}

			if( clientWidth != currentWidth || clientHeight != currentHeight )
			{
				if( IsIconic( hwnd ) )
					ShowWindow( hwnd, SW_RESTORE );
				if( IsZoomed( hwnd ) )
					ShowWindow( hwnd, SW_RESTORE );

				RECT window = {0};
				window.right = currentWidth;
				window.bottom = currentHeight;
				AdjustWindowRect( &window, GetWindowLong( hwnd, GWL_STYLE ), false );

				int cx = window.right - window.left;
				int cy = window.bottom - window.top;
				SetWindowPos( hwnd, 0, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE );

				// its possible that the new window size is not what we asked for.  
				// no window can be sized larger than the desktop, so see if the Windows OS resized the 
				// window to something smaller to fit on the desktop.  Also if WM_GETMINMAXINFO
				// will put a limit on the smallest/largest window size.
				RECT client;
				GetClientRect( hwnd, &client );
				clientWidth = client.right - client.left;
				clientHeight = client.bottom - client.top;

				if( clientWidth != currentWidth || clientHeight != currentHeight )
					return false;
			}
		}

		if( !IsWindowVisible( hwnd ) )
			ShowWindow( hwnd, SW_SHOW );

		// ensure that the display doesn't power down when fullscreen but does when windowed
		if( !currentWindowed )
			SetThreadExecutionState( ES_DISPLAY_REQUIRED | ES_CONTINUOUS );
		else
			SetThreadExecutionState( ES_CONTINUOUS );

		hasOldSettings = true;
		ignoreSizeChanges = false;

		return true;
	}

	void RenderWindow::OnSizeChanged( EventArgs^ e )
	{
		if( ignoreSizeChanges )
			return;

		if( &RenderWindow::SizeChanged != nullptr )
			SizeChanged( this, e );
	}

	void RenderWindow::OnMonitorChanged( EventArgs^ e )
	{
		if( ignoreSizeChanges )
			return;

		monitor = IntPtr( MonitorFromWindow( static_cast<HWND>( Handle.ToPointer() ), MONITOR_DEFAULTTOPRIMARY ) );

		if( &RenderWindow::MonitorChanged != nullptr )
			MonitorChanged( this, e );
	}

	void RenderWindow::OnSuspend( EventArgs^ e )
	{
		if( &RenderWindow::Suspend != nullptr )
			Suspend( this, e );
	}

	void RenderWindow::OnResume( EventArgs^ e )
	{
		if( &RenderWindow::Resume != nullptr )
			Resume( this, e );
	}

	void RenderWindow::OnApplicationActivated( EventArgs^ e )
	{
		if( &RenderWindow::ApplicationActivated != nullptr )
			ApplicationActivated( this, e );
	}

	void RenderWindow::OnApplicationDeactivated( EventArgs^ e )
	{
		if( &RenderWindow::ApplicationDeactivated != nullptr )
			ApplicationDeactivated( this, e );
	}

	void RenderWindow::OnSystemSuspend( EventArgs^ e )
	{
		if( &RenderWindow::SystemSuspend != nullptr )
			SystemSuspend( this, e );
	}

	void RenderWindow::OnSystemResume( EventArgs^ e )
	{
		if( &RenderWindow::SystemResume != nullptr )
			SystemResume( this, e );
	}

	void RenderWindow::OnScreensaver( System::ComponentModel::CancelEventArgs^ e )
	{
		if( &RenderWindow::Screensaver != nullptr )
			Screensaver( this, e );
	}

	void RenderWindow::HandleCreated( Object^ sender, EventArgs^ e )
	{
		SLIMDX_UNREFERENCED_PARAMETER( sender );
		SLIMDX_UNREFERENCED_PARAMETER( e );

		AssignHandle( control->Handle );
	}

	void RenderWindow::HandleDestroyed( Object^ sender, EventArgs^ e )
	{
		SLIMDX_UNREFERENCED_PARAMETER( sender );
		SLIMDX_UNREFERENCED_PARAMETER( e );

		ReleaseHandle();
	}

	void RenderWindow::WndProc( Message% m )
	{
        if( m.Msg == WM_SIZE )
        {
			if( m.WParam.ToInt32() == SIZE_MINIMIZED )
            {
                isMinimized = true;
                isMaximized = false;

				OnSuspend( EventArgs::Empty );
            }
            else
            {
				HWND hwnd = static_cast<HWND>( Handle.ToPointer() );
				RECT client;
				GetClientRect( hwnd, &client );

				if( client.bottom - client.top == 0 )
                {
                    // rapidly clicking the task bar to minimize and restore a window
                    // can cause a WM_SIZE message with SIZE_RESTORED when 
                    // the window has actually become minimized due to rapid change
                    // so just ignore this message
                }
                else if( m.WParam.ToInt32() == SIZE_MAXIMIZED )
                {
                    if( isMinimized )
						OnResume( EventArgs::Empty );

                    isMinimized = false;
                    isMaximized = true;

					OnSizeChanged( EventArgs::Empty );
                    UpdateScreen();
                }
                else if( m.WParam.ToInt32() == SIZE_RESTORED )
                {
                    if( isMinimized )
						OnResume( EventArgs::Empty );

                    isMinimized = false;
                    isMaximized = false;

                    if( !inSizeMove && control->Size != cachedSize )
                    {
						OnSizeChanged( EventArgs::Empty );
                        UpdateScreen();
                        cachedSize = control->Size;
                    }
                }
            }
        }
        else if( m.Msg == WM_ACTIVATEAPP )
        {
			if( m.WParam != IntPtr::Zero )
				OnApplicationActivated( EventArgs::Empty );
            else
				OnApplicationDeactivated( EventArgs::Empty );
        }
        else if( m.Msg == WM_POWERBROADCAST )
        {
            if( m.WParam.ToInt32() == PBT_APMQUERYSUSPEND )
            {
				OnSystemSuspend( EventArgs::Empty );
                m.Result = IntPtr( 1 );
                return;
            }
            else if( m.WParam.ToInt32() == PBT_APMRESUMESUSPEND )
            {
				OnSystemResume( EventArgs::Empty );
                m.Result = IntPtr( 1 );
                return;
            }
        }
        else if( m.Msg == WM_SYSCOMMAND )
        {
            long wparam = m.WParam.ToInt64() & 0xFFF0;
            if( wparam == SC_MONITORPOWER || wparam == SC_SCREENSAVE )
            {
				System::ComponentModel::CancelEventArgs^ e = gcnew System::ComponentModel::CancelEventArgs();
                OnScreensaver( e );
                if( e->Cancel )
                {
					m.Result = IntPtr::Zero;
                    return;
                }
            }
        }
		else if( m.Msg == WM_ENTERSIZEMOVE )
		{
			inSizeMove = true;
			cachedSize = control->Size;
			OnSuspend( EventArgs::Empty );
		}
		else if( m.Msg == WM_EXITSIZEMOVE )
		{
			OnSizeChanged( EventArgs::Empty );
			UpdateScreen();
			inSizeMove = false;

			OnResume( EventArgs::Empty );
		}

		NativeWindow::WndProc( m );
	}

	void RenderWindow::UpdateScreen()
	{
		System::Windows::Forms::Screen^ s = System::Windows::Forms::Screen::FromHandle( Handle );
		if( screen == nullptr || screen->DeviceName != s->DeviceName )
		{
			screen = s;
			if( screen != nullptr )
				OnMonitorChanged( EventArgs::Empty );
		}
	}
}
}