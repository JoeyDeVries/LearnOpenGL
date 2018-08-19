#!/bin/bash

[ -n "$(which x11docker)" ] \
    || { echo "x11docker is required https://github.com/mviereck/x11docker"; exit 1; }

SCRIPT_DIR=$(dirname $(readlink -f "$0"))
PROJECT_DIR=$(dirname ${SCRIPT_DIR})

CMD=${@}
[ -n "${CMD}" ] \
    || { echo "Command is required"; exit 1; }

IMAGE=learnopengl

[ -n "$(docker images -q --filter=reference="${IMAGE}")" ] \
    || docker build -t ${IMAGE} ${SCRIPT_DIR}

x11docker \
    --gpu \
    --hostdisplay \
    --homedir ${HOME} \
    --clipboard \
    --stdout --stderr \
    --cap-default \
    --workdir ${PROJECT_DIR} \
    -- "--cap-add=SYS_PTRACE" \
    ${IMAGE} \
    ${CMD}
