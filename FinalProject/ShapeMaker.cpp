#include <vector>

#include "ShapeMaker.h"
#include "Mesh.h"

using namespace std;


/* Here is where we build the vertices for the individual shapes, and apply transformations */


void ShapeMaker::uBuildPlane(GLMesh& mesh)
{
    // Position and Color data
    mesh.v = {
        // Vertices               // normals          // texture
        -5.0f, -0.5f, -5.0f,    0.0f, -1.0f,  0.0f,   0.0f,  0.0f,
         5.0f, -0.5f, -5.0f,    0.0f, -1.0f,  0.0f,   1.0f,  0.0f,
         5.0f, -0.5f,  5.0f,    0.0f, -1.0f,  0.0f,   1.0f,  1.0f,

         5.0f, -0.5f,  5.0f,    0.0f, -1.0f,  0.0f,   1.0f,  1.0f,
        -5.0f, -0.5f,  5.0f,    0.0f, -1.0f,  0.0f,   0.0f,  1.0f,
        -5.0f, -0.5f, -5.0f,    0.0f, -1.0f,  0.0f,   0.0f,  0.0f,

    };

    uCreateBuffers(mesh);
}


void ShapeMaker::uBuildCone(GLMesh& mesh)
{
    // Declare height, length, radius, and number of sides
    GLfloat height = 2.0f;
    GLfloat l = 2.0f;
    GLfloat r = 0.5f;
    GLfloat s = 20.0f;

    // Determine the step between sectors using PI and number of sides
    constexpr float PI = 3.14f;
    const float sectorStep = 2.0f * PI / s;
    const float textStep = 0.5f / s;
    float textureXLoc = 0.0f;

    // Loop through the sides to create the triangles
    for (auto i = 1; i < s + 1; i++) {

        mesh.v.insert(mesh.v.end(), { 0.5f, 0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.5f, 0.25f });
        mesh.v.insert(mesh.v.end(), { 0.5f + r * cos(i * sectorStep), 0.5f + r * sin(i * sectorStep), 0.0f,     0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f,  1.0f, 0.5f + (r * cos((i)*sectorStep)), 0.25f + (0.25f * sin((i)*sectorStep)) });
        mesh.v.insert(mesh.v.end(), { 0.5f + (r * cos((i + 1) * sectorStep)), 0.5f + (r * sin((i + 1) * sectorStep)),0.0f,   0.5f + (r * cos((i + 1) * (sectorStep * 1.5f))), 1.0f,  1.0f, 0.5f + (r * cos((i + 1) * sectorStep)), 0.25f + (0.25f * sin((i + 1) * sectorStep)) });
        mesh.v.insert(mesh.v.end(), { 0.5f + (r * cos(i * sectorStep)) ,0.5f + (r * sin(i * sectorStep)) , 0.0f ,  0.5f + (r * cos(i * (sectorStep * 1.5f))), 1.0f,  1.0f, textureXLoc, 0.5f });
        mesh.v.insert(mesh.v.end(), { 0.5f + (r * cos((i + 1) * sectorStep)) ,0.5f + (r * sin((i + 1) * sectorStep)), 0.0f ,    0.5f + (r * cos((i + 1) * (sectorStep * 1.5f))), 1.0f,  1.0f, textureXLoc + textStep, 0.5f });
        mesh.v.insert(mesh.v.end(), { 0.5f , 0.5f , l ,  1.0f, 1.0f,  1.0f, textureXLoc + (textStep / 2), 1.0f }); // peak

        textureXLoc += textStep;

    }

    uCreateBuffers(mesh);
}

