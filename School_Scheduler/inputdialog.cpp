#include "inputdialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

// Constructor for InputDialog class
InputDialog::InputDialog(const char** titles, int size, QWidget* parent) : QDialog(parent) {

    QFormLayout* lytMain = new QFormLayout(this); // Create a form layout for the dialog


    for (int i = 0; i < size; ++i)
    {
        QLabel* tLabel = new QLabel(QString(titles[i]), this);  // Create a label with the title
        QLineEdit* tLine = new QLineEdit(this);                 // Create a corresponding line edit field
        lytMain->addRow(tLabel, tLine);                         // Add label and line edit to the form layout

        fields << tLine;                                        // Add the line edit field 
                                                                // to the QList for later retrieval
    }

    // Create a QDialogButtonBox containing Ok and Cancel buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox
    (QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    lytMain->addWidget(buttonBox);                              // Add the button box to the form layout

    // Connect signals from the button box to slots of the InputDialog
    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::accept);
    Q_ASSERT(conn);                                             // Ensure the connection is successful

    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &InputDialog::reject);
    Q_ASSERT(conn);                                             // Ensure the connection is successful

    setLayout(lytMain);                                         // Set the form layout as the layout 
                                                                // for the dialog
}

// Function to create an InputDialog instance and retrieve input strings
QStringList InputDialog::getStrings(const char** titles, int size, QWidget* parent, bool* ok) {
    // Create a new InputDialog instance
    InputDialog* dialog = new InputDialog(titles, size, parent);

    QStringList list;                                           // Create a QStringList to store input strings

    const int ret = dialog->exec();                             // Execute the dialog and wait for user input
    if (ok)
        *ok = !!ret;                                            // If the 'ok' pointer is provided, update its
    // If the user clicked Ok                                   // value based on the return value of exec()
    if (ret) {
        // Iterate through each QLineEdit field in the dialog and retrieve text
        foreach(auto field, dialog->fields) {
            list << field->text();                              // Add the text to the QStringList
        }
    }

    dialog->deleteLater();                                      // Delete the dialog after retrieving the 
                                                                // necessary information

    return list;                                                // Return the list of input strings
}