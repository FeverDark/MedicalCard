﻿#include "pch.h"
#include "framework.h"
#include "Worker.h"

std::vector<Man*> _tempworkersdb_;
std::vector<Man*> _temppatientssdb_;

Operation::Operation(std::wstring text = L"", std::wstring date = L"", int workerid = 0) {
    this->date = date;
    this->text = text;
    this->workerid = workerid;
}
std::wstring Operation::getText() {
    return this->text;
}
void Operation::setText(std::wstring text) {
    this->text = text;
}
Operation::~Operation() {}

Man::Man() {}
Man::~Man() {}
Man::Man(const Man&) {}
Man* Man::copy() { return NULL; }
const int& Man::getId() const { return NULL; }
void Man::pushOperation(Operation) {}
std::string Man::getLogin() { return NULL; }
std::string Man::getPassword() { return NULL; }
std::wstring Man::getName() { return NULL; }
std::wstring Man::getDob() { return NULL; }
std::wstring Man::getChange() { return NULL; }
std::wstring Man::getCreation() { return NULL; }
std::wstring Man::getDiagnosis() { return NULL; }
const std::vector<Operation>& Man::getOperations() const { return std::vector<Operation>(); };
void Man::setName(std::wstring name) {}
void Man::setDob(std::wstring dob) {}
void Man::setDiagnosis(std::wstring diagnosis, std::wstring date) {}
void Man::setOperation(std::wstring oldtext, std::wstring text) {}
void Man::deleteOperation(std::wstring text) {}
void Man::addOperation(std::wstring, std::wstring, int) {}

Patient::Patient(int id = 0, std::wstring name = L"", std::wstring dob = L"", std::wstring creationdate = L"", std::wstring changedate = L"", std::wstring diagnosis = L"") {
    this->id = id;
    this->name = name;
    this->dob = dob;
    this->creationdate = creationdate;
    this->changedate = changedate;
    this->diagnosis = diagnosis;
}
Patient::~Patient() {}
Patient::Patient(const Patient& temp) {
    id = temp.id;
    name = temp.name;
    dob = temp.dob;
    creationdate = temp.creationdate;
    changedate = temp.changedate;
    diagnosis = temp.diagnosis;
    a = temp.a;
}
Man* Patient::copy() { return new Patient(*this); }
const int& Patient::getId() const { return this->id; }
void Patient::pushOperation(Operation t) { this->a.push_back(t); }
std::wstring Patient::getName() { return this->name; }
std::wstring Patient::getDob() { return this->dob; }
std::wstring Patient::getChange() { return this->changedate; }
std::wstring Patient::getCreation() { return this->creationdate; }
std::wstring Patient::getDiagnosis() { return this->diagnosis; }
const std::vector<Operation>& Patient::getOperations() const { return a; };
void Patient::setName(std::wstring name) {
    this->name = name;
}
void Patient::setDob(std::wstring dob) {
    this->dob = dob;
}
void Patient::setDiagnosis(std::wstring diagnosis, std::wstring date) {
    this->diagnosis = diagnosis;
    this->changedate = date;
}
void Patient::setOperation(std::wstring oldtext, std::wstring text) {
    std::for_each(a.begin(), a.end(), [&](Operation& temp) {
        if (temp.getText() == oldtext) {
            temp.setText(text);
        }
    });
}
void Patient::deleteOperation(std::wstring text) {
    a.erase(std::remove_if(a.begin(), a.end(), [&](Operation& temp) {
        return temp.getText() == text;

    }), a.end());
}
void Patient::addOperation(std::wstring text, std::wstring date, int wid) {
    a.push_back(Operation(text, date, wid));
}

Worker::Worker(int id = 0, std::wstring name = L"", std::wstring job = L"", std::string login = "", std::string password = "") {
    this->id = id;
    this->name = name;
    this->job = job;
    this->login = login;
    this->password = password;
}
Worker::~Worker() {}
Worker::Worker(const Worker& temp) {
    id = temp.id;
    name = temp.name;
    job = temp.job;
    login = temp.login;
    password = temp.password;
}
Man* Worker::copy() { return new Worker(*this); }
const int& Worker::getId() const { return this->id; }
std::string Worker::getLogin() { return this->login; }
std::string Worker::getPassword() { return this->password; }
std::wstring Worker::getName() { return this->name; }

const char* creatingTables = "CREATE TABLE IF NOT EXISTS patients ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	name text NOT NULL,"
"	dob date NOT NULL,"
"	carddate date NOT NULL,"
"	changedate date NOT NULL,"
"	diagnosis text NOT NULL"
");"
"CREATE TABLE IF NOT EXISTS operations ("
"	people_id integer NOT NULL REFERENCES patients(id) ON DELETE CASCADE ON UPDATE CASCADE,"
"	textofoperation text NOT NULL,"
"	operationdate date NOT NULL,"
"	worker integer NOT NULL REFERENCES workers(id) ON DELETE SET NULL ON UPDATE CASCADE,"
"   PRIMARY KEY(\"people_id\", \"textofoperation\")"
");"
"CREATE TABLE IF NOT EXISTS workers ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	name text NOT NULL,"
"	job text NOT NULL,"
"	login text NOT NULL,"
"	password text NOT NULL"
");";

