
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>
#include <QtSvg/QSvgRenderer>
#include <QPainter>

#include "components/ValveControlButton.h"
#include "../Setup.h"

CLickableIcon::CLickableIcon(const QString &text, QWidget *parent) : QLabel(text, parent) {
    setObjectName("refreshButton");
    

    resetStyle();
    QPixmap buttonPixMap;
    // icon from icons8 : https://icones8.fr/icon/123373/mettre-%C3%A0-jour-la-rotation-%C3%A0-gauche
    if (text.endsWith(".svg", Qt::CaseInsensitive)) {
        QSvgRenderer svgRenderer(QString(":/images/prop-diagram-firehorn.svg"));
        if (svgRenderer.isValid()) {
            // Calculate the scaled size while maintaining the aspect ratio
            int scaledWidth = svgRenderer.defaultSize().width();
            int scaledHeight = svgRenderer.defaultSize().height();

            // Calculate the offsets to center the image both horizontally and vertically
            int xOffset = 0; // Center horizontally
            int yOffset = 0; // Center vertically

            // Render the SVG onto a pixmap
            buttonPixMap = QPixmap(scaledWidth, scaledHeight);
            buttonPixMap.fill(Qt::transparent);
            QPainter painter(&buttonPixMap);
            svgRenderer.render(&painter, QRectF(0, 0, scaledWidth, scaledHeight));
        }
    } else {
       buttonPixMap = QPixmap(text);
    }

    
    setScaledContents(false); 
    setFixedHeight(40);
    setFixedWidth(40);
    setPixmap(buttonPixMap);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void CLickableIcon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        setStyleSheet(QString(R"(
            #refreshButton {
                background:transparent;
                border-radius: 10%;
            }
            #refreshButton:hover {
                background: rgba(90, 90, 90, 130);
            }
            
        )"));
        QTimer::singleShot(100,  [this]() {
            this->resetStyle();
        });
        emit clicked();
}

void CLickableIcon::resetStyle() {
    setStyleSheet(QString(R"(
            #refreshButton {
                background:transparent;
                border-radius: 10%;
            }
            #refreshButton:hover {
                background: rgba(90, 90, 90, 90);
            }
            
        )"));
}

ValveControlButton::ValveControlButton(const QString &title, QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background: transparent;");
    
    // Create the title label
    QLabel *titleLabel = new QLabel(title, this);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setStyleSheet(QString("color:%1").arg(col::primary));
    QFont font = titleLabel->font();
    font.setPointSize(10);
    font.setBold(true);
    titleLabel->setFont(font);
    QString str = title;
    str = str.remove(' ');
    str = str.toLower();
    
    toggleButton = new ToggleButton(str, this);
    refreshLabel = new CLickableIcon(":/icons/refresh-icon.png", this);


    // Set up layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(toggleButton);
    buttonsLayout->addWidget(refreshLabel);
    
    mainLayout->addLayout(buttonsLayout);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    setLayout(mainLayout);

    connect(toggleButton, &ToggleButton::toggled, this, &ValveControlButton::valveToggled);
    connect(refreshLabel, &CLickableIcon::clicked, this, &ValveControlButton::refreshClicked);
    refreshLabel->setCursor(Qt::PointingHandCursor); // Change cursor to hand cursor for hover effect
}

QSize ValveControlButton::sizeHint() const
{
    return QSize(120, 60); // Adjust the height to accommodate the title label and buttons
}

bool ValveControlButton::isValveOpen() const
{
    return toggleButton->isChecked();
}



void ValveControlButton::setValveOpen(bool open)
{
    toggleButton->setChecked(open);
}

