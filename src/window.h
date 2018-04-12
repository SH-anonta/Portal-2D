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
        currentWindow ->w_engine = this;    // very important
    }
};


class HelpScreenWindow: public Window{
public :

    Window* previous_window;    // this window gets loaded after user exits this window

    HelpScreenWindow(Window* previous_window): Window(){
        this->previous_window = previous_window;
    }

    void execute() override{


//        printf("HELP SCREEN!\n");
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);

        // when enter is pressed
//        if(key == 13){
//            printf("Help: Enter Key pressed\n");
//            printf("->> %d\n", previous_window);
//        }
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
    bool key_pressed[300];

    Player player1;
    Player player2;

//    Portal portal2= Portal(-1,0, Up);
//    Portal portal1= Portal(-1,-2.8, Down);
    Portal portal1= Portal(-2.89,-1, Left);
    Portal portal2= Portal(3,-1, Right);


    list<Bullet> bullets;

    GameWindow(): Window(){
        printf("Game window loaded\n");
        player1= Player(game_map.p1position);
        player2= Player(game_map.p2position);
        player2.color = Color(.7,.5, .7);

        portal1.setLinkedPortal(&portal2);
        portal2.setLinkedPortal(&portal1);

        for(int i = 0; i<300; i++){
            key_pressed[i]= false;
        }
    }

    void execute() override{
        drawHealthBars();

        updatePlayerPositions();
        drawPlayers();

        doTeleportations();
        drawPortals();

        drawMap();

        spawnNewBullets();
        updateBulletPositions();
        Bullet::drawBullets(bullets);   // draw all bullets at once
    }

    void doTeleportations(){

    }

    void drawPortals(){
        portal1.draw();
        portal2.draw();
    }

    void drawHealthBars(){

        float p1_bar_width = (float)player1.health / (float)MAX_PLAYER_HEALTH;
        float p2_bar_width = (float)player2.health / (float)MAX_PLAYER_HEALTH;

        float thickness = .15;

        glEnable(GL_BLEND);

        glLineWidth(1);
        glColor4f(.9,.9,.9, .5);

        // player 1 health bar
        glPushMatrix();
        glTranslatef(-2.7, 2.7, 0);
        glScalef(2.5,1,1);

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
        glTranslatef(0.13, 2.7, 0);

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


        if(!game_map.detectCollision(player1)){
            player1.updatePosition();
        }
        else{
            player1.resetNextPosition();
        }

        if(!game_map.detectCollision(player2)){
            player2.updatePosition();
        }
        else{
            player2.resetNextPosition();
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

            portal2.teleportBullet(*bullet);
            portal1.teleportBullet(*bullet);

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
