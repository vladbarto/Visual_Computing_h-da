#include "Scene.h"
#include "Cube.h"
#include "Transform.h"
#include <AssetManager.h>

int FrameCounter = 0;

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();
//// For the House in the first Lab
        float vertices[] = {-0.5, -0.5, 0.0, 0.0, 1.0,
                            0.5,  -0.5, 0.0, 0.0, 1.0,
                            0.5,   0.5, 0.0, 1.0, 0.0,
                            0.0,   1.0, 1.0, 0.0, 0.0,
                            -0.5,  0.5, 0.0, 1.0, 0.0};

        int indices[] = {0, 1, 2,
                         0, 2, 4,
                         4, 2, 3};
 //// For Name Initials
//        float vertices[] = {
//                // V
//                -0.6, 0.5, 0.0, 1.0, 0.0,
//                -0.5, -0.5, 0.0, 0.0, 1.0,
//                -0.4, 0.5, 1.0, 0.0, 0.0,
//
//                // B
//                -0.3, 0.5, 1.0, 0.0, 0.0,
//                -0.3, 0.0, 0.0, 1.0, 0.0,
//                -0.1, 0.25, 0.0, 1.0, 0.0,
//                -0.3, -0.5, 0.0, 0.0, 1.0,
//                -0.1, -0.25, 0.0, 1.0, 0.0,
//        };
//
//        int indices[] = {
//                // V
//                0, 1, 2,
//
//                // B
//                3, 4, 5,
//                4, 6, 7,
//        };

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */
        //GLuint vboID, vaoID; //der VBO is declared here. VAO auch.

        // Aufgabe 1.1 a
        glGenBuffers(1, &vboID); // VBO now generated
        glBindBuffer(GL_ARRAY_BUFFER, vboID); // VBO now activated
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW); // VBO now fulled up with data vertex

        // Aufgabe 1.1 b
        glGenVertexArrays(1, &vaoID); // VAO now generated
        glBindVertexArray(vaoID); //VAO now activated (binded)

        // Aufgabe 1.1 c
        // describe VBO in VAO
