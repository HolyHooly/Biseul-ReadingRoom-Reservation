#ifndef SEATINFO_H
#define SEATINFO_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <Qt>
#include <QGridLayout>
#include <QPushButton>

#include <ctime>

namespace Ui {
class SeatInfoPanel;
}

class SeatInfoPanel : public QDialog
{
    Q_OBJECT

public:
    explicit SeatInfoPanel(QWidget *parent, const int, const std::string, const tm*, const tm*, const int);
    ~SeatInfoPanel();

    void init_n(int numm);

private slots:
    void cancel();

private:
    Ui::SeatInfoPanel *ui;

    QLabel *position_label;
    QLabel *name_label;
    QLabel *time_label;
    QLabel* time_end_label;
    QLabel *pause_label;

    QPushButton *n_button;
};

#endif // SEATINFO_H
