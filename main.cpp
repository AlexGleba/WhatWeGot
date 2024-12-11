
//  Won't accept PI without this
#define _USE_MATH_DEFINES

// Include Header Files
#include "Spacecraft.h"
#include "Asteroid.h"
#include "game.h"
#include "ErrorLog.h"
// #include "CMakeLists.txt"

// Define arrow key codes

// Include OpenGL headers
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>


// Include neccessary libraries
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <memory>
#include <cmath>

#define LEFT_ARROW 37
#define RIGHT_ARROW 39

using namespace std;

// Create classes in order to run the game
// Requirements: Draw the Spacecraft, Asteroids

const int window_width = 750;
const int window_height = 750;

class DrawObjects
{
public:
    // Virtual destructor
    virtual ~DrawObjects() {}

    // Pure virtual function for drawing
    virtual void draw() const = 0;
    // Implemented by derived classes
};

// ** SPACECRAFT **
void Spacecraft::draw(float posX, float posY)
{
    // Draw the Spacecraft
    float bodyWidth = 40 * square_size;    // Width of the spacecraft body
    float bodyHeight = 20.0 * square_size; // Height of the spacecraft body
    float finWidth = 6.0 * square_size;    // Width of the fins
    float finHeight = 10.0 * square_size;  // Height of the fins

    // Draw main body of Spacecraft through use of ellipse
    glBegin(GL_POLYGON); // Begin drawing the body as a polygon
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0;          // Convert to radians
        float x = bodyWidth * 0.5 * cos(angle);  // X coordinate of the ellipse
        float y = bodyHeight * 0.5 * sin(angle); // Y coordinate of the ellipse
        glVertex2f(x + posX, y + posY);          // Drawing the vertex at the spacecraft position
    }
   // glEnd();

    // Draw cockpit as small circle at the top of the Spacecraft
    float cockpitradius = 5.0 * square_size;
    glBegin(GL_POLYGON); // Begin drawing the cockpit
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0; // convert to radians
        float x = cockpitradius * cos(angle);
        float y = cockpitradius * sin(angle);
        glVertex2f(x + posX, y + posY + bodyHeight * 0.25); // Position it on top of the Spacecraft
    }
   // glEnd();

    // Set Spacecraft color to white (RGB: 1.0, 1.0, 0.0)
    // All the colors are set to their maximum value 1 to be fully on
    glColor3f(1.0, 1.0, 1.0);

    // Draw the fins as triangles at the bottom of the spacecraft
    glBegin(GL_TRIANGLES); // Begin drawing the fins
    // Drawing the left fin
    glVertex2f(posX - bodyWidth * 0.25, posY - bodyHeight * 0.5); // Bottom left
    glVertex2f(posX - bodyWidth * 0.5, posY - bodyHeight * 0.75); // Bottom left point of the fin
    glVertex2f(posX - bodyWidth * 0.75, posY - bodyHeight * 0.5); // Bottom right

    // Drawing the right fin
    glVertex2f(posX + bodyWidth * 0.25, posY - bodyHeight * 0.5); // Bottom left
    glVertex2f(posX + bodyWidth * 0.5, posY - bodyHeight * 0.75); // Bottom left point of the fin
    glVertex2f(posX + bodyWidth * 0.75, posY - bodyHeight * 0.5); // Bottom right
    glEnd();
}

/*
// Global variable
std::vector<Asteroid> asteroids;
// List of the asteroids

// Generate random number between given range
float getRandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Spawn new asteroid
void spawnAsteroid()
{
    Asteroid newAsteroid;
    newAsteroid.x = getRandomFloat(0, window_width); // Asteroid falls starting from random X position
    newAsteroid.y = window_height;                   // Start at the top of the screen
    newAsteroid.size = getRandomFloat(10.0f, 30.0f); // Asteroid has a random size
    newAsteroid.speed = getRandomFloat(1.0f, 5.0f);  // Asteroid has a random fall speed
    asteroids.push_back(newAsteroid);
}

void updateAsteroids(int value)
{
    // Updating the positions of the asteroids
    for (auto &asteroid : asteroids)
    {
        asteroid.y -= asteroid.speed; // Moving the asteroid down
    }

    // Removing asteroids that are off the screen
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                   [](const Asteroid &asteroid)
                                   {
                                       return asteroid.y + asteroid.size < 0; // Check if asteroid is out of screen
                                   }),
                    asteroids.end());
    // might delete but helps spawn new asteroids
    if (rand() % 50 == 0)
    { // Chance to spawn a new asteroid
        spawnAsteroid();                    
    }
    glutPostRedisplay();  

    glutTimerFunc(20, updateAsteroids, 0); // Call this function again after 20 ms
}
// Drawing the Asteroids
void renderAsteroids()
{
   // glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Render each asteroid
    for (const auto &asteroid : asteroids)
    {
        //asteroid.draw();
        glPushMatrix();
        glTranslatef(asteroid.x, asteroid.y, 0); // Translate to asteroid's position
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 30)
        {
            float angle = i * M_PI / 180;                                       // convert to radians
            glVertex2f(cos(angle) * asteroid.size, sin(angle) * asteroid.size); // Draw a circle for the Asteroid
        }
        glEnd();
        glPopMatrix();
    }

    glutSwapBuffers(); // Swap the buffers to display the new frame

    //glEnd();
}
*/


