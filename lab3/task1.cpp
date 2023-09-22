#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void processorArchitecture() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    cout << "Processor architecture: ";
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_INTEL:
            cout << "x86 (32-bits)" << endl;
            break;
        case PROCESSOR_ARCHITECTURE_AMD64:
            cout << "x64 (32-bits)" << endl;
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            cout << "ARM" << std::endl;
            break;
        default:
            cout << "Unknown!" << endl;
            break;
    }
}

void numberOfHDD() {
    int diskCount = 0;
    for (char driveLetter = 'A'; driveLetter <= 'Z'; driveLetter++) {
        wstring rootPath = L"A:\\";
        UINT driveType = GetDriveType(reinterpret_cast<LPCSTR>(rootPath.c_str()));
        if (driveType == DRIVE_REMOVABLE) {
            diskCount++;
        }
    }
    cout << "Number of HDD drives: " << diskCount << endl;
}

void mathCoprocessor() {
    if (IsProcessorFeaturePresent(PF_FLOATING_POINT_EMULATED)) {
        cout << "Mathematical coprocessor: exists" << endl;
    } else {
        cout << "Mathematical coprocessor: missing" << endl;
    }
}

void displayType() {
    DISPLAY_DEVICE display;
    display.cb = sizeof(DISPLAY_DEVICE);
    if (EnumDisplayDevices(nullptr, 0, &display, 0)) {
        wcout << L"Display adapter type: " << display.DeviceString << endl;
    }
}

void RS232Port() {
    int comPortCount = 0;
    for (int portNumber = 1; portNumber <= 256; portNumber++) {
        wstring comPortName = L"\\\\.\\COM" + to_wstring(portNumber);
        HANDLE comPort = CreateFile(reinterpret_cast<LPCSTR>(comPortName.c_str()), GENERIC_READ | GENERIC_WRITE, 0,
                                    nullptr, OPEN_EXISTING, 0, nullptr);
        if (comPort != INVALID_HANDLE_VALUE) {
            comPortCount++;
            CloseHandle(comPort);
        }
    }
    cout << "Number of RS232 ports: " << comPortCount << endl;
}

void printers() {
    int printerCount = 0;
    PRINTER_INFO_2 *pInfo;
    DWORD dwBytesNeeded = 0;
    DWORD dwPrinterEnumFlags = PRINTER_ENUM_LOCAL | PRINTER_ENUM_CONNECTIONS;
    if (EnumPrinters(dwPrinterEnumFlags, nullptr, 2, nullptr, 0, &dwBytesNeeded,
                     nullptr)) {
        if (dwBytesNeeded > 0) {
            pInfo = reinterpret_cast<PRINTER_INFO_2 *>(malloc(dwBytesNeeded));
            if (pInfo != nullptr) {
                if (EnumPrinters(dwPrinterEnumFlags, nullptr, 2,
                                 reinterpret_cast<LPBYTE>(pInfo), dwBytesNeeded, &dwBytesNeeded, nullptr)) {
                    for (DWORD i = 0; i < pInfo->cJobs; i++) {
                        printerCount++;
                    }
                }
            }
            free(pInfo);
        }
    }
    cout << "Number of printers: " << printerCount << endl;
}

void memorySize() {
    MEMORYSTATUS memStatus;
    GlobalMemoryStatus(&memStatus);
    cout << "Memory size: " << memStatus.dwTotalPhys / 1024 << " kb" << endl;
}

void ssdSize() {
    MEMORYSTATUS extMemStatus;
    GlobalMemoryStatus(&extMemStatus);
    cout << "SSD size: " << static_cast<unsigned
    long>(extMemStatus.dwTotalVirtual / 1024) << " kb" << endl;
}

int main() {
    processorArchitecture();
    numberOfHDD();
    mathCoprocessor();
    displayType();
    RS232Port();
    printers();
    memorySize();
    ssdSize();

    return 0;
}

