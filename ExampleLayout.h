#pragma once
#include <iostream>
#include <Windows.h>

namespace Pointers::Example {
	struct U_ExampleLayout {
		//public void Example(int value)
		void (*ExamplePointer)(void* instance, int value);
		
		//public static void Example_Static(int value)
		void (*ExamplePointer_Static)(int value); //class obj isnt required for static, so no __this param.

		void Setup() {
			ExamplePointer = (void(*)(void*, int)) reinterpret_cast<void**>((uint64_t)GetModuleHandleA("GameAssembly.dll") + 0x0);
			ExamplePointer_Static = (void(*)(int)) reinterpret_cast<void**>((uint64_t)GetModuleHandleA("GameAssembly.dll") + 0x0);
		}
	};
	extern U_ExampleLayout ExampleLayout;
}