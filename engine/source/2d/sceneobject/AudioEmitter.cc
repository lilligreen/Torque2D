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
#include "2d/sceneobject/AudioEmitter.h"
#endif

#ifndef _DGL_H_
#include "graphics/dgl.h"
#endif

// Script bindings.
#include "2d/sceneobject/AudioEmitter_ScriptBinding.h"

//------------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(AudioEmitter);

//------------------------------------------------------------------------------

AudioEmitter::AudioEmitter()
{
}

//------------------------------------------------------------------------------

AudioEmitter::~AudioEmitter()
{
}

//------------------------------------------------------------------------------

void AudioEmitter::initPersistFields()
{
    // Call parent.
    Parent::initPersistFields();

    addProtectedField("Audio", TypeAudioAssetPtr, Offset(mAudioAsset, AudioEmitter), &setAudio, &getAudio, &writeAudio, "");
}

//------------------------------------------------------------------------------

void AudioEmitter::copyTo(SimObject* object)
{
    // Call to parent.
    Parent::copyTo(object);

    // Cast to emitter.
    AudioEmitter* pAudioEmitter = static_cast<AudioEmitter*>(object);

    // Sanity!
    AssertFatal(pAudioEmitter != NULL, "AudioEmitter::copyTo() - Object is not the correct type.");

    // Call audio provider.
    AudioProvider::copyTo(pAudioEmitter);
}

//-----------------------------------------------------------------------------

void AudioEmitter::integrateObject(const F32 totalTime, const F32 elapsedTime, DebugStats* pDebugStats)
{
    // Call Parent.
    Parent::integrateObject(totalTime, elapsedTime, pDebugStats);

    // Update attributes if spatials are dirty.
    if (getSpatialDirty())
    {
        // Fetch position.
        const Vector2 position = getPosition();

        // Update position.
        setAudioPosition(position);
    }
}

//-----------------------------------------------------------------------------

void AudioEmitter::sceneRenderOverlay(const SceneRenderState* sceneRenderState)
{
    // Call Parent.
    Parent::sceneRenderOverlay(sceneRenderState);

    // Get Scene.
    Scene* pScene = getScene();

    // Cannot do anything without scene!
    if (!pScene)
        return;

    // Don't draw debug if not enabled.
    if ( !isEnabled() )
        return;

    // Get merged Local/Scene Debug Mask.
    U32 debugMask = getDebugMask() | pScene->getDebugMask();

    // Finish here if we're not rendering any debug info or only have scene-rendered debug options.
    if ( !debugMask || (debugMask & ~(Scene::SCENE_DEBUG_METRICS | Scene::SCENE_DEBUG_JOINTS)) == 0 )
        return;

    // Clear blending.
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    // Draw audio volume distances.
    if (debugMask & Scene::SCENE_DEBUG_AUDIO_EMITTER)
    {
        pScene->mDebugDraw.DrawAudioEmitters( getRenderPosition(), getMinMaxDistance(), getRenderAngle() );
    }
}

//------------------------------------------------------------------------------

void AudioEmitter::onAudioEnd(void)
{
    // Do script callback.
    Con::executef(this, 1, "onAudioEnd");
}
