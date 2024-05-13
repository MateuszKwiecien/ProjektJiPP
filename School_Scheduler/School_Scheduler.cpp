#include "School_Scheduler.h"
#include <QMessageBox>
#include <QInputDialog>
#include <iostream>

using namespace std;

School_Scheduler::School_Scheduler(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
}

School_Scheduler::~School_Scheduler() {
    
}


// Get the needed data to import user data from file.
void School_Scheduler::import_data() {
    bool success;                                                                                      // success flag
    QString text = QInputDialog::getText(this,                                                         // parent
                                        "Import Data.",                                                // title
                                        "Please select the amount and the file you want to import.",   // text in the input dialog
                                        QLineEdit::Normal,                                             // text format in the input - user can see the text
                                        "inputfile.txt",                                               // default file name
                                        &success);                                                     // if user pressed 'OK' or 'Cancel'

    if (success && text.isEmpty())
        cout << "Empty text!" << endl;

}
