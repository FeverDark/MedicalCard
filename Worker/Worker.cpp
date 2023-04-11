#include "pch.h"
#include "framework.h"
#include "Worker.h"

std::vector<Man*> _tempdb_;
//std::vector<Diagnosis> _tempdiagnosesdb_;

Man::Man() {}
Man::~Man() {}

Patient::Patient(int id = 0, std::wstring name = L"", std::wstring dob = L"", Diagnosis d = Diagnosis()) {
    this->id = id;
    this->name = name;
    this->dob = dob;
    if (d.text != L"", d.date != L"",d.workerid != 0) {
        this->a.push_back(d);
    }
}
Patient::~Patient() {}

Worker::Worker(int id = 0, std::wstring name = L"", std::wstring job = L"", std::string login = "", std::string password = "") {
    this->id = id;
    this->name = name;
    this->job = job;
    this->login = login;
    this->password = password;
}
Worker::~Worker() {}

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
        _tempdb_.push_back(new Patient(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i + 1]), Diagnosis()));
        /*std::cout << azColName[i - 1] << " " << argv[i - 1] << std::endl;
        std::cout << azColName[i] << " " << argv[i] << std::endl;
        std::cout << azColName[i + 1] << " " << argv[i + 1] << std::endl;*/
    }
    //std::cout << std::endl;
    return 0;
}

const char* getDiagnosesDataSql = "SELECT * FROM diagnoses";
int getDiagnosesData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i+=5) {
        for (int j = 0; j < _tempdb_.size(); ++j) {
            if (atoi(argv[i]) == _tempdb_[j]->getId()) {
                _tempdb_[i]->pushDiagnosis(Diagnosis(charToWstring(argv[i + 1]), charToWstring(argv[i + 2]), atoi(argv[i + 3])));
            }
        }
        /*std::cout << azColName[i - 1] << " " << argv[i - 1] << std::endl;
        std::cout << azColName[i] << " " << argv[i] << std::endl;
        std::cout << azColName[i + 1] << " " << argv[i + 1] << std::endl;
        std::cout << azColName[i + 2] << " " << argv[i + 2] << std::endl;
        std::cout << azColName[i + 3] << " " << argv[i + 3] << std::endl;*/
    }
    //std::cout << std::endl;
    return 0;
}

const char* getWorkersDataSql = "SELECT * FROM workers";
int getWorkersData(void* _, int argc, char** argv, char** azColName) {
    for (int i = 1; i <= argc; i += 5) {
        _tempdb_.push_back(new Worker(atoi(argv[i - 1]), charToWstring(argv[i]), charToWstring(argv[i+1]), std::string(argv[i + 2]), std::string(argv[i + 3])));
        /*std::cout << azColName[i - 1] << " " << argv[i - 1] << std::endl;
        std::cout << azColName[i] << " " << argv[i] << std::endl;
        std::cout << azColName[i + 1] << " " << argv[i + 1] << std::endl;
        std::cout << azColName[i + 2] << " " << argv[i + 2] << std::endl;
        std::cout << azColName[i + 3] << " " << argv[i + 3] << std::endl;*/
    }
    //std::cout << std::endl;
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
}
DB::~DB() {}
