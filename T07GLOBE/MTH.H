/* FILE NAME: MTH.H
 * PROGRAMMER: EN5
 * DATE: 05.06.2020
 * PURPOSE: 3D math implementation module.
 */

#ifndef __MTH_H_
#define __MTH_H_

#include <math.h>
#include <windows.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Base float point types */
typedef double DBL;
typedef double FLT;

/* Space vector/point representation type */
typedef struct tagVEC
{
  DBL X, Y, Z; /* Vector coordinates */
} VEC;

/* matrix type */
typedef struct tagMATR
{
  DBL M[4][4];
} MATR;

/* Unit matrix */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Create vectors function.
 * ARGUMENTS:
 *   - Vector coordinates:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
} /* End of 'VecSet' function */

/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Sub two vectors function.
 * ARGUMENTS:
 *   - vectors to be sub:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Multiplicate vector on number function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V1;
 *   - numder:
 *       DBL N;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Division vector on number function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V1;
 *   - numder:
 *       DBL N;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC VecDivNum( VEC V1, DBL N )
{
  if (N == 0 || N == 1)
    return V1;

  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecDivNum' function */

/* Negative vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V1;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC VecNeg( VEC V1 )
{
  return VecSet(-V1.X, -V1.Y, -V1.Z);
} /* End of 'VecNeg' function */

/* Dot multiplicate of two vector function.
 * ARGUMENTS:
 *   - first vector:
 *       VEC V1;
 *   - second vector:
 *       VEC V2;
 * RETURNS:
 *   (DBL) Dot multiplicate.
 */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Cross multiplicate of two vector function.
 * ARGUMENTS:
 *   - first vector:
 *       VEC V1;
 *   - second vector:
 *       VEC V2;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Len of vector in squere function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (DBL) squere lenth.
 */
__inline DBL VecLen2( VEC V )
{
  return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
} /* End of 'VecLen2' function */

/* Len of vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (DBL) lenth.
 */
__inline DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
} /* End of 'VecLen' function */

/* Normalize vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC VecNormalize( VEC V )
{
  return VecDivNum(V, VecLen(V));
} /* End of 'VecNormalize' function */

/* Multiplicate point on matrix function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z + M.M[3][0],
                M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z + M.M[3][1],
                M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z + M.M[3][2]);
} /* End of 'PointTransform' function */

/* Multiplicate vector on matrix function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) resalut vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z,
                M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z,
                M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z);
} /* End of 'VectorTransform' function */

/* Vector by matrix multiplication (with homogenious devide) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC V;
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  DBL w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w,
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Identity matrix.
 * ARGUMENTS: None.
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Translate matrix function.
 * ARGUMENTS:
 *   - vector:
 *       VEC T;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {T.X, T.Y, T.Z, 1}
    }
  };

  return M;
} /* End of 'MatrTranslate' function */

/* Scale matrix function.
 * ARGUMENTS:
 *   - vector:
 *       VEC T;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrScale( VEC S )
{
  MATR M =
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrScale' function */

/* Rotate vector on angle x function.
 * ARGUMENTS:
 *   - angle:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL Angle = D2R(AngleInDegree);
  DBL c = cos(Angle), s= sin(Angle);
  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, c, s, 0},
      {0, -s, c, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotateX' function */

/* Rotate vector on angle y function.
 * ARGUMENTS:
 *   - angle:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL Angle = D2R(AngleInDegree);
  DBL c = cos(Angle), s= sin(Angle);
  MATR M =
  {
    {
      {c, 0, -s, 0},
      {0, 1, 0, 0},
      {s, 0, c, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotateY' function */

/* Rotate vector on angle z function.
 * ARGUMENTS:
 *   - angle:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL Angle = D2R(AngleInDegree);
  DBL c = cos(Angle), s= sin(Angle);
  MATR M =
  {
    {
      {c, s, 0, 0},
      {-s, c, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotateZ' function */

/* Rotate vector on angle and vector function.
 * ARGUMENTS:
 *   - angle:
 *       DBL AngleInDegree;
 *   - vector:
 *       VEC R;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrRotate( DBL AngleInDegree, VEC R )
{
  DBL Angle = D2R(AngleInDegree), s = sin(Angle), c = cos(Angle);
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {c + V.X * V.X * (1 - c), V.X * V.Y * (1 - c) + V.Z * s, V.X * V.Z * (1 - c) - V.Y * s, 0},
      {V.Y * V.X * (1 - c) - V.Z * s, c + V.Y * V.Y * (1 - c), V.Y * V.Z * (1 - c) + V.X * s, 0},
      {V.Z * V.X * (1 - c) + V.Y * s, V.Z * V.Y * (1 - c) - V.X * s, c + V.Z * V.Z * (1 - c), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotate' function */

