#include "mainwin.h"
#include "ui_mainwin.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

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

// import file
void MainWin::on_Btn_file_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("All Files (*.*)"));  //选择路径
    if(fileName.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    }
    ui->lineEdit_input->setText(fileName);
    inFile = new QFile(fileName);
    outFile = new QFile(fileName + ".aes");
}

bool MainWin::openFiles()
{
    if(!inFile->open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Warning"), tr("Can't open the infile."));
        return false;
    }
    if(!outFile->open(QFile::WriteOnly | QFile::Append))   //不存在则创建文件
    {
        QMessageBox::warning(this, tr("Warning"), tr("Can't open the outfile."));
        return false;
    }

    return true;
}

bool MainWin::readFile(char* buffer)
{
    memset(buffer, 0, sizeof(buffer)*4);  //读之前先清空buffer
    qint64 len = 0;
    if(inFile->atEnd())
    {
        inFile->close();
        return false;
    }
    else
        len = inFile->read(buffer, MAX_SIZE);
    if(len == -1)
        return false;
    return true;
}

void MainWin::writeFile(char* buffer)
{
    outFile->write(buffer, sizeof(buffer));
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
    ui->lineEdit_input->clear();
}

// 加密
void MainWin::on_Btn_encrypt_clicked()
{
    if(!openFiles())    //打开文件
    {
        return;
    }
    CRijndael m_Rijndael;         //AES实现对象
    ui->lineEdit_output->clear();       //清空output框
    while(readFile(szDataIn))   //读取文件至末尾
    {
        memset(szDataOut, 0, inputLen);
        memset(szHex, 0, 2*inputLen);
        qDebug()<<szDataIn<<strlen(szHex)<<" "<<blockSize<<" "<<strlen(szDataIn)<<endl;

        try{
            m_Rijndael.MakeKey(key,CRijndael::sm_chain0,keyLen,blockSize);
            m_Rijndael.Encrypt(szDataIn,szDataOut,strlen(szDataIn),iMode);
            //qDebug()<<"szDataOut:"<<szDataOut<<endl;
            CharStr2HexStr((unsigned char*)szDataOut,szHex,strlen(szDataOut));
            writeFile(szHex);    //将16进制字符缓冲区写入文件
        } catch (QString exception) {
            QMessageBox::warning(this,tr("Warning"),exception);
        }
    }
    outFile->close();
    ui->lineEdit_output->setText(fileName + ".aes");  //output框显示输出文件
}

// 解密
void MainWin::on_Btn_decrypt_clicked()
{
    if(!openFiles())  //打开文件
    {
        return;
    }
    CRijndael m_Rijndael;         //AES实现对象
    ui->lineEdit_output->clear();    //清空output框
   while(readFile(szHex))
   {
       memset(szDataIn, 0, inputLen);
       memset(szDataOut, 0, inputLen);
       HexStr2CharStr(szHex,(unsigned char*)szDataIn,strlen(szHex));   //将16进制转化为字符串
       //qDebug()<<szHex<<endl<<"Hex2Char:"<<szDataIn<<endl;

       try{
           m_Rijndael.MakeKey(key,CRijndael::sm_chain0,keyLen,blockSize);
           m_Rijndael.Decrypt(szDataIn,szDataOut,strlen(szDataIn),iMode);

           writeFile(szDataOut);
       } catch (QString exception) {
           QMessageBox::warning(this,tr("Warning"),exception);
       }
   }
   outFile->close();
   fileName.remove(".aes");
   ui->lineEdit_output->setText(fileName); //output框显示输出文件
}
