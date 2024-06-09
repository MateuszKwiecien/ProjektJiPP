#include "School_Scheduler.h"
#include "importFile.h"
#include "inputContainer.h"
#include "classElementContainer.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog.h>
#include <QLabel>
#include <QListWidget>
#include <QPushButton.h>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QTableWidget>
#include <QComboBox>
#include <iostream>

using namespace std;

InputContainer inputContainer;
ClassElementContainer classContainer;

School_Scheduler::School_Scheduler(QWidget* parent) : QMainWindow(parent) {
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

    // Set the dialog to be application modal, so it blocks input to other windows in the application.
    scheduleDialog->setWindowModality(Qt::WindowModality::ApplicationModal);

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
    layout->addWidget(addElementButton);
    addElementButton->show();

    // Create and configure a QPushButton to save the schedule to a file.
    QPushButton* saveButton = new QPushButton("Save to file.", scheduleDialog);
    layout->addWidget(saveButton);
    saveButton->show();

    QStringList horizontalHeaderLabels;
    horizontalHeaderLabels << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";

    QStringList verticalHeaderLabels;
    // Adjusted vertical labels from 7:00 to 19:00 with 15-minute increments.
    for (int hour = 7; hour <= 19; ++hour) {
        for (int minute = 0; minute < 60; minute += 15) {
            QString timeLabel = QString("%1 : %2").arg(hour, 2, 10, QChar('0')).arg(minute, 2, 10, QChar('0'));
            verticalHeaderLabels << timeLabel;
        }
    }

    // Create a QTableWidget to display the schedule. It's size is verticalHeaderLabels x horizontalHeaderLabels
    QTableWidget* scheduleTable = new QTableWidget(verticalHeaderLabels.size(), horizontalHeaderLabels.size(), scheduleDialog);
    scheduleTable->setHorizontalHeaderLabels(horizontalHeaderLabels);
    scheduleTable->setVerticalHeaderLabels(verticalHeaderLabels);

    scheduleTable->show();

    QPushButton* refreshButton = new QPushButton("Refresh", scheduleDialog);
    connect(refreshButton, &QPushButton::clicked, [scheduleTable]() {
        scheduleTable->clearContents();
        classContainer.refreshTable(scheduleTable);
        });
    layout->addWidget(refreshButton);

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
    // Create a new QDialog for adding an element
    QDialog* addElementDialog = new QDialog();

    // Set fixed dimensions for the dialog window
    addElementDialog->setFixedHeight(400);
    addElementDialog->setFixedWidth(500);

    // Create a QVBoxLayout to manage the overall layout of the dialog
    QVBoxLayout* mainLayout = new QVBoxLayout(addElementDialog);

    // Create and configure a QLabel for the title of the dialog.
    QLabel* addElementLabel = new QLabel("Enter the data of a new class element:", addElementDialog);
    addElementLabel->setStyleSheet("QLabel { font-size : 16px; }");
    addElementLabel->setAlignment(Qt::AlignCenter);

    // Add the QLabel to the main layout
    mainLayout->addWidget(addElementLabel);

    // Create a QFormLayout to manage the form fields
    QFormLayout* formLayout = new QFormLayout();

    // Create and configure QLineEdit and QComboBox widgets for inputting various data
    QLineEdit* classNameInput = new QLineEdit(addElementDialog);
    classNameInput->setPlaceholderText("Enter class name");

    QComboBox* classTimeInput = new QComboBox(addElementDialog);
    classTimeInput->setPlaceholderText("Enter class start time");

    // Populate the classTimeInput ComboBox with time values from 7:30 to 19:00 at 15-minute intervals
    for (int hour = 7; hour <= 19; ++hour) {
        for (int minute = 0; minute < 60; minute += 15) {
            if (!(hour == 19 && minute > 0)) {
                QString timeLabel = QString("%1:%2").arg(hour, 2, 10, QChar('0')).arg(minute, 2, 10, QChar('0'));
                classTimeInput->addItem(timeLabel);
            }
        }
    }

    QComboBox* classDuration = new QComboBox(addElementDialog);
    classDuration->setPlaceholderText("Enter class duration (in school hours)");

    QStringList classDurationItems;
    classDurationItems << "1" << "2" << "3" << "4";
    classDuration->addItems(classDurationItems);

    QLineEdit* classRoomInput = new QLineEdit(addElementDialog);
    classRoomInput->setPlaceholderText("Enter class room");

    QComboBox* instructorNameCombo = new QComboBox(addElementDialog);
    inputContainer.update();
    for (int i = 0; i < inputContainer.get_size(); i++) {
        instructorNameCombo->addItem(inputContainer.get_at_index(i));
    }
    
    QComboBox* classTypeCombo = new QComboBox(addElementDialog);
    classTypeCombo->setPlaceholderText("Class Type");
    classTypeCombo->addItems({ "LECTURE", "LABORATORY", "CLASSICAL" });

    QComboBox* dayOfWeekComboBox = new QComboBox(addElementDialog);
    dayOfWeekComboBox->setPlaceholderText("Day of the week");
    dayOfWeekComboBox->addItems({ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" });

    // Add the QLineEdit widgets and QComboBox to the form layout with corresponding labels
    formLayout->addRow("Class Name:", classNameInput);
    formLayout->addRow("Class Start Time:", classTimeInput);
    formLayout->addRow("Class Time Duration:", classDuration);
    formLayout->addRow("Class Room:", classRoomInput);
    formLayout->addRow("Instructor Name:", instructorNameCombo);
    formLayout->addRow("Day of the Week:", dayOfWeekComboBox);
    formLayout->addRow("Class Type:", classTypeCombo);

    // Add the form layout to the main layout
    mainLayout->addLayout(formLayout);

    // Create and configure a QPushButton to submit the input data.
    QPushButton* submitButton = new QPushButton("Submit", addElementDialog);

    // Add the QPushButton to the main layout
    mainLayout->addWidget(submitButton);

    // Connect the submit button's clicked signal to a slot that will handle the input data
    connect(submitButton, &QPushButton::clicked, [addElementDialog, classNameInput, classTimeInput, classDuration, classRoomInput, instructorNameCombo, dayOfWeekComboBox, classTypeCombo, this]() {
        QString className = classNameInput->text();
        QString classTime = classTimeInput->currentText();
        QString classDurationText = classDuration->currentText();
        QString classRoom = classRoomInput->text();
        QString instructorName = instructorNameCombo->currentText();
        QString dayOfWeek = dayOfWeekComboBox->currentText();
        QString classType = classTypeCombo->currentText();

        // Process the data, add data to a classElement* vector
        ClassElement* newClass = new ClassElement(className, classTime, classDurationText, classRoom, instructorName, dayOfWeek, classType);
        classContainer.addElement(newClass);

        // Close the dialog after processing the input
        addElementDialog->accept();
        });

    // Set the main layout for the dialog
    addElementDialog->setLayout(mainLayout);

    // Display the new element window
    addElementDialog->exec();  // Use exec() to make the dialog modal
}