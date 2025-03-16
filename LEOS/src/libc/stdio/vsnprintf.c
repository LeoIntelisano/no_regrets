#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

int vsnprintf(char* buffer, size_t size, const char* __restrict format, va_list parameters) {
    size_t written = 0;

    while (*format != '\0') {
        if (written >= size - 1) { // Ensure room for null terminator
            // Truncate and null-terminate the buffer
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
                amount = size - written - 1; // Prevent overflow
            }

            memcpy(&buffer[written], format, amount);
            written += amount;
            format += amount;
            continue;
        }

        const char* format_begun_at = format++;

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
            if (d == 0) {
                if (written < size - 1)
                    buffer[written++] = '0';
            } else {
                char temp[32];
                int index = 0;
                int neg = (d < 0);
                if (neg) d = -d;
        
                while (d) {
                    temp[index++] = (d % 10) + '0';
                    d /= 10;
                }
                if (neg && written < size - 1)
                    buffer[written++] = '-';
                // Copy in correct order
                while (index > 0 && written < size - 1)
                    buffer[written++] = temp[--index];
            }
        } else if (*format == 'x' || *format == 'X') {
            char temp[32];  // Enough for 32-bit integer
            int index = 0;
            unsigned int hex = va_arg(parameters, unsigned int);
        
            if (hex == 0) {
                if (written < size - 1)
                    buffer[written++] = '0';
            } else {
                while (hex) {
                    int temp_val = hex % 16;
                    temp[index++] = (temp_val < 10) ? 
                                    (temp_val + '0') : 
                                    (temp_val - 10 + ((*format == 'x') ? 'a' : 'A'));
                    hex /= 16;
                }
               
                // Copy in correct order
                while (index > 0 && written < size - 1)
                    buffer[written++] = temp[--index];
            }
            format++;
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