<h1 align="center">Computer Graphics Lab 🐉🎪</h1>
<img align="right" alt="graphics" width="250" style="margin-left: 20;" src="https://static.javatpoint.com/tutorial/computer-graphics/images/computer-graphics-tutorial.png">

### Universidad Nacional Autónoma de México

### Facultad de Ingeniería, DIE

### Practice 9: 🎆 Animated Billboard & Dragon Animation 🐉

#### Objective

In this practice, we focused on combining **text animation**, **hierarchical modeling**, and **custom function-based transformations** to bring dynamic elements to life using **OpenGL**.

<h2>Implementation Details</h2>

### 🎆 Animated Billboard on Arch Structure

* **Modeling**: The top sign portion was separated from the arch model to allow independent manipulation.
* **Text Display**: The phrase <strong>"PROYECTO CGEIHC Feria"</strong> was rendered on the sign.
* **Animation**:

  * Letters moved from **left to right** in a **looping, cyclical pattern**, simulating an **LED/LCD marquee** display.
  * Timing and speed were controlled to create a smooth scrolling effect.

### 🐉 Animated Dragon with Independent Head Functions

* **Model Preparation**:

  * Dragon heads (including necks) were detached from the body to animate individually.
  * Each head was assigned a **distinct color**: red, blue, green, white, and brown.

* **Dragon Body Animation**:

  * The body was animated with a smooth **back-and-forth motion**, simulating idle movement.

* **Wing Flapping**:

  * Wings were hierarchically animated with periodic **flapping motion**.

* **Head Movements**:

  * Each dragon head followed a **unique movement algorithm**:

    * Head 1: Spiral movement (Archimedean spiral)
    * Head 2: Sine wave oscillation
    * Head 3: Lemniscate pattern
    * Head 4 & 5: Custom or mixed parametric functions
  * Movements were continuous and visually distinct, adding character and complexity.


