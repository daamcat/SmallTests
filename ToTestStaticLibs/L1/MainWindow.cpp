#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>

#include "Label.h"
#include "PushButton.h"

#include "dropbox/DropboxClient.h"
#include "dropbox/users/UsersRoutes.h"
#include "dropbox/endpoint/DropboxAppInfo.h"
#include "dropbox/endpoint/DropboxAuthInfo.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Label* label = new Label(this);
    PushButton* pushButton = new PushButton(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(pushButton);
    this->centralWidget()->setLayout(layout);


    dropboxQt::DropboxAuthInfo authInfo;

}

MainWindow::~MainWindow()
{
    delete ui;
}