void ShapeMaker::uBuildCube(GLMesh& mesh)
{
    // Position and Color data
        mesh.v = {
            // Vertex Positions    // Normals
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.25f, 0.5f,
             0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f,  0.5f,
             0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f,  1.0f,

             0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.25f, 0.5f,
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.25f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f,  1.0f,

            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  0.25f, 0.5f,
             0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  0.25f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  0.5f,  1.0f,

             0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  0.25f, 0.5f,
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  0.5f,  1.0f,

            -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.75f, 0.5f,
            -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.75f, 1.0f,

            -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.5f,  1.0f,
            -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.75f, 1.0f,

             0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   1.0f,  0.5f,
             0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.75f, 1.0f,

             0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,   1.0f,  0.5f,
             0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.75f, 0.5f,
             0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.75f, 1.0f,

            -0.5f, -0.5f, -0.5f,   0.0f, -1.0, 0.0f,   0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,   0.0f, -1.0, 0.0f,   0.0f,  0.5f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0, 0.0f,   0.25f, 0.0f,

             0.5f, -0.5f,  0.5f,   0.0f, -1.0, 0.0f,   0.0f,  0.5f,
            -0.5f, -0.5f,  0.5f,   0.0f, -1.0, 0.0f,   0.25f, 0.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0, 0.0f,   0.25f, 0.5f,

            -0.5f,  0.5f, -0.5f,   0.0f, -1.0, 0.0f,   0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,   0.0f, -1.0, 0.0f,   0.0f,  0.5f,
             0.5f,  0.5f,  0.5f,   0.0f, -1.0, 0.0f,   0.25f, 0.0f,

             0.5f,  0.5f,  0.5f,   0.0f, -1.0, 0.0f,   0.0f,  0.5f,
            -0.5f,  0.5f,  0.5f,   0.0f, -1.0, 0.0f,   0.25f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, -1.0, 0.0f,   0.25f, 0.5f,

    };

    uCreateBuffers(mesh);

}

