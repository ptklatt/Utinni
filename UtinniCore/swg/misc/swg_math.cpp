#include "swg_math.h"

namespace swg::math
{

using pVectorNormalize = bool(__thiscall*)(Vector* pThis);

pVectorNormalize vectorNormalize = (pVectorNormalize)0x00AB5C40;

Vector2d::Vector2d()
    : X(0)
    , Y(0)
{
}

Vector2d::Vector2d(float x, float y)
    : X(x)
    , Y(y)
{
}

Vector2d Vector2d::operator+(const Vector2d& vector) const
{
    return Vector2d(X + vector.X, Y + vector.Y);
}

Vector2d Vector2d::operator-(const Vector2d& vector) const
{
    return Vector2d(X - vector.X, Y - vector.Y);
}

Vector2d Vector2d::operator*(float scalar) const
{
    return Vector2d(X * scalar, Y * scalar);
}

Vector2d Vector2d::operator/(float scalar) const
{
    const float multiplier(float(1.0) / scalar);
    return Vector2d(X * multiplier, Y * multiplier);
}

//bool Vector2d::normalize()
//{
//    return vector2Normalize(this);
//}

Vector::Vector()
    : X(0)
    , Y(0)
    , Z(0)
{
}

Vector::Vector(float x, float y, float z)
    : X(x)
    , Y(y)
    , Z(z)
{
}

Vector Vector::operator+(const Vector& vector) const
{
    return Vector(X + vector.X, Y + vector.Y, Z + vector.Z);
}

Vector Vector::operator-(const Vector& vector) const
{
    return Vector(X - vector.X, Y - vector.Y, Z - vector.Z);
}

Vector Vector::operator*(float scalar) const
{
    return Vector(X * scalar, Y * scalar, Z * scalar);
}

Vector Vector::operator/(float scalar) const
{
    const float multiplier(float(1.0) / scalar);
    return Vector(X * multiplier, Y * multiplier, Z * multiplier);
}

bool Vector::normalize()
{
    return vectorNormalize(this);
}

Transform::Transform()
{
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;
}

Transform::Transform(float x, float y, float z)
{
    setPosition(x, y, z);
}

Transform::Transform(Vector& position)
{
    setPosition(position);
}

void Transform::setPosition(float x, float y, float z)
{
    matrix[0][3] = x;
    matrix[1][3] = y;
    matrix[2][3] = z;
}

void Transform::setPosition(const Vector& vector)
{
    matrix[0][3] = vector.X;
    matrix[1][3] = vector.Y;
    matrix[2][3] = vector.Z;
}

Vector Transform::getPosition()
{
    return { matrix[0][3], matrix[1][3], matrix[2][3] };
}

Vector Transform::rotate_l2p(const Vector& vector)
{
    return Vector(
        matrix[0][0] * vector.X + matrix[0][1] * vector.Y + matrix[0][2] * vector.Z,
        matrix[1][0] * vector.X + matrix[1][1] * vector.Y + matrix[1][2] * vector.Z,
        matrix[2][0] * vector.X + matrix[2][1] * vector.Y + matrix[2][2] * vector.Z);

}

Transform Transform::addPosition(const Transform& transform)
{
    matrix[0][3] += transform.matrix[0][3];
    matrix[1][3] += transform.matrix[1][3];
    matrix[2][3] += transform.matrix[2][3];

    return Transform(*this);
}

Transform Transform::addPosition(const Vector& vector)
{
    matrix[0][3] += vector.X;
    matrix[1][3] += vector.Y;
    matrix[2][3] += vector.Z;

    return Transform(*this);
}

Transform Transform::subtractPosition(const Transform& transform)
{
    matrix[0][3] -= transform.matrix[0][3];
    matrix[1][3] -= transform.matrix[1][3];
    matrix[2][3] -= transform.matrix[2][3];

    return Transform(*this);
}

Transform Transform::subtractPosition(const Vector& vector)
{
    matrix[0][3] -= vector.X;
    matrix[1][3] -= vector.Y;
    matrix[2][3] -= vector.Z;

    return Transform(*this);
}

void matrixMultiply_3x4(float* source, const float* left, const float* right)
{
    if (left == source || right == source)
    {
        float tmp[12];

        tmp[0] = left[0] * right[0] + left[1] * right[4] + left[2] * right[8];
        tmp[1] = left[0] * right[1] + left[1] * right[5] + left[2] * right[9];
        tmp[2] = left[0] * right[2] + left[1] * right[6] + left[2] * right[10];
        tmp[3] = left[0] * right[3] + left[1] * right[7] + left[2] * right[11] + left[3];

        tmp[4] = left[4] * right[0] + left[5] * right[4] + left[6] * right[8];
        tmp[5] = left[4] * right[1] + left[5] * right[5] + left[6] * right[9];
        tmp[6] = left[4] * right[2] + left[5] * right[6] + left[6] * right[10];
        tmp[7] = left[4] * right[3] + left[5] * right[7] + left[6] * right[11] + left[7];

        tmp[8] = left[8] * right[0] + left[9] * right[4] + left[10] * right[8];
        tmp[9] = left[8] * right[1] + left[9] * right[5] + left[10] * right[9];
        tmp[10] = left[8] * right[2] + left[9] * right[6] + left[10] * right[10];
        tmp[11] = left[8] * right[3] + left[9] * right[7] + left[10] * right[11] + left[11];

        for (int i = 0; i < 12; ++i)
        {
            source[i] = tmp[i];
        }
    }
    else
    {
        source[0] = left[0] * right[0] + left[1] * right[4] + left[2] * right[8];
        source[1] = left[0] * right[1] + left[1] * right[5] + left[2] * right[9];
        source[2] = left[0] * right[2] + left[1] * right[6] + left[2] * right[10];
        source[3] = left[0] * right[3] + left[1] * right[7] + left[2] * right[11] + left[3];

        source[4] = left[4] * right[0] + left[5] * right[4] + left[6] * right[8];
        source[5] = left[4] * right[1] + left[5] * right[5] + left[6] * right[9];
        source[6] = left[4] * right[2] + left[5] * right[6] + left[6] * right[10];
        source[7] = left[4] * right[3] + left[5] * right[7] + left[6] * right[11] + left[7];

        source[8] = left[8] * right[0] + left[9] * right[4] + left[10] * right[8];
        source[9] = left[8] * right[1] + left[9] * right[5] + left[10] * right[9];
        source[10] = left[8] * right[2] + left[9] * right[6] + left[10] * right[10];
        source[11] = left[8] * right[3] + left[9] * right[7] + left[10] * right[11] + left[11];
    }
}

void Transform::multiply(const Transform& left, const Transform& right)
{
    matrixMultiply_3x4(matrix[0], left.matrix[0], right.matrix[0]);
}

void Transform::invert(const Transform& transform)
{
    matrix[0][0] = transform.matrix[0][0];
    matrix[0][1] = transform.matrix[1][0];
    matrix[0][2] = transform.matrix[2][0];

    matrix[1][0] = transform.matrix[0][1];
    matrix[1][1] = transform.matrix[1][1];
    matrix[1][2] = transform.matrix[2][1];

    matrix[2][0] = transform.matrix[0][2];
    matrix[2][1] = transform.matrix[1][2];
    matrix[2][2] = transform.matrix[2][2];

    const float x = transform.matrix[0][3];
    const float y = transform.matrix[1][3];
    const float z = transform.matrix[2][3];
    matrix[0][3] = -(matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z);
    matrix[1][3] = -(matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z);
    matrix[2][3] = -(matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z);
}

Vector Transform::rotate_o2w(const Vector& vector)
{
    return {
        matrix[0][0] * vector.X + matrix[0][1] * vector.Y + matrix[0][2] * vector.Z,
        matrix[1][0] * vector.X + matrix[1][1] * vector.Y + matrix[1][2] * vector.Z,
        matrix[2][0] * vector.X + matrix[2][1] * vector.Y + matrix[2][2] * vector.Z };

}

Vector Transform::rotate_p2w(const Vector& vector)
{
    return {
        matrix[0][0] * vector.X + matrix[1][0] * vector.Y + matrix[2][0] * vector.Z,
        matrix[0][1] * vector.X + matrix[1][1] * vector.Y + matrix[2][1] * vector.Z,
        matrix[0][2] * vector.X + matrix[1][2] * vector.Y + matrix[2][2] * vector.Z };
}

Transform Transform::getIdentity()
{
    return Transform();
}

Matrix4x4::Matrix4x4()
{
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;
    matrix[1][3] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
}

Matrix4x4::Matrix4x4(const Transform& transform)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            matrix[i][j] = transform.matrix[i][j];
            matrix[i][j] = transform.matrix[i][j];
            matrix[i][j] = transform.matrix[i][j];
            matrix[i][j] = transform.matrix[i][j];
        }
    }

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
}

