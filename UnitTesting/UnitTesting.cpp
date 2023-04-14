#include "Controller.h"

struct _ {
    ~_() {
        _CrtDumpMemoryLeaks();
    }
} __;

int main() {
    CController* controller = CController::getInstance();
    std::string p = "1";
    std::cout << sha_256(p);
	return 0;
}