void ShapeMaker::uBuildLightCube(GLMesh& mesh)
{
  

    mesh.v = {
        //Positions          //Normals
           // --------------------------------------
           //Back Face          //Negative Z Normals
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

          //Front Face         //Positive Z Normals
         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
          0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

         //Left Face          //Negative X Normals
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        //Right Face         //Positive X Normals
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        //Bottom Face        //Negative Y Normals
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

       //Top Face           //Positive Y Normals
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    uCreateLightBuffers(mesh);
}

void ShapeMaker::uBuildCylinder(GLMesh& mesh)
{
    vector<float> c = { 1.0f, 1.0f, 1.0f, 1.0f };

    float r = mesh.radius; // 0.5
    float l = mesh.length;
    float s = mesh.number_of_sides; // 128
    float h = mesh.height; //4

    constexpr float PI = 3.14f;
    const float sectorStep = 2.0f * PI / s;

    vector<float> v;

    for (auto i = 1; i < s + 1; i++)
    {
        // triangle fan, bottom
        v.insert(v.end(), { 0.5f, 0.5f, 0.0f, 0.0, -1.0, 0.0, 0.5f, 0.125f });			// origin (0.5, 0.5) works best for textures
        v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,			// x
                                        0.5f + r * sin(i * sectorStep) ,			// y
                                        0.0f ,										// z
                                        0.0, -1.0, 0.0, 						// normals
                                        0.5f + (r * cos((i)*sectorStep)) ,		// texture x; adding the origin for proper alignment
                                        (0.125f + (0.125f * sin((i)*sectorStep))) });		// texture y


        v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
                                        0.5f + r * sin((i + 1) * sectorStep) ,
                                        0.0f ,
                                        0.0, -1.0, 0.0,  					// color data r g b a
                                        0.5f + (r * cos((i + 1) * sectorStep)) ,
                                        (0.125f + (0.125f * sin((i + 1) * sectorStep))) });


    }

    for (auto i = 1; i < s + 1; i++)
    {
        // triangle fan, top
        v.insert(v.end(), { 0.5f, 0.5f, l,  0.0, 1.0, 0.0, 0.5f, 0.875f });			// origin (0.5, 0.5) works best for textures
        v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
                                        0.5f + r * sin(i * sectorStep) ,
                                        l ,										// build this fan the 'l' value away from the other fan
                                        0.0, 1.0, 0.0, 					// color data r g b a
                                        0.5f + (r * cos((i)*sectorStep)) ,
                                        0.875f + (0.125f * sin((i)*sectorStep)) });
        v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
                                        0.5f + r * sin((i + 1) * sectorStep) ,
                                        l ,
                                        0.0, 1.0, 0.0,					           // color data r g b a
                                        0.5f + (r * cos((i + 1) * sectorStep)) ,
                                        0.875f + (0.125f * sin((i + 1) * sectorStep)) });
    }

    // since all side triangles have the same points as the fans above, the same calculations are used
    // to wrap the texture around the cylinder, the calculated points are used to determine which section of
    // the texture to clamp to the corresponding point.
    constexpr float x = 1.0f;
    float j = 1.0f / (s / x);	// for calculating texture location; change 'x' to increase or decrease how many times the texture wraps around the cylinder
    float k = 0.0f;				// for texture clamping

    // sides
    for (auto i = 1; i < s + 1; i++)
    {
        v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
                                        0.5f + r * sin(i * sectorStep) ,
                                        0.0f ,
                                        0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f, 0.0f,					// normals
                                        k ,
                                        0.25f });
        v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
                                        0.5f + r * sin(i * sectorStep) ,
                                        l ,
                                        0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f, 0.0f,				// normals
                                        k ,
                                        0.75f });
        v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
                                        0.5f + r * sin((i + 1) * sectorStep) ,
                                        l ,
                                        0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f, 0.0f, 				// normals
                                        k + j ,
                                        0.75f });

        v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
                                        0.5f + r * sin((i + 1) * sectorStep) ,
                                        l ,
                                        0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f, 0.0f, 				// normals
                                        k + j ,
                                        0.75f });
        v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
                                        0.5f + r * sin((i + 1) * sectorStep) ,
                                        0.0f ,
                                       0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f, 0.0f, 					// normals
                                        k + j ,
                                        0.25f });
        v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
                                        0.5f + r * sin(i * sectorStep) ,
                                        0.0f ,
                                        0.5f + r * cos(i * (sectorStep * 1.5f)), 0.0f, 0.0f, 					// normals
                                        k,
                                        0.25f });
        k += j;
    }
    mesh.v = v;

    uCreateBuffers(mesh);
}

