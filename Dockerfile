FROM alpine:latest

RUN apk update
RUN apk add build-base
RUN apk add readline-dev
RUN apk add tree
RUN apk add curl

WORKDIR /tmp

RUN mkdir nutsh && cd nutsh
COPY . .
RUN make && cp nutsh /usr/bin/nutsh

RUN adduser -S user
USER user
WORKDIR /home/user

RUN mkdir -p Documents/School Documents/Work Pictures/Family Pictures/Art Music/Albums Music/Singles

ENTRYPOINT [ "nutsh" ]