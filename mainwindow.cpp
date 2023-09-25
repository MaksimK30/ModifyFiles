#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Установка размеров необходимым элементам
    this->setMinimumSize(500, 500);
    selectInputFolderBtn->setFixedSize(25, 25);
    selectOutputFolderBtn->setFixedSize(25, 25);

    //Настройка виджета ввода исходного пути
    inputFileLayout->addWidget(inputLbl);
    inputFileLayout->addWidget(inputFileEdt);
    inputFileLayout->addWidget(selectInputFolderBtn);
    inputFileLayout->setAlignment(Qt::AlignLeft);
    inputFileWgt->setLayout(inputFileLayout);

    //Настройка виджета вывода исходного пути
    outputFileLayout->addWidget(outputLbl);
    outputFileLayout->addWidget(outputFileEdt);
    outputFileLayout->addWidget(selectOutputFolderBtn);
    outputFileLayout->setAlignment(Qt::AlignLeft);
    outputFileWgt->setLayout(outputFileLayout);

    //Настройка виджета ввода маски файлов
    maskLayout->addWidget(maskLbl);
    maskLayout->addWidget(maskEdt);
    maskLayout->setAlignment(Qt::AlignLeft);
    maskWgt->setLayout(maskLayout);

    //Настройка виджета с чекбоксом перезаписи при повторе имени
    rewriteLayout->addWidget(rewriteLbl);
    rewriteLayout->addWidget(rewriteCB);
    rewriteLayout->setAlignment(Qt::AlignLeft);
    rewriteWgt->setLayout(rewriteLayout);

    //Настройка виджета с чекбоксом удаления исходных файлов
    deleteBaseLayout->addWidget(deleteBaseLbl);
    deleteBaseLayout->addWidget(deleteBaseCB);
    deleteBaseLayout->setAlignment(Qt::AlignLeft);
    deleteBaseWgt->setLayout(deleteBaseLayout);

    //Настройка виджета с чекбоксом обхода вложенных папок
    searchInAttachedLayout->addWidget(searchInAttachedLbl);
    searchInAttachedLayout->addWidget(searchInAttachedCB);
    searchInAttachedLayout->setAlignment(Qt::AlignLeft);
    searchInAttachedWgt->setLayout(searchInAttachedLayout);

    //Настройка виджета ввода строки-ключа шифрования
    keyEdt->setMaxLength(32);
    keyEdt->setValidator(keyValidator);
    keyLayout->addWidget(keyLbl);
    keyLayout->addWidget(keyEdt);
    keyLayout->setAlignment(Qt::AlignLeft);
    keyWgt->setLayout(keyLayout);

    //Настройка виджета выбора операции
    operationCB->addItems(*operationsLst);
    operationLayout->addWidget(operationLbl);
    operationLayout->addWidget(operationCB);
    operationLayout->setAlignment(Qt::AlignLeft);
    operationWgt->setLayout(operationLayout);

    //Настройка виджета установки режима таймера
    useTimerLayout->addWidget(useTimerLbl);
    useTimerLayout->addWidget(timerCB);
    useTimerLayout->setAlignment(Qt::AlignLeft);
    useTimerWgt->setLayout(useTimerLayout);

    //Настройка таймера
    QTime minTime = QTime();
    minTime.setHMS(0,1,0,0);
    timerEdt->setMinimumTime(minTime);
    timerLayout->addWidget(timerLbl);
    timerLayout->addWidget(timerEdt);
    timerLayout->setAlignment(Qt::AlignLeft);
    timerWgt->setLayout(timerLayout);
    timerWgt->setVisible(false);

    //Настройка виджета с кнопками
    btnLayout->addWidget(startBtn);
    btnLayout->addWidget(stopBtn);
    btnLayout->setAlignment(Qt::AlignLeft);
    btnWgt->setLayout(btnLayout);

    //Настройка строки статуса
    statusBar->addWidget(statusLbl);

    //Компоновка всех виджетов
    layout->addWidget(inputFileWgt);
    layout->addWidget(outputFileWgt);
    layout->addWidget(maskWgt);
    layout->addWidget(keyWgt);
    layout->addWidget(searchInAttachedWgt);
    layout->addWidget(deleteBaseWgt);
    layout->addWidget(rewriteWgt);
    layout->addWidget(operationWgt);
    layout->addWidget(useTimerWgt);
    layout->addWidget(timerWgt);
    layout->addWidget(btnWgt);
    centralWgt->setLayout(layout);

    //Настройка компоновщика центрального виджета
    this->setCentralWidget(centralWgt);
    this->setStatusBar(statusBar);

    //Установка доступности интерфейса
    setInterfaceEnabled(true);

    //Настройка виджета ввода исходного пути
    connect(selectInputFolderBtn, SIGNAL(clicked(bool)), this, SLOT(setInputPath()));
    connect(selectOutputFolderBtn, SIGNAL(clicked(bool)), this, SLOT(setOutputPath()));
    connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startWorking()));
    connect(stopBtn, SIGNAL(clicked(bool)), this, SLOT(stopTimer()));
    connect(timerCB, SIGNAL(toggled(bool)), timerWgt, SLOT(setVisible(bool)));
    connect(timerTmr, SIGNAL(timeout()), this, SLOT(slotTimeAlarm()));
}

//Слот окончания отсчёта таймера
void MainWindow::slotTimeAlarm(){
    encoding();
}