void ShapeMaker::uBuildTorus(GLMesh& mesh)
{
    int _mainSegments = 30;
    int _tubeSegments = 30;
    float _mainRadius = 2.0f;
    float _tubeRadius = 1.5f;

    auto mainSegmentAngleStep = glm::radians(360.0f / float(_mainSegments));
    auto tubeSegmentAngleStep = glm::radians(360.0f / float(_tubeSegments));

    std::vector<glm::vec3> vertex_list;
    std::vector<std::vector<glm::vec3>> segments_list;
    std::vector<glm::vec3> normals_list;
    std::vector<glm::vec2> texture_coords;
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    glm::vec3 normal;
    glm::vec3 vertex;
    glm::vec2 text_coord;

    // generate the torus vertices
    auto currentMainSegmentAngle = 0.0f;
    for (auto i = 0; i < _mainSegments; i++)
    {
        // Calculate sine and cosine of main segment angle
        auto sinMainSegment = sin(currentMainSegmentAngle);
        auto cosMainSegment = cos(currentMainSegmentAngle);
        auto currentTubeSegmentAngle = 0.0f;
        std::vector<glm::vec3> segment_points;
        for (auto j = 0; j < _tubeSegments; j++)
        {
            // Calculate sine and cosine of tube segment angle
            auto sinTubeSegment = sin(currentTubeSegmentAngle);
            auto cosTubeSegment = cos(currentTubeSegmentAngle);

            // Calculate vertex position on the surface of torus
            auto surfacePosition = glm::vec3(
                (_mainRadius + _tubeRadius * cosTubeSegment) * cosMainSegment,
                (_mainRadius + _tubeRadius * cosTubeSegment) * sinMainSegment,
                _tubeRadius * sinTubeSegment);

            //vertex_list.push_back(surfacePosition);
            segment_points.push_back(surfacePosition);

            // Update current tube angle
            currentTubeSegmentAngle += tubeSegmentAngleStep;
        }
        segments_list.push_back(segment_points);
        segment_points.clear();

        // Update main segment angle
        currentMainSegmentAngle += mainSegmentAngleStep;
    }

    float horizontalStep = 1.0 / _mainSegments;
    float verticalStep = 1.0 / _tubeSegments;
    float u = 0.0;
    float v = 0.0;

    // connect the various segments together, forming triangles
    for (int i = 0; i < _mainSegments; i++)
    {
        for (int j = 0; j < _tubeSegments; j++)
        {
            if (((i + 1) < _mainSegments) && ((j + 1) < _tubeSegments))
            {
                vertex_list.push_back(segments_list[i][j]);
                normal = normalize(segments_list[i][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v));
                vertex_list.push_back(segments_list[i][j + 1]);
                normal = normalize(segments_list[i][j + 1] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v + verticalStep));
                vertex_list.push_back(segments_list[i + 1][j + 1]);
                normal = normalize(segments_list[i + 1][j + 1] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u + horizontalStep, v + verticalStep));
                vertex_list.push_back(segments_list[i][j]);
                normal = normalize(segments_list[i][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v));
                vertex_list.push_back(segments_list[i + 1][j]);
                normal = normalize(segments_list[i + 1][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u + horizontalStep, v));
                vertex_list.push_back(segments_list[i + 1][j + 1]);
                normal = normalize(segments_list[i + 1][j + 1] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u + horizontalStep, v - verticalStep));
                vertex_list.push_back(segments_list[i][j]);
                normal = normalize(segments_list[i][j] - center);
                normals_list.push_back(normal);
                texture_coords.push_back(glm::vec2(u, v));
            }
            else
            {
                if (((i + 1) == _mainSegments) && ((j + 1) == _tubeSegments))
                {
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i][0]);
                    normal = normalize(segments_list[i][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, 0));
                    vertex_list.push_back(segments_list[0][0]);
                    normal = normalize(segments_list[0][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[0][j]);
                    normal = normalize(segments_list[0][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v));
                    vertex_list.push_back(segments_list[0][0]);
                    normal = normalize(segments_list[0][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                }
                else if ((i + 1) == _mainSegments)
                {
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i][j + 1]);
                    normal = normalize(segments_list[i][j + 1] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v + verticalStep));
                    vertex_list.push_back(segments_list[0][j + 1]);
                    normal = normalize(segments_list[0][j + 1] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v + verticalStep));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[0][j]);
                    normal = normalize(segments_list[0][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v));
                    vertex_list.push_back(segments_list[0][j + 1]);
                    normal = normalize(segments_list[0][j + 1] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(0, v + verticalStep));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                }
                else if ((j + 1) == _tubeSegments)
                {
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i][0]);
                    normal = normalize(segments_list[i][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, 0));
                    vertex_list.push_back(segments_list[i + 1][0]);
                    normal = normalize(segments_list[i + 1][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u + horizontalStep, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                    vertex_list.push_back(segments_list[i + 1][j]);
                    normal = normalize(segments_list[i + 1][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u + horizontalStep, v));
                    vertex_list.push_back(segments_list[i + 1][0]);
                    normal = normalize(segments_list[i + 1][0] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u + horizontalStep, 0));
                    vertex_list.push_back(segments_list[i][j]);
                    normal = normalize(segments_list[i][j] - center);
                    normals_list.push_back(normal);
                    texture_coords.push_back(glm::vec2(u, v));
                }

            }
            v += verticalStep;
        }
        v = 0.0;
        u += horizontalStep;
    }

    std::vector<GLfloat> combined_values;

    // combine interleaved vertices, normals, and texture coords
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex = vertex_list[i];
        normal = normals_list[i];
        text_coord = texture_coords[i];
        combined_values.push_back(vertex.x);
        combined_values.push_back(vertex.y);
        combined_values.push_back(vertex.z);
        combined_values.push_back(normal.x);
        combined_values.push_back(normal.y);
        combined_values.push_back(normal.z);
        combined_values.push_back(text_coord.x);
        combined_values.push_back(text_coord.y);
    }

    mesh.v = combined_values;

    uCreateBuffers(mesh);
}


