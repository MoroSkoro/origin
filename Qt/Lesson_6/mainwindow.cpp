#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sb_initNum->setValue(200000);
    ui->rb_synchOff->setChecked(true);

   race1 = new Controller(&m);
   race2 = new Controller(&m);

   concurRace1 = new ExampleRace(&m);
   concurRace2 = new ExampleRace(&m);

    //Сигналы по завершению работы потоков
    connect(race1, &Controller::sig_WorkFinish, [&](){
        //отображаем только когда второй поток закончит работу
        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                  QString::number(ui->sb_initNum->value()*2));
            ui->pb_start->setEnabled(true);
        }

    });

    connect(race2, &Controller::sig_WorkFinish, [&](){

        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть "+
                                 QString::number(ui->sb_initNum->value()*2));
            ui->pb_start->setEnabled(true);
        }

    });


    connect(concurRace1, &ExampleRace::sig_Finish, [&](){

        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                 QString::number(ui->sb_initNum->value()*2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(concurRace2, &ExampleRace::sig_Finish, [&](){

        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                 QString::number(ui->sb_initNum->value()*2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(&ftWhWork1, &QFutureWatcher<void>::finished, this, [&]{
        futureRace2 = QtConcurrent::run(concurRace2->DoWork, concurRace2,
                                        &number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
        //ftWhWork2.setFuture(futureRace2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Метод запускает два потока
void MainWindow::StartRace(void){
//number = 0;

    if(ui->rb_qtConcur->isChecked()){

        //ui->te_debug->append("Выполни ДЗ!");
        //Тут должен быть код ДЗ

//              Вариант 1. Но в DoWork нужно мьютексы включить.
//        QFuture <void> futureRace1 = QtConcurrent::run(concurRace1->DoWork, concurRace1,
//                                                      &number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value() );
//        QFuture <void> futureRace2 = QtConcurrent::run(concurRace2->DoWork, concurRace2,
//                                                      &number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value() );

//              Вариант 2. Последовательно.
//        QtConcurrent::run([&]{concurRace1->DoWork(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());}).
//                        then([&]{concurRace2->DoWork(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());});


//              Вариант 3. С Watcher.
//        futureRace1 = QtConcurrent::run(concurRace1->DoWork, concurRace1,
//                          &number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
//        ftWhWork1.setFuture(futureRace1);

//              Вариант 4. Последовательно с лямдой.
                auto wk1 = [&]{concurRace1->DoWork(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());};
                auto wk2 = [&]{concurRace2->DoWork(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());};
                QtConcurrent::run(wk1).then(wk2);

    }
    else{
        race1->operate(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
        race2->operate(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
    }
}

//Обработка кнопки "Старт"
void MainWindow::on_pb_start_clicked()
{
    ui->pb_start->setEnabled(false);
    countFinish = 0;
    number = 0;
    StartRace( );
}

