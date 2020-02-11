#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    struct Settings;
    Ui::MainWindow *ui;
    void printHelp(void);
    uint8_t readConsoleArg(Settings* param);
    uint8_t readListFiles(const QString dir, QStringList &listFiles);
    int readFile(const char *nameFile);
};

#endif // MAINWINDOW_H
