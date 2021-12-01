#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexSource;
	std::string fragmentSource;

	// Read files
	getFileFrom(vertexFile, vertexSource);
	getFileFrom(fragmentFile, fragmentSource);


	// Make shader
	unsigned int vertexShader, fragmentShader;
	const char* vertexShaderCode = vertexSource.c_str();
	const char* fragmentShaderCode = fragmentSource.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderCode, 0);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, 0);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Check compile error
	int result;
	char errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR : Vertex Shader Compile Error!\n" << errorLog << std::endl;
		exit(100);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR : Fragment Shader Compile Error!\n" << errorLog << std::endl;
		exit(100);
	}

	m_iProgram = glCreateProgram();

	glAttachShader(m_iProgram, vertexShader);
	glAttachShader(m_iProgram, fragmentShader);
	glLinkProgram(m_iProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(m_iProgram);

	vertexSource.clear();
	fragmentSource.clear();

	std::cout << "Compile complete\n";
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_iProgram);
}

void ShaderProgram::getFileFrom(const char* fileName, std::string& target)
{
	std::ifstream fin(fileName);
	if (!fin) {
		std::cerr << "Can't Find \"" << fileName << "\" !!" << std::endl;
		exit(100);
	}

	fin.seekg(0, std::ios::end);			// ���� ���� �� ������ ��������
	int size = fin.tellg();					// ���� ��ġ�� ������ ������ ũ���� (������ ũ��)
	target.resize(size);					// ���� �� ũ�⸸ŭ ���Ҵ�
	fin.seekg(0, std::ios::beg);			// ���� ���� �� ������ �ٽ� ��������
	fin.read(&target[0], size);				// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.

	std::cout << "\tFile Name : " << fileName << "\n";

	fin.close();
}

unsigned int ShaderProgram::getProgram() const
{
	return m_iProgram;
}

void ShaderProgram::use()
{
	glUseProgram(m_iProgram);
}

void ShaderProgram::setMat4(const char* varName, glm::mat4 matrix)
{
	glUseProgram(m_iProgram);
	unsigned int mat4 = glGetUniformLocation(this->m_iProgram, varName);
	glUniformMatrix4fv(mat4, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setVec3(const char* varName, glm::vec3 vector)
{
	glUseProgram(m_iProgram);
	unsigned int vec3 = glGetUniformLocation(this->m_iProgram, varName);
	glUniform3fv(vec3, 1, glm::value_ptr(vector));
}
