#include "Console.h"
#include "Vars.h"

void CMD::Load() {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitle("Console");
    printf("LOADED MENU\n");
}