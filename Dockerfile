FROM alpine:latest

RUN mkdir /tmp/nutsh
WORKDIR /tmp/nutsh

COPY . .

RUN apk --no-cache update \
 && apk --no-cache add build-base libstdc++ gcc readline readline-dev \
 && make \
 && cp nutsh /usr/bin/nutsh \
 && adduser -S user \
 && apk del readline-dev build-base

USER user
WORKDIR /home/user

RUN mkdir -p Documents/School Documents/Work Pictures/Family Pictures/Art Music/Albums Music/Singles

ENTRYPOINT [ "nutsh" ]