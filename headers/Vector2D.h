#pragma once
#include <iostream>
/**
 * A simple Vector2D class.
 *
 * xPosition and yPosition are type int.
 * It has all the binary operations with ( + , - , * , /).
 *
 */
class Vector2D{
private:
    int x=0;
    int y=0;
public:

    void setX(int X);
    void setY(int Y);
    int getX() const;
    int getY() const;

    Vector2D() = default;
    Vector2D(int x, int y);
    void setPos(int x, int y);
    void Zero();
    Vector2D operator+(const Vector2D& v2) const;
    Vector2D operator-(const Vector2D& v2) const;
    Vector2D operator*(const Vector2D& v2) const;
    Vector2D operator/(const Vector2D& v2) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D operator*(int k) const;
    Vector2D operator/(int k) const;
    bool operator==(const Vector2D& other);
    bool operator==(Vector2D&& other);
    bool operator>=(const Vector2D& other);
    bool operator>=(Vector2D&& other);
    bool operator<=(const Vector2D other);
    bool operator<=(Vector2D&& other);
    friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);
};