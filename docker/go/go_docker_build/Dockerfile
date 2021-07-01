#Go
FROM golang:latest as build
MAINTAINER Wangwenwei <970074804@qq.com>
LABEL Description="This image is the go dev base images"  Version="1.0"
#change Goproxy 
RUN go env -w GOPROXY=https://goproxy.cn
RUN go env -w GO111MODULE=on
#配置工作目录:方便挂载
WORKDIR /go/src/darbuly_go/src
#设置包缓存目录为 /go/src/darbuly_go/pkg/mod,方便挂载
RUN go env -w GOMODCACHE="/go/src/darbuly_go/pkg/mod"

#todo 做更多工作