#ifndef __import_File_h__
#define __import_File_h__

#include "School_Scheduler.h"

// Function to open a file dialog and return the selected file's name.
// Parameters:
//   parent: The parent widget for the file dialog.
//   title: The title of the file dialog (optional). Defaults to "Open file".
//   format: The file format filter (optional). Defaults to "text files (*.txt)".
QString get_open_file_name(QWidget* parent, const char* title = "Open file", const char* format = "text files (*.txt)");


// Function to get the number of rows to import via a dialog.
// Parameters:
//   parent: The parent widget for the dialog.
//   currentVal: The initial value to be displayed in the dialog (optional). Defaults to 0.
//   minVal: The minimum value that can be entered (optional). Defaults to -100.
//   maxVal: The maximum value that can be entered (optional). Defaults to 100).
//   text: The message to be displayed in the dialog (optional). Defaults to "How many row do you want to import?".
//   title: The title of the dialog (optional). Defaults to "Import Data.".
int get_number_of_rows_to_import(QWidget* parent, int currentVal = 0, int minVal = -100, int maxVal = 100, const char* text = "How many row do you want to import?", const char* title = "Import Data.");

// Function to process the file with the specified number of items.
// Parameters:
//   fileName: The name of the file to be processed.
//   numberOfItems: The number of items (rows) to import from the file.
void processFile(const QString& fileName, int numberOfItems);

#endif // !__import_File_h__
