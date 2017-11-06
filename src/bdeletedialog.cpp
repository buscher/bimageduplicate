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

#include "bdeletedialog.h"

#include <QFile>

BDeleteDialog::BDeleteDialog(const QString & aPixOne, const QString & aPixTwo)
{
    setupUi(this);
    QPixmap tOnePix(aPixOne);
    myPixOneLabel->setPixmap( tOnePix.scaled(400,300,Qt::KeepAspectRatio));
    myOneName->setText(aPixOne);
    mySizeOne->setText( QString::number(tOnePix.width()) + "x" + QString::number(tOnePix.height()));

    QPixmap tTwoPix(aPixTwo);
    myPixTwoLabel->setPixmap( tTwoPix.scaled(400,300,Qt::KeepAspectRatio));
    myTwoName->setText(aPixTwo);
    mySizeTwo->setText( QString::number(tTwoPix.width()) + "x" + QString::number(tTwoPix.height()));
    myPixOne = aPixOne;
    myPixTwo = aPixTwo;
    myDeleted = 0;
    myIgnored = 0;

    connect(myDeleteOne, SIGNAL(clicked()), this, SLOT(deteleOne()));
    connect(myDeleteTwo, SIGNAL(clicked()), this, SLOT(deteleTwo()));
    connect(myIgnoreOne, SIGNAL(clicked()), this, SLOT(ignoreOne()));
    connect(myIgnoreTwo, SIGNAL(clicked()), this, SLOT(ignoreTwo()));
}

void BDeleteDialog::deteleOne()
{
    QFile::remove( myPixOne );
    myDeleted = 1;
    accept();
}

void BDeleteDialog::deteleTwo()
{
    QFile::remove( myPixTwo );
    myDeleted = 2;
    accept();
}

int BDeleteDialog::deleted()
{
    return myDeleted;
}

void BDeleteDialog::ignoreOne()
{
    myIgnored = 1;
    accept();
}

void BDeleteDialog::ignoreTwo()
{
    myIgnored = 2;
    accept();
}

int BDeleteDialog::ignored()
{
    return myIgnored;
}