void Asteroid::draw(float posX, float posY)
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
   for (int i = 0; i < 360; i += 30)
        {
            float angle = i * M_PI / 180;                                       // convert to radians
            glVertex2f(cos(angle) * size, sin(angle) * size); // Draw a circle for the Asteroid
        }
        glEnd(); 
}

// Game
Game::Game(Spacecraft& s, Asteroid& a) : spacecraft(s), asteroid(a), replay(false), over(true), square_size(50.0), xincrements(1.5), yincrements(0), xincrementa(0), yincrementa(0)
{
    // set spacecraft
    // add asteroid
    keyStates.resize(256);

    bitmap1 = {     { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
                    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
}
// Change Game constructor to accept unique_ptr



// Destructor for the game
Game::~Game()
{
    for (auto drawobject : drawobjects)
    {
        delete drawobject;
    }
};

void Game::init()
{
    // Reset all keys states to false so the game can start (256 for broad, generic range)
    keyStates.resize(256, false);
    for (int i = 0; i < 256; i++)
    {
        keyStates[i] = false;
    }
}

void Game::resetGame()
{
    // start the game over by resetting over to false
    over = false;

    // reset increments back to original state
    xincrements = 1.5;
    yincrements = 0;
    xincrementa = 0;
    yincrementa = 0;

    // Reset keys back to original state
    for (int i = 0; i < 256; i++)
    {
        keyStates[i] = false;
    }
}

void Game::keyOperations()
{
    // Update Spacecraft's movement according to keys pressed

    x_s = (1.5 + xincrements) * square_size;
    y_s = (1.5 + yincrements) * square_size;

    if (keyStates[LEFT_ARROW])
    {
        xincrements -= 1.5;
    }

    if (keyStates[RIGHT_ARROW])
    {
        xincrements += 1.5;
    }

    if (keyStates[' '])
    {
        // Reset the game if desiring to replay and the game is over
        if (!replay && over)
        {
            resetGame();
            replay = true;
        }
        else if (replay && over)
        {
            replay = false;
        }
    }

    // Reset the game when r is pressed
    if (keyStates['r'])
    {
        resetGame();
        replay = true;
    }
}

// Method to check if the game is over
void Game::gameover()
{
    cout << x_s << ',' << y_s << ',' << x_a << ',' << y_a << endl;
    static constexpr float square_size = 50.0;
    float bodyWidth = 40 * square_size;    // Width of the spacecraft body
    float bodyHeight = 20.0 * square_size; // Height of the spacecraft body
    float finWidth = 6.0 * square_size;    // Width of the fins
    float finHeight = 10.0 * square_size;  // Height of the fins


    int number_x = x_a;                              // Check this number
    int lowerbound_x = x_s - (bodyWidth + finWidth); // Lower bound of x range
    int upperbound_x = x_s + (bodyWidth + finWidth); // Upper bound of x range

    int number_y;                                      // Check this number
    int lowerbound_y = y_s - (bodyHeight + finHeight); // Lower bound of y range
    int upperbound_y = y_s + (bodyHeight + finHeight); // Upper bound of y range

    if (number_x >= lowerbound_x && number_x <= upperbound_x)
    {
        if (number_y >= lowerbound_y && number_y <= upperbound_y)
        {
            cout << "Game Over: Number is between the bounds." << endl;
            over = true;
            return;
        }
    }
    else
    {
        cout << "Game continues: Number outside the bounds." << endl;
    }

    if (time_interval == 60) // Allow game to go on for a minute
    {
        over = true;
        return;
    }
}

// Display the results of the game at the end
void Game::resultsdisplay()
{
    // Clear the screen by showing a black screen
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (time_interval == 60)
    {
        // Display Message when the Game is Won
        const char *title = "*************************************";
        glRasterPos2f(170, 250);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "CONGRATULATIONS YOU WON SPACECRAFT! ";
        glColor3f(1, 1, 1);
        glRasterPos2f(150, 300);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "*************************************";
        glRasterPos2f(170, 350);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "In order to restart the game, press the letter r on the keyboard.";
        glRasterPos2f(170, 550);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *title++);
    }
    else
    {
        // Display Message when the Game is Lost
        const char *title = "*************************";
        glRasterPos2f(230, 250);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "SORRY, YOU LOST THE GAME SPACECRAFT";
        glColor3f(1, 1, 1);
        glRasterPos2f(210, 300);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "*************************";
        glRasterPos2f(230, 350);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "In order to restart the game, press the letter r on the keyboard.";
        glRasterPos2f(170, 550);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *title++);
    }

    glFlush();
}

