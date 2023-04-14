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

std::string sha_256(std::string temp) {
    return sha256(temp);
}