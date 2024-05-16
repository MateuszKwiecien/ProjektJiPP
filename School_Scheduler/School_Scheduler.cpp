#include "School_Scheduler.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog.h>
#include <iostream>

using namespace std;

QString get_open_file_name(QWidget* parent, const char* title = "Open file", const char* format = "text files (*.txt)");
int get_number_of_rows_to_import(QWidget* parent, int currentVal=0, int minVal=-100, int maxVal=100, const char* text = "How many row do you want to import?", const char* title = "Import Data.");
void processFile(const QString& fileName, int numberOfItems);

School_Scheduler::School_Scheduler(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
}

School_Scheduler::~School_Scheduler() {
    
}


// Get the needed data to import user data from file.
void School_Scheduler::import_data() {

    // Open File Dialog.
    QString fileName = get_open_file_name(this);

    // If file opened get the amount of rows.
    int numberOfItems = get_number_of_rows_to_import(this, 5, 0, 10);

    // Read and process the file.
    processFile(fileName, numberOfItems);
}


QString get_open_file_name(QWidget* parent, const char* title, const char* format) {
    return QFileDialog::getOpenFileName(parent,                                                 // Parent.
                                        School_Scheduler::tr(title),                            // Title of the dialog.
                                        QDir::currentPath(),                                    // Where to open the dialog.
                                        School_Scheduler::tr(format));                          // What files will be taken as input.
}


int get_number_of_rows_to_import(QWidget* parent, int currentVal, int minVal, int maxVal, const char* text, const char* title) {
    return QInputDialog::getInt(parent,                                                         // Parent.
                                School_Scheduler::tr(title),                                    // Title of the dialog.
                                School_Scheduler::tr(text),                                     // Text in the input dialog.
                                currentVal,                                                     // Current value.
                                minVal,                                                         // Minimum value.
                                maxVal);                                                        // Maximum value.
}


void processFile(const QString& fileName, int numberOfItems) {
    QFile file(fileName);                                                                       // Open files.

    if (!file.open(QIODevice::ReadOnly))                                                        // Check if open is succesful
        return;                                                                                 // or user selected a file.


    // Read the lines.
    QTextStream input(&file);
    for (int i = 0; i < numberOfItems && !input.atEnd(); i++) {
        QString line = input.readLine();
        qDebug() << i << " " << line;
    }
    file.close();
}
