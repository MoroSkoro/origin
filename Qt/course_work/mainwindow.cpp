#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataDb = new DbData(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);
    msg->setStandardButtons(QMessageBox::Retry |
                            QMessageBox::Ok | QMessageBox::Cancel);

    pix = new QPixmap();
    pixLb = new QLabel(this);
    msgLb = new QLabel(this);

    pix->load(":/images/led_off.png");
    pixLb->setPixmap(pix->scaledToHeight(pix->height()/4));

    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

 //* Добавим БД используя стандартный драйвер PSQL и зададим имя.

    dataBase->AddDataBase("QPSQL", "MyDB");

 //* Устанавливаем данные для подключениея к БД.

    connect(dataDb, &DbData::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });

    connect(this, &MainWindow::sig_ConnectAnew, this, &MainWindow::autoConnectAnew);
    connect(this, &MainWindow::sig_AirportListRequest, this, &MainWindow::slot_AirportListRequest);

    ui->stBar->addWidget(pixLb);
    ui->stBar->addWidget(msgLb);
    msgLb->setStyleSheet("color:red");
    msgLb->setText("Отключено");

    values = new QList<QPair<QString,QString>>();
    model = new QComboBoxModel();

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDisplayFormat("dd.MM.yyyy");
    ui->dateEdit->setMaximumDate(QDate(2017, 9, 14));
    ui->dateEdit->setMinimumDate(QDate(2016, 8, 15));

    ui->radBut_arrival->setChecked(true);
    ui->pushBut_Request->setDisabled(true);
    ui->pushBut_Statist->setDisabled(true);

    DialogStatistic = new DialogStatistics(this);
    connect(DialogStatistic, &DialogStatistics::signal_chart, this, &MainWindow::sl_monthStatistic);
    yearBar = new StatisticBar(this);
    plot = new StatisticPlot(this);
    DialogStatistic->ui->graphicsView->setChart(plot->chart);
    DialogStatistic->ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //this->autoConnect();
}

MainWindow::~MainWindow()
{
    delete values;
    delete model;
    delete dataBase;
    delete pix;
    delete pixLb;
    delete msgLb;
    delete ui;
}

/*!
 * @brief Слот отображает форму для ввода данных подключения к БД
 */
void MainWindow::on_act_addData_triggered()
{
    //Отобразим диалоговое окно. Какой метод нужно использовать?
    dataDb->show();
}

/*!
 * @brief Слот выполняет подключение к БД. И отображает ошибки.
 */

void MainWindow::on_act_connect_triggered()
{
    /*
     * Обработчик кнопки у нас должен подключаться и отключаться от БД.
     * Можно привязаться к надписи лейбла статуса. Если он равен
     * "Отключено" мы осуществляем подключение, если "Подключено" то
     * отключаемся
    */

    if(msgLb->text() == "Отключено"){

        bool connectStatus = false;

        connectStatus =  dataBase->ConnectToDataBase(dataForConnect);

        if(connectStatus){
            ui->act_connect->setText("Отключиться");
            msgLb->setStyleSheet("color:green");
            msgLb->setText("Подключено");
            pix->load(":/images/led_on.png");
            pixLb->setPixmap(pix->scaledToHeight(pix->height()/4));
            emit sig_AirportListRequest();
        }
        else{
            dataBase->DisconnectFromDataBase("MyDB");
            msg->setIcon(QMessageBox::Critical);
            msg->setText(dataBase->GetLastError().text());
            QTimer::singleShot(5000, this, autoConnectAnew);
            m_howClosed_msg = msg->exec();

            if (m_howClosed_msg==QMessageBox::Retry)
                emit sig_ConnectAnew();
        }

    }
    else{
        dataBase->DisconnectFromDataBase("MyDB");
        msgLb->setStyleSheet("color:red");
        msgLb->setText("Отключено");

        ui->act_connect->setText("Подключиться");

        pix->load(":/images/led_off.png");
        pixLb->setPixmap(pix->scaledToHeight(pix->height()/4));

        ui->pushBut_Request->setDisabled(true);
        ui->pushBut_Statist->setDisabled(true);
    }
}

void MainWindow::slot_AirportListRequest(){
    QSqlError err;
    QPair<QString,QString> date;

    err = dataBase->RequestToDB(request);

    if(err.type() != QSqlError::NoError){
        msg->setText(err.text());
        msg->exec();
    }
    else{
        while (dataBase->AirportQuery->next()){
            date.first = dataBase->AirportQuery->value(0).toString();
            date.second = dataBase->AirportQuery->value(1).toString();
            values->append(date);
        }

        std::sort(values->begin(), values->end());
        model->values = this->values;
        this->ui->combBoxAirList->setModel(model);

        ui->pushBut_Request->setEnabled(true);
        ui->pushBut_Statist->setEnabled(true);
    }
}

