#include "smalltests.h"

#include <QVector>
#include <QColorDialog>
#include <QPrinterInfo>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPainter>
#include <QPixmap>
#include <QUrl>
#include <QFileInfo>
#include <QHash>
#include <QString>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QRegExp>

#include <iostream>
#include <iterator>
#include <vector>
#include <cctype>

void test_iterator()
{
    std::cout<<"++++++++++++++ test_iterator ++++++++++++++"<<std::endl;

    std::vector<int> v = {10,23,5,31,7,13,21,65};

    for (unsigned int k=0;k<v.size();k=k+2)
    {
        std::cout<<" ** "<< v.at(k);
    }

    std::cout<<std::endl;

    std::cout<<"++++++++++++++ iterate QHash ++++++++++++++"<<std::endl;
    QHash<QString,int> hash;
    hash["one"] = 10;
    hash["two"] = 20;
    hash["three"] = 30;

    std::cout<<"++++++++++++++ iterate values ++++++++++++++"<<std::endl;
    for (int a : hash)
    {
        std::cout<<a<<std::endl;
    }
    std::cout<<"++++++++++++++ iterate keys ++++++++++++++"<<std::endl;
    for (QString sa : hash.keys())
    {
        std::cout<<sa.toStdString()<<std::endl;
    }
}

void test_pointer()
// Ref: https://www.tutorialspoint.com/cplusplus/cpp_pointers.htm
{
    std::cout<<std::endl<<"++++++++++++++ test_pointer ++++++++++++++"<<std::endl;

    // Every variable is written in a memory location:
    int a = 5;
    // This memory location has an address, which can be accessed by (&):
    std::cout<<"Value of a: "<< a <<std::endl;
    std::cout<<"Address of a in memory (&a): "<< &a <<std::endl;

    // Now imagine you want to save this address and use it somewhere else. To define a pointer, you need to know the type of variable in the address. Then:
    // variableType *pointerName = &variableName;

    // Three operations that we do with the pointers frequently:

    //##################
    // 1. Define pointer variable
    //##################
    // Here the variable "a" is of type "int". So:
    int *aPtr;

    //##################
    // 2. Access the address of the variable to the pointer
    //##################
    aPtr = &a;
    std::cout<<"Address of a in memory using pointer (aPtr): "<< aPtr <<std::endl;

    //##################
    // 3. Access the value in the address
    //##################
    int b = *aPtr;
    std::cout<<"The value of the variable using its pointer (b = *aPtr): "<< b <<std::endl;

    //##################
    // Null pointer
    //##################
    int *bPtr = &a;
    std::cout<<"bPtr points to the address of a in memory: "<< bPtr <<std::endl;

    // How can we make the pointer to point to address 0 in memory?
    bPtr = nullptr;
    std::cout<<" Pointer points to address zero: "<< bPtr <<std::endl;


}

void test_strings()
{
    std::cout<<"++++++++++++++ test_strings ++++++++++++++"<<std::endl;

    QString str1 = "Meter";
    QString str2 = "Foot";
    std::cout<<"str1: "<<str1.toStdString()<<", str2: "<<str2.toStdString()<<std::endl;
    if (str1==str2)
    {
        std::cout<<str1.toStdString()<<" and "<<str2.toStdString()<<" are equal!"<<std::endl;
    }
    else
    {
        std::cout<<str1.toStdString()<<" and "<<str2.toStdString()<<" are not equal!"<<std::endl;
    }

    if ("Foot"==str2)
    {
        std::cout<<"Foot and "<<str2.toStdString()<<" are equal!"<<std::endl;
    }
    else
    {
        std::cout<<"Foot and "<<str2.toStdString()<<" are not equal!"<<std::endl;
    }

    //QString hala = tr("are");    
}

void test_color_dialog()
{
    std::cout<<"++++++++++++++ test_color_dialog ++++++++++++++"<<std::endl;

    QColor color = QColorDialog::getColor(Qt::yellow );
    std::cout<<"Chosen color: "<<color.name().toStdString();
    std::cout<<", (R,G,B): ("<<color.red()<<","<<color.green()<<","<<color.blue()<<")"<<std::endl;

    QList<QString> colors = {"#mm8833","mm8833","#mm8833g","fdssdsf","#fdaadb","458435","#326421", "#aa54c1"};
    for (int k=0;k<colors.size();k++)
    {
        QString colorName = colors.at(k);
        QColor color1(colorName);

        if (color1.isValid() == true)
        {
            std::cout<<"Color: "<<colorName.toStdString()<<" is valid! ";
        }
        else
        {
            std::cout<<"Color: "<<colorName.toStdString()<<" is invalid! ";
        }
        std::cout<<", (R,G,B): ("<<color1.red()<<","<<color1.green()<<","<<color1.blue()<<")"<<std::endl;

    }

    std::cout<<"Testing the strings without Qt..."<<std::endl;
    // Test the strings without Qt:
    for (int k=0;k<colors.size();k++)
    {
        std::string colorHexaDecimal = colors.at(k).toStdString();

        std::cout<<"Color: "<<colorHexaDecimal<<";";

        if (colorHexaDecimal.compare(0,1,"#") != 0)
        {
            std::cout<<" Invalid! "<<std::endl;
            continue;
        }
        if (colorHexaDecimal.length() != 7)
        {
            std::cout<<" Invalid! "<<std::endl;
            continue;
        }
        if (colorHexaDecimal.find_first_not_of("0123456789abcdefABCDEF", 1) != std::string::npos)
          // If except the first character, there is any character not existing in the given set of characters,...
        {
            std::cout<<" Invalid! "<<std::endl;
            continue;
        }

        // If we are here, the hexa decimal name is valid!
        std::string redString = colorHexaDecimal.substr(1, 2);
        int red = static_cast<int>(std::stoul(redString, nullptr, 16));

        std::string greenString = colorHexaDecimal.substr(3, 2);
        int green = static_cast<int>(std::stoul(greenString, nullptr, 16));

        std::string blueString = colorHexaDecimal.substr(5, 2);
        int blue = static_cast<int>(std::stoul(blueString, nullptr, 16));

        std::cout<<", (R,G,B): ("<<red<<","<<green<<","<<blue<<")"<<std::endl;
    }
}

