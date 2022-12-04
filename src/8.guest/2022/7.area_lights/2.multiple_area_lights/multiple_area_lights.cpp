//
// Implementing Areal Lights with Linearly Transformed Cosines.
//
// Inspiration:
// https://advances.realtimerendering.com/s2016/s2016_ltc_rnd.pdf
// https://eheitzresearch.wordpress.com/415-2/

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
#include <functional>
#include <chrono>
#include <random>

// CUSTOM
#include "../ltc_matrix.hpp"
#include "../colors.hpp" // LOOK FOR DIFFERENT COLORS!

// FUNCTION PROTOTYPES
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement(GLfloat deltaTime);
unsigned int loadTexture(const char *path, bool gammaCorrection);
void renderQuad();
void renderCube();

// SETTINGS AND GLOBALS
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const glm::vec3 LIGHT_COLOR = Color::BurlyWood; // CHANGE AREA LIGHT COLOR HERE!
bool keys[1024]; // activated keys
const int NUM_AREA_LIGHTS = 16;
Shader* ltcShaderPtr;

// camera
Camera camera(glm::vec3(-0.224556, 10.4038, -18.9259), glm::vec3(0.0f, 1.0f, 0.0f), 89.3999, -34.3001);
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


struct VertexAL {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

struct AreaLight {
	glm::vec3 offset;
	float yRotation;

