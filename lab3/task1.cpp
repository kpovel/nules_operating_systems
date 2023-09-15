// g++ task1.cpp -o ./target/task1 && ./target/task1
#include <iostream>
#include <cstdlib>

int main() {
    system("sysctl hw.model");
    std::cout << "\n";

    system("system_profiler SPHardwareDataType");
    std::cout << "\n";

    system("sysctl hw.memsize");
    std::cout << "\n";

    system("sw_vers");
    std::cout << "\n";

    return 0;
}

