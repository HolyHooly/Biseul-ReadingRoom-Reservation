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
			int check1;
			int check2;
			int check;
			sqlite3_open(DBsystem::filename.c_str(), &DB);
			check1 = sqlite3_exec(DB, ("CREATE TABLE IF NOT EXISTS studinf(name varchar(" + std::to_string(max_name_length) + "),x1 INT, x2 INT, x3 INT, x4 INT);").c_str(), NULL, NULL, &error_msg);

			if (check1 != SQLITE_OK) {
				throw error_msg;
			}
			check2 = sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS datainf(typename varchar(30)),datanumber INT;", NULL, NULL, &error_msg);
			if (check2 != SQLITE_OK) {
				throw error_msg;
			}
			try {
				std::string query = "insert into datainf VALUES ('studinf',0);";
				check = sqlite3_exec(DB, query.c_str(), NULL, NULL, &error_msg);
				if (check != SQLITE_OK) {
					throw error_msg;
				}
			}
			catch (char* error) {
				//cout << "Fail.#### error code: "<< *error << ". try again." << endl;
				throw error;
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
			int check1;
			int check2;
			int check;
			//terminate();
			DBsystem::filename = *filename;
			sqlite3_open(filename->c_str(), &DB);
			check1 = sqlite3_exec(DB, ("CREATE TABLE IF NOT EXISTS studinf(name varchar(" + std::to_string(max_name_length) + "),x1 INT, x2 INT, x3 INT, x4 INT);").c_str(), NULL, NULL, &error_msg);
			if (check1 != SQLITE_OK) {
				throw error_msg;
			}
			check2 = sqlite3_exec(DB, "CREATE TABLE IF NOT EXISTS datainf(typename varchar(30),datanumber INT);", NULL, NULL, &error_msg);
			if (check2 != SQLITE_OK) {
				throw error_msg;
			}
			try {
				std::string query = "insert into datainf VALUES ('studinf',0);";
				check = sqlite3_exec(DB, query.c_str(), NULL, NULL, &error_msg);
				if (check != SQLITE_OK) {
					throw error_msg;
				}
			}
			catch (char* error) {
				//cout << "Fail.#### error code: "<< *error << ". try again." << endl;
				throw error;
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

	bool DBsystem::get_all_studinf(std::vector<studinf>& ret) {
		std::vector<studinf> datalst{};
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		int stud_idtmp, warningtmp, indextmp, totalnumber = 0;
		_int64 rfidtmp = 0;
		sqlite3_stmt* stmt;
		get_data_number(totalnumber);
		for (int i = 0; i < totalnumber; i++) {
			nametmp = "";
			try {
				if (get_studinf_byindex(nameptr, stud_idtmp, rfidtmp, warningtmp, i)) {
					indextmp = i;
					studinf newone(nametmp, stud_idtmp, rfidtmp, warningtmp, indextmp);
					datalst.push_back(newone);
				}
				else {
					throw (bool)signal::DBSORTERR;
				}
			}
			catch (signal x) { throw x; }
		}
		ret = datalst;
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::datasort(int axis, int mode) {
		std::vector<studinf> datalst{};
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		int stud_idtmp, warningtmp, indextmp, totalnumber = 0;
		_int64 rfidtmp = 0;
		sqlite3_stmt* stmt;
		get_data_number(totalnumber);
		for (int i = axis; i < totalnumber; i++) {
			nametmp = "";
			try {
				if (get_studinf_byindex(nameptr, stud_idtmp, rfidtmp, warningtmp, i)) {
					indextmp = i;
					studinf newone(nametmp, stud_idtmp, rfidtmp, warningtmp, indextmp);
					datalst.push_back(newone);
				}
				else {
					throw (bool)signal::DBSORTERR;
				}
			}
			catch (signal x) { throw x; }
		}
		for (std::vector<studinf>::iterator iter = datalst.begin(); iter != datalst.end(); iter++) {
			iter->index = iter->index + mode;
			modify_byrfid(&(iter->name), iter->stud_id, iter->rfid_id, iter->warning, iter->index);
		}
		return (bool)signal::DBSUCCESS;
	}

	/*bool DBsystem::update_data_index(int stud_id, int new_index) {

		char* error_msg;
		int check;
		int warning = 0;
		int index = 0;
		std::string nametemp = "";
		std::string* nameptr = &nametemp;
		_int64 rfidnumtmp;
		int studtmp;
		sqlite3_stmt* stmt;
		if ((stud_id == 0) || (stud_id > 999999999) || (stud_id < -999999999) || (new_index > 999999999) || (new_index < 0)) {
			throw signal::DBPARAMETERERR;
		}

		if (get_studinf_bystudid(nameptr, stud_id, rfidnumtmp, warning, index)) {
			try {
				std::string query = "UPDATE studinf SET name = '" + *nameptr + "', x1= " + std::to_string(stud_id) + ", x2= " + std::to_string(rfidnumtmp) + ", x3= " + std::to_string(warning) + ", x4= " + std::to_string(new_index) + " WHERE x1== " + std::to_string(stud_id);
				sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
				sqlite3_step(stmt);
				if (sqlite3_column_int64(stmt, 2) != SQLITE_OK) {
					throw signal::DBMODIFYERR;
				}
				else { return (bool)signal::DBSUCCESS; }
			}
			catch (signal x) { throw x; }
		}
		else { throw signal::DBNOTEXIST; }
	}*/


	bool DBsystem::insert(std::string* name, int stud_id, _int64 rfid_id) {
		char* error_msg;
		int check;
		int warning = 0;
		int index = 0;
		std::string nametemp = "";
		std::string* nameptr = &nametemp;
		_int64 rfidnumtmp;
		int studtmp;
		try {
			if ((stud_id == 0) || (rfid_id == 0) || (name->length() > 99)||(rfid_id>9999999999)||(rfid_id<-9999999999) || (stud_id > 999999999) || (stud_id < -999999999)){
				throw signal::DBPARAMETERERR;
			}

			if ((get_studinf_bystudid(nameptr, stud_id, rfidnumtmp, warning,index)) || (get_studinf_byrfid(nameptr, studtmp, rfid_id, warning,index))) {
				throw signal::DBOVERLAP;
			}
			else {
				try {
					get_data_number(index);
					std::string query = "insert into studinf VALUES ('" + *name + "', " + std::to_string(stud_id) + ", " + std::to_string(rfid_id) + ", " + std::to_string(warning) + ", " + std::to_string(index)+");";
					check = sqlite3_exec(DB, query.c_str(), NULL, NULL, &error_msg);
					if (check != SQLITE_OK) {
						throw error_msg;
					}
				}
				catch (char* error) {
					throw error;
				}
				update_total_data_number(index + 1);
				std::cout << index<<std::endl;
				return (bool)signal::DBSUCCESS;
			}
		}
		catch (signal x) {
			throw x;
		}
	}

	bool DBsystem::get_data_number(int& number) {
		sqlite3_stmt* stmt;
		std::string query = "select typename, datanumber from datainf where typename == 'studinf'";
		sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
		sqlite3_step(stmt);
		number = sqlite3_column_int(stmt, 1);
		return true;
	}

	bool DBsystem::update_total_data_number(int add) {
		sqlite3_stmt* stmt;
		std::string query = "UPDATE datainf SET typename = 'studinf', datanumber ="+std::to_string(add);
		try {
			sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
			sqlite3_step(stmt);
			if (sqlite3_column_int(stmt, 1) != SQLITE_OK) {
				throw signal::DBUPDATEERR;
			}
		}
		catch (signal sign) {
			throw sign;
		}
		return true;
	}

	bool DBsystem::modify_byrfid(const std::string* name, const int stud_id, const _int64 rfid_id, const int warning,const int index) {
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		sqlite3_stmt* stmt;

		int studtmp, warningtmp,indextmp = 0;
		try {
			if ((rfid_id == 0) || (stud_id == 0) || (name->length() > 99) || (rfid_id > 9999999999) || (rfid_id < -9999999999) || (stud_id > 999999999) || (stud_id < -999999999) || (warning > 999999999) || (warning < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_byrfid(nameptr, studtmp, rfid_id, warningtmp,indextmp)) {
				std::string query = "UPDATE studinf SET name = '" + *name + "', x1= " + std::to_string(stud_id) + ", x2= " + std::to_string(rfid_id) + ", x3= " + std::to_string(warning)  +", x4= "+std::to_string(index)+" WHERE x2== " + std::to_string(rfid_id);
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

	bool DBsystem::get_studinf_bystudid(std::string*& name, const int& stud_id, _int64& rfid_id, int& warning, int& index) {
		sqlite3_stmt* stmt;
		int id = stud_id;
		try {
			if ((stud_id == 0) || (stud_id > 999999999) || (stud_id < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			std::string query = "select name, x1, x2, x3, x4 from studinf where x1 == " + std::to_string(id);
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
		index = sqlite3_column_int(stmt, 4);
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::get_studinf_byrfid(std::string*& name, int& stud_id, const _int64& rfid_id, int& warning, int& index) {
		sqlite3_stmt* stmt;
		try {
			if ((rfid_id == 0) || (rfid_id > 9999999999) || (rfid_id < -9999999999)) {
				throw signal::DBPARAMETERERR;
			}
			std::string query = "select name, x1, x2, x3, x4 from studinf where x2 == " + std::to_string(rfid_id);
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
		index = sqlite3_column_int(stmt, 4);
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::get_studinf_byindex(std::string*& name, int& stud_id, _int64& rfid_id, int& warning, const int& index) {
		sqlite3_stmt* stmt;
		try {
			if ((index > 999999998) || (index <  0)) {
				throw signal::DBPARAMETERERR;
			}
			std::string query = "select name, x1, x2, x3, x4 from studinf where x4 == " + std::to_string(index);
			sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
			sqlite3_step(stmt);
			if (sqlite3_column_int(stmt, 4) != index) {
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
		rfid_id = sqlite3_column_int64(stmt, 2);
		warning = sqlite3_column_int(stmt, 3);
		return (bool)signal::DBSUCCESS;
	}

	bool DBsystem::remove_data_bystudid(int& stud_id) {
		sqlite3_stmt* stmt;
		std::string nametemp = "";
		std::string* nameptr = &nametemp;
		_int64 rfidtmp;
		int warntmp;
		int indextmp;
		int count;
		int totalnum;
		try {
			if ((stud_id == 0) ||(stud_id > 999999999) || (stud_id < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_bystudid(nameptr, stud_id, rfidtmp, warntmp,indextmp)) {
				try {
					count = indextmp;
					std::string query = "DELETE from studinf where x1 == " + std::to_string(stud_id);
					sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
					sqlite3_step(stmt);
					if (get_studinf_bystudid(nameptr, stud_id, rfidtmp, warntmp,indextmp)) {
						throw signal::DBREMOVEERR;
					}
				}
				catch (signal x) {
					throw x;
				}
				datasort(count+1, -1);
				get_data_number(totalnum);
				update_total_data_number(totalnum-1);
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
		int studidtmp;
		int warntmp;
		int indextmp;
		int count;
		int totalnum;
		try {
			if ((rfid_id == 0) || (rfid_id > 9999999999) || (rfid_id < -9999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_byrfid(nameptr, studidtmp, rfid_id, warntmp,indextmp)) {
				try {
					count = indextmp;
					std::string query = "DELETE from studinf where x2 == " + std::to_string(rfid_id);
					sqlite3_prepare_v2(DB, query.c_str(), -1, &stmt, 0);
					sqlite3_step(stmt);
					if (get_studinf_byrfid(nameptr, studidtmp, rfid_id, warntmp,indextmp)) {
						throw signal::DBREMOVEERR;
					}
				}
				catch (signal errorcode) {
					throw errorcode;
				}
				datasort(count + 1, -1);
				get_data_number(totalnum);
				update_total_data_number(totalnum - 1);
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
		int indextmp;
		try {
			if ((stud_id == 0) ||(stud_id > 999999999) || (stud_id < -999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_bystudid(nameptr, stud_id, rfidtmp, warningtmp,indextmp)) {
				std::string query = "UPDATE studinf SET name = '" + nametmp + "', x1= " + std::to_string(stud_id) + ", x2= " + std::to_string(rfidtmp) + ", x3= " + std::to_string(warningtmp + 1) +", x4="+std::to_string(indextmp) + " WHERE x1== " + std::to_string(stud_id);
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
		int indextmp;
		try {
			if ((rfid_id == 0) || (rfid_id > 9999999999) || (rfid_id < -9999999999)) {
				throw signal::DBPARAMETERERR;
			}
			if (get_studinf_byrfid(nameptr, studtmp, rfid_id, warningtmp,indextmp)) {
				std::string query = "UPDATE studinf SET name = '" + nametmp + "', x1= " + std::to_string(studtmp) + ", x2= " + std::to_string(rfid_id) + ", x3= " + std::to_string(warningtmp + 1) +",x4= "+std::to_string(indextmp)+ " WHERE x2== " + std::to_string(rfid_id);
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