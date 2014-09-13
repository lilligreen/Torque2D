//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
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

//-----------------------------------------------------------------------------

ConsoleType( audioAssetPtr, TypeAudioAssetPtr, sizeof(AssetPtr<AudioAsset>), ASSET_ID_FIELD_PREFIX )

//-----------------------------------------------------------------------------

ConsoleGetType( TypeAudioAssetPtr )
{
    // Fetch asset Id.
    return (*((AssetPtr<AudioAsset>*)dptr)).getAssetId();
}

//-----------------------------------------------------------------------------

ConsoleSetType( TypeAudioAssetPtr )
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
   mAudioFile                        = StringTable->EmptyString;

}

//--------------------------------------------------------------------------

void AudioAsset::initPersistFields()
{
   Parent::initPersistFields();

   addProtectedField("AudioFile", TypeAssetLooseFilePath, Offset(mAudioFile, AudioAsset), &setAudioFile, &getAudioFile, &defaultProtectedWriteFn, "" );

   //addField("is3D",              TypeBool,    Offset(mDescription.mIs3D, AudioAsset));
   //addField("referenceDistance", TypeF32,     Offset(mDescription.mReferenceDistance, AudioAsset));
   //addField("maxDistance",       TypeF32,     Offset(mDescription.mMaxDistance, AudioAsset));
   //addField("coneInsideAngle",   TypeS32,     Offset(mDescription.mConeInsideAngle, AudioAsset));
   //addField("coneOutsideAngle",  TypeS32,     Offset(mDescription.mConeOutsideAngle, AudioAsset));
   //addField("coneOutsideVolume", TypeF32,     Offset(mDescription.mConeOutsideVolume, AudioAsset));
   //addField("coneVector",        TypePoint3F, Offset(mDescription.mConeVector, AudioAsset));
   //addField("environmentLevel",  TypeF32,     Offset(mDescription.mEnvironmentLevel, AudioAsset));
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
}

//--------------------------------------------------------------------------

void AudioAsset::initializeAsset( void )
{
    // Call parent.
    Parent::initializeAsset();

    // Ensure the audio-file is expanded.
    mAudioFile = expandAssetFilePath( mAudioFile );

    // Asset should never auto-unload.
    setAssetAutoUnload( false );
}

//--------------------------------------------------------------------------

void AudioAsset::setAudioFile( const char* pAudioFile )
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

void AudioAsset::setVolume( const F32 volume )
{

}

//--------------------------------------------------------------------------

void AudioAsset::setVolumeChannel( const S32 volumeChannel )
{

}

//--------------------------------------------------------------------------

void AudioAsset::setLooping( const bool looping )
{

}


//--------------------------------------------------------------------------

void AudioAsset::setStreaming( const bool streaming )
{

}

//-----------------------------------------------------------------------------

void AudioAsset::onTamlPreWrite( void )
{
    // Call parent.
    Parent::onTamlPreWrite();

    // Ensure the audio-file is collapsed.
    mAudioFile = collapseAssetFilePath( mAudioFile );
}

//-----------------------------------------------------------------------------

void AudioAsset::onTamlPostWrite( void )
{
    // Call parent.
    Parent::onTamlPostWrite();

    // Ensure the audio-file is expanded.
    mAudioFile = expandAssetFilePath( mAudioFile );
}


