#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "ShapeMaker.h"
#include "SceneMaker.h"
#include "Mesh.h"

#include "camera.h"
#include "VertexShaderSource.h"
#include "FragmentShaderSource.h"
#include "LightVertexShaderSource.h"
#include "LightFragmentShaderSource.h"
#include "SkyboxVertexShader.h"
#include "SkyboxFragmentShader.h"


/*Shader program Macro*/
//#ifndef GLSL
//#define GLSL(Version, Source) "#version " #Version " core \n" #Source
//#endif

using namespace std; // Standard namespace

    const char* const WINDOW_TITLE = "CS330 Final Project"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;

    struct GLightMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbo;     // Handles for the vertex buffer objects
        GLuint nIndices;    // Number of indices of the mesh
    };

    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    // Meshes
    SceneMaker maker;
    // Light cube mesh
    GLightMesh spotLightMesh;
    GLightMesh keyLightMesh;
    GLuint gProgramId;
    GLuint gLightProgramId;
    GLuint gSkyboxProgramId;

    vector<GLMesh> shapes;

    Camera gCamera(glm::vec3(-5.0f, 2.5f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 35.0f, -20.0f);
    float gLastX = WINDOW_WIDTH / 2.0f;
    float gLastY = WINDOW_HEIGHT / 2.0f;
    bool gFirstMouse = true;

    // timing
    float gDeltaTime = 0.0f;
    float gLastFrame = 0.0f;

    bool perspective = true;

    // Subject position and scale
    glm::vec3 gCubePosition(0.0f, 0.0f, 0.0f);
    glm::vec3 gCubeScale(2.0f);

    // Light color, position and scale
    glm::vec3 gAmbLightColor(1.0f, 0.75f, 1.0f);
    glm::vec3 gAmbLightPosition(0.7f, 3.0f, 8.0f);
    glm::vec3 gAmbLightScale(0.1f);

    // Light color, position and scale
    glm::vec3 gKeyLightColor(1.0f, 1.0f, 0.75f);
    glm::vec3 gKeyLightPosition(1.0f, 8.0f, 0.0f);
    glm::vec3 gKeyLightScale(0.5f);

  
/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
bool UCreateTexture(const char* filename, GLuint& textureId);
void URender(vector<GLMesh> shapes);
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);
void UDestroyMesh(GLMesh& mesh);
void UDestroyTexture(GLuint textureId);
void UCreateLightMesh(GLightMesh& lightMesh);
unsigned int UCreateCubeMap(vector<std::string> faces);

void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}

int main(int argc, char* argv[])
{
   if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    // Create the meshes
    SceneMaker::uMakeScene(shapes);

    if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramId))
        //cout << "Fail 2" << endl;	cin.get();
        return EXIT_FAILURE;

    if (!UCreateShaderProgram(skyBoxVertexShader, skyBoxFragmentShader, gSkyboxProgramId))
        return EXIT_FAILURE;


    // Generate textures for each shape
    for (auto& m : shapes)
    {
        if (m.gUseCubeMap)
        {
             m.faces = { 
               m.cubeMapFile1,
               m.cubeMapFile2,
               m.cubeMapFile3,
               m.cubeMapFile4,
               m.cubeMapFile5,
               m.cubeMapFile6,
             };
            
            glUseProgram(gSkyboxProgramId);
            // We set the texture as texture unit 0
            glUniform1i(glGetUniformLocation(gSkyboxProgramId, "skyBox"), 0);
            m.cubeMapTexture = UCreateCubeMap(m.faces);
           
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m.cubeMapTexture);
        }
        else 
        {
            // Set the shader to be used
            glUseProgram(gProgramId);

            if (!UCreateTexture(m.texFilename, m.textureId1))
            {
                cout << "Failed to load texture " << m.texFilename << endl;
                return EXIT_FAILURE;

            }
            if (m.gMultipleTex)
            {
                if (!UCreateTexture(m.texFilename2, m.textureId2))
                {
                    cout << "Failed to load texture " << m.texFilename2 << endl;
                    return EXIT_FAILURE;
                }
            }
            // We set the texture as texture unit 0
            glUniform1i(glGetUniformLocation(gProgramId, "uTextureBase"), 0);
            // We set the texture as texture unit 1
            glUniform1i(glGetUniformLocation(gProgramId, "uTextureExtra"), 1);
   
        }
       
     }
      
    if (!UCreateShaderProgram(LightVertexShaderSource, lightFragmentShaderSource, gLightProgramId))
        return EXIT_FAILURE;

    UCreateLightMesh(spotLightMesh);
    UCreateLightMesh(keyLightMesh);

 
    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // Sets the background color of the window to black (it will be implicitely used by glClear)
        glClearColor(0.49f, 0.858f, 0.227f, 1.0f);

        // per-frame timing
        // --------------------
        float currentFrame = glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // input
        // -----
        UProcessInput(gWindow);


        // Render this frame
        URender(shapes);

        glfwPollEvents();
    }

    // Release mesh data
    for (auto& m : shapes)
    {
        UDestroyMesh(m);
    }

    //UDestroyMesh(gLightCubeMesh);

    shapes.clear();

    // Release shader program
    UDestroyShaderProgram(gProgramId);
    UDestroyShaderProgram(gSkyboxProgramId);
    UDestroyShaderProgram(gLightProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers

        // ---------------------------------------

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))

        {

            std::cout << "Failed to initialize GLAD" << std::endl;

            return -1;

        }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.0f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        gCamera.ProcessKeyboard(UP, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        gCamera.ProcessKeyboard(DOWN, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        perspective = !perspective;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (gFirstMouse)
    {
        gLastX = xpos;
        gLastY = ypos;
        gFirstMouse = false;
    }

    float xoffset = xpos - gLastX;
    float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

    gLastX = xpos;
    gLastY = ypos;

    gCamera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    gCamera.ProcessMouseScroll(yoffset);
}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        if (action == GLFW_PRESS)
            cout << "Left mouse button pressed" << endl;
        else
            cout << "Left mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
    {
        if (action == GLFW_PRESS)
            cout << "Middle mouse button pressed" << endl;
        else
            cout << "Middle mouse button released" << endl;
    }
    break;

    case GLFW_MOUSE_BUTTON_RIGHT:
    {
        if (action == GLFW_PRESS)
            cout << "Right mouse button pressed" << endl;
        else
            cout << "Right mouse button released" << endl;
    }
    break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}

