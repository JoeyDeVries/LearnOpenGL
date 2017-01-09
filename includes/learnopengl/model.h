#pragma once

#include <GL/glew.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "shaderprogram.h"

#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/LogStream.hpp>

#include <sstream>
#include <vector>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

struct Vertex
{
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normals;
	// TexCoords
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
	aiString path;
};

class MeshModel {
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	/*  Functions  */
	// Constructor
	MeshModel() {}
	MeshModel(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		// Now that we have all the required data, set the vertex buffers and its attribute pointers.
		this->setupMesh();
	}

	~MeshModel()
	{
		vertices.clear();
		vertices.shrink_to_fit();

		indices.clear();
		indices.shrink_to_fit();

		textures.clear();
		textures.shrink_to_fit();
	}

	// Render the mesh
	void Draw(ShaderProgram shader)
	{
		// Bind appropriate textures
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		GLuint normalNr = 1;
        GLuint heightNr = 1;

		for (GLuint i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
											  // Retrieve texture number (the N in diffuse_textureN)
			std::stringstream ss;
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // Transfer GLuint to stream
			else if (name == "texture_specular")
				ss << specularNr++; // Transfer GLuint to stream
			else if(name == "texture_normal")
                 ss << normalNr++; // Transfer GLuint to stream
            else if(name == "texture_height")
            	 ss << heightNr++; // Transfer GLuint to stream
			number = ss.str();
			// Now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(shader.getProgram(), (name + number).c_str()), i);
			// And finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
		glUniform1f(glGetUniformLocation(shader.getProgram(), "material.shininess"), 16.0f);

		// Draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Always good practice to set everything back to defaults once configured.
		for (GLuint i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	void BoneBuffers(GLsizeiptr size, const GLvoid *data, GLenum usage)
	{
	}

private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;

	/*  Functions    */
	// Initializes all the buffer objects/arrays
	void setupMesh()
	{
		// Create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenBuffers(1, 0);

		glBindVertexArray(VAO);
		// Load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		// Set the vertex attribute pointers
		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normals));
		// Vertex Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}
};

class Model
{
public:
	Model() {}

	Model(std::string path)
	{
		loadModel(path);//, &test);
	}

	~Model()
	{
		if (m_vertices.size() > 0)
		{
			m_vertices.clear();
			m_vertices.shrink_to_fit();
		}

		if (m_indices.size() > 0)
		{
			m_indices.clear();
			m_indices.shrink_to_fit();
		}

		if (m_textures.size() > 0)
		{
			m_textures.clear();
			m_textures.shrink_to_fit();
		}

		if (meshes.size() > 0)
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
			{
				meshes[i].~MeshModel();
			}

			meshes.clear();
			meshes.shrink_to_fit();
		}
	}

	GLint TextureFromFile(const char* path, std::string directory)
	{
		//Generate texture ID and load texture data 
		std::string filename = std::string(path);
		filename = directory + '\\' + filename;
		error = filename + " is the path to the texture!";
		GLuint textureID;
		glGenTextures(1, &textureID);
		int width, height, channel;
		unsigned char* image = NULL;
		if (ends_with(filename, ".png") || ends_with(filename, ".jpg"))
		{
			image = SOIL_load_image(filename.c_str(), &width, &height, &channel, SOIL_LOAD_RGBA);
		}
		if (ends_with(filename, ".dds") || ends_with(filename, ".tga"))
		{
			image = SOIL_load_image(filename.c_str(), &width, &height, &channel, SOIL_LOAD_AUTO | SOIL_LOAD_RGBA);
		}
		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		SOIL_free_image_data(image);

		return textureID;
	}

	// Draws the model, and thus all its meshes
	void Draw(ShaderProgram shader)
	{
		for (GLuint i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw(shader);
		}
	}

	void DrawBoundingBox(glm::mat4 *view, glm::mat4 *projection, glm::mat4 *model)
	{
		glBegin(GL_LINES);

		//front
		glVertex3f(scene_min.x, scene_max.y, scene_max.z);
		glVertex3f(scene_max.x, scene_max.y, scene_max.z);

		glVertex3f(scene_min.x, scene_min.y, scene_max.z);
		glVertex3f(scene_min.x, scene_max.y, scene_max.z);

		glVertex3f(scene_max.x, scene_max.y, scene_max.z);
		glVertex3f(scene_max.x, scene_min.y, scene_max.z);

		glVertex3f(scene_max.x, scene_min.y, scene_max.z);
		glVertex3f(scene_min.x, scene_min.y, scene_max.z);

		//right
		glVertex3f(scene_max.x, scene_min.y, scene_max.z);
		glVertex3f(scene_max.x, scene_max.y, scene_max.z);

		glVertex3f(scene_max.x, scene_max.y, scene_max.z);
		glVertex3f(scene_max.x, scene_max.y, scene_min.z);

		glVertex3f(scene_max.x, scene_max.y, scene_min.z);
		glVertex3f(scene_max.x, scene_min.y, scene_min.z);

		glVertex3f(scene_max.x, scene_min.y, scene_min.z);
		glVertex3f(scene_max.x, scene_min.y, scene_max.z);

		//back
		glVertex3f(scene_min.x, scene_max.y, scene_min.z);
		glVertex3f(scene_max.x, scene_max.y, scene_min.z);

		glVertex3f(scene_min.x, scene_min.y, scene_min.z);
		glVertex3f(scene_min.x, scene_max.y, scene_min.z);

		glVertex3f(scene_max.x, scene_max.y, scene_min.z);
		glVertex3f(scene_max.x, scene_min.y, scene_min.z);

		glVertex3f(scene_max.x, scene_min.y, scene_min.z);
		glVertex3f(scene_min.x, scene_min.y, scene_min.z);

		//left
		glVertex3f(scene_min.x, scene_min.y, scene_max.z);
		glVertex3f(scene_min.x, scene_max.y, scene_max.z);

		glVertex3f(scene_min.x, scene_max.y, scene_max.z);
		glVertex3f(scene_min.x, scene_max.y, scene_min.z);

		glVertex3f(scene_min.x, scene_max.y, scene_min.z);
		glVertex3f(scene_min.x, scene_min.y, scene_min.z);

		glVertex3f(scene_min.x, scene_min.y, scene_min.z);
		glVertex3f(scene_min.x, scene_min.y, scene_max.z);

		//top
		glVertex3f(scene_max.x, scene_max.y, scene_max.z);
		glVertex3f(scene_max.x, scene_max.y, scene_min.z);

		glVertex3f(scene_min.x, scene_max.y, scene_min.z);
		glVertex3f(scene_max.x, scene_max.y, scene_min.z);

		glVertex3f(scene_min.x, scene_max.y, scene_max.z);
		glVertex3f(scene_min.x, scene_max.y, scene_min.z);

		glVertex3f(scene_min.x, scene_max.y, scene_max.z);
		glVertex3f(scene_max.x, scene_max.y, scene_max.z);

		//bottom
		glVertex3f(scene_max.x, scene_min.y, scene_max.z);
		glVertex3f(scene_max.x, scene_min.y, scene_min.z);

		glVertex3f(scene_min.x, scene_min.y, scene_min.z);
		glVertex3f(scene_max.x, scene_min.y, scene_min.z);

		glVertex3f(scene_min.x, scene_min.y, scene_max.z);
		glVertex3f(scene_min.x, scene_min.y, scene_min.z);

		glVertex3f(scene_min.x, scene_min.y, scene_max.z);
		glVertex3f(scene_max.x, scene_min.y, scene_max.z);

		glEnd();
	}

	std::string getError() { return error; }

	glm::vec3 getSceneMin() { return glm::vec3(scene_min.x, scene_min.y, scene_min.z); }
	glm::vec3 getSceneMax() { return glm::vec3(scene_max.x, scene_max.y, scene_max.z); }

	// Data to fill
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<Texture> m_textures;

	float vertices;

private:
	aiVector3D scene_min, scene_max;
	std::string error;

	std::vector<MeshModel> meshes;

	std::string directory;

	bool ends_with(std::string const & value, std::string const & ending)
	{
		if (ending.size() > value.size()) return false;
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

	// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(std::string path)//, Model *m)
	{
		// Read file via ASSIMP
		Assimp::Importer importer;
		const aiScene *m_scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);// | aiProcess_CalcTangentSpace);

																																 // Check for errors
		if (!m_scene || m_scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode) // if is Not Zero
		{
			//fatalError("ERROR::ASSIMP:: " + *importer.GetErrorString());
			return;
		}

		if (m_scene)
		{
			get_bounding_box(&scene_min, &scene_max, m_scene);
		}

		// Retrieve the directory path of the filepath
		directory = path.substr(0, path.find_last_of('\\'));

		// Process ASSIMP's root node recursively
		processNode(m_scene->mRootNode, m_scene);

		m_scene = nullptr;
		delete m_scene;
	}

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene)
	{
		// Process each mesh located at the current node
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));

			mesh = nullptr;
			delete mesh;

			afterProcessMesh();
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	void afterProcessMesh()
	{
		if (m_vertices.size() > 0)
		{
			m_vertices.clear();
			m_vertices.shrink_to_fit();
		}

		if (m_indices.size() > 0)
		{
			m_indices.clear();
			m_indices.shrink_to_fit();
		}

		if (m_textures.size() > 0)
		{
			m_textures.clear();
			m_textures.shrink_to_fit();
		}
	}

	MeshModel processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Walk through each of the mesh's vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
							  // Positions
			vector.x = -mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = -mesh->mVertices[i].z;
			vertex.Position = vector;

			// Normals
			if (mesh->mNormals != 0)
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normals = vector;
			}

			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			m_vertices.push_back(vertex);
		}

		vertices = mesh->mNumVertices;

		// Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// Retrieve all indices of the face and store them in the indices vector
			for (GLuint j = 0; j < face.mNumIndices; j++)
			{
				m_indices.push_back(face.mIndices[j]);
			}
		}

		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN

			// 1. Diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			m_textures.insert(m_textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. Specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			m_textures.insert(m_textures.end(), specularMaps.begin(), specularMaps.end());
            // 3. Normal maps
            std::vector<Texture> normalMaps = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            // 4. Height maps
            std::vector<Texture> heightMaps = this->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
			
			material = nullptr;
			delete material;
		}

		// Return a mesh object created from the extracted mesh data
		return MeshModel(m_vertices, m_indices, m_textures);
	}

	void get_bounding_box_for_node(const aiNode* nd, const aiScene* scene, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo)
	{
		aiMatrix4x4 prev;
		unsigned int n = 0, t;

		prev = *trafo;
		aiMultiplyMatrix4(trafo, &nd->mTransformation);

		for (; n < nd->mNumMeshes; ++n)
		{
			const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

			for (t = 0; t < mesh->mNumVertices; ++t)
			{
				aiVector3D tmp = mesh->mVertices[t];
				aiTransformVecByMatrix4(&tmp, trafo);

				min->x = aisgl_min(min->x, -tmp.x);
				min->y = aisgl_min(min->y, tmp.y);
				min->z = aisgl_min(min->z, -tmp.z);

				max->x = aisgl_max(max->x, -tmp.x);
				max->y = aisgl_max(max->y, tmp.y);
				max->z = aisgl_max(max->z, -tmp.z);
			}

			mesh = nullptr;
			delete mesh;
		}

		for (n = 0; n < nd->mNumChildren; ++n) {
			get_bounding_box_for_node(nd->mChildren[n], scene, min, max, trafo);
		}
		*trafo = prev;
	}

	void get_bounding_box(aiVector3D* min, aiVector3D* max, const aiScene* scene)
	{
		aiMatrix4x4 trafo;
		aiIdentityMatrix4(&trafo);

		min->x = min->y = min->z = 1e10f;
		max->x = max->y = max->z = -1e10f;
		get_bounding_box_for_node(scene->mRootNode, scene, min, max, &trafo);
	}

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
		}
		return textures;
	}
};