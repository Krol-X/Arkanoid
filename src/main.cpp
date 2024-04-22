#include "game.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    Game game;
    game.Run();

    return 0;
}
