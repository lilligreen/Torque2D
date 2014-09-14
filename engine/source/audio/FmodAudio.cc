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

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

#ifndef _CONSOLE_H_
#include "console/console.h"
#endif

#ifndef _VECTOR2_H_
#include "2d/core/Vector2.h"
#endif

#include "audio/FmodAudio.h"
#include "audio/FmodAudio_ScriptBinding.h"

#include "fmod.hpp"
#include "fmod_errors.h"

//-----------------------------------------------------------------------------

namespace FmodAudio
{

bool initializeFmod(U32 maxChannels)
{
    FMOD_RESULT result;
    
    // Create a system object.
    result = FMOD::System_Create(&mAudioSystem);

    // Sanity.
    if (result != FMOD_OK)
    {
        Con::errorf("Cannot initialize FMOD Audio System");
        return false;
    }

    // Check if the maxChannels parameter is correct.
    if (maxChannels < 1 || maxChannels > 4093)
    {
        Con::errorf("FmodAudio::initializeFmod - incorrect amount of max channels specified");
        return false;
    }

    // Initialize the system object.
    result = mAudioSystem->init(maxChannels, FMOD_INIT_NORMAL, 0);

    // Sanity.
    if (result != FMOD_OK)
    {
        Con::errorf("FmodAudio::initializeFmod - %s", FMOD_ErrorString(result));
        return false;
    }

    Con::printf("FMOD Audio System initialized");

    // Initialize a start position for the listener.
    FMOD_VECTOR startPosition = {0.0f, 0.0f, 0.0f};

    // Set the listener attributes.
    result = mAudioSystem->set3DListenerAttributes(0, &startPosition, 0, 0, 0);

    // Sanity.
    if (result != FMOD_OK)
    {
        Con::errorf("FmodAudio::initializeFmod - %s", FMOD_ErrorString(result));
        return false;
    }

    // Flag startup as a success.
    return true;
}

//-----------------------------------------------------------------------------

void shutdownFmod()
{
    mAudioSystem->release();
    Con::printf("FMOD Audio System has been shutdown");
}

//-----------------------------------------------------------------------------

FMOD::Sound* createSound(StringTableEntry filename, bool looping)
{
    FMOD::Sound* pNewSound;
    FMOD_RESULT result;
    FMOD_MODE mode = FMOD_DEFAULT;

    // Check if this sound should loop.
    if (looping)
        mode = FMOD_LOOP_NORMAL;

    // Create the sound.
    result = mAudioSystem->createSound(filename, mode, 0, &pNewSound);

    // Sanity.    
    if (result != FMOD_OK)
    {
        Con::warnf("FmodAudio::createSound - %s", FMOD_ErrorString(result));
        return NULL;
    }

    return pNewSound;
}

//-----------------------------------------------------------------------------

FMOD::Sound* createStream(StringTableEntry filename, bool looping)
{
    FMOD::Sound* pNewSound;
    FMOD_RESULT result;
    FMOD_MODE mode = FMOD_DEFAULT;

    // Check if the stream should loop.
    if (looping)
        mode = FMOD_LOOP_NORMAL;

    // Create the stream.
    result = mAudioSystem->createStream(filename, mode, 0, &pNewSound);

    // Sanity.    
    if (result != FMOD_OK)
    {
        Con::warnf("FmodAudio::createStream - %s", FMOD_ErrorString(result));
        return NULL;
    }

    return pNewSound;
}

//-----------------------------------------------------------------------------

S32 play(FMOD::Sound* sound, F32 volume)
{
    FMOD::Channel* pChannel = 0;
    FMOD_RESULT result;
    S32 index = -1;

    // Set up the sound to play but leave the channel paused.
    result = mAudioSystem->playSound(sound, 0, true, &pChannel);

    // Sanity.
    if (result != FMOD_OK)
    {
        Con::warnf("FmodAudio::play - %s", FMOD_ErrorString(result));
        return index;
    }

    // Set the volume and unpause.
    pChannel->setVolume(volume);
    pChannel->setPaused(false);
    
    // Update the system.
    mAudioSystem->update();
    
    // Get the channel index.
    pChannel->getIndex(&index);

    return index;
}

//-----------------------------------------------------------------------------

void stop(S32 index)
{
    FMOD::Channel* pChannel = 0;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Stop playback.
    pChannel->stop();
    
    // Update the system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

void stopAll(void)
{
    FMOD::ChannelGroup* pMasterGroup;

    // Fetch the master channel group.
    mAudioSystem->getMasterChannelGroup(&pMasterGroup);
    
    // Stop playback.
    pMasterGroup->stop();
    
    // Update the system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

void setPaused(S32 index, bool paused)
{
    FMOD::Channel* pChannel = 0;
        
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
        
    // Pause or unpause the channel.
    pChannel->setPaused(paused);
    
    // Update the system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

bool getIsPlaying(S32 index)
{
    FMOD::Channel* pChannel = 0;
    bool status;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Retrieve playing status.
    pChannel->isPlaying(&status);
    
    // Return the status.
    return status;
}

//-----------------------------------------------------------------------------

void setVolume(S32 index, F32 volume)
{
    FMOD::Channel* pChannel = 0;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Set the volume level.
    pChannel->setVolume(volume);
    
    // Update the system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

F32 getVolume(S32 index)
{
    FMOD::Channel* pChannel = 0;
    F32 volume;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Retrieve the volume level.
    pChannel->getVolume(&volume);

    // Return the volume level.
    return volume;
}

//-----------------------------------------------------------------------------

void setMute(S32 index, bool mute)
{
    FMOD::Channel* pChannel = 0;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Set the mute status.
    pChannel->setMute(mute);
    
    // Update the system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

bool getMute(S32 index)
{
    FMOD::Channel* pChannel = 0;
    bool mute;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Retrieve the mute status.
    pChannel->getMute(&mute);

    // Return the mute status.
    return mute;
}

//-----------------------------------------------------------------------------

void setPan(S32 index, F32 pan)
{
    FMOD::Channel* pChannel = 0;
    
    // Get the channel.
    mAudioSystem->getChannel(index, &pChannel);
    
    // Set the pan level.
    pChannel->setPan(pan);
    
    // Update the system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

FMOD::Sound* createPositionalSound(StringTableEntry filename, bool looping)
{
    FMOD::Sound* pNewSound;
    FMOD_RESULT result;
    FMOD_MODE mode = FMOD_3D | FMOD_3D_LINEARROLLOFF;

    // Check if this sound should loop.
    if (looping)
        mode = FMOD_3D | FMOD_3D_LINEARROLLOFF | FMOD_LOOP_NORMAL;

    // Create the sound.
    result = mAudioSystem->createSound(filename, mode, 0, &pNewSound);

    // Sanity.
    if (result != FMOD_OK)
    {
        Con::warnf("FmodAudio::createPositionalSound - %s", FMOD_ErrorString(result));
        return NULL;
    }

    return pNewSound;
}

//-----------------------------------------------------------------------------

FMOD::Channel* createPositionalChannel(FMOD::Sound* sound)
{
    FMOD::Channel* pChannel = 0;
    FMOD_RESULT result;

    // Set up the sound to play but leave the channel paused.
    result = mAudioSystem->playSound(sound, 0, true, &pChannel);

    // Sanity.
    if (result != FMOD_OK)
    {
        Con::warnf("FmodAudio::createPositionalChannel - %s", FMOD_ErrorString(result));
        return NULL;
    }

    return pChannel;
}

//-----------------------------------------------------------------------------

void updateAudioListener( const Vector2& position )
{
    // Convert position to fmod vector.
    const FMOD_VECTOR fmodPosition = { position.x, position.y, 0.0f };

    // Update listener position.
    mAudioSystem->set3DListenerAttributes(0, &fmodPosition, 0, 0, 0);

    // Update audio system.
    mAudioSystem->update();
}

//-----------------------------------------------------------------------------

Vector2 getListenerPosition()
{
    FMOD_VECTOR fmodPosition;
    FMOD_VECTOR fmodVelocity;
    FMOD_VECTOR fmodForward;
    FMOD_VECTOR fmodUp;

    // Get attributes.
    mAudioSystem->get3DListenerAttributes(0, &fmodPosition, &fmodVelocity, &fmodForward, &fmodUp);

    // Convert to engine position.
    Vector2 position = { fmodPosition.x, fmodPosition.y };

    return position;
}

//-----------------------------------------------------------------------------

} // namespace FmodAudio
