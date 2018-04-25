#include "widget.h"
#include <QApplication>

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDate>

//--------------------------------------------------------------------------------------------------------------------------------------------
QFile*  gTmpFile    = NULL;
bool    gLogMode    = false;
QString gStartDir;
QString gLogFileName;

//--------------------------------------------------------------------------------------------------------------------------------------------
void crashMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    const char * msg = str.toStdString().c_str();

    if( gTmpFile == NULL ){
        gTmpFile = new QFile(gLogFileName);
    }

    gTmpFile->open(QIODevice::Append | QIODevice::Text);

    QTextStream out(gTmpFile);
    out << "[" << QDateTime::currentMSecsSinceEpoch() << "] " << str << endl;

    gTmpFile->close();

    Q_UNUSED(type);
    Q_UNUSED(msg);

}
//--------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList args = QCoreApplication::arguments();

    if(args.count()){

        gStartDir = args.at(0);

        for(int i=1;i<args.count();i++){

            if(args.at(i).contains("-log")){

                gLogMode        = true;
                gLogFileName    = "/tmp/helloworld.log";

                qInstallMessageHandler(crashMessageOutput);

                if( (i+1) < args.count()){
                    gLogFileName = args.at(i+1);
                }
            }
        }
    }


    QCoreApplication::setOrganizationName("Giorgio Marinangleli Inc.");
    QCoreApplication::setOrganizationDomain("https://giorgiomarinangeli.wordpress.com/");
    QCoreApplication::setApplicationName("QtHelloWorld");


    Widget w;
    w.show();

    return a.exec();
}
