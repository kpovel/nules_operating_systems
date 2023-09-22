#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <cstdio>

#define ARRAY_SIZE 1024

int main() {
    LPVOID drivers[ARRAY_SIZE];
    DWORD cbNeeded;
    int cDrivers, i;

    if (!EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) || cbNeeded >= sizeof(drivers)) {
        _tprintf(TEXT("EnumDeviceDrivers failed; array size needed is %llu\n"), cbNeeded / sizeof(LPVOID));
        return 1;
    }

    TCHAR szDriver[ARRAY_SIZE];
    cDrivers = cbNeeded / sizeof(drivers[0]);

    _tprintf(TEXT("There are %d drivers:\n"), cDrivers);
    for (i = 0; i < cDrivers; i++) {
        if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver) / sizeof(szDriver[0]))) {
            _tprintf(TEXT("%d: %s\n"), i + 1, szDriver);
        }
    }

    return 0;
}