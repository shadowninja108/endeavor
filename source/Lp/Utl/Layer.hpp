#pragma once

#include <agl/lyr/Layer.hpp>

namespace Lp::Utl {
    /* TODO: make these return appropriate types. */
    /* gsys::Layer* */          agl::lyr::Layer* getGfxLayer(int);
    /* Lp::Sys::GfxLayer3D* */  agl::lyr::Layer* getGfxLayer3D(int);
    /* Lp::Sys::GfxLayer2D* */  agl::lyr::Layer* getGfxLayer2D(int);
}