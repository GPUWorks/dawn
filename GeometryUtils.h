#pragma once

#include <string>
#include <cstdint>
#include "types.h"
#include "Path.h"

namespace dawn
{
    class GeometryUtils
    {
    public:
        static bool point_in_triangle(vec2f P, vec2f A, vec2f B, vec2f C);
        static bool is_ear(int ai, int bi, int ci, const vec2farray &vertices);
        static void triangulate_ec(const vec2farray &vertices, std::vector<uint8_t> &indices);
        static void create_uvs(const vec2farray &vertices, vec2farray &uvs, vec4f uv);

        static void arc(vec2farray &positions, float cx, float cy, float r, float start, float sweep);

        static void fill(const Path *path, vec2farray &positions, std::vector<uint8_t> &indices);
        static void stroke(const Path *path, float strokewidth, vec2farray &positions, std::vector<uint8_t> &indices);
    };
}