void ShapeMaker::uCreateBuffers(GLMesh& mesh)
{

    GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    // Generate VAO
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    // Create VBO
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, mesh.v.size() * sizeof(float), &mesh.v.front(), GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nVertices = mesh.v.size() / (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Space between each vertex coordinate
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(floatsPerVertex * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // begin transformations

    // scale
    mesh.scale = glm::scale(glm::vec3(mesh.t[0], mesh.t[1], mesh.t[2]));

    const glm::mat4 rot = glm::mat4(1.0f);

    // rotation
    mesh.xRotation = glm::rotate(rot, glm::radians(mesh.t[3]), glm::vec3(mesh.t[4], mesh.t[5], mesh.t[6]));
    mesh.yRotation = glm::rotate(rot, glm::radians(mesh.t[7]), glm::vec3(mesh.t[8], mesh.t[9], mesh.t[10]));
    mesh.zRotation = glm::rotate(rot, glm::radians(mesh.t[11]), glm::vec3(mesh.t[12], mesh.t[13], mesh.t[14]));

    // move the object
    mesh.translation = glm::translate(glm::vec3(mesh.t[15], mesh.t[16], mesh.t[17]));

    mesh.model = mesh.translation * mesh.xRotation * mesh.yRotation * mesh.zRotation * mesh.scale;

    mesh.gUVScale = glm::vec2(mesh.t[18], mesh.t[19]);
    if (mesh.gMultipleTex)
    {
        mesh.gUVScaleExtra = glm::vec2(mesh.t[20], mesh.t[21]);
    }
  

}

void ShapeMaker::uCreateLightBuffers(GLMesh& mesh)
{
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;

    // Generate VAO
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    // Create VBO
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, mesh.v.size() * sizeof(float), &mesh.v.front(), GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nVertices = mesh.v.size() / (floatsPerVertex + floatsPerNormal);

    // Space between each vertex coordinate
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    // begin transformations

    // scale
    mesh.scale = glm::scale(glm::vec3(mesh.t[0], mesh.t[1], mesh.t[2]));

    const glm::mat4 rot = glm::mat4(1.0f);

    // rotation
    mesh.xRotation = glm::rotate(rot, glm::radians(mesh.t[3]), glm::vec3(mesh.t[4], mesh.t[5], mesh.t[6]));
    mesh.yRotation = glm::rotate(rot, glm::radians(mesh.t[7]), glm::vec3(mesh.t[8], mesh.t[9], mesh.t[10]));
    mesh.zRotation = glm::rotate(rot, glm::radians(mesh.t[11]), glm::vec3(mesh.t[12], mesh.t[13], mesh.t[14]));

    // move the object
    mesh.translation = glm::translate(glm::vec3(mesh.t[15], mesh.t[16], mesh.t[17]));

    mesh.model = mesh.translation * mesh.xRotation * mesh.yRotation * mesh.zRotation * mesh.scale;

    mesh.gUVScale = glm::vec2(mesh.t[18], mesh.t[19]);
    if (mesh.gMultipleTex)
    {
        mesh.gUVScaleExtra = glm::vec2(mesh.t[20], mesh.t[21]);
    }


}


