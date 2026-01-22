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
// Application
//
// This class represents the base application available to the end user.  The 
// Windows Main function is contained withing the .cpp file, and automatically
// checks for an instance of a CApplication class.  If one is not found then the
// program is exited.
//
// The application currently supports Input, Sound, Rendering, Logging, Timing, 
// and profiling.  These are all available to the user when building an 
// application.
//
// 06.02.2012: BeforeRegisterWindowClass method added by Francois Piette.
//--------------------------------------------------------------------------------
#ifndef Application_h
#define Application_h
//--------------------------------------------------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//--------------------------------------------------------------------------------
#include "PCH.h"

#include "Log.h"
#include "Timer.h"
#include "EventManager.h"
#include "IEventListener.h"
#include "IWindowProc.h"
#include "Scene.h"

// Window Events
#include "EvtWindowResize.h"

// Keyboard Events
#include "EvtChar.h"
#include "EvtKeyUp.h"
#include "EvtKeyDown.h"

// Mouse Events
#include "EvtMouseWheel.h"
#include "EvtMouseMove.h"
#include "EvtMouseLeave.h"
#include "EvtMouseLButtonUp.h"
#include "EvtMouseLButtonDown.h"
#include "EvtMouseMButtonUp.h"
#include "EvtMouseMButtonDown.h"
#include "EvtMouseRButtonUp.h"
#include "EvtMouseRButtonDown.h"
//--------------------------------------------------------------------------------
namespace Glyph3
{
class Application : public IEventListener , public IWindowProc
{
public:
    static Application* GetApplication();
protected:
    // Application pointer to ensure single instance
    static Application* ms_pApplication;

public:
    Application();
    virtual ~Application();

    virtual bool        ConfigureCommandLine( LPSTR lpcmdline );

    virtual bool        ConfigureEngineComponents() = 0;   // 애플리케이션에 필요한 엔진 컴포넌트 설정
    virtual void        ShutdownEngineComponents() = 0;    // 애플리케이션에 필요한 엔진 컴포넌트 종료

    virtual void        Initialize() = 0;                  // 애플리케이션 초기화
    virtual void        Update() = 0;                      // 애플리케이션 업데이트 및 렌더링
    virtual void        Shutdown() = 0;                    // 애플리케이션 종료

    virtual void        MessageLoop();
    virtual LRESULT     WindowProc( HWND hwnd , UINT msg , WPARAM wparam , LPARAM lparam );
    virtual void        BeforeRegisterWindowClass( WNDCLASSEX& wc );

    virtual bool        HandleEvent( EventPtr pEvent );

    void                RequestTermination();
    virtual void        TakeScreenShot() = 0;

public:
    // Helpers
    Timer*              m_pTimer;

    // Engine Compon    ents
    EventManager        m_EvtManager;

    Scene*              m_pScene;

    bool                m_bSaveScreenshot;
    bool                m_bLoop;

};
};
//--------------------------------------------------------------------------------
#endif // Application_h
//--------------------------------------------------------------------------------