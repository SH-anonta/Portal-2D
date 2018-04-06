#ifndef WINDOW_H
#define WINDOW_H

class WindowEngine;
class Window;
class GameWindow;

class Window{
public:
    WindowEngine* w_engine;

    Window(){
//        this->w_engine = w_engine;
    }

    virtual void execute(){
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void keyPress(unsigned char key, int x, int y){
        printf("%c\n", key);
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void specialKeyPress(int key, int x, int y){
        printf("%d\n", key);
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void keyUp(unsigned char key, int x, int y){
        printf("Window class executed, needs to be overwritten\n");
    }
};


class WindowEngine{
public:
    Window* currentWindow;

    WindowEngine(Window* initail_window){
        currentWindow = initail_window;
        currentWindow->w_engine = this;
    }

    void execute(){
        currentWindow->execute();
    }

    void keyPress(unsigned char key, int x, int y){
        currentWindow->keyPress(key, x, y);
    }

    void specialKeyPress(int key, int x, int y){
        currentWindow->specialKeyPress(key, x, y);
    }

    void keyUp(unsigned char key, int x, int y){
        currentWindow->keyUp(key, x, y);
    }

    void switchWindow(Window* new_window){
        currentWindow = new_window;
    }
};


class GameWindow: public Window{
public:
    Map game_map = createMapTheVoid();
    bool key_pressed[300];

    Player player1;
    Player player2;

    GameWindow(): Window(){
        printf("Game window loaded\n");
        player1= Player(game_map.p1position);
        player2= Player(game_map.p2position);
        player2.color = Color(.7,.5, .7);

        for(int i = 0; i<300; i++){
            key_pressed[i]= false;
        }
    }

    void execute() override{

//        if(player1.move_up){
//            SS
//        }

        drawMap();
        updatePlayerPositions();
        drawPlayers();
    }

    void updatePlayerPositions(){
//        printf("%f %f\n", player1.position.x, player1.next_position.x);

//        printf(key_pressed[key] ? "true" : "false");

        if(key_pressed['w']){
            player1.moveUp();
        }
        if(key_pressed['a']){
            player1.moveLeft();
        }
        if(key_pressed['s']){
            player1.moveDown();
        }
        if(key_pressed['d']){
            player1.moveRight();
        }

        if(key_pressed['5']){
            player2.moveUp();
        }
        if(key_pressed['1']){
            player2.moveLeft();
        }
        if(key_pressed['2']){
            player2.moveDown();
        }
        if(key_pressed['3']){
            player2.moveRight();
        }

        player1.updatePosition();
        player2.updatePosition();
    }

    void drawMap(){
        game_map.draw();
    }

    void drawPlayers(){
        player1.draw();
        player2.draw();
    }


    void keyPress(unsigned char key, int x, int y) override{
        // convert upper case characters to lower case character
        if(key >= 'A' && key <= 'Z'){
            key += ' ';
        }

        key_pressed[key]= true;

        printf("press: %c\n", key);

        if(key == 13){
        // when enter is pressed
           printf("Game SCREEN!\n");
        }
//        else if(key == 'w'){
//            player1.moveUp();
//        }
//        else if(key == 'a'){
//            player1.moveLeft();
//        }
//        else if(key == 's'){
//            player1.moveDown();
//        }
//        else if(key == 'd'){
//            player1.moveRight();
//        }

//        glutPostRedisplay();
    }

    void specialKeyPress(int key, int x, int y) override{

//        printf("-> %d\n", key);

        key_pressed[key]= true;
//        if(key == GLUT_KEY_UP){
//            player2.moveUp();
//        }
//        else if(key == GLUT_KEY_DOWN){
//            player2.moveDown();
//        }
//        else if(key == GLUT_KEY_LEFT){
//            player2.moveLeft();
//        }
//        else if(key == GLUT_KEY_RIGHT){
//            player2.moveRight();
//        }
        if(key == GLUT_KEY_F12){
            printf("TODO: Load Show help screen\n");
            // todo, show help screen
        }

//        glutPostRedisplay();
    }

    void keyUp(unsigned char key, int x, int y) override{
        printf("Release: %c\n", key);
        key_pressed[key]= false;
    }
};

class SplashScreenWindow:public Window{
public:

    SplashScreenWindow(): Window(){

    }

    void execute() override{
//        printf("SPLASH SCREEN!\n");
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        // when enter is pressed
        if(key == 13){
            printf("Splash: Enter Key pressed\n");
            this->w_engine->switchWindow(new GameWindow());
        }
    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);
    }

    void keyUp(unsigned char key, int x, int y) override{

    }
};





#endif
