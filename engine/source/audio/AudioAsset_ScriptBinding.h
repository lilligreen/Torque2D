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

ConsoleMethodGroupBeginWithDocs(AudioAsset, AssetBase)

/*! Sets the audio file.
    @param AudioFile The audio file to associate with this asset.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setAudioFile, ConsoleVoid, 3, 3, (AudioFile))
{
    object->setAudioFile( argv[2] );
}

//-----------------------------------------------------------------------------

/*! Gets the audio file.
    @return Returns the audio file.
*/
ConsoleMethodWithDocs(AudioAsset, getAudioFile, ConsoleString, 2, 2, ())
{
    return object->getAudioFile();
}

//-----------------------------------------------------------------------------

/*! Sets the initial volume to play the audio file.
    @param volume The volume level as a float between 0.0 (no volume) and 1.0 (full volume).
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setVolume, ConsoleVoid, 3, 3, (volume))
{
    object->setVolume( dAtof(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the initial volume which the audio file is played at.
    @return The volume level as a float.
*/
ConsoleMethodWithDocs(AudioAsset, getVolume, ConsoleFloat, 2, 2, ())
{
    return object->getVolume();
}

//-----------------------------------------------------------------------------

/*! Sets whether the audio playback should loop or not.
    @param looping True/false.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setLooping, ConsoleVoid, 3, 3, (bool looping))
{
    object->setLooping( dAtob(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets whether the audio playback should loop or not.
    @return The looping parameter as a boolean.
*/
ConsoleMethodWithDocs(AudioAsset, getLooping, ConsoleBool, 2, 2, ())
{
    return object->getLooping();
}

//-----------------------------------------------------------------------------

/*! Sets whether the audio file should be streamed from disk or loaded into memory.
    @param streaming When true, the audio file will be streamed. When false, loaded into memory.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setStreaming, ConsoleVoid, 3, 3, (bool streaming))
{
    object->setStreaming( dAtob(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the streaming parameter for this asset.
    @return The streaming parameter as a boolean.
*/
ConsoleMethodWithDocs(AudioAsset, getStreaming, ConsoleBool, 2, 2, ())
{
    return object->getStreaming();
}

//-----------------------------------------------------------------------------

/*! Sets the minimum audible distance between the object and listener at which the volume will be at its maximum.
    @param distance The minimum volume distance in world units.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setMinDistance, ConsoleVoid, 3, 3, (distance))
{
    object->setMinDistance( dAtof(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the minimum audible distance for full volume between object and listener.
    @return The minimum audible distance in world units.
*/
ConsoleMethodWithDocs(AudioAsset, getMinDistance, ConsoleFloat, 2, 2, ())
{
    return object->getMinDistance();
}

//-----------------------------------------------------------------------------

/*! Sets the maximum audible distance between the object and listener after which the sound can no longer be heard.
    @param distance The maximum volume distance in world units.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setMaxDistance, ConsoleVoid, 3, 3, (distance))
{
    object->setMaxDistance( dAtof(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the maximum audible distance between object and listener at which the sound can be heard.
    @return The maximum audible distance in world units.
*/
ConsoleMethodWithDocs(AudioAsset, getMaxDistance, ConsoleFloat, 2, 2, ())
{
    return object->getMaxDistance();
}

//-----------------------------------------------------------------------------

/*! Sets the inside cone angle, in degrees. This is the angle within which the sound is at its normal volume. Must not be greater than 'OutsideAngle'.
    @param angle The inside cone angle, in degrees.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setInsideAngle, ConsoleVoid, 3, 3, (angle))
{
    object->setInsideAngle( dAtof(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the inside cone angle. This is the angle within which the sound is at its normal volume.
    @return The inside cone angle, in degrees.
*/
ConsoleMethodWithDocs(AudioAsset, getInsideAngle, ConsoleFloat, 2, 2, ())
{
    return object->getInsideAngle();
}

//-----------------------------------------------------------------------------

/*! Sets the outside cone angle, in degrees. This is the angle outside of which the sound is at its outside volume. Must not be less than 'InsideAngle'.
    @param angle The inside cone angle, in degrees.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setOutsideAngle, ConsoleVoid, 3, 3, (angle))
{
    object->setOutsideAngle( dAtof(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the outside cone angle. This is the angle outside of which the sound is at its outside volume.
    @return The outside cone angle, in degrees.
*/
ConsoleMethodWithDocs(AudioAsset, getOutsideAngle, ConsoleFloat, 2, 2, ())
{
    return object->getOutsideAngle();
}

//-----------------------------------------------------------------------------

/*! Sets the cone outside volume.
    @param volume The cone outside volume, as a float from 0.0 to 1.0.
    @return No return value.
*/
ConsoleMethodWithDocs(AudioAsset, setOutsideVolume, ConsoleVoid, 3, 3, (volume))
{
    object->setOutsideVolume( dAtof(argv[2]) );
}

//-----------------------------------------------------------------------------

/*! Gets the cone outside volume.
    @return The cone outside volume, from 0.0 to 1.0.
*/
ConsoleMethodWithDocs(AudioAsset, getOutsideVolume, ConsoleFloat, 2, 2, ())
{
    return object->getOutsideVolume();
}

ConsoleMethodGroupEndWithDocs(AudioAsset)
