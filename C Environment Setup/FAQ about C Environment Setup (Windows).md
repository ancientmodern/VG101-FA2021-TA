# FAQ about C/C++ environment setup on Windows

VG101 FA2021 TA Group

## 1. My SJTU e-mail cannot be used to activate the CLion, what should I do?

For SJTU students, usually there are two ways to activate the CLion, 

+ Apply in: https://www.jetbrains.com/shop/eform/students **(Official Document)**, with your CHSI certification from https://my.chsi.com.cn/archive/gdjy/xj/show.action, or the photo of your student card.
+ Or download **JetBrains All in One** from [this page](http://lic.si.sjtu.edu.cn/Default/softshow/tag/MDAwMDAwMDAwMLGedqE), and then follow the steps on [this page](http://lic.si.sjtu.edu.cn/Default/huatishow/tag/MDAwMDAwMDAwMLJ4iqE), notice that the **server address** is http://lic.si.sjtu.edu.cn:8080, the address directly copied from the page maybe wrong.
  + <img src="http://lic.si.sjtu.edu.cn/Public/Upload/ue/20210917/1631864657908818.png" alt="微信截图_20210917100235.png" style="zoom: 80%;" />



## 2. What should I choose for "Import Clion Settings"?

<img src="https://img-blog.csdnimg.cn/2019021814081744.png" alt="mac安装Clion_JanzeeLiu的博客-程序员资料_mac安装clion - 程序员资料" style="zoom:80%;" />

Since this is the first JetBrains product you install on your computer, there is no existing config, so just choose **"Do not import settings"**.



## 3. When installing MinGW-w64, it shows "The file has been downloaded incorrectly"

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021012700283.png" alt="image-20211021012700283" style="zoom: 67%;" />

The default installer of MinGW-w64 is an online installer, due to some network issues (especially without VPN), errors may occur in the downloading process. If the problem keeps happening, you can download the entire package of MinGW-w64. On https://sourceforge.net/projects/mingw-w64/files/, choose **x86_64-posix-seh**.

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021012957715.png" alt="image-20211021012957715" style="zoom: 50%;" />

And then unzip the downloaded `.7z` file, if you do not have corresponding unzip software, you may install "7-Zip". Notice that in this case, the unzipped file is already the final form of MinGW-w64. You can move the folder to an ideal place (without Chinese characters), copy the path of the folder, and then follow the steps in next question.



## 4. I have just installed MinGW32/MinGW-w64, where and how can I make use of it?

Usually there are two approaches,

### In CLion (Required)

On the left corner of the interface of CLion, click **"File - Settings - Build, Execution, Deployment - Toolchains - MinGW"**, first use "Up" to set MinGW as the **default/first** toolchain, and then type the **installation path** of your MinGW32 or MinGW-w64 into the **"Environment"** blank.

Here are two samples,

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021010751362.png" alt="image-20211021010751362" style="zoom:80%;" />

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021010805424.png" alt="image-20211021010805424" style="zoom:80%;" />

Then CLion will automatically detect the Make, C Compiler, C++ Compiler and Debugger. If you see some warnings about **CMake**, check the Question 5.

### In Command-Line Interfaces (Cmd/PowerShell) by modifying the environment path

Note: Since I cannot change my Windows language to English, the following part will be partly in Chinese.

1. On your desktop, right click "此电脑 - 属性"

   <img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021011227157.png" alt="image-20211021011227157" style="zoom:50%;" />

2. On the right side, click "高级系统设置"

   <img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021011335645.png" alt="image-20211021011335645" style="zoom:50%;" />

3. Click "环境变量"

   <img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021011420994.png" alt="image-20211021011420994" style="zoom:50%;" />

4. Double click the variable "Path" in "系统变量"

   <img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021011507149.png" alt="image-20211021011507149" style="zoom:50%;" />

5. Click "新建" and add the path of the "bin" directory (containing `gcc.exe/g++.exe`) of your MinGW

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021011717479.png" alt="image-20211021011717479" style="zoom:50%;" />

6. Press "Win + R" and enter "powershell", and enter the command `gcc -v` in the PowerShell, if you see message like this, it means your environment path is configured correctly. Note that you may restart or open a new PowerShell, since the PowerShell only loads the environment path when it launches.<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021011946824.png" alt="image-20211021011946824" style="zoom: 50%;" />

7. Enjoy using GCC/G++ via command line!



## 5. I have completed all the steps above, but in CLion the CMake shows "not able to compile a simple test program"

![image-20211021014402340](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021014402340.png)

This is usually caused by non-Latin symbols (for example, Chinese) in the installation path of CLion, as CMake and MinGW do not support non-Latin symbols. Hence, when you use the bundled CMake in CLion, there will be some problems. 

Besides reinstall CLion in another path without Chinese character, a possible solution is to use a custom CMake. You can download CMake from https://cmake.org/download/,

![image-20211021015012094](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021015012094.png)

and install it in the path without Chinese character. Then you can **follow similar steps in Question 4 to add the custom CMake into CLion's toolchain**. When installing CMake, you can select this option, and it will automatically add CMake into your environment path.

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211021015429459.png" alt="image-20211021015429459" style="zoom:50%;" />



## 6. My problem is neither listed above nor in the previous guidelines, what should I do?

First you may try to search your problems (for example, the error messages) through the search engines. Actually I got all of above solutions from Google. 

If you do not find the solution, feel free to ask TAs for help. Don't worry that your question may be a little "stupid", in fact I think setting up C/C++ environment is really a difficult task on Windows, and it requires a certain amount of programming knowledge. Our three TAs are always willing to help you solve your problems, and assist you to build up the foundation for further C/C++ journey. Good luck!

<img src="http://wx4.sinaimg.cn/large/86883a42gy1fsys3g8222j20c80c8ta7.jpg" alt="今天也要加油鸭 - 唐老鸭鸭鸭表情包_唐老鸭_鸭鸭_卡通表情" style="zoom: 50%;" />

