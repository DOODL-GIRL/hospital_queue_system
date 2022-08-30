#include "widget.h"

#include <QApplication>
#include <QStyleFactory>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* 设置全局风格 */
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    //QApplication::setStyle(QStyleFactory::create("WindowsXP"));
    //QApplication::setStyle(QStyleFactory::create("WindowsVista"));

    //qt 自带的  style
    //qApp->setStyle(QStyleFactory::create("Fusion"));
    //注释下面的代码则为白色界面
//    QPalette palette;
//    palette.setColor(QPalette::Window, QColor(53, 53, 53));
//    palette.setColor(QPalette::WindowText, Qt::white);
//    palette.setColor(QPalette::Base, QColor(15, 15, 15));
//    palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
//    palette.setColor(QPalette::ToolTipBase, Qt::white);
//    palette.setColor(QPalette::ToolTipText, Qt::white);
//    palette.setColor(QPalette::Text, Qt::white);
//    palette.setColor(QPalette::Button, QColor(53, 53, 53));
//    palette.setColor(QPalette::ButtonText, Qt::white);
//    palette.setColor(QPalette::BrightText, Qt::red);
//    //palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter()); //紫色
//    palette.setColor(QPalette::Highlight, QColor(161, 65, 13).lighter());//橙色
//    palette.setColor(QPalette::HighlightedText, Qt::black);
//    qApp->setPalette(palette);



    Widget w;
    w.show();

    return a.exec();
}
