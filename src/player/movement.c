#include <movement.h>

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

void UpdateMovement(Player *player, PlayerInput input, Vector3 wishDir, float dt) {
    Gravity(player, dt);
    GroundCheck(player);
    Friction(player, input ,dt);

    if (input.jump) {
        Jump(player, dt);
    }

    if (player->OnGround) {
        GroundMovement(player, wishDir, dt);
    } else {
        AirMovement(player, wishDir, dt);
    }
    
    //calc speed
    player->speed = sqrt((player->velocity.x * player->velocity.x) +
                        (player->velocity.z * player->velocity.z));


    player->position.x += player->velocity.x * dt;
    player->position.y += player->velocity.y * dt;
    player->position.z += player->velocity.z * dt;
}

void GroundMovement(Player *player, Vector3 wishDir, float dt) {
    float currentspeed = Vector3DotProduct(player->velocity, wishDir);

    // how much more speed the player can add before the cap is reached
    float remainingSpeed = player->maxGroundSpeed - currentspeed;

    // if the cap is reached return
    if (remainingSpeed <= 0) {
        return;
    }

    // calculate this frames acceleration
    float speedToAddThisFrame = player->acceleration * player->maxGroundSpeed * dt;
    if (speedToAddThisFrame > remainingSpeed) {
        speedToAddThisFrame = remainingSpeed;
    }


    player->velocity.x += speedToAddThisFrame * wishDir.x;
    player->velocity.z += speedToAddThisFrame * wishDir.z;
}

void AirMovement(Player *player, Vector3 wishDir, float dt) {

    float currentspeed = Vector3DotProduct(player->velocity, wishDir);

    // how much more speed the player can add before the cap is reached
    float remainingSpeed = player->wishSpeed - currentspeed;

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
void GroundCheck(Player *player) {
    if (player->position.y <= 0) { player->OnGround = true;
                                    player->canJump = true;
                                    //snap the player back and prevemt velocity growing when on ground
                                    player->position.y = 0;
                                    player->velocity.y = 0;
     } else { player->OnGround = false;
            player->canJump = false; }
}

void Gravity(Player *player, float dt) {
    if(!player->OnGround) {
        player->velocity.y += player->gravity * dt;
    }
}

void Friction(Player *player, PlayerInput input, float dt) {
    if (player->OnGround) {
        // calculate the friction by dt
        float frictionAmount = player->friction * dt;
        float remaining = 1.0f - frictionAmount;

        // snap it back if it goes to - so the player isnt thrown backwards
        if (remaining < 0.0f) remaining = 0.0f;
    
        player->velocity.x *= remaining;
        player->velocity.z *= remaining;
    }
}



void Jump(Player *player, float dt) {
    if(player->canJump) {
        player->velocity.y += player->jumpForce;
    }
}

//