#pragma once

void create_hook(void* target, void* detour, void** orig)
{
	MH_CreateHook(target, detour, orig);
	MH_EnableHook(target);
}

#define HOOK(offset, detour, orig) create_hook(reinterpret_cast<void**>((uint64_t)GetModuleHandleA("GameAssembly.dll") + offset), &detour, (void**)&orig)

void (*old_ExampleInline)(void* instance);
void ExampleInline(void* instance) {
	return old_ExampleInline(instance);
}

bool (*old_ExampleBool)(void* instance);
bool ExampleBool(void* instance) {
	if (instance != nullptr) { //if (instance != nullptr && toggle) - if you want it toggled.
		return true;
	}
	return old_ExampleBool(instance);
}


void loadHooks() {
	MH_Initialize();
	HOOK(0x0, ExampleInline, old_ExampleInline);
	HOOK(0x0, ExampleBool, old_ExampleBool);
}

