/* -------------------------------------------------
 * Using this tutorial:
 * https://www.youtube.com/watch?v=brAaoNhK4Mk
 *
 * -------------------------------------------------
 */

#include <irrlicht.h>
#include <stdio.h>
#include <cstdlib>
#include "ltpmessage.h"
#include "ltpclass.h"
#include <iostream>
#include <vector>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


LtpClass ltp1;

void ConvertToXYZ(double *x_pos, double *y_pos, struct LtpSample *ltp_sample)
{
    double theta = ((double)ltp_sample->angle_)/4000*360/180*3.14159;
    *x_pos = ltp_sample->distance_ * cos(theta);
    *y_pos = ltp_sample->distance_ * sin(theta);
}

int main(int argc, char *argv[])
{
    ltp1.Init("/dev/ttyUSB0", (3.1415192/2));
    LtpHitXyz hitpos;
    int arrayLength = 30;
    // this is kinda like a window, but it's more than that, its how I wanna render
    // my content
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                          dimension2d<u32>(1600, 800), 16, false, false, false, 0);

    if (!device)
    {
        return EXIT_FAILURE;
    }

    // Create our window
    device->setWindowCaption(L"Cooool!!!");

    // Create our video driver and scene manager
    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();

    // Lights!
    ILightSceneNode* light1 = smgr->addLightSceneNode(0, core::vector3df(0,400,-200),
            video::SColorf(0.3f,0.3f,0.3f), 1.0f,1);

    ISceneNode* cube = smgr->addCubeSceneNode();
    if(!cube)
    {
        device->drop();
        return EXIT_FAILURE;
    }


    // this makes the node visible
    cube->setMaterialFlag(EMF_LIGHTING, false);

    ISceneNode **cubes = new ISceneNode*[arrayLength];
    for(int i = 0; i < arrayLength; i++)
    {
        cubes[i] = smgr->addCubeSceneNode();
        if(!cubes[i])
        {
            device->drop();
            return EXIT_FAILURE;
        }

        cubes[i]->setMaterialFlag(EMF_LIGHTING, true);
        cubes[i]->setScale(vector3df(1,10,1));
        cubes[i]->getMaterial(0).Shininess = 20.0f;
    }



    IAnimatedMesh *terrain_model = smgr->addHillPlaneMesh("groundPlane", // Name of the scenenode
                                   core::dimension2d<f32>(50.0f, 50.0f), // Tile size
                                   core::dimension2d<u32>(80, 80), // Tile count
                                   0, // Material
                                   0.0f, // Hill height
                                   core::dimension2d<f32>(0.0f, 0.0f), // countHills
                                   core::dimension2d<f32>(80.0f, 80.0f)); // textureRepeatCount

    IAnimatedMeshSceneNode* terrain_node = smgr->addAnimatedMeshSceneNode(terrain_model);
    terrain_node->setMaterialTexture(0, driver->getTexture(
                                         "../assets/floor.jpg"));
    terrain_node->setMaterialFlag(EMF_LIGHTING, false);
    terrain_node->setPosition(core::vector3df(0,-100,0));
    
    smgr->addCameraSceneNode(0, 
            core::vector3df(0, 500, 0), // Look from
            core::vector3df(0, 0, 0)	  // Look to
            );						  // Camera ID

    smgr->addCameraSceneNodeFPS();

    core::vector3df new_pos;
    core::vector3df old_pos;

    std::vector<core::vector3df> posVector;

    // Create a game loop
    while (device->run())
    {
        if(ltp1.PollRead(&hitpos)) {
            //std::cout<<"x pos: " << hitpos.hitpos_x
            //         << " y pos: " << hitpos.hitpos_y
            //         << " z pos: " << hitpos.hitpos_z
            //         << std::endl;

            cube->setPosition(core::vector3df(
                                  hitpos.hitpos_y*-100,
                                  hitpos.hitpos_z*100,
                                  hitpos.hitpos_x*100));
            new_pos.X = hitpos.hitpos_y*-100;
            new_pos.Y = hitpos.hitpos_z*100;
            new_pos.Z = hitpos.hitpos_x*100;
            old_pos = new_pos;

            // add the new pos
            posVector.push_back(new_pos);
            int vectorSize = posVector.size(); 
            if(vectorSize >= arrayLength)
            {
                posVector.erase(posVector.begin());
            }
            
            for(int i = 0; i < posVector.size(); i++)
            {
                cubes[i]->setPosition(posVector.at(i));
            }
        }



        std::cout.flush();
        driver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, video::SColor(255,100,100,100));
        driver->draw3DLine(new_pos, old_pos);
        smgr->drawAll();
        driver->endScene();

    }

    device->drop();

    return EXIT_SUCCESS;
}

