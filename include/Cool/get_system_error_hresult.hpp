#if defined(_WIN32)
#pragma once
#include <windows.h>
#include <string>

namespace Cool {

auto get_system_error(HRESULT) -> std::string;

} // namespace Cool
#endif