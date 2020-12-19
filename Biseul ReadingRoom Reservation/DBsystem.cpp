#include "DBsystem.h"
namespace biseul_rroom {

	DBsystem::DBsystem(std::string* filename, int max_name_length = 100) noexcept {

		DBsystem::max_name_length = max_name_length;
		DBsystem::filename = *filename;

	}
	DBsystem::DBsystem() noexcept {}
	DBsystem::~DBsystem() {
		terminate();
	}

	bool DBsystem::load() {
		char* error_msg;

		try {
			int check;
			sqlite3_open(DBsystem::filename.c_str(), &DB);
			check = sqlite3_exec(DB, ("CREATE TABLE IF NOT EXISTS studinf(name varchar(" + std::to_string(max_name_length) + "),x1 INT, x2 INT, x3 INT);").c_str(), NULL, NULL, &error_msg);
			if (check != SQLITE_OK) {
				throw error_msg;
			}
		}
		catch (char* error) {
			throw error;
		}
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::load(const std::string* filename) {
		char* error_msg;
		try {
			int check;
			//terminate();
			DBsystem::filename = *filename;
			sqlite3_open(filename->c_str(), &DB);
			check = sqlite3_exec(DB, ("CREATE TABLE IF NOT EXISTS studinf(name varchar(" + std::to_string(max_name_length) + "),x1 INT, x2 INT, x3 INT);").c_str(), NULL, NULL, &error_msg);
			if (check != SQLITE_OK) {
				throw error_msg;
			}
		}

		catch (char* error) {
			throw(error);
		}
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::terminate() {
		try {
			if (sqlite3_close_v2(DB) != SQLITE_OK) {
				throw signal::DBCLOSEFAIL;
			}
		}
		catch (signal x) {
			throw signal::DBCLOSEFAIL;
		}
		return (bool)signal::DBSUCCESS;
	}


	bool DBsystem::insert(std::string* name, int stud_id, _int64 rfid_id) {
		char* error_msg;
		int check;
		int warning = 0;
		std::string nametemp = "";
		std::string* nameptr = &nametemp;
		_int64 rfidnumtmp;
		int studtmp;
		try {
			if ((stud_id == 0) || (rfid_id == 0) || (name->length() > 99)||(rfid_id>9999999999)||(rfid_id<-9999999999) || (stud_id > 999999999) || (stud_id < -999999999)){
				throw signal::DBPARAMETERERR;
			}

			if ((get_studinf_bystudid(nameptr, stud_id, rfidnumtmp, warning)) || (get_studinf_byrfid(nameptr, studtmp, rfid_id, warning))) {
				throw signal::DBOVERLAP;
			}
			else {
				try {
					//cout << endl << "From DBsystem: " << filename << "~~" << " Inserting data...  ";
					std::string query = "insert into studinf VALUES ('" + *name + "', " + std::to_string(stud_id) + ", " + std::to_string(rfid_id) + ", " + std::to_string(warning) + ");";
					check = sqlite3_exec(DB, query.c_str(), NULL, NULL, &error_msg);
					if (check != SQLITE_OK) {
						throw error_msg;
					}
				}
				catch (char* error) {
					//cout << "Fail.#### error code: "<< *error << ". try again." << endl;
					throw error;
				}
				//cout << " insert success. " << endl;
				return (bool)signal::DBSUCCESS;
			}
		}
		catch (signal x) {
			throw x;
		}
	}

	bool DBsystem::modify_byrfid(const std::string* name, const int stud_id, const _int64 rfid_id, const int warning) {
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		sqlite3_stmt* stmt;

		int studtmp, warningtmp = 0;
		try {
			if ((rfid_id == 0) || (stud_id == 0) || (name->length() > 99) || (rfid_id > 9999999999) || (rfid_id < -9999999999) || (stud_id > 999999999) || (stud_id < -999999999) || (warning > 999999999) || (warning < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_byrfid(nameptr, studtmp, rfid_id, warningtmp)) {
				std::string query = "UPDATE studinf SET name = '" + *name + "', x1= " + std::to_string(stud_id) + ", x2= " + std::to_string(rfid_id) + ", x3= " + std::to_string(warning) + " WHERE x2== " + std::to_string(rfid_id);
				sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
				sqlite3_step(stmt);
				if (sqlite3_column_int64(stmt, 2) != SQLITE_OK) {
					throw signal::DBMODIFYERR;
				}
			}
			else {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			throw expn;
		}
		catch (signal err) {
			throw err;
		}
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::get_studinf_bystudid(std::string*& name, const int& stud_id, _int64& rfid_id, int& warning) {
		sqlite3_stmt* stmt;
		int id = stud_id;
		try {
			if ((stud_id == 0) || (stud_id > 999999999) || (stud_id < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			std::string query = "select name, x1, x2, x3 from studinf where x1 == " + std::to_string(id);
			sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
			sqlite3_step(stmt);
			if (sqlite3_column_int(stmt, 1) != stud_id) {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			return (bool)signal::DBNOTEXIST;
		}
		catch (signal x) {
			return false;
		}
		char* myname;
		myname = (char*)sqlite3_column_text(stmt, 0);
		*name += myname;
		rfid_id = sqlite3_column_int64(stmt, 2);
		warning = sqlite3_column_int(stmt, 3);
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::get_studinf_byrfid(std::string*& name, int& stud_id, const _int64& rfid_id, int& warning) {
		sqlite3_stmt* stmt;
		try {
			if ((rfid_id == 0) || (rfid_id > 9999999999) || (rfid_id < -9999999999)) {
				throw signal::DBPARAMETERERR;
			}
			std::string query = "select name, x1, x2, x3 from studinf where x2 == " + std::to_string(rfid_id);
			sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
			sqlite3_step(stmt);
			if (sqlite3_column_int64(stmt, 2) != rfid_id) {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			return (bool)signal::DBNOTEXIST;
		}
		catch (signal x) {
			return false;
		}
		char* myname;
		myname = (char*)sqlite3_column_text(stmt, 0);
		*name += myname;
		stud_id = sqlite3_column_int(stmt, 1);
		warning = sqlite3_column_int(stmt, 3);
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::remove_data_bystudid(int& stud_id) {
		sqlite3_stmt* stmt;
		std::string nametemp = "";
		std::string* nameptr = &nametemp;
		_int64 rfidtmp;
		int warntmp;
		try {
			if ((stud_id == 0) ||(stud_id > 999999999) || (stud_id < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_bystudid(nameptr, stud_id, rfidtmp, warntmp)) {
				try {
					std::string query = "DELETE from studinf where x1 == " + std::to_string(stud_id);
					sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
					sqlite3_step(stmt);
					if (get_studinf_bystudid(nameptr, stud_id, rfidtmp, warntmp)) {
						throw signal::DBREMOVEERR;
					}
				}
				catch (signal x) {
					throw x;
				}
				return (bool)signal::DBSUCCESS;
			}
			else {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			return (bool)signal::DBNOTEXIST;
		}
		catch (signal errorcode) {
			throw errorcode;
		}
	}

	bool DBsystem::remove_data_byrfidid(_int64& rfid_id) {
		sqlite3_stmt* stmt;
		std::string nametemp = "";
		std::string* nameptr = &nametemp;
		int studidtmp, warntmp;
		try {
			if ((rfid_id == 0) || (rfid_id > 9999999999) || (rfid_id < -9999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_byrfid(nameptr, studidtmp, rfid_id, warntmp)) {
				try {
					std::string query = "DELETE from studinf where x2 == " + std::to_string(rfid_id);
					sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
					sqlite3_step(stmt);
					if (get_studinf_byrfid(nameptr, studidtmp, rfid_id, warntmp)) {
						throw signal::DBREMOVEERR;
					}
				}
				catch (signal errorcode) {
					throw errorcode;
				}
				return (bool)signal::DBSUCCESS;
			}
			else {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			return (bool)signal::DBNOTEXIST;
		}
		catch (signal errorcode) {
			throw errorcode;
		}
	}

	bool DBsystem::add_penalty(int& stud_id) {
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		sqlite3_stmt* stmt;
		_int64 rfidtmp;
	    int warningtmp;
		try {
			if ((stud_id == 0) ||(stud_id > 999999999) || (stud_id < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_bystudid(nameptr, stud_id, rfidtmp, warningtmp)) {
				std::string query = "UPDATE studinf SET name = '" + nametmp + "', x1= " + std::to_string(stud_id) + ", x2= " + std::to_string(rfidtmp) + ", x3= " + std::to_string(warningtmp + 1) + " WHERE x1== " + std::to_string(stud_id);
				sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
				sqlite3_step(stmt);
				if (sqlite3_column_int(stmt, 1) != SQLITE_OK) {
					throw signal::DBMODIFYERR;
				}
			}
			else {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			throw expn;
		}
		catch (signal errorcode) {
			throw errorcode;
		}
		return (bool)signal::DBSUCCESS;
	}
	bool DBsystem::add_penalty_byrfid(_int64& rfid_id) {
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		sqlite3_stmt* stmt;
		int studtmp, warningtmp;
		try {
			if ((rfid_id == 0) || (rfid_id > 9999999999) || (rfid_id < -9999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_byrfid(nameptr, studtmp, rfid_id, warningtmp)) {
				std::string query = "UPDATE studinf SET name = '" + nametmp + "', x1= " + std::to_string(studtmp) + ", x2= " + std::to_string(rfid_id) + ", x3= " + std::to_string(warningtmp + 1) + " WHERE x2== " + std::to_string(rfid_id);
				sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
				sqlite3_step(stmt);
				if (sqlite3_column_int64(stmt, 2) != SQLITE_OK) {
					throw signal::DBMODIFYERR;
				}
			}
			else {
				throw (bool)signal::DBNOTEXIST;
			}
		}
		catch (bool expn) {
			throw expn;
		}
		catch (signal errorcode) {
			throw errorcode;
		}
		return (bool)signal::DBSUCCESS;
	}
}