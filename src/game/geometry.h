#ifndef GEOMETRY_H
#define GEOMETRY_H

float pointDistance(const Point& a, const Point& b){
    float dx = a.x-b.x;
    float dy = a.y-b.y;
    return sqrt(dx*dx + dy*dy);
}

#endif
