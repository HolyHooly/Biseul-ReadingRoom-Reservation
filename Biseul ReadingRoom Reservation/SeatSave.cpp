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


            seats << seat_no << "," << name << "," << student_id << "," << rfid_id << "," << status << "," << pause_time << "\n";
        }
        
        std::string seats_status = seats.str().erase((seats.str().length()-1),1);

        return seats_status;
    }

    void save_seats(std::string seat_info) {
        std::ofstream myfile;
        myfile.open("./log/seat_status.csv");
        myfile << "Seat #, User Name, Student ID, Rfid ID, Seat Status, Pause Time" << "\n";
        myfile << seat_info;
    }


    void save_status(std::vector<std::pair<int, Seat*>> seat_info)
    {
        std::string info_string = status_to_string(seat_info);
        save_seats(info_string);
    }
}