// Functioned called to render a frame
void URender(vector<GLMesh> shapes)
{   
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the frame and z buffers
    glClearColor(0.49f, 0.858f, 0.227f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Transforms the camera: move the camera back (z axis)
    glm::mat4 view = gCamera.GetViewMatrix();

    // Creates a perspective projection
    glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

    // Allows a switch between Perspective and Ortho
    if (perspective == true) {
        projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    }
    else {
        projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
    }
    // loop to render each shape
    for (auto i = 0; i < shapes.size(); ++i)
    {
        auto mesh = shapes[i];

       // Check to see if we are rendering a cubemap
        if (mesh.gUseCubeMap)
        {
                // Bind the cubemap texture
                glUseProgram(gSkyboxProgramId);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, mesh.cubeMapTexture);

                GLint modelLoc = glGetUniformLocation(gSkyboxProgramId, "model");
                GLint viewLoc = glGetUniformLocation(gSkyboxProgramId, "view");
                GLint projLoc = glGetUniformLocation(gSkyboxProgramId, "projection");

                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh.model));
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

                // Reference matrix uniforms from the shape shader program for the shape color, light color, light position, and camera position
                GLint objectColorLoc = glGetUniformLocation(gSkyboxProgramId, "objectColor");

                // Spotlight
                GLint lightColorLoc = glGetUniformLocation(gSkyboxProgramId, "lightColor");
                GLint lightPositionLoc = glGetUniformLocation(gSkyboxProgramId, "lightPos");

                // Key light
                GLint keyLightColorLoc = glGetUniformLocation(gSkyboxProgramId, "keyLightColor");
                GLint keyLightPositionLoc = glGetUniformLocation(gSkyboxProgramId, "keyLightPos");

                // Camera view
                GLint viewPositionLoc = glGetUniformLocation(gSkyboxProgramId, "viewPosition");

                // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
                glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);
                // Ambient Light
                glUniform3f(lightColorLoc, gAmbLightColor.r, gAmbLightColor.g, gAmbLightColor.b);
                glUniform3f(lightPositionLoc, gAmbLightPosition.x, gAmbLightPosition.y, gAmbLightPosition.z);

                // Key Light
                glUniform3f(keyLightColorLoc, gKeyLightColor.r, gKeyLightColor.g, gKeyLightColor.b);
                glUniform3f(keyLightPositionLoc, gKeyLightPosition.x, gKeyLightPosition.y, gKeyLightPosition.z);

                const glm::vec3 cameraPosition = gCamera.Position;
                glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
            
        }
        else
        {
            // Set the shader to be used
            glUseProgram(gProgramId);
            glDepthFunc(GL_LESS);
            GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
            glUniform2fv(UVScaleLoc, 1, glm::value_ptr(mesh.gUVScale));

            GLint UVScale2Loc = glGetUniformLocation(gProgramId, "uvScaleExtra");
            glUniform2fv(UVScale2Loc, 1, glm::value_ptr(mesh.gUVScaleExtra));

            GLuint multipleTexturesLoc = glGetUniformLocation(gProgramId, "multipleTextures");
            glUniform1i(multipleTexturesLoc, mesh.gMultipleTex);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh.textureId1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, mesh.textureId2);

            // Retrieves and passes transform matrices to the Shader program
            GLint modelLoc = glGetUniformLocation(gProgramId, "model");
            GLint viewLoc = glGetUniformLocation(gProgramId, "view");
            GLint projLoc = glGetUniformLocation(gProgramId, "projection");

            // Set up all uniforms
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh.model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

            // Reference matrix uniforms from the shape shader program for the shape color, light color, light position, and camera position
            GLint objectColorLoc = glGetUniformLocation(gProgramId, "objectColor");

            // Spotlight
            GLint lightColorLoc = glGetUniformLocation(gProgramId, "lightColor");
            GLint lightPositionLoc = glGetUniformLocation(gProgramId, "lightPosition");

            // Key light
            GLint keyLightColorLoc = glGetUniformLocation(gProgramId, "keyLightColor");
            GLint keyLightPositionLoc = glGetUniformLocation(gProgramId, "keyLightPos");

            // Camera view
            GLint viewPositionLoc = glGetUniformLocation(gProgramId, "viewPosition");


            // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
            //glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);
            // Ambient Light
            glUniform3f(lightColorLoc, gAmbLightColor.r, gAmbLightColor.g, gAmbLightColor.b);
            glUniform3f(lightPositionLoc, gAmbLightPosition.x, gAmbLightPosition.y, gAmbLightPosition.z);

            // Key Light
            glUniform3f(keyLightColorLoc, gKeyLightColor.r, gKeyLightColor.g, gKeyLightColor.b);
            glUniform3f(keyLightPositionLoc, gKeyLightPosition.x, gKeyLightPosition.y, gKeyLightPosition.z);

            const glm::vec3 cameraPosition = gCamera.Position;
            glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

        }
        
        // Activate the VBOs contained within the mesh's VAO
        glBindVertexArray(mesh.vao);
  
        //// Draws the triangles
        glDrawArrays(GL_TRIANGLES, 0, mesh.nVertices); 

        // deactivate vao's
        glBindVertexArray(0);
        glUseProgram(0);
       
    }

    // Set the shader to be used
    glUseProgram(gLightProgramId);
    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(spotLightMesh.vao);

    // Light location and Scale
    glm::mat4 model = glm::translate(gAmbLightPosition) * glm::scale(gAmbLightScale);

    // Matrix uniforms from the Light Shader program
    GLint modelLoc = glGetUniformLocation(gLightProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gLightProgramId, "view");
    GLint projLoc = glGetUniformLocation(gLightProgramId, "projection");

    // Matrix data
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Draw the light
    glDrawArrays(GL_TRIANGLES, 0, spotLightMesh.nIndices);

    // Draw the Key Light
    glUseProgram(gLightProgramId);
    glBindVertexArray(keyLightMesh.vao);

    // Light location and Scale
    model = glm::translate(gKeyLightPosition) * glm::scale(gKeyLightScale);

    // Matrix uniforms from the Light Shader program
    modelLoc = glGetUniformLocation(gLightProgramId, "model");
    viewLoc = glGetUniformLocation(gLightProgramId, "view");
    projLoc = glGetUniformLocation(gLightProgramId, "projection");

    // Matrix data
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

     //Draw the light
    glDrawArrays(GL_TRIANGLES, 0, keyLightMesh.nIndices);
  
    // deactivate vao's
    glBindVertexArray(0);
    glUseProgram(0);

    // swap front and back buffers
    glfwSwapBuffers(gWindow);

   }

void UCreateLightMesh(GLightMesh& lightMesh)
{
    // Position and Color data
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       //Front Face         //Positive Z Normal
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

      //Left Face          //Negative X Normal
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Right Face         //Positive X Normal
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     //Bottom Face        //Negative Y Normal
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    //Top Face           //Positive Y Normal
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    lightMesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &lightMesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(lightMesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &lightMesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, lightMesh.vbo); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


// clean-up methods
void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);
}

// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}

bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
   
    if (image)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
}

unsigned int UCreateCubeMap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
          
        } 
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
   
    return textureID;
}

void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}

void UDestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}
