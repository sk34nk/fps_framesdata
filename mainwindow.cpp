#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <istream>
#include <string>
#include "./gzstream/gzstream.h"

QTextStream cout(stdout);

struct MainWindow::Settings
{
    QString pathInput;
    QString pathOutput;
    uint8_t startEpisode;
    uint8_t stopEpisode;
    //QString seasonName;
};

void MainWindow::printHelp(void)
{
    std::cout << "usage: fps_framesdata [options]" << std::endl;
    std::cout << "General fps_framesdata options:" << std::endl;
    std::cout << "-d <Path> (--dir <Path>)" << std::endl;
    std::cout << "      Путь к каталогу с набором *.info.yaml.gz файлов" << std::endl;
    std::cout << "-s <number episode> (--start <number episode>)" << std::endl;
    std::cout << "      Номер эпизода, с которого начинается подсчёт FPS."
                 " Если не указан, то FPS подсчитывается с первого в директории" << std::endl;
    std::cout << "-e <number episode> (--end <number episode>) " << std::endl;
    std::cout << "      Номер эпизода, на котором заканчивается подсчёт FPS."
                 " Если не указан, то FPS подсчитывается до последнего в директории;" << std::endl;
    std::cout << "-o <Patch output> (--output <Patch output>)" << std::endl;
    std::cout << "      Путь к файлу .csv с таблицей, содержащей отчёт о FPS для разных устройств."
                 " Первая колонка – имя устройства (соответствует шапке), вторая колонка –значение"
                 " FPS для данного устройства. Если не задано, то вывод в консоль." << std::endl;
    /*std::cout << "-sn <Season name> (--season <Season name>)" << std::endl;
    std::cout << "      Название совокупности проездов" << std::endl;*/
    std::cout << "-h (—help)" << std::endl;
    std::cout << "      Справка об использовании программы." << std::endl;
}

uint8_t MainWindow::readConsoleArg(Settings* param)
{
    QStringList arguments = qApp->arguments();
    QString option;

    if(arguments.count() > 1)
    {
        for (int i = 1; i < arguments.count(); i++)
        {
            option = arguments[i];
            if(arguments[i] == "--help" || arguments[i] == "-h")
            {
                printHelp();
            }
            else if(arguments[i] == "--dir" || arguments[i] == "-d")
            {
                ui->pathInput->setPlainText(arguments[++i]);
                param->pathInput = arguments[i];
            }
            else if(arguments[i] == "--output" || arguments[i] == "-o")
            {
                ui->pathOutput->setPlainText(arguments[++i]);
                param->pathOutput = arguments[i];
            }
            else if(arguments[i] == "--start" || arguments[i] == "-s")
            {
                ui->startEpisode->setPlainText(arguments[++i]);
                param->startEpisode = arguments[i].toInt();
            }
            else if(arguments[i] == "--end" || arguments[i] == "-e")
            {
                ui->stopEpisode->setPlainText(arguments[++i]);
                param->stopEpisode = arguments[i].toInt();
            }
            /*else if(arguments[i] == "--season" || arguments[i] == "-sn")
            {
                ui->seasonName->setPlainText(arguments[++i]);
                param->seasonName = arguments[i];
            }*/
        }
        return 1;
    }
    else
    {
        printHelp();
        return 0;
    }
}

uint8_t MainWindow::readListFiles(const QString dir, QStringList &listFiles)
{
    QApplication::processEvents();
    QDir inputDir;

    if (inputDir.cd(dir) != false)
    {
        listFiles = inputDir.entryList(QStringList() << "*.gz", QDir::Files);
    }
    else
    {
        cout << "Directory not exists" << endl;
        return 0;
    }
    return 1;
}

int MainWindow::readFile(const char *nameFile)
{
    igzstream in(nameFile);
    std::string line;
    bool trueYaml = false;
    while (std::getline(in, line))
    {
        std::cout << line << std::endl;
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Settings varsSettings;
    QStringList listFiles;

    if(readConsoleArg(&varsSettings) != 0)
    {
        if (readListFiles(varsSettings.pathInput, listFiles) != 0)
        {
            for(uint16_t i = varsSettings.startEpisode - 1; i <= listFiles.count() - 1; i++)
            {
                std::string name = varsSettings.pathInput.toStdString() + listFiles[i].toStdString();

                std::cout << name << std::endl;
                const char *nameFile = name.c_str();
                try
                {
                    readFile(nameFile);
                }
                catch (...)
                {
                    std::cout << "Bad file: " << nameFile << std::endl;
                }
            }
        }
    }
    else
    {
        QMessageBox::about(this, "Settings", "Enter parameters");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
