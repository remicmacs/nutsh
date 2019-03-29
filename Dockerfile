FROM alpine:latest

RUN apk add build-base

WORKDIR /tmp

RUN mkdir nutsh && cd nutsh
COPY . .
RUN make && cp nutsh /usr/bin/nutsh
ENV USER root

ENTRYPOINT [ "nutsh" ]