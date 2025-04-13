#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	llantaIzqSup = 0.0f;
	llantaDerSup = 0.0f;
	llantaIzqInf = 0.0f;
	llantaDerInf = 0.0f;
	traslacion = 0.0f;
	cofreAbre = 0.0f;
	cofreCierra = 0.0f;
	traslacionHeli = 0.0f;
	encederFarola = 1;
	apagarFarola = 0;
	avanza = 0;
	retrocede = 0;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la práctica", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
	// Asignar valores de la ventana y coordenadas

	//Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}


	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
	//Rotación cofre
	if (key == GLFW_KEY_F)
	{
		if (theWindow->cofreAbre < 30) {
			theWindow->cofreAbre += 1.5;
			theWindow->cofreCierra -= 1.5;
		}
	}
	if (key == GLFW_KEY_G)
	{
		if (theWindow->cofreCierra < 0) {
			theWindow->cofreCierra += 1.5;
			theWindow->cofreAbre -= 1.5;
		}
	}
	//Traslación coche
	if (key == GLFW_KEY_J)
	{
		theWindow->traslacion += 1.0;
		theWindow->avanza = 1;
		theWindow->retrocede = 0;

	}
	if (key == GLFW_KEY_K)
	{
		theWindow->traslacion -= 1.0;
		theWindow->retrocede = 1;
		theWindow->avanza = 0;
	}
	//Giro Llantas
	if (key == GLFW_KEY_O)
	{
		theWindow->llantaDerSup += 10.0;
		theWindow->llantaIzqSup += 10.0;
		theWindow->llantaIzqInf += 10.0;
		theWindow->llantaDerInf += 10.0;
	}
	if (key == GLFW_KEY_P)
	{
		theWindow->llantaDerSup -= 10.0;
		theWindow->llantaIzqSup -= 10.0;
		theWindow->llantaIzqInf -= 10.0;
		theWindow->llantaDerInf -= 10.0;
	}//Traslación coche
	if (key == GLFW_KEY_M)
	{
		theWindow->traslacionHeli += 1.0;
	}
	if (key == GLFW_KEY_N)
	{
		theWindow->traslacionHeli -= 1.0;
	}
	//Encender y Apagar Farola
	if (key == GLFW_KEY_T)
	{
		theWindow->encederFarola = 1;
		theWindow->apagarFarola = 0;
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow->apagarFarola = 1;
		theWindow->encederFarola = 0;
	}



	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
