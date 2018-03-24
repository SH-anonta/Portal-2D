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

    }

    virtual void keyPress(unsigned char key, int x, int y){
        printf("%c\n", key);
    }

    virtual void specialKeyPress(int key, int x, int y){
        printf("%d\n", key);
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

    void switchWindow(Window* new_window){
        currentWindow = new_window;
    }
};


class GameWindow: public Window{
public:
    Map game_map = createMapTheVoid();
    Player player1;

    GameWindow(): Window(){
        printf("Game window loaded\n");
        player1= Player(game_map.p1position);
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
        player1.calculateNextPosition();
        player1.updatePosition();
    }

    void drawMap(){
        game_map.draw();
    }

    void drawPlayers(){
        player1.draw();
    }


    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        // when enter is pressed
        if(key == 13){
           printf("Game SCREEN!\n");
        }
        else if(key == 'w'){
            player1.move_up = !player1.move_up;
            player1.move_down = false;
        }
        else if(key == 'a'){
            player1.move_left = !player1.move_left ;
            player1.move_right = false;
        }
        else if(key == 's'){
            player1.move_down = !player1.move_down;
            player1.move_up = false;
        }
        else if(key == 'd'){
            player1.move_right = !player1.move_right ;
            player1.move_left = false;
        }

    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);
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
};





#endif
