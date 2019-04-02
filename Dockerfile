FROM alpine:latest

RUN apk update
RUN apk add build-base
RUN apk add readline-dev

WORKDIR /tmp

RUN mkdir nutsh && cd nutsh
COPY . .
RUN make && cp nutsh /usr/bin/nutsh

RUN adduser -S user
USER user
WORKDIR /home/user

ENV USER user

ENTRYPOINT [ "nutsh" ]