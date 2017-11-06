/***************************************************************************
 *   Copyright (C) 2008 by Bernd Buschinski   *
 *   b.buschinski@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef BFOLDERSCANNER_H
#define BFOLDERSCANNER_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QDir>

class BImageItem
{
public:
    QString image;
    quint64 colorValue;
};

class BImageItemStore
{
public:
    BImageItem* item1;
    BImageItem* item2;
};

class BFolderScanner
{
public:
    BFolderScanner();
    ~BFolderScanner();

    void setRecursive(bool aRecursive);
    void setFollowSymlinks(bool aSymlinks);
    void setRangeCheck(quint64 aRange);

    void appendDir(const QString& aFolder);

    int scan();

private:
    QList<BImageItem*> myList;
    QList<QString> myFolderList;
    QStringList myFilterList;
    quint64 myRangeCheck;

    bool myScanRecursive;
    bool myFollowSymlinks;
    bool myScanRange;
    QDir::Filters myFilterFlags;

    inline void updateFilterFlags();
    inline void createAndInsertHash(const QString& aString);
    inline void compare();
    inline bool compareColorValue(quint64 aColorVal1, quint64 aColorVal2);
    inline QStringList filter();
    inline void scan(const QString& aFile);

};

#endif //BFOLDERSCANNER_H
