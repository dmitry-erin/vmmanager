#ifndef ROOTCONTEXT_H
#define ROOTCONTEXT_H

#include <QObject>
#include "vmdatamodel.h"

class RootContext : public QObject
{
    Q_OBJECT
public:
    RootContext();

    VMDataModel * getVMDataModel() {return &mVMDataModel;}

    Q_INVOKABLE void updateModel();

private:
    VMDataModel mVMDataModel;
    QString execCommand(const char * cmd);
};

#endif // ROOTCONTEXT_H
