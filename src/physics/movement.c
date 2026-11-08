#include <movement.h>
#include <collision.h>
#include <stdio.h>

void UpdateMovement(Player *player, PlayerInput input, Vector3 wishDir, float dt, Map *map) {
    bool onFloor = GroundCheck(player);
    bool onBox = CheckNearby(player, map, player->position, player->playerSize).grounded;

    // better groundcheck and groundcheck checks worlds floor
    if (onBox || onFloor){
        player->velocity.y = 0.0f;
        player->OnGround = true;
        player->canJump = true;
    } else {
        player->OnGround = false;
        player->canJump = false;
    }
    
    
    Gravity(player, dt);

    if (input.jump) {
        Jump(player);
    }

    // friction after jump
    Friction(player, input ,dt);

    // crouch
    UpdateCrouch(player, input.crouch, map);

    if (player->OnGround) {
        GroundMovement(player, wishDir, dt);
    } else {
        AirMovement(player, wishDir, dt);
    }

    //calc speed
    player->speed = sqrt((player->velocity.x * player->velocity.x) +
                        (player->velocity.z * player->velocity.z));


    Vector3 newPosition = player->position;
    newPosition.y += player->velocity.y * dt;
    newPosition.x += player->velocity.x * dt;
    newPosition.z += player->velocity.z * dt;

    CollisionResult result = CheckNearby(player, map, newPosition, player->playerSize);
    

    if (result.landed) { // landing on top
        player->velocity.y = 0.0f;
        player->position.y = result.groundHeight;
        player->OnGround = true;
    }
    else if (result.hit && result.blockedY && result.hitCeiling) { // Hit the underside
        player->velocity.y = 0.0f;
        player->position.y = result.ceilingHeight - player->playerSize.y;
    } else { // no collision
        player->position.y = newPosition.y;
    }

    // x collision
    Vector3 test_pos = {newPosition.x, player->position.y, player->position.z};
    result = CheckNearby(player, map, test_pos, player->playerSize);

    if (!result.blockedX) {
        player->position.x = test_pos.x;
    } else {
        player->velocity.x = 0.0f;
    }

    // Z collision
    test_pos = (Vector3){player->position.x, player->position.y, newPosition.z};
    result = CheckNearby(player, map, test_pos, player->playerSize);

    if (!result.blockedZ) {
        player->position.z = test_pos.z;
    } else {
        player->velocity.z = 0.0f;
    };

}

//get wish dir with camera yaw and inputs
Vector3 GetWishDir(PlayerInput input, float yaw) {
    Vector3 wishDir = { 0.0f };

    int inputVertical = input.forward - input.backward;
    int inputHorizontal = input.right - input.left;

    if (inputHorizontal == 0.0f && inputVertical == 0.0f) return wishDir;

    // up down
    Vector3 vertical = {
        cosf(yaw),
        0.0f,
        sinf(yaw)
    };

    // left right
    Vector3 horizontal = {
        -sinf(yaw),
        0.0f,
        cosf(yaw)
    };

    // combine inputs into wishdir
    Vector3 moveVertical = Vector3Scale(vertical, inputVertical);
    Vector3 moveHorizontal = Vector3Scale(horizontal, inputHorizontal);
    wishDir = Vector3Add(moveVertical, moveHorizontal);

    return Vector3Normalize(wishDir);
}

void GroundMovement(Player *player, Vector3 wishDir, float dt) {
    float currentspeed = Vector3DotProduct(player->velocity, wishDir);

    // how much more speed the player can add before the cap is reached
    float speedCap = player->crouching
        ? player->crouchSpeed
        : player->maxGroundSpeed;

    float remainingSpeed = speedCap - currentspeed;

    // if the cap is reached return
    if (remainingSpeed <= 0) {
        return;
    }


    float accelerationSpeed;

    if (player->crouching) {
        accelerationSpeed = player->crouchSpeed;
    } else {
        accelerationSpeed = player->maxGroundSpeed;
    }

    float speedToAdd = player->acceleration * accelerationSpeed * dt;

    if (speedToAdd > remainingSpeed) {
        speedToAdd = remainingSpeed;
    }

    player->velocity.x += speedToAdd * wishDir.x;
    player->velocity.z += speedToAdd * wishDir.z;
}

void AirMovement(Player *player, Vector3 wishDir, float dt) {

    float currentspeed = Vector3DotProduct(player->velocity, wishDir);

    float cappedWishSpeed = Clamp(player->wishSpeed, 0.0f, player->wishSpeedLimit);

    // how much more speed the player can add before the cap is reached
    float remainingSpeed = cappedWishSpeed - currentspeed;

    // if the cap is reached return
    if (remainingSpeed <= 0) {
        return;
    }

    // calculate this frames acceleration
    float speedToAddThisFrame = player->airAcceleration * player->wishSpeed * dt;
    if (speedToAddThisFrame > remainingSpeed) {
        speedToAddThisFrame = remainingSpeed;
    }


    player->velocity.x += speedToAddThisFrame * wishDir.x;
    player->velocity.z += speedToAddThisFrame * wishDir.z;
}

//simple groundcheck !!!fix later
bool GroundCheck(Player *player) {
    if (player->position.y <= 1) { player->OnGround = true;
                                    player->canJump = true;
                                    //snap the player back and prevemt velocity growing when on ground
                                    player->position.y = 1;
                                    player->velocity.y = 0;
                                    return true;
     } else { player->OnGround = false;
            player->canJump = false; 
            return false;}
}

void Gravity(Player *player, float dt) {
    if(!player->OnGround) {
        player->velocity.y += player->gravity * dt;
    }
}

void Friction(Player *player, PlayerInput input, float dt) {
    if (player->OnGround) {
        //get the current speed
        float speed = sqrtf(player->velocity.x * player->velocity.x + player->velocity.z * player->velocity.z);

        if (speed < 0.001f) {
            player->velocity.x = 0.0f;
            player->velocity.z = 0.0f;
            return;
        }

        float controlSpeed = fmaxf(speed, player->stopSpeed);

        // calculate the friction by dt and control speed
        float frictionAmount = controlSpeed * player->friction * dt;

        float remaining = speed - frictionAmount;

        // snap it back if it goes to - so the player isnt thrown backwards
        if (remaining < 0.0f) remaining = 0.0f;

        float scale = remaining / speed;
        player->velocity.x *= scale;
        player->velocity.z *= scale;
    }
}



void Jump(Player *player) {
    if(player->canJump) {
        player->canJump = false;
        player->OnGround = false;
        player->velocity.y = player->jumpForce;
    }
}

void UpdateCrouch(Player *player, bool crouchInput, Map *map)  {
    if(crouchInput){
        if(!player->crouching) {
            Crouch(player);
        }
    } else {
        if (player->crouching) {
            Vector3 testSize = player->playerSize;
            testSize.y = player->standingHeight;

            CollisionResult result = CheckNearby(player, map, player->position, testSize);

            if(result.hit) {
                player->crouching = true;
            } else {
                player->crouching = false;
                player->playerSize.y = player->standingHeight;
                player->maxGroundSpeed = player->standSpeed;
            }

        }
    }
}

void Crouch(Player *player) {
    player->crouching = true;
    player->playerSize.y = player->crouchHeight;
    player->maxGroundSpeed = player->crouchSpeed;
}