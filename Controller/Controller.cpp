#include "pch.h"
#include "framework.h"
#include "Controller.h"

CController::CController() {
    db = new DB();
}

CController* CController::getInstance() {
    if (!p_instance)
        p_instance = new CController();
    return p_instance;
}
CController::~CController() {
    delete db;
};

CController* CController::p_instance = 0;

void CController::pushPatient(int id = 0, std::wstring name = L"", std::wstring dob = L"", std::wstring creationdate = L"", std::wstring changedate = L"", std::wstring diagnosis = L"") {
	this->db->patients.push_back(new Patient(id, name, dob, creationdate, changedate, diagnosis));
}

void CController::deletePatient(int id) {
    delete db->patients[id];
    db->patients.erase(db->patients.begin() + id);
}

std::string sha_256(std::string temp) {
    return sha256(temp);
}