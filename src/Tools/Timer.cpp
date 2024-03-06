

#include "Timer.h"

void Timer::start_timer(double seconds) {
    needed_time_ = sf::seconds(seconds);
    stop_point_ = sf::seconds(0);
    continue_point_ = sf::seconds(0);
    is_working_ = true;
    timer_.restart();
}

bool Timer::check_timer() {
    if (is_working_ && timer_.getElapsedTime() > needed_time_ + continue_point_ - stop_point_) {
        is_working_ = false;
        return true;
    }
    return false;
}

void Timer::stop_timer() {
    is_working_ = false;
    stop_point_ = timer_.getElapsedTime();
}

void Timer::continue_timer() {
    is_working_ = true;
    continue_point_ = timer_.getElapsedTime();
}

// :
//     std::chrono::time_point<std::chrono::high_resolution_clock> time_;
//     double needed_seconds;
//     bool is_working;