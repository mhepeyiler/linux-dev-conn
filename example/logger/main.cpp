#include "logger.h"

int main() {
    LOG_TRACE("Trace test");
    LOG_DEBUG("Debug test");
    LOG_INFO("Info test");
    LOG_WARN("Warn test");
    LOG_ERROR("Error test");
    LOG_FATAL("Fatal test");

    LOG_TRACE("Trace test with param %d", 5);
    LOG_DEBUG("Debug test with param %s", "dummy");
    LOG_INFO("Info test with param %f", 5.0);
    LOG_WARN("Warn test with param %d", 50);
    LOG_ERROR("Error test with param %c",  'A');
    LOG_FATAL("Fatal test with param %d", 9);
}