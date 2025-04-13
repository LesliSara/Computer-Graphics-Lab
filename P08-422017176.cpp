/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture dadoTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;

Model Carro_M;
Model Cofre_M;
Model LlantaDerecha_M; //Es el mismo modelo para ambas llantas derechas
Model LlantaIzquierda_M; //Es el mismo modelo para ambas llantas izquierdas
Model Farola_M;
Model Penny_M;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];//Primer arreglo de luces puntuales, 4 luces en max_point_lights
//La variable puede ser un valor estático de 4 luces porque lo dice

SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[4];


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}




void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		1.0f, -1.0f, -1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		1.0f, -1.0f, -1.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		1.0f, -1.0f, -1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		1.0f, -1.0f, -1.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		1.0f, -1.0f, -1.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		1.0f, -1.0f, -1.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		1.0f, -1.0f, -1.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		1.0f, -1.0f, -1.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CrearDado()
{
	unsigned int cubo_indices[] = {
		//top pyramid
		0, 1, 2, //front
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		//bottom pyramid
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,

	};

	GLfloat cubo_vertices[] = {
		//x			y			z			S		T			NX		NY		NZ
		//top front
		-0.5f,		0.0f,		0.5f,		0.01f,   0.51f,		0.0f,	-1.0f,	-1.0f,	//0
		0.5f,		0.0f,		0.5f,		0.19f,	0.51f,		0.0f,	-1.0f,	-1.0f,	//1
		0.0f,		0.65f,		0.0f,		0.10f,	0.99f,		0.0f,	-1.0f,	-1.0f,	//2
		//top back
		-0.5f,		0.0f,		-0.5f,		0.59f,   0.51f,		0.0f,	-1.0f,	1.0f,	//3
		0.5f,		0.0f,		-0.5f,		0.41f,	0.51f,		0.0f,	-1.0f,	1.0f,	//4
		0.0f,		0.65f,		0.0f,		0.50f,	0.99f,		0.0f,	-1.0f,	1.0f,	//5
		//top right
		0.5f,		0.0f,		0.5f,		0.21f,   0.51f,		-1.0f,	-1.0f,	0.0f,	//6
		0.5f,		0.0f,		-0.5f,		0.39f,	0.51f,		-1.0f,	-1.0f,	0.0f,	//7
		0.0f,		0.65f,		0.0f,		0.30f,	0.99f,		-1.0f,	-1.0f,	0.0f,	//8
		//top left
		-0.5f,		0.0f,		0.5f,		0.79f,   0.51f,		1.0f,	-1.0f,	0.0f,	//9
		-0.5f,		0.0f,		-0.5f,		0.61f,	0.51f,		1.0f,	-1.0f,	0.0f,	//10
		0.0f,		0.65f,		0.0f,		0.70f,	0.99f,		1.0f,	-1.0f,	0.0f,	//11


		//bottom front
		-0.5f,		0.0f,		0.5f,		0.50f,   0.01f,		0.0f,	1.0f,	-1.0f,	//12
		0.5f,		0.0f,		0.5f,		0.41f,	0.49f,		0.0f,	1.0f,	-1.0f,	//13
		0.0f,		-0.65f,		0.0f,		0.59f,	0.49f,		0.0f,	1.0f,	-1.0f,	//14
		//bottom back		
		-0.5f,		0.0f,		-0.5f,		0.01f,   0.49f,		0.0f,	1.0f,	1.0f,	//15
		0.5f,		0.0f,		-0.5f,		0.10f,	0.01f,		0.0f,	1.0f,	1.0f,	//16
		0.0f,		-0.65f,		0.0f,		0.19f,	0.49f,		0.0f,	1.0f,	1.0f,	//17
		//bottom right		
		0.5f,		0.0f,		0.5f,		0.99f,   0.51f,		-1.0f,	1.0f,	0.0f,	//18
		0.5f,		0.0f,		-0.5f,		0.81f,	0.51f,		-1.0f,	1.0f,	0.0f,	//19
		0.0f,		-0.65f,		0.0f,		0.90f,	0.99f,		-1.0f,	1.0f,	0.0f,	//20
		//bottom left		
		-0.5f,		0.0f,		0.5f,		0.21f,   0.49f,		1.0f,	1.0f,	0.0f,	//21
		-0.5f,		0.0f,		-0.5f,		0.30f,	0.01f,		1.0f,	1.0f,	0.0f,	//22
		0.0f,		-0.65f,		0.0f,		0.39f,	0.49f,		1.0f,	1.0f,	0.0f,	//23


	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 24);
	meshList.push_back(dado);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDado();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	dadoTexture = Texture("Textures/textura_dado.jpg");
	dadoTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	Carro_M = Model();
	Carro_M.LoadModel("Models/Cuerpo_Carro.obj");
	Cofre_M = Model();
	Cofre_M.LoadModel("Models/Cofre_Carro.obj");
	LlantaDerecha_M = Model();
	LlantaDerecha_M.LoadModel("Models/Llanta_Derecha.obj");
	LlantaIzquierda_M = Model();
	LlantaIzquierda_M.LoadModel("Models/Llanta_Izquierda.obj");
	Farola_M = Model();
	Farola_M.LoadModel("Models/Farola.obj");
	Penny_M = Model();
	Penny_M.LoadModel("Models/pennyM.obj");
	

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f, //Intensidad ambiental, la radiación de la luz, lo que se podría ver como la intensidad de 0.3 a 0.6
		//Se cambia la tonalidad del blanco, el segundo valor. Se satura. Solo se modifica si 
		0.0f, -1.0f, 0.0f); //Sol
	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	//POINLIGHTS PRÁCTICA 7
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		3.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	//Luz Farola
	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		0.2f, 0.6f,
		0.0f, 8.0f, -10.0f,
		0.3f, 0.02f, 0.01f);
	pointLightCount++;

	//Luz Penny
	pointLights[2] = PointLight(1.0f, 1.0f, 0.0f,
		0.3f, 0.4f,
		20.0f, 4.0f, -10.0f,
		0.3f, 0.1f, 0.05f);
	pointLightCount++;



	

	////POINTLIGHTS PRÁCTICA 8
	////luz verde
	//pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
	//	0.0f, 1.0f,
	//	3.0f, 1.5f, 1.5f,
	//	0.3f, 0.2f, 0.1f);
	//pointLightCount++;
	////Luz azul
	//pointLights[1] = PointLight(0.0f, 0.0f, 1.0f,
	//	0.2f, 0.6f,
	//	0.0f, 8.0f, -10.0f,
	//	0.3f, 0.02f, 0.01f);
	//pointLightCount++;
	////Luz roja
	//pointLights[2] = PointLight(1.0f, 0.0f, 0.0f,
	//	0.2f, 0.6f,
	//	0.0f, 8.0f, -10.0f,
	//	0.3f, 0.02f, 0.01f);
	//pointLightCount++;
	////Luz blanca
	//pointLights[3] = PointLight(1.0f, 1.0f, 1.0f,
	//	0.2f, 0.6f,
	//	0.0f, 8.0f, -10.0f,
	//	0.3f, 0.02f, 0.01f);
	//pointLightCount++;

	////ARREGLO DE POINTLIGHTS2
	////Como son las mismas luces solo se igualan, esto funciona solo porque son las mismas cuatro luces
	////No se incrementa el contador porque se necesitan solo 4 luces
	//pointLights2[0] = pointLights[3];
	//pointLights2[1] = pointLights[0];
	//pointLights2[2] = pointLights[1];
	//pointLights2[3] = pointLights[2];

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//cofre
	spotLights[1] = SpotLight(0.1f, 0.0f, 0.0f,
		4.0f, 3.0f,
		0.0f, 0.0f, 0.0f,									
		0.0f, 0.0f, 0.0f,									
		1.0f, 0.0f, 0.0f,
		10.0f);												
	spotLightCount++;

	//Avanza
	spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f,
		0.5f, 3.0f,											
		0.0f, 0.0f, 0.0f,									
		0.0f, 0.0f, 0.0f,									
		1.0f, 0.0f, 0.0f,
		20.0f);												
	spotLightCount++;

	//retrocede
	spotLights[3] = SpotLight(1.0f, 1.0f, 0.0f,
		0.5f, 3.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 
	spotLights2[0] = spotLights[0];
	spotLights2[1] = spotLights[1];
	spotLights2[2] = spotLights[3];
	spotLights2[3] = spotLights[2];
	//Segundo arreglo de luces para encender y apagar en retroceso y avance


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
			glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());//Con esta se liga a la camara
		//Las demás luces se quedan fuera del while, por lo que si se comenta ya no se liga y se queda fija
		spotLights[1].SetFlash(glm::vec3(3.82f + mainWindow.gettraslacion() + (2.18f * cos(glm::radians(mainWindow.getcofreaAbre()))), 1.601f + (2.18f * sin(glm::radians(mainWindow.getcofreaAbre()))), 0.0f), glm::vec3(1.0f * cos(glm::radians(mainWindow.getcofreaAbre())), 1.0f * sin(glm::radians(mainWindow.getcofreaAbre())), 0.0f));
		spotLights2[1].SetFlash(glm::vec3(3.82f + mainWindow.gettraslacion() + (2.18f * cos(glm::radians(mainWindow.getcofreaAbre()))), 1.601f + (2.18f * sin(glm::radians(mainWindow.getcofreaAbre()))), 0.0f), glm::vec3(1.0f * cos(glm::radians(mainWindow.getcofreaAbre())), 1.0f * sin(glm::radians(mainWindow.getcofreaAbre())), 0.0f));
		
		spotLights[2].SetFlash(glm::vec3(6.0f + mainWindow.gettraslacion(), 1.8f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		spotLights2[3].SetFlash(glm::vec3(6.0f + mainWindow.gettraslacion(), 1.8f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		spotLights[3].SetFlash(glm::vec3(-5.3f + mainWindow.gettraslacion(), 1.8f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		spotLights2[2].SetFlash(glm::vec3(-5.3f + mainWindow.gettraslacion(), 1.8f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));


		//información al shader de fuentes de iluminación
		//AQUÍ SE CAMBIAN LAS LUCES
		shaderList[0].SetDirectionalLight(&mainLight);
		if (mainWindow.getencederFarola() == 1) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount-2);
		}
		if (mainWindow.getavanza() == 1) {
			shaderList[0].SetSpotLights(spotLights, spotLightCount-1);
		}
		else {
			shaderList[0].SetSpotLights(spotLights2, spotLightCount-1);
		}
	


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//Ayuda para ver luz cofre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//Instancia del coche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0 + mainWindow.gettraslacion(), 1.35f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carro_M.RenderModel();

		// Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.611f, -0.875f, 3.922f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaDerInf()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaDerecha_M.RenderModel();


		// Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.338f, -0.875f, 3.922f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaDerSup()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaDerecha_M.RenderModel();

		// Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(6.338f, -0.875f, -3.672f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaIzqSup()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaIzquierda_M.RenderModel();

		// Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.611f, -0.875f, -3.672f));
		model = glm::rotate(model, glm::radians(mainWindow.getllantaIzqInf()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaIzquierda_M.RenderModel();


		// Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.82f, 1.601f, 0.118f));
		model = glm::rotate(model, glm::radians(mainWindow.getcofreaAbre()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getcofreCierra()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cofre_M.RenderModel();

		//Farola
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.40f, -10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Farola_M.RenderModel();

		//DADO 8 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -15.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshList[4]->RenderMesh();
	
		//Helicoptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f - mainWindow.gettraslacionHeli(), 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//PENNY 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 4.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Penny_M.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
