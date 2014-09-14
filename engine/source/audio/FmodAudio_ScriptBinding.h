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

#ifndef _ASSET_MANAGER_H_
#include "assets/assetManager.h"
#endif

#ifndef _AUDIO_ASSET_H_
#include "audio/AudioAsset.h"
#endif

#ifndef _FMOD_AUDIO_H_
#include "audio/FmodAudio.h"
#endif

//-----------------------------------------------------------------------------

/*! @defgroup AudioFunctions Audio
    @ingroup TorqueScriptFunctions
    @{
*/

//-----------------------------------------------------------------------------

/*! Initialize the FMOD audio system. This must be done before all other audio operations.
    @param maxChannels The maximum number of channels FMOD is allowed to use. Limit is 4093.
    @return Returns true on successful initialization, false otherwise.
*/
ConsoleFunctionWithDocs(initializeFmod, ConsoleBool, 2, 2, (maxChannels))
{
    // Call the initialize function and return true if successful.
    if (FmodAudio::initializeFmod( dAtoi(argv[1]) ))
        return true;

    // Something went wrong.
    return false;
}

//-----------------------------------------------------------------------------

/*! Stops/shuts down the FMOD audio system.
    After this is called, you must restart with initializeFmod() to execute any new audio operations.
    @return No return value.
*/
ConsoleFunctionWithDocs(shutdownFmod, ConsoleVoid, 1, 1, ())
{
    FmodAudio::shutdownFmod();
}

//-----------------------------------------------------------------------------

/*! Play the AudioAsset.
    @param AudioAssetId The asset Id to play.
    @return The channel that is playing the AudioAsset or -1 on error.
*/
ConsoleFunctionWithDocs(audioPlay, ConsoleInt, 2, 2, (AudioAssetId))
{
    // Fetch asset Id.
    const char* pAssetId = argv[1];

    // Acquire audio asset.
    AudioAsset* pAudioAsset = AssetDatabase.acquireAsset<AudioAsset>(pAssetId);

    // Did we get the audio asset?
    if (pAudioAsset == NULL)
    {
        // No, so warn.
        Con::warnf( "audioPlay() - Could not find audio asset '%s'.", pAssetId );
        return -1;
    }
    
    FMOD::Sound* sound;

    // Is this a streaming asset?
    if (pAudioAsset->getStreaming())
    {
        // Open a sound to stream from disk.
        sound = FmodAudio::createStream(pAudioAsset->getAudioFile(), pAudioAsset->getLooping());
    }
    else
    {
        // Open a sound that's loaded into memory.
        sound = FmodAudio::createSound(pAudioAsset->getAudioFile(), pAudioAsset->getLooping());
    }

    // Play at the specified asset volume.
    S32 channelIndex = FmodAudio::play(sound, pAudioAsset->getVolume());
    
    // Release asset.
    AssetDatabase.releaseAsset(pAssetId);

    // Return the channel number.
    return channelIndex;
}

//-----------------------------------------------------------------------------

/*! Stops playing the AudioAsset. This makes the channel available again for re-use by the audio priority system.
    @param channel The index number of the channel to stop.
    @return No return value.
*/
ConsoleFunctionWithDocs(audioStop, ConsoleVoid, 2, 2, (channel))
{
    // Fetch the index.
    S32 index = dAtoi(argv[1]);

    // Stop the channel.
    FmodAudio::stop(index);
}

//-----------------------------------------------------------------------------

/*! Stops playing all AudioAssets. This makes all channels available again for re-use by the audio priority system.
    @return No return value.
*/
ConsoleFunctionWithDocs(audioStopAll, ConsoleVoid, 1, 1, ())
{
    // Stop everything.
    FmodAudio::stopAll();
}

//-----------------------------------------------------------------------------

/*! Pauses or resumes the playback of the AudioAsset.
    @param channel The channel to pause or unpause.
    @param paused True to pause, false to unpause.
    @return No return value.
*/
ConsoleFunctionWithDocs(audioSetPaused, ConsoleVoid, 3, 3, (int channel, bool paused))
{
    // Fetch the index.
    S32 index = dAtoi(argv[1]);
    
    // Fetch the paused status.
    bool paused = dAtob(argv[2]);

    // Pause the channel.
    FmodAudio::setPaused(index, paused);
}

