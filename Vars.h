#pragma once
#include <Windows.h>

// Per-tab UI state
extern bool tab1_test;
extern bool tab1_switch;
extern bool tab2_test;
extern bool tab2_switch;
extern bool tab3_test;
extern bool tab3_switch;

// Per-tab sliders (not used in Settings/Themes)
extern float tab1_slider;
extern float tab2_slider;
extern float tab3_slider;

// Theme management
extern int current_theme; // 0: Dark, 1: Light, 2: Classic

// DLL module handle for uninject
extern HMODULE g_hModule;

