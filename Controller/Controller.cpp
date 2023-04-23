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
    this->db->pushPatient(id, name, dob, creationdate, changedate, diagnosis);

}

void CController::deletePatient(int id) {
    int tempid = db->patients[id]->getId();
    delete db->patients[id];
    db->patients.erase(db->patients.begin() + id);
    this->db->deletePatient(tempid);
}

void CController::editPatient(int id, std::wstring name, std::wstring dob) {
    this->db->editPatient(id, name, dob);
    this->db->patients[id]->setName(name);
    this->db->patients[id]->setDob(dob);
};

void CController::editPatientDiagnosis(int id, std::wstring diagnosis, std::wstring date) {
    this->db->patients[id]->setDiagnosis(diagnosis, date);
    this->db->editPatientDiagnosis(id, diagnosis, date);
}

std::vector<std::wstring> CController::getProcedures(int id) {
    std::vector<std::wstring> a;
    std::vector<Operation> temp = db->patients[id]->getOperations();
    for (int i = 0; i < temp.size(); ++i) {
        a.push_back(temp[i].getText());
    }
    return a;
}

void CController::editProcedure(int id, std::wstring oldtext, std::wstring text) {
    db->editProcedure(id, text, oldtext);
    db->patients[id]->setOperation(oldtext, text);
}

void CController::deleteProcedure(int id, std::wstring text) {
    db->patients[id]->deleteOperation(text);
    db->deleteProcedure(id, text);
}

void CController::addProcedure(int id, std::wstring text, std::wstring date, int wid) {
    db->patients[id]->addOperation(text, date, wid);
    db->addProcedure(id, text, date, wid);
}