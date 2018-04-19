#ifndef WINDOW_H
#define WINDOW_H

class WindowEngine;
class Window;
class HelpScreenWindow;
class GameWindow;

class Window{
public:
    WindowEngine* w_engine;

    Window(){
//        this->w_engine = w_engine;
    }

    virtual void onWindowLoad(){
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void execute(){
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void draw(){
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
        currentWindow->onWindowLoad();
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
        currentWindow->w_engine = this;    // very important
        currentWindow->onWindowLoad();
    }
};


class HelpScreenWindow: public Window{
public :

    Window* previous_window;    // this window gets loaded after user exits this window

    HelpScreenWindow(Window* previous_window): Window(){
        this->previous_window = previous_window;
    }

    void onWindowLoad() override{
        printf("Help screen loaded\n");
    }

    void execute() override{
//        printf("HELP SCREEN!\n");

        glPushMatrix();
        glTranslatef(.1, .05, 0);
        drawTexts();

        glPopMatrix();
        drawMainBackground();
    }

    void draw()override {

    }

    void drawTexts(){
        ///  printf("HELP SCREEN!\n");

        glPushMatrix();
        glTranslatef(-2.9, 0,0);

        drawString(0, 2.6, "Controls");

        glColor3f(.9,.9,.9);
        drawString(0, 2.3, "Action");
        drawString(2.5, 2.3, "Player1");
        drawString(5,2.3,  "Player2");

        glColor3f(0.2,0.6,.9);

        drawString(0, 2.0, "Move Up");
        drawString(2.5, 2.0,"W");
        drawString(5,2.0,  "5");
        drawString(0, 1.7, "MoveDown");
        drawString(2.5,1.7," S");
        drawString(5,1.7,"2");
        drawString(0, 1.4, "MoveLeft");
        drawString(2.5,1.4,"A");
        drawString(5, 1.4,"1");
        drawString(0, 1.1, "Move Right");
        drawString(2.5,1.1,"D");
        drawString(5,1.1,"3");
        drawString(0, 0.8, "Shoot");
        drawString(2.5,0.8,"<Space>");
        drawString(5,0.8,"0");
        drawString(0, 0.5, "Open Portal 1");
        drawString(2.5,0.5," Q");
        drawString(5,0.5,"4");
        drawString(0, 0.3, "Pause game");
        drawString(2.5,0.3,"Esc");
        drawString(5,0.3,"Esc");
        drawString(0, 0.0, "Help screeen");
        drawString(2.5,0.0,"F12");
        drawString(5,0.0,"F12");

        glPopMatrix();
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        if(key == 27){
            // when escape is pressed
            this->w_engine->switchWindow(previous_window);
        }

    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);

    }

    void keyUp(unsigned char key, int x, int y) override{
    }

};

class ConfirmQuitGameWindow: public Window{
    Window* previous_window;
public:

    ConfirmQuitGameWindow(Window* previous_window){
        this->previous_window = previous_window;
    }

    void execute() override{
        setColor(DEFAULT_TEXT_COLOR);
        drawString(-.4,0, "Quit Game?", GLUT_BITMAP_TIMES_ROMAN_24);

        // transparent
//        glColor4f(0.1, 0.1, 0.1, .8);
//        glBegin(GL_QUADS);
//        plot(-4, -4);
//        plot(4, -4);
//        plot(4, 4);
//        plot(-4, 4);
//        glEnd();

//        this->previous_window->draw();
        drawMainBackground();
    }

    void draw()override {

    }

    void onWindowLoad() override{
        printf("Confirm quit game window loaded\n");
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);
        if(key == 27){
            // when escape is pressed
            this->w_engine->switchWindow(previous_window);
        }

    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);
    }

    void keyUp(unsigned char key, int x, int y) override{
    }
};

class GameWindow: public Window{
public:
//    Map game_map = createMapTheVoid();
    Map game_map = createMap_NeedleEye();
//    Map game_map = createMap_Pockets();

    bool key_pressed[300];

    Player player1;
    Player player2;

//    Portal portal1= Portal(-1,.1, Down);
    Portal portal1= Portal(-1,-2.8, Down);
    Portal portal2= Portal(-1,0, Up);
//    Portal portal3= Portal(-1.2, .1, Down);
    Portal portal3= Portal(-2.89,-1, Left);
    Portal portal4= Portal(3,-1, Right);


    list<Bullet> bullets;

    GameWindow(): Window(){
        printf("Game window loaded\n");
        player1= Player(game_map.p1position);
        player2= Player(game_map.p2position);
        player2.color = Color(.7,.5, .7);

        portal1.setLinkedPortal(&portal4);
        portal2.setLinkedPortal(&portal3);
        portal3.setLinkedPortal(&portal2);
        portal4.setLinkedPortal(&portal1);

        portal1.color = Color(.9, .7, .1);
        portal2.color = Color(.7, .4, .3);
        portal3.color = Color(.7, .4, .7);
        portal4.color = Color(.8, .5,.3);

        for(int i = 0; i<300; i++){
            key_pressed[i]= false;
        }
    }

    void onWindowLoad() override{
        printf("Game window loaded\n");

        for(int i = 0; i<300; i++){
            key_pressed[i]= false;
        }
    }

    void execute() override{
        updateGame();
        drawGame();
    }

    void draw()override {
        drawGame();
    }

    void updateGame(){
        updatePlayerPositions();
        spawnNewBullets();
        updateBulletPositions();
    }

    void drawGame(){
        drawPlayers();
        drawPortals();
        Bullet::drawBullets(bullets);   // draw all bullets at once
        drawHealthBars();
        drawMap();
    }


