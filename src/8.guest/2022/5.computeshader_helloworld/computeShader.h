#include <learnopengl/shader_m.h>


class ComputeShader : public Shader
{
	public:
		ComputeShader(const char* computePath)
		{
            // 1. retrieve the vertex/fragment source code from filePath
            std::string computeCode;
            std::ifstream cShaderFile;
            // ensure ifstream objects can throw exceptions:
            cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                // open files
                cShaderFile.open(computePath);

                std::stringstream cShaderStream;
                // read file's buffer contents into streams
                cShaderStream << cShaderFile.rdbuf();
                // close file handlers
                cShaderFile.close();
                // convert stream into string
                computeCode = cShaderStream.str();
            }
            catch (std::ifstream::failure& e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            }
            const char* cShaderCode = computeCode.c_str();
            // 2. compile shaders
            unsigned int compute;
            // compute shader
            compute = glCreateShader(GL_COMPUTE_SHADER);
            glShaderSource(compute, 1, &cShaderCode, NULL);
            glCompileShader(compute);
            checkCompileErrors(compute, "COMPUTE");
           
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, compute);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            // delete the shaders as they're linked into our program now and no longer necessery
            glDeleteShader(compute);

		}
};