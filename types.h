#pragma once

#include <cstdint>
#include <math.h>

class TypeA
{
public:
    [[nodiscard]] int32_t GetInt() const { return m_IntValue; }
    void SetInt(int32_t value) { m_IntValue = value; }
private:
    int32_t m_IntValue{};
};

class TypeB
{
public:
    [[nodiscard]] float_t GetFloat() const { return m_FloatValue; }
    void SetFloat(float_t value) { m_FloatValue = value; }
private:
    float_t m_FloatValue{0.0f};
};
