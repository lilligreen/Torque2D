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

#ifndef _FMOD_AUDIO_H_
#define _FMOD_AUDIO_H_

#ifndef _STRINGTABLE_H_
#include "string/stringTable.h"
#endif

#include "fmod.hpp"

//-----------------------------------------------------------------------------

namespace FmodAudio
{
    static FMOD::System* mAudioSystem = NULL;

    bool initializeFmod(U32 maxChannels);
    void shutdownFmod();

    inline void updateAudioSystem(void) { mAudioSystem->update(); };

    FMOD::Sound* createSound(StringTableEntry filename, bool looping);
    FMOD::Sound* createStream(StringTableEntry filename, bool looping);

    S32 play(FMOD::Sound* sound, F32 volume);
    void stop(S32 index);
    void stopAll(void);
    void setPaused(S32 index, bool paused);
    bool getIsPlaying(S32 index);

    void setVolume(S32 index, F32 volume);
    F32 getVolume(S32 index);
    void setMute(S32 index, bool mute);
    bool getMute(S32 index);

    void setPan(S32 index, F32 pan);
    
    FMOD::Sound* createPositionalSound(StringTableEntry filename, bool looping);
    FMOD::Channel* createPositionalChannel(FMOD::Sound* sound);
    
    void updateAudioListener(const Vector2& position);
    inline S32 getListenerCount(void) { S32 count; mAudioSystem->get3DNumListeners(&count); return count; };
    Vector2 getListenerPosition(void);
}

#endif // _FMOD_AUDIO_H_
