#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "Rijndael.h"

namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private:
    Ui::MainWin *ui;
    CRijndael m_Rijndael;    //AES实现对象

    int getkeyLen();     //从ui->comboBox获取key length转换为数值
    int getMode();       //从ui->comboBox获取mode转换为数值
    char* QStr2Char(const QString str);    //将QString对象转换为char*
    void Hex2Char(char const* szHex, unsigned char& rch);
    void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
};

#endif // MAINWIN_H
