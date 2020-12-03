#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QPushButton>

#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QTableView>
#include <QAbstractScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QSize>

namespace Ui {
    class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();

private:
    Ui::AdminPanel* ui;
    QPushButton* p_seat[125] = { nullptr };
};

#endif // ADMIN_H
