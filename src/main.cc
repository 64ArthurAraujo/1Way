/*
 Copyright (c) 2023 Arthur Araujo

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "QMLShell.h"
#include <QDesktopServices>

int main(int argc, char const *argv[])
{
    setenv("QT_QPA_PLATFORM", "mirserver", 1 /* overwrite */);
    qInfo("Using mirserver qt platform");

    QMLShell *shell = new QMLShell(argc, (char **)argv);

    int result = shell->exec();

    shell->destroyResources();

    delete shell;

    return result;
}
