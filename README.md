<h1 align="center">Computer Graphics Lab 💻</h1>
<img align="right" alt="another" width="250" style="margin-left: 20;" src="https://static.javatpoint.com/tutorial/computer-graphics/images/computer-graphics-tutorial.png">


### Universidad Nacional Autonoma de México
### Facultad de Ingeniería, DIE

### Practice 3
  <p>
        In this practice, we developed a program to generate a <strong>Pyraminx-style 3D puzzle</strong>, 
        composed of <strong>9 smaller pyramids per face</strong>. The goal was to apply 
        <strong>transformations</strong> such as <em>translations, rotations, and scaling</em> to 
        properly arrange the pyramids while ensuring each face had a distinct color. Additionally, visible 
        <strong>separation lines</strong> between the smaller pyramids were required to enhance differentiation.
  </p>

<h2>Implementation Details</h2>
    <ul>
        <li><strong>Base Pyraminx Construction</strong>
            <ul>
                <li>A larger pyramid serves as the base structure.</li>
                <li>Each of its four faces consists of <strong>9 smaller pyramids</strong>, arranged in a 3x3 triangular grid.</li>
            </ul>
        </li>
        <li><strong>Transformations</strong>
            <ul>
                <li><strong>Translations</strong> to position each small pyramid correctly.</li>
                <li><strong>Rotations</strong> to align the pyramids to their respective face orientations.</li>
                <li><strong>Scaling</strong> to ensure the small pyramids fit neatly within their designated positions.</li>
            </ul>
        </li>
        <li><strong>Coloring & Shading</strong>
            <ul>
                <li>Each face of the Pyraminx is rendered in a different color.</li>
                <li>Gaps (dark lines) between adjacent pyramids simulate separation, improving the visual distinction of individual pieces.</li>
            </ul>
        </li>
    </ul>
