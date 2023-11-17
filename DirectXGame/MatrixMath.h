#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <math.h>

Vector3 Add(Vector3 vector1, Vector3 vector2);

Vector3 Subtract(Vector3 vector1, Vector3 vector2);

Vector3 VectorMultiply(float scalar, const Vector3& v1);

Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

float Dot(Vector3 vector1, Vector3 vector2);

float Length(Vector3 v);

Vector3 Normalize(const Vector3& v);

// 1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// 2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// 3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, Vector3& rotate, const Vector3& translate);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Matrix4x4 Inverse(const Matrix4x4& m);