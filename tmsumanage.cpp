#include "tmsumanage.h"

#include <iostream>
#include <QProcess>

TmsuManage::TmsuManage(QString itemName)
    : itemName(itemName)
{
    {
        // Get all tags (without values)
        QProcess p;
        p.start("tmsu",
                QStringList() << "tags"
                              << "-1");
        p.waitForFinished();
        dbTags = QString(p.readAllStandardOutput()).split("\n", Qt::SkipEmptyParts);
        assert(!dbTags.isEmpty());
    }
    {
        // Get item tags (with values)
        QProcess p;
        p.start("tmsu",
                QStringList() << "tags"
                              << "-n"
                              << "never" << itemName);
        p.waitForFinished();
        itemTags = QString(p.readAllStandardOutput()).split("\n", Qt::SkipEmptyParts);
    }
    // Append tags with values to dbTags
    for (const QString &tag : qAsConst(itemTags)) {
        if (tag.contains("=")) {
            dbTags << tag;
        }
    }
}

TmsuManage::~TmsuManage() {}

void TmsuManage::UpdateTags(QStringList itemTagsNew)
{
    QStringList toDel;
    QStringList toAdd;
    bool itemIsOld, itemIsNew, itemToDelete;

    for (const QString &ln : itemTagsNew) {
        if (!itemTags.contains(ln)) {
            toAdd << ln;
        }
    }
    {
        QProcess p;
        p.start("tmsu",
                QStringList() << "tag"
                              << "-t" << toAdd.join(" ") << itemName);
        p.waitForFinished();
    }

    for (const QString &l : qAsConst(itemTags)) {
        if (!itemTagsNew.contains(l)) {
            toDel << l;
        }
    }
    {
        QProcess p;
        p.start("tmsu",
                QStringList() << "untag"
                              << "-t" << toDel.join(" ") << itemName);
        p.waitForFinished();
    }
}
