#include "Cool/get_system_error.hpp"

#if defined(_WIN32)
#include <windows.h>

namespace Cool {

auto get_system_error() -> std::string
{
    DWORD const error_id = ::GetLastError();
    if (error_id == 0)
        return "";

    LPSTR      message_buffer{nullptr};
    auto const size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        error_id,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&message_buffer), // NOLINT(*reinterpret-cast)
        0,
        nullptr
    );

    auto message = std::string{message_buffer, size};
    LocalFree(message_buffer);
    return message;
}

} // namespace Cool

#else

namespace Cool {

auto get_system_error() -> std::string
{
    auto message_buffer = std::string{128, '\0'}; // Start with an initial size of 128 characters
    while (true)
    {
        int const result = strerror_r(errno, &message_buffer[0], message_buffer.size());
        if (result == 0)
        {
            // Success: Trim any excess null characters and return the message
            message_buffer.resize(std::strlen(message_buffer.c_str()));
            return message_buffer;
        }
        else if (result == ERANGE)
        {
            // Buffer too small: Double the size and retry
            message_buffer.resize(message_buffer.size() * 2);
        }
        else
        {
            // Unknown error: Return a generic error message
            return "Unknown error code: " + std::to_string(errno);
        }
    }
}

} // namespace Cool

#endif