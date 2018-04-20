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
//        printf("%d\n", key);
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void keyUp(unsigned char key, int x, int y){
        printf("Window class executed, needs to be overwritten\n");
    }

    virtual void specialKeyUp(int key, int x, int y){
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

    void specialKeyUp(int key, int x, int y){
        currentWindow->specialKeyUp(key, x, y);
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
        printf("Help Window loaded\n");
    }

    void execute() override{
//        printf("HELP SCREEN!\n");
        draw();
    }

    void draw() override{
        glPushMatrix();
        glTranslatef(.1, .05, 0);
        drawTexts();

        glPopMatrix();

        drawMainBackground();
    }

    void drawTexts(){
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

    void specialKeyUp(int key, int x, int y) override{

    }
};

class GameGuideWindow: public Window{
    Window* previous_window;    // this window gets loaded after user exits this window
    float text_translate_y= 0.0;     // how much to translate the text in y axis shown in this window, needed for scrolling

public:
    GameGuideWindow(Window* previous_window){
        this->previous_window = previous_window;
    }

    void onWindowLoad() override{
        printf("Game Guide loaded\n");
    }

    void execute() override{
        draw();
    }

    void draw()override {
        glPushMatrix();

        glTranslatef(0, text_translate_y, 0);

        drawTexts();
        glPopMatrix();

        drawMainBackground();
    }

    void drawTexts(){
        glColor3f(.9,.9,.9);
        drawString(0, 0, "Place holder text");
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        if(key == 27){
            // when escape is pressed
            this->w_engine->switchWindow(previous_window);
        }

    }

    void scrollUp(){
        text_translate_y+= 0.03;
    }

    void scrollDown(){
        text_translate_y-= 0.03;
    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);
        if(key == GLUT_KEY_UP){
            scrollUp();
        }
        else if(key == GLUT_KEY_DOWN){
            scrollDown();
        }

    }

    void keyUp(unsigned char key, int x, int y) override{
    }

    void specialKeyUp(int key, int x, int y) override{

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

    void specialKeyUp(int key, int x, int y) override{

    }
};

class GameWindow: public Window{
public:
//    Map game_map = createMapTheVoid();
    Map game_map = createMap_NeedleEye();
//    Map game_map = createMap_Pockets();

    bool key_pressed[300];
    bool SHIFT_IS_PRESSED= false;
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

        this->SHIFT_IS_PRESSED = false;

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
        if(SHIFT_IS_PRESSED){
            // player 1 shift movements
            if(key_pressed['w']){
                player1.shiftUp();
            }
            if(key_pressed['a']){
                player1.shiftLeft();
            }
            if(key_pressed['s']){
                player1.shiftDown();
            }
            if(key_pressed['d']){
                player1.shiftRight();
            }
        }
        else{
            //player 1 movements
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
        }

        if(key_pressed['+']){
            //player 2 shift movements
            if(key_pressed['5']){
                player2.shiftUp();
            }
            if(key_pressed['1']){
                player2.shiftLeft();
            }
            if(key_pressed['2']){
                player2.shiftDown();
            }
            if(key_pressed['3']){
                player2.shiftRight();
            }
        }
        else{
            //player 2 movements
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
        }

        // if the new position of player causes a collision, reset position to prevision value
        // else update actual position to new position
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

    // this method must be invoked by a GLUT "core input callback"
    // else this method of shift key press checking will not work
    // This method is meant to be invoked by keyPress() method (Which is indirectly invoked by a code input callback)
    void updateShiftKeyStatus(){
        // Check if shift is pressed
        this->SHIFT_IS_PRESSED = GLUT_ACTIVE_SHIFT & glutGetModifiers();
    }

    void keyPress(unsigned char key, int x, int y) override{
        // convert upper case characters to lower case character
        if(key >= 'A' && key <= 'Z'){
            key += ' ';
        }

        key_pressed[key]= true;
        updateShiftKeyStatus();

        //TODO: remove, only here for debugging purpose
        if(key == 'x'){
            bullets.clear();
        }
        else if(key == 27){
            // if escape was pressed
            this->w_engine->switchWindow(new ConfirmQuitGameWindow(this));
        }

//        printf("press: %c\n", key);


    }

    void specialKeyPress(int key, int x, int y) override{
//        key_pressed[key]= true;

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

    void specialKeyUp(int key, int x, int y) override{

    }
};

class MainMenuWindow: public Window{
    // options are shown from top to bottom, option at index 0 is shown on top
    vector<char*> menu_options = {"Play", "Controls", "Guide", "Exit"};
    int selected_option_idx = 0;

public:

    MainMenuWindow(){
    }

    void execute() override{
        draw();
    }

    void draw()override {

        glPushMatrix();
        glTranslatef(-2.5,2.5,0);

        drawMenueOptions();
        glPopMatrix();


        drawMainBackground();
    }

    void handleChosenOption(int chosen_option_idx){
//        printf("%d\n", chosen_option_idx);

        if(chosen_option_idx == 0){
            this->w_engine->switchWindow(new GameWindow());
        }
        else if(chosen_option_idx == 1){
            this->w_engine->switchWindow(new HelpScreenWindow(this));
        }
        else if(chosen_option_idx == 2){

        }
        else if(chosen_option_idx == 3){
            exit(0);
        }
    }

    void drawMenueOptions(){
        float LINE_SPACING = 0.25;
        float y = 0;        //level of line


        for(int i= 0, len = menu_options.size(); i<len; i++){
            if(selected_option_idx == i){
                glColor3f(.9,.9,.9);
            }
            else{
                glColor3f(0.2,0.6,.9);
            }

            drawString(0, y, menu_options[i]);
            y-= LINE_SPACING;
        }
    }

    void onWindowLoad() override{
        printf("Main Menu window loaded\n");

    }

    void keyPress(unsigned char key, int x, int y) override{
        // when enter is pressed
        if(key == 13){
//            this->w_engine->switchWindow(new GameWindow());
            handleChosenOption(selected_option_idx);
        }
    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);
        if(key == GLUT_KEY_UP){
            selectOptionAbove();
        }
        else if(key == GLUT_KEY_DOWN){
            selectOptionBellow();
        }

//        printf("%d\n", selected_option_idx);
    }

    void keyUp(unsigned char key, int x, int y) override{

    }

    void specialKeyUp(int key, int x, int y) override{

    }

    void selectOptionAbove(){
        selected_option_idx = (selected_option_idx-1)%menu_options.size();
    }

    void selectOptionBellow(){
        selected_option_idx = (selected_option_idx+1)%menu_options.size();
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

    void specialKeyUp(int key, int x, int y) override{

    }
};


#endif
