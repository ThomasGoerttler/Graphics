
#pragma once

#include <QString>


class AbstractExercise
{
public:
    AbstractExercise(float animationFrame = 0.0f);

    void setActive(const bool active);
    const bool isActive() const;

    virtual const QString hints() const = 0;

    virtual void setAnimationFrame(float animFrame);

protected:
    virtual const bool initialize() = 0;

    virtual void enable();
    virtual void disable();

protected:
    bool m_initialized;
    bool m_active;
    float m_animationFrame;
};
