/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#pragma once

#include "utinni.h"

namespace swg::math
{
struct UTINNI_API Vector2d
{
    float X;
    float Y;

    Vector2d();
    Vector2d(float x, float y);

    Vector2d operator +(const Vector2d& vector) const;
    Vector2d operator -(const Vector2d& vector) const;
    Vector2d operator *(float scalar) const;
    Vector2d operator /(float scalar) const;

    //bool normalize();
};

struct UTINNI_API Vector
{
    float X;
    float Y;
    float Z;

    Vector();
    Vector(float x, float y, float z);

    Vector operator +(const Vector& vector) const;
    Vector operator -(const Vector& vector) const;
    Vector operator *(float scalar) const;
    Vector operator /(float scalar) const;

    bool operator ==(const Vector& vector) const;
    bool operator !=(const Vector& vector) const;

    bool normalize();
};

struct UTINNI_API Transform
{
    float matrix[3][4]{};

    Transform();
    Transform(float x, float y, float z);
    Transform(Vector& position);

    void setPosition(float x, float y, float z);
    void setPosition(const Vector& vector);
    Vector getPosition();

    Transform addPosition(const Transform& transform);
    Transform addPosition(const Vector& vector);
    Transform subtractPosition(const Transform& transform);
    Transform subtractPosition(const Vector& vector);

    void multiply(const Transform& transform);
    void multiply(const Transform& left, const Transform& right);

    void invert(const Transform& transform);

    void yaw(float degrees);
    void pitch(float degrees);
    void roll(float degrees);
    void setRotationAxis(float x, float y, float z);
    void setRotationAxis(const Vector& vector);

    float getYaw_p2l();
    float getPitch_p2l();

    Vector rotate_o2w(const Vector& vector);
    Vector rotate_p2w(const Vector& vector);
    Vector rotate_l2p(const Vector& vector);

    Vector rotateTranslate_l2p(const Vector& vector);

    void copyRotation(const Transform& transform);
    bool isRotationEqual(const Transform& transform);

    static Transform getIdentity();
};

struct UTINNI_API Matrix4x4
{
    float matrix[4][4]{};

    Matrix4x4();
    Matrix4x4(const Transform& Transform);
    Matrix4x4(const Matrix4x4& matrix4x4);

    Matrix4x4 addPosition(const Matrix4x4& matrix4x4);
    Matrix4x4 subtractPosition(const Matrix4x4& matrix4x4);

    static void transpose(const float* source, float* destination);
    Matrix4x4 operator +(const Matrix4x4& matrix) const;
    Matrix4x4 operator -(const Matrix4x4& matrix) const;
};

struct UTINNI_API Plane
{
    Vector normal;
    float d;
};

struct UTINNI_API Volume
{
    int numberOfPlanes;
    Plane* plane;
};

struct UTINNI_API Quaternion
{
    Quaternion();
    Quaternion(const Transform& Transform);
    //Quaternion(float angle, const Vector& vector);

    float W;
    float X;
    float Y;
    float Z;
};

struct UTINNI_API Point
{
    Point();
    Point(float x, float y);

    float X;
    float Y;
};

struct UTINNI_API UiPoint
{
    int X;
    int Y;

    UiPoint();
    UiPoint(int x, int y);
};

struct UTINNI_API Rect2d
{
    float X0;
    float Y0;

    float X1;
    float Y1;

    Rect2d();
    Rect2d(float x0, float y0, float x1, float y1);

    float getWidth() const { return abs(X1 - X0); }
    float getHeight() const { return abs(Y1 - Y0); }
};

struct UTINNI_API UiRect
{
    int Left;
    int Top;

    int Right;
    int Bottom;

    UiRect();
    UiRect(int left, int top, int right, int bottom);

    int getWidth() const { return Right - Left; }
    int getHeight() const { return Bottom - Top; }
};
}
