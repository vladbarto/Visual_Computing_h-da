#include "Scene.h"
#include "Cube.h"
#include "Transform.h"
#include "Tyre.h"
#include <AssetManager.h>

int FrameCounter = 0;

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

void Scene::Szenegraph_Tyres () {
    glm::vec4 translate_front_left = glm::vec4(-1.5f, 0.0f, +0.7f, 1.0f);
    glm::vec4 translate_front_right = glm::vec4(-1.5f, 0.0f, -0.7f, 1.0f);
    glm::vec4 translate_rear_left = glm::vec4(+1.5f, 0.0f, +0.7f, 1.0f);
    glm::vec4 translate_rear_right = glm::vec4(+1.5f, 0.0f, -0.7f, 1.0f);

    FrontAxis_L.translate(translate_front_left);
    FrontAxis_R.translate(translate_front_right);
    RearAxis_L.translate(translate_rear_left);
    RearAxis_R.translate(translate_rear_right);
}
void Scene::Szenegraph_Main_Body () {
    glm::vec4 shrink_floor = glm::vec4(3.0f, 0.2f, 1.5f, 1.0f);
    Floor.scale(shrink_floor);

    glm::vec4 scale_cockpit = glm::vec4(2.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 translate_cockpit = glm::vec4(-1.0f, 0.5f, 0.0f, 1.0f);
    Cockpit.translate(translate_cockpit);
    Cockpit.scale(scale_cockpit);

    glm::vec4 scale_chair_bottom = glm::vec4(0.5f, 0.2f, 0.5f, 1.0f);
    glm::vec4 translate_chair_bottom = glm::vec4(0.2f, 0.2f, 0.0f, 1.0f);
    Chair_bottom.translate(translate_chair_bottom);
    Chair_bottom.scale(scale_chair_bottom);

    glm::vec4 scale_chair_back = glm::vec4(0.1f, 1.5f, 0.5f, 1.0f);
    float thetaDegrees = -10.0f;
    float thetaRadians = glm::radians(thetaDegrees);
    glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::quat tilt_chair_back = glm::angleAxis(thetaRadians, axis);
    glm::vec4 translate_chair_back = glm::vec4(0.5f, 0.7f, 0.0f, 1.0f);
    Chair_back.translate(translate_chair_back);
    Chair_back.rotate(tilt_chair_back);
    Chair_back.scale(scale_chair_back);

}
void Scene::Szenegraph_Spoiler () {
    glm::vec4 scale_pillar = glm::vec4(0.05f, 1.5f, 0.05f, 1.0f);
    float thetaDegrees = -5.0f;
    float thetaRadians = glm::radians(thetaDegrees);
    glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::quat tilt_pillar = glm::angleAxis(thetaRadians, axis);
    glm::vec4 translate_pillar_left = glm::vec4(1.2f, 0.7f, 0.5f, 1.0f);
    glm::vec4 translate_pillar_right = glm::vec4(1.2f, 0.7f, -0.5f, 1.0f);

    Pillar_L.translate(translate_pillar_left);
    Pillar_L.rotate(tilt_pillar);
    Pillar_L.scale(scale_pillar);

    Pillar_R.translate(translate_pillar_right);
    Pillar_R.rotate(tilt_pillar);
    Pillar_R.scale(scale_pillar);

    float alphaDegrees = +15.0f;
    float alphaRadians = glm::radians(alphaDegrees);
    glm::vec3 axis_2 = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::quat tilt_spoiler = glm::angleAxis(alphaRadians, axis_2);
    glm::vec4 scale_spoiler = glm::vec4(0.7f, 0.1f, 1.5f, 1.0f);
    glm::vec4 translate_spoiler = glm::vec4(1.2f, 1.4f, 0.0f, 1.0f);

    Spoiler.translate(translate_spoiler);
    Spoiler.rotate(tilt_spoiler);
    Spoiler.scale(scale_spoiler);
}
bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        // Aufgabe 1.1 a
        glGenBuffers(1, &vboID_tyre); // VBO now generated
        glBindBuffer(GL_ARRAY_BUFFER, vboID_tyre); // VBO now activated
        glBufferData(GL_ARRAY_BUFFER, sizeof(tyreVert), &tyreVert, GL_STATIC_DRAW); // VBO now fulled up with data vertex
        // Aufgabe 1.1 b
        glGenVertexArrays(1, &vaoID_tyre); // VAO now generated
        glBindVertexArray(vaoID_tyre);  // Bind VAO_Tyre

        // Aufgabe 1.1 c
        // describe VBO in VAO
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0); //function call for Vertices (x, y, z)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12); //function call for Vertices (r, g, b)
        glEnableVertexAttribArray(1);

        // Aufgabe 1.1 d : Setup IBO
        GLuint iboID_tyre, iboID_cube;
        glGenBuffers(1, &iboID_tyre); // only works after glGenVertexArrays()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_tyre);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tyreInd), tyreInd, GL_STATIC_DRAW);

        // Aufgabe 1.1 e : Loeschen (unbind, delete)
