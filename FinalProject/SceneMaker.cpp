// This class will call off to individual functions to build each shape, 
// then add the meshes to the mesh array.

#include "SceneMaker.h"
#include "ShapeMaker.h"
#include "Mesh.h"

using namespace std;

void SceneMaker::uMakeScene(vector<GLMesh>& shapes)
{
    

    // Build the cone
    GLMesh gConeMesh;

    gConeMesh.t =
    {
        0.8f,  0.8f,  0.8f,           // scale x, y, z
      270.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        0.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        0.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
       0.6f, -0.75f,  7.4f,           // translate x, y, z
       1.0f,  1.0f,                    // Texture scale
       2.0f,  2.0f,                    // Texture scale 2
    };

    gConeMesh.gUseCubeMap = false;
    gConeMesh.gMultipleTex = true;
    gConeMesh.texFilename = "../CS330_FinalProject/Resources/ConeTexture.png";
    gConeMesh.texFilename2 = "../CS330_FinalProject/Resources/TireTreadTexture.png";
    ShapeMaker::uBuildCone(gConeMesh);
    shapes.push_back(gConeMesh);


    //// Build the bottom of the cone
    GLMesh gConeBottom;

    gConeBottom.t =
    {
        1.0f,  0.2f,  1.0f,          // scale x, y, z
        0.0f,  1.0f,  0.0f,  0.0f,   // x amount of rotation
        0.0f,  0.0f,  1.0f,  0.0f,   // y amount of rotation
        0.0f,  0.0f,  0.0f,  1.0f,   // z amount of rotation
        1.0f, -0.85f,  7.0f,          // translate x, y, z
        1.0f,  1.0f,                  // Texture scale 
    };

    gConeBottom.gUseCubeMap = false;
    gConeBottom.gMultipleTex = false;
    gConeBottom.texFilename = "../CS330_FinalProject/Resources/ConeTexture.png";
    ShapeMaker::uBuildCube(gConeBottom);
    shapes.push_back(gConeBottom);


    //Build the plane
    GLMesh gPlaneMesh;

    gPlaneMesh.t =
    {
        5.0f, 5.0f, 5.0f,         // scale x, y, z
        0.0f, 1.0f, 0.0f, 0.0f,   // x amount of rotation
        0.0f, 0.0f, 1.0f, 0.0f,   // y amount of rotation
        0.0f, 0.0f, 0.0f, 1.0f,   // z amount of rotation
        2.0f, 1.5f, 2.0f,         // translate x, y, z
        1.0f, 1.0f,               // Texture scale
    };

    gPlaneMesh.gUseCubeMap = false;
    gPlaneMesh.gMultipleTex = false;
    gPlaneMesh.texFilename = "../CS330_FinalProject/Resources/ArenaTexture.png";
    ShapeMaker::uBuildPlane(gPlaneMesh);
    shapes.push_back(gPlaneMesh);

    //Build the cylinders
    GLMesh gCylinderMesh;

    gCylinderMesh.t =
    {
        2.0f, 2.0f, 2.0f,         // scale x, y, z
        90.0f, 1.0f, 0.0f, 0.0f,   // x amount of rotation
        0.0f, 0.0f, 1.0f, 0.0f,   // y amount of rotation
        0.0f, 0.0f, 0.0f, 1.0f,   // z amount of rotation
        9.0f, 1.1f, -2.0f,         // translate x, y, z
        1.0f, 1.0f,               // Texture scale
    };

    gCylinderMesh.gUseCubeMap = false;
    gCylinderMesh.gMultipleTex = false;
    gCylinderMesh.texFilename = "../CS330_FinalProject/Resources/ShinyBluePlastic.png";
    gCylinderMesh.height = 4.0f;
    gCylinderMesh.radius = 0.5f;
    gCylinderMesh.length = 1.0f;
    gCylinderMesh.number_of_sides = 128.0f;
    ShapeMaker::uBuildCylinder(gCylinderMesh);
    shapes.push_back(gCylinderMesh);


    // Build Left Front tire
    GLMesh gLeftFrontTireMesh;

    gLeftFrontTireMesh.t =
    {
        0.3f,  0.3f,  0.3f,           // scale x, y, z
        180.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        90.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        90.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
        2.6f,  -0.1f,  2.0f,           // translate x, y, z
        1.0f,  1.0f,                    // Texture scale
        2.0f,  2.0f,                    // Texture scale 2
    };

    gLeftFrontTireMesh.gMultipleTex = false;
    gLeftFrontTireMesh.gUseCubeMap = false;
    gLeftFrontTireMesh.texFilename = "../CS330_FinalProject/Resources/RubberTireTex.png";
    ShapeMaker::uBuildTorus(gLeftFrontTireMesh);
    shapes.push_back(gLeftFrontTireMesh);


    // Build Right Front tire
    GLMesh gRightFrontTireMesh;

    gRightFrontTireMesh.t =
    {
        0.3f,  0.3f,  0.3f,           // scale x, y, z
        180.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        90.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        90.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
        5.3f,  -0.1f,  2.0f,           // translate x, y, z
        1.0f,  1.0f,                    // Texture scale
        2.0f,  2.0f,                    // Texture scale 2
    };

    gRightFrontTireMesh.gMultipleTex = false;
    gRightFrontTireMesh.gUseCubeMap = false;
    gRightFrontTireMesh.texFilename = "../CS330_FinalProject/Resources/RubberTireTex.png";
    ShapeMaker::uBuildTorus(gRightFrontTireMesh);
    shapes.push_back(gRightFrontTireMesh);


    // Build Left Rear tire
    GLMesh gLeftRearTireMesh;

    gLeftRearTireMesh.t =
    {
        0.3f,  0.3f,  0.3f,           // scale x, y, z
        180.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        90.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        90.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
        2.6f,  -0.1f,  5.2f,           // translate x, y, z
        1.0f,  1.0f,                    // Texture scale
        2.0f,  2.0f,                    // Texture scale 2
    };

    gLeftRearTireMesh.gMultipleTex = false;
    gLeftRearTireMesh.gUseCubeMap = false;
    gLeftRearTireMesh.texFilename = "../CS330_FinalProject/Resources/RubberTireTex.png";
    ShapeMaker::uBuildTorus(gLeftRearTireMesh);
    shapes.push_back(gLeftRearTireMesh);


    // Build Right Rear tire
    GLMesh gRightRearTireMesh;

    gRightRearTireMesh.t =
    {
        0.3f,  0.3f,  0.3f,           // scale x, y, z
        180.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        90.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        90.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
        5.3f,  -0.1f,  5.2f,           // translate x, y, z
        1.0f,  1.0f,                    // Texture scale
        2.0f,  2.0f,                    // Texture scale 2
    };

    gRightRearTireMesh.gMultipleTex = false;
    gRightRearTireMesh.gUseCubeMap = false;
    gRightRearTireMesh.texFilename = "../CS330_FinalProject/Resources/RubberTireTex.png";
    ShapeMaker::uBuildTorus(gRightRearTireMesh);
    shapes.push_back(gRightRearTireMesh);


    //// Build the front of the truck
    GLMesh gTruckFrontMesh;

    gTruckFrontMesh.t =
    {
        2.0f,  2.0f,  1.8f,           // scale x, y, z
      270.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        0.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        0.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
        4.0,   0.6f,  2.0f,           // translate x, y, z
        1.0f, 1.0f,
    };

    gTruckFrontMesh.gMultipleTex = false;
    gTruckFrontMesh.gUseCubeMap = true;
    gTruckFrontMesh.cubeMapFile1 = "../CS330_FinalProject/Resources/TruckFrontRi.png";
    gTruckFrontMesh.cubeMapFile2 = "../CS330_FinalProject/Resources/TruckFrontLe.png";
    gTruckFrontMesh.cubeMapFile3 = "../CS330_FinalProject/Resources/TruckFrontGrill.png";
    gTruckFrontMesh.cubeMapFile4 = "../CS330_FinalProject/Resources/ShinyGreenPlastic150.png";
    gTruckFrontMesh.cubeMapFile5 = "../CS330_FinalProject/Resources/TruckFrontHood.png";
    gTruckFrontMesh.cubeMapFile6 = "../CS330_FinalProject/Resources/MetalTexture150.png";
    ShapeMaker::uBuildCube(gTruckFrontMesh);
    shapes.push_back(gTruckFrontMesh);


    // Build the back of the truck
    GLMesh gTruckBackMesh;

    gTruckBackMesh.t =
    {
        1.9f,  3.5f,  3.0f,           // scale x, y, z
      270.0f,  1.0f,  0.0f,  0.0f,    // x amount of rotation
        0.0f,  0.0f,  1.0f,  0.0f,    // y amount of rotation
        0.0f,  0.0f,  0.0f,  1.0f,    // z amount of rotation
        4.0f,  0.9f,  4.5f,           // translate x, y, z
        1.0, 1.0f,
    };

    gTruckBackMesh.gMultipleTex = false;
    gTruckBackMesh.gUseCubeMap = true;
    gTruckBackMesh.cubeMapFile1 = "../CS330_FinalProject/Resources/TruckBackRight.png";
    gTruckBackMesh.cubeMapFile2 = "../CS330_FinalProject/Resources/TruckBackLeft.png";
    gTruckBackMesh.cubeMapFile3 = "../CS330_FinalProject/Resources/TruckWindshield.png";
    gTruckBackMesh.cubeMapFile4 = "../CS330_FinalProject/Resources/TruckBackFinal.png";
    gTruckBackMesh.cubeMapFile5 = "../CS330_FinalProject/Resources/TruckTop.png";
    gTruckBackMesh.cubeMapFile6 = "../CS330_FinalProject/Resources/MetalTexture150.png";
    ShapeMaker::uBuildCube(gTruckBackMesh);
    shapes.push_back(gTruckBackMesh);


};