//-----------------------------------------------------------------------------

/*! Retreives the playing state of the AudioAsset.
    @param channel The index number of the channel.
    @return No return value.
*/
ConsoleFunctionWithDocs(audioGetIsPlaying, ConsoleBool, 2, 2, (channel))
{
    // Fetch the index.
    S32 index = dAtoi(argv[1]);
    
    // Get the channel playing status.
    bool status = FmodAudio::getIsPlaying(index);
    
    return status;
}

//-----------------------------------------------------------------------------

/*! Set a volume [0.0, 1.0] for the channel specified by the channel index.
    @param channel An integer value, equal to or greater than 0, corresponding to a valid audio channel.
    @param volume A value between 0.0 and 1.0 specifying the new volume for the given channel.
    @return No return value.
*/
ConsoleFunctionWithDocs(audioSetVolume, ConsoleVoid, 3, 3, (channel, volume))
{
    // Fetch the index and volume.
    S32 index = dAtoi(argv[1]);
    F32 volume = mClampF(dAtof(argv[2]), 0.f, 1.f);

    // Set the volume.
    FmodAudio::setVolume(index, volume);
}

//-----------------------------------------------------------------------------

/*! Retreives the volume state of the AudioAsset.
    @param channel The index number of the channel.
    @return A value between 0.0 and 1.0 specifying the volume for the given channel.
*/
ConsoleFunctionWithDocs(audioGetVolume, ConsoleFloat, 2, 2, (channel))
{
    // Fetch the channel index.
    S32 index = dAtoi(argv[1]);
    
    // Get the volume.
    F32 volume = FmodAudio::getVolume(index);
    
    return volume;
}

//-----------------------------------------------------------------------------

/*! Sets whether the channel specified by the channel index is muted or not.
    @param channel An integer value, equal to or greater than 0, corresponding to a valid audio channel.
    @param mute A boolean: true mutes the channel, false unmutes it.
    @return No return value.
*/
ConsoleFunctionWithDocs(audioSetMute, ConsoleVoid, 3, 3, (channel, mute))
{
    // Fetch the index and mute status.
    S32 index = dAtoi(argv[1]);
    bool mute = dAtob(argv[2]);

    // Set the mute status.
    FmodAudio::setMute(index, mute);
}

//-----------------------------------------------------------------------------

/*! Retreives the mute state of the AudioAsset.
    @param channel The index number of the channel.
    @return True if the channel is muted (silent), false if unmuted (normal volume).
*/
ConsoleFunctionWithDocs(audioGetMute, ConsoleBool, 2, 2, (channel))
{
    // Fetch the channel index.
    S32 index = dAtoi(argv[1]);
    
    // Get the mute status.
    bool mute = FmodAudio::getMute(index);
    
    return mute;
}

//-----------------------------------------------------------------------------

/*! Sets the pan level [-1.0, 1.0] for the channel specified by the channel index.
    @param channel An integer value, equal to or greater than 0, corresponding to a valid audio channel.
    @param pan A value between -1.0 (left) and 1.0 (right) specifying the new pan level. Default = 0 (center).
    @return No return value.
*/
ConsoleFunctionWithDocs(audioSetPan, ConsoleVoid, 3, 3, (channel, pan))
{
    // Fetch the index and volume.
    S32 index = dAtoi(argv[1]);
    F32 pan = mClampF(dAtof(argv[2]), -1.f, 1.f);

    // Set the pan level.
    FmodAudio::setPan(index, pan);
}

//-----------------------------------------------------------------------------

/*! Retreives the number of audio listeners. Default is 1.
    @return The number of audio listeners.
*/
ConsoleFunctionWithDocs(audioGetListenerCount, ConsoleInt, 1, 1, ())
{
    return FmodAudio::getListenerCount();
}

//-----------------------------------------------------------------------------

/*! Gets the current position of the audio listener. This should match the position of the object in the scene.
    @return The number of audio listeners.
*/
ConsoleFunctionWithDocs(audioGetListenerPosition, ConsoleString, 1, 1, ())
{
    return FmodAudio::getListenerPosition().scriptThis();
}

/*! @} */ // group AudioFunctions
