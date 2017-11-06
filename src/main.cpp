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

#include <QApplication>

#include <QDebug>
#include <QString>
#include <QDir>

#include <stdlib.h>

#include "bfolderscanner.h"

void parseOption(BFolderScanner *aScanner, char** aAgrv, int *aIndex, int aArgc)
{
    QString tArgv = QString(aAgrv[*aIndex]);
    if (tArgv == "-R" || tArgv == "--recursive")
        aScanner->setRecursive(true);
    else if (tArgv == "-f" || tArgv == "--follow-symlinks")
        aScanner->setFollowSymlinks(true);
#if 0
    else if (tArgv == "-r" || tArgv == "--range-check")
    {
        if((*aIndex)+1 > aArgc)
        {
            qWarning("missing argument from range check");
            exit(1);
        }
        bool ok = false;
        quint64 tVal = QString(aAgrv[(*aIndex)+1]).toULongLong(&ok);
        if (ok)
        {
            aScanner->setRangeCheck(tVal);
            ++(*aIndex);
        }
    }
#endif
    else if (tArgv == "-h" || tArgv == "--help")
    {
        qWarning("-R --recursive\t\tScan folder recursive");
#if 0
        qWarning("-r --range-check value\t\tenables a range checking, normal values goes from 20000 to 500000, default 150000");
#endif
        qWarning("-f --follow-symlinks\tfollow symlinks");
        qWarning("-h --help\tprints this help and exit");
        exit(0);
    }
    else
        qWarning() << "unknown option: " << tArgv;
}

int main(int argc, char** argv)
{
    QApplication tApp(argc,argv);

    BFolderScanner tScanner;
    for (int i = 1; i < argc; ++i)
    {
        QString tArgv = argv[i];
        if (tArgv.startsWith('-'))
        {
            parseOption(&tScanner, argv, &i, argc);
        }
        else if (QDir(tArgv).exists())
        {
            tScanner.appendDir(tArgv);
        }
        else
        {
            qWarning() << "unknown arg or non-existing folder: " << tArgv;
        }
    }
    return tScanner.scan();
}
