#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])    //argc命令行变量的数量 argv命令行变量的数组
{
    QApplication a(argc, argv);     //a为应用程序对象，有且仅有一个

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "2100810224_QtAPP_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;           //窗口对象，继承自QMainWindow，默认不显示，调用show()显示
    w.show();
    return a.exec();        //让程序对象进入消息循环，类似 while()，并阻塞代码
}