Matrix4x4::Matrix4x4(const Matrix4x4& matrix4x4)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            matrix[i][j] = matrix4x4.matrix[i][j];
            matrix[i][j] = matrix4x4.matrix[i][j];
            matrix[i][j] = matrix4x4.matrix[i][j];
            matrix[i][j] = matrix4x4.matrix[i][j];
        }
    }
}

Matrix4x4 Matrix4x4::addPosition(const Matrix4x4& matrix4x4)
{
    matrix[0][3] += matrix4x4.matrix[0][3];
    matrix[1][3] += matrix4x4.matrix[1][3];
    matrix[2][3] += matrix4x4.matrix[2][3];

    return Matrix4x4(*this);
}

Matrix4x4 Matrix4x4::subtractPosition(const Matrix4x4& matrix4x4)
{
    matrix[0][3] -= matrix4x4.matrix[0][3];
    matrix[1][3] -= matrix4x4.matrix[1][3];
    matrix[2][3] -= matrix4x4.matrix[2][3];

    return Matrix4x4(*this);
}

void Matrix4x4::transpose(const float* source, float* destination)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            destination[i * 4 + j] = source[j * 4 + i];
        }
    }
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& matrix4x4) const
{
    Matrix4x4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.matrix[i][j] = matrix[i][j] + matrix4x4.matrix[i][j];
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& matrix4x4) const
{
    Matrix4x4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result.matrix[i][j] = matrix[i][j] - matrix4x4.matrix[i][j];
        }
    }
    return result;
}