//Установка доступности интерфейса
void MainWindow::setInterfaceEnabled(bool value){
    startBtn->setEnabled(value);
    stopBtn->setEnabled(!value);
    inputFileEdt->setEnabled(value);
    outputFileEdt->setEnabled(value);
    selectInputFolderBtn->setEnabled(value);
    selectOutputFolderBtn->setEnabled(value);
    maskEdt->setEnabled(value);
    searchInAttachedCB->setEnabled(value);
    deleteBaseCB->setEnabled(value);
    rewriteCB->setEnabled(value);
    keyEdt->setEnabled(value);
    operationCB->setEnabled(value);
    timerCB->setEnabled(value);
    timerEdt->setEnabled(value);
}

//Слот остановки таймера
void MainWindow::stopTimer(){
    timerTmr->stop();
    setInterfaceEnabled(true);
    statusLbl->setText("Готово к работе");
}

//Вывод выбранного пути к исходным файлам
void MainWindow::setInputPath(){
    QFileDialog *fileDlg = new QFileDialog();
    fileDlg->setFileMode(QFileDialog::Directory);
    fileDlg->open();
    connect(fileDlg, &QFileDialog::accepted, [this, fileDlg](){
        inputFileEdt->setText(fileDlg->directory().path());
        delete fileDlg;
    });
}

//Вывод выбранного пути к выходным файлам
void MainWindow::setOutputPath(){
    QFileDialog *fileDlg = new QFileDialog();
    fileDlg->setFileMode(QFileDialog::Directory);
    fileDlg->open();
    connect(fileDlg, &QFileDialog::accepted, [this, fileDlg](){
        outputFileEdt->setText(fileDlg->directory().path());
        delete fileDlg;
    });
}

//Слот запуска процесса кодирования в выбранном режиме
void MainWindow::startWorking(){
    if(timerCB->isChecked()){
        int msecs = timerEdt->time().hour() * 3600000 + timerEdt->time().minute() * 60000;
        setInterfaceEnabled(false);
        timerTmr->start(msecs);
        statusLbl->setText("Работает по таймеру");
    }else{
        statusLbl->setText("Работа начата");
        encoding();
    }
}

//Кодирование выбранного файла
void MainWindow::encoding(){
    QFile *inputFile = nullptr;
    QFile *outputFile = nullptr;
    QByteArray byteArray;
    QByteArray tempArray;
    QByteArray keyArray;
    QString outFilePath;
    QStringList *filesList = new QStringList();

    //Заполнение списка масок файлов
    masksList = new QStringList{maskEdt->text().remove(" ").split("|")};

    //Проверка заполнения полей
    if(inputFileEdt->text() == "" || outputFileEdt->text() == "" || maskEdt->text() == ""){
        statusLbl->setText("Заполните все поля !");
        return;
    }

    searchFiles(filesList, inputFileEdt->text());

    keyArray = QByteArray::fromHex(keyEdt->text().toLocal8Bit());

    for(int i = 0; i < filesList->size(); i++){
        QString fileName = filesList->at(i).split("/").last();

        //Чтение файла в массив байтов
        inputFile = new QFile(filesList->at(i));
        inputFile->open(QIODevice::ReadWrite);
        byteArray = inputFile->readAll();
        tempArray.clear();

        //Если ключ не пуст или выбрана операция отрицания, то провести изменения
        if(keyEdt->text() != "" or operationCB->currentText() == "NOT"){
            for(int i = 0; i < byteArray.size(); i++){
                if(operationCB->currentText() == "XOR"){
                    tempArray.append(byteArray[i] ^ keyArray[i % keyArray.size()]);
                }
                else if(operationCB->currentText() == "OR"){
                    tempArray.append(byteArray[i] | keyArray[i % keyArray.size()]);
                }
                else if(operationCB->currentText() == "AND"){
                    tempArray.append(byteArray[i] & keyArray[i % keyArray.size()]);
                }
                else if(operationCB->currentText() == "NOT"){
                    tempArray.append(~byteArray[i]);
                }
            }
        }else{
            //Иначе скопировать массив без изменений
            tempArray.append(byteArray);
        }

        //Путь выходного файла
        outFilePath = outputFileEdt->text() + "/" + fileName;

        //Если во входном пути содержится выходной путь, то игнорировать
        if(filesList->at(i).contains(outputFileEdt->text())){
            continue;
        }

        //Проверка файла на существование и перезапись
        if(QFile(outFilePath).exists() && !rewriteCB->isChecked()){
            int counter = 1;
            QFile *file = new QFile(outputFileEdt->text() + "/" + QString::number(counter) + "_" + fileName);

            while(file->exists()){
                counter++;
                delete file;
                file = new QFile(outputFileEdt->text() + "/" + QString::number(counter) + "_" + fileName);
            }

            outputFile = file;
        }else{
            outputFile = new QFile(outFilePath);
        }

        //Запись в выходной файл изменённых байт информации
        if(outputFile->open(QIODevice::WriteOnly)){
            outputFile->write(tempArray, tempArray.size());
            outputFile->close();
        }

        //Удалить файл, если необходимо
        if(deleteBaseCB->isChecked()){
            inputFile->remove();
        }
    }

    statusLbl->setText("Готово к работе");

    //Освобождение выделенной памяти, для избежания утечек
    delete filesList;
    delete inputFile;
    delete outputFile;
}

//Функция отбора файлов по указанным параметрам
void MainWindow::searchFiles(QStringList *list, QString path){
    QDirIterator *it;

    //Установка режима обхода папок
    if(searchInAttachedCB->isChecked()){
        it = new QDirIterator(path, *masksList, QDir::Files, QDirIterator::Subdirectories);
    }else{
        it = new QDirIterator(path, *masksList, QDir::Files, QDirIterator::NoIteratorFlags);
    }

    //Заполнение списка путей подходящих файлов
    for(int i = 0; it->hasNext(); i++){
        it->next();
        list->append(it->filePath());
    }

    //Освобождение выделенной памяти, для избежания утечек
    delete it;
}

MainWindow::~MainWindow()
{
}
