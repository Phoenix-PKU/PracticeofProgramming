# ？了个？

> PKU 程序设计实习 Qt大作业

## 游戏简介
该程序为一款游戏，模仿最近比较热门的“羊了个羊”微信小游戏。

实现了羊了个羊的大部分功能，以及自行选择游戏难度等其他功能以增加游戏的趣味性，为用户提供休闲娱乐，益智以及社交的平台。

主界面可以选择游戏难度；游戏界面包括卡牌、卡槽和三种道具按钮；游戏上方有进度条以提示游戏完成度。

## 游戏规则
(1) 用户选择游戏中使用的图标，选择游戏难度。

(2) 开始游戏之后用户可以点击最上层的图标并加入卡槽中。

(3) 当下层图标上方覆盖的图标均被移除后下方图标变为最上层图标。

(3) 用户可以点击道具卡牌以进行洗牌、撤回、破坏等，道具卡牌使用次数有限制 ~~，看广告可获得道具~~。

## 游戏视频
https://www.bilibili.com/video/？？？

## 环境配置
支持Windows和MacOS，需安装Qt 6.5.1以及Multimedia包。

将sheep_and_sheep下载到本地后，用Qt Creator打开CMakeLists.txt，根据提示进行项目构建。
