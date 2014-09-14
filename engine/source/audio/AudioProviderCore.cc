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

#include "audio/AudioProviderCore.h"

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

#ifndef _STRINGBUFFER_H_
#include "string/stringBuffer.h"
#endif

#ifndef _FMOD_AUDIO_H_
#include "audio/FmodAudio.h"
#endif

#ifndef _VECTOR2_H_
#include "2d/core/Vector2.h"
#endif

//-----------------------------------------------------------------------------

AudioProviderCore::AudioProviderCore() : mpAudioAsset(NULL)
{
}

//-----------------------------------------------------------------------------

AudioProviderCore::~AudioProviderCore()
{
    // Reset the state.
    resetState();
}

//-----------------------------------------------------------------------------

void AudioProviderCore::allocateAssets(AssetPtr<AudioAsset>* pAudioAssetPtr)
{
    // Sanity!
    AssertFatal( mpAudioAsset == NULL, "AudioProviderCore: Assets already allocated." );
    AssertFatal( pAudioAssetPtr != NULL, "AudioProviderCore: AudioAsset pointer cannot be NULL." );

    // Reset the state.
    resetState();

    // Set asset pointer.
    mpAudioAsset = pAudioAssetPtr;
}

//-----------------------------------------------------------------------------

void AudioProviderCore::resetState(void)
{
    mSelfTick = false;

    mAudioPlaying = false;
    mAudioPaused = false;
    mAudioFinished = true;
    mAudioVirtual = false;
    
    mChannel = NULL;
    mSound = NULL;

    clearAssets();
}

//-----------------------------------------------------------------------------

void AudioProviderCore::copyTo(AudioProviderCore* pAudioProviderCore) const
{
    // Sanity!
    AssertFatal(pAudioProviderCore != NULL, "AudioProviderCore::copyTo - Copy object cannot be NULL.");

    // Set self ticking.
    pAudioProviderCore->mSelfTick = mSelfTick;
}

//------------------------------------------------------------------------------

void AudioProviderCore::update(const F32 elapsedTime)
{
    // Finish if the audio has finished or is paused.
    if ( isAudioFinished() || isAudioPaused() )
        return;

    // Update the audio.
    updateAudio( Tickable::smTickSec );

    // Finish if the audio has NOT finished.
    if ( !isAudioFinished() )
        return;

    // Turn-off tick processing.
    setProcessTicks(false);

    // Perform callback.
    onAudioEnd();
}

//------------------------------------------------------------------------------

void AudioProviderCore::processTick(void)
{
    // Update using tick period.
    update( Tickable::smTickSec );
}

//-----------------------------------------------------------------------------

void AudioProviderCore::updateAudio(const F32 elapsedTime)
{
    // Check virtual status and update.
    mChannel->isVirtual(&mAudioVirtual);

    // Get the playing state of the channel.
    mChannel->isPlaying(&mAudioPlaying);

    // If we are not playing and not paused and not virtual, then the audio has ended.
    if (!mAudioPlaying && !mAudioPaused && !mAudioVirtual)
    {
        mAudioFinished = true;
    }
}

//-----------------------------------------------------------------------------

bool AudioProviderCore::setAudio(const char* pAudioAssetId)
{
    // Set asset.
    mpAudioAsset->setAssetId(pAudioAssetId);

    // Finish if we didn't get an audio asset.
    if ( mpAudioAsset->isNull() )
        return false;

    // Create a sound.
    if ( !createSound(*mpAudioAsset) )
        return false;

    // Return Okay.
    return true;
}

//-----------------------------------------------------------------------------

bool AudioProviderCore::createSound(const AssetPtr<AudioAsset>& pAudioAsset)
{
    // Finish if no audio asset.
    if ( pAudioAsset.isNull() )
        return false;

    // Create a sound from this asset.
    mSound = FmodAudio::createPositionalSound(pAudioAsset->getAudioFile(), pAudioAsset->getLooping());

    // Sanity.
    if (mSound == NULL)
        return false;

    // Return Okay.
    return true;
}

//-----------------------------------------------------------------------------

