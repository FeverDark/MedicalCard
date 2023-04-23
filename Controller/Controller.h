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
    void pushPatient(int, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring);    // Добавление пациента в дб - void(int ид, std::wstring имя, std::wstring дата рождения, std::wstring дата создания карты, std::wstring дата изменения карты, std::wstring диагноз)
    void deletePatient(int);                                                                        // Удаление пациента по ключу - void (int ид)
    void editPatient(int, std::wstring, std::wstring);                                              // Изменения информации о пациенте - void (int ид, std::wstring имя, std::wstring дата рождения)
    void editPatientDiagnosis(int, std::wstring, std::wstring);                                     // Изменение диагноза - void (int ид, std::wstring диагноз, std::wstring дата изменения карты)
    std::vector<std::wstring> getProcedures(int);                                                   // Полчение списка процедур у пациента - std::vector<std::wstring> (int ид)
    void editProcedure(int, std::wstring, std::wstring);                                            // Изменение процедуры по ключу - void (int ид, std::wstring старый_текст, std::wstring текст)
    void deleteProcedure(int, std::wstring);                                                        // Удаление процедуры по ключу - void (int ид, std::wstring текст)
    void addProcedure(int, std::wstring, std::wstring, int);                                        // Добавление процедуры - void (int ид, std::wstring текст, std::wstring дата, int ид_сотрудника)
};

#endif //CONTROLLER_H
