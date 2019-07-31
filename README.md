# SHA256WithRSA
<a href="https://996.icu"><img src="https://img.shields.io/badge/link-996.icu-red.svg" alt="996.icu" /></a>
C++/Qt 的SHA256WithRSA私钥签名

鸣谢：https://www.jianshu.com/p/8d363b2898d7 Replay923提供的源码

验证支持为支付宝的RSA验签平台：https://docs.open.alipay.com/291/105971

作者提供的源码为SHA1摘要，即EVP_sha1()，我需要的为SHA256WithRSA，故使用EVP_sha256()

由于上传的限制，openssl的头文件我进行的压缩打包，解压使用即可，库使用的是macOS支持的dylib格式，需要libcrypto.3.dylib与libssl.3.dylib支持
其他平台自行使用openssl源码进行make make install即可。

mainWindow函数中使用的是RSA2私钥签名，具体其他函数在rsacrypto文件中。

AES算法为我个人需要加密，视具体项目进行增改。

C++初学者，如有不妥请见谅
联系方式QQ：1019832705@qq.com
