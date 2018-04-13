#ifndef TEXT_DRAW_H
#define TEXT_DRAW_H

void drawString(float x, float y, char *str, void *font= GLUT_BITMAP_HELVETICA_18){
    int len;

    glRasterPos2f(x, y);
    len = (int) strlen(str);
    for(int i = 0; i < len; i++) {
        glutBitmapCharacter(font, str[i]);
    }
}

#endif
