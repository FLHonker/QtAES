#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include "Rijndael.h"
#define MAX_SIZE 1024

namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private slots:
    void on_comboBox_keyLen_currentIndexChanged(int index);

    void on_comboBox_mode_currentIndexChanged(int index);

    void on_comboBox_blockLen_currentTextChanged(const QString &arg1);

    void on_Btn_encrypt_clicked();

    void on_Btn_decrypt_clicked();

    void on_Btn_clear_clicked();

private:
    Ui::MainWin *ui;
    int keyLen;    //密钥块长度
    int blockSize;   //数据块长度
    int iMode;      //ECB,CBC,CFB模式索引
    int inputLen;    //输入文本的长度
    char key[50];    //key最长48个字符
    char szDataIn[MAX_SIZE];    //存储输入文本的数组
    char szDataOut[MAX_SIZE], szHex[MAX_SIZE * 2];

    void getKey();      //从ui->lineEdit获取Key值并互赞华为char*
    void QStr2Char(const QString qstr, char* newChar);    //将QString对象转换为char*
    void getInputText(char* szData);   //从ui->textEdit获取文本并转化为char*
    void Char2Hex(unsigned char ch, char* szHex);
    void Hex2Char(char const* szHex, unsigned char& rch);
    void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
    void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
};

#endif // MAINWIN_H
