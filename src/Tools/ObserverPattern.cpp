#include "ObserverPattern.h"
#include <algorithm>

// void Observable::add_observer_to_coll_signal(Observer* observer) {
//     to_collision.push_back(observer);
// }

// void Observable::add_observer_to_food_signal(Observer* observer) {
//     to_food.push_back(observer);
// }

// void Observable::add_observer_to_powerUp_signal(Observer* observer) {
//     to_powerUp.push_back(observer);
// }

// void Observable::remove_observer(Observer* observer) {
//     auto it = std::find(to_collision.begin(), to_collision.end(), observer);
//     if (it != to_collision.end()) {
//         to_collision.erase(it);
//     }
// }

// void Observable::emit_collision_signal() {
//     for (auto obs : to_collision) {
//         obs->handle_collision_with_ghost();
//     }
// }

// void Observable::emit_food_signal() {
//     for (Observer* obs : to_food) {
//         obs->handle_food_signal();
//     }
// }


// void Observable::emit_food_signal() {
//     for (Observer* obs : to_powerUp) {
//         obs->handle_powerUp_signal();
//     }
// }

void Observable::add_observer(SIGNAL id, Observer* observer) {
    observers_[id].push_back(observer);
}

void Observable::remove_observer(SIGNAL id, Observer* observer) {
    if (observers_.find(id) != observers_.end()) {
        auto it = std::find(observers_[id].begin(), observers_[id].end(), observer);
        if (it != observers_[id].end()) {
            observers_[id].erase(it);
        }
    }
}


void Observable::emit_signal(SIGNAL id) {
    if (observers_.find(id) != observers_.end()) {
        for (auto obs : observers_[id]) {
            obs->handle_event(id);
        }
    }
}

