# Gm88 游戏SDK 文档

本项目是Gm88游戏SDK的文档站点，使用Jekyll编译，同时支持两个镜像

* Github Page: https://gm88tp.github.io/GameSDKDoc
* Gitee Page: https://gm88-tp.gitee.io/gamesdkdoc

## 子模块

本项目包括多个子模块，用于将各终端的SDK文档包括进来

* Android/Domestic https://github.com/gm88tp/Android-Domestic-SDK-Demo
* Android/Global https://github.com/gm88tp/Android-Global-SDK-Demo
* Android/Global-Standalone https://github.com/gm88tp/Android-Global-SDK-Demo-StandAlone
* Ios/Domestic https://github.com/gm88tp/Ios-Domestic-SDK-Demo
* Ios/Global https://github.com/gm88tp/Ios-Global-SDK-Demo
* Ios/Global-Standalone https://github.com/gm88tp/Ios-Global-SDK-Demo-StandAlone
* Server https://github.com/gm88tp/Server-SDK-Demo

## 更新

更新子模块

```bash
git submodule update --remote
```

复制文档到输出目录
```bash
./sync-doc.sh
```

提交
```bash
git commit -m 'message'
```

推送

```bash
git push
```
