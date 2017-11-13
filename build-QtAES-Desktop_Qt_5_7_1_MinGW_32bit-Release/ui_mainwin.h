/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWin
{
public:
    QWidget *centralWidget;
    QLabel *label_keyLen;
    QLabel *label_mode;
    QGroupBox *groupBox_settings;
    QRadioButton *rBtn_compare;
    QComboBox *comboBox_mode;
    QLabel *label_key;
    QLineEdit *lineEdit_key;
    QPushButton *Btn_encrypt;
    QPushButton *Btn_decrypt;
    QComboBox *comboBox_keyLen;
    QLabel *label_input;
    QLabel *label;
    QGroupBox *groupBox;
    QLabel *label_blockLen;
    QComboBox *comboBox_blockLen;
    QLabel *label_change;
    QLabel *label_percentage;
    QPushButton *Btn_file;
    QLineEdit *lineEdit_input;
    QLineEdit *lineEdit_output;
    QPushButton *Btn_save;
    QLabel *label_file1;
    QLabel *label_file2;
    QLineEdit *lineEdit_file1;
    QLineEdit *lineEdit_file2;
    QGroupBox *groupBox_compare;
    QPushButton *Btn_compare;
    QPushButton *Btn_file1;
    QPushButton *Btn_file2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWin)
    {
        if (MainWin->objectName().isEmpty())
            MainWin->setObjectName(QStringLiteral("MainWin"));
        MainWin->resize(480, 374);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWin->sizePolicy().hasHeightForWidth());
        MainWin->setSizePolicy(sizePolicy);
        MainWin->setMinimumSize(QSize(480, 266));
        MainWin->setMaximumSize(QSize(480, 374));
        MainWin->setMouseTracking(false);
        MainWin->setFocusPolicy(Qt::ClickFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/images/locker1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWin->setWindowIcon(icon);
        centralWidget = new QWidget(MainWin);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label_keyLen = new QLabel(centralWidget);
        label_keyLen->setObjectName(QStringLiteral("label_keyLen"));
        label_keyLen->setGeometry(QRect(40, 30, 61, 21));
        label_mode = new QLabel(centralWidget);
        label_mode->setObjectName(QStringLiteral("label_mode"));
        label_mode->setGeometry(QRect(40, 60, 51, 21));
        groupBox_settings = new QGroupBox(centralWidget);
        groupBox_settings->setObjectName(QStringLiteral("groupBox_settings"));
        groupBox_settings->setGeometry(QRect(20, 10, 311, 111));
        rBtn_compare = new QRadioButton(groupBox_settings);
        rBtn_compare->setObjectName(QStringLiteral("rBtn_compare"));
        rBtn_compare->setGeometry(QRect(170, 50, 111, 21));
        comboBox_mode = new QComboBox(centralWidget);
        comboBox_mode->setObjectName(QStringLiteral("comboBox_mode"));
        comboBox_mode->setGeometry(QRect(100, 60, 61, 22));
        comboBox_mode->setCursor(QCursor(Qt::OpenHandCursor));
        label_key = new QLabel(centralWidget);
        label_key->setObjectName(QStringLiteral("label_key"));
        label_key->setGeometry(QRect(40, 90, 21, 16));
        lineEdit_key = new QLineEdit(centralWidget);
        lineEdit_key->setObjectName(QStringLiteral("lineEdit_key"));
        lineEdit_key->setGeometry(QRect(70, 90, 241, 20));
        lineEdit_key->setFocusPolicy(Qt::StrongFocus);
        Btn_encrypt = new QPushButton(centralWidget);
        Btn_encrypt->setObjectName(QStringLiteral("Btn_encrypt"));
        Btn_encrypt->setGeometry(QRect(370, 40, 75, 23));
        Btn_encrypt->setCursor(QCursor(Qt::PointingHandCursor));
        Btn_encrypt->setAutoDefault(false);
        Btn_encrypt->setFlat(false);
        Btn_decrypt = new QPushButton(centralWidget);
        Btn_decrypt->setObjectName(QStringLiteral("Btn_decrypt"));
        Btn_decrypt->setGeometry(QRect(370, 90, 75, 23));
        Btn_decrypt->setCursor(QCursor(Qt::PointingHandCursor));
        comboBox_keyLen = new QComboBox(centralWidget);
        comboBox_keyLen->setObjectName(QStringLiteral("comboBox_keyLen"));
        comboBox_keyLen->setGeometry(QRect(110, 30, 51, 22));
        comboBox_keyLen->setCursor(QCursor(Qt::OpenHandCursor));
        label_input = new QLabel(centralWidget);
        label_input->setObjectName(QStringLiteral("label_input"));
        label_input->setGeometry(QRect(21, 140, 36, 16));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 190, 41, 16));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(349, 20, 111, 101));
        label_blockLen = new QLabel(centralWidget);
        label_blockLen->setObjectName(QStringLiteral("label_blockLen"));
        label_blockLen->setGeometry(QRect(180, 30, 81, 21));
        comboBox_blockLen = new QComboBox(centralWidget);
        comboBox_blockLen->setObjectName(QStringLiteral("comboBox_blockLen"));
        comboBox_blockLen->setGeometry(QRect(260, 30, 51, 22));
        comboBox_blockLen->setCursor(QCursor(Qt::OpenHandCursor));
        label_change = new QLabel(centralWidget);
        label_change->setObjectName(QStringLiteral("label_change"));
        label_change->setGeometry(QRect(140, 300, 81, 21));
        label_percentage = new QLabel(centralWidget);
        label_percentage->setObjectName(QStringLiteral("label_percentage"));
        label_percentage->setGeometry(QRect(220, 300, 81, 21));
        Btn_file = new QPushButton(centralWidget);
        Btn_file->setObjectName(QStringLiteral("Btn_file"));
        Btn_file->setGeometry(QRect(380, 140, 81, 23));
        lineEdit_input = new QLineEdit(centralWidget);
        lineEdit_input->setObjectName(QStringLiteral("lineEdit_input"));
        lineEdit_input->setGeometry(QRect(62, 140, 311, 20));
        lineEdit_input->setReadOnly(true);
        lineEdit_output = new QLineEdit(centralWidget);
        lineEdit_output->setObjectName(QStringLiteral("lineEdit_output"));
        lineEdit_output->setGeometry(QRect(60, 190, 311, 20));
        lineEdit_output->setReadOnly(true);
        Btn_save = new QPushButton(centralWidget);
        Btn_save->setObjectName(QStringLiteral("Btn_save"));
        Btn_save->setGeometry(QRect(380, 190, 81, 23));
        label_file1 = new QLabel(centralWidget);
        label_file1->setObjectName(QStringLiteral("label_file1"));
        label_file1->setGeometry(QRect(20, 240, 31, 21));
        label_file2 = new QLabel(centralWidget);
        label_file2->setObjectName(QStringLiteral("label_file2"));
        label_file2->setGeometry(QRect(20, 270, 31, 21));
        lineEdit_file1 = new QLineEdit(centralWidget);
        lineEdit_file1->setObjectName(QStringLiteral("lineEdit_file1"));
        lineEdit_file1->setGeometry(QRect(60, 240, 311, 21));
        lineEdit_file1->setReadOnly(true);
        lineEdit_file2 = new QLineEdit(centralWidget);
        lineEdit_file2->setObjectName(QStringLiteral("lineEdit_file2"));
        lineEdit_file2->setGeometry(QRect(60, 270, 311, 21));
        lineEdit_file2->setReadOnly(true);
        groupBox_compare = new QGroupBox(centralWidget);
        groupBox_compare->setObjectName(QStringLiteral("groupBox_compare"));
        groupBox_compare->setGeometry(QRect(10, 220, 461, 101));
        Btn_compare = new QPushButton(groupBox_compare);
        Btn_compare->setObjectName(QStringLiteral("Btn_compare"));
        Btn_compare->setGeometry(QRect(300, 80, 61, 21));
        Btn_file1 = new QPushButton(groupBox_compare);
        Btn_file1->setObjectName(QStringLiteral("Btn_file1"));
        Btn_file1->setGeometry(QRect(370, 20, 81, 23));
        Btn_file2 = new QPushButton(groupBox_compare);
        Btn_file2->setObjectName(QStringLiteral("Btn_file2"));
        Btn_file2->setGeometry(QRect(370, 50, 81, 23));
        MainWin->setCentralWidget(centralWidget);
        groupBox_compare->raise();
        groupBox_settings->raise();
        groupBox->raise();
        label_keyLen->raise();
        label_mode->raise();
        comboBox_mode->raise();
        label_key->raise();
        lineEdit_key->raise();
        Btn_encrypt->raise();
        Btn_decrypt->raise();
        comboBox_keyLen->raise();
        label_input->raise();
        label->raise();
        label_blockLen->raise();
        comboBox_blockLen->raise();
        label_change->raise();
        label_percentage->raise();
        Btn_file->raise();
        lineEdit_input->raise();
        lineEdit_output->raise();
        Btn_save->raise();
        label_file1->raise();
        label_file2->raise();
        lineEdit_file1->raise();
        lineEdit_file2->raise();
        menuBar = new QMenuBar(MainWin);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 480, 22));
        MainWin->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWin);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWin->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWin);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWin->setStatusBar(statusBar);

        retranslateUi(MainWin);

        Btn_encrypt->setDefault(true);


        QMetaObject::connectSlotsByName(MainWin);
    } // setupUi

    void retranslateUi(QMainWindow *MainWin)
    {
        MainWin->setWindowTitle(QApplication::translate("MainWin", "Qt AES", Q_NULLPTR));
        label_keyLen->setText(QApplication::translate("MainWin", "Key length", Q_NULLPTR));
        label_mode->setText(QApplication::translate("MainWin", "AES Mode", Q_NULLPTR));
        groupBox_settings->setTitle(QApplication::translate("MainWin", "Settings", Q_NULLPTR));
        rBtn_compare->setText(QApplication::translate("MainWin", "compare files", Q_NULLPTR));
        comboBox_mode->clear();
        comboBox_mode->insertItems(0, QStringList()
         << QApplication::translate("MainWin", "ECB", Q_NULLPTR)
         << QApplication::translate("MainWin", "CBC", Q_NULLPTR)
         << QApplication::translate("MainWin", "CFB", Q_NULLPTR)
        );
        label_key->setText(QApplication::translate("MainWin", "Key", Q_NULLPTR));
        lineEdit_key->setPlaceholderText(QApplication::translate("MainWin", "Enter a key of the selected length...", Q_NULLPTR));
        Btn_encrypt->setText(QApplication::translate("MainWin", "Encrypt", Q_NULLPTR));
        Btn_encrypt->setShortcut(QApplication::translate("MainWin", "Ctrl+E", Q_NULLPTR));
        Btn_decrypt->setText(QApplication::translate("MainWin", "Decrypt", Q_NULLPTR));
        Btn_decrypt->setShortcut(QApplication::translate("MainWin", "Ctrl+D", Q_NULLPTR));
        comboBox_keyLen->clear();
        comboBox_keyLen->insertItems(0, QStringList()
         << QApplication::translate("MainWin", "16", Q_NULLPTR)
         << QApplication::translate("MainWin", "24", Q_NULLPTR)
         << QApplication::translate("MainWin", "32", Q_NULLPTR)
        );
        label_input->setText(QApplication::translate("MainWin", "Input:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWin", "Output:", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWin", "AES", Q_NULLPTR));
        label_blockLen->setText(QApplication::translate("MainWin", "Block length", Q_NULLPTR));
        comboBox_blockLen->clear();
        comboBox_blockLen->insertItems(0, QStringList()
         << QApplication::translate("MainWin", "16", Q_NULLPTR)
         << QApplication::translate("MainWin", "24", Q_NULLPTR)
         << QApplication::translate("MainWin", "32", Q_NULLPTR)
        );
        label_change->setText(QApplication::translate("MainWin", "change chars:", Q_NULLPTR));
        label_percentage->setText(QApplication::translate("MainWin", "0%", Q_NULLPTR));
        Btn_file->setText(QApplication::translate("MainWin", "Import file", Q_NULLPTR));
        Btn_save->setText(QApplication::translate("MainWin", "Save path", Q_NULLPTR));
        label_file1->setText(QApplication::translate("MainWin", "file1", Q_NULLPTR));
        label_file2->setText(QApplication::translate("MainWin", "file2", Q_NULLPTR));
        groupBox_compare->setTitle(QApplication::translate("MainWin", "Compare Files", Q_NULLPTR));
        Btn_compare->setText(QApplication::translate("MainWin", "Compare", Q_NULLPTR));
        Btn_file1->setText(QApplication::translate("MainWin", "Import file1", Q_NULLPTR));
        Btn_file2->setText(QApplication::translate("MainWin", "Import file2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWin: public Ui_MainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
