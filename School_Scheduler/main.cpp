#include "School_Scheduler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    School_Scheduler w;
    w.show();
    return a.exec();
}
