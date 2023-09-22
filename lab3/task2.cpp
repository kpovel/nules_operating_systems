#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

#define VK_LCTRL 0xA2
#define VK_RALT 0xA5
#define VK_Q 0x51

int main() {
    bool blockKey = false;
    int a, b, c, i;
    int tmp = 1;
    string s;
    char buffer[81];
    char ch;
    char* p;
    system("cls");
    setlocale(LC_ALL, "");
    cout << "To block the 'q' key input, press the hotkey combination: LCtrl + RAlt + Q" << endl;

    while (tmp != 0)
    {
        Sleep(4000);
        a = GetKeyState(VK_LCTRL);
        b = GetKeyState(VK_Q);
        c = GetKeyState(VK_RALT);
        cout << " Q--> " << b << " LCtrl--> " << a << " RALT--> " << c << "\n";
        cout << "To re-enter the hotkey combination, enter '1'.\nTo finish the input, enter '0': ";
        cin >> tmp;
    }

    if (a != 0 && b != 0 && c != 0)
    {
        Beep(300, 700);
        cout << "Hotkey combination LCtrl+RAlt+Q activated!" << endl;
        RegisterHotKey(0, 1, 0, 'q');
        blockKey = true;
    }
    else
    {
        cout << "Hotkey combination LCtrl+RAlt+Q not activated!" << endl;
        RegisterHotKey(0, 0, 0, 'q');
    }

    if (blockKey)
    {
        p = buffer;
        cout << "\nEnter a string of characters: ";
        cin >> s;
        i = 0;
        cout << "\nThe entered string of characters:\n";
        while (i < s.length())
        {
            ch = s[i];
            i++;
            if (ch != 'q')
            {
                *p = ch;
                p++;
                *p = '\0';
                cout << ch;
            }
        }
        cout << "\n";
    }
    else
    {
        UnregisterHotKey(nullptr, 0);
    }

    system("pause");
    return 0;
}

