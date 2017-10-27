#include "mainwin.h"
#include "ui_mainwin.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    keyLen = 16;
    blockSize = 16;
    iMode = 0;
    inputLen = 0;
    memset(key, 0, sizeof(key)*4);
    memset(szDataIn, 0, MAX_SIZE);
    memset(szDataOut, 0, MAX_SIZE);
    memset(szHex, 0, MAX_SIZE*2);
}

MainWin::~MainWin()
{
    delete ui;
}

// 将QString对象转换为char*
void MainWin::QStr2Char(const QString qstr, char* newChar)
{
    if(qstr.length()>1024*1024)
    {
        qDebug("QString长度超出栈大小（1MB）\n");
        QMessageBox::warning(this,tr("Warning"),tr("The input-text is too large!"),QMessageBox::Yes);
        return;
    }
    /*
    QByteArray barray = qstr.toLatin1();
    newChar = (char*)malloc(qstr.length());
    strcpy(newChar,barray.data());
    */
    std::string str = qstr.toStdString();
    const char* ch = str.c_str();
    if(sizeof(newChar)<sizeof(ch))
    {
        newChar = new char[qstr.length()];
        memset(newChar, 0, sizeof(newChar)*4 - 1);
    }
    strcpy(newChar, ch);
}

// 从ui->lineEdit获取Key值并互转化为char*
void MainWin::getKey()
{
    QString keyStr = ui->lineEdit_key->text();
    if(keyStr.isEmpty())
    {
        qDebug("Please input Key!");
        QMessageBox::warning(this,tr("Warning"),tr("Please input Key!"));
        return;
    }
    QStr2Char(keyStr, key);
}

// 从ui->textEdit获取文本并转化为char*；为szDataInszDataOut,szHex分配合适大小的内存空间;并把内容存入szDataIn。
void MainWin::getInputText(char* szData)
{
    QString inputStr = ui->textEdit_input->document()->toPlainText();  //从textEdit控件中获取文本
    QStr2Char(inputStr, szData);
    inputLen = strlen(szDataIn);   //inputStr.length() + 1;

    /*
    szDataIn = new char[len];
    memset(szDataIn,0,len-1);
    szDataOut = new char[len];
    memset(szDataOut,0,len-1);
    szHex = new char[2*len];
    memset(szHex,0,2*len-1);
    strcpy(szDataIn, input);
    */
}

//Function to convert unsigned char to string of length 2
void MainWin::Char2Hex(unsigned char ch, char* szHex)
{
    char byte[2];
    byte[0] = ch/16;
    byte[1] = ch%16;
    for(int i=0; i<2; i++)
    {
        if(byte[i] >= 0 && byte[i] <= 9)
            szHex[i] = '0' + byte[i];
        else
            szHex[i] = 'A' + byte[i] - 10;
    }
    szHex[2] = 0;
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

//Function to convert string of chars to string of unsigned chars
void MainWin::HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize)
{
    int i;
    unsigned char ch;
    for(i=0; i<iSize; i++)
    {
        Hex2Char(pszHexStr+2*i, ch);
        pucCharStr[i] = ch;
    }
}

int MainWin::hexcharToInt(char c)
{
    if (c >= '0' && c <= '9') return (c - '0');
    if (c >= 'A' && c <= 'F') return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f') return (c - 'a' + 10);
    return 0;
}

void MainWin::hexstringToBytes(char* hexstring,char* bytes,int hexlength)
{
    for (int i=0 ; i <hexlength ; i+=2)
        *bytes++ = (char) ((hexcharToInt(hexstring[i]) << 4) | hexcharToInt(hexstring[i+1]));
}

// comboBox_keyLen中的选项触发的槽函数,保证数据块长度大于密钥；并设置key length
void MainWin::on_comboBox_keyLen_currentIndexChanged(int index)
{
    ui->comboBox_blockLen->clear();    //首先清理一次项目
    switch(index)
    {
        case 0:
            ui->comboBox_blockLen->addItem(tr("16"));
        case 1:
            ui->comboBox_blockLen->addItem(tr("24"));
        case 2:
            ui->comboBox_blockLen->addItem(tr("32"));
    }
    keyLen = (index + 2)*8;    //设置key length
}

// 设置加密/解密mode,恰好等于索引
void MainWin::on_comboBox_mode_currentIndexChanged(int index)
{
    iMode = index;
}

// 根据选中的内容设置blockSize
void MainWin::on_comboBox_blockLen_currentTextChanged(const QString &arg1)
{
    blockSize = arg1.toInt();   //QString转换为int即可
}

// 清空input框，为新的输入做准备
void MainWin::on_Btn_clear_clicked()
{
    ui->textEdit_input->clear();
}

// 加密
void MainWin::on_Btn_encrypt_clicked()
{
    CRijndael m_Rijndael;         //AES实现对象
    ui->textEdit_output->clear();       //清空output框
    getInputText(szDataIn);
    memset(szDataOut, 0, inputLen);
    memset(szHex, 0, 2*inputLen);
    qDebug()<<szDataIn<<strlen(szHex)<<" "<<blockSize<<" "<<strlen(szDataIn)<<endl;

    try{
        m_Rijndael.MakeKey(key,CRijndael::sm_chain0,keyLen,blockSize);
        m_Rijndael.Encrypt(szDataIn,szDataOut,strlen(szDataIn),iMode);
        //qDebug()<<"szDataOut:"<<szDataOut<<endl;

        CharStr2HexStr((unsigned char*)szDataOut,szHex,strlen(szDataOut));
        QString output(szHex);
        ui->textEdit_output->setText(output);
    } catch (QString exception) {
        QMessageBox::warning(this,tr("Warning"),exception);
    }
}

// 解密
void MainWin::on_Btn_decrypt_clicked()
{
    CRijndael m_Rijndael;         //AES实现对象
    ui->textEdit_output->clear();    //清空output框
    memset(szHex, 0, MAX_SIZE * 2);
    getInputText(szHex);
    memset(szDataIn, 0, inputLen);
    memset(szDataOut, 0, inputLen);
    //hexstringToBytes(szHex, szDataIn, strlen(szHex));
    HexStr2CharStr(szHex,(unsigned char*)szDataIn,strlen(szHex));   //将16进制转化为字符串
    qDebug()<<szHex<<endl<<"Hex2Char:"<<szDataIn<<endl;

    try{
        m_Rijndael.MakeKey(key,CRijndael::sm_chain0,keyLen,blockSize);
        m_Rijndael.Decrypt(szDataIn,szDataOut,strlen(szDataIn),iMode);
        //m_Rijndael.Decrypt(szDataOut,szDataIn,strlen(szDataOut),iMode);

        QString output(szDataOut);
        ui->textEdit_output->setText(output);
    } catch (QString exception) {
        QMessageBox::warning(this,tr("Warning"),exception);
    }
}
