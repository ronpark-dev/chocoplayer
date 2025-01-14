#include "AppDelegate.h"
#include "cocos2d.h"
#include "CCEventType.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{

	JavaVM *g_VM;
	JNIEnv *g_env;
	char g_DefaultGamesPath[128];
	AppDelegate *g_pAppDelegate;
	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		g_VM = vm;

		JniHelper::setJavaVM(vm);

		return JNI_VERSION_1_4;
	}

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
	{
		g_env = env;

		if (!CCDirector::sharedDirector()->getOpenGLView())
		{
			CCEGLView *view = CCEGLView::sharedOpenGLView();
			view->setFrameSize(w, h);

			g_pAppDelegate = new AppDelegate();
			//pAppDelegate->setGamesPath(g_DefaultGamesPath);

			CCApplication::sharedApplication()->run();
		}
		else
		{
			ccGLInvalidateStateCache();
			CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
			ccDrawInit();
			CCTextureCache::reloadAllTextures();
			CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
			CCDirector::sharedDirector()->setGLDefaultValues();
		}
	}
}