std::wstring charToWstring(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::string wstringToString(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

std::string getPatientsDataSql = "SELECT * FROM patients";
int getPatientsData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 6) {
        _temppatientssdb_.push_back(new Patient(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i + 1]), charToWstring(argv[i + 2]), charToWstring(argv[i + 3]), charToWstring(argv[i + 4])));
    }
    return 0;
}

std::string getOperationsDataSql = "SELECT * FROM operations";
int getOperations(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 4) {
        for (int j = 0; j < _temppatientssdb_.size(); ++j) {
            if ((int)atoi(argv[i - 1]) == (int)_temppatientssdb_[j]->getId()) {
                _temppatientssdb_[j]->pushOperation(Operation(charToWstring(argv[i]), charToWstring(argv[i + 1]), atoi(argv[i + 2])));
            }
        }
    }
    return 0;
}

std::string getWorkersDataSql = "SELECT * FROM workers";
int getWorkersData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 5) {
        _tempworkersdb_.push_back(new Worker(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i + 1]), std::string(argv[i + 2]), std::string(argv[i + 3])));
    }
    return 0;
}

DB::DB() {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getWorkersDataSql.c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getPatientsDataSql.c_str(), getPatientsData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }     
        if (SQLITE_OK != (rc = sqlite3_exec(db, getOperationsDataSql.c_str(), getOperations, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
    for (int i = 0; i < _temppatientssdb_.size(); ++i) {
        this->patients.push_back(_temppatientssdb_[i]->copy());
        delete _temppatientssdb_[i];
    }
    _temppatientssdb_.clear();
    for (int i = 0; i < _tempworkersdb_.size(); ++i) {
        this->workers.push_back(_tempworkersdb_[i]->copy());
        delete _tempworkersdb_[i];
    }
    _tempworkersdb_.clear();
}
void DB::pushPatient(int id, std::wstring name, std::wstring dob, std::wstring creationdate, std::wstring changedate, std::wstring diagnosis) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("INSERT INTO patients VALUES (" + std::to_string(id) + ", \"" + wstringToString(name) + "\", \"" + wstringToString(dob) + "\", \"" + wstringToString(creationdate) + "\", \"" + wstringToString(changedate) + "\", \"" + wstringToString(diagnosis)+"\");").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
void DB::deletePatient(int id) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("DELETE FROM patients WHERE id = " + std::to_string(id) + ";").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
void DB::editPatient(int id, std::wstring name, std::wstring dob) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("UPDATE patients SET name = \"" + wstringToString(name) + "\", dob = \"" + wstringToString(dob) +"\" WHERE id = " + std::to_string(this->patients[id]->getId()) + ";").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
void DB::editPatientDiagnosis(int id, std::wstring diagnosis, std::wstring date) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("UPDATE patients SET diagnosis = \"" + wstringToString(diagnosis) + "\", changedate = \"" + wstringToString(date) +"\" WHERE id = " + std::to_string(this->patients[id]->getId()) + ";").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
void DB::editProcedure(int id, std::wstring text, std::wstring oldtext) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("UPDATE operations SET textofoperation = \"" + wstringToString(text) + "\" WHERE people_id = " + std::to_string(this->patients[id]->getId()) + " AND textofoperation = \"" + wstringToString(oldtext) + "\";").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
void DB::deleteProcedure(int id, std::wstring text) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("DELETE FROM operations WHERE people_id = " + std::to_string(this->patients[id]->getId()) + " AND textofoperation = \"" + wstringToString(text) + "\";").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
void DB::addProcedure(int id, std::wstring text, std::wstring date, int wid) {
    sqlite3* db = NULL;
    int rc = 0;
    do {
        if (SQLITE_OK != (rc = sqlite3_initialize())) {
            std::cerr << "Failed to initialize library: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_open_v2("card.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))) {
            std::cerr << "Failed to open db: " << rc << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, creatingTables, NULL, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, std::string("INSERT INTO operations VALUES (" + std::to_string(this->patients[id]->getId()) + ", \"" + wstringToString(text) + "\", \"" + wstringToString(date) + "\", " + std::to_string(wid) + ");").c_str(), getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
    } while (false);
    if (NULL != db) sqlite3_close(db);
    sqlite3_shutdown();
}
DB::~DB() {
    for (std::vector<Man*>::iterator i = patients.begin(); i != patients.end(); ++i) {
        delete *i;
    }
    patients.clear();
    for (std::vector<Man*>::iterator i = workers.begin(); i != workers.end(); ++i) {
        delete* i;
    }
    workers.clear();
}
