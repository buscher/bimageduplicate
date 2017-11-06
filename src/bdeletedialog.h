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

#ifndef BDELETEDIALOG_H
#define BDELETEDIALOG_H

#include "ui_bdeletedialog.h"

#include <QString>
#include <QDialog>

class BDeleteDialog : public QDialog, public Ui::BDeleteDialog
{
Q_OBJECT

public:
    BDeleteDialog( const QString& aPixOne, const QString& aPixTwo);
    int deleted();
    int ignored();

protected slots:
    void deteleOne();
    void deteleTwo();
    void ignoreOne();
    void ignoreTwo();

private:
    QString myPixOne;
    QString myPixTwo;
    int myDeleted;
    int myIgnored;
};

#endif //BDELETEDIALOG_H
