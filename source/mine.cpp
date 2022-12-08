#include "field.hpp"
#include "buffer.hpp"
#include "setup.hpp"
#include "colour.hpp"
#include "display.hpp"
#include <stdio.h>

void clrscr()
{
    int n;
    for (n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}

Field parseArguments(int argc, char **argv)
{
    // Arguments:
    // if 1 or 2 args:
    // 1: quickClear 1/0 (true/false)
    // 2: difficulty 1-4
    // if 4 args
    // 1: quickClear
    // 2: x
    // 3: y
    // 4: numMines
    if (argc <= 1)
    {
        setGameMode();
        getQuickClearSettings();
        return Field(0, 0, 0);
    }
    QUICKCLEAR = argv[1][0] == '1';
    if (argc == 2 || argc == 4)
    {
        setGameMode();
        return Field(0, 0, 0);
    }
    if (argc == 3)
    {
        int mode = std::min(std::atoi(argv[2]), 4);
        if (mode <= 0)
            mode = 4;
        gameMode = (GAME_MODE)mode;
        return Field(0, 0, 0);
    }
    int l, b, m;
    l = std::max(1, std::min(std::atoi(argv[2]), 30));
    b = std::max(9, std::min(std::atoi(argv[3]), 16));
    m = std::max(1, std::atoi(argv[4]));
    gameMode = PRESET;
    return Field(l, b, m);
}

int main(int argc, char **argv)
{
    clrscr();
    Field field = parseArguments(argc, argv);
    while (true)
    {
        clrscr();

        dispBanner();
        field.drawField();
        dispFlagCounter();

        if (gameState != RUNNING)
            dispVictoryOrDefeat();
        else
            dispControls();

        writeBuf.disp();
        writeBuf.clear();

        if (gameState == RUNNING)
            field.getMove();
        else
            break;
    }

    std::cout << endl
              << reset;

    return 0;
}