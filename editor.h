#pragma once
#include <QApplication>
#include <QMainWindow>

#include "types.h"

class Editor : public QMainWindow {
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = nullptr);

private:
    Session session{};

private slots:
    void onOpen();
};
