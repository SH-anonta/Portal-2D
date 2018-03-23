#ifndef WINDOW_H
#define WINDOW_H

class WindowEngine;

class Window{
public:
    WindowEngine* w_engine;

    Window(WindowEngine* w_engine){
        this->w_engine = w_engine;
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

class SplashScreenWindow:public Window{
public:

    SplashScreenWindow(WindowEngine* w_engine): Window(w_engine){

    }

    void execute(){
//        printf("SPLASH SCREEN!\n");
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        // when enter is pressed
        if(key == 13){
            SS
        }
    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);


    }
};


class WindowEngine{
public:
    Window* currentWindow;

    WindowEngine(){
        currentWindow = new SplashScreenWindow(this);
    }

    void execute(){

    }

    void keyPress(unsigned char key, int x, int y){
        currentWindow->keyPress(key, x, y);
        printf("%c\n", key);
    }

    void specialKeyPress(int key, int x, int y){
        currentWindow->specialKeyPress(key, x, y);
        printf("%d\n", key);
    }
};


#endif
