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

    GameWindow(): Window(){
        printf("Game window loaded\n");
    }

    void execute() override{
        drawMap();
    }

    void drawMap(){

    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        // when enter is pressed
        if(key == 13){
            printf("Game SCREEN!\n");
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
