#include <viewmodel.h>
#include <stdio.h>

Viewmodel ViewmodelInit() {
    Viewmodel viewmodel = {0};
    viewmodel.model = LoadModel("src/assets/viewmodel.glb");
    viewmodel.animations = LoadModelAnimations("src/assets/viewmodel.glb", &viewmodel.animCount);
    viewmodel.animIndex = 1; //init animation to IDLE

    if (&viewmodel.model == NULL) {
        printf("Error initializing hands");
        ViewmodelUnload(&viewmodel);
    }

    return viewmodel;
};

void ViewmodelUpdate(Viewmodel *viewmodel, float dt) {
    float animSpeed = dt * 34;

    //get the total frame count of idle
    int totalframes_idle = viewmodel->animations[1].keyframeCount;

    //get total fram count of hit
    int totalframes_hit = viewmodel->animations[0].keyframeCount;


    if(viewmodel->animIndex == 1) {
        viewmodel->animFrame += animSpeed;
        if (viewmodel->animFrame < totalframes_idle) {
            UpdateModelAnimation(viewmodel->model, viewmodel->animations[1], (int)viewmodel->animFrame); // display the frame using int
        } else {
            viewmodel->animFrame = 0;
            UpdateModelAnimation(viewmodel->model, viewmodel->animations[1], (int)viewmodel->animFrame);
        }
    } else {
        viewmodel->animFrame += animSpeed;
        if(viewmodel->animFrame < totalframes_hit) {
            UpdateModelAnimation(viewmodel->model, viewmodel->animations[0], (int)viewmodel->animFrame);
        } else {
            viewmodel->animFrame = 0;
            viewmodel->animIndex = 1; // go back to idle
        }
    }
}

void ViewmodelShoot(Viewmodel *viewmodel) {
    if (viewmodel->animIndex != 0) { // if not already shooting
        viewmodel->animIndex = 0; // set animation to hit
        viewmodel->animFrame = 0; // reset the frame to 0
    }
}


void ViewmodelUnload(Viewmodel *viewmodel) {
    UnloadModel(viewmodel->model);
    UnloadModelAnimations(viewmodel->animations, viewmodel->animCount);
}