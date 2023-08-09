#pragma once
#include <SFML/Graphics.hpp>
#include "Sorter.h"
#include <string>

using namespace sf;

class Prog
{
public:

    void init(Vector2f windowSize);
    
    void update();

    void draw(RenderWindow& window);
    
private:

    void genNewValues(const int count);
    
    void reverseValues();
    
    bool reverseFlag;
    const int topOffset = 50;
    bool valsIsSorted;
    std::vector<int> values;
    RectangleShape tile;
    FloatRect wndSize;
    Text statusbar;
    Font font;
};
