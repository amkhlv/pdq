#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QtXml>

class Config
{
public:
    Config();
    bool invert;
    int dpi;
private:
    QDomDocument doc;
};

#endif // CONFIG_H
