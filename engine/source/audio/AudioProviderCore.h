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

#ifndef _AUDIO_PROVIDER_CORE_H_
#define _AUDIO_PROVIDER_CORE_H_

#ifndef _AUDIO_ASSET_H_
#include "audio/AudioAsset.h"
#endif

#ifndef _TICKABLE_H_
#include "platform/Tickable.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

#ifndef _FMOD_HPP
#include "fmod.hpp"
#endif

//-----------------------------------------------------------------------------

class AudioProviderCore :
    public virtual Tickable,
    public IFactoryObjectReset,
    protected AssetPtrCallback
{
protected:
    bool                                    mSelfTick;

    AssetPtr<AudioAsset>*                   mpAudioAsset;
    FMOD::Channel*                          mChannel;
    FMOD::Sound*                            mSound;

    bool                                    mAudioPlaying;
    bool                                    mAudioPaused;
    bool                                    mAudioFinished;
    bool                                    mAudioVirtual;

public:
    AudioProviderCore();
    virtual ~AudioProviderCore();

    void allocateAssets(AssetPtr<AudioAsset>* pAudioAssetPtr);
    inline void deallocateAssets(void) { mpAudioAsset = NULL; }

    virtual void copyTo(AudioProviderCore* pAudioProviderCore) const;

    /// Integration.
    virtual void update(const F32 elapsedTime);
    virtual void processTick();
    virtual void interpolateTick(F32 delta) {};
    virtual void advanceTime(F32 timeDelta) {};
    virtual void setProcessTicks(bool tick) { Tickable::setProcessTicks( mSelfTick ? tick : false ); }
    void updateAudio(const F32 elapsedTime);

    virtual bool setAudio(const char* pAudioAssetId);
    inline StringTableEntry getAudio(void) const { return mpAudioAsset->getAssetId(); }

    bool createSound(const AssetPtr<AudioAsset>& audioAsset);
    S32 playAudio(Vector2 position);
    inline void pauseAudio(const bool audioPaused) { mChannel->setPaused(audioPaused); mAudioPaused = audioPaused; }
    inline void stopAudio(void) { mChannel->stop(); mAudioFinished = true; mAudioPaused = false; }
    inline bool isAudioPaused(void) const { return mAudioPaused; }
    inline bool isAudioFinished(void) const { return mAudioFinished; };
    inline bool isAudioVirtual(void) const { return mAudioVirtual; };

    inline F32 getAudibility(void) { F32 volume; mChannel->getAudibility(&volume); return volume; }
    inline void setMute(const bool mute) { mChannel->setMute(mute); }
    inline bool getMute(void) { bool mute; mChannel->getMute(&mute); return mute; }
    inline void setVolume(F32 volume) { mChannel->setVolume(volume); }
    inline F32 getVolume(void) { F32 volume; mChannel->getVolume(&volume); return volume; };
    
    Vector2 getMinMaxDistance(void);

    void setAudioPosition(const Vector2& position);
    Vector2 getAudioPosition(void);

    void setConeOrientation(const F32 angle);
    F32 getConeOrientation(void);
    Vector2 getConeAngles(void);

    void clearAssets(void);

    virtual void resetState(void);

protected:
    virtual void onAudioEnd(void) {}
    virtual void onAssetRefreshed(AssetPtrBase* pAssetPtrBase);
};

#endif // _AUDIO_PROVIDER_CORE_H_
