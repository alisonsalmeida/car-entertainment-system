#ifndef BUTTON_H
#define BUTTON_H
#include <QFrame>
#include <QLabel>

class Button: public QFrame
{
    Q_OBJECT
public:
    
    explicit Button(unsigned int index, QString icon_name, QWidget *parent = nullptr);
    void select(bool value);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *e) override {
        emit onClick(this->_index);
    };

signals:
    void onClick(unsigned int index);
    
private:
    unsigned int _index;
    bool _selected;
    QString _icon_name;
    QLabel *_icon;
};

#endif