//        glVertexAttribPointer(0, 2, GL_FLOAT, false, 20, 0); //function call for Vertices
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(1, 3, GL_FLOAT, false, 20, (void*)8); //function call for Points
//        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0); //function call for Vertices (x, y, z)
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12); //function call for Vertices (r, g, b)
        glEnableVertexAttribArray(1);

        // Aufgabe 1.1 d : Setup IBO
        GLuint iboID;
        glGenBuffers(1, &iboID); // only works after glGenVertexArrays()
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        // Aufgabe 1.1 e : Loeschen (unbind, delete)
//        glDeleteVertexArrays(1, &vaoID);
//        glDeleteBuffers(1, &vboID);
        /**
         * From here bis Aufgabe 1.4 we will place our Szenegraph
         */
        float angleDegrees = 30.0f;
        float angleRadians = glm::radians(angleDegrees);
        glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::quat rotation = glm::angleAxis(angleRadians, axis);

        float angleDegreesX = 20.0f;
        float angleRadiansX = glm::radians(angleDegreesX);
        glm::vec3 axisX = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::quat rotationX = glm::angleAxis(angleRadiansX, axisX);

        glm::vec4 scaleHalf = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        glm::vec4 stretchOnY = glm::vec4(1.0f, 2.0f, 1.0f, 1.0f);
        glm::vec4 tighten = glm::vec4(0.8f, 1.0f, 0.8f, 1.0f);
        //body.rotate(rotation);
        body.scale(tighten);
        body.scale(stretchOnY);
        body.scale(scaleHalf);

        /** head = scale to half, scale to half, translate */
        glm::vec4 translateAboveBody = glm::vec4(0.0f, 0.65f, 0.0f, 1.0f);
        head.translate(translateAboveBody);
        head.rotate(rotationX);
        //head.rotate(rotation);
        head.scale(tighten);
        head.scale(scaleHalf);
        head.scale(scaleHalf);

        /** left Arm: scale on x, scale on z, translate */
        glm::vec4 scaleBone = glm::vec4( 0.3f, 0.6f, 0.3f, 1.0f);
        glm::vec4 translateLeftForArmUp = glm::vec4(-0.35f, 0.3f, 0.0f, 1.0f);
        leftUpperArm.translate(translateLeftForArmUp);
        leftUpperArm.rotate(rotationX);
        leftUpperArm.rotate(rotation);
        leftUpperArm.scale(scaleBone);
        leftUpperArm.scale(scaleBone);

        glm::vec4 translateLeftForArmDown = glm::vec4(-0.35f, -0.1f, 0.0f, 1.0f);
        leftLowerArm.translate(translateLeftForArmDown);
        leftLowerArm.scale(scaleBone);
        leftLowerArm.scale(scaleBone);

        /** right Arm: idem */
        glm::vec4 translateRightForArmUp = glm::vec4(+0.35f, 0.3f, 0.0f, 1.0f);
        rightUpperArm.translate(translateRightForArmUp);
        rightUpperArm.rotate(rotationX);
        float angleDegrees2 = -30.0f;
        float angleRadians2 = glm::radians(angleDegrees2);
        glm::quat rotation2 = glm::angleAxis(angleRadians2, axis);
        rightUpperArm.rotate(rotation2);
        rightUpperArm.scale(scaleBone);
        rightUpperArm.scale(scaleBone);

        glm::vec4 translateRightForArmDown = glm::vec4(+0.35f, -0.1f, 0.0f, 1.0f);
        rightLowerArm.translate(translateRightForArmDown);
        rightLowerArm.scale(scaleBone);
        rightLowerArm.scale(scaleBone);

        /** left and right Legs: idem... almost */
        glm::vec4 translateLeftLeg = glm::vec4(-0.1f, -0.7f, 0.0f, 1.0f);
        leftLeg.translate(translateLeftLeg);
        leftLeg.scale(scaleBone);
        leftLeg.scale(scaleBone);

        glm::vec4 translateRightLeg = glm::vec4(+0.1f, -0.7f, 0.0f, 1.0f);
        rightLeg.translate(translateRightLeg);
        rightLeg.scale(scaleBone);
        rightLeg.scale(scaleBone);

//        /** Load into Vertex Shader the ViewMatrix */
//        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
//        glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);
//        glm::vec3 cameraTarget(0.0f, 2.0f, 0.0f);
//
//        glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);
//
//        m_shader->setUniform("view", view, false);
//
//        /** Projection Matrix into Vertex Shader */
//        int width = 1920;
//        int height = 1080;
//        float fov = glm::radians(45.0f);  // Field of view in degrees, convert to radians
//        float aspectRatio = width / height;  // Adjust the aspect ratio based on your window size
//        float nearClip = 0.1f;
//        float farClip = 100.0f;
//
//        glm::mat4 projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
//
//        // Example of changing FOV dynamically
//        fov = glm::radians(60.0f);  // Change FOV to 60 degrees
//        projection = glm::perspective(fov, aspectRatio, nearClip, farClip);
//        m_shader->setUniform("projection", projection, false);

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

