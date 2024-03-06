#pragma once
#include <list>
#include <string>
#include <map>

// Signals that can be emitted
enum class SIGNAL {
    FOOD_UP,
    POWER_UP,
    HIT,
    GHOST_HIT,
    BUTTON_PRESSED,
    QUIT_PRESSED,
    PLAY_PRESSED
};

/*
Idea of the this class to implement signal system:
some objects can emit signal others react on them
*/

// Objects which have to handle events
class Observer {
public:
    // Should be overrided and provide a realisation of signals it can be called
    virtual void handle_event(SIGNAL id) = 0;
    virtual ~Observer() {};
};

// Objects which can emit signals
class Observable {
public:
    void add_observer(SIGNAL id, Observer* observer);
    void remove_observer(SIGNAL id, Observer* observer);
    void emit_signal(SIGNAL id);
private:
    std::map<SIGNAL, std::list<Observer*>> observers_;
};
