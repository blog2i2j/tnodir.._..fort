#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>

class ToolButton : public QToolButton
{
    Q_OBJECT

public:
    explicit ToolButton(QWidget *parent = nullptr);

protected:
    bool mousePressed() const { return m_mousePressed; }

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    void onRightClicked();

private:
    bool m_mousePressed : 1 = false;
};

#endif // TOOLBUTTON_H
