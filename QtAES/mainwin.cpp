#include "mainwin.h"
#include "ui_mainwin.h"
#include <QByteArray>
#include <QDebug>

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
}

MainWin::~MainWin()
{
    delete ui;
}

// 从ui->comboBox获取key length转换为数值
int MainWin::getkeyLen()
{
    int keyLen = 0;
    int index = ui->comboBox_keyLen->currentIndex();  //获取comboBox中被选中的索引
    switch(index)    //根据索引确定key length
    {
    case 0:
        keyLen = 16;
        break;
    case 1:
        keyLen = 24;
        break;
    case 2:
        keyLen = 32;
    }
    return keyLen;
}

// 从ui->comboBox获取mode转换为数值
int MainWin::getMode()
{
    int mode = ui->comboBox_mode->currentIndex();  //获取comboBox中被选中的索引,恰巧与mode值对应！

    return mode;
}

 // 将QString对象转换为char*
char* MainWin::QStr2Char(const QString str)
{
    if(str.length()>1024*1024)
    {
        qDebug("QString长度超出栈大小（1MB）\n");
        return NULL;
    }
    QByteArray barray = str.toLatin1();
    char *ch = barray.data();

    return ch;
}

//Function to convert string of length 2 to unsigned char
void MainWin::Hex2Char(char const* szHex, unsigned char& rch)
{
    rch = 0;
    for(int i=0; i<2; i++)
    {
        if(*(szHex + i) >='0' && *(szHex + i) <= '9')
            rch = (rch << 4) + (*(szHex + i) - '0');
        else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
            rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
        else
            break;
    }
}

//Function to convert string of unsigned chars to string of chars
void MainWin::CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize)
{
    int i;
    char szHex[3];
    pszHexStr[0] = 0;
    for(i=0; i<iSize; i++)
    {
        Char2Hex(pucCharStr[i], szHex);
        strcat(pszHexStr, szHex);
    }
}
