//--------------------------------------------------------------------------------
// This file is a portion of the Hieroglyph 3 Rendering Engine.  It is distributed
// under the MIT License, available in the root of this distribution and 
// at the following URL:
//
// http://www.opensource.org/licenses/mit-license.php
//
// Copyright (c) Jason Zink 
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//#include "PCH.h"
//#include "Application.h"
//#include "ScriptManager.h"

//#include "Timer.h"
//#include "Log.h"

//#include <sstream>

#include "Win32RenderWindow.h"
#include "IWindowProc.h"
#include "Win32Window.h"
//--------------------------------------------------------------------------------
using namespace Glyph3;


struct WindowProcessor : public IWindowProc
{
	virtual LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch( msg )
		{	

			case WM_CREATE: 
				{
					// Automatically return 0 to allow the window to proceed in the
					// creation process.

					return( 0 );
				} break;

			case WM_PAINT:
				{
					// This message is handled by the default handler to avoid a 
					// repeated sending of the message.  This results in the ability
					// to process all pending messages at once without getting stuck
					// in an eternal loop.
				} break;

			case WM_CLOSE:
				{
					// This message is sent when a window or an application should
					// terminate.
				} break;

			case WM_DESTROY: 
				{
					// This message is sent when a window has been destroyed.
					PostQuitMessage(0);
					return( 0 );
				} break;

			case WM_SIZE:
				{				
//					EvtWindowResizePtr pEvent = EvtWindowResizePtr( new EvtWindowResize( hwnd, wparam, lparam ) );
//					EvtManager.ProcessEvent( pEvent );
				} break;

		}

		return( DefWindowProc( hwnd, msg, wparam, lparam ) );
	}

	virtual void BeforeRegisterWindowClass(WNDCLASSEX &wc) 
	{
	};
};

/// <summary>
/// 메인 진입점 함수
/// </summary>
int WINAPI WinMain( _In_ HINSTANCE h_Inst, _In_opt_ HINSTANCE h_PrevInst, _In_ LPSTR lpcmdline, _In_ int ncmdshow )
{
	WindowProcessor messageHandler;

	Win32RenderWindow mainFrame;
	mainFrame.SetSize( 320, 240 );
	mainFrame.SetPosition( 200, 100 );
	mainFrame.Initialize( &messageHandler );
	
	Win32Window window2( 160, 240, L"Some Text" );

	for ( unsigned int i = 170; i < 320; i+=10 ) 
	{
		window2.SetSize(i,240);
		Sleep(100);
	}
	
	MSG msg;
	
	while( true )
	{
		while ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			if ( msg.message == WM_QUIT )
			{
				return true;
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		// Call the overloaded application update function.
		//Update();
		//TakeScreenShot();
	}

	return true;
}
//--------------------------------------------------------------------------------
