#ifndef TMSUMANAGE_H
#define TMSUMANAGE_H

#include <QStringList>

class TmsuManage
{
public:
    TmsuManage(QString itemName);
    ~TmsuManage();
    void UpdateTags(QStringList itemTagsNew);
    QStringList dbTags;
    QStringList itemTags;
//    QStringList itemValueTags;

private:
    QString itemName;
};

#endif // TMSUMANAGE_H
