#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Worker.h"
#include "sha256.h"

#ifdef CONTROLLER_EXPORTS
#define CONTROLLER_API __declspec(dllexport)
#else
#define CONTROLLER_API __declspec(dllimport)
#endif

CONTROLLER_API std::string sha_256(std::string);

class CONTROLLER_API CController {
private:
    static CController* p_instance;
    CController();
    CController(const CController&);
    CController& operator=(CController&);
public:
    DB* db;
    static CController* getInstance();
    ~CController();
    void pushPatient(int, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring);
    void deletePatient(int);
};

#endif //CONTROLLER_H
