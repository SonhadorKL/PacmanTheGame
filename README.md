# Описание проекта #
## Основная информация ##
Проект представляет из себя копию популярной игры Pacman, написанный на языке C++ с использованием мультимедийной библиотеки [SFML](https://www.sfml-dev.org/)  
Игрок управляет персонажем Pacman, отвечая за его перемещение по игровому полю. Вместе с этим на пакмана охотятся призраки. Цель игрока - собрать всю еду, расположенную по игровому полю, и при этом уворачиваться от призраков. Когда вся еда будет собрана, игра перезапускается, сохраняя собранные ранее очки.



## Запуск проекта ##
Проект работает на Ubuntu, Windows. Для запуска актуальной версии склонируйте репозиторий к себе
```console
git clone git@github.com:SonhadorKL/PacmanTheGame.git
cd PacmanTheGame
```
В проекте используется библиотека SFML. Если вы используйте Ubuntu, то для её установки просто соберите проект с правами администратора:
```console
mkdir build && cd build
sudo cmake ..
make
```
На других системах достаточно собрать проект обычным образом.
```console
mkdir build && cd build
cmake ..
make
```
Наконец, для запуска игры пропишите:
```console
../bin/Pacman
```

## Игровой процесс
Здесь можете посмотреть на на скриншоты непосредственно игры и экрана поражения.

![](/docs/img/game.png)
![](/docs/img/death_screen.png)

## Процесс разработки ##
### 19.03.2023 ###

К первой итерации была реализована основа внутренней логики проекта, а именно:
1. Реализованы классы Pacman и Ghost, а также их передвижение по игровому полю
2. Еда, подбираемая игроком
3. Непосредственно игровое поле классом Field
4. Класс Game, отвечающий за базовое управление игровым процессом  

С подробностями архитектуры можно ознакомиться в UML диаграммe в папке docs

### 14.04.2023 ###
Ко второй итерации доделан game play, реализован базовый GUI.

Игровый процесс:
1. На уровнях появились усилители! Съешьте их, чтобы стать бессмертным и отомстить призракам.
2. Три жизни у пакмана! Берегите их, если хотите набрать больше очков
3. Усложнение. После того, как pacman собирает всю еду на поле, игровой процесс усложняется: всё становится быстрее, призраки лучше видят, а со временем их становится больше! В награду вы получаете больше очков, но как долго вы сможете продержаться?

Графический интерфейс (теперь он есть!):
1. Игра начинается в меню
2. В процессе игры вы видите своё здоровье, очки и уровень
3. YOU DIED с набранными очками

### 28.04.2023 ###
Третья итерация - регулировка баланса и сохранение рекордов!
1. Изменена формула для изменения скорости игра: теперь совремем она растет медленнее
2. Количество призраков теперь фиксировано: их всегда четыре
3. Появился смысл играть! Теперь результаты игры сохраняются и 10 ваших рекордов показываются в Leaderboard