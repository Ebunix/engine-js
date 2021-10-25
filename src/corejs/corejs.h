#pragma once
#include <string>

namespace corejs {
    int init(char* data);
    void destroy();
    void run(const std::string& code);
}

