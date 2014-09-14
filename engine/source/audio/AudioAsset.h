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

#ifndef _AUDIO_ASSET_H_
#define _AUDIO_ASSET_H_

#ifndef _SIMBASE_H_
#include "sim/simBase.h"
#endif

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
#endif

#ifndef _UTILITY_H_
#include "2d/core/Utility.h"
#endif

//----------------------------------------------------------------------------

DefineConsoleType(TypeAudioAssetPtr)

//----------------------------------------------------------------------------

class AudioAsset: public AssetBase
{
private:
    typedef AssetBase Parent;

    StringTableEntry    mAudioFile;
    F32                 mVolume;
    bool                mIsLooping;
    bool                mIsStreaming;
    F32                 mMinDistance;
    F32                 mMaxDistance;
    F32                 mInsideAngle;
    F32                 mOutsideAngle;
    F32                 mOutsideVolume;

public:
    AudioAsset();
    static void initPersistFields();
    virtual void copyTo(SimObject* object);

    void setAudioFile(const char* pAudioFile);
    inline StringTableEntry getAudioFile(void) const { return mAudioFile; }

    void setVolume(const F32 volume);
    inline F32 getVolume(void) const { return mVolume; }

    void setLooping(const bool looping);
    inline bool getLooping(void) const { return mIsLooping; }

    void setStreaming(const bool streaming);
    inline bool getStreaming(void) const { return mIsStreaming; }

    void setMinDistance(const F32 minDistance);
    inline F32 getMinDistance(void) const { return mMinDistance; }

    void setMaxDistance(const F32 maxDistance);
    inline F32 getMaxDistance(void) const { return mMaxDistance; }

    void setInsideAngle(const F32 angle);
    inline F32 getInsideAngle(void) const { return mInsideAngle; }

    void setOutsideAngle(const F32 angle);
    inline F32 getOutsideAngle(void) const { return mOutsideAngle; }

    void setOutsideVolume(const F32 volume);
    inline F32 getOutsideVolume(void) const { return mOutsideVolume; }

    DECLARE_CONOBJECT(AudioAsset);

protected:
    virtual void initializeAsset(void);

    /// Taml callbacks.
    virtual void onTamlPreWrite(void);
    virtual void onTamlPostWrite(void);

protected:
    static bool setAudioFile(void* obj, const char* data)                  { static_cast<AudioAsset*>(obj)->setAudioFile(data); return false; }
    static const char* getAudioFile(void* obj, const char* data)           { return static_cast<AudioAsset*>(obj)->getAudioFile(); }

    static bool setVolume(void* obj, const char* data)                     { static_cast<AudioAsset*>(obj)->setVolume(dAtof(data)); return false; }
    static bool writeVolume(void* obj, StringTableEntry pFieldName)        { return mNotEqual(static_cast<AudioAsset*>(obj)->getVolume(), 1.0f); }

    static bool setLooping(void* obj, const char* data)                    { static_cast<AudioAsset*>(obj)->setLooping(dAtob(data)); return false; }
    static bool writeLooping(void* obj, StringTableEntry pFieldName)       { return static_cast<AudioAsset*>(obj)->getLooping() == true; }

    static bool setStreaming(void* obj, const char* data)                  { static_cast<AudioAsset*>(obj)->setStreaming(dAtob(data)); return false; }
    static bool writeStreaming(void* obj, StringTableEntry pFieldName)     { return static_cast<AudioAsset*>(obj)->getStreaming() == true; }

    static bool setMinDistance(void* obj, const char* data)                { static_cast<AudioAsset*>(obj)->setMinDistance(dAtof(data)); return false; }
    static bool writeMinDistance(void* obj, StringTableEntry pFieldName)   { return mNotEqual(static_cast<AudioAsset*>(obj)->getMinDistance(), 0.5f); }

    static bool setMaxDistance(void* obj, const char* data)                { static_cast<AudioAsset*>(obj)->setMaxDistance(dAtof(data)); return false; }
    static bool writeMaxDistance(void* obj, StringTableEntry pFieldName)   { return mNotEqual(static_cast<AudioAsset*>(obj)->getMaxDistance(), 1.0f); }

    static bool setInsideAngle(void* obj, const char* data)                { static_cast<AudioAsset*>(obj)->setInsideAngle(dAtof(data)); return false; }
    static bool writeInsideAngle(void* obj, StringTableEntry pFieldName)   { return mNotEqual(static_cast<AudioAsset*>(obj)->getInsideAngle(), 360.0f); }

    static bool setOutsideAngle(void* obj, const char* data)               { static_cast<AudioAsset*>(obj)->setOutsideAngle(dAtof(data)); return false; }
    static bool writeOutsideAngle(void* obj, StringTableEntry pFieldName)  { return mNotEqual(static_cast<AudioAsset*>(obj)->getOutsideAngle(), 360.0f); }

    static bool setOutsideVolume(void* obj, const char* data)              { static_cast<AudioAsset*>(obj)->setOutsideVolume(dAtof(data)); return false; }
    static bool writeOutsideVolume(void* obj, StringTableEntry pFieldName) { return mNotEqual(static_cast<AudioAsset*>(obj)->getOutsideVolume(), 1.0f); }
};

#endif  // _AUDIO_ASSET_H_
