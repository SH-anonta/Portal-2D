#ifndef WINDOW_H
#define WINDOW_H

class WindowEngine;
class Window;
class HelpScreenWindow;
class GameWindow;


Window* createConfirmQuitWIndow(Window* previous_window);
Window* createGameOverWindow(string message);

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
        double size_d=-.2;

        glPushMatrix();
        glTranslatef(-2.9, 0,0);

        glColor3f(.9,.9,.9);
        drawString(0, 2.6, "Controls");


        drawString(0, 2.4+size_d, "Action",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5, 2.4+size_d, "Player1",GLUT_BITMAP_HELVETICA_18);
        drawString(5,2.4+size_d,  "Player2",GLUT_BITMAP_HELVETICA_18);

        glColor3f(0.2,0.6,.9);

        drawString(0, 2.0+size_d, "Move Up",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5, 2.0+size_d,"W",GLUT_BITMAP_HELVETICA_18);
        drawString(5,2.0+size_d,  "5",GLUT_BITMAP_HELVETICA_18);
        drawString(0, 1.7+size_d, "Move Down",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,1.7+size_d,"S",GLUT_BITMAP_HELVETICA_18);
        drawString(5,1.7+size_d,"2",GLUT_BITMAP_HELVETICA_18);
        drawString(0, 1.4+size_d, "Move Left",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,1.4+size_d,"A",GLUT_BITMAP_HELVETICA_18);
        drawString(5, 1.4+size_d,"1",GLUT_BITMAP_HELVETICA_18);
        drawString(0, 1.1+size_d, "Move Right",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,1.1+size_d,"D",GLUT_BITMAP_HELVETICA_18);
        drawString(5,1.1+size_d,"3",GLUT_BITMAP_HELVETICA_18);
        drawString(0, 0.8+size_d, "Shoot",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,0.8+size_d,"<Space>",GLUT_BITMAP_HELVETICA_18);
        drawString(5,0.8+size_d,"0",GLUT_BITMAP_HELVETICA_18);
        drawString(0, 0.5+size_d, "Open Portal 1",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,0.5+size_d," Q",GLUT_BITMAP_HELVETICA_18);
        drawString(5,0.5+size_d,"4",GLUT_BITMAP_HELVETICA_18);

        drawString(0, 0.3+size_d, "Open Portal 2",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,0.3+size_d," E",GLUT_BITMAP_HELVETICA_18);
        drawString(5,0.3+size_d,"6",GLUT_BITMAP_HELVETICA_18);


        drawString(0, 0.0+size_d, "Shift Up",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,0.0+size_d,"Shift+W ",GLUT_BITMAP_HELVETICA_18);
        drawString(5,0.0+size_d,"Enter+5",GLUT_BITMAP_HELVETICA_18);

        drawString(0, -0.3+size_d, "Shift Down",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,-0.3+size_d,"Shift+S ",GLUT_BITMAP_HELVETICA_18);
        drawString(5,-0.3+size_d,"Enter+2",GLUT_BITMAP_HELVETICA_18);

       drawString(0, -0.6+size_d, "Shift Left",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,-0.6+size_d,"Shift+A ",GLUT_BITMAP_HELVETICA_18);
        drawString(5,-0.6+size_d,"Enter+1",GLUT_BITMAP_HELVETICA_18);

        drawString(0, -0.9+size_d, "Shift Right",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,-0.9+size_d,"Shift+D",GLUT_BITMAP_HELVETICA_18);
        drawString(5,-0.9+size_d,"Enter+3",GLUT_BITMAP_HELVETICA_18);


       drawString(0, -1.2+size_d, "Pause game",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,-1.2+size_d,"Esc",GLUT_BITMAP_HELVETICA_18);
        drawString(5,-1.2+size_d,"Esc",GLUT_BITMAP_HELVETICA_18);

        drawString(0, -1.5+size_d, "Help screeen",GLUT_BITMAP_HELVETICA_18);
        drawString(2.5,-1.5+size_d,"F12",GLUT_BITMAP_HELVETICA_18);
        drawString(5,-1.5+size_d,"F12",GLUT_BITMAP_HELVETICA_18);

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



const Color P1PORTAL1_COLOR = Color(1.000,0.592,0.439);
const Color P1PORTAL2_COLOR = Color(0.439,0.839,1.000);
const Color P2PORTAL1_COLOR = Color(0.737,0.169,0.078);
const Color P2PORTAL2_COLOR = Color(0.016,0.098,0.400);

class GameWindow: public Window{
public:
    Map game_map;

