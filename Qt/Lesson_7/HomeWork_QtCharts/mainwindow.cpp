#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_clearResult->setCheckable(true);

    d = new DialogChart(this);

    //Выделим память под наши объекты.

    //Объект QChart является основным, в котором хранятся все данные графиков и который отвечает
    //за само поле отображения графика, управляет осями, легенодой и прочими атрибутами графика.
    chart = new QChart( );
    chart->legend()->setVisible(false);
    //Объект QChartView является виджетом отображальщиком графика. В его конструктор необходимо передать ссылку
    //на объект QChart.
    chartView = new QChartView(chart);
    //И создадим объект нашего класса.
    graphClass = new GraphicChart(CANALS_NUM);
    //Создаем оси
    axisX = new QValueAxis;
    axisY = new QValueAxis;

    ui->pb_chart->setDisabled(true);

    connect(d, d->sig_pb_cleane, this, &MainWindow::sl_pb_clear_clicked );
    connect(d, d->sig_pb_builde, this, &MainWindow::sl_pb_updGraph_clicked );
    connect(this, &MainWindow::sig_yDataReady, this, &MainWindow::sl_chartReady);

//chart -> chartVuiew -> данные для отображения
    d->layout->addWidget(chartView);
    d->wid_chart->setLayout(d->layout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
    delete graphClass;
    delete chartView;
    delete axisX;
    delete axisY;
}



/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::ReadFile(QString path, uint8_t numberChannel)
{

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.isOpen() == false){

        if(pathToFile.isEmpty()){
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }
    else{

        //продумать как выйти из функции
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWorld = 0, sizeFrame = 0;

    while(dataStream.atEnd() == false){

        dataStream >> currentWorld;

        if(currentWorld == 0xFFFFFFFF){

            dataStream >> currentWorld;

            if(currentWorld < 0x80000000){

                dataStream >> sizeFrame;

                if(sizeFrame > 1500){
                    continue;
                }

                for(int i = 0; i<sizeFrame/sizeof(uint32_t); i++){

                    dataStream >> currentWorld;

                    if((currentWorld >> 24) == numberChannel){

                        readData.append(currentWorld);

                    }
                }
            }
        }
    }
    ui->chB_readSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::ProcessFile(const QVector<uint32_t> dataFile)
{
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if(word > 0x800000){
            word -= 0x1000000;
        }

        double res = ((double)word/6000000)*10;
        resultData.append(res);
    }
    ui->chB_procFileSucces->setChecked(true);

    return resultData;
}

QVector<double> MainWindow::FindMax(QVector<double> resultData)
{
    double max = 0, sMax=0;
    //Поиск первого максиума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > max){
            max = num;
        }
    }

    //Поиск 2го максимума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > sMax && (qFuzzyCompare(num, max) == false)){
            sMax = num;
        }
    }

    QVector<double> maxs = {max, sMax};
    ui->chB_maxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::FindMin(QVector<double> resultData)
{

    double min = 0, sMin = 0;
    QThread::sleep(1);
    //Поиск первого максиума
    foreach (double num, resultData){
        if(num < min){
            min = num;
        }
    }
    QThread::sleep(1);
    //Поиск 2го максимума
    foreach (double num, resultData){
        if(num < sMin && (qFuzzyCompare(num, min) == false)){
            sMin = num;
        }
    }

    QVector<double> mins = {min, sMin};
    ui->chB_minSucess->setChecked(true);
    return mins;

}

void MainWindow::DisplayResult(QVector<double> mins, QVector<double> maxs)
{
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
}


/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_path_clicked()
{
    pathToFile = "";
    ui->le_path->clear();

    pathToFile =  QFileDialog::getOpenFileName(this,
                                              tr("Открыть файл"), "/home/", tr("ADC Files (*.adc)"));

    ui->le_path->setText(pathToFile);
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_start_clicked()
{
    ui->pb_chart->setDisabled(true);
    //проверка на то, что файл выбран
    if(pathToFile.isEmpty()){

        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    ui->chB_maxSucess->setChecked(false);
    ui->chB_procFileSucces->setChecked(false);
    ui->chB_readSucces->setChecked(false);
    ui->chB_minSucess->setChecked(false);

    int selectIndex = ui->cmB_numCh->currentIndex();
    //Маски каналов
    if(selectIndex == 0){
        numberSelectChannel = 0xEA;
    }
    else if(selectIndex == 1){
        numberSelectChannel = 0xEF;
    }
    else if(selectIndex == 2){
        numberSelectChannel = 0xED;
    }


    auto read = [&]{ return ReadFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> res){ return ProcessFile(res);};
    auto findMax = [&](QVector<double> res){
                                                maxs = FindMax(res);
                                                mins = FindMin(res);

                                                DisplayResult(mins, maxs);
                                                /*
                                                 * Тут необходимо реализовать код наполнения серии
                                                 * и вызов сигнала для отображения графика
                                                 */
                                                y_data.clear();
                                                y_data = res;
                                                emit sig_yDataReady();
                                             };

    auto result = QtConcurrent::run(read)
                               .then(process)
                               .then(findMax);
}

//Для графика
void MainWindow::on_pb_chart_clicked()
{
    d->show();
    MainWindow::sl_pb_updGraph_clicked();
}


/*!
    @brief Метод обрабатывает нажатие кнопки "Очистить"
*/
void MainWindow::sl_pb_clear_clicked()
{
    //Вызовем метод очистки графика.
    graphClass->ClearGraph(chart);
}

/*!
    @brief Метод обрабатывает нажатие кнопки "Построить"
*/
void MainWindow::sl_pb_updGraph_clicked()
{

    //Перед новой отрисовкой очистим графики
    if(chart->series().isEmpty() == false){
        graphClass->ClearGraph(chart);
    }

    //создадим контейнеры для хранения данных
    QVector<double> x;
    QVector<double> y;

    //считываем шаг сетки и граничные значения
    double step = 1;

    int minVal = d->ui->dbSbox_minRange->value();
    int maxVal = d->ui->dbSbox_maxRange->value();

    /*
        Формируем сетку значений, ресайзим вектор и заполняем его
    */
    int steps = (maxVal-minVal); // round(((maxVal-minVal)/step));
    x.resize(steps);
    x[0] = minVal;
    for(int i = 1; i<steps; i++){
        x[i] = x[i-1]+step;
    }

    /*
     * Заполняем массив значений в зависимости
     * от выбранного флажка
     */
        y.resize(steps);
    for(int i = 0; i<steps; i++){
        y[i]=y_data[minVal+i];
    }

        //Добавляем данные в серию
    graphClass->AddDataToGrahp(x,y, FIRST_GRAPH);

    //Обновим график, т.е. добавим сформированыые серии на график
        graphClass->UpdateGraph(chart);

        axisX->setRange(minVal, maxVal);
        axisX->setTickCount(20);
        axisX->setLabelFormat("%i");
        chartView->chart()->setAxisX(axisX, graphClass->ptrGraph[FIRST_GRAPH]);

        axisY->setRange(-1, -0.75);
        axisY->setTickCount(1);
        axisY->setLabelFormat("%.2f");
        chartView->chart()->setAxisY(axisY, graphClass->ptrGraph[FIRST_GRAPH]);

    //И отобразим его.
    ViewGraph();
}

void MainWindow::ViewGraph()
{
    chartView->show( );
}

void MainWindow::sl_chartReady(){
    ui->pb_chart->setEnabled(true);
}
