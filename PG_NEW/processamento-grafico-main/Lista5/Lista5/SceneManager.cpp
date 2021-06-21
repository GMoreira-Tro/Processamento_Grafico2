#include "SceneManager.h"

static bool resized;
static GLuint width, height;

void SceneManager::initialize(GLuint w, GLuint h, string windowName, string texturePath)
{
	width = w;
	height = h;

	initializeGraphics(windowName);
	setupScene(texturePath);
}

void SceneManager::initializeGraphics(string windowName)
{
	glfwInit();

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	addShader("../shaders/transformations.vs", "../shaders/transformations.fs");

	resized = true;
}

void SceneManager::addShader(string vFilename, string fFilename)
{
	shader = new Shader(vFilename.c_str(), fFilename.c_str());
}

void SceneManager::resize(GLFWwindow* currentWindow, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	glViewport(0, 0, width, height);
}


void SceneManager::checkEsc()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void SceneManager::render(Ponto3d backgroundColor)
{
	glClearColor(backgroundColor.x, backgroundColor.y,backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (resized)
	{
		setupCamera2D();
		resized = false;
	}

	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->update();
		sprites[i]->draw(sprites[i]->channel);
	}
}

void SceneManager::run(Ponto3d backgroundColor)
{
	while (!glfwWindowShouldClose(window))
	{
        glfwPollEvents();

		checkEsc();

		render(backgroundColor);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}

void SceneManager::setupScene(string texturePath)
{
	unsigned int texID = loadTexture(texturePath);

	printSprite(glm::vec3(133.33f, 500.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f),1);
	printSprite(glm::vec3(400, 500.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f),2);
	printSprite(glm::vec3(666.67f, 500.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f),3);

	printSprite(glm::vec3(133.33f, 300.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f), 4);
	printSprite(glm::vec3(400, 300.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f),5);
	printSprite(glm::vec3(666.67f, 300.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f),6);

	printSprite(glm::vec3(133.33f, 100.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f), 7);
	printSprite(glm::vec3(400, 100.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f), 8);
	printSprite(glm::vec3(666.67f, 100.0f, 0.0), glm::vec3(266.67f, 200.0f, 1.0f), 9);

	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->textureID = texID;
	}

	ortho2D[0] = 0.0f;
	ortho2D[1] = 800.0f;
	ortho2D[2] = 0.0f;
	ortho2D[3] = 600.0f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SceneManager::printSprite(glm::vec3 position, glm::vec3 scale, unsigned int channel)
{
	Sprite* sprite = new Sprite;
	sprite->position = position;
	sprite->scale = scale;
	sprite->setShader(shader);
	sprite->channel = channel;
	sprites.push_back(sprite);
}

void SceneManager::setupCamera2D()
{
	float zNear = -1.0, zFar = 1.0;

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);

	GLint projLoc = glGetUniformLocation(shader->ID, "projection");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	
	return texture1;
}