    bool key_pressed[300];
    bool SHIFT_IS_PRESSED= false;
    BasePlayer* player1;
    BasePlayer* player2;

    // these flags are used to prevent a player getting wrapped by "FallingIntoPit" decorator multiple times
    bool player1_is_alive= true;
    bool player2_is_alive= true;


    Portal p1Portal1= Portal(-2.9, 0, Left);
    Portal p1Portal2= Portal(0,-2.8, Down);
    Portal p2Portal1= Portal(3, 0, Right);
    Portal p2Portal2= Portal(0, 2.8, Up);

    list<Bullet> bullets;
    list<Collectable*> collectables;

    CollectableFactory* collectable_factory;
    clock_t next_spawn_time;

    GameWindow(Map gmap): Window(){
        printf("Game window loaded\n");
        game_map = gmap;

//        player1= Player(game_map.p1position);
//        player2= Player(game_map.p2position);

        player1 = new Player(game_map.p1position);
        player2 = new Player(game_map.p2position);

        player1->setColor(Color(.2, .8, .3));
        player2->setColor(Color(.7, .7, .5));

        p1Portal1.setLinkedPortal(p1Portal2);
        p2Portal1.setLinkedPortal(p2Portal2);

        p1Portal1.color = P1PORTAL1_COLOR;
        p1Portal2.color = P1PORTAL2_COLOR;
        p2Portal1.color = P2PORTAL1_COLOR;
        p2Portal2.color = P2PORTAL2_COLOR;;

        for(int i = 0; i<300; i++){
            key_pressed[i]= false;
        }

        collectable_factory = new RandomCollectableFactory();
        next_spawn_time = clock()+CLOCKS_PER_SEC*10;
    }

    ~GameWindow(){
        delete player1;
        delete player2;
        delete collectable_factory;
    }

    void onWindowLoad() override{
        printf("Game window loaded\n");

        this->SHIFT_IS_PRESSED = false;

        for(int i = 0; i<300; i++){
            key_pressed[i]= false;
        }
    }

    void execute() override{
        updatePlayers();
        updatePlayerPositions();
        updateCollectables();
        spawnNewBullets();
        spawnNewPortals();
        updateBulletPositions();

        draw();

        if(player1->getHealth()  == 0){
            w_engine->switchWindow(createGameOverWindow("Player 2 wins"));
        }
        else if(player2->getHealth()  == 0){
            w_engine->switchWindow(createGameOverWindow("Player 1 wins"));
        }
    }

    void updateCollectables(){
        // spawn new collectables if time

        if(clock() > next_spawn_time){
            next_spawn_time = clock()+CLOCKS_PER_SEC*10 + CLOCKS_PER_SEC*randomf()*10;
            Collectable* col = collectable_factory->getCollectable(game_map.getValidSpawnPoint());
//            col->setPosition(game_map.getValidSpawnPoint());
            collectables.push_back(col);
        }

        // update existing collectables
        auto citer = collectables.begin();  //collectables iterator
        auto last = collectables.end();

        while(citer != last){
            // if player 1 touches the collectable
            if((*citer)->detectCollision(player1)){
                player1 = (*citer)->getWrappedPlayer(player1);
                citer = collectables.erase(citer);
            }
            else if((*citer)->detectCollision(player2)){
                player2 = (*citer)->getWrappedPlayer(player2);
                citer = collectables.erase(citer);
            }
            else{
                citer++;
            }
        }
    }

    void updatePlayers(){
        player1 = player1->updateWrapperChain();
        player2 = player2->updateWrapperChain();
    }

    void draw()override {

        drawPlayers();
        drawPortals();
        Bullet::drawBullets(bullets);   // draw all bullets at once
        drawCollectables();
        drawHealthBars();
        drawMap();
    }

    void drawCollectables(){
        auto citer = collectables.begin();
        auto last = collectables.end();

//        printf("%d\n", collectables.size());
        while(citer != last){
            (*citer)->draw();
            citer++;
        }
    }

    void drawPortals(){
        p1Portal1.draw();
        p1Portal2.draw();
        p2Portal1.draw();
        p2Portal2.draw();
    }

