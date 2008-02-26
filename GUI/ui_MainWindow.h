/********************************************************************************
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: Tue 26. Feb 16:14:02 2008
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDial>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QAction *m_pActionExit;
    QWidget *m_pCentralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *m_pCamera1Label;
    QLabel *m_pCamera2Label;
    QLabel *m_pCamera3Label;
    QLabel *m_pMainCameraLabel;
    QHBoxLayout *hboxLayout1;
    QGroupBox *m_pDetailsGroupBox;
    QWidget *verticalLayout;
    QVBoxLayout *vboxLayout2;
    QGroupBox *m_pDescriptionGroupBox;
    QVBoxLayout *vboxLayout3;
    QLabel *m_pDescriptionLabel;
    QPushButton *m_pExecuteButton;
    QLabel *m_pCommandLabel;
    QStackedWidget *m_pArgumentsStackedWidget;
    QWidget *m_pAnglePage;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout2;
    QLabel *m_pAngleLabel;
    QSpinBox *m_pAngleSpinBox;
    QSpacerItem *spacerItem;
    QDial *m_pAngleDial;
    QWidget *m_pPositionPage;
    QVBoxLayout *vboxLayout5;
    QHBoxLayout *hboxLayout3;
    QLabel *m_pPositionLabel;
    QDoubleSpinBox *m_pPositionDoubleSpinBox;
    QHBoxLayout *hboxLayout4;
    QLabel *m_pAxisLabel;
    QComboBox *m_pAxisComboBox;
    QWidget *m_pNoArgsPage;
    QLabel *m_pNoArgumentsLabel;
    QListWidget *m_pCommandsListWidget;
    QMenuBar *m_pMenubar;
    QMenu *m_pMenuFile;
    QMenu *m_pMenuHelp;
    QStatusBar *m_pStatusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(623, 553);
    m_pActionExit = new QAction(MainWindow);
    m_pActionExit->setObjectName(QString::fromUtf8("m_pActionExit"));
    m_pCentralwidget = new QWidget(MainWindow);
    m_pCentralwidget->setObjectName(QString::fromUtf8("m_pCentralwidget"));
    vboxLayout = new QVBoxLayout(m_pCentralwidget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    m_pCamera1Label = new QLabel(m_pCentralwidget);
    m_pCamera1Label->setObjectName(QString::fromUtf8("m_pCamera1Label"));
    m_pCamera1Label->setMaximumSize(QSize(133, 100));
    m_pCamera1Label->setFrameShape(QFrame::StyledPanel);
    m_pCamera1Label->setScaledContents(true);

    vboxLayout1->addWidget(m_pCamera1Label);

    m_pCamera2Label = new QLabel(m_pCentralwidget);
    m_pCamera2Label->setObjectName(QString::fromUtf8("m_pCamera2Label"));
    m_pCamera2Label->setMaximumSize(QSize(133, 100));
    m_pCamera2Label->setFrameShape(QFrame::StyledPanel);
    m_pCamera2Label->setScaledContents(true);

    vboxLayout1->addWidget(m_pCamera2Label);

    m_pCamera3Label = new QLabel(m_pCentralwidget);
    m_pCamera3Label->setObjectName(QString::fromUtf8("m_pCamera3Label"));
    m_pCamera3Label->setMaximumSize(QSize(133, 100));
    m_pCamera3Label->setFrameShape(QFrame::StyledPanel);
    m_pCamera3Label->setScaledContents(true);

    vboxLayout1->addWidget(m_pCamera3Label);


    hboxLayout->addLayout(vboxLayout1);

    m_pMainCameraLabel = new QLabel(m_pCentralwidget);
    m_pMainCameraLabel->setObjectName(QString::fromUtf8("m_pMainCameraLabel"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(m_pMainCameraLabel->sizePolicy().hasHeightForWidth());
    m_pMainCameraLabel->setSizePolicy(sizePolicy);
    m_pMainCameraLabel->setMinimumSize(QSize(0, 0));
    m_pMainCameraLabel->setFrameShape(QFrame::StyledPanel);
    m_pMainCameraLabel->setScaledContents(true);

    hboxLayout->addWidget(m_pMainCameraLabel);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    m_pDetailsGroupBox = new QGroupBox(m_pCentralwidget);
    m_pDetailsGroupBox->setObjectName(QString::fromUtf8("m_pDetailsGroupBox"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(m_pDetailsGroupBox->sizePolicy().hasHeightForWidth());
    m_pDetailsGroupBox->setSizePolicy(sizePolicy1);
    m_pDetailsGroupBox->setMinimumSize(QSize(401, 200));
    m_pDetailsGroupBox->setFlat(false);
    m_pDetailsGroupBox->setCheckable(false);
    verticalLayout = new QWidget(m_pDetailsGroupBox);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setGeometry(QRect(9, 10, 191, 181));
    vboxLayout2 = new QVBoxLayout(verticalLayout);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    vboxLayout2->setContentsMargins(0, 0, 0, 0);
    m_pDescriptionGroupBox = new QGroupBox(verticalLayout);
    m_pDescriptionGroupBox->setObjectName(QString::fromUtf8("m_pDescriptionGroupBox"));
    vboxLayout3 = new QVBoxLayout(m_pDescriptionGroupBox);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    m_pDescriptionLabel = new QLabel(m_pDescriptionGroupBox);
    m_pDescriptionLabel->setObjectName(QString::fromUtf8("m_pDescriptionLabel"));
    m_pDescriptionLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    m_pDescriptionLabel->setWordWrap(true);

    vboxLayout3->addWidget(m_pDescriptionLabel);


    vboxLayout2->addWidget(m_pDescriptionGroupBox);

    m_pExecuteButton = new QPushButton(verticalLayout);
    m_pExecuteButton->setObjectName(QString::fromUtf8("m_pExecuteButton"));
    m_pExecuteButton->setEnabled(false);

    vboxLayout2->addWidget(m_pExecuteButton);

    m_pCommandLabel = new QLabel(m_pDetailsGroupBox);
    m_pCommandLabel->setObjectName(QString::fromUtf8("m_pCommandLabel"));
    m_pCommandLabel->setGeometry(QRect(220, 10, 163, 20));
    m_pCommandLabel->setAlignment(Qt::AlignCenter);
    m_pArgumentsStackedWidget = new QStackedWidget(m_pDetailsGroupBox);
    m_pArgumentsStackedWidget->setObjectName(QString::fromUtf8("m_pArgumentsStackedWidget"));
    m_pArgumentsStackedWidget->setGeometry(QRect(210, 30, 181, 161));
    m_pAnglePage = new QWidget();
    m_pAnglePage->setObjectName(QString::fromUtf8("m_pAnglePage"));
    vboxLayout4 = new QVBoxLayout(m_pAnglePage);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    m_pAngleLabel = new QLabel(m_pAnglePage);
    m_pAngleLabel->setObjectName(QString::fromUtf8("m_pAngleLabel"));

    hboxLayout2->addWidget(m_pAngleLabel);

    m_pAngleSpinBox = new QSpinBox(m_pAnglePage);
    m_pAngleSpinBox->setObjectName(QString::fromUtf8("m_pAngleSpinBox"));
    m_pAngleSpinBox->setMaximum(360);

    hboxLayout2->addWidget(m_pAngleSpinBox);

    spacerItem = new QSpacerItem(25, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem);


    vboxLayout4->addLayout(hboxLayout2);

    m_pAngleDial = new QDial(m_pAnglePage);
    m_pAngleDial->setObjectName(QString::fromUtf8("m_pAngleDial"));
    m_pAngleDial->setMaximum(360);
    m_pAngleDial->setSliderPosition(0);
    m_pAngleDial->setOrientation(Qt::Horizontal);
    m_pAngleDial->setWrapping(true);
    m_pAngleDial->setNotchTarget(6);
    m_pAngleDial->setNotchesVisible(true);

    vboxLayout4->addWidget(m_pAngleDial);

    m_pArgumentsStackedWidget->addWidget(m_pAnglePage);
    m_pPositionPage = new QWidget();
    m_pPositionPage->setObjectName(QString::fromUtf8("m_pPositionPage"));
    vboxLayout5 = new QVBoxLayout(m_pPositionPage);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    m_pPositionLabel = new QLabel(m_pPositionPage);
    m_pPositionLabel->setObjectName(QString::fromUtf8("m_pPositionLabel"));

    hboxLayout3->addWidget(m_pPositionLabel);

    m_pPositionDoubleSpinBox = new QDoubleSpinBox(m_pPositionPage);
    m_pPositionDoubleSpinBox->setObjectName(QString::fromUtf8("m_pPositionDoubleSpinBox"));

    hboxLayout3->addWidget(m_pPositionDoubleSpinBox);


    vboxLayout5->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    m_pAxisLabel = new QLabel(m_pPositionPage);
    m_pAxisLabel->setObjectName(QString::fromUtf8("m_pAxisLabel"));

    hboxLayout4->addWidget(m_pAxisLabel);

    m_pAxisComboBox = new QComboBox(m_pPositionPage);
    m_pAxisComboBox->setObjectName(QString::fromUtf8("m_pAxisComboBox"));

    hboxLayout4->addWidget(m_pAxisComboBox);


    vboxLayout5->addLayout(hboxLayout4);

    m_pArgumentsStackedWidget->addWidget(m_pPositionPage);
    m_pNoArgsPage = new QWidget();
    m_pNoArgsPage->setObjectName(QString::fromUtf8("m_pNoArgsPage"));
    m_pNoArgumentsLabel = new QLabel(m_pNoArgsPage);
    m_pNoArgumentsLabel->setObjectName(QString::fromUtf8("m_pNoArgumentsLabel"));
    m_pNoArgumentsLabel->setGeometry(QRect(50, 60, 67, 20));
    m_pArgumentsStackedWidget->addWidget(m_pNoArgsPage);

    hboxLayout1->addWidget(m_pDetailsGroupBox);

    m_pCommandsListWidget = new QListWidget(m_pCentralwidget);
    m_pCommandsListWidget->setObjectName(QString::fromUtf8("m_pCommandsListWidget"));
    QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(m_pCommandsListWidget->sizePolicy().hasHeightForWidth());
    m_pCommandsListWidget->setSizePolicy(sizePolicy2);

    hboxLayout1->addWidget(m_pCommandsListWidget);


    vboxLayout->addLayout(hboxLayout1);

    MainWindow->setCentralWidget(m_pCentralwidget);
    m_pMenubar = new QMenuBar(MainWindow);
    m_pMenubar->setObjectName(QString::fromUtf8("m_pMenubar"));
    m_pMenubar->setGeometry(QRect(0, 0, 623, 21));
    m_pMenuFile = new QMenu(m_pMenubar);
    m_pMenuFile->setObjectName(QString::fromUtf8("m_pMenuFile"));
    m_pMenuHelp = new QMenu(m_pMenubar);
    m_pMenuHelp->setObjectName(QString::fromUtf8("m_pMenuHelp"));
    MainWindow->setMenuBar(m_pMenubar);
    m_pStatusbar = new QStatusBar(MainWindow);
    m_pStatusbar->setObjectName(QString::fromUtf8("m_pStatusbar"));
    MainWindow->setStatusBar(m_pStatusbar);
    m_pAngleLabel->setBuddy(m_pAngleSpinBox);

    m_pMenubar->addAction(m_pMenuFile->menuAction());
    m_pMenubar->addAction(m_pMenuHelp->menuAction());
    m_pMenuFile->addAction(m_pActionExit);

    retranslateUi(MainWindow);
    QObject::connect(m_pActionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
    QObject::connect(m_pAngleDial, SIGNAL(valueChanged(int)), m_pAngleSpinBox, SLOT(setValue(int)));
    QObject::connect(m_pAngleSpinBox, SIGNAL(valueChanged(int)), m_pAngleDial, SLOT(setValue(int)));
    QObject::connect(m_pCommandsListWidget, SIGNAL(currentTextChanged(QString)), m_pCommandLabel, SLOT(setText(QString)));

    m_pArgumentsStackedWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    m_pActionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
    m_pCamera1Label->setText(QString());
    m_pCamera2Label->setText(QString());
    m_pCamera3Label->setText(QString());
    m_pMainCameraLabel->setText(QString());
    m_pDetailsGroupBox->setTitle(QApplication::translate("MainWindow", "Command details", 0, QApplication::UnicodeUTF8));
    m_pDescriptionGroupBox->setTitle(QApplication::translate("MainWindow", "Description", 0, QApplication::UnicodeUTF8));
    m_pDescriptionLabel->setText(QApplication::translate("MainWindow", "This is a short description of what a command does, to inform the user of the program what he's about to do.", 0, QApplication::UnicodeUTF8));
    m_pExecuteButton->setText(QApplication::translate("MainWindow", "Execute command", 0, QApplication::UnicodeUTF8));
    m_pCommandLabel->setText(QApplication::translate("MainWindow", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Command</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    m_pAngleLabel->setText(QApplication::translate("MainWindow", "Angle:", 0, QApplication::UnicodeUTF8));
    m_pPositionLabel->setText(QApplication::translate("MainWindow", "Position:", 0, QApplication::UnicodeUTF8));
    m_pAxisLabel->setText(QApplication::translate("MainWindow", "Axis:", 0, QApplication::UnicodeUTF8));
    m_pAxisComboBox->clear();
    m_pAxisComboBox->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8)
     << QApplication::translate("MainWindow", "Z", 0, QApplication::UnicodeUTF8)
    );
    m_pNoArgumentsLabel->setText(QApplication::translate("MainWindow", "No arguments", 0, QApplication::UnicodeUTF8));
    m_pCommandsListWidget->clear();

    QListWidgetItem *__item = new QListWidgetItem(m_pCommandsListWidget);
    __item->setText(QApplication::translate("MainWindow", "Initialize", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item1 = new QListWidgetItem(m_pCommandsListWidget);
    __item1->setText(QApplication::translate("MainWindow", "Park", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item2 = new QListWidgetItem(m_pCommandsListWidget);
    __item2->setText(QApplication::translate("MainWindow", "Rotate absolute", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item3 = new QListWidgetItem(m_pCommandsListWidget);
    __item3->setText(QApplication::translate("MainWindow", "Rotate relative", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item4 = new QListWidgetItem(m_pCommandsListWidget);
    __item4->setText(QApplication::translate("MainWindow", "Position absolute", 0, QApplication::UnicodeUTF8));

    QListWidgetItem *__item5 = new QListWidgetItem(m_pCommandsListWidget);
    __item5->setText(QApplication::translate("MainWindow", "Position relative", 0, QApplication::UnicodeUTF8));
    m_pMenuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    m_pMenuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // UI_MAINWINDOW_H
