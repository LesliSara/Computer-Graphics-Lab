<h1 align="center">Computer Graphics Lab 🚘🔦</h1>
<img align="right" alt="graphics" width="250" style="margin-left: 20;" src="https://static.javatpoint.com/tutorial/computer-graphics/images/computer-graphics-tutorial.png">

### Universidad Nacional Autónoma de México  
### Facultad de Ingeniería, DIE  

### Practice 8: Advanced Lighting Control with Spotlights & Point Lights

#### Objective
This practice expanded on our knowledge of lighting by combining dynamic control and multiple light sources in OpenGL. We created interactive spotlights and point lights synchronized with animated parts of our custom models.

<h2>Implementation Details</h2>

### 🚗 Exercise 1: Spotlight from the Car Hood
- **Colorful Spotlight**: A **non-white, non-blue** spotlight was attached to the car's hood.
- **Dynamic Direction**: When the hood opens or closes, the light's direction updates accordingly.
- **Hierarchical Link**: The light was made child to the hood to follow its transformation matrix.

### 💡 Exercise 2: Bidirectional Spotlights Based on Movement
- **Forward Spotlight**:
  - Activated when moving left (negative X axis).
  - Illuminates the front of the car.
- **Reverse Spotlight**:
  - Activated when moving right (positive X axis).
  - Illuminates the rear of the car.
- **Logic Control**: Boolean flags determine which spotlight is active depending on user input.

### 🧸 Exercise 3: Interactive Point Light on a Custom Model
- **Model Selection**: A non-lamp model was chosen to host a white point light.
- **Interactivity**: Both the point light from this model and the lamp’s point light (from Practice 7) can be independently toggled on/off using the keyboard.
- **Lighting Update**: Ensured correct light enable/disable logic within the scene loop.

### 🧰 Tools & Techniques
- Light state control via keyboard events
- GL_LIGHTi configuration for spotlights and point lights
- Scene graph hierarchy for light-object linkage
- Conditional rendering and lighting logic in OpenGL

This practice provided a deeper understanding of dynamic lighting interactions, especially regarding movement-based behavior and hierarchical transformations tied to light sources.

