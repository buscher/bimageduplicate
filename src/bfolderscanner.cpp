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

#include "bfolderscanner.h"

#include "bdeletedialog.h"

#include <QDebug>
#include <QDir>
#include <QImage>
#include <QImageReader>
#include <QByteArray>
#include <QColor>

BFolderScanner::BFolderScanner()
{
    myScanRecursive = false;
    myFollowSymlinks = false;
    myScanRange = false;
    myRangeCheck = 0;
    myFilterList = filter();
    updateFilterFlags();
}

BFolderScanner::~BFolderScanner()
{
    while (!myList.isEmpty())
        delete myList.takeFirst();
}

void BFolderScanner::createAndInsertHash(const QString& aString)
{
    qWarning() << aString;

    //slow?
    for (int i = 0; i < myList.size(); ++i)
    {
        if (myList.at(i)->image == aString)
        {
            qWarning() << "skipping, image already list: " << aString;
            return;
        }
    }

    QImage tImage(aString);
    tImage = tImage.scaled( 800, 600, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    quint64 tColor = 0;
    for (int i = 0; i < tImage.width(); ++i)
    {
        for (int j = 0; j < tImage.height(); ++j)
        {
            tColor += QColor(tImage.pixel(i,j)).red();
            tColor += QColor(tImage.pixel(i,j)).blue();
        }
    }
    qWarning() << "tColor: " << QString::number(tColor);

    BImageItem* tItem = new BImageItem();
    tItem->image = aString;
    tItem->colorValue = tColor;
    myList.append( tItem );
}

void BFolderScanner::compare()
{
    QList<BImageItemStore> tResult;
    for (int i = 0; i < myList.size(); ++i)
    {
        for (int j = 0; j < myList.size(); ++j)
        {
            if (i==j) continue;
            if (compareColorValue(myList.at(i)->colorValue, myList.at(j)->colorValue))
            {
                BImageItemStore t;
                t.item1 = myList.at(i);
                t.item2 = myList.at(j);
                tResult.append( t );
//                 qWarning("old: same pic: "+ myList.at(i)->image.toAscii() + " " + myList.at(j)->image.toAscii() );
            }
        }
    }

//! dont clean it, we need it for "same" deletion
//     //clean list
//     for (int i = 0; i < tResult.size(); ++i)
//     {
//         for (int j = 0; j < tResult.size(); ++j)
//         {
//             if (i==j) continue;
//             if (tResult.at(i).item1 == tResult.at(j).item2 && tResult.at(i).item2 == tResult.at(j).item1)
//             {
//                 tResult.removeAt( j );
//                 i--;
//                 break;
//             }
//         }
//     }

    for (int i = 0; i < tResult.size(); ++i)
    {
        qWarning() << "same pic: " << tResult.at(i).item1->image << " " << tResult.at(i).item2->image;
        BDeleteDialog t(tResult.at(i).item1->image, tResult.at(i).item2->image);
        int tr = t.exec();
        if (tr == QDialog::Accepted)
        {
            QString Item;
            if (t.deleted() == 1 || t.ignored() == 1)
                Item = tResult.at(i).item1->image;
            else if (t.deleted() == 2 || t.ignored() == 2)
                Item = tResult.at(i).item2->image;

            for (int x = i+1; x < tResult.size(); ++x)
            {
                if (tResult.at(x).item1->image == Item ||
                    tResult.at(x).item2->image == Item)
                {
                    tResult.removeAt(x);
                    --x;
                }
            }
        }
    }
}

QStringList BFolderScanner::filter()
{
    QStringList tFilter;
    for (int i = 0; i < QImageReader::supportedImageFormats().size(); ++i)
    {
        tFilter << "*."+QString(QImageReader::supportedImageFormats().at(i)).toLower();
        tFilter << "*."+QString(QImageReader::supportedImageFormats().at(i)).toUpper();
        qWarning() << "adding filter: *." << QImageReader::supportedImageFormats().at(i);
    }
    return tFilter;
}

void BFolderScanner::setRecursive(bool aRecursive)
{
    myScanRecursive = aRecursive;
    updateFilterFlags();
}

void BFolderScanner::setFollowSymlinks(bool aSymlinks)
{
    myFollowSymlinks = aSymlinks;
    updateFilterFlags();
}

void BFolderScanner::appendDir(const QString & aFolder)
{
    myFolderList.append(aFolder);
}

int BFolderScanner::scan()
{
    for (int i  = 0; i < myFolderList.size(); ++i)
    {
        scan(myFolderList.at(i));
    }
    compare();

    return 0;
}

void BFolderScanner::scan(const QString& aFile)
{
    QFileInfo tFileInfo(aFile);
    if (tFileInfo.isSymLink())
    {
        if (myFollowSymlinks && QFile::exists(tFileInfo.symLinkTarget()))
            scan(tFileInfo.symLinkTarget());
        return;
    }

    if (tFileInfo.isDir())
    {
        QDir tDir(aFile);
        QStringList tList = tDir.entryList(myFilterList, myFilterFlags);
        for (int j = 0; j < tList.size(); ++j)
        {
            scan(tDir.absolutePath() + "/" + tList.at(j));
        }
        return;
    }

    createAndInsertHash(aFile);
}

void BFolderScanner::updateFilterFlags()
{
    myFilterFlags = QDir::Files|QDir::NoDotAndDotDot|QDir::Dirs|QDir::Readable;
    if (myScanRecursive)
        myFilterFlags |= QDir::AllDirs;
    if (!myFollowSymlinks)
        myFilterFlags |= QDir::NoSymLinks;
}

bool BFolderScanner::compareColorValue(quint64 aColorVal1, quint64 aColorVal2)
{
    if (myScanRange)
    {
        if (aColorVal1 > aColorVal2)
            return (aColorVal2+(myRangeCheck/2) >= aColorVal1);
        else
            return (aColorVal1+(myRangeCheck/2) >= aColorVal2);
    }
    else
    {
        return (aColorVal1 == aColorVal2);
    }
    return false;
}

void BFolderScanner::setRangeCheck(quint64 aRange)
{
    myRangeCheck = aRange;
    myScanRange = true;
}
