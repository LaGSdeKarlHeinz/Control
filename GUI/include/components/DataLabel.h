

#include <QLabel>

/**
 * @brief The DataLabel class is a class that thisplay a QLbael as well as it connects to the field sepcified in constructor
 */
class DataLabel : public QLabel
{
    Q_OBJECT

public:
    DataLabel(const QString &field, QWidget *parent = nullptr);
    virtual ~DataLabel() {};
private:
    QString field;

};