#include "SeatSave.h"

namespace biseul_rroom {
    std::string status_to_string(std::vector<std::pair<int, Seat*>> seat_info)
    {
        std::string status;
        std::stringstream seats;
        for (int i = 0; i < seat_info.size(); i++) {
            if (seat_info[i].second->get_status() == SeatStatus::Occupied) {
                status = "Occupied";
            }
            else if (seat_info[i].second->get_status() == SeatStatus::Paused) {
                status = "Paused";
            }
            UserManger* manager = nullptr;

            int seat_no = seat_info[i].first;
            std::string name = seat_info[i].second->get_reserver()->get_name();
            int student_id = seat_info[i].second->get_reserver()->get_stud_id();
            __int64 rfid_id = seat_info[i].second->get_reserver()->get_rfid_id();
            SeatStatus seat_status = seat_info[i].second->get_status();
            int pause_time = seat_info[i].second->get_pause_time();
            //빌린 시간이랑 빌리는 거 끝나는 시간
            tm* reserved = seat_info[i].second->get_reserved_time();
            tm* reserve_end = seat_info[i].second->get_reserve_end_time();

            seats << seat_no << "," << name << "," << student_id << "," << rfid_id << "," << status << "," << pause_time 
                << reserved->tm_hour << "-" << reserved->tm_min << "-" << reserved->tm_sec << "-" 
                << reserved->tm_mday << "-" << reserved->tm_mon << "-" << reserved->tm_year << "-" << reserved->tm_wday << "-" << reserved->tm_yday << "-" << reserved->tm_isdst << ","
                << reserve_end->tm_hour << "-" << reserve_end->tm_min << "-" << reserve_end->tm_sec << "-"
                << reserve_end->tm_mday << "-" << reserve_end->tm_mon << "-" << reserve_end->tm_year << "-" << reserve_end->tm_wday << "-" << reserve_end->tm_yday << "-" << reserve_end->tm_isdst << "\n";
        }
        
        std::string seats_status = seats.str().erase((seats.str().length()-1),1);

        return seats_status;
    }

    void save_seats(std::string seat_info) {
        std::ofstream myfile;
        myfile.open("./log/seat_status.csv");
        myfile << "Seat #, User Name, Student ID, Rfid ID, Seat Status, Pause Time, Reserved time, Reserve End Time" << "\n";
        myfile << seat_info;
    }


    void save_status(std::vector<std::pair<int, Seat*>> seat_info)
    {
        std::string info_string = status_to_string(seat_info);
        save_seats(info_string);
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Loading
    ///////////////////////////////////////////////////////////////////////////////////////////////

    void Loading::load_status()
    {
        std::fstream status_file;
        std::string member;

        Loading* seat = nullptr;

        status_file.open("log/seat_status.csv", std::ios::in);

        int seat_number_checker = 0;
        while (!status_file.eof()) {
            //csv 파일에서 한 줄씩 읽기
            getline(status_file, member, '\n');

            //string ,로 잘라주려고 std::string에서 char*[]으로 변환
            std::vector<char> str_char(member.begin(), member.end());
            str_char.push_back('\0');
            char* words = &str_char[0];

            // 한 줄을 {자리 번호},{이름},{학번},{rfid_id},{자리상태},{일시정시시간},{예약한 시간},{예약 끝 시간}으로 각각 나눠줌
            char* word[8] = { nullptr, }, * context;

            word[0] = strtok_s(words, ",", &context);
            for (int i = 1; i < 8; i++) {
                word[i] = strtok_s(NULL, ",", &context);
            }

            //예약한 시간, 예약 끝 시간 각각 tm에 넣어주기
            char* r_time[9] = { nullptr, }, * rcon;

            r_time[0] = strtok_s(word[6], "-", &rcon);
            for (int i = 1; i < 8; i++) {
                r_time[i] = strtok_s(NULL, "-", &rcon);
            }
            tm reserved = {0,};
            reserved.tm_hour = atoi(r_time[0]);
            reserved.tm_min = atoi(r_time[1]);
            reserved.tm_sec = atoi(r_time[2]);
            reserved.tm_mday = atoi(r_time[3]);
            reserved.tm_mon = atoi(r_time[4]);
            reserved.tm_year = atoi(r_time[5]);
            reserved.tm_wday = atoi(r_time[6]);
            reserved.tm_yday = atoi(r_time[7]);
            reserved.tm_isdst = atoi(r_time[8]);

            char* re_time[9] = { nullptr, }, * recon;

            re_time[0] = strtok_s(word[7], "-", &recon);
            for (int i = 1; i < 8; i++) {
                re_time[i] = strtok_s(NULL, "-", &recon);
            }
            tm reserve_end = { 0, };
            reserve_end.tm_hour = atoi(re_time[0]);
            reserve_end.tm_min = atoi(re_time[1]);
            reserve_end.tm_sec = atoi(re_time[2]);
            reserve_end.tm_mday = atoi(re_time[3]);
            reserve_end.tm_mon = atoi(re_time[4]);
            reserve_end.tm_year = atoi(re_time[5]);
            reserve_end.tm_wday = atoi(re_time[6]);
            reserve_end.tm_yday = atoi(re_time[7]);
            reserve_end.tm_isdst = atoi(re_time[8]);


            // seat number 유무 따라서 seat에 채워주기
            if (seat_number_checker != 0) {
                seat = new Loading;
                if (atoi(word[2]) != 0) {
                    seat->seat_no = atoi(word[0]);
                    seat->name = std::string(word[1]);
                    seat->student_id = atoi(word[2]);
                    seat->rfid_id = _atoi64(word[3]);
                    seat->seat_status = std::string(word[4]);
                    seat->pause_time = atoi(word[5]);
                    seat->reserved_time = reserved;
                    seat->reserve_end_time = reserve_end;
                }
                seats[atoi(word[0]) - 1] = seat;
            }
            ++seat_number_checker;
        }
    }
    bool Loading::get_seat(int seatno)
    {
        if (seats[seatno - 1] == nullptr) {
            return false;
        }
        return true;
    }

    SeatStatus Loading::seat_status_converter(int seatno)
    {
        if (seats[seatno - 1] == nullptr) {
            return SeatStatus::Vacant;
        }

        std::string status = seats[seatno - 1]->seat_status;
        if (status.compare("Occupied") == 0) {
            return SeatStatus::Occupied;
        }
        if (status.compare("Paused") == 0) {
            return SeatStatus::Paused;
        }
    }
}