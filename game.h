#ifndef GAME_H
#define GAME_H
#include <vector>
#include <deque>
#include <string>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>



// Forward declaration of Pacman and Ghost classes
class Spacecraft;
class Asteroid;
class DrawObjects;

class Game {
private:
        //static Game * instancePtr;
        // Game(){};
    
    Spacecraft& spacecraft;
    Asteroid& asteroid;
    bool replay;
    bool over;
    float square_size;
    float xincrements;
    float yincrements;
    float xincrementa;
    float yincrementa;
    std::vector<std::vector<bool>> bitmap1;
    int time_interval = 0;
    std::vector<DrawObjects*> drawobjects;
    bool moveLeft;
    bool moveRight;
    float x_s;
    float y_s;
    float x_a;
    float y_a;
    // std::vector<float> asteroid positions; (not sure if needed)

public:

//Game(const Game &obj) = delete;
        //static Game *getGame()
       // {
         //   return instancePtr;
      //  }

    //void set(Spacecraft& s);
    // void add(Asteroid& a);

    Game(Spacecraft& s, Asteroid& a);
    virtual ~Game();
    void init();   
    void keyPressed(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void resetGame();
    void keyOperations();
    void gameover();
    void resultsdisplay();
    void Instructionscreen();
    void display();
    void reshape(int width, int height);
    std::vector<bool> keyStates;

    //void updateAsteroids(int value);
    //void renderAsteroids();
};
// Game *Game::instancePtr = new Game();
#endif // GAME_H
