#include "Timer.h"
#include<ctime>


Timer::Timer()
{
    m_started = m_running = m_hasChanged = m_elapsed = m_elapsedTotal = 0;
}

void Timer::Start()
{
    if (!m_started)
    {
        m_started = m_running = true;
        m_startTime = m_lastTime = m_currTime = time(NULL);
    }
    else if (m_started && !m_running)
    {
        Resume();
    }
}

void Timer::Pause()
{
    if (m_running)
    {
        m_running = m_hasChanged = false;
        m_elapsedTotal += m_elapsed;
        m_elapsed = 0;
    }
}

void Timer::Resume()
{
    if (m_started && !m_running)
    {
        m_startTime = time(NULL);
        m_running = true;
    }
}

void Timer::Update()
{
    if (m_running)
    {
        m_lastTime = m_currTime;
        m_currTime = time(NULL);
        if (m_lastTime != m_currTime)
        {
            m_hasChanged = true;
        }
        else
        {
            m_hasChanged = false;
        }
        m_elapsed = (int)m_currTime - (int)m_startTime;
    }
}

std::string Timer::GetTime()
{
    return std::to_string(m_elapsedTotal + m_elapsed);
}

bool Timer::HasChanged()
{
    return m_hasChanged;
}
