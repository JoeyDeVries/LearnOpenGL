# FPS Demo - First Person Shooter Game Basic Setup

这是一个基于 OpenGL 的 FPS（第一人称射击）游戏基础设置演示。

## 功能特性

- **FPS 相机控制**: 
  - WASD 键移动（前后左右）
  - 鼠标控制视角
  - 鼠标滚轮缩放
  
- **基本光照**: 
  - 环境光
  - 漫反射光照
  - 镜面高光

- **3D 渲染**:
  - 带纹理的旋转立方体
  - 深度测试
  - 法线贴图支持

## 文件结构

```
1.fps_demo/
├── fps_demo.cpp    # 主程序源代码
├── fps_demo.vs     # 顶点着色器
└── fps_demo.fs     # 片段着色器
```

## 构建说明

### Linux (Ubuntu/Debian)

1. 安装依赖:
```bash
sudo apt-get install libglfw3-dev libglm-dev libassimp-dev libglew-dev libfreetype-dev libgl1-mesa-dev
```

2. 创建构建目录并编译:
```bash
cd /path/to/LearnOpenGL
mkdir build && cd build
cmake ..
make
```

3. 运行程序:
```bash
cd ../bin/8.guest/2024
./8.guest__2024__1.fps_demo
```

### Windows

1. 确保已安装 Visual Studio 和 CMake
2. 使用 CMake GUI 或命令行生成项目文件
3. 编译并运行

### macOS

```bash
brew install cmake assimp glm glfw freetype
mkdir build && cd build
cmake -G Xcode ..
# 或使用 make
cmake ..
make
```

## 操作说明

| 按键 | 功能 |
|------|------|
| W | 向前移动 |
| S | 向后移动 |
| A | 向左移动 |
| D | 向右移动 |
| 鼠标移动 | 控制视角 |
| 鼠标滚轮 | 缩放视野 |
| ESC | 退出程序 |

## 技术细节

### 相机系统
使用 LearnOpenGL 的 Camera 类，提供：
- 欧拉角计算（Yaw, Pitch）
- 观察矩阵生成
- 键盘和鼠标输入处理

### 着色器
- **顶点着色器**: 处理顶点位置、纹理坐标和法线，应用 MVP 变换
- **片段着色器**: 实现 Phong 光照模型（环境光 + 漫反射 + 镜面光）

### 顶点数据
每个顶点包含：
- 位置 (3 float)
- 纹理坐标 (2 float)
- 法线 (3 float)

## 扩展建议

要完善 FPS 游戏，可以考虑添加：
1. 玩家碰撞检测
2. 武器系统和射击机制
3. 敌人 AI
4. 地图/关卡系统
5. 音效系统（irrKlang）
6. 动画系统（Assimp）
7. UI/HUD 界面
8. 物理引擎集成

## 参考资料

- [LearnOpenGL](https://learnopengl.com)
- [GLFW Documentation](https://www.glfw.org/documentation.html)
- [GLM Documentation](https://glm.g-truc.net/)
