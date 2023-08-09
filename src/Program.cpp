#include "Program.h"

void Prog::init(Vector2f windowSize)
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());

    reverseFlag = true;

    tile.setFillColor(Color::White);
    tile.setOutlineColor(Color(127, 127, 127));

    wndSize.width = windowSize.x;
    wndSize.height = windowSize.y - topOffset;
    wndSize.top = topOffset;

    font.loadFromFile("PixelFont.ttf");

    statusbar.setFont(font);
    statusbar.setFillColor(Color::Green);
    statusbar.setCharacterSize(14);

    genNewValues(75);

    Sorter::setIterDelay(10);
}

void Prog::update()
{
    std::string statusBarStr = "Status: ";

    if (Sorter::sortIsEnd())
    {
        statusBarStr += (valsIsSorted ? "Sorted" : "Shuffled");

        if (Keyboard::isKeyPressed(Keyboard::Num1) && valsIsSorted)
        {
            genNewValues(75);
            valsIsSorted = false;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num2) && reverseFlag)
        {
            reverseValues();
            reverseFlag = false;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num3))
        {
            Sorter::beginSort(values, Sorter::SOTRTYPE::BUBLE);
            valsIsSorted = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num4))
        {
            Sorter::beginSort(values, Sorter::SOTRTYPE::COCTAIL);
            valsIsSorted = true;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Num5))
        {
            Sorter::beginSort(values, Sorter::SOTRTYPE::INSERTION);
            valsIsSorted = true;
        }

        if (!Keyboard::isKeyPressed(Keyboard::Num2) && !reverseFlag)
            reverseFlag = true;

        if (valsIsSorted)
            statusBarStr += "\tNum1 - Shuffle | ";
        else
            statusBarStr += "\t\t\t";

        statusBarStr += "Num2 - Reverse | Num3 - Buble sort | Num4 - Coctail sort | Num5 - Isertion sort";

    }
    else
    {
        switch (Sorter::getCurrSortType())
        {
        case Sorter::SOTRTYPE::BUBLE:
            statusBarStr += "Buble sorting...";
            break;
        case Sorter::SOTRTYPE::COCTAIL:
            statusBarStr += "Coctail sorting...";
            break;
        case Sorter::SOTRTYPE::INSERTION:
            statusBarStr += "Isertion sorting...";
            break;
        }

    }

    statusBarStr += "\nSwaps: " + std::to_string(Sorter::getLastSwapCount());

    statusbar.setString(statusBarStr);
}

void Prog::draw(RenderWindow& window)
{
    for (int i = 0; i < values.size(); i++)
    {
        float y = (values[i] * wndSize.height) / values.size();
        tile.setSize(Vector2f(tile.getSize().x, y));
        tile.setPosition(tile.getSize().x * i + wndSize.left, wndSize.height - y + wndSize.top);
        tile.setFillColor(std::find(Sorter::getIndexs().cbegin(), Sorter::getIndexs().cend(), i) != Sorter::getIndexs().cend() ? Color::Red : Color::White);
        window.draw(tile);
    }

    window.draw(statusbar);
}

void Prog::genNewValues(const int count)
{
    if (count != values.size())
    {
        values.resize(count);
        for (int i = 0; i < count; i++)
            values[i] = count - i;
    }

    std::random_shuffle(values.begin(), values.end());

    float x = wndSize.width / count;
    tile.setSize(Vector2f(x, 0));
    tile.setOutlineThickness(x >= 3 ? -1 : 0);
}

void Prog::reverseValues()
{
    std::reverse(values.begin(), values.end());
}
