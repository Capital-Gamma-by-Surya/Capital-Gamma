FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Replace the default mirror with a different one
RUN find /etc/apt -type f -exec sed -i 's|http://ports.ubuntu.com/ubuntu-ports|http://mirror.kumi.systems/ubuntu-ports/|g' {} +

RUN apt-get update && \
    apt-get install -y --fix-missing \
        sudo \
        cmake \
        g++ \
        ninja-build \
        python3-full \
        python3.12-venv \
        python3-pip && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

CMD ["sh"]
