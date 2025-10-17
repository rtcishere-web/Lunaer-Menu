#include "Render.h"
#include "Vars.h"

// Define static members
bool Render::isOpened = false;
bool Render::show_credits = false;
int Render::current_theme = 0;
bool Render::tab1_test = false;
float Render::tab1_slider = 90.0f;
bool Render::tab1_switch = false;
bool Render::tab2_test = false;
float Render::tab2_slider = 500.0f;
bool Render::tab2_switch = false;

// Thread proc to uninject the DLL safely
static DWORD WINAPI UninjectThread(LPVOID) {
    FreeLibraryAndExitThread(g_hModule, 0);
    return 0;
}

bool Render::IsOpened() {
    return isOpened;
}

void Render::KeyManager() {
    if (GetAsyncKeyState(VK_INSERT) & 1 || GetAsyncKeyState(VK_DELETE) & 1) {
        isOpened = !isOpened;
        ImGui::GetIO().MouseDrawCursor = isOpened;
    }
}

void Render::UI() {
    if (!isOpened) return;

    // Set up the main window
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
    
    bool show_window = true;
    if (ImGui::Begin("Lunaer", &show_window, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
        // Sidebar
        ImGui::BeginChild("Sidebar", ImVec2(150, 0), true);
        
        // Sidebar buttons
        const char* sidebar_items[] = {"AIMBOT", "VISUALS", "MISC", "SETTINGS", "CONFIG"};
        static int selected_item = 0;
        
        ImGui::Dummy(ImVec2(0, 10));
        for (int i = 0; i < IM_ARRAYSIZE(sidebar_items); i++) {
            bool is_selected = (selected_item == i);
            if (ImGui::Selectable(sidebar_items[i], is_selected, 0, ImVec2(130, 30))) {
                selected_item = i;
            }
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        
        // Add some spacing at the bottom
        ImGui::Dummy(ImVec2(0, ImGui::GetWindowHeight() - 200));
        
        // Add version text at the bottom
        ImGui::Text("v1.0.0");
        
        ImGui::EndChild();
        
        // Main content area
        ImGui::SameLine();
        ImGui::BeginChild("Content", ImVec2(0, 0), true);
        
        // Content based on selected tab
        switch (selected_item) {
            // Aimbot Tab
            case 0: {
                ImGui::Checkbox("Enable Aimbot", &tab1_test);
                ImGui::SliderFloat("FOV", &tab1_slider, 0.0f, 360.0f, "%.1f");
                ImGui::Custom::SimpleToggle("Visible Check", &tab1_switch);
                break;
            }
                
            // Visuals Tab
            case 1: {
                ImGui::Checkbox("Player ESP", &tab2_test);
                ImGui::SliderFloat("Max Distance", &tab2_slider, 0.0f, 1000.0f, "%.0f");
                ImGui::Custom::SimpleToggle("Show Health", &tab2_switch);
                break;
            }
            
            // MISC Tab
            case 2: {
                ImGui::Text("Miscellaneous settings will go here");
                break;
            }
                
            // Settings Tab
            case 3: {
                if (ImGui::BeginTabBar("SettingsTabs")) {
                    if (ImGui::BeginTabItem("Themes")) {
                        const char* themes[] = { "Dark", "Light", "Classic" };
                        if (ImGui::Combo("Theme", &current_theme, themes, IM_ARRAYSIZE(themes))) {
                            if (current_theme == 0) ImGui::StyleColorsDark();
                            else if (current_theme == 1) ImGui::StyleColorsLight();
                            else ImGui::StyleColorsClassic();
                        }
                        ImGui::EndTabItem();
                    }
                    
                    if (ImGui::BeginTabItem("Settings")) {
                        if (ImGui::Button("Uninject")) {
                            CreateThread(nullptr, 0, UninjectThread, nullptr, 0, nullptr);
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Close Game")) {
                            ExitProcess(0);
                        }
                        ImGui::EndTabItem();
                    }
                    
                    ImGui::EndTabBar();
                }
                break;
            }
            
            // CONFIG Tab
            case 4: {
                ImGui::Text("Configuration options will go here");
                break;
            }
        }
        
        ImGui::EndChild();
        ImGui::End();
    }
    ImGui::PopStyleVar();
}

// Thread function for uninjecting
DWORD WINAPI Render::UninjectThread(LPVOID lpParam) {
    Sleep(100);
    FreeLibraryAndExitThread(GetModuleHandleA(NULL), 0);
    return 0;
}