Quaternion::Quaternion()
    : W(1)
    , X(0)
    , Y(0)
    , Z(0)
{
}

Quaternion::Quaternion(const Transform& transform)
    : W(1)
    , X(0)
    , Y(0)
    , Z(0)
{
    const float trace = transform.matrix[0][0] + transform.matrix[1][1] + transform.matrix[2][2] + 1.0f;
    if (trace >= 2.0f)
    {
        const float sqrtTrace = sqrt(trace);
        W = sqrtTrace * 0.5f;

        const float d = 0.5f / sqrtTrace;
        X = (transform.matrix[2][1] - transform.matrix[1][2]) * d;
        Y = (transform.matrix[0][2] - transform.matrix[2][0]) * d;
        Z = (transform.matrix[1][0] - transform.matrix[0][1]) * d;
    }
    else
    {
        int i = 0, j = 1, k = 2;
        if (transform.matrix[1][1] > transform.matrix[i][i])
        {
            i = 1, j = 2, k = 0;
        }
        if (transform.matrix[2][2] > transform.matrix[i][i])
        {
            i = 2, j = 0, k = 1;
        }

        float* v = &X;
        v[i] = sqrt(((transform.matrix[i][i] - transform.matrix[j][j]) - transform.matrix[k][k]) + 1.0f) * 0.5f;
        const float d = 1.0f / (4.0f * v[i]);
        v[j] = (transform.matrix[j][i] + transform.matrix[i][j]) * d;
        v[k] = (transform.matrix[k][i] + transform.matrix[i][k]) * d;
        W = (transform.matrix[k][j] - transform.matrix[j][k]) * d;
    }
}

Point::Point()
    : X(0)
    , Y(0)
{
}

Point::Point(float x, float y)
    : X(x)
    , Y(y)
{
}

UiPoint::UiPoint()
    : X(0)
    , Y(0)
{
}

UiPoint::UiPoint(int x, int y)
    : X(0)
    , Y(0)
{
}

Rect2d::Rect2d()
    : X0(0)
    , Y0(0)
    , X1(0)
    , Y1(0)
{
}

Rect2d::Rect2d(float x0, float y0, float x1, float y1)
    : X0(x0)
    , Y0(y0)
    , X1(x1)
    , Y1(y1)
{
}

UiRect::UiRect()
    : Left(0)
    , Top(0)
    , Right(0)
    , Bottom(0)
{
}

UiRect::UiRect(int left, int top, int right, int bottom)
    : Left(left)
    , Top(top)
    , Right(right)
    , Bottom(bottom)
{
}

}