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

function AudioEmitterToy::create(%this)
{
    // Execute scripts
    %fileSpec = "./scripts" @ "/*.cs";
    for (%file = findFirstFile(%fileSpec); %file !$= ""; %file = findNextFile(%fileSpec))
        exec(%file);

    // Setup keyboard bindings
    new ActionMap(moveMap);
    moveMap.push();

    // Create a container for all Taml objects
    new SimSet(GameObjects);
        
    // Load Objects
    %fileSpec = "./objects" @ "/*.taml";
    for (%file = findFirstFile(%fileSpec); %file !$= ""; %file = findNextFile(%fileSpec))
        GameObjects.add(TamlRead(%file));

    // Initialize the toy's settings.
    AudioEmitterToy.WorldTop = 35;
    AudioEmitterToy.WorldBottom = -110;
    AudioEmitterToy.WorldLeft = -50;
    AudioEmitterToy.WorldRight = 140;

    // Reset the toy.
    AudioEmitterToy.reset();
}

//-----------------------------------------------------------------------------

function AudioEmitterToy::destory(%this)
{
    // Stop all audio.
    audioStopAll();
}

//-----------------------------------------------------------------------------

function AudioEmitterToy::reset(%this)
{
    // Clear the scene.
    SandboxScene.clear();

    // Stop all audio.
    audioStopAll();

    // Limit the camera to the four sections of the desert
    SandboxWindow.setViewLimitOn( AudioEmitterToy.WorldLeft, AudioEmitterToy.WorldBottom, AudioEmitterToy.WorldRight, AudioEmitterToy.WorldTop );

    // Add all objects to the scene
    for (%i = 0; %i < GameObjects.getCount(); %i++)
        SandboxScene.add(GameObjects.getObject(%i));

    // Mount the player to the camera.
    SandboxWindow.mount(Player, "0 0", 0, true, false);

    // Turn on visual aid for emitters.
    SandboxScene.setDebugOn("audio");

    // Play sounds.
    $FireIndex = FireAudio.play();
    $BeeIndex = BeeAudio.play();
}

//-----------------------------------------------------------------------------

function AudioEmitterToy::onTouchDown(%this, %touchID, %worldPosition)
{
    Player.MoveTo(%worldPosition, 10);
}
