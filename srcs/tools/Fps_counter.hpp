/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fps_counter.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:24:41 by ldutriez          #+#    #+#             */
/*   Updated: 2022/10/31 09:25:18 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LCPPGL_FPS_COUNTER_HPP
# define LCPPGL_FPS_COUNTER_HPP

# include <chrono>
# include <ctime>

// Class for timing events
class Interval
{
  private:
    typedef std::chrono::steady_clock Time;
    std::chrono::steady_clock::time_point initial_;

  public:
    inline Interval() : initial_(Time::now()) {}
    virtual ~Interval() {}

    inline unsigned int value() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>
            (Time::now() - initial_).count();
    }

    inline void reset()
    {
        initial_ = Time::now();
    }
};

// Class for calculating the fps of a loop or function
class Fps_counter
{
  protected:
    unsigned int m_fps;
    unsigned int m_fpscount;
    Interval m_fpsinterval;

  public:
    Fps_counter() : m_fps(0), m_fpscount(0), m_fpsinterval(Interval()) {}

    void update()
    {
        // increase the counter by one
        m_fpscount++;

        // one second elapsed?
        if (m_fpsinterval.value() >= 1000000)
        {
            // save the current counter value to m_fps
            m_fps = m_fpscount;

            // reset the counter and the interval
            m_fpscount = 0;
            m_fpsinterval.reset();
        }
    }

    unsigned int get() const
    {
        if (m_fps == 0)
        {
            return m_fpscount;
        }

        return m_fps;
    }

    unsigned int getFrameCount() const
    {
        return m_fpscount;
    }
};

#endif