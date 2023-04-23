#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <vector>
#include <set>
#include <algorithm>
#include "..\sqlite\sqlite3.h"

#ifdef WORKER_EXPORTS
#define WORKER_API __declspec(dllexport)
#else
#define WORKER_API __declspec(dllimport)
#endif

// Структура процедуры
struct WORKER_API Operation {
	std::wstring text;							// Сам текст процедуры
	std::wstring date;							// Дата выполнения
	int workerid;								// id сотрудника
	Operation(std::wstring, std::wstring, int);	// Конструктор(текст, дата, ид сотрудника)
	std::wstring getText();						// Геттер текста (std::wstrin)
	void setText(std::wstring);					// Сеттер текста (std::wstrin)
	~Operation();
};

class WORKER_API Man {
private:
public:
	Man();
	virtual ~Man();
	Man(const Man&);
	virtual Man* copy();												
	virtual const int& getId() const;											// Получение уникального идентификатора человека (пациент, сотрудник) (int)
	virtual void pushOperation(Operation);							// Добавление процедуры в карту пацинта
	virtual std::string getLogin();									// Получение логина сотрудника (std::string)
	virtual std::string getPassword();								// Получение пароля сотрудника (std::string)
	virtual std::wstring getName();									// Получение имени человека (пациент, сотрудник) (std::wstring)
	virtual std::wstring getDob();									// Получение даты рождения пациента (std::wstring)
	virtual std::wstring getChange();								// Получение даты последнего редактирования карты (std::wstring)
	virtual std::wstring getCreation();								// Получение даты создания карты (std::wstring)
	virtual std::wstring getDiagnosis();							// Получение диагноза пацинта (std::wstring)
	virtual const std::vector<Operation>& getOperations() const;	// Получение списка процедур пациента (const std::vector<Operation>&)
	virtual void setName(std::wstring);								// Установление имени пациента, сотрудника - void (std::wstring)
	virtual void setDob(std::wstring);								// Установление даты рождения пациента - void (std::wstring)
	virtual void setDiagnosis(std::wstring, std::wstring);			// Установление диагноза пациенту - void (std::wstring текст, std::wstring дата)
	virtual void setOperation(std::wstring, std::wstring);			// Редактирование процедуры пациента по ключу (человек, текст) - void (std::wstring текст, std::wstring старый текст)
	virtual void deleteOperation(std::wstring);						// Удалении процедуры пациента по ключу (человек, текст) - void (std::wstring текст)
	virtual void addOperation(std::wstring, std::wstring, int);		// Добавление процедуры пациенту - void (std::wstring текст, std::wstring дата, int ид сотрудника)
};

class WORKER_API Patient : public Man {
private:
	int id;
	std::wstring name;
	std::wstring dob;
	std::wstring creationdate;
	std::wstring changedate;
	std::wstring diagnosis;
	std::vector<Operation> a;
public:
	Patient(int, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring);
	~Patient();
	Patient(const Patient&);
	Man* copy() override;
	const int& getId() const override;
	void pushOperation(Operation) override;
	std::wstring getName() override;
	std::wstring getDob() override;
	std::wstring getChange() override;
	std::wstring getCreation() override;
	std::wstring getDiagnosis() override;
	const std::vector<Operation>& getOperations() const override;
	void setName(std::wstring) override;
	void setDob(std::wstring) override;
	void setDiagnosis(std::wstring, std::wstring) override;
	void setOperation(std::wstring, std::wstring) override;
	void deleteOperation(std::wstring) override;
	void addOperation(std::wstring, std::wstring, int) override;
};

class WORKER_API Worker : public Man {
private:
	int id;
	std::wstring name;
	std::wstring job;
	std::string login;
	std::string password;
public:
	Worker(int, std::wstring, std::wstring, std::string, std::string);
	~Worker();
	Worker(const Worker&);
	Man* copy() override;
	const int& getId() const override;
	std::string getLogin() override;
	std::string getPassword() override;
	std::wstring getName() override;
};

class WORKER_API DB {
private:
public:
	std::vector<Man*> patients;
	std::vector<Man*> workers;
	DB();
	void pushPatient(int, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring);	// Добавление пациента в дб - void (int ид, std::wstring имя, std::wstring дата рождения, std::wstring дата создания карты, std::wstring дата изменения карты, std::wstring диагноз)
	void deletePatient(int);																		// Удаление пациента по ключу - void (int ид)
	void editPatient(int, std::wstring, std::wstring);												// Изменения информации о пациенте - void (int ид, std::wstring имя, std::wstring дата рождения)
	void editPatientDiagnosis(int, std::wstring, std::wstring);										// Изменение диагноза - void (int ид, std::wstring диагноз, std::wstring дата изменения карты)
	~DB();
	void editProcedure(int, std::wstring, std::wstring);											// Изменение процедуры по ключу - void (int ид, std::wstring текст, std::wstring старый_текст)
	void deleteProcedure(int, std::wstring);														// Удаление процедуры по ключу - void (int ид, std::wstring текст)
	void addProcedure(int, std::wstring, std::wstring, int);										// Добавление процедуры - void (int ид, std::wstring текст, std::wstring дата, int ид_сотрудника)
};

#endif //WORKER_H
