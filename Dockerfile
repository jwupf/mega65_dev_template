FROM mcr.microsoft.com/devcontainers/base:debian

RUN sed -i 's/^Components: main$/& contrib/' /etc/apt/sources.list.d/debian.sources &&\
    apt-get update &&\
    apt-get install -y wget xz-utils build-essential cmake ninja-build git vice libsdl2-dev libgtk-3-dev libreadline-dev fakeroot alien


#ADD --keep-git-dir=true https://github.com/llvm-mos/llvm-mos.git /opt/llvm-mos-src    
RUN git clone https://github.com/llvm-mos/llvm-mos.git /opt/llvm-mos-src
RUN (mkdir /opt/llvm-mos && \
        cd /opt/llvm-mos && \
        cmake -C /opt/llvm-mos-src/clang/cmake/caches/MOS.cmake -G Ninja -S /opt/llvm-mos-src/llvm && \
        ninja -j 3)

ENV PATH="/opt/llvm-mos/bin:${PATH}"

#ADD --keep-git-dir=true https://github.com/llvm-mos/llvm-mos-sdk.git /opt/llvm-mos-sdk-src
RUN git clone https://github.com/llvm-mos/llvm-mos-sdk.git /opt/llvm-mos-sdk-src
RUN (mkdir /opt/llvm-mos-sdk && \
        cd /opt/llvm-mos-sdk && \
        cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/opt/llvm-mos /opt/llvm-mos-sdk-src && \
        ninja install)

#ADD --keep-git-dir=true https://github.com/MEGA65/mega65-libc.git /opt/mega65-libc
RUN git clone https://github.com/MEGA65/mega65-libc.git /opt/mega65-libc-src
RUN (mkdir /opt/mega65-libc && \
        cd /opt/mega65-libc && \
        cmake -DCMAKE_PREFIX_PATH=/opt/llvm-mos /opt/mega65-libc-src && \
        make && \
        make install)

RUN chown -R 1000:1000 /opt/llvm-mos
RUN chown -R 1000:1000 /opt/llvm-mos-sdk
RUN chown -R 1000:1000 /opt/mega65-libc

ENTRYPOINT [ "/bin/bash" ]
CMD [ "/bin/bash" ]
