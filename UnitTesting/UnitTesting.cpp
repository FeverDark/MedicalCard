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
    for (int i = 0; i < controller->db->patients.size(); ++i) {
        std::wcout << controller->db->patients[i]->getDob() << std::endl;
        std::wcout << controller->db->patients[i]->getCreation() << std::endl;
  }
	return 0;
}