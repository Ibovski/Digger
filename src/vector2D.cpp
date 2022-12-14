#include "../headers/Vector2D.h"
#include <cassert>
Vector2D::Vector2D(int x, int y) : x(x), y(y) {
}

std::ostream &operator<<(std::ostream &out, const Vector2D &v) {
    out<<"("<<v.x<<" , "<<v.y<<")";
    return out;
}

void Vector2D::Zero() {
    x = y = 0;
}

Vector2D Vector2D::operator*(int k) const{
    Vector2D newV;
    newV.x = this->x * k;
    newV.y = this->y * k;
    return newV;
}

bool Vector2D::operator==(const Vector2D &other) {
    return (x == other.x && y == other.y);
}

bool Vector2D::operator==(Vector2D &&other) {
    return (x == other.x && y == other.y);
}

bool Vector2D::operator>=(const Vector2D &other) {
    return (x >= other.x && y >= other.y);
}

bool Vector2D::operator>=(Vector2D &&other) {
    return (x >= other.x && y >= other.y);
}

bool Vector2D::operator<=(const Vector2D other) {
    return (x <= other.x && y <= other.y);
}

bool Vector2D::operator<=(Vector2D &&other) {
    return (x <= other.x && y <= other.y);
}

void Vector2D::setX(int X) {
    x = X;
}

void Vector2D::setY(int Y) {
    y = Y;
}

int Vector2D::getX() const{
    return x;
}

int Vector2D::getY() const {
    return y;
}

Vector2D Vector2D::operator/(int k) const {
    if(k == 0) return *this;
    Vector2D newV;
    newV.x = this->x / k;
    newV.y = this->y / k;
    return newV;
}

void Vector2D::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator+(const Vector2D &v2) const{
    Vector2D newV;
    newV.x = this->x + v2.x;
    newV.y = this->y + v2.y;
    return newV;
}

Vector2D Vector2D::operator-(const Vector2D &v2) const {
    Vector2D newV;
    newV.x = this->x - v2.x;
    newV.y = this->y - v2.y;
    return newV;
}

Vector2D Vector2D::operator*(const Vector2D &v2) const {
    Vector2D newV;
    newV.x = this->x * v2.x;
    newV.y = this->y * v2.y;
    return newV;
}

Vector2D Vector2D::operator/(const Vector2D &v2) const {
    assert(v2.x !=0 && v2.y !=0);
    Vector2D newV;
    newV.x = this->x  / v2.x;
    newV.y = this->y / v2.y;
    return newV;
}

Vector2D &Vector2D::operator+=(const Vector2D &other) {
    *this = *this + other;
    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &other) {
    *this = *this - other;
    return *this;
}