    void drawPortals(){
        portal1.draw();
        portal2.draw();
        portal3.draw();
        portal4.draw();
    }

    void drawHealthBars(){

        float thickness = .05;
        float p1_bar_width = (float)player1.health / (float)MAX_PLAYER_HEALTH;
        float p2_bar_width = (float)player2.health / (float)MAX_PLAYER_HEALTH;

        glLineWidth(1);
        glColor4f(.9,.9,.9, .9);

        {

        // player 1 health bar
        glPushMatrix();
        glTranslatef(-2.7, 2.7, 0);
        glScalef(2.5,1,1);

        drawString(-0.05,0, "P1", GLUT_BITMAP_HELVETICA_12);

        glBegin(GL_QUADS);
        plot(0,0);
        plot(p1_bar_width,0);
        plot(p1_bar_width, thickness);
        plot(0, thickness);
        glEnd();

        glBegin(GL_LINE_LOOP);
        plot(0,0);
        plot(1,0);
        plot(1, thickness);
        plot(0, thickness);
        glEnd();
        glPopMatrix();

        // player 2 health bar
        glPushMatrix();
        glScalef(2.5,1,1);
        glTranslatef(0.11, 2.7, 0);

        drawString(1.01,0, "P2", GLUT_BITMAP_HELVETICA_12);

        glBegin(GL_QUADS);
        plot(1-p2_bar_width,0);
        plot(1,0);
        plot(1, thickness);
        plot(1-p2_bar_width, thickness);
        glEnd();

        glBegin(GL_LINE_LOOP);
        plot(0,0);
        plot(1,0);
        plot(1, thickness);
        plot(0, thickness);
        glEnd();

        glPopMatrix();
        }

    }

    void updatePlayerPositions(){

        //player 1 keys
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

        //player 2 keys
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


        if(game_map.detectCollision(player1)){
            player1.resetNextPosition();
        }
        else{
            player1.updatePosition();
        }

        if(game_map.detectCollision(player2)){
            player2.resetNextPosition();
        }
        else{
            player2.updatePosition();
        }

    }

    void spawnNewBullets(){
        if(key_pressed[' '] && player1.reloadTimeIsOver()){
            Bullet new_bullet =  player1.shootBullet();
            bullets.push_back(new_bullet);
        }

        if(key_pressed['0'] && player2.reloadTimeIsOver()){
            Bullet new_bullet =  player2.shootBullet();
            bullets.push_back(new_bullet);
        }
    }

    void updateBulletPositions(){
//        printf("len: %d\n", bullets.size());

        auto bullets_end = bullets.end();
        auto bullet =  bullets.begin();

        while(bullet != bullets_end){

            bullet->updatePosition();

            portal1.teleportBullet(*bullet);
            portal2.teleportBullet(*bullet);
            portal3.teleportBullet(*bullet);
            portal4.teleportBullet(*bullet);

            if(player1.detectHit(*bullet)){
                bullet= bullets.erase(bullet);
                player1.takeDamage();
            }
            else if(player2.detectHit(*bullet)){
                bullet= bullets.erase(bullet);
                player2.takeDamage();
            }
            else if(game_map.detectCollision(*bullet)){
                bullet= bullets.erase(bullet);
            }
            else{
                bullet++;
            }
        }
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
//        if(key == 13){
//            printf("GW: Enter Key pressed\n");
//            printf("->> %d\n", this);
//        }

        //TODO: remove, only here for debugging purpose
        if(key == 'x'){
            bullets.clear();
        }
        else if(key == 27){
            // if escape was pressed
            this->w_engine->switchWindow(new ConfirmQuitGameWindow(this));
        }
        key_pressed[key]= true;
//        printf("press: %c\n", key);


    }

    void specialKeyPress(int key, int x, int y) override{

        if(key == GLUT_KEY_F12){
            this->w_engine->switchWindow(new HelpScreenWindow(this));
        }

    }

    void keyUp(unsigned char key, int x, int y) override{
//        printf("Release: %c\n", key);

        if(key >= 'A' && key <= 'Z'){
            key += ' ';
        }
        key_pressed[key]= false;
    }
};

class SplashScreenWindow:public Window{
public:

    // final rgb color to achieve
    float final_r= 0.2;
    float final_g= 0.6;
    float final_b= 0.9;

    float r= 0, g= 0,b= 0;   // current color intensity, starts at black

    int current_iteration = 0;
    const int TOTAL_ITERATIONS= 70;    // how long the animation will take to complete

    // how much to increment on each iteration
    const float ri= final_r/TOTAL_ITERATIONS;   // text color
    const float gi= final_g/TOTAL_ITERATIONS;   // text color
    const float bi= final_b/TOTAL_ITERATIONS;   // text color

    SplashScreenWindow(): Window(){

    }

    void execute() override{
//        printf("SPLASH SCREEN!\n");

        if(current_iteration < TOTAL_ITERATIONS){
           r+= ri;
           g+= gi;
           b+= bi;

           current_iteration++;
        }
        else{
            glColor3f(1,1,1);
            drawString(-.4,-2.5, "<PRESS ENTER>", GLUT_BITMAP_9_BY_15);
        }

        glColor3f(r,g,b);
        glPushMatrix();
        glTranslatef(-.4,0,1);
        drawString(0,0, "PORTAL  2D", GLUT_BITMAP_TIMES_ROMAN_24);
        glPopMatrix();

        drawMainBackground();
    }

    void draw()override {

    }

    void onWindowLoad() override{
        printf("Splash screen window loaded\n");

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