    void drawHealthBars(){

        float thickness = .05;
        float p1_bar_width = (float)player1->getHealth() / (float)MAX_PLAYER_HEALTH;
        float p2_bar_width = (float)player2->getHealth() / (float)MAX_PLAYER_HEALTH;

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
                player1->shiftUp();
            }
            if(key_pressed['a']){
                player1->shiftLeft();
            }
            if(key_pressed['s']){
                player1->shiftDown();
            }
            if(key_pressed['d']){
                player1->shiftRight();
            }
        }
        else{
            //player 1 movements
            if(key_pressed['w']){
                player1->moveUp();
            }
            if(key_pressed['a']){
                player1->moveLeft();
            }
            if(key_pressed['s']){
                player1->moveDown();
            }
            if(key_pressed['d']){
                player1->moveRight();
            }
        }

        // if enter key is pressed
        if(key_pressed[13]){
            //player 2 shift movements
            if(key_pressed['5']){
                player2->shiftUp();
            }
            if(key_pressed['1']){
                player2->shiftLeft();
            }
            if(key_pressed['2']){
                player2->shiftDown();
            }
            if(key_pressed['3']){
                player2->shiftRight();
            }
        }
        else{
            //player 2 movements
            if(key_pressed['5']){
                player2->moveUp();
            }
            if(key_pressed['1']){
                player2->moveLeft();
            }
            if(key_pressed['2']){
                player2->moveDown();
            }
            if(key_pressed['3']){
                player2->moveRight();
            }
        }

        // portal
        p1Portal1.teleportPlayer(*player1);
        p2Portal1.teleportPlayer(*player1);
        p1Portal2.teleportPlayer(*player1);
        p2Portal2.teleportPlayer(*player1);

        p1Portal1.teleportPlayer(*player2);
        p2Portal1.teleportPlayer(*player2);
        p1Portal2.teleportPlayer(*player2);
        p2Portal2.teleportPlayer(*player2);

        // if the new position of player causes a collision, reset position to prevision value
        // else update actual position to new position
        if(game_map.detectCollision(*player1)){
            player1->resetNextPosition();
        }
        else{
            player1->updatePosition();
        }

        if(game_map.detectCollision(*player2)){
            player2->resetNextPosition();
        }
        else{
            player2->updatePosition();
        }


        // if players enter a pit, they die instantly
        if(player1_is_alive && game_map.detectPitCollision(player1)){
            player1 = new FallingIntoPit(player1);
            player1_is_alive= false;
        }
        else if(player2_is_alive && game_map.detectPitCollision(player2)){
            player2 = new FallingIntoPit(player2);
            player2_is_alive= false;
        }
    }

    void spawnNewBullets(){
        if(key_pressed[' '] && player1->reloadTimeIsOver()){
            Bullet new_bullet =  player1->shootBullet();
            bullets.push_back(new_bullet);
        }

        if(key_pressed['0'] && player2->reloadTimeIsOver()){
            Bullet new_bullet =  player2->shootBullet();
            bullets.push_back(new_bullet);
        }
    }


    // portal trajectory is a line with end points A (player's position)
    // and B (horizontally or vertically far away, in the player's direction )
    // this method returns the later mentioned end point
    Point getPortalGunTragectoryLinePoint(Point player_pos, Direction player_direction){
        Point other_end_point = player_pos;

        if(player_direction == Up){
            other_end_point.y += 900;
        }
        else if(player_direction == Down){
            other_end_point.y -= 900;
        }
        else if(player_direction == Left){
            other_end_point.x -= 900;
        }
        else{
            //player1.direction == right
            other_end_point.x += 900;
        }

        return other_end_point;
    }

    void spawnNewPortals(){
        // for player 1
        if(key_pressed['q'] && player1->portalGunReloadTimeIsOver()){
            reOpenPortal(*player1, p1Portal1, p1Portal2);
            p1Portal1.color = P1PORTAL1_COLOR;
        }
        else if(key_pressed['e'] && player1->portalGunReloadTimeIsOver()){
            reOpenPortal(*player1, p1Portal2, p1Portal1);
            p1Portal2.color = P1PORTAL2_COLOR;
        }


        if(key_pressed['4'] && player2->portalGunReloadTimeIsOver()){
            reOpenPortal(*player2, p2Portal1, p2Portal2);
            p2Portal1.color = P2PORTAL1_COLOR;
        }
        else if(key_pressed['6'] && player2->portalGunReloadTimeIsOver()){
            reOpenPortal(*player2, p2Portal2, p2Portal1);
            p2Portal2.color = P2PORTAL2_COLOR;
        }
    }

    void reOpenPortal(BasePlayer& player, Portal& portal, Portal& link_portal){
        Direction player_direction =  player.getDirection();
        Point other_end_point = getPortalGunTragectoryLinePoint(player.getPosition(), player_direction);

        // record when this portal is opened
        player.setPortalOpenTimeNow();
        Point player_pos = player.getPosition();

        if(player_direction == Up || player_direction == Down){
            Point intercept = game_map.getNearestHorizontalIntercept(player_pos, other_end_point, player_pos);
            portal = Portal(intercept.x, intercept.y, player_direction);
            portal.setLinkedPortal(link_portal);
//                printf("%f %f\n", intercept.x, intercept.y);
        }
        else{
            // else player direction is left or right
            Point intercept = game_map.getNearestVerticalIntercept(player_pos, other_end_point, player_pos);
            portal = Portal(intercept.x, intercept.y, player_direction);
            portal.setLinkedPortal(link_portal);
        }
    }

    void updateBulletPositions(){
//        printf("len: %d\n", bullets.size());

        auto bullets_end = bullets.end();
        auto bullet =  bullets.begin();

        while(bullet != bullets_end){

            bullet->updatePosition();

            p1Portal1.teleportBullet(*bullet);
            p1Portal2.teleportBullet(*bullet);
            p2Portal1.teleportBullet(*bullet);
            p2Portal2.teleportBullet(*bullet);

            if(player1->detectHit(*bullet)){
                bullet= bullets.erase(bullet);
                player1->takeDamage(5);
            }
            else if(player2->detectHit(*bullet)){
                bullet= bullets.erase(bullet);
                player2->takeDamage(5);
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
        player1->draw();
        player2->draw();
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
//            this->w_engine->switchWindow(new ConfirmQuitGameWindow(this));
            this->w_engine->switchWindow(createConfirmQuitWIndow(this));
        }
        else if(key == 't'){
//            collectables.push_back(new HealthCollectable(game_map.getValidSpawnPoint()));
            Collectable* col = collectable_factory->getCollectable(game_map.getValidSpawnPoint());
//            col->setPosition(game_map.getValidSpawnPoint());
            collectables.push_back(col);
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

class MapSelectionMenue: public Window{
    // options are shown from top to bottom, option at index 0 is shown on top
    Window* previous_window;
    vector<Map> menu_options = getAllMaps();
    int selected_option_idx = 0;

public:

    MapSelectionMenue(Window* previous_window){
        this->previous_window = previous_window;
    }

    void execute() override{
        draw();
    }

    void draw()override {

        glColor3f(.9,.9,.9);
        glPushMatrix();

        glTranslatef(-2.5,2.5,0);
        drawMenueOptions();
        glPopMatrix();

        drawMapPreview();

        drawMainBackground();
    }

    void drawMapPreview(){
        // show map preview
        glColor3f(.9,.9,.9);
        drawString(-.5,1.6, "Preview");

        glPushMatrix();
        glTranslatef(1,0,0);
        glScalef(.5,.5, 1);
        menu_options[selected_option_idx].draw();
        glPopMatrix();
    }

    void handleChosenOption(int chosen_option_idx){
        //start game with selected map
        this->w_engine->switchWindow(new GameWindow(menu_options[chosen_option_idx]));
    }

    void drawMenueOptions(){
        float LINE_SPACING = 0.25;
        float y = 0;        //level of line

        drawString(0,0, "Maps");
        y-= 2*LINE_SPACING;

        for(int i= 0, len = menu_options.size(); i<len; i++){
            if(selected_option_idx == i){
                glColor3f(.9,.9,.9);
            }
            else{
                glColor3f(0.2,0.6,.9);
            }

            drawString(0, y, (char*)menu_options[i].getMapName().c_str());
            y-= LINE_SPACING;
        }
    }

    void onWindowLoad() override{
        printf("Map Selection Menu loaded\n");

    }

    void keyPress(unsigned char key, int x, int y) override{
        if(key == 27){
            // when escape is pressed
            this->w_engine->switchWindow(previous_window);
        }
        else if(key == 13){
            // when enter is pressed
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
        selected_option_idx -= 1;
        if(selected_option_idx < 0){
            selected_option_idx = menu_options.size()-1;
        }
    }

    void selectOptionBellow(){
        selected_option_idx = (selected_option_idx+1)%menu_options.size();
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
            this->w_engine->switchWindow(new MapSelectionMenue(this));
        }
        else if(chosen_option_idx == 1){
            this->w_engine->switchWindow(new HelpScreenWindow(this));
        }
        else if(chosen_option_idx == 2){
            this->w_engine->switchWindow(new GameGuideWindow(this));
        }
        else if(chosen_option_idx == 3){
            exit(0);
        }
    }

    void drawMenueOptions(){
        float LINE_SPACING = 0.25;
        float y = 0;        //level of line

        glColor3f(.9,.9,.9);
        drawString(0,0, "Main Menu");
        y-= 2*LINE_SPACING;

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
        selected_option_idx -= 1;
        if(selected_option_idx < 0){
            selected_option_idx = menu_options.size()-1;
        }
    }

    void selectOptionBellow(){
        selected_option_idx = (selected_option_idx+1)%menu_options.size();
    }
};


class ConfirmQuitGameWindow: public Window{
    Window* previous_window;
    vector<char*> menu_options = {"Yes", "No"};
    int selected_option_idx = 0;
public:

    ConfirmQuitGameWindow(Window* previous_window){
        this->previous_window = previous_window;
    }

    void execute() override{
        draw();
    }

    void draw()override {
        setColor(DEFAULT_TEXT_COLOR);
        drawString(-.4,.5, "Quit Game?", GLUT_BITMAP_TIMES_ROMAN_24);

        drawMenueOptions();
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

    void handleChosenOption(int chosen_option_idx){
        //start game with selected map
        if(chosen_option_idx == 0){
            // if yes is selected, go back to main menu
            this->w_engine->switchWindow(new MainMenuWindow());
        }
        else if(chosen_option_idx == 1){
            // if no is selected resume game
            this->w_engine->switchWindow(previous_window);
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
        printf("Confirm quit game window loaded\n");
    }

    void keyPress(unsigned char key, int x, int y) override{
//        printf("%c\n", key);
        if(key == 27){
            // when escape is pressed, resume game
            this->w_engine->switchWindow(previous_window);
        }
        else if(key == 13){
            handleChosenOption(selected_option_idx);
        }

    }

    void specialKeyPress(int key, int x, int y) override{
        if(key == GLUT_KEY_UP){
            selectOptionAbove();
        }
        else if(key == GLUT_KEY_DOWN){
            selectOptionBellow();
        }
    }

    void keyUp(unsigned char key, int x, int y) override{
    }

    void specialKeyUp(int key, int x, int y) override{

    }

    void selectOptionAbove(){
        selected_option_idx -= 1;
        if(selected_option_idx < 0){
            selected_option_idx = menu_options.size()-1;
        }
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
        draw();
    }

    void draw()override {

        if(current_iteration < TOTAL_ITERATIONS){
           r+= ri;
           g+= gi;
           b+= bi;

           current_iteration++;
        }
        else{
            glColor3f(1,1,1);
            drawString(-.4,-2.5, "<PRESS ANY KEY>", GLUT_BITMAP_9_BY_15);
        }

        glColor3f(r,g,b);
        glPushMatrix();
        glTranslatef(-.4,0,1);
        drawString(0,0, "PORTAL  2D", GLUT_BITMAP_TIMES_ROMAN_24);
        glPopMatrix();

        drawMainBackground();
    }

    void onWindowLoad() override{
        printf("Splash screen window loaded\n");

    }

    void goToMainMenue(){
        //this->w_engine->switchWindow(new GameWindow());
        this->w_engine->switchWindow(new MainMenuWindow());
    }

    void keyPress(unsigned char key, int x, int y) override{
        // when any is pressed
        goToMainMenue();
    }

    void specialKeyPress(int key, int x, int y) override{
//        printf("%d\n", key);
        goToMainMenue();
    }

    void keyUp(unsigned char key, int x, int y) override{

    }

    void specialKeyUp(int key, int x, int y) override{

    }
};


class GameOverWindow: public Window{
    string message;
public:

    GameOverWindow(string msg){
        message = msg ;
    }

    void execute() override{
        draw();
    }

    void draw()override {
        setColor(DEFAULT_TEXT_COLOR);
        drawString(-.4,.5, "Game over", GLUT_BITMAP_TIMES_ROMAN_24);
        drawString(-.5,.0, (char*)message.c_str(), GLUT_BITMAP_TIMES_ROMAN_24);

        drawMainBackground();
    }

    void onWindowLoad() override{
        printf("Confirm quit game window loaded\n");
    }

    void keyPress(unsigned char key, int x, int y) override{
        if(key == 13){
            this->w_engine->switchWindow(new MainMenuWindow());
        }
    }

    void specialKeyPress(int key, int x, int y) override{
    }

    void keyUp(unsigned char key, int x, int y) override{
    }

    void specialKeyUp(int key, int x, int y) override{

    }
};

Window* createConfirmQuitWIndow(Window* previous_window){
    return new ConfirmQuitGameWindow(previous_window);
}

Window* createGameOverWindow(string msg){
    return new GameOverWindow(msg);
}

#endif
