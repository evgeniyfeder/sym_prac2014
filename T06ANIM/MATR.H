/* FILENAME: MATR.C
 * PROGRAMMER: EF2
 * PURPOSE: Matrix defenition module.
 * LAST UPDATE: 06.06.2014
 */

#ifndef __MATR_H_
#define __MATR_H_

#include "def.h"
#include <math.h>

/* Main vector data type */
typedef struct tagVEC
{
  DBL X, Y, Z; /* Vector information */
} VEC;

/* Main matrix data type */
typedef struct tagMATR
{
  DBL A[4][4];  /* Matrix information */
} MATR;

/* Mult two matrix function */
MATR EF2_MatrMult4x4( MATR A, MATR B );

/* Create vector function.
 * ARGUMENTS:
 *   - coordinates of vector:
 *       DBL X, Y, Z;
 * RETURNS:
 *   (VEC) Vector in his data type.
 */
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
} /* End of 'VecSet' function */

/* Sum two vectors function.
 * ARGUMENTS:
 *   - two vectors for action:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X,
                V1.Y + V2.Y,
                V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Sub two vectors function.
 * ARGUMENTS:
 *   - two vectors for action:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X,
                V1.Y - V2.Y,
                V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Mul vector for a number function.
 * ARGUMENTS:
 *   - vector for action:
 *       VEC V;
 *   - number for action:
 *       BDL N;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecMulNum( VEC V, DBL N )
{
  return VecSet(V.X * N, V.Y * N, V.Z * N);
} /* End of 'VecMulNum' function */

/* Div vectir for a number function.
 * ARGUMENTS:
 *   - vector for action:
 *       VEC V;
 *   - number for action:
 *       BDL N;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecDivNum( VEC V, DBL N )
{
  return VecSet(V.X / N, V.Y / N, V.Z / N);
} /* End of 'VecDivNum' function */

/* Create 'negative' vector function.
 * ARGUMETNS:
 *   - vector for action:
 *       VEC V;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Dot vector for vector function.
 * ARGUMENTS:
 *   - vectors for action:
 *       VEC V1, V2;
 * RETURNS:
 *   (DBL) Result number.
 */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Do vector mult for vectors function
 * ARGUMENTS:
 *   - vectors for action:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y,
                V1.Z * V2.X - V1.X * V2.Z,
                V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Do normalize fo vector function.
 * ARGUMETNS:
 *   - vectors for action:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) Result vector.
 */
__inline VEC VecNormalize( VEC V )
{
  DBL len = V.X * V.X + V.Y * V.Y + V.Z * V.Z;
  if (len != 0 && len != 1)
  {
    len = sqrt(len);
    return VecSet(V.X / len, V.Y / len,  V.Z / len);
  }
  return V;
} /* End of 'VecNormalize' function */

/* Get Unity Matrix function */
MATR MatrIdenity( VOID );

/* Mult matrix for vector function */
VEC EF2_MatrMultVec( MATR A, VEC B );

/* Give matrix for position function */
MATR EF2_MatrViewLookAt( VEC Loc, VEC At, VEC Up );

#endif /* __MATR_H_ */

/* END OF 'MATR.H' FILE */
