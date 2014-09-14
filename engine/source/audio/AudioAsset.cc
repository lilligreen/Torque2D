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
#include "AudioAsset.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

#ifndef _CONSOLETYPES_H_
#include "console/consoleTypes.h"
#endif

// Script bindings.
#include "AudioAsset_ScriptBinding.h"

//-----------------------------------------------------------------------------

ConsoleType(audioAssetPtr, TypeAudioAssetPtr, sizeof(AssetPtr<AudioAsset>), ASSET_ID_FIELD_PREFIX)

//-----------------------------------------------------------------------------

ConsoleGetType(TypeAudioAssetPtr)
{
    // Fetch asset Id.
    return (*((AssetPtr<AudioAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType(TypeAudioAssetPtr)
{
    // Was a single argument specified?
    if( argc == 1 )
    {
        // Yes, so fetch field value.
        const char* pFieldValue = argv[0];

        // Fetch asset pointer.
        AssetPtr<AudioAsset>* pAssetPtr = dynamic_cast<AssetPtr<AudioAsset>*>((AssetPtrBase*)(dptr));

        // Is the asset pointer the correct type?
        if ( pAssetPtr == NULL )
        {
            // No, so fail.
            Con::warnf( "(TypeAudioAssetPtr) - Failed to set asset Id '%d'.", pFieldValue );
            return;
        }

        // Set asset.
        pAssetPtr->setAssetId( pFieldValue );

        return;
    }

    // Warn.
    Con::warnf( "(TypeAudioAssetPtr) - Cannot set multiple args to a single asset." );
}

//--------------------------------------------------------------------------

IMPLEMENT_CONOBJECT(AudioAsset);

//--------------------------------------------------------------------------

AudioAsset::AudioAsset()
{
    mAudioFile          = StringTable->EmptyString;
    mVolume             = 1.0f;
    mIsLooping          = false;
    mIsStreaming        = false;
    mMinDistance        = 0.5f;
    mMaxDistance        = 1.0f;
    mInsideAngle        = 360.0f;
    mOutsideAngle       = 360.0f;
    mOutsideVolume      = 1.0f;
}

//--------------------------------------------------------------------------

void AudioAsset::initPersistFields()
{
    Parent::initPersistFields();

    addProtectedField("AudioFile", TypeAssetLooseFilePath, Offset(mAudioFile, AudioAsset), &setAudioFile, &getAudioFile, &defaultProtectedWriteFn, "" );
    addProtectedField("Volume", TypeF32, Offset(mVolume, AudioAsset), &setVolume, &defaultProtectedGetFn, &writeVolume, "");
    addProtectedField("Looping", TypeBool, Offset(mIsLooping, AudioAsset), &setLooping, &defaultProtectedGetFn, &writeLooping, "");
    addProtectedField("Streaming", TypeBool, Offset(mIsStreaming, AudioAsset), &setStreaming, &defaultProtectedGetFn, &writeStreaming, "");
    addProtectedField("MinDistance", TypeF32, Offset(mMinDistance, AudioAsset), &setMinDistance, &defaultProtectedGetFn, &writeMinDistance, "");
    addProtectedField("MaxDistance", TypeF32, Offset(mMaxDistance, AudioAsset), &setMaxDistance, &defaultProtectedGetFn, &writeMaxDistance, "");
    addProtectedField("InsideAngle", TypeF32, Offset(mInsideAngle, AudioAsset), &setInsideAngle, &defaultProtectedGetFn, &writeInsideAngle, "");
    addProtectedField("OutsideAngle", TypeF32, Offset(mOutsideAngle, AudioAsset), &setOutsideAngle, &defaultProtectedGetFn, &writeOutsideAngle, "");
    addProtectedField("OutsideVolume", TypeF32, Offset(mOutsideVolume, AudioAsset), &setOutsideVolume, &defaultProtectedGetFn, &writeOutsideVolume, "");
}

//------------------------------------------------------------------------------

void AudioAsset::copyTo(SimObject* object)
{
    // Call to parent.
    Parent::copyTo(object);

    // Cast to asset.
    AudioAsset* pAsset = static_cast<AudioAsset*>(object);

    // Sanity!
    AssertFatal(pAsset != NULL, "AudioAsset::copyTo() - Object is not the correct type.");

    // Copy state.
    pAsset->setAudioFile( getAudioFile() );
    pAsset->setVolume( getVolume() );
    pAsset->setLooping( getLooping() );
    pAsset->setStreaming( getStreaming() );
    pAsset->setMinDistance( getMinDistance() );
    pAsset->setMaxDistance( getMaxDistance() );
    pAsset->setInsideAngle( getInsideAngle() );
    pAsset->setOutsideAngle( getOutsideAngle() );
    pAsset->setOutsideVolume( getOutsideVolume() );
}

//--------------------------------------------------------------------------

void AudioAsset::initializeAsset(void)
{
    // Call parent.
    Parent::initializeAsset();

    // Ensure the audio-file is expanded.
    mAudioFile = expandAssetFilePath( mAudioFile );

    // Asset should never auto-unload.
    setAssetAutoUnload( false );
}

//--------------------------------------------------------------------------

void AudioAsset::setAudioFile(const char* pAudioFile)
{
    // Sanity!
    AssertFatal( pAudioFile != NULL, "Cannot use a NULL audio filename." );

    // Fetch audio filename.
    pAudioFile = StringTable->insert( pAudioFile );

    // Ignore no change,
    if ( pAudioFile == mAudioFile )
        return;

    // Update.
    mAudioFile = getOwned() ? expandAssetFilePath( pAudioFile ) : pAudioFile;

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setVolume(const F32 volume)
{
    // Ignore no change.
    if ( mIsEqual(volume, mVolume) )
        return;

    // Update.
    mVolume = mClampF(volume, 0.0f, 1.0f);

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setLooping(const bool looping)
{
    // Ignore no change.
    if ( looping == mIsLooping )
        return;

    // Update.
    mIsLooping = looping;

    // Refresh the asset.
    refreshAsset();
}


//--------------------------------------------------------------------------

void AudioAsset::setStreaming(const bool streaming)
{
    // Ignore no change.
    if ( streaming == mIsStreaming )
        return;

    // Update.
    mIsStreaming = streaming;

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setMinDistance(const F32 distance)
{
    // Ignore no change.
    if ( mIsEqual(distance, mMinDistance) )
        return;

    // Update.
    mMinDistance = mClampF(distance, 0.0f, 10000.0f);

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setMaxDistance(const F32 distance)
{
    // Ignore no change.
    if ( mIsEqual(distance, mMaxDistance) )
        return;

    // Update.
    mMaxDistance = mClampF(distance, 0.0f, 10000.0f);

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setInsideAngle(const F32 angle)
{
    // Ignore no change.
    if ( mIsEqual(angle, mInsideAngle) )
        return;

    // Update.
    mInsideAngle = mClampF(angle, 0.0f, 360.0f);

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setOutsideAngle(const F32 angle)
{
    // Ignore no change.
    if ( mIsEqual(angle, mOutsideAngle) )
        return;

    // Update.
    mOutsideAngle = mClampF(angle, 0.0f, 360.0f);

    // Refresh the asset.
    refreshAsset();
}

//--------------------------------------------------------------------------

void AudioAsset::setOutsideVolume(const F32 volume)
{
    // Ignore no change.
    if ( mIsEqual(volume, mOutsideVolume) )
        return;

    // Update.
    mOutsideVolume = mClampF(volume, 0.0f, 1.0f);

    // Refresh the asset.
    refreshAsset();
}

//-----------------------------------------------------------------------------

void AudioAsset::onTamlPreWrite(void)
{
    // Call parent.
    Parent::onTamlPreWrite();

    // Ensure the audio-file is collapsed.
    mAudioFile = collapseAssetFilePath(mAudioFile);
}

//-----------------------------------------------------------------------------

void AudioAsset::onTamlPostWrite(void)
{
    // Call parent.
    Parent::onTamlPostWrite();

    // Ensure the audio-file is expanded.
    mAudioFile = expandAssetFilePath(mAudioFile);
}
