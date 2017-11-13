#include "mainwin.h"
#include "ui_mainwin.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
using namespace std;

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    keyLen = 16;
    blockSize = 16;
    iMode = 0;
    memset(key, 0, 50);
    ui->rBtn_compare->setChecked(false);
    ui->groupBox_compare->hide();
    ui->label_file1->hide();
    ui->label_file2->hide();
    ui->lineEdit_file1->hide();
    ui->lineEdit_file2->hide();
    ui->Btn_compare->hide();
    ui->label_change->hide();
    ui->label_percentage->hide();
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
    ui->lineEdit_output->clear();
}

// Save path
void MainWin::on_Btn_save_clicked()
{
    saveName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("All Files (*.*);;*.aes;;*.txt")); //选择路径
    ui->lineEdit_output->setText(saveName);
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

/**
 * 输入空指针，返回读取文件的内容
 * @param memblock
 */
long MainWin::readFile(char *&memblock, const string &filename)
{
    /*
     * 先跳转到文件末尾，然后计算文件长度，重定向文件指针到文件头部，读取整个文件内容
     */
    ifstream file(filename, ios::ate);
    long size = 0;
    // 读文件
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char[size];
        file.seekg(0, ios::beg);
        file.read(memblock, size);
    }
    file.close();
    return size;
}


/**
 * 把加密后的内容写到文件中
 */
int MainWin::writeFile(char *content, const string &filename, long size)
{
    ofstream file(filename, ios::out | ios::trunc);
    file.write(content, size + 1);
//    file << content;  // 如果 content 中出现 ‘\0’ 则不能正常运作
    file.close();
    return 0;
}


/**
 * 加密文件，加密后的内容保存在 out 指针所指向的地方
 * @return
 */
int MainWin::encryptFile(const char *key, char *in, char *out, long size)
{
    int keySize = strlen(key);
    if (keySize != 16 && keySize != 24 && keySize != 32)
    {
        QMessageBox::warning(this,tr("密钥错误"),tr("秘钥长度应该为 16 24 或者 32"));
        return -1;
    }
    CRijndael oRijndael;
    // 设置秘钥
    oRijndael.MakeKey(key, CRijndael::sm_chain0, keySize, keySize);
    // size 与 block_size 应该能够互相整除
    oRijndael.Encrypt(in, out, size, iMode);
    return 0;
}

/**
 * size 长度不包含空字符 '\0'
 */
char* MainWin::partitionEncrypt(const char *key, char *in, long size)
{
    long keySize = strlen(key);
    if (size % keySize != 0)
    {
        long leftCount = keySize - size % keySize;
        // 扩展至可以整除块大小
        auto tmpIn = new char[size + leftCount + 1];
        auto tmpOut = new char[size + leftCount + 1];
        // 使用 0 填充后面空余
        memset(tmpIn + size, 0, leftCount + 1);
        // 全填充 0
        memset(tmpOut, 0, size + leftCount + 1);
        // 复制数组中的内容
        for (int i = 0; i < size; ++i)
            tmpIn[i] = in[i];
        // 加密
        encryptFile(key, tmpIn, tmpOut, size + leftCount);
        return tmpOut;
    } else {
        auto tmpOut = new char[size + 1];
        memset(tmpOut, 0, size + 1);
        encryptFile(key, in, tmpOut, size);
        return tmpOut;
    }
}

/**
 * 不处理最后一块不能够整除 key 长度的
 */
char* MainWin::partitionEncrypt2(const char *key, char *in, long size)
{
    long keySize = strlen(key);
    if (size % keySize != 0) {
        long leftCount = size - size % keySize;
        // 扩展至可以整除块大小
        auto tmpIn = new char[leftCount];
        auto tmpOut = new char[size];
        // 全填充 0
        // 复制数组中的内容
        for (int i = 0; i < leftCount; ++i) {
            tmpIn[i] = in[i];
        }
        // 加密
        encryptFile(key, tmpIn, tmpOut, leftCount);
        // 向 tmpOut 中追加没有被加密的最后一块
        for (int j = leftCount; j < size; ++j) {
            tmpOut[j] = in[j];
        }
        return tmpOut;
    } else {
        auto tmpOut = new char[size + 1];
        memset(tmpOut, 0, size + 1);
        encryptFile(key, in, tmpOut, size);
        return tmpOut;
    }
}


/**
 * 解密文件，解密后的内容保存在 out 指针所指向的地方+
 * @return
 */
int MainWin::decryptFile(const char *key, char *in, char *out, long size)
{
    int keySize = strlen(key);
    if (keySize != 16 && keySize != 24 && keySize != 32)
    {
        QMessageBox::warning(this,tr("密钥错误"),tr("秘钥长度应该为 16 24 或者 32"));
        return -1;
    }
    CRijndael oRijndael;
    oRijndael.MakeKey(key, CRijndael::sm_chain0, keySize, keySize);
    oRijndael.Decrypt(in, out, size, iMode);
    return 0;
}

/**
 * 因为需要解密的块大小不一定能够整除秘钥大小，所以需要做增长处理
 * @return
 */
