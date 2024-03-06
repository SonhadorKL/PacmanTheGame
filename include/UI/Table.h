#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Label.h"

/*
Class to show strings in rows
*/
class Table : public UI {
public:
    Table();

    // Name of the table
    void set_name(std::string name);
    // Add new line to the table
    void add_row(Label name);

    virtual sf::FloatRect get_boundaries() const override;
    virtual sf::Vector2f get_position() const override;
    virtual void set_position(sf::Vector2f new_position) override;

    void render(sf::RenderWindow&);
private:
    // Construct table
    void rebuild();

    std::vector<Label> rows_;
    Label name_;
};