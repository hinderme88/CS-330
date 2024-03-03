#pragma once
#include  "Mesh.h"

using namespace std;

class ShapeMaker
{
public:
	static void uBuildPlane(GLMesh& mesh);
	static void uBuildCone(GLMesh& mesh);
	static void uBuildCube(GLMesh& mesh);
	static void uBuildLightCube(GLMesh& mesh);
	static void uBuildCylinder(GLMesh& mesh);
	static void uBuildTorus(GLMesh& mesh);
	static void uCreateBuffers(GLMesh& mesh);
	static void uCreateLightBuffers(GLMesh& mesh);
};
