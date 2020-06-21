# 1、 Centos下七牛云qshell安装 #


## 1.1 查看自己的Linux内核版本 ##

    cat /proc/version


## 1.2 到官方下载对应的zip安装包 ##

[https://developer.qiniu.com/kodo/tools/1302/qshell](https://developer.qiniu.com/kodo/tools/1302/qshell)


## 1.3 上传到一个具体的目录 ##
我上传到了/home/tools/,
解压

    unzip qshell-linux-x86-v2.4.1.zip

移动到/home/tools/

    mv qshell-linux-x86-v2.4.1.zip /home/tools/qshell

1.4 写环境变量
编辑profile文件

    vi /etc/profile

找到export行，在下面新增加一行，内容为：export PATH=$PATH:/home/tools。
注：＝ 等号两边不能有任何空格。
修改不会立马生效，如果需要立即生效的话，执行

    source /etc/profile



1.5 测试安装情况

    qshell -v

# 2、 配置用户信息 #

配置AccessKey\SecretKey\Name
    
    qshell account ak sk name
# 3、 常用入门级命令 #
## 3.1 buckets 获取当前账号下所有的空间名称 ##
    qshell buckets
## 3.2 buckets 获取具体空间名称下所有文件 ##
    qshell listbucket <Bucket> 

# 4. 上传具体目录下的文件 #

如我要上传/www/wwwroot/xxx.cn/Public/uploads下所有文件
## 4.1 在当前目录下写上传配置文件 ##

    {
      "src_dir" : "/www/wwwroot/xxx.cn/Public/uploads",
      "bucket" : "xxx"
    }

## 4.2 简单的上传命令 ##
为了方便我看是否上传成功，我在当前目录下建立以qiniu目录，
保存当前上传文件成功列表。

     qshell qupload --success-list qiniu/sucessList uploadConfig