#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

int vsnprintf(char* buffer, size_t size, const char* __restrict format, va_list parameters) {
    size_t written = 0;

    while (*format != '\0') {
        if (written >= size - 1) { // Ensure room for null terminator
            buffer[size - 1] = '\0';
            return written;
        }

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;

            if (written + amount >= size) {
                amount = size - written - 1;
            }

            memcpy(&buffer[written], format, amount);
            written += amount;
            format += amount;
            continue;
        }

        const char* format_begun_at = format++;
        char temp[32]; // Buffer for number conversions

        if (*format == 'c') {
            format++;
            char c = (char) va_arg(parameters, int);
            if (written + 1 < size)
                buffer[written] = c;
            written++;
        } else if (*format == 's') {
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);

            if (written + len >= size) {
                len = size - written - 1;
            }

            memcpy(&buffer[written], str, len);
            written += len;
        } else if (*format == 'i' || *format == 'd') {
            format++;
            int d = va_arg(parameters, int);
            itoa(d, temp, 10); // Convert integer to string
            size_t len = strlen(temp);

            if (written + len >= size) {
                len = size - written - 1;
            }

            memcpy(&buffer[written], temp, len);
            written += len;
        } else if (*format == 'x' || *format == 'X') {
            char specifier = *format; // Store 'x' or 'X'
            format++;
            unsigned int hex = va_arg(parameters, unsigned int); // Use unsigned
            itoa(hex, temp, 16); // Convert to hex string

            if (specifier == 'X') { // Convert to uppercase if needed
                for (size_t i = 0; temp[i] != '\0'; i++)
                    if (temp[i] >= 'a' && temp[i] <= 'f')
                        temp[i] -= 32;
            }

            size_t len = strlen(temp);
            if (written + len >= size) {
                len = size - written - 1;
            }

            memcpy(&buffer[written], temp, len);
            written += len;
        } else if (*format == '0') {    // assume hex
            format++;
            int digits = *(format) - '0';
            format += 2;
            unsigned int hex = va_arg(parameters, unsigned int);
            itoa(hex, temp, 16);
            if (strlen(temp) < digits && digits < 9) {
                char t1 = temp[0];
                char t2 = temp[1];
                int len = digits - strlen(temp);
                for (int i = 0; i < len; i++) {
                    temp[i] = '0';
                    temp[i+1] = t1;
                    t1 = t2;
                    t2 = temp[i+2];
                    digits--;
                }
            }
            size_t len = strlen(temp);
            if (written + len >= size) {
                len = size - written - 1;
            }

            memcpy(&buffer[written], temp, len);
            written += len;
        } 
        else {
            format = format_begun_at;
            size_t len = strlen(format);

            if (written + len >= size) {
                len = size - written - 1;
            }

            memcpy(&buffer[written], format, len);
            written += len;
            format += len;
        }
    }
    buffer[written < size ? written : size - 1] = '\0'; // Ensure null termination
    return written;
}