// instructions screen messages
void Game::Instructionscreen()
{
    glClearColor(0, 1.0, 1.0, 1.0); // make the screen a cyan color
    glClear(GL_COLOR_BUFFER_BIT);

    // Set text color to white
    glColor3f(1.0, 1.0, 1.0);

    // Title Section
    const char *title = "*************************************";
    glRasterPos2f(150, 500);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "Asteroid Avoider";
    glRasterPos2f(240, 550);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "*************************************";
    glRasterPos2f(150, 600);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    // Instruction Text Section
    title = "To move the spacecraft, use the left and right arrow keys";
    glRasterPos2f(150, 450);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "Press the space key to begin!";
    glRasterPos2f(200, 400);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "To reset the game, press the r key.";
    glRasterPos2f(200, 350);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    glFlush();
}

void Game::display()
{
    // if the game starts with 1 second, set over to false
    if (this->time_interval == 1)
    {
        this->over = false;
    }

    this->keyOperations();
    glClear(GL_COLOR_BUFFER_BIT);
    this->gameover();

   // updateAsteroids(0);
   // renderAsteroids();

    // If the player is replaying then draw the asteroid and spacecraft again
    if (this->replay)
    {
        if (!this->over)
        {

            this->spacecraft.draw(1.5 + this->xincrements, 1.5 + this->yincrements);
           // this->asteroid.draw(1.5 + this->xincrementa, 1.5 + this->yincrementa);
        }
        else
        {
            this->resultsdisplay();
        }
    }
    else
    {
        this->Instructionscreen();
    }
    glutSwapBuffers();
}

// Method to reshape the game if the screen size changes
void Game::reshape(int w_resize, int h_resize)
{

    // Switch to the projection matrix mode
    glMatrixMode(GL_PROJECTION);

    // Reset the projection matrix to the identity matrix
    glLoadIdentity();

    // Set the viewport to match the new window size
    glViewport(0, 0, (GLsizei)w_resize, (GLsizei)h_resize);

    // Define the orthographic projection matrix with new window dimensions
    glOrtho(0, 750, 750, 0, -1.0, 1.0);

    // Switch back to the modelview matrix mode
    glMatrixMode(GL_MODELVIEW);
}

// unique pointer for Spacecraft object
std::unique_ptr<Spacecraft> spacecraftPtr(new Spacecraft);
std::unique_ptr<Asteroid> asteroidPtr(new Asteroid);

Game game(*spacecraftPtr,*asteroidPtr);


void displaycallback() {game.display();}
void reshapecallback(int width, int height) {game.reshape(width,height);}

void keypressedcallback(unsigned char key, int x, int y)
{
    std::cout << "Pressed key: " << static_cast<int>(key) << std::endl;
    game.keyStates[key] = true;
}

void keyUpCallback(unsigned char key, int x, int y) { game.keyStates[key] = false; }
//{ Game::getGame()->keyStates[key] = false; }
void specialKeyPressedCallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        //Game::getGame()->keyStates[LEFT_ARROW] = true;
        game.keyStates[LEFT_ARROW] = true;
        break;

    case GLUT_KEY_RIGHT:
        //Game::getGame()->keyStates[RIGHT_ARROW] = true;
        game.keyStates[RIGHT_ARROW] = true;
        break;
    }
}

void specialkeyupcallback(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
        //Game::getGame()->keyStates[LEFT_ARROW] = false;
        game.keyStates[LEFT_ARROW] = false;
        break;

    case GLUT_KEY_RIGHT:
         game.keyStates[RIGHT_ARROW] = false;
        //Game::getGame()->keyStates[RIGHT_ARROW] = false;
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering for smooth rendering
    glutInitWindowSize(750, 750);                // Set the window size
    glutCreateWindow("Asteroids Avoiders");    // Create the window

    // Set up OpenGL settings
    glClearColor(0.0, 0.0, 0.0, 1.0);                      // Set background color (black)
    glOrtho(0, window_width, 0, window_height, -1.0, 1.0); // Set 2D orthogonal projection

    // Register the display function and handle input
    
    //glutDisplayFunc(display);           // Display callback for rendering
    //glutKeyboardFunc(keyPressed);       // Regular key press callback
    //glutSpecialFunc(specialkeypressed); // Special key press callback
    //glutTimerFunc(16, update, 0);       // Start the update loop (60 FPS)


     // Set GLUT callbacks
     
    glutKeyboardFunc(keypressedcallback);
    glutKeyboardUpFunc(keyUpCallback);
    glutDisplayFunc(displaycallback);
    glutReshapeFunc(reshapecallback);
    glutIdleFunc(displaycallback);
    glutSpecialFunc(specialKeyPressedCallback);
    glutSpecialUpFunc(specialkeyupcallback);

    // Spawn the first asteroid
  //  spawnAsteroid();

    // Initialize game
    game.init(); 

    //glutTimerFunc(20, updateAsteroids, 0); // Update asteroids every 20 ms
    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}

