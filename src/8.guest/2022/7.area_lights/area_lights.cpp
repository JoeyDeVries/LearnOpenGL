// GLAD, GLFW, STB-IMAGE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// LEARNOPENGL
#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

// STANDARD
#include <iostream>
#include <vector>

// CUSTOM
#include "ltc_matrix.hpp"

// FUNCTION PROTOTYPES
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path, bool gammaCorrection);
void renderQuad();
void renderCube();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool bloom = true;
float exposure = 1.0f;
int programChoice = 1;
float bloomFilterRadius = 0.005f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;



//
// 2---3-5
// |  / /|
// | / / |
// |/ /  |
// 1-4---6
//
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

const GLfloat size = 10.0f;
Vertex planeVertices[6] = {
	{ {-size, 0.0f, -size}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
	{ {-size, 0.0f,  size}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
	{ { size, 0.0f,  size}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
	{ {-size, 0.0f, -size}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
	{ { size, 0.0f,  size}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
	{ { size, 0.0f, -size}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} }
};
Vertex areaLightVertices[6] = {
	{ {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // 0 1 5 4
	{ {-8.0f, 2.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
	{ {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
	{ {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
	{ {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
	{ {-8.0f, 0.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }
};

GLuint planeVBO, planeVAO;
GLuint areaLightVBO, areaLightVAO;

void configureMockupData()
{
    // PLANE
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);

    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // AREA LIGHT
    glGenVertexArrays(1, &areaLightVAO);
    glBindVertexArray(areaLightVAO);

    glGenBuffers(1, &areaLightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, areaLightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(areaLightVertices), areaLightVertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glBindVertexArray(0);
}

void renderPlane()
{
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void renderAreaLight()
{
	glBindVertexArray(areaLightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}



struct LTC_matrices {
	GLuint mat1;
	GLuint mat2;
};

GLuint loadMTexture()
{
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64,
	             0, GL_RGBA, GL_FLOAT, LTC1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

GLuint loadLUTTexture()
{
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64,
	             0, GL_RGBA, GL_FLOAT, LTC2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}



void incrementRoughness(float step)
{
	static glm::vec3 color = Color::SlateGray;
	static float roughness = 0.5f;
	roughness += step;
	roughness = glm::clamp(roughness, 0.0f, 1.0f);
	//std::cout << "roughness: " << roughness << '\n';
	lightingShader->Activate();
	lightingShader->SetUniformVec4("material.albedoRoughness", glm::vec4(color, roughness));
	lightingShader->Deactivate();
}

void incrementLightIntensity(float step)
{
	static float intensity = 4.0f;
	intensity += step;
	intensity = glm::clamp(intensity, 0.0f, 10.0f);
	//std::cout << "intensity: " << intensity << '\n';
	lightingShader->Activate();
	lightingShader->SetUniformFloat("areaLight.intensity", intensity);
	lightingShader->Deactivate();
}

void switchTwoSided(bool doSwitch)
{
	static bool twoSided = true;
	if (doSwitch) twoSided = !twoSided;
	//std::cout << "twoSided: " << std::boolalpha << twoSided << '\n';
	lightingShader->Activate();
	lightingShader->SetUniformBool("areaLight.twoSided", twoSided);
	lightingShader->Deactivate();
}



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(
	    SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL: Area Lights", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader shaderLTC("7.area_light.vs", "7.area_light.fs");
    // Shader shaderLight("6.bloom.vs", "6.light_box.fs");
    // Shader shaderBlur("6.old_blur.vs", "6.old_blur.fs");
    // Shader shaderBloomFinal("6.bloom_final.vs", "6.bloom_final.fs");

    // load textures
    // -------------
    unsigned int concreteTexture = loadTexture(FileSystem::getPath("resources/textures/concreteTexture.jpg").c_str(), true);

    // shader configuration
    // --------------------
    shaderLTC.use();
    shaderLTC.setVec3("areaLight.points[0]", areaLightVertices[0].position);
    shaderLTC.setVec3("areaLight.points[1]", areaLightVertices[1].position);
	shaderLTC.setVec3("areaLight.points[2]", areaLightVertices[4].position);
	shaderLTC.setVec3("areaLight.points[3]", areaLightVertices[5].position);
	shaderLTC.setVec3("areaLight.color", Color::White);
	shaderLTC.setInt("LTC1", 0);
	shaderLTC.setInt("LTC2", 1);
	shaderLTC.setInt("material.diffuse", 2);
	incrementRoughness(0.0f);
	incrementLightIntensity(0.0f);
	switchTwoSided(false);
	glUseProgram(0);


    // shader.setInt("diffuseTexture", 0);
    // shaderBlur.use();
    // shaderBlur.setInt("image", 0);
    // shaderBloomFinal.use();
    // shaderBloomFinal.setInt("scene", 0);
    // shaderBloomFinal.setInt("bloomBlur", 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. render scene into floating point framebuffer
        // -----------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, woodTexture);
        // set lighting uniforms
        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
            shader.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
            shader.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
        }
        shader.setVec3("viewPos", camera.Position);
        // create one large cube that acts as the floor
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
        model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
        shader.setMat4("model", model);
        renderCube();
        // then create multiple cubes as the scenery
        glBindTexture(GL_TEXTURE_2D, containerTexture);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
        model = glm::scale(model, glm::vec3(0.5f));
        shader.setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
        model = glm::scale(model, glm::vec3(0.5f));
        shader.setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
        model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        shader.setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
        model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        model = glm::scale(model, glm::vec3(1.25));
        shader.setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
        model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
        shader.setMat4("model", model);
        renderCube();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
        model = glm::scale(model, glm::vec3(0.5f));
        shader.setMat4("model", model);
        renderCube();

        // finally show all the light sources as bright cubes
        shaderLight.use();
        shaderLight.setMat4("projection", projection);
        shaderLight.setMat4("view", view);

        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(lightPositions[i]));
            model = glm::scale(model, glm::vec3(0.25f));
            shaderLight.setMat4("model", model);
            shaderLight.setVec3("lightColor", lightColors[i]);
            renderCube();
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        if (programChoice < 1 || programChoice > 3) { programChoice = 1; }
        bloom = (programChoice == 1) ? false : true;
        bool horizontal = true;

        // 2.A) bloom is disabled
        // ----------------------
        if (programChoice == 1)
        {

        }

        // 2.B) blur bright fragments with two-pass Gaussian Blur
        // ------------------------------------------------------
        else if (programChoice == 2)
        {
	        bool first_iteration = true;
	        unsigned int amount = 10;
	        shaderBlur.use();
	        for (unsigned int i = 0; i < amount; i++)
	        {
		        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		        shaderBlur.setInt("horizontal", horizontal);
		        glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
		        renderQuad();
		        horizontal = !horizontal;
		        if (first_iteration)
			        first_iteration = false;
	        }
	        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        // 2.C) use unthresholded bloom with progressive downsample/upsampling
        // -------------------------------------------------------------------
        else if (programChoice == 3)
        {
	        bloomRenderer.RenderBloomTexture(colorBuffers[1], bloomFilterRadius);
        }

        // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
        // --------------------------------------------------------------------------------------------------------------------------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderBloomFinal.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
        glActiveTexture(GL_TEXTURE1);
        if (programChoice == 1) {
	        glBindTexture(GL_TEXTURE_2D, 0); // trick to bind invalid texture "0", we don't care either way!
        }
        if (programChoice == 2) {
	        glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
        }
        else if (programChoice == 3) {
	        glBindTexture(GL_TEXTURE_2D, bloomRenderer.BloomTexture());
        }
        shaderBloomFinal.setInt("programChoice", programChoice);
        shaderBloomFinal.setFloat("exposure", exposure);
        renderQuad();

        //std::cout << "bloom: " << (bloom ? "on" : "off") << "| exposure: " << exposure << std::endl;

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bloomRenderer.Destroy();
    glfwTerminate();
    return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void do_movement(GLfloat deltaTime)
{
    GLfloat cameraSpeed = 10.0f * deltaTime;

    if(keys[GLFW_KEY_W]) {
        cam->MoveForwards(cameraSpeed);
    }
    else if(keys[GLFW_KEY_S]) {
        cam->MoveBackwards(cameraSpeed);
    }
    if(keys[GLFW_KEY_A]) {
        cam->StrafeLeft(cameraSpeed);
    }
    else if(keys[GLFW_KEY_D]) {
        cam->StrafeRight(cameraSpeed);
    }

    if (keys[GLFW_KEY_Z]) {
	    if (keys[GLFW_KEY_LEFT_SHIFT]) cam->MoveDown(cameraSpeed);
	    else cam->MoveUp(cameraSpeed);
    }

    if (keys[GLFW_KEY_R]) {
	    if (keys[GLFW_KEY_LEFT_SHIFT]) incrementRoughness(0.01f);
	    else incrementRoughness(-0.01f);
    }

    if (keys[GLFW_KEY_I]) {
	    if (keys[GLFW_KEY_LEFT_SHIFT]) incrementLightIntensity(0.025f);
	    else incrementLightIntensity(-0.025f);
    }

    if (keys[GLFW_KEY_LEFT]) {
	    areaLightTranslate.z += 0.01f;
    }
    if (keys[GLFW_KEY_RIGHT]) {
	    areaLightTranslate.z -= 0.01f;
    }
    if (keys[GLFW_KEY_UP]) {
	    areaLightTranslate.y += 0.01f;
    }
    if (keys[GLFW_KEY_DOWN]) {
	    areaLightTranslate.y -= 0.01f;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    static unsigned short wireframe = 0;

    if(action == GLFW_PRESS)
    {
        switch(key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            return;
        case GLFW_KEY_L:
            screen_lock = !screen_lock;
            break;
        case GLFW_KEY_C:
	        lightingShader = new Shaders::ShaderWrapper(shadername, Shaders::SHADERS_VF);
	        recompileShader = true;
	        break;
        case GLFW_KEY_B:
	        switchTwoSided(true);
	        break;
        default:
            keys[key] = true;
            break;
        }
    }

    if(action == GLFW_RELEASE)
    {
        if(key == GLFW_KEY_SPACE) {
            switch(wireframe)
            {
            case 0:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                wireframe = 1;
                break;
            default:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                wireframe = 0;
                break;
            }
        }
        else {
            keys[key] = false;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path, bool gammaCorrection)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum internalFormat;
        GLenum dataFormat;
        if (nrComponents == 1)
        {
            internalFormat = dataFormat = GL_RED;
        }
        else if (nrComponents == 3)
        {
            internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
            dataFormat = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
            dataFormat = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