char* MainWin::partitionDecrypt(const char *key, char *in, long size)
{
    long keySize = strlen(key);
    if (size % keySize != 0)
    {
        long addCount = keySize - size % keySize;
        auto tmpIn = new char[size + addCount + 1];
        auto tmpOut = new char[size + addCount + 1];
        memset(tmpIn + size, 0, addCount + 1);
        memset(tmpOut, 0, size + addCount + 1);
        // 复制 in 内容到 tmpIn
        for (int i = 0; i < size; ++i) {
            tmpIn[i] = in[i];
        }
        decryptFile(key, tmpIn, tmpOut, size + addCount);
        return tmpOut;
    } else {
        auto tmpOut = new char[size + 1];
        memset(tmpOut, 0, size + 1);
        decryptFile(key, in, tmpOut, size);
        return tmpOut;
    }
}

/**
 * 直接不处理最后一块不能够整除的长度
 */
char* MainWin::partitionDecrypt2(const char *key, char *in, long size)
{
    long keySize = strlen(key);
    if (size % keySize != 0)
    {
        long leftCount = size - size % keySize;
        auto tmpIn = new char[leftCount];
        auto tmpOut = new char[size];
        // 复制 in 内容到 tmpIn
        for (int i = 0; i < leftCount; ++i)
            tmpIn[i] = in[i];
        decryptFile(key, tmpIn, tmpOut, leftCount);
        for (int j = leftCount; j < size; ++j)
            tmpOut[j] = in[j];

        return tmpOut;
    } else {
        auto tmpOut = new char[size + 1];
        memset(tmpOut, 0, size + 1);
        decryptFile(key, in, tmpOut, size);
        return tmpOut;
    }
}

/**
 * @brief 解密函数封装
 * @param fileToDecrypt
 * @param saveDecrypt
 * @param key
 * @return
 */
int MainWin::doDecrypt(string fileToDecrypt, string saveDecrypt, const char *key)
{
    char *in;
    long size = readFile(in, fileToDecrypt);
    auto out = partitionDecrypt2(key, in, size);
    writeFile(out, saveDecrypt, size - 1);
    return 0;
}

/**
 * @brief 加密函数封装
 * @param fileToEncrypt
 * @param saveEncrypt
 * @param key
 * @return
 */
int MainWin::doEncrypt(string fileToEncrypt, string saveEncrypt, const char *key)
{
    char *in;
    long size = readFile(in, fileToEncrypt);      // 读取回来的数据，最后一个字符是 '\0'
    auto out = partitionEncrypt2(key, in, size);
    writeFile(out, saveEncrypt, size - 1);
    return 0;
}

/**
 * 对比2个加密文档
 */
float MainWin::compare(const string &f1, const string &f2)
{
    char * content1;
    char * content2;
    long s1 = readFile(content1, f1);
    long s2 = readFile(content2, f2);
    int m = 0, n = 0;       // n 统计所有 bit 数目, m 统计所有不同 1 的个数
    char tmp;
    for (int i = 0; i < s1 && i < s2; ++i)
    {
        // 异或运算寻找两个二进制不同位的个数
        tmp = content1[i] ^ content2[i];
        // 统计 1 的个数
        for (int j = 0; j < 8; ++j)
        {
            if (tmp & 1)  m += 1;
            tmp >>= 1;
        }
        n += 8;
    }
    return (float)m / n;
}

// 加密
void MainWin::on_Btn_encrypt_clicked()
{
    getKey();   //获取密钥
    ui->statusBar->clearMessage();
    doEncrypt(fileName.toStdString(),saveName.toStdString(),key);
    ui->statusBar->showMessage(tr("加密完成！"));
}

// 解密
void MainWin::on_Btn_decrypt_clicked()
{
    getKey();   //获取密钥
    ui->statusBar->clearMessage();
    doDecrypt(fileName.toStdString(),saveName.toStdString(),key);
    ui->statusBar->showMessage(tr("解密完成！"));
}

/**
 * 文件比对块
 */
// import file1
void MainWin::on_Btn_file1_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("All Files (*.*)"));  //选择路径
    if(fileName.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    }
    ui->lineEdit_file1->setText(fileName);
}

// import file2
void MainWin::on_Btn_file2_clicked()
{
    fileName2 = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("All Files (*.*)"));  //选择路径
    if(fileName2.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    }
    ui->lineEdit_file2->setText(fileName2);
}

// 显示compare组与否
void MainWin::on_rBtn_compare_toggled(bool checked)
{
    if(checked)
    {
        this->maximumHeight();
        ui->groupBox_compare->show();
        ui->label_file1->show();
        ui->label_file2->show();
        ui->lineEdit_file1->show();
        ui->lineEdit_file2->show();
        ui->Btn_compare->show();
        ui->label_change->show();
        ui->label_percentage->show();
    }
    else
    {
        this->minimumHeight();
        ui->groupBox_compare->hide();
        ui->label_file1->hide();
        ui->label_file2->hide();
        ui->lineEdit_file1->hide();
        ui->lineEdit_file2->hide();
        ui->Btn_compare->hide();
        ui->label_change->hide();
        ui->label_percentage->hide();
    }
}

/**
 * @brief 比对开始
 */
void MainWin::on_Btn_compare_clicked()
{
    ui->statusBar->clearMessage();
    float changes = 100 * compare(fileName.toStdString(),fileName2.toStdString());
    QString changesStr = QString("%1%").arg(changes);
    ui->label_percentage->setText(changesStr);
    ui->statusBar->showMessage(tr("比对完成!"));
}
