//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2007-2013 zSpace, Inc.  All Rights Reserved.
//
//  File:       MathConverterD3d11_1.h
//  Content:    The math conversion class for converting to and from
//              D3d11 based math objects.
//  $Id:        
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZSPACE_MATH_CONVERTER_D3D11_1_H__
#define __ZSPACE_MATH_CONVERTER_D3D11_1_H__

#include "ZSpace/Common/CommonDefines.h"

#include "ZSpace/Common/Math/Matrix4.h"


#include <DirectXMath.h>


ZSPACE_COMMON_NS_BEGIN

/**
* @addtogroup Common
* @{
*
*   @addtogroup Math
*   @{
*/

/** Class which converts various zSpace structures into DirectX::XMMATRIX format.
*/
class MathConverterD3d11_1
{
public:
  /**
  * Convert a zSpace Matrix4 to a matrix in DirectX::XMMATRIX format.
  *
  * @param[in] src
  *   A matrix in zSpace Matrix4 format.
  * @param[out] dest
  *   A matrix in DirectX::XMMATRIX format.
  */
  static void convertMatrix4ToMatrixD3d11_1(const zspace::common::Matrix4& src, DirectX::XMMATRIX* dest);

  /**
  * Convert a matrix in DirectX::XMMATRIX format to a zSpace Matrix4.
  *
  * @param[in] src
  *   A matrix in DirectX::XMMATRIX format.
  * @param[out] dest
  *   A matrix in zSpace Matrix4 format.
  */
  static void convertMatrixD3d11_1ToMatrix4(const DirectX::XMMATRIX* src, zspace::common::Matrix4& dest);
};

/** @} */   // End of group: Math
/** @} */   // End of group: Common

inline void MathConverterD3d11_1::convertMatrix4ToMatrixD3d11_1(const zspace::common::Matrix4& src, DirectX::XMMATRIX* dest)
{
  if (!dest)
    return;

  // Transpose the matrix.
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      dest->r[i].m128_f32[j] = src[j][i];

  // Negate the z-direction.
  for (int i = 0; i < 4; i++)
    dest->r[2].m128_f32[i] = -dest->r[2].m128_f32[i];

  // Negate the z-components.
  for (int i = 0; i < 4; i++)
    dest->r[i].m128_f32[2] = -dest->r[i].m128_f32[2];
}


inline void MathConverterD3d11_1::convertMatrixD3d11_1ToMatrix4(const DirectX::XMMATRIX* src, zspace::common::Matrix4& dest)
{
  if (!src)
    return;

  // Transpose the matrix.
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      dest[i][j] = src->r[j].m128_f32[i];

  // Negate the z-direction.
  for (int i = 0; i < 4; i++)
    dest[2][i] = -dest[2][i];

  // Negate the z-components.
  for (int i = 0; i < 4; i++)
    dest[i][2] = -dest[i][2];
}

ZSPACE_COMMON_NS_END

#endif // __ZSPACE_MATH_CONVERTER_D3D11_1_H__