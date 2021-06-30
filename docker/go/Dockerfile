#Go
FROM golang:latest as build
MAINTAINER Wangwenwei <970074804@qq.com>
LABEL Description="This image is the go dev base images"  Version="1.0"
#change Goproxy 
RUN go env -w GOPROXY=https://goproxy.cn
RUN go env -w GO111MODULE=on
#配置工作目录
WORKDIR /go/src/darbuly/demo

#拷贝当前所有文件夹:所以在build的时候，必须以及写好go脚本，有main.go
COPY . .

#初始化 go.mod
RUN go mod init darbuly.com/demo

#安装第三方拓展包
RUN go mod tidy 

#执行build
RUN go build main.go

# 引入alphine最小linux镜像
FROM alpine
# 设置工作目录
WORKDIR /data/app
#拷贝编译好的执行文件带当前目录
COPY --from=build /go/src/darbuly/demo/main .

# ！！！ 注意，经测试发现alpine中缺少动态库，经查询后的解决方式为创建一个软链
RUN mkdir /lib64 && ln -s /lib/libc.musl-x86_64.so.1 /lib64/ld-linux-x86-64.so.2

#EXPOSE 20020 20021 20022

#执行可执行文件
CMD ["./main"]





