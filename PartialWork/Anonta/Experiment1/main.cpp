#include "./debugger.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include <cstdio>
#include <math.h>

#include <vector>

using namespace std;

// keyboard status, true for pressed, false for unpressed
bool keyStatus[500];

struct Point{
    double x, y;

    Point(){
    }
    Point(double x, double y){
        this->x= x;
        this->y= y;
    }
};



double distance(Point p1, Point p2){
    double dx = p2.x-p1.x;
    double dy = p2.y-p1.y;

    return sqrt(dx*dx+dy*dy);
}

bool pointOnLine(Point& a, Point& b, Point& c){
    double ab= distance(a,b);
    double ac= distance(a,c);
    double bc= distance(b,c);

//    printf("%f %f %f", ab, ac, bc);
//    getchar();

    return (ac+bc) - ab < 0.00001;
}

struct Player{
    int x,y;

    int nx, ny;

    void updatePosition(){
        x= nx;
        y= ny;
    }

    void dontMove(){
        nx = x;
        ny = y;
    }
};
Player player1;
Player player2;

struct Wall{
    Point p1, p2;

    Wall(){

    }

    Wall(double x1, double y1, double x2, double y2){
        p1.x= x1;
        p1.y= y1;

        p2.x= x2;
        p2.y= y2;
    }

    void draw(){
//        printf("%f%f", p2.x, p2.y);
//        getchar();

        glColor3f(.8,0,.4);
        glBegin(GL_LINES);
        plot(p1.x, p1.y);
        plot(p2.x, p2.y);
        glEnd();
    }
};
vector<Wall> walls;

void physicsUpdate(){
    for(int i = 0, len = walls.size(); i<len; i++){
        Point p(player1.nx, player1.ny);

        if(pointOnLine(walls[i].p1, walls[i].p2, p)){
            player1.dontMove();
        }
        else{
            player1.updatePosition();
        }
    }
}

void drawWalls(){
//    printf("AAAAAAAAAAAA");

    for(int i = 0, len = walls.size(); i<len; i++){
        walls[i].draw();
    }
}

void initializeMap(){
    walls.push_back(Wall(0,50, 50,50));
}



void keyEventHandler();

void idle(){
    physicsUpdate();

    keyEventHandler();
    glutPostRedisplay();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    drawWalls();

//    drawGrid();
    glBegin(GL_POINTS);

    plot(player1.x, player1.y);
    plot(player2.x, player2.y);

    glEnd();

    glFlush();
}

void keyEventHandler(){

//    printf("AAAAAAAAAA\n");
    //player 1 movement
    if(keyStatus['w'])
        player1.ny= player1.y+1;
    if(keyStatus['s'])
        player1.ny= player1.ny-1;
    if(keyStatus['a'])
        player1.nx= player1.x-1;
    if(keyStatus['d'])
        player1.nx= player1.x+1;

    // player 2 movement


    if(keyStatus[GLUT_KEY_UP])
        player2.y++;
    if(keyStatus[GLUT_KEY_DOWN])
        player2.y--;
    if(keyStatus[GLUT_KEY_LEFT])
        player2.x--;
    if(keyStatus[GLUT_KEY_RIGHT])
        player2.x++;

    for(int i =0; i<256; i++){
        keyStatus[i]= false;
    }
}

// sets key status on and off
void keyHandler(unsigned char key, int x, int y){
    keyStatus[key] = true;
}

// handles special key presses line arrow keys
void specialKeyHandler(int key, int x, int y){
    keyStatus[key] = true;
}


setConfigs(){
    glPointSize(5);
}

void init(void)
{
    /* select clearing (background) color */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    //gluOrtho2D(0.0,1,0.0,1);
}

void setCallBacks(){
    glutKeyboardFunc(keyHandler);
	glutSpecialFunc(specialKeyHandler);
//	glutMouseFunc(handleMouseclick);
//	glutMotionFunc(handleMouseDrag);
//	glutReshapeFunc(handleResize);
//	glutTimerFunc(10, new_update, 0);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(800, 100);
    glutCreateWindow("test");
    init();

    setConfigs();
    setCallBacks();

    initializeMap();

    glutMainLoop();
    return 0; /* ISO C requires main to return int. */
}
