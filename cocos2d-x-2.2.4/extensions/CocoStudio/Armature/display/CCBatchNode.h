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

#ifndef __CCBATCHNODE_H__
#define __CCBATCHNODE_H__

#include "../utils/CCArmatureDefine.h"

NS_CC_EXT_BEGIN
/**
 *  @lua NA
 */
class CC_EX_DLL CCBatchNode : public CCNode
{
public:
    static CCBatchNode *create();
public:
    /**
     *  @js ctor
     */
    CCBatchNode();
    /**
     *  @js NA
     */
    ~CCBatchNode();
    /**
     *  @js NA
     */
    virtual bool init();
    virtual void addChild(CCNode *pChild);
    virtual void addChild(CCNode *pChild, int zOrder);
    virtual void addChild(CCNode *pChild, int zOrder, int tag);
    virtual void removeChild(CCNode* child, bool cleanup);
    virtual void visit();
    /**
     *  @js NA
     */
    void draw();

    virtual CCTextureAtlas *getTexureAtlasWithTexture(CCTexture2D *texture);
protected:
    CCTextureAtlas *m_pAtlas;
    CCDictionary *m_pTextureAtlasDic;
};

NS_CC_EXT_END

#endif /*__CCBATCHNODE_H__*/
