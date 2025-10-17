#pragma once
namespace ImGui {
    namespace Custom {
        extern bool FancyToggle(const char* label, bool* v);
        // A different visual style toggle
        extern bool SimpleToggle(const char* label, bool* v);
    }
}