//        glDeleteVertexArrays(1, &vaoID);
//        glDeleteBuffers(1, &vboID);
        /**
         * Here we will place our Szenegraph for wheels
         */
        Szenegraph_Tyres();

        glBindVertexArray(0);  // Unbind VAO_Tyre

        glGenBuffers(1, &vboID_cube); // VBO now generated
        glBindBuffer(GL_ARRAY_BUFFER, vboID_cube); // VBO now activated
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW); // VBO now fulled up with data vertex

        glGenVertexArrays(1, &vaoID_cube); // VAO now generated
        glBindVertexArray(vaoID_cube);  //Bind VAO_Cube

        // describe VBO in VAO (again)
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0); //function call for Vertices (x, y, z)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12); //function call for Vertices (r, g, b)
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &iboID_cube); // only works after glGenVertexArrays()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID_cube);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        /**
         * Here will take place the Szenegraph for cubes
         */
        Szenegraph_Main_Body();
        Szenegraph_Spoiler();

        // Aufgabe 1.4
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        // Aufgabe 2.3.3: Deep Test activation for OpenGL
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearDepth(1.0);
        static Transform xyz;
        std::cout << "Scene initialization done\n";
        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}
void Scene::render_shapes_on_screen () {
    /**
     * Render the wheels, contained in vaoID_tyre
     */
    m_shader->setUniform("model", FrontAxis_L.getMatrix(), false);
    glBindVertexArray(vaoID_tyre); // activate VAO (only once needed)
    glDrawElements(GL_TRIANGLES, sizeof(tyreInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", FrontAxis_R.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(tyreInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", RearAxis_L.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(tyreInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", RearAxis_R.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(tyreInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Floor.getMatrix(), false);
    glBindVertexArray(vaoID_cube); // activate VAO (only once needed)
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Cockpit.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Chair_bottom.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Chair_back.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Pillar_L.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Pillar_R.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", Spoiler.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

//    m_shader->setUniform("model", cube.getMatrix(), false);
//    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);
}

float displacement_factor = 0;
void Scene::render(float dt)
{
    /**
     * Revolve the cube around x and y
     */

    /**
     * Aufgabe 2.3.2: Hintergrund löschen
     */
    glClearColor(0.0f, 0.66f, 0.37f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render_shapes_on_screen();

    /**
     * Deal with color animation
     */
    static float animationTime = 0.0f;
    animationTime += dt;
    m_shader->setUniform("animation", animationTime/10);

    float angleDegrees = 45.0f * dt;
    float angleRadians = glm::radians(angleDegrees);
    glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::quat rotation = glm::angleAxis(angleRadians, axis);

    glm::vec3 jointFrontAxisR = glm::vec3(-1.5f+displacement_factor, -0.1f, 0.3f);
    FrontAxis_R.rotateAroundPoint(jointFrontAxisR, glm::vec3(0.0f, 0.0f, angleDegrees/10));

    glm::vec3 jointFrontAxisL = glm::vec3(-1.5f+displacement_factor, -0.1f, -0.3f);
    FrontAxis_L.rotateAroundPoint(jointFrontAxisL, glm::vec3(0.0f, 0.0f, angleDegrees/10));

    glm::vec3 jointRearAxisR = glm::vec3(1.5f+displacement_factor, -0.1f, 0.3f);
    RearAxis_R.rotateAroundPoint(jointRearAxisR, glm::vec3(0.0f, 0.0f, angleDegrees/10));

    glm::vec3 jointRearAxisL = glm::vec3(1.5f+displacement_factor, -0.1f, -0.3f);
    RearAxis_L.rotateAroundPoint(jointRearAxisL, glm::vec3(0.0f, 0.0f, angleDegrees/10));

    glm::vec4 translate_car = glm::vec4(-0.02f, 0.0f, 0.0f, 1.0f);

    {/**
     * De-comment this block to make the car move
     * Comment this block to make the car stay where it is
     */
    displacement_factor += -0.02f;
    Floor.translate(translate_car);
    Cockpit.translate(translate_car);
    Chair_bottom.translate(translate_car);
    Chair_back.translate(translate_car);
    Pillar_L.translate(translate_car);
    Pillar_R.translate(translate_car);
    Spoiler.translate(translate_car);
    }

    glBindVertexArray(0); // good programmers should use reset
    /**
     * Remark: the code only works with convex forms. Any concave form and it will break
     */
}

// Global:
float moveCameraUpDown = 0.0f; //for y-Axis
float moveCameraLeftRight = 0.0f; // for x-Axis
MousePosition mousePosition;
float moveCameraForwardZ = -5.0f;
float moveCameraTargetX = 0.0f;
float moveCameraTargetY = 0.0f;
float moveCameraTargetZ = 0.0f;

void Scene::update(float dt)
{
    int width = 16;
    int height = 9;
    float fov = glm::radians(60.0f);  // Field of view in degrees, convert to radians
    float aspectRatio = width / height;  // Adjust the aspect ratio based on your window size
    float nearClip = 0.1f;
    float farClip = 100.0f;


    // Tastatureingabe
    if(m_window->getInput().getKeyState(Key::W) == KeyState::Pressed) {
        moveCameraTargetY += 0.1f;
    }
    if(m_window->getInput().getKeyState(Key::S) == KeyState::Pressed) {
        moveCameraTargetY -= 0.1f;
    }
    if(m_window->getInput().getKeyState(Key::A) == KeyState::Pressed) {
        moveCameraTargetX += 0.1f;
    }
    if(m_window->getInput().getKeyState(Key::D) == KeyState::Pressed) {
        moveCameraTargetX -= 0.1f;
    }

    // Mauseingabe
    onMouseMove(mousePosition);
    if(m_window->getInput().getMouseButtonState(MouseButton::MouseButton1) == MouseButtonState::Pressed) {
        // Zoom in illusion. In fact, we move the camera position vorwärts (forward) on z-Axis
        moveCameraForwardZ += 0.1f;
    }
    if(m_window->getInput().getMouseButtonState(MouseButton::MouseButton2) == MouseButtonState::Pressed) {
        // Zoom out illusion. In fact, we move the camera position rückwärts (backward) on z-Axis
        moveCameraForwardZ -= 0.1f;
    }
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraPosition(moveCameraLeftRight, moveCameraUpDown, moveCameraForwardZ);
    glm::vec3 cameraTarget(moveCameraTargetX, moveCameraTargetY, moveCameraTargetZ);

    /** View and Projection Matrices loading into Vertex Shader */
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);
    m_shader->setUniform("view", view, false);

    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
    m_shader->setUniform("projection", projection, false);
}

OpenGLWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

float dot_product_two_vectors(glm::vec3 A, glm::vec3 B) {
    return (A.x * B.x) +
            (A.y * B.y) +
             (A.z * B.z);
}
float length_of_a_vector(glm::vec3 V) {
    return sqrt(V.x * V.x +
                    V.y * V.y +
                        V.z * V.z);
}
float arccos_two_vectors (glm::vec3 a, glm::vec3 b) {
    //Returns in Degrees
    return acos((dot_product_two_vectors(a, b)) / (length_of_a_vector(a) * length_of_a_vector(b))) * 3.14 * 10000 / 180;
}
void Scene::onMouseMove(MousePosition mouse)
{
    int prescaler = 50;

    if(m_window->getInput().getMouseButtonState(MouseButton::MouseButton3) == MouseButtonState::Pressed) {
        if(m_window->getInput().getKeyState(Key::LeftShift) == KeyState::Pressed) {
            // So if LeftShift + ScrollMouseButton
            moveCameraTargetX += (mouse.X - mouse.oldX) / prescaler;
            moveCameraTargetY += (mouse.Y - mouse.oldY) / prescaler;
            moveCameraTargetZ += ((mouse.X - mouse.oldX) + (mouse.Y - mouse.oldY)) / prescaler;

            moveCameraLeftRight += (mouse.X - mouse.oldX) / prescaler;
            moveCameraUpDown += (mouse.Y - mouse.oldY) / prescaler;
        }
        else
        {
            // Rotate camera only if the scroll button is pressed, without LeftShift
            moveCameraUpDown += (mouse.Y - mouse.oldY) / prescaler;
            glm::vec3 initialCameraLookVector = glm::vec3(0.0f,
                                                          0.0f,
                                                          0.5f);
            glm::vec3 currentCameraLookVector = glm::vec3(moveCameraTargetX - moveCameraLeftRight,
                                                          moveCameraTargetY - moveCameraUpDown,
                                                          moveCameraTargetZ - moveCameraForwardZ);
            int arccos = (int)arccos_two_vectors(initialCameraLookVector, currentCameraLookVector) % 360;
            if(arccos >= 0 && arccos < 90) {
                moveCameraLeftRight += (mouse.X - mouse.oldX) / prescaler;
                moveCameraForwardZ += (mouse.X - mouse.oldX) / prescaler;
            }
            else if(arccos >= 90 && arccos < 180) {
                moveCameraLeftRight -= (mouse.X - mouse.oldX) / prescaler;
                moveCameraForwardZ += (mouse.X - mouse.oldX) / prescaler;
            }
            else if(arccos >= 180 && arccos < 270) {
                moveCameraLeftRight -= (mouse.X - mouse.oldX) / prescaler;
                moveCameraForwardZ -= (mouse.X - mouse.oldX) / prescaler;
            }
            else if(arccos >= 270 && arccos < 360) {
                moveCameraLeftRight += (mouse.X - mouse.oldX) / prescaler;
                moveCameraForwardZ -= (mouse.X - mouse.oldX) / prescaler;
            }
            std::cout<<arccos_two_vectors(initialCameraLookVector, currentCameraLookVector)<<"\n";
        }
    }
}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}