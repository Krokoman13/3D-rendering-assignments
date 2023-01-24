#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ShaderUtil.h"

/**
 * Basic demo of rendering a triangle in OpenGL through the new programmable pipeline.
 * In a real life example, this code should include error checking and refactor into classes/functions.
 * In addition VAO's are missing.
 */

int main () {
    //Open SFML Window == Valid OpenGL Context
    sf::Window window(
        sf::VideoMode (800, 800),       //800 x 600 x 32 bits pp
        "OpenGL Window",                //title
        sf::Style::Default,             //Default, Fullscreen, Titlebar, etc
        sf::ContextSettings (
            24,                         //24 bits depth buffer, important for 3D!
            0,                          //no stencil buffer
            0,                          //no anti aliasing
            3,                          //requested major OpenGL version
            3                           //requested minor OpenGL version
        )
    );
	window.setVerticalSyncEnabled(true);

    //initialize glew to load all available opengl functions/extensions
    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        std::cout << "Could not initialize GLEW, byeeee!" << std::endl;
        return -1;
    }

	//Create the shader program
	GLuint chessBoard = ShaderUtil::createProgram("vertexshader.vert", "checkerboardShader.frag");
	GLuint circChessBoard = ShaderUtil::createProgram("vertexshader.vert", "roundCheckerboardShader.frag");

	//declare the data to upload
	const GLfloat vertices[] = {
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		0.5f, 0.5f, 0,

		-0.5f, -0.5f, 0,
		-0.5f, 0.5f, 0,
		0.5f, 0.5f, 0
	};

	//create a handle to the buffer
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	sf::Clock clock;

    glClearColor(0, 0, 0, 1);

	float scaleSpeed = 0;
	float scale = 1;
	bool downScaling = false;
	float rotationSpeed = 0;
	float rotation = 0;

    while (window.isOpen()) {

		glClear( GL_COLOR_BUFFER_BIT );

		float elapsedTime = clock.getElapsedTime().asSeconds();
		float mouseY = (-sf::Mouse::getPosition(window).y + 800);
		float mouseX = sf::Mouse::getPosition(window).x;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) scaleSpeed += 0.001f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) scaleSpeed -= 0.001f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rotationSpeed += 0.001f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rotationSpeed -= 0.001f;

		rotation += rotationSpeed;

		if (scaleSpeed < 0) scaleSpeed = 0;
		if (downScaling) scale -= scaleSpeed;
		else scale += scaleSpeed;

		if (scale < 0.1f) downScaling = false;
		else if (scale > 1.9f) downScaling = true;

		//============ RECT CHESS BOARD ===============
        glUseProgram (chessBoard);

		//offset
		glUniform2f(glGetUniformLocation(chessBoard, "offset"), 0.5f*cos(elapsedTime), 0.5f*sin(elapsedTime));
		glUniform2f(glGetUniformLocation(chessBoard, "u_resolution"), window.getSize().x, window.getSize().y);
		glUniform2f(glGetUniformLocation(chessBoard, "u_mouse"), mouseX, mouseY);
		glUniform1f(glGetUniformLocation(chessBoard, "scale"), scale);
		glUniform1f(glGetUniformLocation(chessBoard, "rotation"), rotation);
		glUniform1f(glGetUniformLocation(chessBoard, "rows"), 8);
		glUniform1f(glGetUniformLocation(chessBoard, "colums"), 10);

        //get index for the attributes in the shader
		GLint vertexIndexRectChess = glGetAttribLocation(chessBoard, "vertex");
		glEnableVertexAttribArray(vertexIndexRectChess);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glVertexAttribPointer(vertexIndexRectChess, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray (vertexIndexRectChess);

		//============ ROUND CHESS BOARD ===============
		glUseProgram(circChessBoard);

		glUniform2f(glGetUniformLocation(circChessBoard, "offset"), -0.5f * cos(elapsedTime), -0.5f * sin(elapsedTime));
		glUniform2f(glGetUniformLocation(circChessBoard, "u_resolution"), window.getSize().x, window.getSize().y);
		glUniform2f(glGetUniformLocation(circChessBoard, "u_mouse"), mouseX, mouseY);
		glUniform1f(glGetUniformLocation(circChessBoard, "scale"), scale);
		glUniform1f(glGetUniformLocation(circChessBoard, "rotation"), rotation);
		glUniform1f(glGetUniformLocation(circChessBoard, "layers"), 6);
		glUniform1f(glGetUniformLocation(circChessBoard, "sections"), 8);

		GLint vertexIndexRotChess = glGetAttribLocation(circChessBoard, "vertex");
		glEnableVertexAttribArray(vertexIndexRotChess);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glVertexAttribPointer(vertexIndexRotChess, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(vertexIndexRotChess);

        //display it
        window.display();

		//empty the event queue
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
        }
    }

    return 0;
}


