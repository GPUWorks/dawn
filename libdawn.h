#pragma once

#include "duktape.h"

extern duk_ret_t object_destroy(duk_context *ctx);
extern duk_ret_t object_id(duk_context *ctx);
extern duk_ret_t object_isdirty(duk_context *ctx);
extern duk_ret_t object_clean(duk_context *ctx);

extern duk_ret_t image_width(duk_context *ctx);
extern duk_ret_t image_height(duk_context *ctx);

extern duk_ret_t planegeometry_create(duk_context *ctx);
extern duk_ret_t planegeometry_width(duk_context *ctx);
extern duk_ret_t planegeometry_height(duk_context *ctx);
extern duk_ret_t planegeometry_size(duk_context *ctx);

extern duk_ret_t ellipsisgeometry_create(duk_context *ctx);
extern duk_ret_t ellipsisgeometry_width(duk_context *ctx);
extern duk_ret_t ellipsisgeometry_height(duk_context *ctx);
extern duk_ret_t ellipsisgeometry_segments(duk_context *ctx);

extern duk_ret_t shadermaterial_create(duk_context *ctx);
extern duk_ret_t shadermaterial_uniform(duk_context *ctx);

extern duk_ret_t object3d_create(duk_context *ctx);
extern duk_ret_t object3d_transform(duk_context *ctx);
extern duk_ret_t object3d_visible(duk_context *ctx);
extern duk_ret_t object3d_appendchild(duk_context *ctx);
extern duk_ret_t object3d_removechild(duk_context *ctx);
extern duk_ret_t object3d_replacechild(duk_context *ctx);

extern duk_ret_t mesh3d_create(duk_context *ctx);
extern duk_ret_t mesh3d_geometry(duk_context *ctx);
extern duk_ret_t mesh3d_material(duk_context *ctx);

extern duk_ret_t orthographiccamera_create(duk_context *ctx);
extern duk_ret_t perspectivecamera_create(duk_context *ctx);

/* Module initialization */
static const duk_function_list_entry libdawn_funcs[] = {
    { "object_destroy", object_destroy, 1 },
    { "object_id", object_id, 1 },

    { "image_width", image_width, 1 },
    { "image_height", image_height, 1 },

    { "planegeometry_create", planegeometry_create, 2 },
    { "planegeometry_width", planegeometry_width, 2 },
    { "planegeometry_height", planegeometry_height, 2 },
    { "planegeometry_size", planegeometry_size, 3 },

    { "ellipsisgeometry_create", ellipsisgeometry_create, 3 },
    { "ellipsisgeometry_width", ellipsisgeometry_width, 2 },
    { "ellipsisgeometry_height", ellipsisgeometry_height, 2 },
    { "ellipsisgeometry_segments", ellipsisgeometry_segments, 3 },

    { "shadermaterial_create", shadermaterial_create, 1 },
    { "shadermaterial_uniform", shadermaterial_uniform, 3 },

    { "object3d_create", object3d_create, 0 },
    { "object3d_transform", object3d_transform, 2 },
    { "object3d_visible", object3d_visible, 2 },
    { "object3d_appendchild", object3d_appendchild, 2 },
    { "object3d_removechild", object3d_removechild, 2 },
    { "object3d_replacechild", object3d_replacechild, 3 },

    { "mesh3d_create", mesh3d_create, 2 },
    { "mesh3d_geometry", mesh3d_geometry, 2 },
    { "mesh3d_material", mesh3d_material, 2 },

    { "orthographiccamera_create", orthographiccamera_create, 6 },
    { "perspectivecamera_create", perspectivecamera_create, 4 },

    { NULL, NULL, 0 }
};

static const duk_function_list_entry libdawn_debug_funcs[] = {
    // TODO Remove the below two from api, UI Shouldn't need to worry
    { "object_isdirty", object_isdirty, 2 },
    { "object_clean", object_clean, 1 },

    { NULL, NULL, 0 }
};

extern duk_ret_t sdl_image_create(duk_context *ctx);

static const duk_function_list_entry libdawn_sdl_funcs[] = {
    // TODO Remove the below two from api, UI Shouldn't need to worry
    { "image_create", sdl_image_create, 1 },

    { NULL, NULL, 0 }
};

static const duk_number_list_entry libdawn_consts[] = {
    { "FLAG_FOO", (double) (1 << 0) },
    { NULL, 0.0 }
};

/* Init function name is dukopen_<modname>. */
extern duk_ret_t dukopen_libdawn(duk_context *ctx);
