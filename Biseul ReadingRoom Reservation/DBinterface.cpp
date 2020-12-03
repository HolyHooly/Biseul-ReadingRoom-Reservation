#include "DBInterface.h"
namespace biseul_rroom {

	DBinterface::DBinterface()noexcept {
		try {
			dbsys.load();
		}
		catch (char* error) {
			exception.scenario(error);
		}
	}
	DBinterface::DBinterface(std::string filename)noexcept {
		try {
			dbsys.load(&filename);
		}
		catch (char* error) {
			exception.scenario(error);
			//throw false;
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			//throw false;
		}
	}
	bool DBinterface::closeDB() {
		try {
			dbsys.terminate();
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			return false;
		}
		return true;
	}
	bool DBinterface::openDB(std::string* filename) {
		try {
			dbsys.load(filename);
		}
		catch (char* error) {
			exception.scenario(error);
			return false;
		}
		return true;
	}
	bool DBinterface::insert(std::string* name, int stud_id, int rfid_id) {
		try {
			dbsys.insert(name, stud_id, rfid_id);
			return true;

		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		catch (char* error) {
			exception.scenario(error);
			return false;
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			return false;
		}
	}
	bool DBinterface::modify_byrfid(const std::string name, const int stud_id, const int rfid_id, const int warning) {
		try {
			const std::string* nameptr = &name;
			dbsys.modify_byrfid(nameptr, stud_id, rfid_id, warning);
		}
		catch (bool expn) {
			return false;
		}
		catch (signal errorcode) {
			return false;
		}
		return true;
	}
	bool DBinterface::remove(int rfid_id) {
		try {
			if (dbsys.remove_data_byrfidid(rfid_id)) {
				return true;
			}
			else {
				throw false;
			}
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			return false;
		}
	}
	bool DBinterface::remove_by_studid(int stud_id) {
		try {
			if (dbsys.remove_data_bystudid(stud_id)) {
				return true;
			}
			else {
				throw false;
			}
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			return false;
		}
	}
	bool DBinterface::existence_check(int stud_id) {
		try {
			std::string nametmp = "";
			std::string* nameptr = &nametmp;
			int rfid_id, warntmp;
			if (dbsys.get_studinf_bystudid(nameptr, stud_id, rfid_id, warntmp)) {
				return true;
			}
			else {
				return false;
			}
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
	}

	bool DBinterface::get_studinf(std::string*& name, const int& stud_id, int& rfid, int& warning) {
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		int rfid_id, warntmp;
		try {
			if (dbsys.get_studinf_bystudid(nameptr, stud_id, rfid_id, warntmp)) {}
			else {
				return false;
			}
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		*name = nametmp;
		rfid = rfid_id;
		warning = warntmp;
		return true;
	}
	bool DBinterface::get_studinf_byrfid(std::string*& name, int& stud_id, const int& rfid, int& warning) {
		std::string nametmp = "";
		std::string* nameptr = &nametmp;
		int studtmp, warntmp;
		try {
			if (dbsys.get_studinf_byrfid(nameptr, studtmp, rfid, warntmp)) {
			}
			else {
				return false;
			}
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		*name = nametmp;
		stud_id = studtmp;
		warning = warntmp;
		return true;
	}

	bool DBinterface::give_penalty(int stud_id) {
		try {
			dbsys.add_penalty(stud_id);
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			return false;
		}
		return true;
	}
	bool DBinterface::give_penalty_byrfid(int rfid) {
		try {
			dbsys.add_penalty_byrfid(rfid);
		}
		catch (bool expn) {
			exception.scenario(expn);
			return false;
		}
		catch (signal errorcode) {
			exception.scenario((int)errorcode);
			return false;
		}
		return true;
	}
}
////  get함수 변환. bool 타입. 참조자로 해당데이터 넘겨주는식으로.
////  경고횟수 데이터 추가.