#include "School_Scheduler.h"
#include "importFile.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog.h>
#include <QLabel>
#include <QListWidget>
#include <iostream>

using namespace std;

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