S32 AudioProviderCore::playAudio(Vector2 position)
{
    S32 index = -1;

    // Sanity.
    if (mSound == NULL)
        return index;
    
    // Assign the sound a channel for playback.
    mChannel = FmodAudio::createPositionalChannel(mSound);
    
    // Set audio position.
    setAudioPosition(position);

    // Get the audio asset.
    const AssetPtr<AudioAsset>& pAudioAsset = *mpAudioAsset;

    // Set the base volume.
    mChannel->setVolume(pAudioAsset->getVolume());

    // Set the audible distance.
    F32 minDistance = pAudioAsset->getMinDistance();
    F32 maxDistance = pAudioAsset->getMaxDistance();

    mChannel->set3DMinMaxDistance(minDistance, maxDistance);

    // Play.
    mChannel->setPaused(false);
    
    // Update.
    FmodAudio::updateAudioSystem();
    
    // Reset audio finished flag.
    mAudioFinished = false;

    // Turn on tick processing.
    setProcessTicks(true);

    // Get the channel index and return it.
    mChannel->getIndex(&index);
    
    return index;
}

//------------------------------------------------------------------------------

Vector2 AudioProviderCore::getMinMaxDistance(void)
{
    F32 minDistance;
    F32 maxDistance;

    // Get the min/max volume distances.
    mChannel->get3DMinMaxDistance(&minDistance, &maxDistance);

    // Combine the floats into a vector.
    Vector2 distances = { minDistance, maxDistance };

    return distances;
}

//------------------------------------------------------------------------------

void AudioProviderCore::setAudioPosition(const Vector2& position)
{
    // Convert to FMOD vector.
    const FMOD_VECTOR fmodPosition = { position.x, position.y, 0.0f };

    // Update channel.
    if (mChannel != NULL)
    {
        mChannel->set3DAttributes(&fmodPosition, 0, 0);
    }
}

//------------------------------------------------------------------------------

Vector2 AudioProviderCore::getAudioPosition(void)
{
    FMOD_VECTOR fmodPosition;
    FMOD_VECTOR fmodVelocity;

    mChannel->get3DAttributes(&fmodPosition, &fmodVelocity);

    Vector2 position = { fmodPosition.x, fmodPosition.y };

    return position;
}

//------------------------------------------------------------------------------

void AudioProviderCore::setConeOrientation(const F32 angle)
{
    // Convert to radians.
    F32 radians = mDegToRad(angle);

    // Create FMOD vector.
    FMOD_VECTOR coneVector = { mCos(radians), mSin(radians), 0.0f };

    // Update channel.
    if (mChannel != NULL)
    {
        mChannel->set3DConeOrientation(&coneVector);
    }
}

//------------------------------------------------------------------------------

F32 AudioProviderCore::getConeOrientation(void)
{
    FMOD_VECTOR coneVector;

    // Get the cone orientation vector.
    mChannel->get3DConeOrientation(&coneVector);

    // Convert the vector to an angle.
    F32 radians = mAtan(coneVector.x, coneVector.y);

    // Convert radians to degrees.
    F32 angle = mRadToDeg(radians);

    return angle;
}

//------------------------------------------------------------------------------

Vector2 AudioProviderCore::getConeAngles(void)
{
    F32 insideAngle;
    F32 outsideAngle;
    F32 outsideVolume;

    // Get the cone settings.
    mChannel->get3DConeSettings(&insideAngle, &outsideAngle, &outsideVolume);

    // Combine the angles into a vector. The volume is ignored.
    Vector2 angles = { insideAngle, outsideAngle };

    return angles;
}

//------------------------------------------------------------------------------

void AudioProviderCore::clearAssets(void)
{
    // Clear asset.
    if (mpAudioAsset != NULL)
        mpAudioAsset->clear();

    // Reset remaining state.
    setProcessTicks(false);
}

//-----------------------------------------------------------------------------

void AudioProviderCore::onAssetRefreshed(AssetPtrBase* pAssetPtrBase)
{
    // Don't perform any action if the audio is not already playing.
    if (mAudioFinished)
        return;

    // Create a sound.
    createSound(*mpAudioAsset);

    // Attempt to restart the audio.
    playAudio(getAudioPosition());
}