void test_printer()
{
    // Ref:
    // https://stackoverflow.com/questions/8310681/how-to-print-image-file-from-a-printer-using-qt

    std::cout<<"++++++++++++++ test_printer ++++++++++++++"<<std::endl;
    QList<QPrinterInfo> printerInfos = QPrinterInfo::availablePrinters();
    for (int k=0 ; k<printerInfos.size() ; k++)
        // As many as the number of detected printers,...
    {
        std::cout<<"Printer "<<k+1<<": "<<printerInfos.at(k).printerName().toStdString()<<std::endl;
    }

    QString fileName = QFileDialog::getOpenFileName(nullptr,"Open File",QString(),"PNG File(*.png)");

    QPrinter printer;
    QPrintDialog *printDialog = new QPrintDialog(&printer);
    if (printDialog->exec() == QDialog::Accepted)
        // If the print job is accepted,...
    {
        std::cout<<"Selected printer: "<<printer.printerName().toStdString()<<std::endl;
        QPixmap image(fileName);
        QPainter painter(&printer);
        painter.drawPixmap(QPoint(10,10),image);
        painter.end();
    }
}

void test_file_dialog()
{
    std::cout<<"++++++++++++++ test_file_dialog ++++++++++++++"<<std::endl;
    QString fileName = QFileDialog::getOpenFileName();
    std::cout<<"fileName: "<<fileName.toStdString()<<std::endl;
    QUrl fileUrl = QFileDialog::getOpenFileUrl();
    std::cout<<"fileUrl: "<<fileUrl.toString().toStdString()<<std::endl;
    std::cout<<"fileUrl scheme: "<<fileUrl.scheme().toStdString()<<std::endl;
    std::cout<<"fileUrl scheme removed: "<<fileUrl.adjusted(QUrl::RemoveScheme).toString().toStdString()<<std::endl;
    std::cout<<"fileUrl fileName: "<<fileUrl.fileName().toStdString()<<std::endl;
    std::cout<<"fileUrl path: "<<fileUrl.path().toStdString()<<std::endl;
    fileUrl.setScheme(QString());

    QFileInfo fileInfo(fileUrl.toString());
    std::cout<<"fileInfo absolute path: "<<fileInfo.filePath().toStdString()<<std::endl;


}

void test_file_dialog_two()
{
    std::cout<<"++++++++++++++ test_file_dialog 2 ++++++++++++++"<<std::endl;
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::FileMode::AnyFile);
    fileDialog.setOptions(QFileDialog::DontUseNativeDialog);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);

    // Set validator:
    auto children = fileDialog.findChildren<QLineEdit*>();
    if (children.size() == 1)
    {
      // Force the user to start the string with lowercase "a"
      QRegExpValidator validator(QRegExp("^a"));
      children.front()->setValidator(&validator);
    }
    fileDialog.exec();

    /*
    if (fileDialog.exec() && fileDialog.selectedFiles().empty() != true)
    {
        QString fileName = fileDialog.selectedFiles().last();
        std::cout<<"File name: "<<fileName.toStdString()<<std::endl;
    }
    */
}


class ToTestStaticMember
// Ref: https://www.learncpp.com/cpp-tutorial/811-static-member-variables/
{
public:
    ToTestStaticMember()
    {
        m_id = ++s_id;
    }

    static int s_value; // Declares static member variable.
    // Static members exist even if no object of the class has been initiated. They are created when the program starts!
    // One may assume static member belongs to the class, not to the object.
    // To set a value to an static member, you don't need any object of the class. You can access static member using :: (scope resolution operator).
    // Where to "define" the static member? Outside the class, in global scope.

    int getId()
    {
        return m_id;
    }

private:
    int m_id;
    static int s_id;
};

int ToTestStaticMember::s_id = 0; // We "initiate" and "initialize" [with zero] the static member.
// If we don't initialize the static member, C++ initializes it with zero.
// Notice that we initiated and initialized a static member which was under "private" identifier.

void test_static_class_member()
{
    std::cout<<"++++++++++++++ test_static_class_member ++++++++++++++"<<std::endl;
    ToTestStaticMember testOne;
    ToTestStaticMember testTwo;

    std::cout<<"Id of 1st instance of class ToTestStaticMember: "<<testOne.getId()<<std::endl;
    std::cout<<"Id of 2nd instance of class ToTestStaticMember: "<<testTwo.getId()<<std::endl;
}
