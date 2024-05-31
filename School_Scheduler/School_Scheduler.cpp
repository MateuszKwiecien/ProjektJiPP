#include "School_Scheduler.h"
#include "importFile.h"
#include "inputContainer.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog.h>
#include <QLabel>
#include <QListWidget>
#include <QPushButton.h>
#include <QGridLayout>
#include <QTableWidget>
#include <QComboBox>
#include <iostream>

using namespace std;

InputContainer inputContainer;

School_Scheduler::School_Scheduler(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
}

School_Scheduler::~School_Scheduler() {
    
}


// Get the needed data to import user data from file.
void School_Scheduler::import_data() {
    // Clean the saved data
    inputContainer.clean_container();

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
    lookAtDataDialog->setFixedHeight(400);
    lookAtDataDialog->setFixedWidth(500);

    // Create a new QLabel instance for the title.
    QLabel* titleLabel = new QLabel();


    titleLabel->setText("This is the data You imported.");
    // 50px from the left (with all these parameters 50px will be from the left and right).
    // 20px from the top
    // 400px width
    // 20px height
    titleLabel->setGeometry(50, 25, 400, 20);              
    titleLabel->setStyleSheet("QLabel { font-size : 16px; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setParent(lookAtDataDialog);
    titleLabel->show();                         

    // Create a new QListWidget instance for displaying the data.
    QListWidget* dataListWidget = new QListWidget();

    dataListWidget->setGeometry(50, 70, 400, 300);
    dataListWidget->setParent(lookAtDataDialog);

    inputContainer.update();
    for (int i = 0; i < inputContainer.get_size(); i++) {
        qDebug() << inputContainer.get_at_index(i);
        dataListWidget->addItem(inputContainer.get_at_index(i));
    }

    dataListWidget->show();

    lookAtDataDialog->show();

}

void School_Scheduler::make_schedule() {
    // Create a new QDialog for the scheduling interface.
    QDialog* scheduleDialog = new QDialog();

    scheduleDialog->setMinimumWidth(640);
    scheduleDialog->setMinimumHeight(480);

    // Create a QGridLayout to manage the layout of widgets within the dialog.
    QGridLayout* layout = new QGridLayout(scheduleDialog);

    // Create and configure a QLabel for the title of the dialog.
    QLabel* titleLabel = new QLabel("This is the school scheduler.", scheduleDialog);
    titleLabel->setStyleSheet("QLabel { font-size : 16px; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->show();
    
    // Create and configure a QPushButton to add elements to the schedule.
    QPushButton* addElementButton = new QPushButton("Add Element.", scheduleDialog);
    connect(addElementButton, SIGNAL(clicked()), this, SLOT(add_element()));
    addElementButton->show();
    
    // Create and configure a QPushButton to save the schedule to a file.
    QPushButton* saveButton = new QPushButton("Save to file.", scheduleDialog);
    saveButton->show();
    
    QStringList horizontalHeaderLabels;
    horizontalHeaderLabels << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
    
    QStringList verticalHeaderLabels;
    verticalHeaderLabels << "07 : 30" << "07 : 45" << "08 : 00" << "08 : 15" << "08 : 30" << "08 : 45" << "09 : 00" << "09 : 15" << "09 : 30" << "09 : 45" << "10 : 00" << "10 : 15" << "10 : 30";



    // Create a QTableWidget to display the schedule. It has 12 rows and 5 columns.
    QTableWidget* scheduleTable = new QTableWidget(12, 5, scheduleDialog);
    scheduleTable->setHorizontalHeaderLabels(horizontalHeaderLabels);
    scheduleTable->setVerticalHeaderLabels(verticalHeaderLabels);
    
    scheduleTable->show();

    // Add widgets to the layout at the specified positions.
    layout->addWidget(addElementButton, 0, 0);
    layout->addWidget(titleLabel, 0, 1);
    layout->addWidget(saveButton, 0, 2);
    layout->addWidget(scheduleTable, 1, 0, 1, 3);

    // Set spacing between the widgets in the layout.
    layout->setHorizontalSpacing(12);
    layout->setVerticalSpacing(8);

    // Display the dialog.
    scheduleDialog->show();
}

void School_Scheduler::add_element() {

    // Create a new QDialog for adding an element.
    QDialog* addElementDialog = new QDialog();

    // Set fixed dimensions for the dialog window.
    addElementDialog->setFixedWidth(200);
    addElementDialog->setMinimumHeight(150);

    // Create a QGridLayout to manage the layout of widgets within the dialog.
    QGridLayout* layout = new QGridLayout(addElementDialog);

    // Create a QComboBox to present the days of the week. 
    QComboBox* dayComboBox = new QComboBox(addElementDialog);
    dayComboBox->addItem("Monday");
    dayComboBox->addItem("Tuesday");
    dayComboBox->addItem("Wednesday");
    dayComboBox->addItem("Thursday");
    dayComboBox->addItem("Friday");

    // Create a QComboBox to present the from hours.
    QComboBox* fromComboBox = new QComboBox(addElementDialog);
    fromComboBox->addItem("07 : 30");
    fromComboBox->addItem("07 : 45");
    fromComboBox->addItem("08 : 00");
    fromComboBox->addItem("08 : 15");
    fromComboBox->addItem("08 : 30");
    fromComboBox->addItem("08 : 45");
    fromComboBox->addItem("09 : 00");
    fromComboBox->addItem("09 : 15");
    fromComboBox->addItem("09 : 30");
    fromComboBox->addItem("09 : 45");
    fromComboBox->addItem("10 : 00");

    // Create a QComboBox to present the to hours.
    QComboBox* toComboBox = new QComboBox(addElementDialog);
    toComboBox->addItem("08 : 00");
    toComboBox->addItem("08 : 15");
    toComboBox->addItem("08 : 30");
    toComboBox->addItem("08 : 45");
    toComboBox->addItem("09 : 00");
    toComboBox->addItem("09 : 15");
    toComboBox->addItem("09 : 30");
    toComboBox->addItem("09 : 45");
    toComboBox->addItem("10 : 00");
    toComboBox->addItem("10 : 15");
    toComboBox->addItem("10 : 30");

    // Create a QLineEdit to get the title. 
    QLineEdit* elementLineEdit = new QLineEdit(addElementDialog);
    elementLineEdit->setToolTip("What is the class about?");

    // Create a QComboBox to present the imported teachers.
    QComboBox* teacherComboBox = new QComboBox(addElementDialog);
    inputContainer.update();
    for (int i = 0; i < inputContainer.get_size(); i++) {
        qDebug() << inputContainer.get_at_index(i);
        teacherComboBox->addItem(inputContainer.get_at_index(i));
    }

    // Create a QPushButton so that the user can submit the selected data.
    QPushButton* submitButton = new QPushButton(addElementDialog);
    submitButton->setText("Submit");

    // Add widgets to the layout at the specified positions.
    layout->addWidget(dayComboBox, 0, 0, 1, 2);
    layout->addWidget(fromComboBox, 1, 0, 1, 1);
    layout->addWidget(toComboBox, 1, 1, 1, 1);
    layout->addWidget(elementLineEdit, 2, 0, 1, 2);
    layout->addWidget(teacherComboBox, 3, 0, 1, 2);
    layout->addWidget(submitButton, 4, 0, 1, 2);

    // Set spacing between the widgets in the layout.
    layout->setHorizontalSpacing(12);
    layout->setVerticalSpacing(8);

    
    // Display new element window
    addElementDialog->show();
}