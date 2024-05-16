#ifndef __INPUTDIALOG_H__
#define __INPUTDIALOG_H__

#include <QDialog>

// This class allows a custom input dialog with multiple text input fields.

// Forward declaration of classes to avoid including their headers.
class QLineEdit;
class QLabel;

// Definition of the InputDialog class, which inherits from QDialog.
class InputDialog : public QDialog
{
    Q_OBJECT // Macro required for Qt's meta-object system to handle signals and slots.
public:

    // Constructor for the InputDialog class. (Constructor cannot be used for implicit conversions).
    // Parameters:
    //   titles: Array of titles for each input field.
    //   size: Number of input fields.
    //   parent: Pointer to the parent widget (optional). Defaults to nullptr.
    explicit InputDialog(const char** titles, int size, QWidget* parent = nullptr);

    // Static function to display the input dialog and retrieve the entered strings.
    // Parameters:
    //   titles: Array of titles for each input field.
    //   size: Number of input fields.
    //   parent: Pointer to the parent widget (optional). Defaults to nullptr.
    //   ok: Pointer to a boolean flag indicating if the dialog was accepted (optional). Defaults to nullptr.
    // Returns:
    //   QStringList containing the entered strings.
    static QStringList getStrings(const char** titles, int size, QWidget* parent, bool* ok = nullptr);

private:
    QList<QLineEdit*> fields;   // List to hold pointers to QLineEdit objects representing input fields.
};

#endif // __INPUTDIALOG_H__
