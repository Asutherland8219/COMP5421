FROM --platform=linux/amd64 debian:bullseye

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    && apt-get clean

WORKDIR /app

COPY .. /app

CMD [ "bash" ]