#include "Scene.h"
#include <AssetManager.h>

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init() {
    try {
        // Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl",
                                                                              "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        // Vertex data
        float vertices[] = {-0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
                            0.5, -0.5, 0.0, 0.0, 0.0, 1.0,
                            0.5, 0.5, 0.0, 0.0, 1.0, 0.0,
                            0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
                            -0.5, 0.5, 0.0, 0.0, 1.0, 0.0};

        int indices[] = {0, 1, 2,
                         0, 2, 4,
                         4, 2, 3};

        // generate and activate VBO and upload data //
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        // generate and activate VAO //
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // describe VBO in the VAO //
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12);
        glEnableVertexAttribArray(1);

        // setup IBO //
        GLuint iboID;
        glGenBuffers(1, &iboID); //only works after glGenVertexArrays();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::cout << "Scene initialization done\n";
        return true;
    }
    catch (std::exception &ex) {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::render(float dt)
{
    // activate VAO //
    glBindVertexArray(vaoID);
    // render call //
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    // check for OpenGL errors
    GLenum error = glGetError();

    // good programmers should reset //
    glBindVertexArray(0);
}

void Scene::update(float dt)
{

}

OpenGLWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

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
