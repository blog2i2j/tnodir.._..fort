#include "pushbutton.h"

#include <QMouseEvent>

PushButton::PushButton(QWidget *parent) : QPushButton(parent) { }

PushButton::PushButton(const QIcon &icon, const QString &text, QWidget *parent) :
    QPushButton(icon, text, parent)
{
}

void PushButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);

    m_mousePressed = true;
}

void PushButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);

    if (!m_mousePressed)
        return;

    m_mousePressed = false;

    if (e->button() == Qt::RightButton) {
        onRightClicked();
    }
}

void PushButton::onRightClicked()
{
    if (menu()) {
        showMenu();
    }
}
