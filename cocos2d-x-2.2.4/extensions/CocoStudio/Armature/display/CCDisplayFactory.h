/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#ifndef __CCDISPLAYFACTORY_H__
#define __CCDISPLAYFACTORY_H__

#include "../utils/CCArmatureDefine.h"
#include "../datas/CCDatas.h"

NS_CC_EXT_BEGIN

class CCSkin;
class CCBone;
class CCDecorativeDisplay;
class CCDisplayData;
/**
 *  @js NA
 *  @lua NA
 */
class CC_EX_DLL CCDisplayFactory
{
public:
    static void addDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData);
    static void createDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay);
    static void updateDisplay(CCBone *bone, float dt, bool dirty);

    static void addSpriteDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData);
    static void createSpriteDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay);
    static void initSpriteDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, const char *displayName, CCSkin *skin);


    static void addArmatureDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData);
    static void createArmatureDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay);
    static void updateArmatureDisplay(CCBone *bone, CCNode *display, float dt);

    static void addParticleDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay, CCDisplayData *displayData);
    static void createParticleDisplay(CCBone *bone, CCDecorativeDisplay *decoDisplay);
    static void updateParticleDisplay(CCBone *bone, CCNode *display, float dt);
};


NS_CC_EXT_END

#endif /*__CCDISPLAYFACTORY_H__*/