/* mutiplate two matrix function.
 * ARGUMENTS:
 *   - first matrix:
 *       MATR M1;
 *   - second matrix:
 *       MATR M2;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;

  r.M[0][0] = M1.M[0][0] * M2.M[0][0] + M1.M[0][1] * M2.M[1][0] + M1.M[0][2] * M2.M[2][0] +
    M1.M[0][3] * M2.M[3][0];
  r.M[0][1] = M1.M[0][0] * M2.M[0][1] + M1.M[0][1] * M2.M[1][1] + M1.M[0][2] * M2.M[2][1] +
    M1.M[0][3] * M2.M[3][1];
  r.M[0][2] = M1.M[0][0] * M2.M[0][2] + M1.M[0][1] * M2.M[1][2] + M1.M[0][2] * M2.M[2][2] +
    M1.M[0][3] * M2.M[3][2];
  r.M[0][3] = M1.M[0][0] * M2.M[0][3] + M1.M[0][1] * M2.M[1][3] + M1.M[0][2] * M2.M[2][3] +
    M1.M[0][3] * M2.M[3][3];

  r.M[1][0] = M1.M[1][0] * M2.M[0][0] + M1.M[1][1] * M2.M[1][0] + M1.M[1][2] * M2.M[2][0] +
    M1.M[1][3] * M2.M[3][0];
  r.M[1][1] = M1.M[1][0] * M2.M[0][1] + M1.M[1][1] * M2.M[1][1] + M1.M[1][2] * M2.M[2][1] +
    M1.M[1][3] * M2.M[3][1];
  r.M[1][2] = M1.M[1][0] * M2.M[0][2] + M1.M[1][1] * M2.M[1][2] + M1.M[1][2] * M2.M[2][2] +
    M1.M[1][3] * M2.M[3][2];
  r.M[1][3] = M1.M[1][0] * M2.M[0][3] + M1.M[1][1] * M2.M[1][3] + M1.M[1][2] * M2.M[2][3] +
    M1.M[1][3] * M2.M[3][3];

  r.M[2][0] = M1.M[2][0] * M2.M[0][0] + M1.M[2][1] * M2.M[1][0] + M1.M[2][2] * M2.M[2][0] +
    M1.M[2][3] * M2.M[3][0];
  r.M[2][1] = M1.M[2][0] * M2.M[0][1] + M1.M[2][1] * M2.M[1][1] + M1.M[2][2] * M2.M[2][1] +
    M1.M[2][3] * M2.M[3][1];
  r.M[2][2] = M1.M[2][0] * M2.M[0][2] + M1.M[2][1] * M2.M[1][2] + M1.M[2][2] * M2.M[2][2] +
    M1.M[2][3] * M2.M[3][2];
  r.M[2][3] = M1.M[2][0] * M2.M[0][3] + M1.M[2][1] * M2.M[1][3] + M1.M[2][2] * M2.M[2][3] +
    M1.M[2][3] * M2.M[3][3];

  r.M[3][0] = M1.M[3][0] * M2.M[0][0] + M1.M[3][1] * M2.M[1][0] + M1.M[3][2] * M2.M[2][0] +
    M1.M[3][3] * M2.M[3][0];
  r.M[3][1] = M1.M[3][0] * M2.M[0][1] + M1.M[3][1] * M2.M[1][1] + M1.M[3][2] * M2.M[2][1] +
    M1.M[3][3] * M2.M[3][1];
  r.M[3][2] = M1.M[3][0] * M2.M[0][2] + M1.M[3][1] * M2.M[1][2] + M1.M[3][2] * M2.M[2][2] +
    M1.M[3][3] * M2.M[3][2];
  r.M[3][3] = M1.M[3][0] * M2.M[0][3] + M1.M[3][1] * M2.M[1][3] + M1.M[3][2] * M2.M[2][3] +
    M1.M[3][3] * M2.M[3][3];
  return r;
} /* End of 'MatrMulMatr' function */

/* Count determinant of matrix 3x3 function.
 * ARGUMENTS:
 *   - matrix element:
 *       DBL A11, A12, A13,
 *           A21, A22, A23,
 *           A31, A32, A33;
 * RETURNS:
 *   (DBL) resalut determinant.
 */
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 +
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Count determinant of matrix 4x4 function.
 * ARGUMENTS:
 *   - matrix 4x4:
 *       MATR M;
 * RETURNS:
 *   (DBL) resalut determinant.
 */
__inline DBL MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                              M.M[2][1], M.M[2][2], M.M[2][3],
                              M.M[3][1], M.M[3][2], M.M[3][3]) +
    -M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                              M.M[2][0], M.M[2][1], M.M[2][3],
                              M.M[3][0], M.M[3][1], M.M[3][3]) +
    -M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
} /* End of 'MatrDeterm' function */

/* Inverse matrix function.
 * ARGUMENTS:
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) resalut matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;

  /* build adjoint matrix and divide by determinante */
  r.M[0][0] =
    MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]) / det;
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]) / det;
  r.M[2][0] =
    MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]) / det;
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]) / det;

  r.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[2][1], M.M[2][2], M.M[2][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]) / det;
  r.M[1][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]) / det;
  r.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[2][0], M.M[2][1], M.M[2][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]) / det;
  r.M[3][1] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]) / det;


  r.M[0][2] =
    MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[3][1], M.M[3][2], M.M[3][3]) / det;
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]) / det;
  r.M[2][2] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[3][0], M.M[3][1], M.M[3][3]) / det;
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]) / det;

  r.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                  M.M[1][1], M.M[1][2], M.M[1][3],
                  M.M[2][1], M.M[2][2], M.M[2][3]) / det;
  r.M[1][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3]) / det;
  r.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                  M.M[1][0], M.M[1][1], M.M[1][3],
                  M.M[2][0], M.M[2][1], M.M[2][3]) / det;
  r.M[3][3] =
    MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2]) / det;

  return r;
} /* End of 'MatrInverse' function */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */

#endif /* __MTH_H_ */

/* END OF 'MTH.H' FILE */