	glm::vec3 color;
	float intensity = 4.0f;
	bool twoSided = true;
};

AreaLight areaLights[NUM_AREA_LIGHTS];


//
// 2---3-5
// |  / /|
// | / / |
// |/ /  |
// 1-4---6
//
const GLfloat psize = 10.0f;
VertexAL planeVertices[6] = {
	{ {-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
	{ {-psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f} },
	{ { psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
	{ {-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
	{ { psize, 0.0f,  psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f} },
	{ { psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} }
};
VertexAL areaLightVertices[6] = {
	{ {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // 0 1 5 4
	{ {-8.0f, 2.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
	{ {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
	{ {-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
	{ {-8.0f, 0.4f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
	{ {-8.0f, 0.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }
};

GLuint planeVBO, planeVAO;
GLuint areaLightVBO, areaLightVAO;

void configureAreaLights()
{
	// CONFIGURE AREA LIGHTS
	std::uniform_real_distribution<GLfloat> random_floats(0.0f, 1.0f);
	typedef std::chrono::high_resolution_clock myclock;
	unsigned seed = myclock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::function<float(void)> fn =
		[&random_floats, &generator]{ return random_floats(generator); };
	for (int i = 0; i < NUM_AREA_LIGHTS; i++)
	{
		float x = fn(); x = (x > 0.5f) ? x : -x;
		float z = fn(); z = (z > 0.5f) ? z : -z;
		areaLights[i].offset = glm::vec3(x, 0.0f, z) * 8.f;
		areaLights[i].yRotation = fn() * glm::two_pi<float>();
		areaLights[i].color = glm::vec3(fn(), fn(), fn());
		// color
		// intensity
	}

	// SEND TO GPU
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

void configurePlane()
{
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
	ltcShaderPtr->use();
	ltcShaderPtr->setVec4("material.albedoRoughness", glm::vec4(color, roughness));
	glUseProgram(0);
}

void incrementLightIntensity(float step)
{
	static float intensity = 4.0f;
	intensity += step;
	intensity = glm::clamp(intensity, 0.0f, 10.0f);
	//std::cout << "intensity: " << intensity << '\n';
	ltcShaderPtr->use();
	ltcShaderPtr->setFloat("areaLight.intensity", intensity);
	glUseProgram(0);
}

void switchTwoSided(bool doSwitch)
{
	static bool twoSided = true;
	if (doSwitch) twoSided = !twoSided;
	//std::cout << "twoSided: " << std::boolalpha << twoSided << '\n';
	ltcShaderPtr->use();
	ltcShaderPtr->setFloat("areaLight.twoSided", twoSided);
	glUseProgram(0);
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
	    SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL: Multiple Area Lights", NULL, NULL);
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

    // LUT textures
    LTC_matrices mLTC;
    mLTC.mat1 = loadMTexture();
    mLTC.mat2 = loadLUTTexture();

    // SHADERS
    Shader shaderLTC("7.multi_area_light.vs", "7.multi_area_light.fs");
    ltcShaderPtr = &shaderLTC;
    Shader shaderLightPlane("7.light_plane.vs", "7.light_plane.fs");

    // TEXTURES
    unsigned int concreteTexture = loadTexture(
	    FileSystem::getPath("resources/textures/concreteTexture.png").c_str(), true);

    // 3D OBJECTS
	configurePlane();
	configureAreaLights();

    // SHADER CONFIGURATION
    shaderLTC.use();
    for (int i = 0; i < NUM_AREA_LIGHTS; i++)
	{
		glm::mat4 model(1.0f);
		model = glm::translate(model, areaLights[i].offset);
		model = glm::rotate(model, areaLights[i].yRotation, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 p0 = glm::vec3(model * glm::vec4(areaLightVertices[0].position, 1.0f));
		glm::vec3 p1 = glm::vec3(model * glm::vec4(areaLightVertices[1].position, 1.0f));
		glm::vec3 p2 = glm::vec3(model * glm::vec4(areaLightVertices[4].position, 1.0f));
		glm::vec3 p3 = glm::vec3(model * glm::vec4(areaLightVertices[5].position, 1.0f));

		std::string str_pos = "areaLights[" + std::to_string(i) + "].points";
		std::string str_col = "areaLights[" + std::to_string(i) + "].color";
		std::string str_int = "areaLights[" + std::to_string(i) + "].intensity";
		std::string str_two = "areaLights[" + std::to_string(i) + "].twoSided";
		shaderLTC.setVec3((str_pos + "[0]").c_str(), p0);
		shaderLTC.setVec3((str_pos + "[1]").c_str(), p1);
		shaderLTC.setVec3((str_pos + "[2]").c_str(), p2);
		shaderLTC.setVec3((str_pos + "[3]").c_str(), p3);
		shaderLTC.setVec3(str_col.c_str(), areaLights[i].color);
		shaderLTC.setFloat(str_int.c_str(), 2.0f);
		shaderLTC.setInt(str_two.c_str(), 1);
	}
	shaderLTC.setInt("numAreaLights", NUM_AREA_LIGHTS);
	shaderLTC.setInt("LTC1", 0);
	shaderLTC.setInt("LTC2", 1);
	shaderLTC.setInt("material.diffuse", 2);
	incrementRoughness(0.0f);
	//incrementLightIntensity(0.0f);
	//switchTwoSided(false);
	glUseProgram(0);

	shaderLightPlane.use();
	{
		glm::mat4 model(1.0f);
		shaderLightPlane.setMat4("model", model);
	}
	shaderLightPlane.setVec3("lightColor", LIGHT_COLOR);
	glUseProgram(0);

	// TIME MEASUREMENT
	GLuint timeQuery;
	glGenQueries(1, &timeQuery);

	GLuint64 totalQueryTimeNs = 0;
	GLuint64 numQueries = 0;


    // RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
		do_movement(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderLTC.use();
        glm::mat4 model(1.0f);
		glm::mat3 normalMatrix = glm::mat3(model);
		shaderLTC.setMat4("model", model);
		shaderLTC.setMat3("normalMatrix", normalMatrix);
		glm::mat4 view = camera.GetViewMatrix();
		shaderLTC.setMat4("view", view);
		glm::mat4 projection = glm::perspective(
			glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shaderLTC.setMat4("projection", projection);
		shaderLTC.setVec3("viewPosition", camera.Position);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mLTC.mat1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mLTC.mat2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, concreteTexture);

		// measure time
		glBeginQuery(GL_TIME_ELAPSED, timeQuery);
		renderPlane();
		glEndQuery(GL_TIME_ELAPSED);

		glUseProgram(0);

		// draw area light planes
		shaderLightPlane.use();
		shaderLightPlane.setMat4("view", view);
		shaderLightPlane.setMat4("projection", projection);
		float sinNowTime = glm::sin(currentFrame);
		for (int i = 0; i < NUM_AREA_LIGHTS; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, areaLights[i].offset);
			model = glm::rotate(model, areaLights[i].yRotation, glm::vec3(0.0f, 1.0f, 0.0f));
			shaderLightPlane.setMat4("model", model);
			shaderLightPlane.setVec3("lightColor", areaLights[i].color);
			renderAreaLight();
		}
		glUseProgram(0);

		// fetch timestamp
		GLuint64 elapsed = 0; // will be in nanoseconds
		glGetQueryObjectui64v(timeQuery, GL_QUERY_RESULT, &elapsed);
		numQueries++;
		totalQueryTimeNs += elapsed;

        glfwSwapBuffers(window);
    }

    // compute average frame time
	double measuredAverageNs = (double)totalQueryTimeNs / (double)numQueries;
	double measuredAverageMs = measuredAverageNs * 1.0e-6;
	std::cout << "Total average time(ms) = " << measuredAverageMs << '\n';

	glDeleteQueries(1, &timeQuery);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteVertexArrays(1, &areaLightVAO);
    glDeleteBuffers(1, &areaLightVBO);

    glfwTerminate();
    return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void do_movement(GLfloat deltaTime)
{
	float cameraSpeed = deltaTime * 3.0f;

    if(keys[GLFW_KEY_W]) {
        camera.ProcessKeyboard(FORWARD, cameraSpeed);
    }
    else if(keys[GLFW_KEY_S]) {
        camera.ProcessKeyboard(BACKWARD, cameraSpeed);
    }
    if(keys[GLFW_KEY_A]) {
        camera.ProcessKeyboard(LEFT, cameraSpeed);
    }
    else if(keys[GLFW_KEY_D]) {
        camera.ProcessKeyboard(RIGHT, cameraSpeed);
    }

    if (keys[GLFW_KEY_R]) {
	    if (keys[GLFW_KEY_LEFT_SHIFT]) incrementRoughness(0.01f);
	    else incrementRoughness(-0.01f);
    }

    // if (keys[GLFW_KEY_I]) {
	//     if (keys[GLFW_KEY_LEFT_SHIFT]) incrementLightIntensity(0.025f);
	//     else incrementLightIntensity(-0.025f);
    // }
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
        // case GLFW_KEY_B:
	    //     switchTwoSided(true);
	    //     break;
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
