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

ConsoleMethodGroupBeginWithDocs(AudioEmitter, SceneObject)

/*! Sets the audio asset Id to play.
    @param AudioAssetId The audio asset Id to play.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioEmitter, setAudio, ConsoleBool, 3, 3, (string AudioAssetId))
{
    // Set the audio asset.
    return static_cast<AudioProvider*>(object)->setAudio( argv[2] );
}

//-----------------------------------------------------------------------------

/*! Gets current audio asset Id.
    @return (string AudioAssetId) The current audio asset Id.
*/
ConsoleMethodWithDocs(AudioEmitter, getAudio, ConsoleString, 2, 2, ())
{
    // Get current audio.
    return static_cast<AudioProvider*>(object)->getAudio();
}

//-----------------------------------------------------------------------------

/*! Starts the audio playback.
    @return Returns the channel index the sound is playing on.
*/
ConsoleMethodWithDocs(AudioEmitter, play, ConsoleInt, 2, 2, ())
{
    Vector2 position = object->getPosition();
    
    return static_cast<AudioProvider*>(object)->playAudio(position);
}

//-----------------------------------------------------------------------------

/*! Stops the audio playback.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioEmitter, stop, ConsoleVoid, 2, 2, ())
{
    static_cast<AudioProvider*>(object)->stopAudio();
}

//-----------------------------------------------------------------------------

/*! Pauses or unpauses the emitter.
    @param paused Whether the audio should be paused or not.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioEmitter, setPaused, ConsoleVoid, 3, 3, (bool paused))
{
    // Get current audio.
    static_cast<AudioProvider*>(object)->pauseAudio( dAtob( argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets whether the emitter is paused or not.
    @return (bool isPaused) The current paused status, true = paused, false = playing.
*/
ConsoleMethodWithDocs(AudioEmitter, getPaused, ConsoleBool, 2, 2, ())
{
    // Get virtual state of channel.
    return static_cast<AudioProvider*>(object)->isAudioPaused();
}

//-----------------------------------------------------------------------------

/*! Gets whether the emitter is virtual or not.
    @return (bool isVirtual) The current virtual status, true = inaudible, false = audible.
*/
ConsoleMethodWithDocs(AudioEmitter, getVirtual, ConsoleBool, 2, 2, ())
{
    // Get virtual state of channel.
    return static_cast<AudioProvider*>(object)->isAudioVirtual();
}

//-----------------------------------------------------------------------------

/*! Retreives the combined volume after positional spatialization calculations are applied.
    @return A value specifying the audibility for the emitter's channel.
*/
ConsoleMethodWithDocs(AudioEmitter, getAudibility, ConsoleFloat, 2, 2, ())
{
    return static_cast<AudioProvider*>(object)->getAudibility();
}

//-----------------------------------------------------------------------------

/*! Mutes or unmutes the emitter.
    @param muted Whether the audio should be muted or not.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioEmitter, setMute, ConsoleVoid, 3, 3, (bool muted))
{
    static_cast<AudioProvider*>(object)->setMute( dAtob( argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets whether the emitter is muted or not.
    @return (bool isMuted) The current mute status, true = silent, false = audible.
*/
ConsoleMethodWithDocs(AudioEmitter, getMute, ConsoleBool, 2, 2, ())
{
    return static_cast<AudioProvider*>(object)->getMute();
}

//-----------------------------------------------------------------------------

/*! Set a volume [0.0, 1.0] for the emitter. Attenuation effects are still applied to this volume.
    @param volume A value between 0.0 and 1.0 specifying the new volume.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioEmitter, setVolume, ConsoleVoid, 3, 3, (volume))
{
    // Fetch the volume.
    F32 volume = mClampF(dAtof(argv[2]), 0.f, 1.f);

    // Set the volume.
    static_cast<AudioProvider*>(object)->setVolume(volume);
}

//-----------------------------------------------------------------------------

/*! Retreives the volume state of the emitter as given from the AudioAsset.
    To get the real-time volume level of the emitter in the scene, use getAudibility().
    @return A value between 0.0 and 1.0 specifying the volume for the emitter.
*/
ConsoleMethodWithDocs(AudioEmitter, getVolume, ConsoleFloat, 2, 2, ())
{
    return static_cast<AudioProvider*>(object)->getVolume();
}

//-----------------------------------------------------------------------------

/*! Gets the minimum and maximum audible distance for the emitter.
    @return (float min, float max) The minimum and maximum audible distances.
*/
ConsoleMethodWithDocs(AudioEmitter, getMinMaxDistance, ConsoleString, 2, 2, ())
{
    return static_cast<AudioProvider*>(object)->getMinMaxDistance().scriptThis();
}

//-----------------------------------------------------------------------------

/*! Retreives the position of the emitter as reported by the audio system. Used mainly for debugging.
    This should match the emitter's position in the scene when using getPosition().
    @return (float x / float y) The position of the audio emitter.
*/
ConsoleMethodWithDocs(AudioEmitter, getAudioPosition, ConsoleString, 2, 2, ())
{
    return static_cast<AudioProvider*>(object)->getAudioPosition().scriptThis();
}

ConsoleMethodGroupEndWithDocs(AudioEmitter)
