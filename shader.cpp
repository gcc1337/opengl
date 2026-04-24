#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vs_fd{};
	std::ifstream fs_fd{};
	std::string vertexShaderSource{};
	std::string fragmentShaderSource{};
	vs_fd.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fs_fd.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vs_fd.open(vertexPath);
		fs_fd.open(fragmentPath);

		vertexShaderSource = std::string(std::istreambuf_iterator<char>(vs_fd), std::istreambuf_iterator<char>());
		fragmentShaderSource = std::string(std::istreambuf_iterator<char>(fs_fd), std::istreambuf_iterator<char>());
			
		vs_fd.close();
		fs_fd.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vShaderCode = vertexShaderSource.c_str();
	const char* fShaderCode = fragmentShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		 
	int success;
	char infoLog[512];

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	// check for linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(Shader::ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}