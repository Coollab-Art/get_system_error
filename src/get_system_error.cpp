#include "Cool/get_system_error.hpp"

#if defined(_WIN32)
#include <windows.h>

namespace Cool {

static auto get_system_error_impl(DWORD error_id) -> std::string
{
    if (error_id == 0)
        return "";

    LPSTR      message_buffer{nullptr};
    auto const size = FormatMessage( // We use FormatMessage because it gives nicer error messages than strerror(errno)
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        error_id,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&message_buffer), // NOLINT(*reinterpret-cast)
        0,
        nullptr
    );
    if (message_buffer == nullptr)
        return "Unknown error code: " + std::to_string(error_id);

    auto message = std::string{message_buffer, size};
    LocalFree(message_buffer);
    return message;
}

auto get_system_error() -> std::string
{
    return get_system_error_impl(::GetLastError());
}

auto get_system_error(HRESULT hr) -> std::string
{
    return get_system_error_impl(static_cast<DWORD>(hr));
}

} // namespace Cool

#else
#include <cstring>

namespace Cool {

auto get_system_error() -> std::string
{
    auto message_buffer = std::string(128, '\0'); // Start with a reasonable buffer size

#ifdef _GNU_SOURCE
    // GNU version of strerror_r returns a char*
    char* const result = strerror_r(errno, &message_buffer[0], message_buffer.size());
    // The result may not use the provided buffer, but an internal buffer instead, so return a copy of that buffer
    if (result != message_buffer.data())
        return result;
#else
    // POSIX version of strerror_r returns an int and fills the buffer
    while (true) // Retry until the buffer is big enough
    {
        int const result = strerror_r(errno, &message_buffer[0], message_buffer.size());
        if (result == 0)
            break; // Success
        else if (result == ERANGE)
            message_buffer.resize(message_buffer.size() * 2);
        else
            return "Unknown error code: " + std::to_string(errno);
    }
#endif

    // Resize the string to fit the actual message length
    message_buffer.resize(std::strlen(message_buffer.c_str()));
    return message_buffer;
}

} // namespace Cool

#endif