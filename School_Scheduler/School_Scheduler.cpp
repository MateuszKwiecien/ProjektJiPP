#include "School_Scheduler.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog.h>
#include <QLabel>
#include <QListWidget>
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

// Show the imported data by the user.
void School_Scheduler::show_import() {
    // Create a new QDialog instance for displaying the imported data.
    QDialog* lookAtDataDialog = new QDialog();
    
    // Set the dialog to be application modal, so it blocks input to other windows in the application.
    lookAtDataDialog->setWindowModality(Qt::WindowModality::ApplicationModal);

    // Set fixed dimensions for the dialog.
    lookAtDataDialog->setMinimumHeight(400);
    lookAtDataDialog->setMinimumWidth(500);
    lookAtDataDialog->setMaximumHeight(400);
    lookAtDataDialog->setMaximumWidth(500);

    // Create a new QLabel instance for the title.
    QLabel* titleLabel = new QLabel();


    titleLabel->setText("This is the data You imported.");
    // 50px from the left (with all these parameters 50px will be from the left and right).
    // 20px from the top
    // 400px width
    // 20px height
    titleLabel->setGeometry(50, 25, 400, 20);              
    titleLabel->setStyleSheet("QLabel { background-color : red; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setParent(lookAtDataDialog);
    titleLabel->show();                         

    // Create a new QListWidget instance for displaying the data.
    QListWidget* dataListWidget = new QListWidget();

    dataListWidget->setGeometry(50, 70, 400, 300);
    dataListWidget->setParent(lookAtDataDialog);

    // Dummy data.
    for (int i = 0; i < 100; i++) {
        dataListWidget->addItem(QString::number(i));
    }

    dataListWidget->show();

    lookAtDataDialog->show();

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
