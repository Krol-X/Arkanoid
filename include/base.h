#pragma once

#define _USE_MATH_DEFINES
#include <mathfu/rect.h>
#include <mathfu/vector.h>

using Rect = mathfu::Rect<float>;
using Vect = mathfu::Vector<float, 2>;

#define IM_VEC2_CLASS_EXTRA                         \
        ImVec2(const Vect& f) { x = f.x; y = f.y; } \
        operator Vect() const { return Vect(x,y); }

#include <imgui.h>
#include <vector>
#include <cmath>
