#include "game.h"

int _main(int argc, char** argv)
{
    Game game;
    game.Run();

    return 0;
}

#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc;
    wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    char** utf8_argv = new char* [argc];

    for (int i = 0; i < argc; ++i)
    {
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, NULL, 0, NULL, NULL);
        utf8_argv[i] = new char[size_needed];
        WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, utf8_argv[i], size_needed, NULL, NULL);
    }
    LocalFree(argv);

    int result = _main(argc, utf8_argv);

    for (int i = 0; i < argc; ++i)
    {
        delete[] utf8_argv[i];
    }
    delete[] utf8_argv;

    return result;
}
#endif

int main(int argc, char** argv)

{
    return _main(argc, argv);
}
