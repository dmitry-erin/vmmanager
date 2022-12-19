#include "rootcontext.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <QDebug>

/*
    Now there is only one way to retrieve appVM's info: using "lsvm" command,
    which provides us with names and statuses of appVM's.
*/

RootContext::RootContext()
{   
    updateModel();
}

void RootContext::updateModel()
{
    if(mVMDataModel.rowCount(QModelIndex()) > 0)
        mVMDataModel.clear();

    //exec lsvm command
    /*QString vmInfo =*/ execCommand("ls");//ls for test

    //parse the execution result and add to the model
//    QTextStream stream (&vmInfo, QIODevice::ReadOnly);
//    while(!stream.atEnd()) {
//        QString temp;
//        stream >> temp;
//        qDebug() << temp;
//    }

    //
    mVMDataModel.addData(Parameter("VM1", "runnig"));
    mVMDataModel.addData(Parameter("VM2", "off"));
    mVMDataModel.addData(Parameter("VM3", "off"));
}

QString RootContext::execCommand(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    //qDebug() << QString::fromStdString(result);

    return QString::fromStdString(result);
}
