#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QFile>
#include "Rijndael.h"
#include <cstring>
#include <iostream>
#include <fstream>
#define MAX_SIZE 192    //buffer size，一定是16,32,48的公倍数
using namespace std;

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

    void on_Btn_file_clicked();

    void on_Btn_save_clicked();

    void on_rBtn_compare_toggled(bool checked);

    void on_Btn_file1_clicked();

    void on_Btn_file2_clicked();

    void on_Btn_compare_clicked();

private:
    Ui::MainWin *ui;
    CRijndael m_Rijndael;         //AES实现对象
    int keyLen;    //密钥块长度
    int blockSize;   //数据块长度
    int iMode;      //ECB,CBC,CFB模式索引
    char key[50];    //key最长48个字符
    QString fileName, fileName2, saveName;

    void getKey();      //从ui->lineEdit获取Key值并转化为char*
    void QStr2Char(const QString qstr, char* newChar);       //将QString对象转换为char*
    long readFile(char *&memblock, const string &filename);          //读取文件
    int writeFile(char *content, const string &filename, long size);    //写入文件
    int encryptFile(const char *key, char *in, char *out, long size);   //加密文件
    char* partitionEncrypt(const char *key, char *in, long size);       //分部加密，最后一个块大小不完整情况
    char* partitionEncrypt2(const char *key, char *in, long size);      //分部加密，整除情况
    int decryptFile(const char *key, char *in, char *out, long size);   //解密文件
    char* partitionDecrypt(const char *key, char *in, long size);       //分部解密，末尾含'\0'
    char* partitionDecrypt2(const char *key, char *in, long size);      //分部加密，末尾不含'\0'
    int doEncrypt(string fileToEncrypt, string saveEncrypt, const char *key);   //加密封装
    int doDecrypt(string fileToDecrypt, string saveDecrypt, const char *key);   //解密封装
    float compare(const string &f1, const string &f2);      //加密文件比对字节差异比例
};

#endif // MAINWIN_H
