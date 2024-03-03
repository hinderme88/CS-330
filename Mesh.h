#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

//#include "camera.h"
// general includes
#include <vector>
#include <string>


struct GLMesh
{
        GLuint vao;                  // Handle for the vertex array object
        GLuint vbo;                  // Holds 1 vertex buffer object
        GLuint nVertices;            // Number of indices of the mesh
        std::vector<float> v;        // Indices to draw
        std::vector<float> t;        // Transformations
      
        float height;
        float length;
        float radius;
        float innerRadius;
        float number_of_sides;

        // matrix objects
        glm::mat4 scale;
        glm::mat4 xRotation;
        glm::mat4 yRotation;
        glm::mat4 zRotation;
        glm::mat4 rotation;
        glm::mat4 translation;
        glm::mat4 model;
        glm::vec2 gUVScale;
        glm::vec2 gUVScaleExtra;

        // texture info
        const char* texFilename;
        const char* texFilename2;
        const char* cubeMapFile1;
        const char* cubeMapFile2;
        const char* cubeMapFile3;
        const char* cubeMapFile4;
        const char* cubeMapFile5;
        const char* cubeMapFile6;
        GLuint cubeMapTexture;
        GLuint textureId1;
        GLuint textureId2;
        bool gMultipleTex;
        bool gUseCubeMap;
        std::vector<std::string> faces;

        //GLint gTextWrapMode = GL_REPEAT;

        class Mesh
        {
        };
};
#endif

	


