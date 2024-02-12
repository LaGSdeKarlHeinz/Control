#include "components/DataLabel.h"
#include "MainWindow.h"
#include "../Setup.h"
#include <QFont>

DataLabel::DataLabel(const QString &field, QWidget *parent) : QLabel(parent), field(field)
{
    setObjectName(QString("dataLabel-%1").arg(field));
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    
    setStyleSheet(QString("background: transparent; color: %1;").arg(col::primary));

    QFont curFont = font();
    curFont.setPointSize(15);
    curFont.setBold(false);
    setFont(curFont);

    
    setText("-");
    MainWindow::clientManager->subscribe(field.toStdString(), [this](const QString newText){setText(newText);});
    
}