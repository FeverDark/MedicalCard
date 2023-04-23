#include "Controller.h"

int main() {
    CController* controller = CController::getInstance();
    for (int i = 0; i < controller->db->patients.size(); ++i) {
        std::wcout << i << " " << controller->db->patients[i]->getId() << std::endl;
    }
    std::wcout << controller->db->workers.size();
    std::vector<std::wstring> temp = controller->getProcedures(0);
	return 0;
}