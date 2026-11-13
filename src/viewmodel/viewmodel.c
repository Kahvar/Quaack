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

// simplify viewmodelupdate
void ViewmodelUpdate(Viewmodel *viewmodel, float dt) {
    ModelAnimation anim = viewmodel->animations[viewmodel->animIndex];
    viewmodel->animFrame += dt * 34.0f; //speed

    if (viewmodel->animFrame >= anim.keyframeCount) {
        viewmodel->animFrame = 0;
        if (viewmodel->animIndex == 0) {          // shoot finished, back to idle
            viewmodel->animIndex = 1;
            anim = viewmodel->animations[1];
        }
    }
    UpdateModelAnimation(viewmodel->model, anim, (int)viewmodel->animFrame);
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