#include "pch.h"
#include "framework.h"
#include "Worker.h"

std::vector<Man*> _tempworkersdb_; // Юзаю глобалку, потому что хочу
std::vector<Man*> _temppatientssdb_; // Юзаю глобалку, потому что хочу

Man::Man() {}
Man::~Man() {}
Man::Man(const Man&) {}
Man* Man::copy() { return NULL; }
int Man::getId() {
    return NULL;
}
void Man::pushDiagnosis(Diagnosis) {}
std::string Man::getLogin() { return NULL; }
std::string Man::getPassword() { return NULL; }


Patient::Patient(int id = 0, std::wstring name = L"", std::wstring dob = L"", Diagnosis d = Diagnosis()) {
    this->id = id;
    this->name = name;
    this->dob = dob;
    if (d.text != L"", d.date != L"",d.workerid != 0) {
        this->a.push_back(d);
    }
}
Patient::~Patient() {}
Patient::Patient(const Patient& temp) {
    id = temp.id;
    name = temp.name;
    dob = temp.dob;
    a = temp.a;
}
Man* Patient::copy() {
    return new Patient(*this);
}
int Patient::getId() {
    return this->id;
}
void Patient::pushDiagnosis(Diagnosis t) {
    this->a.push_back(t);
}
std::string Patient::getLogin() { return NULL; }
std::string Patient::getPassword() { return NULL; }

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
Man* Worker::copy() {
    return new Worker(*this);
}
int Worker::getId() {
    return this->id;
}
void Worker::pushDiagnosis(Diagnosis) {}
std::string Worker::getLogin() {
    return this->login;
}
std::string Worker::getPassword() {
    return this->password;
}

const char* creatingTables = "CREATE TABLE IF NOT EXISTS patients ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	name text,"
"	dob date"
");"
"CREATE TABLE IF NOT EXISTS diagnoses ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	people_id integer,"
"	text text,"
"	date date,"
"	worker integer"
");"
"CREATE TABLE IF NOT EXISTS workers ("
"	id integer PRIMARY KEY AUTOINCREMENT,"
"	name text,"
"	job text,"
"	login text,"
"	password text"
");";

std::wstring charToWstring(char * _) {
    std::string __ = std::string(_);
    std::wstring ___;
    ___.assign(__.begin(), __.end());
    return ___;
}

const char* getPatientsDataSql = "SELECT * FROM patients";
int getPatientsData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 3) {
        _temppatientssdb_.push_back(new Patient(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i + 1]), Diagnosis()));
    }
    return 0;
}

const char* getDiagnosesDataSql = "SELECT * FROM diagnoses";
int getDiagnosesData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 5) {
        for (int j = 0; j < _temppatientssdb_.size(); ++j) {
            if (atoi(argv[i]) == _temppatientssdb_[j]->getId()) {
                _temppatientssdb_[j]->pushDiagnosis(Diagnosis(charToWstring(argv[i + 1]), charToWstring(argv[i + 2]), atoi(argv[i + 3])));
            }
        }
    }
    return 0;
}

const char* getWorkersDataSql = "SELECT * FROM workers";
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
        if (SQLITE_OK != (rc = sqlite3_exec(db, getWorkersDataSql, getWorkersData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getDiagnosesDataSql, getDiagnosesData, NULL, NULL))) {
            std::cerr << "Failed to exec: " << rc << ", " << sqlite3_errmsg(db) << std::endl;
            break;
        }
        if (SQLITE_OK != (rc = sqlite3_exec(db, getPatientsDataSql, getPatientsData, NULL, NULL))) {
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
DB::~DB() {
    for (int i = 0; i < patients.size(); ++i) {
        delete patients[i];
    }
    for (int i = 0; i < workers.size(); ++i) {
        delete workers[i];
    }
}
