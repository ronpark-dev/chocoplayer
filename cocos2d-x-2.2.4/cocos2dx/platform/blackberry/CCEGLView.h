/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_EGLVIEW_BLACKBERRY_H__
#define __CC_EGLVIEW_BLACKBERRY_H__

#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"
#include "platform/CCPlatformMacros.h"

#include <bps/event.h>

NS_CC_BEGIN

class CC_DLL CCEGLView : public CCEGLViewProtocol
{
public:
class CC_DLL EventHandler
	{
	public:
		virtual bool HandleBPSEvent(bps_event_t* event) = 0;

	    virtual ~EventHandler() {}
	};
public:
    CCEGLView();
    virtual ~CCEGLView();

    bool    isOpenGLReady();
	
	void    setEventHandler(EventHandler* pHandler);
    const char* getWindowGroupId() const;

    // keep compatible
    void    end();
    void    swapBuffers();
    void    setIMEKeyboardState(bool bOpen);
    
    // static function
    /**
    @brief    get the shared main open gl window
    */
    static CCEGLView* sharedOpenGLView();

    bool    handleEvents();
    screen_display_t getScreenDisplay() const;

private:
    void        release();

	bool 		initGL();
	void		initEGLFunctions();
	bool    	isGLExtension(const char *searchName) const;
	bool 		initDriver();
	void		showKeyboard();
	void		hideKeyboard();

	static bool 		m_initializedFunctions;
	static const GLubyte *m_extensions;

	bool			 m_isGLInitialized;
	bool 		     m_isWindowActive;
	
	EventHandler*	 m_pEventHandler;

	EGLDisplay 		 m_eglDisplay;
	EGLContext 		 m_eglContext;
	EGLSurface 		 m_eglSurface;
    screen_event_t 	 m_screenEvent;
    screen_window_t  m_screenWindow;
    screen_context_t m_screenContext;
    screen_display_t m_screen_display;
    char 			 m_windowGroupID[16];
};

NS_CC_END

#endif	// end of __CC_EGLVIEW_QNX_H__
