FROM rootproject/root-ubuntu16

USER root
RUN apt-get update \
    && apt-get install -y liblz4-dev \
    && rm -rf /var/lib/apt/lists/*

COPY . /usr/local/dst2root
WORKDIR /usr/local/dst2root

RUN mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && cp dst2root /usr/local/bin/

WORKDIR /tmp
ENTRYPOINT ["/usr/local/bin/dst2root"]
