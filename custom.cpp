#include <map>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "custom.h"




bool ImGui::Custom::FancyToggle(const char* label, bool* v) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    const float square_sz = 17;
    const float spacing = 6;
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect frame_bb(pos, pos + ImVec2(square_sz * 2, square_sz));
    const ImRect total_bb(pos, pos + ImVec2(square_sz * 2 + spacing + label_size.x, square_sz));

    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
    if (pressed) {
        *v = !(*v);
        MarkItemEdited(id);
    }

    struct toggle_animation { float animation; };

    std::map<ImGuiID, toggle_animation> anim;
    
    auto it_anim = anim.find(id);
    if (it_anim == anim.end()) {
        anim.insert({ id, { 0.0f } });
        it_anim = anim.find(id);
    }

    it_anim->second.animation = ImLerp(it_anim->second.animation, *v ? 1.0f : 0.0f, 0.12f * (1.0f - ImGui::GetIO().DeltaTime));

    RenderNavHighlight(total_bb, id);

    ImVec2 toggle_min = frame_bb.Min;
    ImVec2 toggle_max = frame_bb.Min + ImVec2(30, 15);

    RenderFrame(toggle_min, toggle_max, ImColor(15, 15, 16), false, 9.0f);
    RenderFrame(toggle_min, toggle_max, ImColor(ImGui::GetStyle().Colors[ImGuiCol_FrameBg].x, ImGui::GetStyle().Colors[ImGuiCol_FrameBg].y, ImGui::GetStyle().Colors[ImGuiCol_FrameBg].z, it_anim->second.animation), false, 9.0f);

    window->DrawList->AddCircleFilled(ImVec2(toggle_min.x + 7 + 14 * it_anim->second.animation, toggle_min.y + 7), 5.0f, ImColor(1.0f, 1.0f, 1.0f), 30);

    if (label_size.x > 0.0f)
        RenderText(ImVec2(toggle_max.x + spacing, pos.y + 1), label);

    return pressed;
}


// A simpler, different-looking toggle
bool ImGui::Custom::SimpleToggle(const char* label, bool* v) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    const float w = 36.0f;
    const float h = 18.0f;
    const float spacing = 6.0f;
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect frame_bb(pos, pos + ImVec2(w, h));
    const ImRect total_bb(pos, pos + ImVec2(w + (label_size.x > 0 ? spacing + label_size.x : 0.0f), h));

    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
    if (pressed) {
        *v = !(*v);
        MarkItemEdited(id);
    }

    // Colors
    ImU32 bg_on = GetColorU32(ImVec4(0.26f, 0.59f, 0.98f, 1.0f));
    ImU32 bg_off = GetColorU32(ImGuiCol_FrameBg);
    ImU32 knob = GetColorU32(ImVec4(1, 1, 1, 1));

    // Background
    window->DrawList->AddRectFilled(frame_bb.Min, frame_bb.Max, *v ? bg_on : bg_off, h * 0.5f);
    // Knob
    float knob_r = h * 0.45f;
    float t = *v ? 1.0f : 0.0f;
    float x = ImLerp(frame_bb.Min.x + knob_r + 2.0f, frame_bb.Max.x - knob_r - 2.0f, t);
    ImVec2 center(x, frame_bb.Min.y + h * 0.5f);
    window->DrawList->AddCircleFilled(center, knob_r, knob, 24);

    if (label_size.x > 0.0f)
        RenderText(ImVec2(frame_bb.Max.x + spacing, pos.y + (h - label_size.y) * 0.5f), label);

    return pressed;
}

