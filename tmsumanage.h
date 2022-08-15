#ifndef TMSUMANAGE_H
#define TMSUMANAGE_H

#include <QString>
#include <QVector>

class TmsuManage
{
public:
    TmsuManage();
    ~TmsuManage();

private:
    QVector<QString> tags;
    QVector<QString> itemTags;
};

#endif // TMSUMANAGE_H
