#include "importFile.h"
#include "School_Scheduler.h"
#include "inputContainer.h"
#include <QInputDialog>
#include <QFileDialog.h>
#include <iostream>

InputContainer inputContainerFile;

QString get_open_file_name(QWidget* parent, const char* title, const char* format) {
    return QFileDialog::getOpenFileName(parent,                                                 // Parent.
        School_Scheduler::tr(title),                                                            // Title of the dialog.
        QDir::currentPath(),                                                                    // Where to open the dialog.
        School_Scheduler::tr(format));                                                          // What files will be taken as input.
}


int get_number_of_rows_to_import(QWidget* parent, int currentVal, int minVal, int maxVal, const char* text, const char* title) {
    return QInputDialog::getInt(parent,                                                         // Parent.
        School_Scheduler::tr(title),                                                            // Title of the dialog.
        School_Scheduler::tr(text),                                                             // Text in the input dialog.
        currentVal,                                                                             // Current value.
        minVal,                                                                                 // Minimum value.
        maxVal);                                                                                // Maximum value.
}


void processFile(const QString& fileName, int numberOfItems) {
    QFile file(fileName);                                                                       // Open files.

    if (!file.open(QIODevice::ReadOnly))                                                        // Check if open is succesful
        return;                                                                                 // or user selected a file.


    // Read the lines.
    QTextStream input(&file);
    for (int i = 0; i < numberOfItems && !input.atEnd(); i++) {
        QString line = input.readLine();
        inputContainerFile.push(line);
        qDebug() << i << " " << line;
    }
    file.close();
}
