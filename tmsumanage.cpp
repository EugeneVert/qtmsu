#include "tmsumanage.h"

#include <QProcess>

TmsuManage::TmsuManage(QStringList itemNames)
    : itemNames(itemNames)
{
    {
        // Get all tags (without values)
        QProcess p;
        p.start("tmsu",
                QStringList() << "tags"
                              << "-1");
        p.waitForFinished();
        dbTags = QString(p.readAllStandardOutput()).split("\n", Qt::SkipEmptyParts);
        auto err = p.readAllStandardError();
        if (!err.isEmpty()) {
            fprintf(stderr, "TMSU database not found\n");
            exit(1);
        }
    }
    {
        // Get item tags (with values)
        QProcess p;
        p.start("tmsu",
                QStringList() << "tags"
                              << "-1"
                              << "-n"
                              << "never" << itemNames);
        p.waitForFinished();

        foreach (const QString &tag, QString(p.readAllStandardOutput()).split("\n")) {
            if (tag == "") {
                continue;
            }
            itemsTags[tag] += 1;
        }
    }
    // Append tags with values to dbTags
    foreach (const auto &tag, itemsTags.keys()) {
        if (tag.contains("=")) {
            dbTags << tag;
        }
    }
}

TmsuManage::~TmsuManage() {}

void TmsuManage::UpdateTags(QStringList checked, QStringList unchecked)
{
    {
        QProcess p;
        p.start("tmsu",
                QStringList() << "tag"
                              << "-t" << checked.join(" ") << itemNames);
        p.waitForFinished();
    }

    QStringList toDel;
    foreach (const auto &i, itemsTags.keys()) {
        if (unchecked.contains(i)) {
            toDel << i;
        }
    }

    {
        QProcess p;
        p.start("tmsu",
                QStringList() << "untag"
                              << "-t" << toDel.join(" ") << itemNames);
        p.waitForFinished();
    }
}

QStringList TmsuManage::GetTagValues(const QString &tag)
{
    QStringList res;
    {
        QProcess p;
        p.start("tmsu",
                QStringList() << "values"
                              << "-1" << tag);
        p.waitForFinished();
        res = QString(p.readAllStandardOutput()).split("\n", Qt::SkipEmptyParts);
    }
    return res;
}
