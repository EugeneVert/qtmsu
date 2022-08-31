#ifndef TMSUMANAGE_H
#define TMSUMANAGE_H

#include <QMap>
#include <QStringList>

enum ItemTagState {
    OFF = 1 << 0,
    ON = 1 << 1,
    PARTIAL = 3,
};

class TmsuManage
{
public:
    TmsuManage(QStringList itemNames);
    ~TmsuManage();

    //    QStringList itemValueTags;
    QStringList dbTags;
    QMap<QString, uint> itemsTags;
    void UpdateTags(QStringList checked, QStringList unchecked);
    QStringList GetTagValues(const QString &tag);

private:
    QStringList itemNames;
};

#endif // TMSUMANAGE_H
