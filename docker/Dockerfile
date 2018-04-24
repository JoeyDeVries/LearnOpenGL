FROM ubuntu:18.04

ARG TINI_VERSION='0.18.0'

RUN apt-get update \
    && apt-get install -y \
        libgtk2.0-0 libcanberra-gtk-module libxext-dev libxrender-dev libxtst-dev libxslt-dev dmz-cursor-theme \
        build-essential cmake git \
        libglfw3-dev libassimp-dev libxinerama-dev libxcursor-dev mesa-utils mesa-utils-extra \
        wget htop zip unzip nano

ADD https://github.com/krallin/tini/releases/download/v${TINI_VERSION}/tini /tini
RUN chmod +x /tini

ENTRYPOINT ["/tini", "--"]

CMD ["sleep", "infinity"]