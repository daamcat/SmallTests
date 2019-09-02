#include <QCoreApplication>
#include <QApplication>

#include <iostream>

#include "smalltests.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //test_iterator();
    //test_pointer();
    //test_strings();
    //test_color_dialog();
    //test_printer();
    //test_file_dialog();
    //test_file_dialog_two();
    test_static_class_member();


    return a.exec();
}