void MainWindow::ScreenDataFromDB(int typeRequest){

    switch (typeRequest) {
    case 1:{
        dataBase->modelAirportQuery->setHeaderData(0, Qt::Horizontal, tr("Номер рейса"));
        dataBase->modelAirportQuery->setHeaderData(1, Qt::Horizontal, tr("Время вылета"));
        dataBase->modelAirportQuery->setHeaderData(2, Qt::Horizontal, tr("Аэропорт отправления"));
        break;
    }
    case 2:{
        dataBase->modelAirportQuery->setHeaderData(0, Qt::Horizontal, tr("Номер рейса"));
        dataBase->modelAirportQuery->setHeaderData(1, Qt::Horizontal, tr("Время вылета"));
        dataBase->modelAirportQuery->setHeaderData(2, Qt::Horizontal, tr("Аэропорт назначения"));
        break;
    }
    default:
        break;
    }
    ui->td_result->setModel(dataBase->modelAirportQuery);
    ui->td_result->resizeColumnsToContents();
    ui->td_result->show();
}

void MainWindow::autoConnect(){
    dataDb->on_buttonBox_accepted();
    on_act_connect_triggered();
}

void MainWindow::autoConnectAnew(){
    switch (m_howClosed_msg) {
        case QMessageBox::Retry:{
            m_howClosed_msg = QMessageBox::Cancel;
            m_RetryClosed_msg = true;
            on_act_connect_triggered();
            break;
        }
        case QMessageBox::Cancel:{
            if(!m_RetryClosed_msg){
                msg->close();
                on_act_connect_triggered();
            }
            m_RetryClosed_msg=false;
            break;
        }
    }
}

void MainWindow::on_pushBut_Request_clicked(){
    airportCode = (*this->values)[ui->combBoxAirList->currentIndex()].second;
    int i=1;
    QDate day;
    day = ui->dateEdit->date();
    QString dayString = day.toString("M/d/yyyy");
    QString request;
    if(ui->radBut_arrival->isChecked()){
    //request = request_arrival + "'" + airportCode + "' " + "AND '4/17/2017' < scheduled_arrival::date < '4/19/2017'";
        request = request_arrivall + "'" + airportCode + "' "
            + "AND scheduled_arrival::date = '" + dayString + "'";
    }
    else{
        request = request_departure + "'" + airportCode + "' "
            + "AND scheduled_departure::date = '" + dayString + "'";
        i=2;
    }
    dataBase->ModelRequest(request, dataBase->modelAirportQuery);
    ScreenDataFromDB(i);
}


void MainWindow::on_pushBut_Statist_clicked()
{
    QString airportName = "Аэропорт: " + (*this->values)[ui->combBoxAirList->currentIndex()].first;
    DialogStatistic->ui->label->setText(airportName);

    DialogStatistic->show();
    airportCode = (*this->values)[ui->combBoxAirList->currentIndex()].second;
    QString request;
    request = "SELECT count(flight_no), date_trunc('month', scheduled_departure) as \"Month\""
              " from bookings.flights f"
              " WHERE (scheduled_departure::date > date('2016-08-31') and"
              " scheduled_departure::date <= date('2017-08-31')) and (departure_airport = '"
              + airportCode + "' or arrival_airport = '"
              + airportCode + "' ) group by \"Month\"";

    dataBase->ModelRequest(request, dataBase->modelStatisticYearQuery);
    date_for_statisticYear(yearBar->statisticInYear, yearBar->categories, dataBase->modelStatisticYearQuery);
    yearBar->buildHistogram();

    DialogStatistic->ui->graphicsView_2->setChart(yearBar->chartBar);
    DialogStatistic->ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    DialogStatistic->ui->tabWidget->setCurrentWidget(DialogStatistic->ui->tab2);
    DialogStatistic->ui->graphicsView_2->show();
}

void MainWindow::date_for_statisticYear(QBarSet* s, QStringList& categories, QSqlQueryModel* m){

    for(int i = 0; i < m->rowCount(); i++){
        *s << m->data(m->index(i, 0)).toInt();
        categories << m->data(m->index(i, 1)).toString();
    }
}

void MainWindow::sl_monthStatistic(){
    QString month = QString::number(DialogStatistic->currentMonth +1);
    QString request;
    request = "SELECT count(flight_no), date_trunc('day', scheduled_departure) as \"Day\""
              " from bookings.flights f"
              " WHERE(scheduled_departure::date > date('2016-08-31') and"
              " scheduled_departure::date <= date('2017-08-31')) and ( departure_airport = '"
              + airportCode + "' or arrival_airport = '"
              + airportCode +
              "') and date_part('month', scheduled_departure) = "
              + month + " GROUP BY \"Day\"";

    dataBase->ModelRequest(request, dataBase->modelStatisticMonthQuery);

    int size = dataBase->modelStatisticMonthQuery->rowCount();
    plot->x.resize(size);
    plot->y.resize(size);
    for(int i = 0; i < size; i++){
        plot->y[i] = dataBase->modelStatisticMonthQuery->data(dataBase->modelStatisticMonthQuery->index(i, 0)).toInt();
        plot->x[i] = i+1;
    }
    plot->buildPlot(size);
    DialogStatistic->ui->graphicsView->show();
}
