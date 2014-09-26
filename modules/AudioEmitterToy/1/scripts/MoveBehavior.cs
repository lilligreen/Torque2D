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

if (!isObject(MoveBehavior))
{
    %template = new BehaviorTemplate(MoveBehavior);
   
    %template.addBehaviorField(upKey, "Key to bind to acceleration", keybind, "keyboard up");
    %template.addBehaviorField(downKey, "Key to bind to deceleration", keybind, "keyboard down");
    %template.addBehaviorField(leftKey, "Key to bind to rotate left", keybind, "keyboard left");
    %template.addBehaviorField(rightKey, "Key to bind to rotate right", keybind, "keyboard right");
   
    %template.addBehaviorField(acceleration, "Forward acceleration", float, 30.0);
    %template.addBehaviorField(turnSpeed, "Velocity of turning", float, 150.0);
    %template.addBehaviorField(damping, "Amount to damp movement", float, 1.0);
}

//-----------------------------------------------------------------------------

function MoveBehavior::onBehaviorAdd(%this)
{
    if (!isObject(moveMap))
        return;
   
    %this.owner.setLinearDamping(%this.damping);
   
    moveMap.bindObj(getWord(%this.upKey, 0), getWord(%this.upKey, 1), "moveUp", %this);
    moveMap.bindObj(getWord(%this.downKey, 0), getWord(%this.downKey, 1), "moveDown", %this);
    moveMap.bindObj(getWord(%this.leftKey, 0), getWord(%this.leftKey, 1), "moveLeft", %this);
    moveMap.bindObj(getWord(%this.rightKey, 0), getWord(%this.rightKey, 1), "moveRight", %this);
   
    %this.up = 0;
    %this.down = 0;
    %this.left = 0;
    %this.right = 0;
}

//-----------------------------------------------------------------------------

function MoveBehavior::onBehaviorRemove(%this)
{
    if (!isObject(moveMap))
        return;

    moveMap.unbindObj(getWord(%this.upKey, 0), getWord(%this.upKey, 1), %this);
    moveMap.unbindObj(getWord(%this.downKey, 0), getWord(%this.downKey, 1), %this);
    moveMap.unbindObj(getWord(%this.leftKey, 0), getWord(%this.leftKey, 1), %this);
    moveMap.unbindObj(getWord(%this.rightKey, 0), getWord(%this.rightKey, 1), %this);

    %this.up = 0;
    %this.down = 0;
    %this.left = 0;
    %this.right = 0;
}

//-----------------------------------------------------------------------------

function MoveBehavior::onMoveUpDown(%this)
{
    %angle = %this.owner.getAngle() + 90;

    %this.owner.setLinearVelocityPolar(%angle, (%this.down - %this.up) * %this.acceleration);
}

//-----------------------------------------------------------------------------

function MoveBehavior::onMoveLeftRight(%this)
{
    %this.owner.setAngularVelocity((%this.left - %this.right) * %this.turnSpeed);
}

//-----------------------------------------------------------------------------

function MoveBehavior::moveUp(%this, %val)
{
    %this.up = %val;
      
    %this.onMoveUpDown();
}

//-----------------------------------------------------------------------------

function MoveBehavior::moveDown(%this, %val)
{
    %this.down = %val;
      
    %this.onMoveUpDown();
}

//-----------------------------------------------------------------------------

function MoveBehavior::moveLeft(%this, %val)
{
    %this.left = %val;
    %this.onMoveLeftRight();
}

//-----------------------------------------------------------------------------

function MoveBehavior::moveRight(%this, %val)
{
    %this.right = %val;
    %this.onMoveLeftRight();
}
