//-----------------------------------------------------------------------------
// Copyright (c) 2014 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _AUDIO_EMITTER_H_
#define _AUDIO_EMITTER_H_

#ifndef _SCENE_OBJECT_H_
#include "2d/sceneobject/SceneObject.h"
#endif

#ifndef _AUDIO_PROVIDER_H_
#include "audio/AudioProvider.h"
#endif

//------------------------------------------------------------------------------

class AudioEmitter : public SceneObject, public AudioProvider
{
    typedef SceneObject Parent;

public:
    AudioEmitter();
    virtual ~AudioEmitter();

    static void initPersistFields();
    virtual void copyTo(SimObject* object);

    virtual void integrateObject(const F32 totalTime, const F32 elapsedTime, DebugStats* pDebugStats);

    virtual void sceneRenderOverlay(const SceneRenderState* pSceneRenderState);

    // Declare Console Object.
    DECLARE_CONOBJECT(AudioEmitter);

protected:
    virtual void onAudioEnd(void);

protected:
    static bool setAudio(void* obj, const char* data)                       { DYNAMIC_VOID_CAST_TO(AudioEmitter, AudioProvider, obj)->setAudio(data); return false; };
    static const char* getAudio(void* obj, const char* data)                { return DYNAMIC_VOID_CAST_TO(AudioEmitter, AudioProvider, obj)->getAudio(); }
    static bool writeAudio( void* obj, StringTableEntry pFieldName )        { AudioEmitter* pCastObject = static_cast<AudioEmitter*>(obj); return pCastObject->mAudioAsset.notNull(); }
};

#endif // _AUDIO_EMITTER_H_
