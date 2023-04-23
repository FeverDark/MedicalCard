#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Worker.h"

#ifdef CONTROLLER_EXPORTS
#define CONTROLLER_API __declspec(dllexport)
#else
#define CONTROLLER_API __declspec(dllimport)
#endif


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
    void editPatient(int, std::wstring, std::wstring);
    void editPatientDiagnosis(int, std::wstring, std::wstring);
    std::vector<std::wstring> getProcedures(int);
    void editProcedure(int, std::wstring, std::wstring);
    void deleteProcedure(int, std::wstring);
    void addProcedure(int, std::wstring, std::wstring, int);
};

#endif //CONTROLLER_H
