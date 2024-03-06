#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

/*
Just a simple timer with ability to stop it
*/
class Timer {
public:
    Timer() = default;

    // Set timer
    void start_timer(double seconds);
    // Function to check if timer is ready
    bool check_timer();

    void stop_timer();

    void continue_timer();

private:
    sf::Clock timer_;
    sf::Time needed_time_;

    sf::Time stop_point_;
    sf::Time continue_point_;
    bool is_working_;
};