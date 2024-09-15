FROM mcr.microsoft.com/devcontainers/base:debian

RUN sed -i 's/^Components: main$/& contrib/' /etc/apt/sources.list.d/debian.sources &&\
    apt-get update &&\
    apt-get install -y wget xz-utils build-essential cmake ninja-build git vice libsdl2-dev libgtk-3-dev libreadline-dev fakeroot alien

RUN wget -O- https://github.com/llvm-mos/llvm-mos-sdk/releases/latest/download/llvm-mos-linux.tar.xz | tar -xvJC /opt
ENV PATH="/opt/llvm-mos/bin:${PATH}"

#ADD --keep-git-dir=true https://github.com/MEGA65/mega65-libc.git /opt/mega65-libc
# WORKDIR /opt/mega65-libc
RUN git clone https://github.com/MEGA65/mega65-libc.git /opt/mega65-libc
RUN (cd /opt/mega65-libc ; cmake -DCMAKE_PREFIX_PATH=/opt/llvm-mos -B build)

WORKDIR /opt/mega65-libc/build
RUN make && \
    make install

RUN chown -R 1000:1000 /opt

ENTRYPOINT [ "/bin/bash" ]
CMD [ "/bin/bash" ]