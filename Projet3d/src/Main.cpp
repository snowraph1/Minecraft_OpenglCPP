#include"lib.h"

using namespace std;

const float speed = 0.01f;

Vertex vertices[] =
{
    //Front
    glm::vec3(-0.5f, 0.5f, -0.5f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f), //top left
    glm::vec3(-0.5f, -0.5f, -0.5f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f), //bottom left
    glm::vec3(0.5f, -0.5f, -0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f), //bottom right
    glm::vec3(0.5f, 0.5f, -0.5f),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f), //top right 

    //Right
    glm::vec3(0.5f, 0.5f, 0.5f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f), //top right
    glm::vec3(0.5f, -0.5f, 0.5f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f), //bottom right

    //Back
    glm::vec3(-0.5f, 0.5f, 0.5f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 16.f), //top left
    glm::vec3(-0.5f, -0.5f, 0.5f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 4.f, 1.f / 16.f * 15.f), //bottom left

    //Bottom
    glm::vec3(-0.5f, -0.5f, -0.5f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 2.f, 1.f / 16.f * 16.f), //top left
    glm::vec3(0.5f, -0.5f, -0.5f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 2.f, 1.f / 16.f * 15.f), //bottom left
    glm::vec3(0.5f, -0.5f, 0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 15.f), //bottom right
    glm::vec3(-0.5f, -0.5f, 0.5f),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f / 16.f * 3.f, 1.f / 16.f * 16.f), //top right 

    //Top
    glm::vec3(-0.5f, 0.5f, -0.5f),         glm::vec3(1.f, 0.f, 0.f),       glm::vec2(1.f / 16.f * 8.f, 1.f / 16.f * 14.f), //top left
    glm::vec3(0.5f, 0.5f, -0.5f),       glm::vec3(0.f, 1.f, 0.f),       glm::vec2(1.f / 16.f * 8.f, 1.f / 16.f * 13.f), //bottom left
    glm::vec3(0.5f, 0.5f, 0.5f),        glm::vec3(0.f, 0.f, 1.f),       glm::vec2(1.f / 16.f * 9.f, 1.f / 16.f * 13.f), //bottom right
    glm::vec3(-0.5f, 0.5f, 0.5f),        glm::vec3(0.f, 1.f, 1.f),       glm::vec2(1.f / 16.f * 9.f, 1.f / 16.f * 14.f), //top right 
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = {
    2, 1, 0,
    3, 2, 0,
    5, 2, 3,
    3, 4, 5,
    7, 5, 4,
    6, 7, 4,
    1, 6, 0,
    1, 7, 6,
    8, 9, 10,
    8, 10, 11,
    14, 13, 12,
    15, 14, 12
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void UpdateInput(GLFWwindow* window, Camera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    {
        camera.moveCamera(glm::vec3(0.f, 0.f, -speed));
    }
   
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.moveCamera(glm::vec3(0.f, 0.f, speed));
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.moveCamera(glm::vec3(-speed , 0.f, 0.f));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.moveCamera(glm::vec3(speed, 0.f, 0.f));
    }
}

bool loadShaders(GLuint &program) {
    bool loadSuccess = true;

    char infoLog[512];
    GLint success;

    string temp = "";
    string src = "";
    ifstream in_file;

    //vertex
    in_file.open("vertex_core.glsl");

    if (in_file.is_open()) {
        while (getline(in_file, temp))
        {
            src += temp + "\n";
        }
    }
    else {
        cout << "vertex shader pas ouvert \n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertSrc = src.c_str();
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "Vertex shader pas compile \n";
        loadSuccess = false;
    }

    temp = "";
    src = "";

    //fragment
    in_file.open("fragment_core.glsl");

    if (in_file.is_open()) {
        while (getline(in_file, temp))
        {
            src += temp + "\n";
        }
    }
    else {
        cout << "fragment shader pas ouvert \n";
        loadSuccess = false;
    }

    in_file.close();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragSrc = src.c_str();
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "Fragment shader pas compile \n";
        loadSuccess = false;
    }

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        cout << "Erreur program \n";
        loadSuccess = false;
    }

    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccess;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int frameBufferWidth = 0;
    int frameBufferheight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /*make sur the window is the right size*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferheight);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        cout << "Glew pas ok \n";
        glfwTerminate();
    }

    //OPENGL OPTIONS
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Shaders
    GLuint core_program;
    if (!loadShaders(core_program)) {
        cout << "Shaders pas ok \n";
        glfwTerminate();
    }

    //
    GLuint VAO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    //TEXTURE
    int image_width = 0;
    int image_height = 0;
    unsigned char* image = SOIL_load_image("atlas.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "texture pas load \n";
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    glm::vec3 position(0.f);
    glm::vec3 rotation(0.f);
    glm::vec3 scale(1.f);

    glm::mat4 ModelMatrix(1.f);
    ModelMatrix = glm::translate(ModelMatrix, position); 
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    ModelMatrix = glm::scale(ModelMatrix, scale);

    /*
    glm::vec3 camPosition(0.f, 0.f, 2.f);
    glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);

    glm::mat4 ViewMatrix(1.f);
    ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

    Camera camera(camPosition, camFront);

    float fov = 90.f;
    float nearPlane = 0.1f;
    float farPlane = 1000.f;

    glm::mat4 ProjectionMatrix(1.f);
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferheight, nearPlane, farPlane);
    */

    glm::vec3 camPosition(0.f, 0.f, 2.f);
    glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
    Camera camera = Camera(90, 0.1f, 1000.f, frameBufferWidth, frameBufferheight, glm::vec3 (0.f, 0.f, 2.f), glm::vec3(0.f, 0.f, -1.f));

    glUseProgram(core_program);

    glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getWorldToViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));

    glUseProgram(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //UPDATE INPUT ---
        glfwPollEvents();

        //UPDATE ---
        UpdateInput(window, camera);

        //DRAW ---      
        //clear
        glClear(GL_COLOR_BUFFER_BIT);

        //use a program
        glUseProgram(core_program);

        //Model position, rotation, scale
        rotation.x += 0.02f;
        rotation.y += 0.02f;
        rotation.z += 0.02f;

        //position.z -= 0.03f;

        ModelMatrix = glm::mat4(1.f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f));
        ModelMatrix = glm::translate(ModelMatrix, position);
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
        ModelMatrix = glm::scale(ModelMatrix, scale);
        glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));

        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferheight);

        /*
        glm::mat4 ProjectionMatrix(1.f);
        ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth) / frameBufferheight, nearPlane, farPlane);
        glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
        */

        glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getWorldToViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));

        //activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);

        //bind vertex array object
        glBindVertexArray(VAO);

        //draw
        glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

        //end draw
        glfwSwapBuffers(window);
        glFlush();

        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //END OF PROGRAM
    glfwDestroyWindow(window);
    glfwTerminate();

    //DELETE PROGRAM
    glDeleteProgram(core_program);

    return 0;
}