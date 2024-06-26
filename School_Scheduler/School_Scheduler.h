#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_School_Scheduler.h"

class School_Scheduler : public QMainWindow
{
    Q_OBJECT

    public:
        School_Scheduler(QWidget *parent = nullptr);
        ~School_Scheduler();

    private:
        Ui::School_SchedulerClass ui;
        QDialog* dialog;

    private slots:
        void import_data();
        void show_import();
        void make_schedule();
        void add_element();
        void delete_item();
};