void Scene::render(float dt)
{
    /*
    * ************
    * Place your code here!
    * ************
    */

    /**
     * Revolve the cube around x and y
     */
    float angleDegrees = 45.0f * dt;
    float angleRadians = glm::radians(angleDegrees);
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::quat rotation = glm::angleAxis(angleRadians, axis);

//    body.rotate(rotation);
    head.rotate(rotation);
//    leftUpperArm.rotate(rotation);
    /**
     * Aufgabe 2.3.2: Hintergrund löschen
     */
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.66f, 0.37f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /**
     * Render the first cube
     */
    m_shader->setUniform("model", head.getMatrix(), false);
    glBindVertexArray(vaoID); // activate VAO (only once needed)
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // render call (initial number: 9)

    /**
     * Render the second cube (head)
     */
    m_shader->setUniform("model", body.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    /**
     * Render the other parts:
     * left/right upper and lower arms
     * left/right leg
     */
    m_shader->setUniform("model", leftUpperArm.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", leftLowerArm.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", rightUpperArm.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", rightLowerArm.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", leftLeg.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", rightLeg.getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    /**
     * Deal with walking cycle
     */
    glm::vec3 jointHipLeft = glm::vec3(0.0f, -0.5f, 0.0f);
    glm::vec3 jointShoulderLeft = glm::vec3(-0.3f, 0.4f, 0.0f);
    FrameCounter++;
    float armRotationAngle = -15.0f * sin(dt)/20;
    /** Detection mecanism based on FrameCounter so that I can rotate back and forth */
    if(FrameCounter > 60) armRotationAngle *= -1;
    if(FrameCounter > 180) armRotationAngle *= -1, FrameCounter = -60;

    leftUpperArm.rotateAroundPoint(jointShoulderLeft, glm::vec3(armRotationAngle, 0.0f, 0.0f));
    leftLowerArm.rotateAroundPoint(jointShoulderLeft, glm::vec3(armRotationAngle, 0.0f, 0.0f));

    rightUpperArm.rotateAroundPoint(jointShoulderLeft, glm::vec3(-armRotationAngle, 0.0f, 0.0f));
    rightLowerArm.rotateAroundPoint(jointShoulderLeft, glm::vec3(-armRotationAngle, 0.0f, 0.0f));

    leftLeg.rotateAroundPoint(jointShoulderLeft, glm::vec3(armRotationAngle, 0.0f, 0.0f));
    rightLeg.rotateAroundPoint(jointShoulderLeft, glm::vec3(-armRotationAngle, 0.0f, 0.0f));

    /**
     * Deal with color animation
     */
    static float animationTime = 0.0f;
    animationTime += dt;
    m_shader->setUniform("animation", animationTime/10);

    glBindVertexArray(0); // good programmers should use reset

    /**
     * Remark: the code only works with convex forms. Any concave form and it will break
     */
}

// Global:
float lookUpDown = 0.0f;  // for y-Axis
float lookLeftRight = 0.0f;  // for x-Axis
float moveCameraUpDown = 0.0f; //for y-Axis
float moveCameraLeftRight = 0.0f; // for x-Axis
MousePosition mousePosition;

void Scene::update(float dt)
{
    /** Projection Matrix into Vertex Shader */
    int width = 16;
    int height = 9;
    float fov = glm::radians(60.0f);  // Field of view in degrees, convert to radians
    float aspectRatio = width / height;  // Adjust the aspect ratio based on your window size
    float nearClip = 0.1f;
    float farClip = 100.0f;


    // Tastatureingabe
    if(m_window->getInput().getKeyState(Key::W) == KeyState::Pressed) {
        lookUpDown -= 0.1f;
    }
    if(m_window->getInput().getKeyState(Key::S) == KeyState::Pressed) {
        lookUpDown += 0.1f;
    }
    if(m_window->getInput().getKeyState(Key::A) == KeyState::Pressed) {
        lookLeftRight -= 0.1f;
    }
    if(m_window->getInput().getKeyState(Key::D) == KeyState::Pressed) {
        lookLeftRight += 0.1f;
    }

    // Mauseingabe
    onMouseMove(mousePosition);
    std::cout<<"MouseX (new): "<<mousePosition.X<<"\nMouseY (new): "<<mousePosition.Y<<std::endl<<std::endl;
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraPosition(moveCameraLeftRight, moveCameraUpDown, -5.0f);
    glm::vec3 cameraTarget(lookLeftRight, lookUpDown, 0.0f);

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

void Scene::onMouseMove(MousePosition mouse)
{
    int prescaler = 50;
    moveCameraLeftRight += (mouse.X - mouse.oldX) / prescaler;
    moveCameraUpDown += (mouse.Y - mouse.oldY) / prescaler;
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
/**
* x   y r g b
  0   4 8 12 16
  20
*/