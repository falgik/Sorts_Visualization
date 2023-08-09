#include "Program.h"

Prog prog;

int main()
{
    RenderWindow window(VideoMode(1000, 650), "Sorting");
    

    prog.init(Vector2f(window.getSize()));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        prog.update();
        prog.draw(window);

        window.display();
    }

    return 0;
    
}