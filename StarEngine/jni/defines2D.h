#pragma once

#include <stdint.h>

/// <summary>
/// The z-depth value for layer value 0.
/// </summary>
const float32 ZDEPTH_0 = 0.0f;
/// <summary>
/// The value to be multiplied with the layer value of a pos object.
/// This will be come the final Z-value of that position.
/// </summary>
/// <seealso cref="pos"></seealso>
const float32 LAYER_HEIGHT = 1.0f;

typedef int8_t lay;

/// <summary>
/// The default layer value to be used.
/// </summary>
const lay LAYER_DEF = 0;

#include "Helpers/2D/pos.h"
