<h1 align="center">Computer Graphics Lab 🚁💡</h1>
<img align="right" alt="graphics" width="250" style="margin-left: 20;" src="https://static.javatpoint.com/tutorial/computer-graphics/images/computer-graphics-tutorial.png">

### Universidad Nacional Autónoma de México  
### Facultad de Ingeniería, DIE  

### Practice 7: Lighting & Animation in 3D Scenes

#### Objective
In this practice, we explored **lighting techniques** in OpenGL and integrated them into animated 3D scenes. We implemented both **spotlight** and **point light** sources and connected them to moving objects.

<h2>Implementation Details</h2>

### 🚗 Previous Setup: Textured Car with Headlights
- A custom textured car was used with:
  - Hierarchical structure for **wheels**, **hood**, and **body**.
  - Movement through keyboard controls (forward and backward).
  - A **blue headlight (spotlight)** positioned at the front, dynamically updating with the car's movement.

### 🚁 Exercise 1: Helicopter Movement
- **Keyboard-Controlled Motion**: The helicopter can move forward and backward.
- **Model Setup**: Imported from 3ds Max and integrated into the OpenGL environment.

### 💡 Exercise 2: Yellow Spotlight on Helicopter
- **Spotlight Creation**: A yellow spotlight was created.
- **Attachment**: The light was attached to the helicopter and dynamically follows its position.
- **Effect**: The spotlight aims downward to simulate a searchlight.

### 🛋️ Exercise 3: Lamp Model with White Point Light
- **Model Import**: A textured lamp was imported into the scene.
- **Point Light Source**: A white point light was positioned at the lamp's bulb.
- **Static Lighting**: This light remains fixed and illuminates its surrounding area.

### 🔧 Tools & Techniques
- Lighting in **OpenGL** (GL_LIGHTx, GL_POSITION, GL_SPOT_DIRECTION)
- Model design and UV texturing in **3ds Max**
- Real-time scene updates and object-light synchronization

This practice strengthened our understanding of real-time lighting, object interaction with light sources, and how to coordinate animation with illumination effects in OpenGL scenes.

