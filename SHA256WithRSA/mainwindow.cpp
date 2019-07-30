#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <rsacrypto.h>
#include <qdebug.h>
#include <QDateTime>
#include <iostream>
#include <QUrlQuery>
#include <OpenSSL_Base64.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonObject>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const std::string & _publicKey =
            "-----BEGIN PUBLIC KEY-----\n"\
            "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAmn+smNM65ZVVY4uT0SD1\n"\
            "CXKJeSb9RCDg73Mr+OJJlIW547hINtQI1eDgcQprRbDT6nVw060W910AU30Npgdr\n"\
            "L0W69u16iEaLtZ1UedCc6WS2zqJHhzRrTuLTaBG+f6XNfRpZREwY6pfR4O4u4FTG\n"\
            "qgWQPB3zA1vr8C/u6aYhnFI53x9aUy5Cr+ohgnm/Fepsv5wrBEUlcwZ/DXvZ6JoA\n"\
            "zLsypQbQ8LtVBGYtVcf5ox4G3xYC7lqZ44/aJN4UJGhZEFacWuJZIs4kJPORu3TR\n"\
            "GEdhqS0CJbt05w73LSowwio/0I6HJel57Pw4AKSBJUq28j3D6nRuFJtp3Wd9UMom\n"\
            "xQIDAQAB"\
            "-----END PUBLIC KEY-----\n";



    //开发者私钥，由开发者自行生成，用于解密回调数据，请将此私钥修改为开发者自已的私钥。 --------私钥使用 pkcs#1
    const std::string & _privateKey =
            "-----BEGIN PRIVATE KEY-----\n"\
            "MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCaf6yY0zrllVVj\n"\
            "i5PRIPUJcol5Jv1EIODvcyv44kmUhbnjuEg21AjV4OBxCmtFsNPqdXDTrRb3XQBT\n"\
            "fQ2mB2svRbr27XqIRou1nVR50JzpZLbOokeHNGtO4tNoEb5/pc19GllETBjql9Hg\n"\
            "7i7gVMaqBZA8HfMDW+vwL+7ppiGcUjnfH1pTLkKv6iGCeb8V6my/nCsERSVzBn8N\n"\
            "e9nomgDMuzKlBtDwu1UEZi1Vx/mjHgbfFgLuWpnjj9ok3hQkaFkQVpxa4lkiziQk\n"\
            "85G7dNEYR2GpLQIlu3TnDvctKjDCKj/Qjocl6Xns/DgApIElSrbyPcPqdG4Um2nd\n"\
            "Z31QyibFAgMBAAECggEAP3p7wOLxDQlZZygfGMrQwwvzXfreDpLvuJJ6m6zmDIcR\n"\
            "RHYf/Z8K7k2SCf/86UppF6kfLWmtyP7GNodoBzJ/IJIm6nPSZ5GMr5cv8Uj8X4zI\n"\
            "64eTmgK4oFXkBJtdyPanwmIEEWKuzhyI2EEks3lBkvPsOjcX9OZcv3gCUq+2mZIq\n"\
            "z2fYaNzeZBBIAF3qtSjQ9TZ29tTdrZ5qz8KeiuvUHc5bwZUUrn6X+wp5saecIyQd\n"\
            "6HWFHiM3cJ+XHB6yCTYMEMrm3PadOSTKxOpm+iu7GfU2J6Z9xwEu9aKQwsCqDTcy\n"\
            "n+Lw86sSUj++xs0HRcl9iz8ASOmQ13JrRG4p9Sah4QKBgQD+sORju7YBqwQLDcc8\n"\
            "j0nCDAfCvqIMQGu05u7pehxVsnHaP7KQzgCQT8ddFSej8fI7RJqMer6LkDp5Acxp\n"\
            "/IUw6/PoUROzhL1n7BZBgvRkrizYlB7qLFeVkA1Erx+yk2l5fVjXxHhc6+5Gxdx5\n"\
            "jYHpwn4b1qNHE42j5dBECbKw2QKBgQCbSvRuYo9CSzKyLWnHeKWlv3qLzCzG0qNh\n"\
            "S00dVDMyvsQMmHhFT8WhbYfiefrzH7pMTmbWDLNcsdz5NQoYcKeQKWpIpXucAgr0\n"\
            "qNkX2040NgBVJVNBHddPG6rTiUsf5qhcnSRHaewKk342YTOmeo/BV9Nl3sSw1tR1\n"\
            "Cx1H6AExzQKBgQDinPIZ60MeaNPIIhJMSBIQnjOpi4UT8Z3j8DZTd1sOxR+YWWTA\n"\
            "gwrtXI6+u7vxm600Hu6EYBJ6i3H7iSYgh5ba2JbE9p7Y9BqzBNUopSRfELrGWcTI\n"\
            "B3xGj02+9zL06UTH3EfYc+/Efggc4KAzZz1YiL08d9X/v94fHrQYVaiwwQKBgDGH\n"\
            "07SNfRHw+Cd6cp2rrnHSQ9zo73Mu5et3YA41t+q8i71UuC+rROa7D7c9nrwC56HE\n"\
            "8+nbvS2YkVlvAFxROjCx9PNczLMyt5nXbP699RCUFMETmZ1QTkcuFOtJhAuVvydi\n"\
            "+5pHf4DUEFJ56EZ2GvnY8FUym1un+bWnKNyxdAgVAoGBAI9/SYJQImBp82dEp6FX\n"\
            "J5+Zaih08xeMjjndpJCDxN8/S7mr07nxarw+nYkkIJgQuQNvpMUOzS/aTUTEWBQQ\n"\
            "Yi2lTfwqeSWjFtabX8azmYiCBBd3+80iu0hlob9IgHsoGFcWqjSs8ZOmmZn4ZqvR\n"\
            "DC8xnw9sutAKV0rV4lGOq9oc"\
            "-----END PRIVATE KEY-----\n";


    //获得时间戳
    //===========================================================================================
    QDateTime dateTime = QDateTime::currentDateTime();
    qint64 epochTime = dateTime.toMSecsSinceEpoch();
    QString s = QString::number(epochTime, 10);
    QByteArray ba=s.toLatin1();
    char* temp=ba.data();
    char g[17];
    char *timestamp= strncpy(g,temp,17);
    string format = "JSON";
    string sign_type = "RSA2";
    string deviceType = "ios";
    //设置请求头
    //===========================================================================================
    // 基本 URL
    QString baseUrl = "http://XXX.com";
    QUrl url(baseUrl);
    // key-value 对
    QUrlQuery query;
    query.addQueryItem("format","JSON");
    query.addQueryItem("charset","UTF-8");
    query.addQueryItem("timestamp",timestamp);
    query.addQueryItem("version", "1.0");
    query.addQueryItem("appVersion","1.0");
    query.addQueryItem("sign_type", "RSA2");
    query.addQueryItem("encrypt_key",timestamp);
    query.addQueryItem("deviceType","ios");
    QString data = "{\"accountName\":\"Test\"}";
    qDebug() <<"data:\n"<<data<<endl;
    string datas = data.toStdString();
    cout<<"datas:\n"<<datas<<endl;
    AES aes_128;//自行寻找AES加密
    string data_AES= aes_128.EncryptionAES(datas,timestamp);
    data = QString::fromStdString(data_AES);
    qDebug() <<"需要进行AES加密的content字符串:\n"<<data<<endl;
    QByteArray postData;
    postData.append("content="+data);

    //参考支付宝的方式
    //这里把content加入到sign中
    QString timedata ="appVersion=1.0&charset=UTF-8&content=";
    timedata.append(data);
    //timedata.append("&deviceType=ios");
    timedata.append("&deviceType=ios&encrypt_key=");
    timedata.append(timestamp);
    timedata.append("&format=JSON&sign_type=RSA2&timestamp=");
    timedata.append(timestamp);
    timedata.append("&version=1.0");
    qDebug() << "需要进行RSA2加密的Sign字符串:\n"<<timedata<<endl;

    char* ptr;
    QByteArray ptrba;
    ptrba = timedata.toLatin1();
    ptr = ptrba.data();
    qDebug() << "RSA2加密前字符串:\n"<<ptr<<endl;
    std::string _message = ptr;
    //初始化RSA算法
    RSACrypto* _RSACrypto = new RSACrypto(_publicKey, _privateKey);
    _RSACrypto->InitRsa();
    std::string _utf8Message;
    std::string _encrypted;
    std::string _encryptedBase64;
    std::string verify_data;


    //私钥签名
    //===========================================================================================
    std::string _sign;
    //1、 _sign = RSA私钥签名（消息体）
    bool success = _RSACrypto->SignByPrivateKey(_message, _sign);
    //2、 base64Str =   base64编码(_sign )
    std::string _signBase64 = OpenSSL_Base64Encode(_sign.data(), _sign.length(), false);
    //3、UrlEncode编码（_signBase64 ）
    QByteArray baba = QString::fromStdString(_signBase64).toUtf8();
    QByteArray byteArrayPercentEncoded = baba.toPercentEncoding();
    qDebug()<<"RSA2加密后字符串:\n"<<byteArrayPercentEncoded<<endl;
    query.addQueryItem("sign",byteArrayPercentEncoded);
    url.setQuery(query);
    //设置request
    //===========================================================================================
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");  //上面语句固定这么写，要不然会报错“contest—type is missing”
    request.setUrl(QUrl(url));
    qDebug() <<"URL最终发送字符串:\n"<<url<<endl;

    //manager发送请求，并接收reply，委托给slot处理
    manager.post(request,postData);
    connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishRequest(QNetworkReply*)));
}
