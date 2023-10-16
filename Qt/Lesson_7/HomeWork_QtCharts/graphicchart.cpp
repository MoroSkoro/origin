#include "graphicchart.h"

GraphicChart::GraphicChart(uint32_t Canals_number)
{
    //В конструктор необходимо передать сколько серий графиков будет использоваться. Серия это один график,
    //в одних осях может быть несколько графиков, например для сравнения.

    //Примем количество графиков и ресайзнем вектор.
    canalsNum = Canals_number;
    ptrGraph.resize(canalsNum);

    //Создадим объекты серий
    for(int i = 0; i<canalsNum; i++){
        ptrGraph[i] = new QLineSeries(this);
    }

}

/*!
 * \brief Метод добавляет данные на график.
 * \param x - данные по оси Х
 * \param y - по оси У
 * \param canalNum -  (какой график, канал)
 */
void GraphicChart::AddDataToGrahp(QVector<double> x, QVector<double> y, uint32_t canalNum)
{

    //Зададим размер графика, т.е. количество точек.
    uint32_t size = 0;
    //Необходимо, чтобы х и у были равны.
    if(x.size() >= y.size()){
        size = y.size();
    }
    else{
        size = x.size();
    }

    //Добавление точек в серию осуществляется при помощи метода append.
    for(int j = 0; j<size; j++){
        ptrGraph[canalNum]->append(x[j],y[j]);
    }
}
/*!
 * \brief Метод очищает данные на графике
 * \param chart - указатель на график
 */
void GraphicChart::ClearGraph(QChart *chart)
{
    //Необходимо очистить все графики
    for(int i = 0; i<canalsNum; i++){
        //Очищаем серии
        ptrGraph[i]->clear();
        //Удаляем серии из графика
        chart->removeSeries(ptrGraph[i]);
    }
}

/*!
 * \brief Метод добавляет серии к графику
 * \param chart - указатель на график
 */
void GraphicChart::UpdateGraph(QChart *chart)
{
    for(int i = 0; i<canalsNum; i++){
        chart->addSeries(ptrGraph[i]);
    }

}




