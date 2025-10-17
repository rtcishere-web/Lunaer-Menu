#pragma once
#include <Windows.h>
#include "imgui/imgui.h"
#include "custom.h"

class Render {
private:
    static bool isOpened;
    static bool show_credits;
    static int current_theme;
    
    // Tab variables
    static bool tab1_test;
    static float tab1_slider;
    static bool tab1_switch;
    
    static bool tab2_test;
    static float tab2_slider;
    static bool tab2_switch;

public:
    static bool IsOpened();
    static void KeyManager();
    static void UI();
    
    // Forward declaration for the thread function
    static DWORD WINAPI UninjectThread(LPVOID lpParam);
};

// Static member declarations (defined in Render.cpp)
static bool isOpened;
static bool show_credits;
static int current_theme;
static bool tab1_test;
static float tab1_slider;
static bool tab1_switch;
static bool tab2_test;
static float tab2_slider;
static bool tab2_switch;