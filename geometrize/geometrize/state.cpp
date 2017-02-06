#include "state.h"

#include <cstdint>
#include <vector>

#include "bitmap/bitmap.h"
#include "core.h"
#include "shape/shape.h"
#include "shape/shapefactory.h"
#include "shape/shapetypes.h"
#include "scanline.h"

namespace geometrize
{

State::State(const shapes::ShapeTypes shapeTypes, const std::uint32_t alpha, const std::uint32_t width, const std::uint32_t height) :
    m_score{-1.0f}, m_alpha{alpha}, m_shape{geometrize::randomShapeOf(shapeTypes, width, height)}
{}

State& State::operator=(const geometrize::State& other)
{
    if(this != &other) {
        m_shape = other.m_shape->clone();
        m_score = other.m_score;
        m_alpha = other.m_alpha;
    }
    return *this;
}

State::State(const geometrize::State& other)
{
    m_shape = other.m_shape->clone();
    m_score = other.m_score;
    m_alpha = other.m_alpha;
}

float State::calculateEnergy(const geometrize::Bitmap& target, const geometrize::Bitmap& current, geometrize::Bitmap& buffer)
{
    if(m_score < 0) {
        m_score = geometrize::core::energy(m_shape->rasterize(), m_alpha, target, current, buffer, m_score);
    }
    return m_score;
}

geometrize::State State::mutate()
{
    geometrize::State oldState(*this);
    oldState.m_score = -1;
    m_shape->mutate();
    m_score = -1;
    return oldState;
}

}