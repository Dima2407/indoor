Navigator Library
=======
**!! ЭТО ДРАФТ. Статья не закончена !!**

Библиотека для indoor навигациии. Ориентирована на работу на носимых 
устрайствах-гаджетах. Принимает данные с датчиков, радио-маяков и фото-, видеокамер.

Использование
---------------

Использование в простейшем случае:
```C++
using namespace IndoorNavigation;
GeneralNavirator gena;
gena.config( GeneralNaviratorConfiguration(params) );  // или в
while( InputDataBuffer idb = "receive new data from beacons, sensors, cameras" ){
	gena.pushData(idb);  // ввод буффера разнообразных данных
	gena.processPendingData();
	gena.processOutput(); 
}
```
Совсем по-босяцки, получить навигационные данные сразу. Очень не эффективно с точки
зрения производительность.
```
GeneralNavirator gena;
while( InputDataBuffer idb = "receive new data from beacons, sensors, cameras" ){
	OutputNavigationData outnavi = gena.processAll(idb);
	//...
}
```

Описание классов и структуры
----------------

### User space

`InputData` универсальная порция входных данных в 
кросс-платформенном формате, например `ByteArray` или `JSON`, иными
словами то, что можно десериализовать.   
`InputDataBuffer` - буффер входных данных.  

Класс `GeneralNaviratorConfiguration` представляет возможную 
настройку `GeneralNavirator`а: задаёт пачку используемых подлежащих
навигаторов, тайминги, включение/отключение опциональных фильтров и
дополнительных процедур обработки, размеры буфферов.  

`GeneralNavirator::processPendingData()` распределяет входные данные по ответственныи подлежащим навигаторам, 
например, `BeaconNavigator`. Те, в свою очередь, фильтруют, обрабатывают, пересчитывают,
и возвращают текущую, по рассчётам каждого из навигаторов. Результат 
этой функции пачка вычисленных позиций (на диаграмме `OutputNavigationData`) 
от каждого из навигаторов.   

`GeneralNavirator::processOutput()` - Среди вычисленных подлежащими навигаторами,
выбрать, вычислить, отфильтровать, проанализировать и получить 
результат - **позицию**.
Для асинхронного ввода данных и синхронного вывода пользователь 
в одном потоке вводит данные, в другом вызывает процессинг и 
забирает результат.

GeneralNavigator Центральный класс библиотеки.   

### Внутренность 
`GeneralNavigator` распределяет полученные данные в соответствии с их типом
в подлежащие навигаторы: `BeaconNavigator`, `NavigatorBySensors`, `CameraSlamNavigator`, etc.
Эти навигаторы обрабатывают входные данные по алгоритмам, которые реализует *заказчик*.
Диаграмма снабжена большим количеством заметок.

Диаграмма классов. *Стабильный черновик*   
![](NavigatorLibrary-general.png)

  
![](NavigatorLibrary-general_001.png)


**[Ссылка на ТЗ](https://www.evernote.com/shard/s676/nl/159924744/a91bd946-fb37-44c9-9690-9be4d76f463e).**  
1. ![](tech-task-draft-p1-Main.jpg)
2. ![](tech-task-draft-p2-Beacon-RSSI.jpg)
3. ![](tech-task-draft-p3-Positioning-by-sensors.jpg)
4. ![](tech-task-draft-p4-Calibrating-beacons.jpg)
