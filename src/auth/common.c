#include "common.h"

size_t get_message_length(uint8_t* message) {
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    return length;
}